#ifndef GAME_SOCKET_H
#define GAME_SOCKET_H

#include "src/main/model/socket.h"
#include "carddata.h"
#include "src/common/model/publicdata.h"

#include <QObject>

class Game_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Game_Socket(Socket *socket);

public:
    // Send messages to server
    void send_getPlayers(int gameID) const;
    void send_getCards(int gameID) const;
    void send_becomeLandlord(int gameID, bool become) const;
    void send_playCards(int gameID, const QVector<CardData> &cards) const;

signals:
    // Receive messages from server
    void rcv_getPlayers(const QVector<PublicData> &players);
    void rcv_getCards(const QVector<CardData> &cards);
    void rcv_checkBecomeLandlord(int id, int time);
    void rcv_restart();
    void rcv_showLandlord(int id);
    void rcv_showLandlordCards(const QVector<CardData> &cards);
    void rcv_showCards(int id, const QVector<CardData> &cards);
    void rcv_waitForPlayCard(int id, int time);

private:
    Socket *m_socket;

// Process messages from server
private slots:
    // First
    void getGameJSON(const QJsonObject &object);

private:
    // Sencond
    void proc_getPlayers(const QJsonObject &object);
    void proc_getCards(const QJsonObject &object);
    void proc_checkBecomeLandlord(const QJsonObject &object);
    void proc_restart();
    void proc_showLandlord(const QJsonObject &object);
    void proc_showLandlordCards(const QJsonObject &object);
    void proc_showCards(const QJsonObject &object);
    void proc_waitForPlayCard(const QJsonObject &object);
};

#endif // GAME_SOCKET_H
