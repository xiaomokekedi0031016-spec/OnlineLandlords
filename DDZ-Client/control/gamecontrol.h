#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"

/******************************************************************************
 *
 * @file       gamecontrol.h
 * @brief      游戏控制类，负责管流程、管玩家、管牌、管叫地主和出牌，不自己玩，只负责调度
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

//叫地主记录
struct BetRecord
{
    BetRecord()
    {
        reset();
    }
    void reset()
    {
        player = nullptr;
        bet = 0;
        times = 0;
    }
    Player* player;
    int bet;
    int times;  // 第几次叫地主
};

class GameControl : public QObject
{
    Q_OBJECT
public:
    //状态是给机器人玩家服务的
    // 游戏状态
    enum GameStatus
    {
        DispatchCard,//发牌
        CallingLord,//叫地主
        PlayingHand//出牌
    };
    // 玩家状态
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };
    explicit GameControl(QObject *parent = nullptr);
    // 初始化玩家信息
    void playerInit();

    // 得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    //当前玩家的处理
    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 得到出牌玩家和打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    // 初始化卡牌信息
    void initAllCards();
    // 每次发一张牌
    Card takeOneCard();
    // 得到最后的三张底牌
    Cards getSurplusCards();
    //当前游戏结束，重置牌数据
    void resetCardData();
    //得到玩家下注的最高分数
    int getPlayerMaxBet();


    // 准备叫地主 >> 游戏正式开始
    void startLordCard();
    // 成为地主 >> 叫地主结束
    void becomeLord(Player *player, int bet);

    // 处理叫地主
    void onGrabBet(Player* player, int bet);
    // 处理出牌
    void onPlayHand(Player *player, const Cards &card);

    // 清空所有玩家的得分
    void clearPlayerScore();


signals:
    //玩家状态改变
    void playerStatusChanged(Player* player, PlayerStatus status);
    //通知玩家抢地主了
    void notifyGrabLordBet(Player* player, int bet, bool flag);
    // 游戏状态变化
    void gameStatusChanged(GameStatus status);
    // 通知玩家出牌了
    void notifyPlayHand(Player* player, const Cards& card);
    //给玩家传递出牌数据
    void pendingInfo(Player* player, const Cards& card);

private:
    //左侧和右侧机器人
    Robot* m_robotLeft = nullptr;
    Robot* m_robotRight = nullptr;
    //活人
    UserPlayer* m_user = nullptr;
    //当前玩家
    Player* m_currPlayer = nullptr;
    //出牌玩家和打出的牌
    Player* m_pendPlayer = nullptr;
    Cards m_pendCards;
    //存储所有扑克牌
    Cards m_allCards;
    //叫地主记录(叫的分数、玩家、序列)
    BetRecord m_betRecord;
    //底分
    int m_curBet = 0;
};

#endif // GAMECONTROL_H
