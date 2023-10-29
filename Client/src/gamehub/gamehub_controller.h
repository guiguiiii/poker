#ifndef GAMEHUB_CONTROLLER_H
#define GAMEHUB_CONTROLLER_H

#include "model/gamehub_socket.h"
#include "view/form_gamehub.h"
#include "view/form_lounge.h"

#include <QWidget>

class GameHub_Controller : public QWidget
{
    Q_OBJECT
public:
    explicit GameHub_Controller(QWidget *parent);

signals:
    // Move to User_Controller
    void signal_moveToUser();
    // Move to Game_Controller
    void signal_moveToGame(int gameID);

private:
    // TcpSocket pointer
    const GameHub_Socket *m_gameHubSocket;

private:
    int m_loungeID;

private:
    // View pointers
    Form_GameHub *m_formGameHub;
    Form_Lounge *m_formLounge;

private slots:
    // Process signals from socket
    void rcv_getLounges(const QVector<LoungeData> &lounges);
    void rcv_getPublicData(const PublicData &publicData);
    void rcv_enterLoungeOK(int loungeID);
    void rcv_enterLoungeFailed(int status);

    void rcv_getPlayers(const QVector<PlayerData> &players);
    void rcv_playerJoin(const PublicData &publicData);
    void rcv_playerLeave(int id);
    void rcv_playerReady(int id, bool isReady);
    void rcv_gameStart(int gameID);

private slots:
    // Process signals from form_gameHub
    void slot_formGameHub_moveToStart();

    // Process signals from form_lounge
    void slot_formLounge_readyGame(bool isReady);
    void slot_formLounge_leaveLounge();
};

#endif // GAMEHUB_CONTROLLER_H
