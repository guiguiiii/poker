#include "form_lounge.h"
#include "ui_form_lounge.h"

Form_Lounge::Form_Lounge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Lounge)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));

    m_isReady = 0;
    ui->btn_ready->setText("准备游戏");
}

Form_Lounge::~Form_Lounge()
{
    delete ui;
}

void Form_Lounge::setLoungeID(int loungeID)
{
    ui->lbl_gameID->setText(QString::number(loungeID));
}

void Form_Lounge::initPlayers(const QVector<PlayerData> &players)
{
    for(auto it = m_players.begin(); it != m_players.end(); it++){
        it.value()->deleteLater();
        m_players.remove(it.key());
    }

    for(const PlayerData &playerData: players)
        this->newWidgetPlayerInfo(playerData);
}

void Form_Lounge::playerJoin(const PublicData &publicData)
{
    PlayerData playerData;
    playerData.setId(publicData.id());
    playerData.setNickname(publicData.nickname());
    playerData.setPfp(publicData.pfp());
    playerData.setIsReady(false);

    this->newWidgetPlayerInfo(playerData);
}

void Form_Lounge::playerLeave(int id)
{
    auto widget = m_players.value(id);
    widget->deleteLater();
    m_players.remove(id);
}

void Form_Lounge::playerReady(int id, bool isReady)
{
    auto widget = m_players.value(id);
    widget->setIsReady(isReady);
}

void Form_Lounge::newWidgetPlayerInfo(const PlayerData &playerData)
{
    auto widget = new Widget_PlayerInfo(ui->Widget_PlayerList,playerData);
    ui->Widget_PlayerList->layout()->addWidget(widget);
    ui->Widget_PlayerList->layout()->removeItem(ui->VSpacer);
    ui->Widget_PlayerList->layout()->addItem(ui->VSpacer);
    widget->setVisible(true);

    m_players.insert(playerData.id(),widget);
}

void Form_Lounge::on_btn_ready_clicked()
{
    if(m_isReady == 0){
        m_isReady = 1;
        emit signal_readyGame(m_isReady);
        ui->btn_ready->setText("取消准备");

    }else{
        m_isReady = 0;
        emit signal_readyGame(m_isReady);
        ui->btn_ready->setText("准备游戏");
    }
}

void Form_Lounge::on_btn_leave_clicked()
{
    emit signal_leaveLounge();
}
