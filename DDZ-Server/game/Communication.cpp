
#include <netinet/in.h>
#include <random>
#include "Communication.h"
#include "RsaCrypto.h"
#include "Log.h"
#include "Infomation.pb.h"
#include <iostream>
#include "JsonParse.h"

Communication::Communication() {
    JsonParse json;
    std::shared_ptr<DBInfo> info = json.getDatabaseInfo(JsonParse::Mysql);
    m_mysql = new MySqlConn;
    bool flag = m_mysql->connect(info->user, info->dbname, info->passwd, info->ip, info->port);
    // m_mysql = new MySqlConn;
    // bool flag = m_mysql->connect(
    //     "root",
    //     "happy-ddz",
    //     "123456",
    //     "192.168.80.100");
    // std::cout << "111111111111"<< std::endl;
    std::cout << mysql_error(m_mysql->m_conn) << std::endl;
    assert(flag);
}

Communication::~Communication() {
}

void Communication::setCallback(Communication::sendCallback func1, Communication::deleteCallback func2)
{
    sendMessage = func1;
    disconnect = func2;
}

void Communication::parseRequest(Buffer *buf) {
    // 读数据头
    std::string data = buf->data(sizeof(int));
    int length = *(int*)data.data();    // 大端长度
    // 读数据块
    length = ntohl(length);
    data = buf->data(length);
    if(m_aes)
    {
        data = m_aes->decrypt(data);
    }
    // 数据的反序列化
    Codec codec(data);
    Message resMsg;
    shared_ptr<Message> ptr = codec.decodeMsg();
    switch(ptr->reqcode) {
        case RequestCode::AesFenfa:
            handleAesFenfa(ptr.get(), resMsg);
            break;
        case RequestCode::UserLogin:
            handleLogin(ptr.get(), resMsg);
            break;
        case RequestCode::Register:
            handleRegister(ptr.get(), resMsg);
            break;
        default:
            break;
    }
    codec.reLoad(&resMsg);
    sendMessage(codec.encodeMsg());
}

void Communication::handleAesFenfa(Message *reqMsg, Message& resMsg) {
    RsaCrypto rsa("private.pem", RsaCrypto::PrivateKey);
    std::string aesKey = rsa.priKeyDecrypt(reqMsg->data1);
    // m_aesKey = rsa.priKeyDecrypt(reqMsg->data1);
    // 哈希校验
    Hash h(HashType::Sha224);
    // h.addData(m_aesKey);
    h.addData(aesKey);
    std::string res = h.result();
    resMsg.rescode = RespondCode::AesVerifyOK;
    if(reqMsg->data2 != res)
    {
        Debug("秘钥校验失败--aes");
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "Aes 秘钥的哈希校验失败了...";
    }
    else
    {
        m_aes = new AesCrypto(AesCrypto::AES_CBC_256, aesKey);
        Debug("秘钥校验成功了--aes");
    }
}

void Communication::handleRegister(Message *reqMsg, Message &resMsg) {
    // 查询数据库
    // select 字段 from 数据库表 where 条件;
    char sql[1024];
    sprintf(sql, "SELECT * FROM `user` WHERE `name`='%s';", reqMsg->userName.data());
    bool flag = m_mysql->query(sql);
    Debug("flag = %d, sql = %s", flag, sql);
    if(flag && !m_mysql->next())//sql执行成功但是没有查到数据
    {
        // 将注册信息写入到数据库
        m_mysql->transaction();
        sprintf(sql, "INSERT INTO `user`(name, passwd, phone, date) VALUES('%s', '%s', '%s', NOW());",
                reqMsg->userName.data(), reqMsg->data1.data(), reqMsg->data2.data());
        bool fl1 = m_mysql->update(sql);
        Debug("fl1 = %d, sql = %s", fl1, sql);
        sprintf(sql, "INSERT INTO `information`(name, score, status) VALUES('%s', 0, 0);",
                reqMsg->userName.data());
        bool fl2 = m_mysql->update(sql);
        Debug("fl2 = %d, sql = %s", fl2, sql);
        if(fl1 && fl2)
        {
            m_mysql->commit();
            resMsg.rescode = RespondCode::RegisterOk;
        }
        else
        {
            m_mysql->rollback();
            resMsg.rescode = RespondCode::Failed;
            resMsg.data1 = "数据库插入数据失败!";
        }
    }
    else
    {
        resMsg.rescode = RespondCode::Failed;
        resMsg.data1 = "用户名已经存在, 无法完成注册!";
    }
}

void Communication::handleLogin(Message *reqMsg, Message &resMsg) {
    char sql[1024];
    sprintf(sql, "SELECT * FROM `user` WHERE `name`='%s' AND passwd='%s' AND (select  count(*) from information where name = '%s' AND status=0);",
            reqMsg->userName.data(), reqMsg->data1.data(), reqMsg->userName.data());
    bool flag = m_mysql->query(sql);
    if(flag && m_mysql->next())
    {
        m_mysql->transaction();
        sprintf(sql, "update `information` set status=1 WHERE `name`='%s'", reqMsg->userName.data());
        bool flag1 = m_mysql->update(sql);
        if(flag1)
        {
            m_mysql->commit();
            resMsg.rescode = RespondCode::LoginOk;
            Debug("用户登录成功了.....................................");
            return;
        }
        m_mysql->rollback();
    }
    resMsg.rescode = RespondCode::Failed;
    resMsg.data1 = "用户名或者密码错误, 或者当前用户已经成功登录了...";
}
