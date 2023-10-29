#include "loungedata.h"

LoungeData::LoungeData()
{

}

LoungeData::LoungeData(int loungeID, int playerNum) : m_loungeID(loungeID),
    m_playerNum(playerNum)
{}

int LoungeData::loungeID() const
{
    return m_loungeID;
}

void LoungeData::setLoungeID(int newLoungeID)
{
    m_loungeID = newLoungeID;
}

int LoungeData::playerNum() const
{
    return m_playerNum;
}

void LoungeData::setPlayerNum(int newPlayerNum)
{
    m_playerNum = newPlayerNum;
}
