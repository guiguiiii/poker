#ifndef WIDGET_CARDBTN_H
#define WIDGET_CARDBTN_H

#include "../model/carddata.h"

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Widget_CardBtn;
}

class Widget_CardBtn : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_CardBtn(QWidget *parent, const CardData &cardData);
    ~Widget_CardBtn();

public:
    void enlarge();
    void smaller();

signals:
    void cardSelected(bool selected);

private:
    Ui::Widget_CardBtn *ui;

private:
    bool m_picked;

private:
    void initCardUI(const CardData &cardData);

protected:
    bool eventFilter(QObject *target, QEvent *event);
};

#endif // WIDGET_CARDBTN_H
