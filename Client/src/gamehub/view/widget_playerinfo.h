#ifndef WIDGET_PLAYERINFO_H
#define WIDGET_PLAYERINFO_H

#include "../model/playerdata.h"

#include <QWidget>

namespace Ui {
class Widget_PlayerInfo;
}

class Widget_PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_PlayerInfo(QWidget *parent, const PlayerData &playerData);
    ~Widget_PlayerInfo();

public:
    void setIsReady(bool isReady);

private:
    Ui::Widget_PlayerInfo *ui;
};

#endif // WIDGET_PLAYERINFO_H
