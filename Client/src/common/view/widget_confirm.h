#ifndef WIDGET_CONFIRM_H
#define WIDGET_CONFIRM_H

#include <QWidget>

namespace Ui {
class Widget_Confirm;
}

class Widget_Confirm : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Confirm(QWidget *parent);
    explicit Widget_Confirm(QWidget *parent, const QString &text);
    explicit Widget_Confirm(QWidget *parent, const QString &title, const QString &text);
    ~Widget_Confirm();

public:
    void setTitle(const QString &title);
    void setText(const QString &text);
    void setBtnConfirm(const QString &text);
    void setBtnCancel(const QString &text);

signals:
    void confirm();
    void cancel();

private:
    Ui::Widget_Confirm *ui;

private slots:
    void on_btn_confirm_clicked();
    void on_btn_cancel_clicked();
};

#endif // WIDGET_CONFIRM_H
