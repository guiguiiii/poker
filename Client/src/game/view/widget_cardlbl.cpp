#include "widget_cardlbl.h"
#include "ui_widget_cardlbl.h"

Widget_CardLbl::Widget_CardLbl(QWidget *parent, const CardData &cardData) :
    QWidget(parent),
    ui(new Ui::Widget_CardLbl)
{
    ui->setupUi(this);
    this->setFixedWidth(30);
    ui->lbl_suit_big->setVisible(false);
    this->initUI(cardData);
}

Widget_CardLbl::~Widget_CardLbl()
{
    delete ui;
}

void Widget_CardLbl::enlarge()
{
    this->setFixedWidth(68);
    ui->lbl_suit_big->setVisible(true);
}

void Widget_CardLbl::initUI(const CardData &cardData)
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
