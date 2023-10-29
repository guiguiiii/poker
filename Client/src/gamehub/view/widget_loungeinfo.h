#ifndef WIDGET_LOUNGEINFO_H
#define WIDGET_LOUNGEINFO_H

#include "../model/loungedata.h"

#include <QWidget>

namespace Ui {
class Widget_LoungeInfo;
}

class Widget_LoungeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_LoungeInfo(QWidget *parent, const LoungeData &loungeData);
    ~Widget_LoungeInfo();

signals:
    void enterLounge();

private:
    Ui::Widget_LoungeInfo *ui;

private slots:
    void on_btn_enter_clicked();
};

#endif // WIDGET_LOUNGEINFO_H
