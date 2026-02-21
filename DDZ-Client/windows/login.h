#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include "codec.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    // 校验数据
    bool verifyData(QLineEdit* edit);
    // 连接服务器
    void startConnect(Message* msg);
    // 槽函数
    void onLogin();
    void onRegister();
    void onNetOK();
    // 保存数据
    void saveUserInfo();
    // 加载数据
    void loadUserInfo();

private:
    Ui::Login *ui;
    //默认的连接状态
    bool m_isConnected = false;
    //密钥
    const QByteArray KEY = "天长地久有时尽,此恨绵绵无绝期!";
};

#endif // LOGIN_H
