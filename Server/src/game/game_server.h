#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "src/common/publicdata.h"
#include "src/game/game.h"

#include <QObject>
#include <QTcpSocket>

class Game_Server : public QObject
{
    Q_OBJECT
public:
    explicit Game_Server(QObject *parent);

public:
    // Receive
    void rcv_gameJSON(int id, const QJsonObject &object);

private:
    // Process
    void proc_getPlayers(int id, const QJsonObject &object);
    void proc_getCards(int id, const QJsonObject &object);
    void proc_becomeLandlord(int id, const QJsonObject &object);
    void proc_playCards(int id, const QJsonObject &object);

private:
    // Send
    void Send_getPlayers(int id, const QVector<PublicData> &players);
    void Send_getCards(int id, const QVector<CardData> &cards);
    void Send_checkBecomeLandlord(int id, int playerID, int time);
    void Send_restart(int id);
    void Send_showLandlord(int id, int playerID);
    void Send_showLandlordCards(int id, const QVector<CardData> &cards);
    void Send_showCards(int id, int playerID, const QVector<CardData> &cards);
    void Send_waitForPlayCard(int id, int playerID, int time);

private:
    Game *m_game;

signals:
    // Send messages to client
    void signal_sendJSON(int id, const QJsonObject &object);


// Receive IDs from gameHub_server for create new game
signals:
    // Send signals with IDs to gameHub_server for send 'gameStart' to clients
    void signal_gameStart(const QVector<int> &playerIDs, int gameID);
public slots:
    // Get IDs from gameHub_server
    void slot_gameHubServer_gameStart(const QVector<int> &playerIDs);
};

#endif // GAME_SERVER_H
