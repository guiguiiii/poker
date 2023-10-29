#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent);

public:
    void connectToHost(const QString &address, int port);

public:
    void sendJSON(const QJsonObject &object);

signals:
    void rcv_loginJSON(const QJsonObject &object);
    void rcv_userJSON(const QJsonObject &object);
    void rcv_gameHubJSON(const QJsonObject &object);
    void rcv_gameJSON(const QJsonObject &object);

signals:
    void signal_connected();
    void signal_disconnected();

private:
    QTcpSocket *m_tcpSocket;

private:
    void write(const QByteArray &data);
    void processData(const QByteArray &data);

private slots:
    void readyRead();
};

#endif // SOCKET_H
