
#include <netinet/in.h>
#include <random>
#include "Communication.h"
#include "RsaCrypto.h"
#include "Log.h"
#include "Infomation.pb.h"

Communication::Communication() {
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
            break;
        case RequestCode::Register:
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
