#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

#include "model/login_socket.h"
#include "view/form_login.h"
#include "view/form_signup.h"

#include <QObject>

class Login_Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Login_Controller(QWidget *parent);

signals:
    // Move to User_Controller
    void signal_moveToUser();

private:
    // TcpSocket pointer
    const Login_Socket *m_loginSocket;

private:
    // View pointers
    Form_Login *m_formLogin;
    Form_SignUp *m_formSignUp;

private slots:
    // Process signals from socket
    void rcv_login(int status);
    void rcv_signUp(int status);

private slots:
    // Process signals from form_login
    void slot_formLogin_moveToSignUp();

    // Process signals from form_signUp
    void slot_formSignUp_signUpCancel();
};

#endif // LOGIN_CONTROLLER_H
