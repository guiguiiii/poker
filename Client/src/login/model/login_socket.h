#ifndef LOGIN_SOCKET_H
#define LOGIN_SOCKET_H

#include "src/main/model/socket.h"
#include "logindata.h"
#include "signupdata.h"

#include <QObject>

class Login_Socket : public QObject
{
    Q_OBJECT
public:
    explicit Login_Socket(Socket *socket);

public:
    // Send messages to server
    void send_login(const LoginData &loginData) const;
    void send_signUp(const SignUpData &signUpData) const;

signals:
    // Receive messages from server
    void rcv_login(int status);
    void rcv_signUp(int status);

private:
    Socket *m_socket;

// Process messages from server
private slots:
    // First
    void rcv_loginJSON(const QJsonObject &object);

private:
    // Sencond
    void proc_login(const QJsonObject &object);
    void proc_signUp(const QJsonObject &object);
};

#endif // LOGIN_SOCKET_H
