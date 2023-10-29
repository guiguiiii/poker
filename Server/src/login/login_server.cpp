#include "login_server.h"

#include "login_file.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Login_Server::Login_Server(QObject *parent)
    : QObject{parent}
{

}

void Login_Server::rcv_loginJSON(QTcpSocket *socket, const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "login"){
        this->proc_login(socket,object);
    }else if(name == "signUp"){
        this->proc_signUp(socket,object);
    }
}

void Login_Server::idCheckOnline(QTcpSocket *socket, bool online)
{
    if(online == false)
        this->send_login(socket, 1);
    else
        this->send_login(socket, 4);
}

void Login_Server::proc_login(QTcpSocket *socket, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject userObj = bodyArr.first().toObject();
    LoginData loginData;
    loginData.setUsername(userObj["username"].toString());
    loginData.setPassword(userObj["password"].toString());

    // Process
    int status = Login_File::login(loginData);
    if(status == 1){
        int id = Login_File::userID(loginData.username());
        emit signal_loginOK(socket,id);

    // Send messages
    }else
        this->send_login(socket,status);
}

void Login_Server::proc_signUp(QTcpSocket *socket, const QJsonObject &object)
{
    // Get data
    QJsonArray bodyArr = object["body"].toArray();
    QJsonObject userObj = bodyArr.first().toObject();
    SignUpData signUpData;
    signUpData.setUsername(userObj["username"].toString());
    signUpData.setPassword(userObj["password"].toString());
    signUpData.setNickname(userObj["nickname"].toString());

    // Process
    int status = Login_File::signUp(signUpData);
    if(status == 1){
        int id = Login_File::userID(signUpData.username());
        emit signal_signUpOK(socket,id);
    }

    // Send messages
    this->send_signUp(socket,status);
}

void Login_Server::send_login(QTcpSocket *socket, int status)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["status"] = status;
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "login";
    object["name"] = "login";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(socket,object);
}

void Login_Server::send_signUp(QTcpSocket *socket, int status)
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["status"] = status;
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "login";
    object["name"] = "signUp";
    object["body"] = bodyArr;

    // Send message
    emit signal_sendJSON(socket,object);
}
