#include "socketfactory.h"

Socket* SocketFactory::socket = nullptr;

void SocketFactory::setSocket(Socket *socket)
{
    SocketFactory::socket = socket;
}

const Login_Socket *SocketFactory::loginSocket()
{
    if(SocketFactory::socket == nullptr)
        return nullptr;
    const static Login_Socket *loginSocket = new Login_Socket(socket);
    return loginSocket;
}

const User_Socket *SocketFactory::userSocket()
{
    if(SocketFactory::socket == nullptr)
        return nullptr;
    const static User_Socket *userSocket = new User_Socket(socket);
    return userSocket;
}

const GameHub_Socket *SocketFactory::gameHubSocket()
{
    if(SocketFactory::socket == nullptr)
        return nullptr;
    const static GameHub_Socket *gameHubSocket = new GameHub_Socket(socket);
    return gameHubSocket;
}

const Game_Socket *SocketFactory::gameSocket()
{
    if(SocketFactory::socket == nullptr)
        return nullptr;
    const static Game_Socket *gameSocket = new Game_Socket(socket);
    return gameSocket;
}
