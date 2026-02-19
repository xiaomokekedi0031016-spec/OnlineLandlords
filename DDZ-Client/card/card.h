#ifndef CARD_H
#define CARD_H

#include <QVector>

/******************************************************************************
 *
 * @file       card.h
 * @brief      卡牌类，表示一张扑克牌属性
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

class Card
{
public:
    // 花色
    enum CardSuit
    {
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };
    // 点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,    // small joker
        Card_BJ,     // big joker
        Card_End//16
    };

    Card();
    Card(CardPoint point, CardSuit suit);

    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);
    CardPoint point() const;
    CardSuit suit() const;

private:
    CardPoint m_point;
    CardSuit m_suit;
};


// 定义类型的别名
using CardList = QVector<Card>;
//任何放进QSet/QHash的key类型，必须实现两个东西：1.operator==用于判断两个对象是否相等
                                              // 2.qHash(const T&, uint seed)函数，用于计算哈希值

// 操作符重载 (==)
bool operator ==(const Card& left, const Card& right);
// 重写全局函数 qHash >> 只需要保证每张扑克牌的哈希值不一样即可
uint qHash(const Card& card);

//对象比较
bool lessSort(const Card& c1, const Card& c2);
bool greaterSort(const Card& c1, const Card& c2);
bool operator <(const Card& c1, const Card& c2);//处理后续QMap底层红黑树自动排序需要重写<重载

#endif // CARD_H
