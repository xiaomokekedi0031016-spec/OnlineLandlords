#ifndef USERPLAYER_H
#define USERPLAYER_H

#include "player.h"
#include <QObject>

/******************************************************************************
 *
 * @file       userplayer.h
 * @brief      用户玩家类
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit UserPlayer(QObject *parent = nullptr);

    void prepareCallLord() override;
    void preparePlayHand() override;

signals:
    void startCountDown();

};

#endif // USERPLAYER_H
