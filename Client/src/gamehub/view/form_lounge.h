#ifndef FORM_LOUNGE_H
#define FORM_LOUNGE_H

#include "../model/playerdata.h"
#include "src/common/model/publicdata.h"
#include "widget_playerinfo.h"

#include <QWidget>

namespace Ui {
class Form_Lounge;
}

class Form_Lounge : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Lounge(QWidget *parent);
    ~Form_Lounge();

public:
    void setLoungeID(int loungeID);
    void initPlayers(const QVector<PlayerData> &players);
    void playerJoin(const PublicData &publicData);
    void playerLeave(int id);
    void playerReady(int id, bool isReady);

signals:
    void signal_readyGame(bool isReady);
    void signal_leaveLounge();

private:
    Ui::Form_Lounge *ui;

private:
    int m_isReady;
    QHash<int, Widget_PlayerInfo *> m_players;

private:
    void newWidgetPlayerInfo(const PlayerData &playerData);

private slots:
    void on_btn_ready_clicked();
    void on_btn_leave_clicked();
};

#endif // FORM_LOUNGE_H
