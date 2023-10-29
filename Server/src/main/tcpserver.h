#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent);

public:
    void sendJSON(QTcpSocket *socket, const QJsonObject &object);

signals:
    void signal_newConnection(QTcpSocket *socket);
    void signal_readyRead(QTcpSocket *socket, const QJsonObject &object);
    void signal_disconnected(QTcpSocket *socket);

private:
    QTcpServer *m_tcpServer;

private:
    void write(QTcpSocket *socket, const QByteArray &data);

private slots:
    void newConnection();
    void readyRead();
    void disconnected();
};

#endif // TCPSERVER_H
