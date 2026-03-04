//
// Created by sqks on 2026/2/21.
//

#ifndef DDZ_SERVER_ROOM_H
#define DDZ_SERVER_ROOM_H
#include <string>
#include <sw/redis++/redis.h>


class Room {
public:
    Room() = default;
    ~Room();

    // 初始化 - 连接redis, redis++
    bool initEnvironment();
    // 清空数据
    void clear();
    // 保存RSA密钥对
    // key(filed, value)
    // hset
    void saveRsaSecKey(std::string field, std::string value);
    // 读秘钥
    // hget
    std::string rsaSecKey(std::string field);
    // 加入房间
    std::string joinRoom(std::string userName);
    bool joinRoom(std::string userName, std::string roomName);
    // 随机生成房间的名字
    std::string getNewRoomName();
    // 得到房间内玩家的数量
    int getPlayerCount(std::string roomName);
    // 存储玩家的分数
    void updatePlayerScore(std::string roomName, std::string userName, int score);
    // 通过玩家名找房间
    std::string whereAmI(std::string userName);
    // 查询玩家分数
    int playerScore(std::string roomName, std::string userName);

private:
    sw::redis::Redis* m_redis;
    const std::string OnePlayer = "OnePlayer";
    const std::string TwoPlayer = "TwoPlayers";
    const std::string ThreePlayer = "ThreePlayers";
    const std::string Invalid = "Invalid";
};


#endif //DDZ_SERVER_ROOM_H