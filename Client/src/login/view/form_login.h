#ifndef FORM_LOGIN_H
#define FORM_LOGIN_H

#include "../model/logindata.h"

#include <QWidget>

namespace Ui {
class Form_Login;
}

class Form_Login : public QWidget
{
    Q_OBJECT

public:
    Form_Login(QWidget *parent);
    ~Form_Login();

public:
    void loginFailed(int status);

signals:
    void signal_login(const LoginData &loginData);
    void signal_moveToSignUp();

private:
    Ui::Form_Login *ui;

private slots:
    void on_btn_quit_clicked();
    void on_btn_login_clicked();
    void on_btn_signUp_clicked();
    void on_le_username_returnPressed();
    void on_le_password_returnPressed();
};

#endif // FORM_LOGIN_H
