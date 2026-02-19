#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "animationwindow.h"
#include "bgmcontrol.h"
#include "cardpanel.h"
#include "countdown.h"
#include "gamecontrol.h"
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QTimer>

/******************************************************************************
 *
 * @file       gamepanel.h
 * @brief      游戏主窗口类
 *
 * @author     badwoman
 * @date       2026/02/10
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    // 特效动画类型
    enum AnimationType{ShunZi, LianDui, Plane, JokerBomb, Bomb, Bet};

    // 初始化游戏控制类信息
    void gameControlInit();
    // 更新分数面板的分数
    void updatePlayerScore();
    //切割并且存储游戏图片
    void initCardMap();
    // 裁剪图片
    void cropImage(QPixmap& pix, int x, int y, Card& c);
    //初始化游戏按钮组
    void initButtonsGroup();
    // 初始化玩家在窗口中的上下文环境
    void initPlayerContext();
    // 初始化游戏场景
    void initGameScene();
    // 处理游戏的状态
    void gameStatusPrecess(GameControl::GameStatus status);
    // 发牌
    void startDispatchCard();
    //移动扑克牌
    void cardMoveStep(Player* player, int curPos);
    //处理分发得到的扑克牌
    void disposeCard(Player* player, const Cards& cards);
    // 更新扑克牌在窗口中的显示
    void updatePlayerCards(Player* player);
    // 加载玩家头像
    QPixmap loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role);


    //定时器的处理动作
    void onDispatchCard();
    //处理玩家状态的变化
    void onPlayerStatusChanged(Player* player, GameControl::PlayerStatus status);
    //处理玩家抢地主
    void onGrabLordBet(Player* player, int bet, bool flag);
    // 处理玩家的出牌
    void onDisposePlayHand(Player* player, const Cards& cards);
    // 处理玩家选牌
    void onCardSelected(Qt::MouseButton button);
    // 处理用户玩家出牌
    void onUserPlayHand();
    // 用户玩家放弃出牌
    void onUserPass();

    //显示特效动画
    void showAnimation(AnimationType type, int bet = 0);
    //隐藏下一个玩家上轮打出的牌
    void hidePlayerDropCards(Player* player);
    // 显示玩家的最终得分
    void showEndingScorePanel();
    // 初始化闹钟倒计时
    void initCountDown();

protected:
    void paintEvent(QPaintEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

private:
    enum CardAlign{Horizontal, Vertical};
    struct PlayerContext//玩家的上下文环境
    {
        // 1. 玩家扑克牌显示的区域
        QRect cardRect;
        // 2. 出牌的区域
        QRect playHandRect;
        // 3. 扑克牌的对齐方式(水平 or 垂直)
        CardAlign align;
        // 4. 扑克牌显示正面还是背面
        bool isFrontSide;
        // 5. 游戏过程中的提示信息, 比如: 不出
        QLabel* info;
        // 6. 玩家的头像
        QLabel* roleImg;
        // 7. 玩家刚打出的牌
        Cards lastCards;
    };

    Ui::GamePanel *ui;
    QPixmap m_bkImage;//背景图(游戏的)
    GameControl* m_gameCtl;//游戏控制类对象
    QVector<Player*> m_playerList;//玩家列表
    QSize m_cardSize;//单张扑克牌大小
    QPixmap m_cardBackImg;//扑克牌背面图片
    QMap<Card, CardPanel*> m_cardMap;//卡牌和卡牌面板的映射关系
    QMap<Player*, PlayerContext> m_contextMap;//玩家和玩家上下文环境的映射关系
    CardPanel* m_baseCard;//发牌区的扑克牌
    CardPanel* m_moveCard;//发牌过程中移动的扑克牌
    QVector<CardPanel*> m_last3Card;//最后的三张底牌
    QPoint m_baseCardPos;//发牌区的扑克牌位置
    GameControl::GameStatus m_gameStatus;//当前游戏状态
    QTimer* m_timer;//定时器
    AnimationWindow* m_animation;//动画窗口
    CardPanel* m_curSelCard;//当前选中的扑克牌
    QSet<CardPanel*> m_selectCards;//当前选中的扑克牌集合
    QRect m_cardsRect;//玩家扑克牌的展示区域
    QHash<CardPanel*, QRect> m_userCards;//当前用户玩家的扑克牌和扑克牌区域的映射关系
    CountDown* m_countDown;//倒计时闹钟
    BGMControl* m_bgm;//添加bgm
};
#endif // GAMEPANEL_H
