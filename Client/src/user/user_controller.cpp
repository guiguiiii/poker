#include "user_controller.h"

#include "src/main/model/socketfactory.h"

User_Controller::User_Controller(QWidget *parent)
    : QWidget{parent}
{
    m_formPersonal = nullptr;
    m_formSettings = nullptr;

    // Init user_socket
    m_userSocket = SocketFactory::userSocket();
    connect(m_userSocket, &User_Socket::rcv_getPersonal, this, &User_Controller::rcv_getPersonal);
    connect(m_userSocket, &User_Socket::rcv_setPersonal, this, &User_Controller::rcv_setPersonal);

    // Init form_start and show it
    m_formStart = new Form_Start(this);
    connect(m_formStart, &Form_Start::signal_moveToGameHub, this, &User_Controller::slot_formStart_moveToGameHub);
    connect(m_formStart, &Form_Start::signal_moveToPersonal, this, &User_Controller::slot_formStart_moveToPersonal);
    connect(m_formStart, &Form_Start::signal_moveToSettings, this, &User_Controller::slot_formStart_moveToSettings);
    m_formStart->setVisible(true);
}

void User_Controller::rcv_getPersonal(const UserData &userData)
{
    // Hide form_start
    if(m_formStart == nullptr)
        return;

    m_formStart->setParent(nullptr);
    m_formStart->setVisible(false);

    // Init form_personal and show it
    m_formPersonal = new Form_Personal(this);
    m_formPersonal->initPersonalData(userData);   // (Data from socket)
    connect(m_formPersonal, &Form_Personal::signal_setPersonal, m_userSocket, &User_Socket::send_setPersonal);
    connect(m_formPersonal, &Form_Personal::signal_cancel, this, &User_Controller::slot_formPersonal_moveToStart);
    m_formPersonal->setVisible(true);
}

void User_Controller::rcv_setPersonal(int status)
{
    if(m_formPersonal != nullptr)
        m_formPersonal->setPersonalStatus(status);
}

void User_Controller::slot_formStart_moveToGameHub()
{
    emit signal_moveToGameHub();
}

void User_Controller::slot_formStart_moveToPersonal()
{
    if(m_userSocket != nullptr)
        m_userSocket->send_getPersonal();
}

void User_Controller::slot_formStart_moveToSettings()
{
    // Hide form_start
    if(m_formStart == nullptr)
        return;

    m_formStart->setParent(nullptr);
    m_formStart->setVisible(false);

    // Init form_settings and show it
    m_formSettings = new Form_Settings(this);
/*    connect(m_formSettings, &Form_Settings::setSettings, m_userSocket, &UserSocket::setSettings);    */
    connect(m_formSettings, &Form_Settings::signal_cancel, this, &User_Controller::slot_formSettings_moveToStart);
    m_formSettings->setVisible(true);
}

void User_Controller::slot_formPersonal_moveToStart()
{
    // Delete form_personal
    if(m_formPersonal == nullptr)
        return;

    m_formPersonal->setParent(nullptr);
    m_formPersonal->setVisible(false);
    m_formPersonal->deleteLater();
    m_formPersonal = nullptr;

    // Show form_start
    if(m_formStart == nullptr)
        return;

    m_formStart->setParent(this);
    m_formStart->setVisible(true);
}

void User_Controller::slot_formSettings_moveToStart()
{
    // Delete form_settings
    if(m_formSettings == nullptr)
        return;

    m_formSettings->setParent(nullptr);
    m_formSettings->setVisible(false);
    m_formSettings->deleteLater();
    m_formSettings = nullptr;

    // Show form_start
    if(m_formStart == nullptr)
        return;

    m_formStart->setParent(this);
    m_formStart->setVisible(true);
}
