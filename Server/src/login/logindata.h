#ifndef LOGINDATA_H
#define LOGINDATA_H

#include <QString>

class LoginData
{
public:
    LoginData();
    LoginData(const QString &username, const QString &password);

    QString username() const;
    void setUsername(const QString &newUsername);
    QString password() const;
    void setPassword(const QString &newPassword);

private:
    QString m_username;
    QString m_password;
};

#endif // LOGINDATA_H
