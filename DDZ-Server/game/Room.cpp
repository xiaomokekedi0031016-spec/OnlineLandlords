//
// Created by sqks on 2026/2/21.
//

#include <random>
#include "Room.h"
#include "JsonParse.h"
#include "Log.h"

Room::~Room()
{
    if(m_redis)
    {
        delete m_redis;
    }
}


bool Room::initEnvironment()
{
    //tcp://127.0.0.1:6379
    JsonParse json;
    auto info = json.getDatabaseInfo(JsonParse::Redis);
    std::string connStr = "tcp://" + info->ip + ":" + std::to_string(info->port);
    m_redis = new sw::redis::Redis(connStr);
    // 测试连接
    if(m_redis->ping() == "PONG")
    {
        Debug("成功连接了 redis 服务器...");
        return true;
    }
    return false;
}


void Room::clear() {
    // flushdb
    m_redis->flushdb();
}

void Room::saveRsaSecKey(std::string field, std::string value)
{
    m_redis->hset("RSA", field, value);
}

std::string Room::rsaSecKey(std::string field) {
    auto value = m_redis->hget("RSA", field);
    if(value.has_value())
    {
        return value.value();
    }
    return std::string();
}

std::string Room::joinRoom(std::string userName)
{
    std::optional<std::string> room;
    do{
        // scard
        if(m_redis->scard(TwoPlayer) > 0)
        {
            // srandmember
            room = m_redis->srandmember(TwoPlayer);
            break;
        }
        if(m_redis->scard(OnePlayer) > 0)
        {
            // srandmember
            room = m_redis->srandmember(OnePlayer);
            break;
        }
        // 添加新的房间
        room = getNewRoomName();
    }while(0);
    // 加入到某个房间中
    joinRoom(userName, room.value());
    return room.value();
}
bool Room::joinRoom(std::string userName, std::string roomName) {
    if(m_redis->zcard(roomName) >= 3)
    {
        return false;
    }
    // 检查房间是否存在
    if(!m_redis->exists(roomName))
    {
        m_redis->sadd(OnePlayer, roomName);
    }
    // 移动房间
    else if(m_redis->sismember(OnePlayer, roomName))
    {
        m_redis->smove(OnePlayer, TwoPlayer, roomName);
    }
    else if(m_redis->sismember(TwoPlayer, roomName))
    {
        m_redis->smove(TwoPlayer, ThreePlayer, roomName);
    }
    else
    {
        assert(false);  // 异常情况, 直接退出
    }
    // 将玩家添加到房间, 使用的结构是 sortedset
    m_redis->zadd(roomName, userName, 0);
    // 将玩家存储起来 hashs -> 通过玩家找到玩家的房间
    m_redis->hset("Players", userName, roomName);
    return true;
}

std::string Room::getNewRoomName()
{
    // 创建随机设备对象
    std::random_device rd;
    // 创建随机数生成对象
    std::mt19937 gen(rd());
    // 创建随机数分布对象 -> 均匀分布
    std::uniform_int_distribution<int> dis(100000, 999999);
    int randNum = dis(gen);
    return std::to_string(randNum);
}

int Room::getPlayerCount(std::string roomName)
{
    int count = m_redis->zcard(roomName);
    return count;
}

void Room::updatePlayerScore(std::string roomName, std::string userName, int score)
{
    // 更新 -> sortedset
    m_redis->zadd(roomName, userName, score);
}

std::string Room::whereAmI(std::string userName)
{
    auto value = m_redis->hget("Players", userName);
    if(value.has_value())
    {
        return value.value();
    }
    return std::string();
}

int Room::playerScore(std::string roomName, std::string userName) {
    auto value = m_redis->zscore(roomName, userName);
    if(value.has_value())
    {
        return value.value();
    }
    return 0;
}
