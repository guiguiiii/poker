#include "game_socket.h"

#include "src/common/pixtostr.h"

#include <QJsonArray>

Game_Socket::Game_Socket(Socket *socket)
{
    m_socket = socket;
    this->setParent(m_socket->parent());
    connect(m_socket, &Socket::rcv_gameJSON, this, &Game_Socket::getGameJSON);
}

void Game_Socket::send_getPlayers(int gameID) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["gameID"] = gameID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "getPlayers";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Game_Socket::send_getCards(int gameID) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["gameID"] = gameID;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "getCards";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Game_Socket::send_becomeLandlord(int gameID, bool become) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["gameID"] = gameID;
    bodyObj["become"] = become;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "becomeLandlord";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Game_Socket::send_playCards(int gameID, const QVector<CardData> &cards) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyObj["gameID"] = gameID;
    bodyArr.push_back(bodyObj);

    for(const CardData &cardData: cards){
        QJsonObject cardObj;
        cardObj["rank"] = int(cardData.rank());
        cardObj["suit"] = int(cardData.suit());
        bodyArr.append(cardObj);
    }

    // Message title
    QJsonObject object;
    object["title"] = "game";
    object["name"] = "playCards";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Game_Socket::getGameJSON(const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "getPlayers"){
        this->proc_getPlayers(object);
    }else if(name == "getCards"){
        this->proc_getCards(object);
    }else if(name == "checkBecomeLandlord"){
        this->proc_checkBecomeLandlord(object);
    }else if(name == "restart"){
        this->proc_restart();
    }else if(name == "showLandlord"){
        this->proc_showLandlord(object);
    }else if(name == "showLandlordCards"){
        this->proc_showLandlordCards(object);
    }else if(name == "showCards"){
        this->proc_showCards(object);
    }else if(name == "waitForPlayCard"){
        this->proc_waitForPlayCard(object);
    }
}

void Game_Socket::proc_getPlayers(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QVector<PublicData> players;
    for(int i=0; i<bodyArr.size(); i++){
        QJsonObject playerObj = bodyArr.at(i).toObject();
        PublicData publicData;
        publicData.setId(playerObj["id"].toInt());
        publicData.setNickname(playerObj["nickname"].toString());
        publicData.setPfp(PixToStr::strToPix(playerObj["pfp"].toString()));
        players.push_back(publicData);
    }

    // Send signal with data
    emit rcv_getPlayers(players);
}

void Game_Socket::proc_getCards(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QVector<CardData> cards;
    for(int i=0; i<bodyArr.size(); i++){
        QJsonObject cardObj = bodyArr.at(i).toObject();
        CardData cardData;
        cardData.setRank(static_cast<Rank>(cardObj["rank"].toInt()));
        cardData.setSuit(static_cast<Suit>(cardObj["suit"].toInt()));
        cards.push_back(cardData);
    }

    // Send signal with data
    emit rcv_getCards(cards);
}

void Game_Socket::proc_checkBecomeLandlord(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int id = bodyObj["id"].toInt();
    int time = bodyObj["time"].toInt();

    // Send signal with data
    emit rcv_checkBecomeLandlord(id,time);
}

void Game_Socket::proc_restart()
{
    // Send signal with data
    emit rcv_restart();
}

void Game_Socket::proc_showLandlord(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int id = bodyObj["id"].toInt();

    // Send signal with data
    emit rcv_showLandlord(id);
}

void Game_Socket::proc_showLandlordCards(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QVector<CardData> cards;
    for(int i=0; i<bodyArr.size(); i++){
        QJsonObject cardObj = bodyArr.at(i).toObject();
        CardData cardData;
        cardData.setRank(static_cast<Rank>(cardObj["rank"].toInt()));
        cardData.setSuit(static_cast<Suit>(cardObj["suit"].toInt()));
        cards.push_back(cardData);
    }

    // Send signal with data
    emit rcv_showLandlordCards(cards);
}

void Game_Socket::proc_showCards(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int id = bodyObj["id"].toInt();

    QVector<CardData> cards;
    for(int i=1; i<bodyArr.size(); i++){
        QJsonObject cardObj = bodyArr.at(i).toObject();
        CardData cardData;
        cardData.setRank(static_cast<Rank>(cardObj["rank"].toInt()));
        cardData.setSuit(static_cast<Suit>(cardObj["suit"].toInt()));
        cards.push_back(cardData);
    }

    // Send signal with data
    emit rcv_showCards(id,cards);
}

void Game_Socket::proc_waitForPlayCard(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int id = bodyObj["id"].toInt();
    int time = bodyObj["time"].toInt();

    // Send signal with data
    emit rcv_waitForPlayCard(id,time);
}
