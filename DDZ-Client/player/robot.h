#ifndef ROBOT_H
#define ROBOT_H

#include "player.h"
#include <QObject>

/******************************************************************************
 *
 * @file       robot.h
 * @brief      机器人派生类
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit Robot(QObject *parent = nullptr);

    void prepareCallLord() override;
    void preparePlayHand() override;
    void thinkCallLord() override;
    void thinkPlayHand() override;

};

#endif // ROBOT_H
