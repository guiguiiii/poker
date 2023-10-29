#ifndef WIDGET_TIPS_H
#define WIDGET_TIPS_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class Widget_Tips;
}

class Widget_Tips : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Tips(QWidget *parent);
    explicit Widget_Tips(QWidget *parent, const QString &text);
    explicit Widget_Tips(QWidget *parent, const QString &title, const QString &text);
    ~Widget_Tips();

public:
    void setTitle(const QString &title);
    void setText(const QString &text);
    void setBtnText(const QString &text);

private:
    Ui::Widget_Tips *ui;

private slots:
    void on_btn_close_clicked();

protected:
    void keyPressEvent(QKeyEvent *ev);
};

#endif // WIDGET_TIPS_H
