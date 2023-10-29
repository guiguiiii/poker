#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    // Init servers
    m_server = new Server(this);

    // Init user_server
    m_userServer = new User_Server(this);
    connect(m_server, &Server::rcv_userJSON, m_userServer, &User_Server::rcv_userJSON);
    connect(m_userServer, &User_Server::signal_sendJSON, m_server, &Server::sendJSON);

    // Init gameHub_server
    m_gameHubServer = new GameHub_Server(this);
    connect(m_server, &Server::rcv_gameHubJSON, m_gameHubServer, &GameHub_Server::rcv_gameHubJSON);
    connect(m_server, &Server::signal_disConnected, m_gameHubServer, &GameHub_Server::rcv_disConnected);
    connect(m_gameHubServer, &GameHub_Server::signal_sendJSON, m_server, &Server::sendJSON);

    // Init game_server
    m_gameServer = new Game_Server(this);
    connect(m_server, &Server::rcv_gameJSON, m_gameServer, &Game_Server::rcv_gameJSON);
    //    connect(m_server, &Server::signal_disConnected, m_gameServer, &)
    connect(m_gameServer, &Game_Server::signal_sendJSON, m_server, &Server::sendJSON);
    connect(m_gameHubServer, &GameHub_Server::signal_gameStart, m_gameServer, &Game_Server::slot_gameHubServer_gameStart);
    connect(m_gameServer, &Game_Server::signal_gameStart, m_gameHubServer, &GameHub_Server::slot_gameServer_gameStart);
}
