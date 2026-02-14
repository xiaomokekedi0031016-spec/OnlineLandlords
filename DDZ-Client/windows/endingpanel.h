#ifndef ENDINGPANEL_H
#define ENDINGPANEL_H

#include "scorepanel.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget>

/******************************************************************************
 *
 * @file       endingpanel.h
 * @brief      计分板
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class EndingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit EndingPanel(bool isLord, bool isWin, QWidget *parent = nullptr);

    void setPlayerScore(int left, int right, int me);

signals:
    void continueGame();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_bk;//背景图
    QLabel* m_title;//标题
    ScorePanel *m_score;//分数
    QPushButton* m_continue;//继续游戏的面板

};

#endif // ENDINGPANEL_H
