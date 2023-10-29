#ifndef POKER_H
#define POKER_H

#include "carddata.h"

#include <QVector>
#include <QObject>

class Poker : public QObject
{
    Q_OBJECT
public:
    explicit Poker(QObject *parent, const QVector<int> &playerIDs);
    QVector<int> getPlayerIDs(int id);
    QVector<CardData> getCards(int id);
    void becomeLandlord(int id, bool become);
    void playCards(int id, const QVector<CardData> &cards);

signals:
    void signal_checkBecomeLandlord(int id, int player, int time);
    void signal_restart(int id);
    void signal_showLandlord(int id, int player);
    void signal_showLandlordCards(int id, const QVector<CardData> &cards);
    void signal_showCards(int id, int playerID, const QVector<CardData> &cards);
    void signal_waitForPlayCard(int id, int playerID, int time);

private:
    QVector<int> m_playerIDs;
    QVector<QVector<CardData>> m_playersCards;
    QVector<CardData> m_landlordCards;

private:
    int m_curIndex;
    int m_firstIndex;

private:
    int m_time_landlord;
    int m_time_playCard;

private:
    void dealCard();
    void gameStart();
};

#endif // POKER_H
