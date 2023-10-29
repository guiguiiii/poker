#ifndef USERDATA_H
#define USERDATA_H

#include <QPixmap>

class UserData
{
public:
    UserData();
    UserData(const QString &username, const QString &password, const QString &nickname, const QString &signature, const QPixmap &pfp);

    QString username() const;
    void setUsername(const QString &newUsername);
    QString password() const;
    void setPassword(const QString &newPassword);
    QString nickname() const;
    void setNickname(const QString &newNickname);
    QString signature() const;
    void setSignature(const QString &newSignature);
    QPixmap pfp() const;
    void setPfp(const QPixmap &newPfp);

private:
    QString m_username;
    QString m_password;
    QString m_nickname;
    QString m_signature;
    QPixmap m_pfp;
};

#endif // USERDATA_H
