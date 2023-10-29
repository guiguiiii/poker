#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <QObject>
#include <QTcpSocket>

class Login_Server : public QObject
{
    Q_OBJECT
public:
    explicit Login_Server(QObject *parent);

public:
    // Receive
    void rcv_loginJSON(QTcpSocket *socket, const QJsonObject &object);

public:
    void idCheckOnline(QTcpSocket *socket, bool online);

private:
    // Process
    void proc_login(QTcpSocket *socket, const QJsonObject &object);
    void proc_signUp(QTcpSocket *socket, const QJsonObject &object);

private:
    // Send
    void send_login(QTcpSocket *socket, int status);
    void send_signUp(QTcpSocket *socket, int status);

signals:
    // Send messages to client
    void signal_sendJSON(QTcpSocket *socket, const QJsonObject &object);

signals:
    // Signals to Server
    void signal_loginOK(QTcpSocket *socket, int id);
    void signal_signUpOK(QTcpSocket *socket, int id);
};

#endif // LOGIN_SERVER_H
