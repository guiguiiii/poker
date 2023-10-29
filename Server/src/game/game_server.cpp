#include "game_server.h"

#include "src/common/pixtostr.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Game_Server::Game_Server(QObject *parent)
    : QObject{parent}
{
    m_game = new Game(this);
    connect(m_game, &Game::signal_checkBecomeLandlord, this, &Game_Server::Send_checkBecomeLandlord);
    connect(m_game, &Game::signal_restart, this, &Game_Server::Send_restart);
    connect(m_game, &Game::signal_showLandlord, this, &Game_Server::Send_showLandlord);
    connect(m_game, &Game::signal_showLandlordCards, this, &Game_Server::Send_showLandlordCards);
    connect(m_game, &Game::signal_showCards, this, &Game_Server::Send_showCards);
    connect(m_game, &Game::signal_waitForPlayCard, this, &Game_Server::Send_waitForPlayCard);
}

void Game_Server::rcv_gameJSON(int id, const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "getPlayers"){
        this->proc_getPlayers(id,object);
    }else if(name == "getCards"){
        this->proc_getCards(id,object);
    }else if(name == "becomeLandlord"){
        this->proc_becomeLandlord(id,object);
    }else if(name == "playCards"){
        this->proc_playCards(id,object);
    }
}

void Game_Server::proc_getPlayers(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject bodyObj = bodyArr.first().toObject();
    int gameID = bodyObj["gameID"].toInt();

    // Process
    QVector<PublicData> players = m_game->getPlayers(id,gameID);

    // Send messages
    this->Send_getPlayers(id,players);
}

void Game_Server::proc_getCards(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject bodyObj = bodyArr.first().toObject();
    int gameID = bodyObj["gameID"].toInt();

    // Process
    QVector<CardData> cards = m_game->getCards(id,gameID);

    // Send messages
    this->Send_getCards(id,cards);
}

void Game_Server::proc_becomeLandlord(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject bodyObj = bodyArr.first().toObject();
    int gameID = bodyObj["gameID"].toInt();
    bool become = bodyObj["become"].toBool();

    // Process
    m_game->becomeLandlord(id,gameID,become);
}

void Game_Server::proc_playCards(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();

    int gameID = bodyArr.first().toObject()["gameID"].toInt();
    QVector<CardData> cards;
    for(int i=1; i<bodyArr.size(); i++){
        QJsonObject cardObj = bodyArr.at(i).toObject();
        CardData cardData;
        cardData.setRank(static_cast<Rank>(cardObj["rank"].toInt()));
        cardData.setSuit(static_cast<Suit>(cardObj["suit"].toInt()));
        cards.push_back(cardData);
    }

    // Process
    m_game->playCards(id,gameID,cards);
}

void Game_Server::Send_getPlayers(int id, const QVector<PublicData> &players)
{
    // Message body
    QJsonArray bodyArr;
    for(const PublicData &publicData: players){
        QJsonObject playerObj;
        playerObj["id"] = publicData.id();
        playerObj["nickname"] = publicData.nickname();
        playerObj["pfp"] = PixToStr::pixToStr(publicData.pfp());
        bodyArr.append(playerObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "getPlayers";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_getCards(int id, const QVector<CardData> &cards)
{
    // Message body
    QJsonArray bodyArr;
    for(const CardData &cardData: cards){
        QJsonObject cardObj;
        cardObj["rank"] = int(cardData.rank());
        cardObj["suit"] = int(cardData.suit());
        bodyArr.append(cardObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "getCards";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_checkBecomeLandlord(int id, int playerID, int time)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyObj["time"] = time;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "checkBecomeLandlord";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_restart(int id)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "restart";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_showLandlord(int id, int playerID)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "showLandlord";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_showLandlordCards(int id, const QVector<CardData> &cards)
{
    // Message body
    QJsonArray bodyArr;
    for(const CardData &cardData: cards){
        QJsonObject cardObj;
        cardObj["rank"] = int(cardData.rank());
        cardObj["suit"] = int(cardData.suit());
        bodyArr.append(cardObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "showLandlordCards";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_showCards(int id, int playerID, const QVector<CardData> &cards)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyArr.append(bodyObj);

    for(const CardData &cardData: cards){
        QJsonObject cardObj;
        cardObj["rank"] = int(cardData.rank());
        cardObj["suit"] = int(cardData.suit());
        bodyArr.append(cardObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "showCards";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::Send_waitForPlayCard(int id, int playerID, int time)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyObj["time"] = time;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "waitForPlayCard";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void Game_Server::slot_gameHubServer_gameStart(const QVector<int> &playerIDs)
{
    int gameID = m_game->newGame(playerIDs);
    emit signal_gameStart(playerIDs,gameID);
}
