#ifndef WIDGET_CARDLBL_H
#define WIDGET_CARDLBL_H

#include "../model/carddata.h"

#include <QWidget>

namespace Ui {
class Widget_CardLbl;
}

class Widget_CardLbl : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_CardLbl(QWidget *parent, const CardData &cardData);
    ~Widget_CardLbl();

public:
    void enlarge();

private:
    Ui::Widget_CardLbl *ui;

private:
    void initUI(const CardData &cardData);
};

#endif // WIDGET_CARDLBL_H
