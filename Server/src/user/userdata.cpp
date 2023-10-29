#include "userdata.h"

UserData::UserData()
{

}

UserData::UserData(const QString &username, const QString &password, const QString &nickname, const QString &signature, const QPixmap &pfp) : m_username(username),
    m_password(password),
    m_nickname(nickname),
    m_signature(signature),
    m_pfp(pfp)
{}

QString UserData::username() const
{
    return m_username;
}

void UserData::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}

QString UserData::password() const
{
    return m_password;
}

void UserData::setPassword(const QString &newPassword)
{
    m_password = newPassword;
}

QString UserData::nickname() const
{
    return m_nickname;
}

void UserData::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}

QString UserData::signature() const
{
    return m_signature;
}

void UserData::setSignature(const QString &newSignature)
{
    m_signature = newSignature;
}

QPixmap UserData::pfp() const
{
    return m_pfp;
}

void UserData::setPfp(const QPixmap &newPfp)
{
    m_pfp = newPfp;
}
