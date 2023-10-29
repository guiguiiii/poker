#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    // Init tcpServer
    m_tcpServer = new TcpServer(this);
    connect(m_tcpServer, &TcpServer::signal_newConnection, this, &Server::slot_tcpServer_newConnection);
    connect(m_tcpServer, &TcpServer::signal_readyRead, this, &Server::slot_tcpServer_readyRead);
    connect(m_tcpServer, &TcpServer::signal_disconnected, this, &Server::slot_tcpServer_disconnected);

    // Init login_server
    m_loginServer = new Login_Server(this);
    connect(m_loginServer, &Login_Server::signal_sendJSON, this, &Server::slot_loginServer_sendJSON);
    connect(m_loginServer, &Login_Server::signal_loginOK, this, &Server::slot_loginServer_loginOK);
    connect(m_loginServer, &Login_Server::signal_signUpOK, this, &Server::slot_loginServer_signUpOK);
}

void Server::sendJSON(int id, const QJsonObject &object)
{
    QTcpSocket *socket = m_socketAIds.key(id);
    if(socket != nullptr)
        m_tcpServer->sendJSON(socket,object);
}

void Server::slot_tcpServer_newConnection(QTcpSocket *socket)
{
    m_socketAIds.insert(socket,-1);
}

void Server::slot_tcpServer_readyRead(QTcpSocket *socket, const QJsonObject &object)
{
    QString title = object["title"].toString();
    if(title == "login"){
        m_loginServer->rcv_loginJSON(socket,object);
    }else{
        int id = m_socketAIds.value(socket);
        if(id == -1){
            return;
        }else if(title == "user"){
            emit rcv_userJSON(id,object);
        }else if(title == "gameHub"){
            emit rcv_gameHubJSON(id,object);
        }else if(title == "game"){
            emit rcv_gameJSON(id,object);
        }
    }
}

void Server::slot_tcpServer_disconnected(QTcpSocket *socket)
{
    emit signal_disConnected(m_socketAIds.value(socket));
    m_socketAIds.remove(socket);
    socket->deleteLater();
}

void Server::slot_loginServer_sendJSON(QTcpSocket *socket, const QJsonObject &object)
{
    if(m_socketAIds.contains(socket))
        m_tcpServer->sendJSON(socket,object);
}

void Server::slot_loginServer_loginOK(QTcpSocket *socket, int id)
{
    bool online = false;
    for(auto it = m_socketAIds.begin(); it != m_socketAIds.end(); it++)
        if(it.value() == id){
            online = true;
            break;
        }

    if(online == false)
        m_socketAIds.insert(socket,id);

    m_loginServer->idCheckOnline(socket,online);
}

void Server::slot_loginServer_signUpOK(QTcpSocket *socket, int id)
{
    m_socketAIds.insert(socket,id);
}
