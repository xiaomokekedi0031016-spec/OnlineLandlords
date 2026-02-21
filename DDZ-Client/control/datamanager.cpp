#include "datamanager.h"

DataManager* DataManager::m_data = new DataManager;

DataManager *DataManager::getInstance()
{
    return m_data;
}

void DataManager::setUserName(QByteArray name)
{
    m_userName = name;
}

void DataManager::setIP(QByteArray ip)
{
    m_ip = ip;
}

void DataManager::setPort(QByteArray port)
{
    m_port = port;
}

void DataManager::setCommunication(Communication *comm)
{
    m_commun = comm;
}


QByteArray DataManager::getUserName()
{
    return m_userName;
}

QByteArray DataManager::getIP()
{
    return m_ip;
}

QByteArray DataManager::getPort()
{
    return m_port;
}

Communication *DataManager::getCommunication()
{
    return m_commun;
}

void DataManager::setGameMode(GameMode mode)
{
    m_mode = mode;
}


bool DataManager::isNetworkMode()
{
    return m_mode == GameMode::Network ? true : false;
}

