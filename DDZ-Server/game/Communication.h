

#ifndef SERVER_DDZ_COMMUNICATION_H
#define SERVER_DDZ_COMMUNICATION_H
#include "Buffer.h"
#include "Codec.h"
#include "AesCrypto.h"
#include "MySqlConn.h"
#include "Room.h"
#include "RoomList.h"

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
    // 处理用户注册
    void handleRegister(Message* reqMsg, Message& resMsg);
    //处理用户登录
    void handleLogin(Message* reqMsg, Message& resMsg);
    //处理加入房间
    void handleAddRoom(Message* reqMsg, Message& resMsg);
    //处理游戏结束分数更新
    void handleGameOver(Message* reqMsg);
    //处理搜索房间
    void handleSearchRoom(Message* reqMsg, Message& resMsg);
    //处理离开房间
    void handleLeaveRoom(Message* reqMsg, Message& resMsg);
    //处理退出游戏
    void handleGoodBye(Message* reqMsg);

    //准备开始游戏
    void readyForPlay(std::string roomName, std::string data);
    // 发牌
    void dealCards(UserMap players);
    // 洗牌
    void initCards();
    //随机取出一张牌
    std::pair<int, int> takeOneCard();
    // 开始游戏
    void startGame(std::string roomName, UserMap players);
    // 转发数据
    void notifyOtherPlayers(std::string data, std::string roomName, std::string userName);
    // 重新开始游戏
    void restartGame(Message* reqMsg);


private:
    std::string m_aesKey;
    sendCallback sendMessage;
    deleteCallback disconnect;
    AesCrypto* m_aes = nullptr;
    MySqlConn *m_mysql = nullptr;
    Room* m_redis = nullptr;
    std::multimap<int, int> m_cards;//存储扑克牌分别为花色和点数
};


#endif //SERVER_DDZ_COMMUNICATION_H
