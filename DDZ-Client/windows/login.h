#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>


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
    // 槽函数
    void onLogin();
    void onRegister();
    void onNetOK();

private:
    Ui::Login *ui;
    bool m_isConnected = false;
};

#endif // LOGIN_H
