#include "logindata.h"

LoginData::LoginData()
{

}

LoginData::LoginData(const QString &username, const QString &password) : m_username(username),
    m_password(password)
{}

QString LoginData::username() const
{
    return m_username;
}

void LoginData::setUsername(const QString &newUsername)
{
    m_username = newUsername;
}

QString LoginData::password() const
{
    return m_password;
}

void LoginData::setPassword(const QString &newPassword)
{
    m_password = newPassword;
}
