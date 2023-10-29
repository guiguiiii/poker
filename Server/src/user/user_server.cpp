#include "user_server.h"

#include "user_file.h"
#include "src/common/pixtostr.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

User_Server::User_Server(QObject *parent)
    : QObject{parent}
{

}

void User_Server::rcv_userJSON(int id, const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "getPersonal"){
        this->proc_getPersonal(id);
    }else if(name == "setPersonal"){
        this->proc_setPersonal(id,object);
    }
}

void User_Server::proc_getPersonal(int id)
{
    // Process
    UserData userData = User_File::getPersonal(id);

    // Send messages
    this->send_getPersonal(id,userData);
}

void User_Server::proc_setPersonal(int id, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject userObj = bodyArr.first().toObject();
    UserData userData;
    userData.setUsername(userObj["username"].toString());
    userData.setPassword(userObj["password"].toString());
    userData.setNickname(userObj["nickname"].toString());
    userData.setSignature(userObj["signature"].toString());
    userData.setPfp(PixToStr::strToPix(userObj["pfp"].toString()));

    // Process
    int status = User_File::setPersonal(id,userData);

    // Send messages
    this->send_setPersonal(id,status);
}

void User_Server::send_getPersonal(int id, const UserData &userData)
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
    object["name"] = "getPersonal";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}

void User_Server::send_setPersonal(int id, int status)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject personalObj;
    personalObj["status"] = status;
    bodyArr.append(personalObj);

    // Message title
    QJsonObject object;
    object["title"] = "user";
    object["name"] = "setPersonal";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(id,object);
}
