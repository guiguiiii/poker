#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "server.h"
#include "src/user/user_server.h"
#include "src/gamehub/gamehub_server.h"
#include "src/game/game_server.h"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent);

private:
    // Server pointers
    Server *m_server;
    User_Server *m_userServer;
    GameHub_Server *m_gameHubServer;
    Game_Server *m_gameServer;

private slots:
    // Receive signals from login_controller

};

#endif // CONTROLLER_H
