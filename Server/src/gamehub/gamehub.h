#ifndef GAMEHUB_H
#define GAMEHUB_H

#include "loungedata.h"
#include "lounge.h"
#include "src/common/publicdata.h"

#include <QObject>
#include <QMap>

class GameHub : public QObject
{
    Q_OBJECT
public:
    explicit GameHub(QObject *parent);

public:
    // Process
    // ( gamehub )
    QVector<LoungeData> getLounges();
    PublicData getPublicData(int id);
    int enterLounge(int id, int loungeID);
    int quickStart(int id);
    int newLounge(int id);

    // ( lounge )
    QVector<PlayerData> getPlayers(int id, int loungeID = -1);
    void readyGame(int id, bool isReady, int loungeID = -1);
    void leaveLounge(int id, int loungeID = -1);

signals:
    void playerJoin(int id, const PublicData &publicData);
    void playerReady(int id, int playerID, bool isReady);
    void playerLeave(int id, int playerID);
    void signal_gameStart(QVector<int> playerIDs);

private:
    QMap<int, Lounge> m_lounges;
};

#endif // GAMEHUB_H
