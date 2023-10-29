#include "widget_loungeinfo.h"
#include "ui_widget_loungeinfo.h"

Widget_LoungeInfo::Widget_LoungeInfo(QWidget *parent, const LoungeData &loungeData) :
    QWidget(parent),
    ui(new Ui::Widget_LoungeInfo)
{
    ui->setupUi(this);

    ui->lbl_loungeID->setText(QString::number(loungeData.loungeID()));
    ui->lbl_playerNum->setText(QString::number(loungeData.playerNum()));
}

Widget_LoungeInfo::~Widget_LoungeInfo()
{
    delete ui;
}

void Widget_LoungeInfo::on_btn_enter_clicked()
{
    emit enterLounge();
}
