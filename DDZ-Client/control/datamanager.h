#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QByteArray>
#include "cards.h"
#include "communication.h"

// 饿汉模式
class DataManager
{
public:
    enum GameMode{Single, Network};
    enum RoomMode{Auto, Manual};

    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
    static DataManager* getInstance();

    // 设置数据
    void setUserName(QByteArray name);
    void setIP(QByteArray ip);
    void setPort(QByteArray port);
    void setCommunication(Communication* comm);
    void setGameMode(GameMode mode);
    void setRoomMode(RoomMode mode);
    void setRoomName(QByteArray roomName);
    void setCards(Cards cs, Cards last);

    // 获取数据
    QByteArray getUserName();
    QByteArray getIP();
    QByteArray getPort();
    Communication* getCommunication();
    bool isNetworkMode();
    bool isManualMode();
    QByteArray getRoomName();
    Cards getCards();
    Cards getLast3Cards();

private:
    DataManager() = default;
    static DataManager* m_data;

    QByteArray m_userName;
    //房间名
    QByteArray m_roomName;
    QByteArray m_ip = "192.168.80.100";
    QByteArray m_port = "8888";
    Communication* m_commun;
    GameMode m_mode;
    RoomMode m_roomMode;
    Cards m_cs;
    Cards m_last;
};

#endif // DATAMANAGER_H
