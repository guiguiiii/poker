#include "login_controller.h"

#include "src/main/model/socketfactory.h"

Login_Controller::Login_Controller(QWidget *parent)
    : QWidget(parent)
{
    m_formSignUp = nullptr;

    // Init login_socket
    m_loginSocket = SocketFactory::loginSocket();
    connect(m_loginSocket, &Login_Socket::rcv_login, this, &Login_Controller::rcv_login);
    connect(m_loginSocket, &Login_Socket::rcv_signUp, this, &Login_Controller::rcv_signUp);

    // Init form_login and show it
    m_formLogin = new Form_Login(this);
    connect(m_formLogin, &Form_Login::signal_login, m_loginSocket, &Login_Socket::send_login);
    connect(m_formLogin, &Form_Login::signal_moveToSignUp, this, &Login_Controller::slot_formLogin_moveToSignUp);
    m_formLogin->setVisible(true);
}

void Login_Controller::rcv_login(int status)
{
    if(status == 1)
        emit signal_moveToUser();
    else if(m_formLogin != nullptr)
        m_formLogin->loginFailed(status);
}

void Login_Controller::rcv_signUp(int status)
{
    if(status == 1)
        emit signal_moveToUser();
    else if(m_formSignUp != nullptr)
        m_formSignUp->signUpFailed();
}

void Login_Controller::slot_formLogin_moveToSignUp()
{
    // Hide form_login
    if(m_formLogin == nullptr)
        return

    m_formLogin->setParent(nullptr);
    m_formLogin->setVisible(false);

    // Init form_signUp and show it
    m_formSignUp = new Form_SignUp(this);
    connect(m_formSignUp, &Form_SignUp::signal_signUp, m_loginSocket, &Login_Socket::send_signUp);
    connect(m_formSignUp, &Form_SignUp::signal_signUpCancel, this, &Login_Controller::slot_formSignUp_signUpCancel);
    m_formSignUp->setVisible(true);
}

void Login_Controller::slot_formSignUp_signUpCancel()
{
    // Delete form_signUp
    if(m_formSignUp == nullptr)
        return;

    m_formSignUp->setParent(nullptr);
    m_formSignUp->setVisible(false);
    m_formSignUp->deleteLater();
    m_formSignUp = nullptr;

    // Show form_login
    if(m_formLogin == nullptr)
        return;

    m_formLogin->setParent(this);
    m_formLogin->setVisible(true);
}
