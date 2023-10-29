#include "widget_cardbtn.h"
#include "ui_widget_cardbtn.h"

Widget_CardBtn::Widget_CardBtn(QWidget *parent, const CardData &cardData) :
    QWidget(parent),
    ui(new Ui::Widget_CardBtn)
{
    ui->setupUi(this);
    this->setFixedWidth(37);
    this->installEventFilter(this);

    this->initCardUI(cardData);
    ui->lbl_suit_big->setVisible(false);
    ui->lbl_pick->setVisible(false);
    m_picked = false;
}

Widget_CardBtn::~Widget_CardBtn()
{
    delete ui;
}

void Widget_CardBtn::enlarge()
{
    this->setFixedWidth(85);
    ui->lbl_suit_big->setVisible(true);
}

void Widget_CardBtn::smaller()
{
    this->setFixedWidth(37);
    ui->lbl_suit_big->setVisible(false);
}

void Widget_CardBtn::initCardUI(const CardData &cardData)
{
    QPixmap pixmap;
    if(cardData.suit() == Suit::diamond)
        pixmap = QPixmap(":/images/diamond.png");
    else if(cardData.suit() == Suit::club)
        pixmap = QPixmap(":/images/club.png");
    else if(cardData.suit() == Suit::heart)
        pixmap = QPixmap(":/images/heart.png");
    else if(cardData.suit() == Suit::spade)
        pixmap = QPixmap(":/images/spade.png");
    ui->lbl_suit->setPixmap(pixmap);
    ui->lbl_suit_big->setPixmap(pixmap);

    if(cardData.rank() == Rank::three)
        ui->lbl_rank->setText("3");
    if(cardData.rank() == Rank::four)
        ui->lbl_rank->setText("4");
    if(cardData.rank() == Rank::five)
        ui->lbl_rank->setText("5");
    if(cardData.rank() == Rank::six)
        ui->lbl_rank->setText("6");
    if(cardData.rank() == Rank::seven)
        ui->lbl_rank->setText("7");
    if(cardData.rank() == Rank::eight)
        ui->lbl_rank->setText("8");
    if(cardData.rank() == Rank::nine)
        ui->lbl_rank->setText("9");
    if(cardData.rank() == Rank::ten)
        ui->lbl_rank->setText("10");
    if(cardData.rank() == Rank::Jack)
        ui->lbl_rank->setText("J");
    if(cardData.rank() == Rank::Queen)
        ui->lbl_rank->setText("Q");
    if(cardData.rank() == Rank::King)
        ui->lbl_rank->setText("K");
    if(cardData.rank() == Rank::Ace)
        ui->lbl_rank->setText("A");
    if(cardData.rank() == Rank::two)
        ui->lbl_rank->setText("2");
    if(cardData.rank() == Rank::BlackJoker)
        ui->lbl_rank->setText("J\nO\nK");
    if(cardData.rank() == Rank::RedJoker)
        ui->lbl_rank->setText("J\nO\nK");

    if(cardData.suit() == Suit::diamond or cardData.suit() == Suit::heart or cardData.rank() == Rank::RedJoker)
        ui->lbl_rank->setStyleSheet("color:red;");
}

bool Widget_CardBtn::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::Enter){
        ui->Widget_Main->setStyleSheet("QWidget#Widget_Main{ font: 22pt;    background-color: qlineargradient(spread:pad, x1:0.66, y1:0.66, x2:0, y2:0, stop:0 rgba(250, 249, 230, 255), stop:1 rgba(255, 255, 255, 255)); }");

    }else if(event->type() == QEvent::Leave){
        ui->Widget_Main->setStyleSheet("QWidget#Widget_Main{ font: 20pt;    background-color: rgb(255,255,250); }");

    }else if(event->type() == QEvent::MouseButtonPress){
        m_picked = ( m_picked == false ) ? true : false;
        if(m_picked)
            ui->lbl_pick->setVisible(true);
        else
            ui->lbl_pick->setVisible(false);

        emit cardSelected(m_picked);
    }

    return this->parent()->eventFilter(target,event);
}
