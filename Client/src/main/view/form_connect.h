#ifndef FORM_CONNECT_H
#define FORM_CONNECT_H

#include <QWidget>

namespace Ui {
class Form_Connect;
}

class Form_Connect : public QWidget
{
    Q_OBJECT
public:
    explicit Form_Connect(QWidget *parent);
    ~Form_Connect();

signals:
    void signal_connectToHost(const QString &address, int port);

private:
    Ui::Form_Connect *ui;

private slots:
    void on_btn_config_clicked();
    void on_btn_cancel_clicked();
    void on_btn_confirm_clicked();
    void on_btn_connect_clicked();
};

#endif // FORM_CONNECT_H
