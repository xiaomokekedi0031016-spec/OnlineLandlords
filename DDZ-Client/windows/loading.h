#ifndef LOADING_H
#define LOADING_H

#include <QWidget>

/******************************************************************************
 *
 * @file       loading.h
 * @brief      进度条加载游戏
 *
 * @author     badwoman
 * @date       2026/02/05
 * @history
 *****************************************************************************/

class Loading : public QWidget
{
    Q_OBJECT
public:
    explicit Loading(QWidget *parent = nullptr);

signals:
protected:
    void paintEvent(QPaintEvent* event);

private:
    QPixmap m_bk;//加载背景图
    QPixmap m_progress;//加载进度图
    int m_dist = 15;//当前加载进度
};

#endif // LOADING_H
