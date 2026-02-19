

#ifndef SERVER_DDZ_COMMUNICATION_H
#define SERVER_DDZ_COMMUNICATION_H
#include "Buffer.h"
#include "Codec.h"
#include "AesCrypto.h"
class Communication
{
public:
    Communication();
    ~Communication();
    // 设置回调
    using sendCallback = function<void(std::string)>;
    using deleteCallback = function<void()>;
    void setCallback(sendCallback func1, deleteCallback fucn2);
    // 解析客户端发送过来的数据
    void parseRequest(Buffer* buf);
    // 处理秘钥分发
    void handleAesFenfa(Message* reqMsg, Message& resMsg);


private:
    std::string m_aesKey;
    sendCallback sendMessage;
    deleteCallback disconnect;
    AesCrypto* m_aes = nullptr;
};


#endif //SERVER_DDZ_COMMUNICATION_H
