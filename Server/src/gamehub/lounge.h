#ifndef LOUNGE_H
#define LOUNGE_H

#include "playerdata.h"
#include "src/common/publicdata.h"

class Lounge
{
public:
    Lounge();
    Lounge(int loungeID);

public:
    int loungeID() const;
    int playerNum() const;
    QVector<int> playerIDs();
    bool containsID(int id);
    QVector<PlayerData> players();
    bool isReadyGame();

public:
    bool enterLounge(const PublicData &publicData);
    void readyGame(int id, bool isReady);
    void leaveLounge(int id);

private:
    int m_loungeID;
    QVector<PlayerData> m_players;
};

#endif // LOUNGE_H
