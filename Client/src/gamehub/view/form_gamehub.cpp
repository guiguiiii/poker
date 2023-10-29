#include "form_gamehub.h"
#include "ui_form_gamehub.h"

#include "src/common/view/widget_tips.h"
#include "src/common/view/widget_pfp.h"

#include <QTimer>
#include <QTime>

Form_GameHub::Form_GameHub(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_GameHub)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));

    // Init time UI
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        ui->lbl_time->setText(QTime::currentTime().toString("hh:mm:ss"));
    });
    timer->start(1000);
}

Form_GameHub::~Form_GameHub()
{
    delete ui;
}

void Form_GameHub::initLounges(const QVector<LoungeData> &lounges)
{
    for(auto it = m_lounges.begin(); it != m_lounges.end(); it++){
        it.value()->deleteLater();
        m_lounges.remove(it.key());
    }

    for(const LoungeData &lounge: lounges)
        this->newWidgetLoungeInfo(lounge);

    ui->lbl_loungeNum->setText(QString::number(lounges.size()));
}

void Form_GameHub::initPublicData(const PublicData &publicData)
{
    ui->lbl_username->setText(publicData.nickname());
    ui->lbl_pfp->setPixmap(publicData.pfp());
    m_pfp = publicData.pfp();
}

void Form_GameHub::enterLoungeFailed(int status)
{
    if(status == 2){
        (new Widget_Tips(this, "游戏", "房间已满人，进入房间失败"))->setVisible(true);
    }else if(status == 3){
        (new Widget_Tips(this, "游戏", "房间不存在，进入房间失败"))->setVisible(true);
    }
}

void Form_GameHub::newWidgetLoungeInfo(const LoungeData &loungeData)
{
    auto widget = new Widget_LoungeInfo(ui->Widget_sa_Lounges,loungeData);
    connect(widget, &Widget_LoungeInfo::enterLounge, this, &Form_GameHub::widget_loungeInfo_clicked);
    ui->Widget_sa_Lounges->layout()->addWidget(widget);
    ui->Widget_sa_Lounges->layout()->removeItem(ui->VSpacer);
    ui->Widget_sa_Lounges->layout()->addItem(ui->VSpacer);
    widget->setVisible(true);

    m_lounges.insert(loungeData.loungeID(),widget);
}

void Form_GameHub::widget_loungeInfo_clicked()
{
    auto widget = static_cast<Widget_LoungeInfo *>(sender());
    int loungeID = m_lounges.key(widget);
    emit signal_enterLounge(loungeID);
}

void Form_GameHub::on_btn_back_clicked()
{
    emit signal_moveToStart();
}

void Form_GameHub::on_btn_quickStart_clicked()
{
    emit signal_quickStart();
}

void Form_GameHub::on_btn_newLounge_clicked()
{
    emit signal_newGame();
}

void Form_GameHub::on_btn_loungeByID_clicked()
{
    int loungeID = ui->le_loungeID->text().toInt();
    emit signal_enterLounge(loungeID);
}

void Form_GameHub::on_le_loungeID_returnPressed()
{
    this->on_btn_loungeByID_clicked();
}

void Form_GameHub::on_btn_refresh_clicked()
{
    emit signal_getLounges();
}

void Form_GameHub::on_btn_pfp_clicked()
{
    (new Widget_PFP(this,m_pfp))->setVisible(true);
}
