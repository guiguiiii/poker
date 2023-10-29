#ifndef FORM_GAMEHUB_H
#define FORM_GAMEHUB_H

#include "src/common/model/publicdata.h"
#include "widget_loungeinfo.h"

#include <QWidget>

namespace Ui {
class Form_GameHub;
}

class Form_GameHub : public QWidget
{
    Q_OBJECT

public:
    explicit Form_GameHub(QWidget *parent);
    ~Form_GameHub();

public:
    void initLounges(const QVector<LoungeData> &lounges);
    void initPublicData(const PublicData &publicData);
    void enterLoungeFailed(int status);

signals:
    void signal_moveToStart();
    void signal_enterLounge(int loungeID);
    void signal_quickStart();
    void signal_newGame();
    void signal_getLounges();

private:
    Ui::Form_GameHub *ui;

private:
    QPixmap m_pfp;
    QMap<int, Widget_LoungeInfo *> m_lounges;

private:
    void newWidgetLoungeInfo(const LoungeData &loungeData);

private slots:
    void widget_loungeInfo_clicked();

private slots:
    void on_btn_back_clicked();
    void on_btn_quickStart_clicked();
    void on_btn_newLounge_clicked();
    void on_btn_loungeByID_clicked();
    void on_le_loungeID_returnPressed();
    void on_btn_refresh_clicked();
    void on_btn_pfp_clicked();
};

#endif // FORM_GAMEHUB_H
