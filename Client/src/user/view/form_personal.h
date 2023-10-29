#ifndef FORM_PERSONAL_H
#define FORM_PERSONAL_H

#include "../model/userdata.h"

#include <QWidget>

namespace Ui {
class Form_Personal;
}

class Form_Personal : public QWidget
{
    Q_OBJECT

public:
    Form_Personal(QWidget *parent);
    ~Form_Personal();

public:
    void initPersonalData(const UserData &userData);
    void setPersonalStatus(int status);

signals:
    void signal_setPersonal(const UserData &userData);
    void signal_cancel();

private:
    Ui::Form_Personal *ui;

private:
    QPixmap m_pfp;

private slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();
    void on_btn_pfp_clicked();
    void on_btn_setPFP_clicked();
    void on_le_nickname_returnPressed();
    void on_le_username_returnPressed();
    void on_le_password_returnPressed();
};

#endif // FORM_PERSONAL_H
