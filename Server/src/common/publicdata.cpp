#include "publicdata.h"

PublicData::PublicData()
{

}

PublicData::PublicData(int id, const QString &nickname, const QPixmap &pfp) : m_id(id),
    m_nickname(nickname),
    m_pfp(pfp)
{}

int PublicData::id() const
{
    return m_id;
}

void PublicData::setId(int newId)
{
    m_id = newId;
}

QString PublicData::nickname() const
{
    return m_nickname;
}

void PublicData::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}

QPixmap PublicData::pfp() const
{
    return m_pfp;
}

void PublicData::setPfp(const QPixmap &newPfp)
{
    m_pfp = newPfp;
}
