#include "game_controller.h"

#include "src/main/model/socketfactory.h"

Game_Controller::Game_Controller(QWidget *parent, int gameID)
    : QWidget{parent}
{
    m_gameID = gameID;

    // Init socket_game
    m_gameSocket = SocketFactory::gameSocket();
    connect(m_gameSocket, &Game_Socket::rcv_getPlayers, this, &Game_Controller::rcv_getPlayers);
    connect(m_gameSocket, &Game_Socket::rcv_getCards, this, &Game_Controller::rcv_getCards);
    connect(m_gameSocket, &Game_Socket::rcv_checkBecomeLandlord, this, &Game_Controller::rcv_checkBecomeLandlord);
    connect(m_gameSocket, &Game_Socket::rcv_restart, this, &Game_Controller::rcv_restart);
    connect(m_gameSocket, &Game_Socket::rcv_showLandlord, this, &Game_Controller::rcv_showLandlord);
    connect(m_gameSocket, &Game_Socket::rcv_showLandlordCards, this, &Game_Controller::rcv_showLandlordCards);
    connect(m_gameSocket, &Game_Socket::rcv_showCards, this, &Game_Controller::rcv_showCards);
    connect(m_gameSocket, &Game_Socket::rcv_waitForPlayCard, this, &Game_Controller::rcv_waitForPlayCard);

    // Init gameRule
    m_gameRule = new GameRule(this);
    connect(m_gameRule, &GameRule::signal_canPlayCard, this, &Game_Controller::slot_gameRule_canPlayCard);
    connect(m_gameRule, &GameRule::signal_canPassPlayCard, this, &Game_Controller::slot_gameRule_canPassPlayCard);

    // Init form_game and show it
    m_formGame = new Form_Game(this);
    connect(m_formGame, &Form_Game::signal_becomeLandlord, this, &Game_Controller::slot_formGame_becomeLandlord);
    connect(m_formGame, &Form_Game::signal_playCards, this, &Game_Controller::slot_formGame_playCards);
    connect(m_formGame, &Form_Game::signal_pass, this, &Game_Controller::slot_formGame_pass);
    connect(m_formGame, &Form_Game::signal_cardSelected, m_gameRule, &GameRule::cardSelected);
    m_formGame->setVisible(true);

    // Request UI data
    m_gameSocket->send_getPlayers(gameID);
    m_gameSocket->send_getCards(gameID);
}

void Game_Controller::rcv_getPlayers(const QVector<PublicData> &players)
{
    QVector<int> IDs;
    for(const PublicData &publicData: players)
        IDs.push_back(publicData.id());

    // Init gameRule
    m_gameRule->setPlayers(IDs);

    // Init formGame
    m_formGame->setPlayers(players);
}

void Game_Controller::rcv_getCards(const QVector<CardData> &cards)
{
    // Init formGame
    m_formGame->setCards(cards);
}

void Game_Controller::rcv_checkBecomeLandlord(int id, int time)
{
    int playerIndex = m_gameRule->getPlayerIndex(id);
    m_formGame->checkBecomeLandlord(playerIndex,time);
}

void Game_Controller::rcv_restart()
{
    m_gameSocket->send_getCards(m_gameID);
}

void Game_Controller::rcv_showLandlord(int id)
{
    // Init gameRule
    m_gameRule->setLandlord(id);

    // Show UI
    int playerIndex = m_gameRule->getPlayerIndex(id);
    m_formGame->showLandlord(playerIndex);

    // Request data ( cards )
    if(playerIndex == 0)
        m_gameSocket->send_getCards(m_gameID);
}

void Game_Controller::rcv_showLandlordCards(const QVector<CardData> &cards)
{
    m_formGame->showLandlordCards(cards);
}

void Game_Controller::rcv_showCards(int id, const QVector<CardData> &cards)
{
    // Update gameRule
    m_gameRule->setLastCards(id,cards);

    // Show UI
    int player = m_gameRule->getPlayerIndex(id);
    m_formGame->showCards(player,cards);

    // Remove cardBtns
    if(m_gameRule->getPlayerIndex(id) == 0)
        m_formGame->removeCards(cards);
}

void Game_Controller::rcv_waitForPlayCard(int id, int time)
{
    // Show UI
    int player = m_gameRule->getPlayerIndex(id);
    m_formGame->waitForPlayCard(player,time);
}

void Game_Controller::slot_gameRule_canPlayCard(bool ok)
{
    m_formGame->canPlayCard(ok);
}

void Game_Controller::slot_gameRule_canPassPlayCard(bool ok)
{
    m_formGame->canPassPlayCard(ok);
}

void Game_Controller::slot_formGame_becomeLandlord(bool become)
{
    m_gameSocket->send_becomeLandlord(m_gameID,become);
}

void Game_Controller::slot_formGame_playCards()
{
    QVector<CardData> selectedCards = m_gameRule->getSelectedCards();
    m_gameSocket->send_playCards(m_gameID,selectedCards);
    m_gameRule->playSelectedCards();
}

void Game_Controller::slot_formGame_pass()
{
    QVector<CardData> selectedCards;
    m_gameSocket->send_playCards(m_gameID,selectedCards);
}
