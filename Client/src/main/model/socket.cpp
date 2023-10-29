#include "socket.h"

#include <QJsonDocument>

Socket::Socket(QObject *parent)
    : QObject{parent}
{
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &Socket::signal_connected);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &Socket::readyRead);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &Socket::signal_disconnected);
}

void Socket::connectToHost(const QString &address, int port)
{
    m_tcpSocket->connectToHost(address,port);
}

void Socket::sendJSON(const QJsonObject &object)
{
    QByteArray data = QJsonDocument(object).toJson();
    this->write(data);
}

void Socket::write(const QByteArray &data)
{
    quint32 dataSize = data.size();
    QByteArray message;
    QDataStream stream(&message, QIODevice::WriteOnly);
    stream << dataSize;
    message.append(data);
    m_tcpSocket->write(message);
}

void Socket::processData(const QByteArray &data)
{
    QJsonObject object = QJsonDocument::fromJson(data).object();
    QString title = object["title"].toString();
    if(title == "login"){
        emit rcv_loginJSON(object);
    }else if(title == "user"){
        emit rcv_userJSON(object);
    }else if(title == "gameHub"){
        emit rcv_gameHubJSON(object);
    }else if(title == "game"){
        emit rcv_gameJSON(object);
    }
}

void Socket::readyRead()
{
    static QByteArray s_data;
    while(m_tcpSocket->bytesAvailable() > 0){
        QByteArray data = m_tcpSocket->readAll();
        if(s_data.isEmpty() == false){
            data = s_data + data;
            s_data.resize(0);
        }

        while(data.size() >= 4){
            quint32 dataSize;
            QDataStream stream(&data, QIODevice::ReadOnly);
            stream >> dataSize;

            if(data.size() >= dataSize + 4){
                QByteArray packet = data.mid(4, dataSize);
                data = data.mid(dataSize + 4);
                this->processData(packet);
            }else{
                s_data.push_back(data);
                break;
            }
        }
    }
}
