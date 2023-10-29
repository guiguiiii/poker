#include "form_game.h"
#include "ui_form_game.h"

#include <QTimer>

Form_Game::Form_Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Game)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
    this->initUI();
}

Form_Game::~Form_Game()
{
    delete ui;
}

void Form_Game::setPlayers(const QVector<PublicData> &players)
{
    if(players.size() != 3)
        return;

    ui->lbl_username_playerA->setText(players[0].nickname());
    ui->lbl_pfp_playerA->setPixmap(players[0].pfp());
    ui->lbl_pfp_playerC->setPixmap(players[1].pfp());
    ui->lbl_pfp_playerB->setPixmap(players[2].pfp());
}

void Form_Game::setCards(const QVector<CardData> &cards)
{
    this->showCardBtns(cards);
    
    ui->lbl_cardNum_playerB->setText("17");
    ui->lbl_cardNum_playerC->setText("17");
}

void Form_Game::checkBecomeLandlord(int player, int time)
{
    // 显示当前选择是否成为地主的玩家的倒计时控件
    this->countDown(player,time);

    // 若轮到我选择是否成为地主，显示地主选择阶段的控件
    if(player == 0)
        ui->Widget_BTN_Landlord->setVisible(true);
    else
        ui->Widget_BTN_Landlord->setVisible(false);
}

void Form_Game::showLandlord(int player)
{
    // 显示 “地主” 标签，修改地主的牌数控件
    QLabel *label = ui->lbl_landlord_playerA;
    if(player == 1){
        label = ui->lbl_landlord_playerB;
        ui->lbl_cardNum_playerB->setText("20");
    }else if(player == 2){
        label = ui->lbl_landlord_playerC;
        ui->lbl_cardNum_playerC->setText("20");
    }
    label->setText("地主");
    label->setVisible(true);

    // 隐藏地主选择阶段的控件，且停止倒计时
    emit stopCountDown();
    ui->Widget_BTN_Landlord->deleteLater();
}

void Form_Game::showLandlordCards(const QVector<CardData> &cards)
{
    // 展示三张地主牌
    this->showCardLbls(cards);
    for(Widget_CardLbl *widget_card: m_cardLbls)
        widget_card->enlarge();
}

void Form_Game::showCards(int player, const QVector<CardData> &cards)
{
    if(cards.empty() == true)
        return;

    // 若上一位玩家出牌不为空，展示出牌，修改牌数
    this->showCardLbls(cards);
    this->reduceCount(player,cards.size());
}

void Form_Game::waitForPlayCard(int player, int time)
{
    // 显示当前出牌玩家的倒计时控件
    this->countDown(player,time);

    // 若轮到我出牌，显示出牌阶段的控件
    if(player == 0)
        ui->Widget_BTN_PlayCard->setVisible(true);
}

void Form_Game::removeCards(const QVector<CardData> &cards)
{
    // 移除手牌
    this->removeCardBtns(cards);

    // 隐藏出牌阶段的控件
    ui->Widget_BTN_PlayCard->setVisible(false);
}

void Form_Game::canPlayCard(bool ok)
{
    ui->btn_playCard->setEnabled(ok);
}

void Form_Game::canPassPlayCard(bool ok)
{
    ui->btn_pass_playCard->setEnabled(ok);
}

void Form_Game::initUI()
{
    ui->Widget_BTN_PlayCard->setVisible(false);
    ui->Widget_BTN_Landlord->setVisible(false);
    ui->lbl_time_playerA->setVisible(false);
    ui->lbl_time_playerC->setVisible(false);
    ui->lbl_time_playerB->setVisible(false);
    ui->btn_playCard->setEnabled(false);
}

void Form_Game::showCardLbls(const QVector<CardData> &cards)
{
    for(int i = m_cardLbls.size() -1; i>=0; i--)
        m_cardLbls[i]->deleteLater();
    m_cardLbls.resize(0);

    for(int i=0; i<cards.size(); i++){
        CardData cardData = cards.at(i);

        auto widget = new Widget_CardLbl(ui->Widget_CardLbls,cardData);
        if(i == cards.size() -1)
            widget->enlarge();

        ui->Widget_CardLbls->layout()->addWidget(widget);
        m_cardLbls.push_back(widget);
        widget->setVisible(true);
    }

    QLayout *layout = ui->Widget_CardLbls->layout();
    layout->removeItem(ui->HSpacer_right_CardLbls);
    layout->addItem(ui->HSpacer_right_CardLbls);
}

void Form_Game::showCardBtns(const QVector<CardData> &cards)
{
    for(auto it = m_cardBtns.begin(); it != m_cardBtns.end(); it++){
        it.key()->deleteLater();
        m_cardBtns.remove(it.key());
    }

    for(int i=0; i<cards.size(); i++){
        CardData cardData = cards.at(i);

        auto widget = new Widget_CardBtn(ui->Widget_CardBtns,cardData);
        connect(widget, &Widget_CardBtn::cardSelected, this, &Form_Game::widgetCardBtn_clicked);
        if(i == cards.size() -1 and cards.size() <= 17)
            widget->enlarge();

        ui->Widget_CardBtns->layout()->addWidget(widget);
        m_cardBtns.insert(widget,cardData);
        widget->setVisible(true);
    }

    QLayout *layout = ui->Widget_CardBtns->layout();
    layout->removeItem(ui->HSpacer_right_CardBtns);
    layout->addItem(ui->HSpacer_right_CardBtns);

    if(cards.size() <= 17){
        ui->Widget_CardBtns->setFixedWidth(695);
        ui->Widget_CardBtns->move(42,90);
    }else{
        ui->Widget_CardBtns->setFixedWidth(760);
        ui->Widget_CardBtns->move(10,90);
    }
}

void Form_Game::removeCardBtns(const QVector<CardData> &cards)
{
    for(int i=0; i<cards.size(); i++){
        auto widget = m_cardBtns.key(cards[i]);
        m_cardBtns.remove(widget);
        widget->deleteLater();
    }

    if(m_cardBtns.size() - cards.size() <= 17){
        ui->Widget_CardBtns->setFixedWidth(695);
        ui->Widget_CardBtns->move(42,90);
        /*temp*/
        // 不知为什么崩溃
//        m_cardBtns.end().key()->enlarge();
    }else{
        ui->Widget_CardBtns->setFixedWidth(760);
        ui->Widget_CardBtns->move(10,90);
    }
}

void Form_Game::countDown(int player, int time)
{
    // Static timer
    static QTimer *s_timer = nullptr;
    static int s_time = 0;

    // Count down UI
    QLabel *label = ui->lbl_time_playerA;
    if(player == 1)
        label = ui->lbl_time_playerB;
    else if(player == 2)
        label = ui->lbl_time_playerC;

    // Delete last timer
    if(s_timer != nullptr){
        s_timer->stop();
        s_timer->deleteLater();
        s_timer = nullptr;
    }

    // Init timer
    s_time = time;
    s_timer = new QTimer(this);

    connect(this, &Form_Game::stopCountDown, this, [=](){
        if(s_timer != nullptr){
            s_timer->stop();
            s_timer->deleteLater();
            s_timer = nullptr;
        }
    });

    connect(s_timer, &QTimer::destroyed, this, [=](){
        label->setText("");
        label->setVisible(false);
    });

    connect(s_timer, &QTimer::timeout, this, [=](){
        s_time--;
        if(s_time > 0)
            label->setText(QString::number(s_time));
        else{
            s_timer->deleteLater();
            s_timer = nullptr;
        }
    });

    // Timer start
    s_timer->start(1000);
    label->setText(QString::number(time));
    label->setVisible(true);
}

void Form_Game::reduceCount(int player, int number)
{
    if(player != 1 and player != 2)
        return;

    QLabel *label = ui->lbl_cardNum_playerB;
    if(player == 2)
        label = ui->lbl_cardNum_playerC;

    int count = label->text().toInt() - number;
    label->setText(QString::number(count));
}

void Form_Game::widgetCardBtn_clicked(bool selected)
{
    auto widget = static_cast<Widget_CardBtn *>(sender());
    CardData cardData = m_cardBtns.value(widget);
    emit signal_cardSelected(cardData,selected);
}

void Form_Game::on_btn_playCard_clicked()
{
    emit signal_playCards();
}

void Form_Game::on_btn_pass_playCard_clicked()
{
    emit signal_pass();
}

void Form_Game::on_btn_become_clicked()
{
    emit signal_becomeLandlord(true);
}

void Form_Game::on_btn_pass_landlord_clicked()
{
    emit signal_becomeLandlord(false);
}
