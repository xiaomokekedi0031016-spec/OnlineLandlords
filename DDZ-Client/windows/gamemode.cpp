#include "gamemode.h"
#include "codec.h"
#include "datamanager.h"
#include "ui_gamemode.h"
#include "gamepanel.h"

#include <QCloseEvent>

GameMode::GameMode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameMode)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->singleModeBtn, &QPushButton::clicked, this, [=](){
        GamePanel* panel = new GamePanel;
        connect(panel, &GamePanel::panelClose, this, &GameMode::show);
        panel->show();
        hide();
        DataManager::getInstance()->setGameMode(DataManager::Single);
    });

    connect(ui->netModeBtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        DataManager::getInstance()->setGameMode(DataManager::Network);
    });
}

GameMode::~GameMode()
{
    delete ui;
}


void GameMode::closeEvent(QCloseEvent *ev)
{
    if(ui->stackedWidget->currentIndex() == 1)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ev->ignore();//ignore就不会让窗口进行关闭，accept是会的
    }
    else
    {
        ev->accept();

    }
}

