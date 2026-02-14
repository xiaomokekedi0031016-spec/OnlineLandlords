#ifndef ROBOTGRAPLORD_H
#define ROBOTGRAPLORD_H

#include <QRunnable>
#include "player.h"

/******************************************************************************
 *
 * @file       robotgraplord.h
 * @brief      叫地主类，用于机器人玩家在叫地主阶段的思考，基于多线程实现，避免界面卡顿
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/


class RobotGrapLord : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RobotGrapLord(Player* player, QObject *parent = nullptr);

protected:
    void run();

signals:
private:
    Player* m_player;

};

#endif // ROBOTGRAPLORD_H
