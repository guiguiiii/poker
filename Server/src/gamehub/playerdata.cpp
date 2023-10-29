#include "playerdata.h"

PlayerData::PlayerData()
{

}

PlayerData::PlayerData(int id, const QString &nickname, const QPixmap &pfp, bool isReady) : m_id(id),
    m_nickname(nickname),
    m_pfp(pfp),
    m_isReady(isReady)
{}

PlayerData::PlayerData(const PublicData &publicData)
{
    m_id = publicData.id();
    m_nickname = publicData.nickname();
    m_pfp = publicData.pfp();
    m_isReady = false;
}

bool PlayerData::operator==(const PlayerData &playerData) const
{
    if(m_id == playerData.id() and m_nickname == playerData.nickname()
        and m_pfp.toImage() == playerData.pfp().toImage() and m_isReady == playerData.m_isReady)
        return true;
    return false;
}

int PlayerData::id() const
{
    return m_id;
}

void PlayerData::setId(int newId)
{
    m_id = newId;
}

QString PlayerData::nickname() const
{
    return m_nickname;
}

void PlayerData::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}

QPixmap PlayerData::pfp() const
{
    return m_pfp;
}

void PlayerData::setPfp(const QPixmap &newPfp)
{
    m_pfp = newPfp;
}

bool PlayerData::isReady() const
{
    return m_isReady;
}

void PlayerData::setIsReady(bool newIsReady)
{
    m_isReady = newIsReady;
}
