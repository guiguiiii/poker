#include "user_socket.h"

#include "src/common/pixtostr.h"

#include <QJsonArray>

User_Socket::User_Socket(Socket *socket)
    : QObject{socket}
{
    m_socket = socket;
    this->setParent(m_socket->parent());
    connect(m_socket, &Socket::rcv_userJSON, this, &User_Socket::rcv_userJSON);
}

void User_Socket::send_getPersonal() const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject bodyObj;
    bodyArr.append(bodyObj);

    // Message title
    QJsonObject object;
    object["title"] = "user";
    object["name"] = "getPersonal";
    object["body"] = bodyArr;    

    // Send message
    m_socket->sendJSON(object);
}

void User_Socket::send_setPersonal(const UserData &userData) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["username"] = userData.username();
    userObj["password"] = userData.password();
    userObj["nickname"] = userData.nickname();
    userObj["signature"] = userData.signature();
    userObj["pfp"] = PixToStr::pixToStr(userData.pfp());
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "user";
    object["name"] = "setPersonal";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void User_Socket::rcv_userJSON(const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "getPersonal"){
        this->proc_getPersonal(object);
    }else if(name == "setPersonal"){
        this->proc_setPersonal(object);
    }
}

void User_Socket::proc_getPersonal(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject userObj = bodyArr.first().toObject();
    UserData userData;
    userData.setUsername(userObj["username"].toString());
    userData.setPassword(userObj["password"].toString());
    userData.setNickname(userObj["nickname"].toString());
    userData.setSignature(userObj["signature"].toString());
    userData.setPfp(PixToStr::strToPix(userObj["pfp"].toString()));

    // Send signal with data
    emit rcv_getPersonal(userData);
}

void User_Socket::proc_setPersonal(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int status = bodyObj["status"].toInt();

    // Send signal with data
    emit rcv_setPersonal(status);
}
