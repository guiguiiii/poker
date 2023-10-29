#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QPixmap>

class PublicData
{
public:
    PublicData();
    PublicData(int id, const QString &nickname, const QPixmap &pfp);

    int id() const;
    void setId(int newId);
    QString nickname() const;
    void setNickname(const QString &newNickname);
    QPixmap pfp() const;
    void setPfp(const QPixmap &newPfp);

private:
    int m_id;
    QString m_nickname;
    QPixmap m_pfp;
};

#endif // PUBLICDATA_H
