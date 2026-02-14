#ifndef CARDS_H
#define CARDS_H
#include "card.h"

#include <QSet>

/******************************************************************************
 *
 * @file       cards.h
 * @brief      多张卡牌类(例如发三张底牌需要add(cards))
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

class Cards
{
public:
    // 排序类型
    enum SortType{Asc, Desc, NoSort};

    Cards();
    // 添加扑克牌
    void add(const Card& card);//单个
    void add(const Cards& cards);//多个
    void add(const QVector<Cards>& cards);
    // 一次性插入多个数据 (操作符重载 << )
    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);
    // 删除扑克牌
    void remove(const Card& card);
    void remove(const Cards& cards);
    void remove(const QVector<Cards>& cards);
    // 扑克牌的数量
    int cardCount();
    // 是否为空
    bool isEmpty();
    bool isEmpty() const;
    // 清空
    void clear();
    // 最大点数
    Card::CardPoint maxPoint();
    // 最小点数
    Card::CardPoint minPoint();
    // 获取指定点数的牌的数量
    int pointCount(Card::CardPoint point);
    // 某张牌是否在集合中
    bool contains(const Card& card);
    bool contains(const Cards& cards);
    // 随机取出一张扑克牌
    Card takeRandomCard();
    // 转换为有序的卡牌列表
    CardList toCardList(SortType type = Desc);


private:
    //QSet存储的是无序(且不重复)的，用于存储卡牌，而且删除和添加操作效率较高
    QSet<Card> m_cards;
};

#endif // CARDS_H
