#include "gamehub_server.h"

#include "src/common/pixtostr.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

GameHub_Server::GameHub_Server(QObject *parent)
    : QObject{parent}
{
    m_gameHub = new GameHub(this);
    connect(m_gameHub, &GameHub::playerJoin, this, &GameHub_Server::send_playerJoin);
    connect(m_gameHub, &GameHub::playerLeave, this, &GameHub_Server::send_playerLeave);
    connect(m_gameHub, &GameHub::playerReady, this, &GameHub_Server::send_playerReady);
    connect(m_gameHub, &GameHub::signal_gameStart, this, &GameHub_Server::slot_gameHub_gameStart);
}

void GameHub_Server::rcv_gameHubJSON(int id, const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "getLounges"){
        this->proc_getLounges(id);
    }else if(name == "getPublicData"){
        this->proc_getPublicData(id);
    }else if(name == "enterLounge"){
        this->proc_enterLounge(id,object);
    }else if(name == "quickStart"){
        this->proc_quickStart(id);
    }else if(name == "newLounge"){
        this->proc_newLounge(id);
    }else if(name == "getPlayers"){
        this->proc_getPlayers(id);
    }else if(name == "readyGame"){
        this->proc_readyGame(id,object);
    }else if(name == "leaveLounge"){
        this->proc_leaveLounge(id,object);
    }
}

void GameHub_Server::rcv_disConnected(int id)
{
    m_gameHub->leaveLounge(id);
}

void GameHub_Server::proc_getLounges(int id)
{
    // Process
    QVector<LoungeData> lounges = m_gameHub->getLounges();

    // Send messages
    this->send_getLounges(id,lounges);
}

void GameHub_Server::proc_getPublicData(int id)
{
    // Process
    PublicData publicData = m_gameHub->getPublicData(id);

    // Send messages
    this->send_getPublicData(id,publicData);
}

void GameHub_Server::proc_enterLounge(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject loungeObj = bodyArr.first().toObject();
    int loungeID = loungeObj["loungeID"].toInt();

    // Process
    int status = m_gameHub->enterLounge(id,loungeID);

    // Send messages
    if(status == 1)
        this->send_enterLoungeOK(id,loungeID);
    else
        this->send_enterLoungeFailed(id,status);
}

void GameHub_Server::proc_quickStart(int id)
{
    // Process
    int loungeID = m_gameHub->quickStart(id);

    // Send messages
    this->send_enterLoungeOK(id,loungeID);
}

void GameHub_Server::proc_newLounge(int id)
{
    // Process
    int loungeID = m_gameHub->newLounge(id);

    // Send messages
    this->send_enterLoungeOK(id,loungeID);
}

void GameHub_Server::proc_getPlayers(int id)
{
    // Process
    QVector<PlayerData> players = m_gameHub->getPlayers(id);

    // Send messages
    this->send_getPlayers(id,players);
}

void GameHub_Server::proc_readyGame(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject bodyObj = bodyArr.first().toObject();
    int loungeID = bodyObj["loungeID"].toInt();
    bool isReady = bodyObj["isReady"].toBool();

    // Process
    m_gameHub->readyGame(id,isReady,loungeID);
}

void GameHub_Server::proc_leaveLounge(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject bodyObj = bodyArr.first().toObject();
    int loungeID = bodyObj["loungeID"].toInt();

    // Process
    m_gameHub->leaveLounge(id,loungeID);
}

void GameHub_Server::send_getLounges(int id, const QVector<LoungeData> &lounges)
{
    // Message body
    QJsonArray bodyArr;
    for(const LoungeData &lougeData: lounges){
        QJsonObject loungeObj;
        loungeObj["loungeID"] = lougeData.loungeID();
        loungeObj["playerNum"] = lougeData.playerNum();
        bodyArr.append(loungeObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getLounges";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_getPublicData(int id, const PublicData &publicData)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["nickname"] = publicData.nickname();
    userObj["pfp"] = PixToStr::pixToStr(publicData.pfp());
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getPublicData";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_enterLoungeOK(int id, int loungeID)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["loungeID"] = loungeID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "enterLoungeOK";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_enterLoungeFailed(int id, int status)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["status"] = status;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "enterLoungeFailed";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_getPlayers(int id, const QVector<PlayerData> &players)
{
    // Message body
    QJsonArray bodyArr;
    for(const PlayerData &playerData: players){
        QJsonObject playerObj;
        playerObj["id"] = playerData.id();
        playerObj["nickname"] = playerData.nickname();
        playerObj["pfp"] = PixToStr::pixToStr(playerData.pfp());
        playerObj["isReady"] = playerData.isReady();
        bodyArr.append(playerObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getPlayers";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_playerJoin(int id, const PlayerData &playerData)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject playerObj;
    playerObj["id"] = playerData.id();
    playerObj["nickname"] = playerData.nickname();
    playerObj["pfp"] = PixToStr::pixToStr(playerData.pfp());
    playerObj["isReady"] = playerData.isReady();
    bodyArr.append(playerObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "playerJoin";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_playerLeave(int id, int playerID)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "playerLeave";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_playerReady(int id, int playerID, bool isReady)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["id"] = playerID;
    bodyObj["isReady"] = isReady;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "playerReady";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::send_gameStart(int id, int gameID)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["gameID"] = gameID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "gameStart";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void GameHub_Server::slot_gameHub_gameStart(const QVector<int> &playerIDs)
{
    emit signal_gameStart(playerIDs);
}

void GameHub_Server::slot_gameServer_gameStart(const QVector<int> &playerIDs, int gameID)
{
    for(int playerID: playerIDs)
        this->send_gameStart(playerID, gameID);
}
