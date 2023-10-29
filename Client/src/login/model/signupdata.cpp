#include "signupdata.h"

SignUpData::SignUpData()
{

}

SignUpData::SignUpData(const QString &username, const QString &password, const QString &nickname) : m_username(username),
    m_password(password),
    m_nickname(nickname)
{}

QString SignUpData::username() const
{
    return m_username;
}

void SignUpData::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}

QString SignUpData::password() const
{
    return m_password;
}

void SignUpData::setPassword(const QString &newPassword)
{
    m_password = newPassword;
}

QString SignUpData::nickname() const
{
    return m_nickname;
}

void SignUpData::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}
