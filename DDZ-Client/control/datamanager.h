#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QByteArray>
#include "communication.h"

// 饿汉模式
class DataManager
{
public:
    enum GameMode{Single, Network};

    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
    static DataManager* getInstance();

    // 设置数据
    void setUserName(QByteArray name);
    void setIP(QByteArray ip);
    void setPort(QByteArray port);
    void setCommunication(Communication* comm);
    void setGameMode(GameMode mode);

    // 获取数据
    QByteArray getUserName();
    QByteArray getIP();
    QByteArray getPort();
    Communication* getCommunication();
    bool isNetworkMode();
private:
    DataManager() = default;
    static DataManager* m_data;

    QByteArray m_userName;
    QByteArray m_ip = "192.168.80.100";
    QByteArray m_port = "8888";
    Communication* m_commun;

    GameMode m_mode;
};

#endif // DATAMANAGER_H
