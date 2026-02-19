#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include "card.h"
#include "player.h"

/******************************************************************************
 *
 * @file       cardpanel.h
 * @brief      用于显示卡牌窗口
 *
 * @author     badwoman
 * @date       2026/02/06
 * @history
 *****************************************************************************/

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    // 设置获取图片函数(设置一张卡牌的正面和背面)
    void setImage(const QPixmap &front, const QPixmap &back);
    QPixmap getImage();

    // 扑克牌显示那一面
    void setFrontSide(bool flag);
    bool isFrontSide();

    // 记录窗口是否被选中了
    void setSeclected(bool flag);
    bool isSelected();

    // 扑克牌的花色以及点数
    void setCard(const Card& card);
    Card getCard();

    // 扑克牌的所有者
    void setOwner(Player* player);
    Player* getOwner();

    // 模拟扑克牌的点击事件
    void clicked();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

signals:
    //卡牌被选中的信号
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;//扑克牌正面图片
    QPixmap m_back;//扑克牌背面图片
    bool m_isfront = true;
    bool m_isSelect = false;
    Card m_card;
    Player* m_owner = nullptr;
};

#endif // CARDPANEL_H
