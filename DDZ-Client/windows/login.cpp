#include "login.h"
#include "ui_login.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "datamanager.h"
#include "gamepanel.h"
#include <QThreadPool>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // setFixedSize(480, 376);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->homeBtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->regUser, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->netSetBtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    // 数据校验
    QRegularExpression expreg("^[a-zA-Z0-9_]{3,16}$");
    QRegularExpressionValidator *val1 = new QRegularExpressionValidator(expreg, this);
    ui->userName->setValidator(val1);
    ui->regUserName->setValidator(val1);
    /*
     * 密码:
     *  1. 长度为4到12个字符
     *  2. 包含至少一个大写字母、小写字母、数字和特殊字符
    */
    expreg.setPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{4,20}$");
    QRegularExpressionValidator *val2 = new QRegularExpressionValidator(expreg, this);
    ui->password->setValidator(val2);
    ui->regPasswrod->setValidator(val2);

    // 手机号校验
    expreg.setPattern("^1[3456789]\\d{9}$");
    QRegularExpressionValidator *val3 = new QRegularExpressionValidator(expreg, this);
    ui->phone->setValidator(val3);

    // IP校验
    expreg.setPattern("^((\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])\\.){3}(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])$");
    QRegularExpressionValidator *val4 = new QRegularExpressionValidator(expreg, this);
    ui->ipAddr->setValidator(val4);

    // 端口校验
    expreg.setPattern("^(0|([1-9]\\d{0,3})|([1-5]\\d{4})|(6[0-4]\\d{3})|(65[0-4]\\d{2})|(655[0-2]\\d)|(6553[0-5]))$");
    QRegularExpressionValidator *val5 = new QRegularExpressionValidator(expreg, this);
    ui->port->setValidator(val5);

    // 处理按钮点击事件
    connect(ui->loginBtn, &QPushButton::clicked, this, &Login::onLogin);
    connect(ui->registerBtn, &QPushButton::clicked, this, &Login::onRegister);
    connect(ui->netOkBtn, &QPushButton::clicked, this, &Login::onNetOK);

    // 设置线程池最大的线程数量
    QThreadPool::globalInstance()->setMaxThreadCount(8);
}

Login::~Login()
{
    delete ui;
}


bool Login::verifyData(QLineEdit* edit)
{
    if(edit->hasAcceptableInput() == false)
    {
        edit->setStyleSheet("border: 2px solid red;");
        return false;
    }
    else
    {
        edit->setStyleSheet("none");
    }
    return true;
}


void Login::onLogin()
{
    bool flag1 = verifyData(ui->userName);
    bool flag2 = verifyData(ui->password);
    if(flag1 && flag2)
    {
        GamePanel* gamePanel = new GamePanel;
        gamePanel->show();
    }
}

void Login::onRegister()
{
    bool flag1 = verifyData(ui->regUserName);
    bool flag2 = verifyData(ui->regPasswrod);
    bool flag3 = verifyData(ui->phone);
    if(flag1 && flag2 && flag3)
    {

    }
}

void Login::onNetOK()
{
    bool flag1 = verifyData(ui->ipAddr);
    bool flag2 = verifyData(ui->port);
    if(flag1 && flag2)
    {
        DataManager* instance = DataManager::getInstance();
        instance->setIP(ui->ipAddr->text().toUtf8());
        instance->setPort(ui->port->text().toUtf8());
    }
}

