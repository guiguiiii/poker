#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <QPixmap>

class PlayerData
{
public:
    PlayerData();
    PlayerData(int id, const QString &nickname, const QPixmap &pfp, bool isReady);

    int id() const;
    void setId(int newId);
    QString nickname() const;
    void setNickname(const QString &newNickname);
    QPixmap pfp() const;
    void setPfp(const QPixmap &newPfp);
    bool isReady() const;
    void setIsReady(bool newIsReady);

private:
    int m_id;
    QString m_nickname;
    QPixmap m_pfp;
    bool m_isReady;
};

#endif // PLAYERDATA_H
