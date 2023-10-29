#ifndef GAMEHUB_SOCKET_H
#define GAMEHUB_SOCKET_H

#include "src/main/model/socket.h"
#include "loungedata.h"
#include "playerdata.h"
#include "src/common/model/publicdata.h"

#include <QObject>

class GameHub_Socket : public QObject
{
    Q_OBJECT
public:
    explicit GameHub_Socket(Socket *socket);

public:
    // Send messages to server
    // ( gamehub )
    void send_getLounges() const;
    void send_getPublicData() const;
    void send_enterLounge(int loungeID) const;
    void send_quickStart() const;
    void send_newLounge() const;

    // ( lounge )
    void send_getPlayers() const;
    void send_readyGame(int loungeID, bool isReady) const;
    void send_leaveLounge(int loungeID) const;

signals:
    // Receive messages from server
    // ( gamehub )
    void rcv_getLounges(const QVector<LoungeData> &lounges);
    void rcv_getPublicData(const PublicData &publicData);
    void rcv_enterLoungeOK(int loungeID);
    void rcv_enterLoungeFailed(int status);

    // ( lounge )
    void rcv_getPlayers(const QVector<PlayerData> &players);
    void rcv_playerJoin(const PublicData &publicData);
    void rcv_playerLeave(int playerID);
    void rcv_playerReady(int playerID, bool isReady);
    void rcv_gameStart(int gameID);

private:
    Socket *m_socket;

// Process messages from server
private slots:
    // First
    void getGameHubJSON(const QJsonObject &object);

private:
    // Sencond
    // ( gamehub )
    void proc_getLounges(const QJsonObject &object);
    void proc_getPublicData(const QJsonObject &object);
    void proc_enterLoungeOK(const QJsonObject &object);
    void proc_enterLoungeFailed(const QJsonObject &object);

    // ( lounge )
    void proc_getPlayers(const QJsonObject &object);
    void proc_playerJoin(const QJsonObject &object);
    void proc_playerLeave(const QJsonObject &object);
    void proc_playerReady(const QJsonObject &object);
    void proc_gameStart(const QJsonObject &object);
};

#endif // GAMEHUB_SOCKET_H
