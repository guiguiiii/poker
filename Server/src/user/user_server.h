#ifndef USER_SERVER_H
#define USER_SERVER_H

#include "userdata.h"

#include <QObject>
#include <QTcpSocket>

class User_Server : public QObject
{
    Q_OBJECT
public:
    explicit User_Server(QObject *parent);

public:
    // Receive
    void rcv_userJSON(int id, const QJsonObject &object);

private:
    // Process
    void proc_getPersonal(int id);
    void proc_setPersonal(int id, const QJsonObject &object);

private:
    // Send
    void send_getPersonal(int id, const UserData &userData);
    void send_setPersonal(int id, int status);

signals:
    // Send messages to client
    void signal_sendJSON(int id, const QJsonObject &object);
};

#endif // USER_SERVER_H
