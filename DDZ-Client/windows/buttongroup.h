#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

/******************************************************************************
 *
 * @file       buttongroup.h
 * @brief      按钮组，根据游戏状态的不同，显示不同的按钮
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum Panel{Start, PlayCard, PassOrPlay, CallLord, Empty};
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    // 初始化按钮
    void initButtons();

    // 处理page页的切换
    void selectPanel(Panel type, int bet = 0);

signals:
    // 开始游戏
    void startGame();
    // 出牌
    void playHand();
    // 不出牌
    void pass();
    // 抢地主
    void betPoint(int bet);

private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H
