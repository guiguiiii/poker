#include "tcpserver.h"

#include <QJsonDocument>

/*
 *temp
 */
#include <QJsonArray>

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
    this->m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection, this, &TcpServer::newConnection);
    m_tcpServer->listen(QHostAddress::Any, 10523);
}

void TcpServer::sendJSON(QTcpSocket *socket, const QJsonObject &object)
{
    QByteArray byteArr = QJsonDocument(object).toJson();

    /*temp*/
    QByteArray bodyStr = QJsonDocument(object["body"].toArray()).toJson();
    bodyStr.replace('\n',"");
    bodyStr.replace('\"','\'');
    bodyStr.replace(' ',"");
    bodyStr.replace(',',", ");
    int beginIndex = 0;
    while(1){
        int index = bodyStr.indexOf("pfp",beginIndex);
        if(index != -1){
            beginIndex = index + 1;
            int indexR = bodyStr.indexOf('\'',index + 6);
            bodyStr.remove(index + 6,indexR - index - 6);
        }else
            break;
    }
    qDebug()<<"WRITE: "<<object["name"].toString()<<object["title"].toString()<<bodyStr;

    this->write(socket, byteArr);
}

void TcpServer::write(QTcpSocket *socket, const QByteArray &data)
{
    quint32 dataSize = data.size();
    QByteArray message;
    QDataStream stream(&message, QIODevice::WriteOnly);
    stream << dataSize;
    message.append(data);
    socket->write(message);
}

void TcpServer::newConnection()
{
    while(m_tcpServer->hasPendingConnections() == true){
        QTcpSocket* socket = m_tcpServer->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &TcpServer::disconnected);
        emit signal_newConnection(socket);
    }
}

void TcpServer::readyRead()
{
    static QHash<QTcpSocket*, QByteArray> s_data;

    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    while(socket->bytesAvailable() > 0){
        QByteArray data = socket->readAll();
        if(s_data.contains(socket)){
            data = s_data.value(socket) + data;
            s_data.remove(socket);
        }

        while(data.size() >= 4){
            quint32 dataSize;
            QDataStream stream(&data, QIODevice::ReadOnly);
            stream >> dataSize;

            if(data.size() >= dataSize + 4){
                QByteArray packet = data.mid(4, dataSize);
                data = data.mid(dataSize + 4);

                QJsonObject object = QJsonDocument::fromJson(packet).object();

                /*temp*/
                QByteArray bodyStr = QJsonDocument(object["body"].toArray()).toJson();
                bodyStr.replace('\n',"");
                bodyStr.replace('\"','\'');
                bodyStr.replace(' ',"");
                bodyStr.replace(',',", ");
                int beginIndex = 0;
                while(1){
                    int index = bodyStr.indexOf("pfp",beginIndex);
                    if(index != -1){
                        beginIndex = index + 1;
                        int indexR = bodyStr.indexOf('\'',index + 6);
                        bodyStr.remove(index + 6,indexR - index - 6);
                    }else
                        break;
                }
                qDebug()<<"READ: "<<object["name"].toString()<<object["title"].toString()<<bodyStr;

                emit signal_readyRead(socket,object);

            }else{
                s_data.insert(socket,data);
                break;
            }
        }
    }
}

void TcpServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    emit signal_disconnected(socket);
}
