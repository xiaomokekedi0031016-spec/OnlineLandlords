#ifndef ROBOTPLAYHAND_H
#define ROBOTPLAYHAND_H

#include "player.h"
#include <QRunnable>

/******************************************************************************
 *
 * @file       robotplayhand.h
 * @brief      出牌类，基于QThread类实现，负责处理机器人玩家出牌的逻辑，调用Player类中的thinkPlayHand函数
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class RobotPlayHand : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RobotPlayHand(Player* player, QObject *parent = nullptr);

signals:
protected:
    void run() override;

private:
    Player* m_player;

};

#endif // ROBOTPLAYHAND_H
