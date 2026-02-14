#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

#include <QWidget>

/******************************************************************************
 *
 * @file       animationwindow.h
 * @brief      特效动画窗口类，负责显示游戏中的各种特效动画
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class AnimationWindow : public QWidget
{
    Q_OBJECT
public:
    enum Type{Sequence, Pair};
    explicit AnimationWindow(QWidget *parent = nullptr);

    // 显示下注分数
    void showBetScore(int bet);
    // 显示顺子和连对
    void showSequence(Type type);
    // 显示王炸
    void showJokerBomb();
    // 显示炸弹
    void showBomb();
    // 显示飞机
    void showPlane();
signals:

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_image;
    int m_x = 0;//为了飞机
    int m_index = 0;//绘制图片的索引
};

#endif // ANIMATIONWINDOW_H
