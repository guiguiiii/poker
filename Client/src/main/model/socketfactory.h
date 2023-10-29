#ifndef SOCKETFACTORY_H
#define SOCKETFACTORY_H

#include "socket.h"
#include "src/login/model/login_socket.h"
#include "src/user/model/user_socket.h"
#include "src/gamehub/model/gamehub_socket.h"
#include "src/game/model/game_socket.h"

class SocketFactory
{
public:
    static void setSocket(Socket *socket);
    const static Login_Socket* loginSocket();
    const static User_Socket* userSocket();
    const static GameHub_Socket* gameHubSocket();
    const static Game_Socket* gameSocket();

private:
    static Socket *socket;
};

#endif // SOCKETFACTORY_H
