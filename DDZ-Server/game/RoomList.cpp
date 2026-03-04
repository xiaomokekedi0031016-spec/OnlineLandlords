//
// Created by sqks on 2026/3/4.
//

#include "RoomList.h"

RoomList * RoomList::getInstance() {
    static RoomList instance;
    return &instance;
}

void RoomList::addUser(std::string roomName, std::string userName, callback sendMessage)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    // 在当前map中搜索roomName
    if(m_roomMap.find(roomName) != m_roomMap.end())
    {
        // 找到了
        auto &value = m_roomMap[roomName];
        value.insert(make_pair(userName, sendMessage));
    }
    else
    {
        // 没找到
        UserMap value = {{userName, sendMessage}};
        m_roomMap.insert(make_pair(roomName, value));
    }
}