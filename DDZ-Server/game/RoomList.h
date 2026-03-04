#ifndef SERVER_DDZ_ROOMLIST_H
#define SERVER_DDZ_ROOMLIST_H
#include <map>
#include <string>
#include <functional>
#include <mutex>
// 单例模式的类 - 懒汉模式
using callback = std::function<void(std::string)>;
using UserMap = std::map<std::string, callback>;
class RoomList
{
public:
    RoomList(const RoomList&) = delete;
    RoomList& operator=(const RoomList&) = delete;
    static RoomList* getInstance();

    // 添加用户
    void addUser(std::string roomName, std::string userName, callback sendMessage);

private:
    RoomList() = default;
    std::map<std::string, UserMap> m_roomMap;   // 共享资源, 需要多线程访问
    std::mutex m_mutex;
};


#endif //SERVER_DDZ_ROOMLIST_H
