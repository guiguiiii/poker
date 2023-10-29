#ifndef SERVER_H
#define SERVER_H

#include "tcpserver.h"
#include "src/login/login_server.h"

#include <QObject>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent);

public:
    // Send messages to client
    void sendJSON(int id, const QJsonObject &object);

signals:
    // Client disConnected
    void signal_disConnected(int id);

signals:
    // Receive messages from client
    void rcv_userJSON(int id ,const QJsonObject &object);
    void rcv_gameHubJSON(int id, const QJsonObject &object);
    void rcv_gameJSON(int id, const QJsonObject &object);

private:
    // Server pointers
    TcpServer *m_tcpServer;
    Login_Server *m_loginServer;

private:
    // Client's TcpSocket and ID
    QMap<QTcpSocket *, int> m_socketAIds;

private:
    void proc_login_request(QTcpSocket *socket, const QJsonObject &object);

private slots:
    // Process signals from tcpServer
    void slot_tcpServer_newConnection(QTcpSocket *socket);
    void slot_tcpServer_readyRead(QTcpSocket *socket, const QJsonObject &object);
    void slot_tcpServer_disconnected(QTcpSocket *socket);

private slots:
    // Process signals from login_server
    void slot_loginServer_sendJSON(QTcpSocket *socket, const QJsonObject &object);
    void slot_loginServer_loginOK(QTcpSocket *socket, int id);
    void slot_loginServer_signUpOK(QTcpSocket *socket, int id);
};

#endif // SERVER_H
