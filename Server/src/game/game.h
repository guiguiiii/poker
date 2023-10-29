#ifndef GAME_H
#define GAME_H

#include "poker.h"
#include "src/common/publicdata.h"

#include <QMap>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent);

public:
    // Process
    int newGame(const QVector<int> &playerIDs);
    QVector<PublicData> getPlayers(int id, int gameID);
    QVector<CardData> getCards(int id, int gameID);
    void becomeLandlord(int id, int gameID, bool become);
    void playCards(int id, int gameID, const QVector<CardData> &cards);

signals:
    void signal_checkBecomeLandlord(int id, int player, int time);
    void signal_restart(int id);
    void signal_showLandlord(int id, int player);
    void signal_showLandlordCards(int id, const QVector<CardData> &cards);
    void signal_showCards(int id, int playerID, const QVector<CardData> &cards);
    void signal_waitForPlayCard(int id, int playerID, int time);

private:
    QMap<int, Poker*> m_pokers;
};

#endif // GAME_H
