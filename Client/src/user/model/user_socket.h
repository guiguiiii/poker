#ifndef USER_SOCKET_H
#define USER_SOCKET_H

#include "src/main/model/socket.h"
#include "userdata.h"

#include <QObject>

class User_Socket : public QObject
{
    Q_OBJECT
public:
    explicit User_Socket(Socket *socket);

public:
    // Send messages to server
    void send_getPersonal() const;
    void send_setPersonal(const UserData &userData) const;

signals:
    // Receive messages from server
    void rcv_getPersonal(const UserData &userData);
    void rcv_setPersonal(int status);

private:
    Socket *m_socket;

// Process messages from server
private slots:
    // First
    void rcv_userJSON(const QJsonObject &object);

private:
    // Sencond
    void proc_getPersonal(const QJsonObject &object);
    void proc_setPersonal(const QJsonObject &object);
};

#endif // USER_SOCKET_H
