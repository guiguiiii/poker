#ifndef GAMEHUB_SERVER_H
#define GAMEHUB_SERVER_H

#include "gamehub.h"

#include <QObject>
#include <QTcpSocket>

class GameHub_Server : public QObject
{
    Q_OBJECT
public:
    explicit GameHub_Server(QObject *parent);

public:
    // Receive
    void rcv_gameHubJSON(int id, const QJsonObject &object);
    void rcv_disConnected(int id);

private:
    // Process
    // ( gamehub )
    void proc_getLounges(int id);
    void proc_getPublicData(int id);
    void proc_enterLounge(int id, const QJsonObject &object);
    void proc_quickStart(int id);
    void proc_newLounge(int id);

    // ( lounge )
    void proc_getPlayers(int id);
    void proc_readyGame(int id, const QJsonObject &object);
    void proc_leaveLounge(int id, const QJsonObject &object);

private:
    // Send
    // ( gamehub )
    void send_getLounges(int id, const QVector<LoungeData> &lounges);
    void send_getPublicData(int id, const PublicData &publicData);
    void send_enterLoungeOK(int id, int loungeID);
    void send_enterLoungeFailed(int id, int status);

    // ( lounge )
    void send_getPlayers(int id, const QVector<PlayerData> &players);
    void send_playerJoin(int id, const PlayerData &playerData);
    void send_playerLeave(int id, int playerID);
    void send_playerReady(int id, int playerID, bool isReady);
    void send_gameStart(int id, int gameID);

private:
    GameHub *m_gameHub;

private:
    void getLoungeID(int id);

signals:
    // Send messages to client
    void signal_sendJSON(int id, const QJsonObject &object);


// Send IDs to game_server for create new game
signals:
    // Signals to game_server
    void signal_gameStart(const QVector<int> &playerIDs);
private:
    // Get IDs from gameHub
    void slot_gameHub_gameStart(const QVector<int> &playerIDs);
public slots:
    // Receive signals with IDs from game_server for send 'gameStart' to clients
    void slot_gameServer_gameStart(const QVector<int> &playerIDs, int gameID);
};

#endif // GAMEHUB_SERVER_H
