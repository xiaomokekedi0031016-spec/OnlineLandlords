#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QByteArray>

// 饿汉模式
class DataManager
{
public:
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
    static DataManager* getInstance();

    // 设置数据
    void setUserName(QByteArray name);
    void setIP(QByteArray ip);
    void setPort(QByteArray port);

    // 获取数据
    QByteArray getUserName();
    QByteArray getIP();
    QByteArray getPort();
private:
    DataManager() = default;
    static DataManager* m_data;

    QByteArray m_userName;
    QByteArray m_ip = "127.0.0.1";
    QByteArray m_port = "8888";
};

#endif // DATAMANAGER_H
