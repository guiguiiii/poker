#ifndef FORM_GAME_H
#define FORM_GAME_H

#include "../model/carddata.h"
#include "src/common/model/publicdata.h"
#include "widget_cardbtn.h"
#include "widget_cardlbl.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class Form_Game;
}

class Form_Game : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Game(QWidget *parent);
    ~Form_Game();

public:
    void setPlayers(const QVector<PublicData> &players);
    void setCards(const QVector<CardData> &cards);
    void checkBecomeLandlord(int player, int time);
    void showLandlord(int player);
    void showLandlordCards(const QVector<CardData> &cards);
    void showCards(int player, const QVector<CardData> &cards);
    void waitForPlayCard(int player, int time);

public:
    void removeCards(const QVector<CardData> &cards);
    void canPlayCard(bool ok);
    void canPassPlayCard(bool ok);

signals:
    void signal_becomeLandlord(bool become);
    void signal_playCards();
    void signal_pass();
    void signal_cardSelected(const CardData &card, bool selected);

signals:
    void stopCountDown();

private:
    Ui::Form_Game *ui;

private:
    QMap<Widget_CardBtn *, CardData> m_cardBtns;
    QVector<Widget_CardLbl *> m_cardLbls;

private:
    void initUI();
    void showCardLbls(const QVector<CardData> &cards);
    void showCardBtns(const QVector<CardData> &cards);
    void removeCardBtns(const QVector<CardData> &cards);
    void countDown(int player, int time);
    void reduceCount(int player, int number);

private slots:
    void widgetCardBtn_clicked(bool selected);

private slots:
    void on_btn_playCard_clicked();
    void on_btn_pass_playCard_clicked();
    void on_btn_become_clicked();
    void on_btn_pass_landlord_clicked();
};

#endif // FORM_GAME_H
