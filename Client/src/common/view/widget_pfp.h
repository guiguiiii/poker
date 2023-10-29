#ifndef WIDGET_PFP_H
#define WIDGET_PFP_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>

namespace Ui {
class Widget_PFP;
}

class Widget_PFP : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_PFP(QWidget *parent, const QPixmap &pfp);
    ~Widget_PFP();

private:
    Ui::Widget_PFP *ui;

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // WIDGET_PFP_H
