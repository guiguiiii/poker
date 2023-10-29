#include "gamehub_controller.h"

#include "src/main/model/socketfactory.h"

GameHub_Controller::GameHub_Controller(QWidget *parent)
    : QWidget(parent)
{
    m_loungeID = -1;
    m_formLounge = nullptr;

    // Init socket_gameHub
    m_gameHubSocket = SocketFactory::gameHubSocket();
    connect(m_gameHubSocket, &GameHub_Socket::rcv_getLounges, this, &GameHub_Controller::rcv_getLounges);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_getPublicData, this, &GameHub_Controller::rcv_getPublicData);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_enterLoungeOK, this, &GameHub_Controller::rcv_enterLoungeOK);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_enterLoungeFailed, this, &GameHub_Controller::rcv_enterLoungeFailed);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_getPlayers, this, &GameHub_Controller::rcv_getPlayers);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_playerJoin, this, &GameHub_Controller::rcv_playerJoin);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_playerLeave, this, &GameHub_Controller::rcv_playerLeave);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_playerReady, this, &GameHub_Controller::rcv_playerReady);
    connect(m_gameHubSocket, &GameHub_Socket::rcv_gameStart, this, &GameHub_Controller::rcv_gameStart);

    // Init form_gameHub and show it
    m_formGameHub = new Form_GameHub(this);
    connect(m_formGameHub, &Form_GameHub::signal_moveToStart, this, &GameHub_Controller::slot_formGameHub_moveToStart);
    connect(m_formGameHub, &Form_GameHub::signal_enterLounge, m_gameHubSocket, &GameHub_Socket::send_enterLounge);
    connect(m_formGameHub, &Form_GameHub::signal_quickStart, m_gameHubSocket, &GameHub_Socket::send_quickStart);
    connect(m_formGameHub, &Form_GameHub::signal_newGame, m_gameHubSocket, &GameHub_Socket::send_newLounge);
    connect(m_formGameHub, &Form_GameHub::signal_getLounges, m_gameHubSocket, &GameHub_Socket::send_getLounges);
    m_formGameHub->setVisible(true);

    // Request UI data
    m_gameHubSocket->send_getPublicData();
    m_gameHubSocket->send_getLounges();
}

void GameHub_Controller::rcv_getLounges(const QVector<LoungeData> &lounges)
{
    if(m_formGameHub != nullptr)
        m_formGameHub->initLounges(lounges);
}

void GameHub_Controller::rcv_getPublicData(const PublicData &publicData)
{
    if(m_formGameHub != nullptr)
        m_formGameHub->initPublicData(publicData);
}

void GameHub_Controller::rcv_enterLoungeOK(int loungeID)
{
    m_loungeID = loungeID;

    // Hide form_gamehub
    if(m_formGameHub == nullptr)
        return;

    m_formGameHub->setParent(nullptr);
    m_formGameHub->setVisible(false);

    // Init form_lounge and show it
    m_formLounge = new Form_Lounge(this);
    m_formLounge->setLoungeID(loungeID);
    connect(m_formLounge, &Form_Lounge::signal_readyGame, this, &GameHub_Controller::slot_formLounge_readyGame);
    connect(m_formLounge, &Form_Lounge::signal_leaveLounge, this, &GameHub_Controller::slot_formLounge_leaveLounge);
    m_formLounge->setVisible(true);

    // Request UI data
    m_gameHubSocket->send_getPlayers();
}

void GameHub_Controller::rcv_enterLoungeFailed(int status)
{
    if(m_formGameHub != nullptr)
        m_formGameHub->enterLoungeFailed(status);
}

void GameHub_Controller::rcv_getPlayers(const QVector<PlayerData> &players)
{
    if(m_formLounge != nullptr)
        m_formLounge->initPlayers(players);
}

void GameHub_Controller::rcv_playerJoin(const PublicData &publicData)
{
    if(m_formLounge != nullptr)
        m_formLounge->playerJoin(publicData);
}

void GameHub_Controller::rcv_playerLeave(int id)
{
    if(m_formLounge != nullptr)
        m_formLounge->playerLeave(id);
}

void GameHub_Controller::rcv_playerReady(int id, bool isReady)
{
    if(m_formLounge != nullptr)
        m_formLounge->playerReady(id,isReady);
}

void GameHub_Controller::rcv_gameStart(int gameID)
{
    emit signal_moveToGame(gameID);
}

void GameHub_Controller::slot_formGameHub_moveToStart()
{
    emit signal_moveToUser();
}

void GameHub_Controller::slot_formLounge_readyGame(bool isReady)
{
    m_gameHubSocket->send_readyGame(m_loungeID,isReady);
}

void GameHub_Controller::slot_formLounge_leaveLounge()
{
    // Send message
    m_gameHubSocket->send_leaveLounge(m_loungeID);

    m_loungeID = -1;

    // Delete form_lounge
    if(m_formLounge == nullptr)
        return;

    m_formLounge->setParent(nullptr);
    m_formLounge->setVisible(false);
    m_formLounge->deleteLater();
    m_formLounge = nullptr;

    // Show form_gameHub
    if(m_formGameHub == nullptr)
        return;

    m_formGameHub->setParent(this);
    m_formGameHub->setVisible(true);

    // Send message ( auto refresh )
    m_gameHubSocket->send_getLounges();
}
