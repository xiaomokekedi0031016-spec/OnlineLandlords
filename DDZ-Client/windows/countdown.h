#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QTimer>
#include <QWidget>

/******************************************************************************
 *
 * @file       countdown.h
 * @brief      添加倒计时闹钟
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

class CountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CountDown(QWidget *parent = nullptr);

    void showCountDown();
    void stopCountDown();

signals:
    void notMuchTime();
    void timeout();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_clock;
    QPixmap m_number;
    QTimer* m_timer;
    int m_count;//总计时

};

#endif // COUNTDOWN_H
