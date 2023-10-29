#include "gamehub_socket.h"

#include "src/common/pixtostr.h"

#include <QJsonArray>

GameHub_Socket::GameHub_Socket(Socket *socket)
{
    m_socket = socket;
    this->setParent(m_socket->parent());
    connect(m_socket, &Socket::rcv_gameHubJSON, this, &GameHub_Socket::getGameHubJSON);
}

void GameHub_Socket::send_getLounges() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getLounges";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_getPublicData() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getPublicData";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_enterLounge(int loungeID) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject loungeObj;
    loungeObj["loungeID"] = loungeID;
    bodyArr.append(loungeObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "enterLounge";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_quickStart() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "quickStart";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_newLounge() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "newLounge";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_getPlayers() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "getPlayers";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_readyGame(int loungeID, bool isReady) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject loungeObj;
    loungeObj["loungeID"] = loungeID;
    loungeObj["isReady"] = isReady;
    bodyArr.append(loungeObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "readyGame";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::send_leaveLounge(int loungeID) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject loungeObj;
    loungeObj["loungeID"] = loungeID;
    bodyArr.append(loungeObj);

    // Message title
    QJsonObject object;
    object["title"] = "gameHub";
    object["name"] = "leaveLounge";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void GameHub_Socket::getGameHubJSON(const QJsonObject &object)
{
    // Main
    QString name = object["name"].toString();
    if(name == "getLounges"){
        this->proc_getLounges(object);
    }else if(name == "getPublicData"){
        this->proc_getPublicData(object);
    }else if(name == "enterLoungeOK"){
        this->proc_enterLoungeOK(object);
    }else if(name == "enterLoungeFailed"){
        this->proc_enterLoungeFailed(object);
    }else if(name == "getPlayers"){
        this->proc_getPlayers(object);
    }else if(name == "playerJoin"){
        this->proc_playerJoin(object);
    }else if(name == "playerLeave"){
        this->proc_playerLeave(object);
    }else if(name == "playerReady"){
        this->proc_playerReady(object);
    }else if(name == "gameStart"){
        this->proc_gameStart(object);
    }
}

void GameHub_Socket::proc_getLounges(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QVector<LoungeData> lounges;
    for(int i=0; i<bodyArr.size(); i++){
        QJsonObject loungeObj = bodyArr.at(i).toObject();
        LoungeData loungeData;
        loungeData.setLoungeID(loungeObj["loungeID"].toInt());
        loungeData.setPlayerNum(loungeObj["playerNum"].toInt());
        lounges.push_back(loungeData);
    }

    // Send signal with data
    emit rcv_getLounges(lounges);
}

void GameHub_Socket::proc_getPublicData(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject userObj = bodyArr.first().toObject();
    PublicData publicData;
    publicData.setId(userObj["id"].toInt());
    publicData.setNickname(userObj["nickname"].toString());
    publicData.setPfp(PixToStr::strToPix(userObj["pfp"].toString()));

    // Send signal with data
    emit rcv_getPublicData(publicData);
}

void GameHub_Socket::proc_enterLoungeOK(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int loungeID = bodyObj["loungeID"].toInt();

    // Send signal with data
    emit rcv_enterLoungeOK(loungeID);
}

void GameHub_Socket::proc_enterLoungeFailed(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();
    
    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int status = bodyObj["status"].toInt();

    // Send signal with data
    emit rcv_enterLoungeFailed(status);
}

void GameHub_Socket::proc_getPlayers(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QVector<PlayerData> players;
    for(int i=0; i<bodyArr.size(); i++){
        QJsonObject loungeObj = bodyArr.at(i).toObject();
        PlayerData playerData;
        playerData.setId(loungeObj["id"].toInt());
        playerData.setNickname(loungeObj["nickname"].toString());
        playerData.setPfp(PixToStr::strToPix(loungeObj["pfp"].toString()));
        playerData.setIsReady(loungeObj["isReady"].toBool());
        players.push_back(playerData);
    }

    // Send signal with data
    emit rcv_getPlayers(players);
}

void GameHub_Socket::proc_playerJoin(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject playerObj = bodyArr.first().toObject();
    PublicData publicData;
    publicData.setId(playerObj["id"].toInt());
    publicData.setNickname(playerObj["nickname"].toString());
    publicData.setPfp(PixToStr::strToPix(playerObj["pfp"].toString()));

    // Send signal with data
    emit rcv_playerJoin(publicData);
}

void GameHub_Socket::proc_playerLeave(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject playerObj = bodyArr.first().toObject();
    int id = playerObj["id"].toInt();

    // Send signal with data
    emit rcv_playerLeave(id);
}

void GameHub_Socket::proc_playerReady(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject playerObj = bodyArr.first().toObject();
    int id = playerObj["id"].toInt();
    bool isReady = playerObj["isReady"].toBool();

    // Send signal with data
    emit rcv_playerReady(id,isReady);
}

void GameHub_Socket::proc_gameStart(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int gameID = bodyObj["gameID"].toInt();

    // Send signal with data
    emit rcv_gameStart(gameID);
}
