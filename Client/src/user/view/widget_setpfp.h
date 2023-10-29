#ifndef WIDGET_SETPFP_H
#define WIDGET_SETPFP_H

#include <QWidget>
#include <QPixmap>
#include <QDropEvent>
#include <QDragEnterEvent>

namespace Ui {
class Widget_SetPFP;
}

class Widget_SetPFP : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_SetPFP(QWidget *parent);
    ~Widget_SetPFP();

signals:
    void signal_savePFP(const QPixmap &pfp);

private:
    Ui::Widget_SetPFP *ui;
    QPixmap m_pfp;

private slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *ev);
    void dropEvent(QDropEvent *ev);
};

#endif // WIDGET_SETPFP_H
