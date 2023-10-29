#include "login_socket.h"

#include <QJsonArray>

Login_Socket::Login_Socket(Socket *socket)
{
    m_socket = socket;
    this->setParent(m_socket->parent());
    connect(m_socket, &Socket::rcv_loginJSON, this, &Login_Socket::rcv_loginJSON);
}

void Login_Socket::send_login(const LoginData &loginData) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["username"] = loginData.username();
    userObj["password"] = loginData.password();
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "login";
    object["name"] = "login";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Login_Socket::send_signUp(const SignUpData &signUpData) const
{
    // Message body
    QJsonArray bodyArr;
    QJsonObject userObj;
    userObj["username"] = signUpData.username();
    userObj["password"] = signUpData.password();
    userObj["nickname"] = signUpData.nickname();
    bodyArr.append(userObj);

    // Message title
    QJsonObject object;
    object["title"] = "login";
    object["name"] = "signUp";
    object["body"] = bodyArr;

    // Send message
    m_socket->sendJSON(object);
}

void Login_Socket::rcv_loginJSON(const QJsonObject &object)
{
    QString name = object["name"].toString();
    if(name == "login"){
        this->proc_login(object);
    }else if(name == "signUp"){
        this->proc_signUp(object);
    }
}

void Login_Socket::proc_login(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int status = bodyObj["status"].toInt();

    // Send signal with data
    emit rcv_login(status);
}

void Login_Socket::proc_signUp(const QJsonObject &object)
{
    // Get bodyArr
    QJsonArray bodyArr = object["body"].toArray();

    // Get data
    QJsonObject bodyObj = bodyArr.first().toObject();
    int status = bodyObj["status"].toInt();

    // Send signal with data
    emit rcv_signUp(status);
}
