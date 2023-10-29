#include "lounge.h"

Lounge::Lounge()
{

}

Lounge::Lounge(int loungeID) : m_loungeID(loungeID)
{}

int Lounge::loungeID() const
{
    return m_loungeID;
}

int Lounge::playerNum() const
{
    return m_players.size();
}

QVector<int> Lounge::playerIDs()
{
    QVector<int> IDs;
    for(const PlayerData &playerData: m_players)
        IDs.push_back(playerData.id());
    return IDs;
}

bool Lounge::containsID(int id)
{
    for(const PlayerData &playerData: m_players)
        if(playerData.id() == id)
            return true;
    return false;
}

QVector<PlayerData> Lounge::players()
{
    return m_players;
}

bool Lounge::isReadyGame()
{
    if(m_players.size() != 3)
        return false;

    for(const PlayerData &playerData: m_players)
        if(playerData.isReady() == false)
            return false;
    return true;
}

bool Lounge::enterLounge(const PublicData &publicData)
{
    if(m_players.size() >= 3)
        return false;

    PlayerData playerData(publicData);

    if(m_players.contains(playerData) == true)
        return false;
    else{
        m_players.push_back(playerData);
        return true;
    }
}

void Lounge::readyGame(int id, bool isReady)
{
    for(PlayerData &playerData: m_players){
        if(playerData.id() == id){
            playerData.setIsReady(isReady);
            return;
        }
    }
}

void Lounge::leaveLounge(int id)
{
    for(PlayerData &playerData: m_players){
        if(playerData.id() == id){
            m_players.removeOne(playerData);
            return;
        }
    }
}
