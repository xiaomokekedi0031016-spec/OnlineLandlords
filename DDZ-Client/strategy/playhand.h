#ifndef PLAYHAND_H
#define PLAYHAND_H

#include "card.h"
#include "cards.h"

/******************************************************************************
 *
 * @file       playhand.h
 * @brief      出牌类, 用于分析玩家打出的牌的牌型, 点数, 以及相关的附属信息(比如顺子: 记录牌的数量), 以及比较两组牌的大小
 *
 * @author     badwoman
 * @date       2026/02/07
 * @history
 *****************************************************************************/

class PlayHand
{
public:
    // 出牌组合或者方式
    enum HandType
    {
        Hand_Unknown,               // 未知
        Hand_Pass,                  // 过

        Hand_Single,                // 单
        Hand_Pair,                  // 对

        Hand_Triple,                // 三个
        Hand_Triple_Single,         // 三带一
        Hand_Triple_Pair,           // 三带二

        Hand_Plane,                 // 飞机，555_666
        Hand_Plane_Two_Single,      // 飞机带单，555_666_3_4
        Hand_Plane_Two_Pair,        // 飞机带双，555_666_33_44

        Hand_Seq_Pair,              // 连对，33_44_55(_66...)
        Hand_Seq_Single,            // 顺子，34567(8...)

        Hand_Bomb,                  // 炸弹
        Hand_Bomb_Single,           // 炸弹带一个
        Hand_Bomb_Pair,             // 炸弹带一对
        Hand_Bomb_Two_Single,       // 炸弹带两单

        Hand_Bomb_Jokers,           // 王炸
        Hand_Bomb_Jokers_Single,    // 王炸带一个
        Hand_Bomb_Jokers_Pair,      // 王炸带一对
        Hand_Bomb_Jokers_Two_Single	// 王炸带两单
    };

    PlayHand();
    // 传递给类一组牌, 通过类分析出牌型, 点数, 以及相关的附属信息(比如顺子: 记录牌的数量)
    explicit PlayHand(Cards& cards);
    // 传递给类牌型, 点数, 以及相关的附属信息(比如顺子: 记录牌的数量)
    PlayHand(HandType type, Card::CardPoint pt, int extra);


    // 得到牌的属性信息
    HandType getHandType();
    Card::CardPoint getCardPoint();
    int getExtra();

    // 比较自己的牌和其他人的牌的大小
    bool canBeat(const PlayHand& other);

private:
    // 1. 对扑克牌进行分类: 1张的, 2张, 3张, 4张有多少种
    void classify(Cards& cards);

    // 2. 对牌型进行分类,分析出牌型, 点数, 以及相关的附属信息(比如顺子: 记录牌的数量)
    void judgeCardType();
    // 判断牌的类型
    bool isPass();              // 放弃出牌
    bool isSingle();            // 单
    bool isPair();              // 对
    bool isTriple();            // 三个(相同)
    bool isTripleSingle();      // 三带一
    bool isTriplePair();        // 三带二
    bool isPlane();             // 飞机
    bool isPlaneTwoSingle();    // 飞机带两单
    bool isPlaneTwoPair();      // 飞机带2对
    bool isSeqPair();           // 连对
    bool isSeqSingle();         // 顺子
    bool isBomb();              // 炸弹
    bool isBombSingle();        // 炸弹带一单
    bool isBombPair();          // 炸弹带一对
    bool isBombTwoSingle();     // 炸弹带两单
    bool isBombJokers();        // 王炸
    bool isBombJokersSingle();  // 王炸带一单
    bool isBombJokersPair();    // 王炸带一对
    bool isBombJokersTwoSingle();   // 王炸带两单

private:
    HandType m_type;//牌的类型
    Card::CardPoint m_pt;//牌的点数
    int m_extra;//牌的附属信息(比如顺子: 记录牌的数量)
    QVector<Card::CardPoint> m_oneCard;// 1张的牌的点数
    QVector<Card::CardPoint> m_twoCard;// 2张的牌的点数
    QVector<Card::CardPoint> m_threeCard;// 3张的牌的点数
    QVector<Card::CardPoint> m_fourCard;// 4张的牌的点数
};

#endif // PLAYHAND_H
