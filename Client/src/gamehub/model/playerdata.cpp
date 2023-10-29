#include "playerdata.h"

PlayerData::PlayerData()
{

}

PlayerData::PlayerData(int id, const QString &nickname, const QPixmap &pfp, bool isReady) : m_id(id),
    m_nickname(nickname),
    m_pfp(pfp),
    m_isReady(isReady)
{}

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
