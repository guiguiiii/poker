#ifndef FORM_SIGNUP_H
#define FORM_SIGNUP_H

#include "../model/signupdata.h"

#include <QWidget>

namespace Ui {
class Form_SignUp;
}

class Form_SignUp : public QWidget
{
    Q_OBJECT

public:
    Form_SignUp(QWidget *parent);
    ~Form_SignUp();

public:
    void signUpFailed();

signals:
    void signal_signUp(const SignUpData &signUpData);
    void signal_signUpCancel();

private:
    Ui::Form_SignUp *ui;

private slots:
    void on_btn_signUp_clicked();
    void on_btn_cancel_clicked();
    void on_le_username_returnPressed();
    void on_le_password_returnPressed();
    void on_le_password_2_returnPressed();
    void on_le_nickname_returnPressed();
};

#endif // FORM_SIGNUP_H
