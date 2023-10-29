#ifndef SIGNUPDATA_H
#define SIGNUPDATA_H

#include <QString>

class SignUpData
{
public:
    SignUpData();
    SignUpData(const QString &username, const QString &password, const QString &nickname);

    QString username() const;
    void setUsername(const QString &newUsername);
    QString password() const;
    void setPassword(const QString &newPassword);
    QString nickname() const;
    void setNickname(const QString &newNickname);

private:
    QString m_username;
    QString m_password;
    QString m_nickname;
};

#endif // SIGNUPDATA_H
