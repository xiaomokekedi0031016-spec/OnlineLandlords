#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "cards.h"
#include <QObject>

/******************************************************************************
 *
 * @file       player.h
 * @brief      玩家类基类
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

class Player : public QObject
{
    Q_OBJECT
public:
    enum Role{Lord, Farmer};    // 角色
    enum Sex{Man, Woman};       // 性别
    enum Direction{Left, Right};    // 头像的显示方位
    enum Type{Robot, User, UnKnow}; // 玩家的类型
    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);
    // 名字
    void setName(QString name);
    QString getName();

    // 角色
    void setRole(Role role);
    Role getRole();

    // 性别
    void setSex(Sex sex);
    Sex getSex();

    // 方位
    void setDirection(Direction direction);
    Direction getDirection();

    // 玩家类型
    void setType(Type type);
    Type getType();

    // 玩家的分数
    void setScore(int score);
    int getScore();

    // 游戏结果
    void setWin(bool flag);
    bool isWin();

    //设置上家下家
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    //叫地主/抢地主
    void grabLordBet(int point);

    //存储扑克牌(发牌的时候得到)
    void storeDispatchCard(const Card& card);
    void storeDispatchCard(const Cards& cards);//(底牌三张)

    //得到所有的扑克牌(用于显示在界面上)
    Cards getCards();
    //清空玩家手中所有的牌(用于重新开始游戏)
    void clearCards();

    //出牌
    void playHand(const Cards& cards);

    // 获取当前的出牌玩家对象以及这个玩家打出的牌
    Player* getPendPlayer();
    Cards getPendCards();
    //存储出牌玩家对象以及这个玩家打出的牌
    void storePendingInfo(Player* player, const Cards& cards);

    virtual void prepareCallLord();//准备叫地主(通常是创建一个子线程去思考叫地主))
    virtual void preparePlayHand();//准备出牌(通常是创建一个子线程去思考出牌))
    virtual void thinkCallLord();//虚函数,考虑叫地主
    virtual void thinkPlayHand();//虚函数,考虑出牌

signals:
    //通知已经发牌了
    void notifyPickCards(Player* player, const Cards& cards);
    // 通知已经叫地主下注
    void notifyGrabLordBet(Player* player, int bet);
    //通知已经出牌
    void notifyPlayHand(Player* player, const Cards& card);

protected:
    int m_score = 0;//玩家分数
    QString m_name;//玩家名字
    Role m_role;//玩家角色
    Sex m_sex;//玩家性别
    Direction m_direction;//玩家方位
    Type m_type;//玩家类型
    bool m_isWin = false;//玩家是否获胜
    Player* m_prev = nullptr;//上家
    Player* m_next = nullptr;//下家
    Cards m_cards;//玩家手中的牌
    Player* m_pendPlayer = nullptr;//待出牌玩家
    Cards m_pendCards;//待出牌玩家打出的牌
};

#endif // PLAYER_H
