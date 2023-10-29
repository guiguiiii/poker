#include "widget_playerinfo.h"
#include "ui_widget_playerinfo.h"

Widget_PlayerInfo::Widget_PlayerInfo(QWidget *parent, const PlayerData &playerData) :
    QWidget(parent),
    ui(new Ui::Widget_PlayerInfo)
{
    ui->setupUi(this);

    ui->lbl_username->setText(playerData.nickname());
    ui->lbl_pfp->setPixmap(playerData.pfp());
    this->setIsReady(playerData.isReady());
}

Widget_PlayerInfo::~Widget_PlayerInfo()
{
    delete ui;
}

void Widget_PlayerInfo::setIsReady(bool isReady)
{
    if(isReady)
        ui->lbl_status->setText("准备中");
    else
        ui->lbl_status->setText("");
}
