#include "main_controller.h"

#include "model/socketfactory.h"

Main_Controller::Main_Controller(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(parentWidget()->size());

    m_curController = nullptr;
    m_loginController = nullptr;
    m_userController = nullptr;
    m_gameHubController = nullptr;
    m_gameController = nullptr;
    m_formConnect = nullptr;

    // Init socketFactory
    m_socket = new Socket(this);
    connect(m_socket, &Socket::signal_connected, this, &Main_Controller::slot_socket_connected);
    connect(m_socket, &Socket::signal_disconnected, this, &Main_Controller::slot_socket_disconnected);
    SocketFactory::setSocket(m_socket);

    // Init formConnect
    this->slot_socket_disconnected();

    // Connect to host
    m_socket->connectToHost("127.0.0.1",10523);
}

void Main_Controller::slot_socket_connected()
{
    // Delete form_connect
    if(m_formConnect != nullptr){
        m_formConnect->deleteLater();
        m_formConnect = nullptr;
    }

    // Init login_controller and start it
    m_loginController = new Login_Controller(this);
    m_curController = m_loginController;
    connect(m_loginController, &Login_Controller::signal_moveToUser, this, &Main_Controller::slot_loginController_moveToUser);
    m_loginController->setFixedSize(this->size());
    m_loginController->setVisible(true);
}

void Main_Controller::slot_socket_disconnected()
{
    // Delete cur controller
    if(m_curController != nullptr){
        m_curController->deleteLater();
        m_curController = nullptr;

        m_loginController = nullptr;
        m_userController = nullptr;
        m_gameHubController = nullptr;
        m_gameController = nullptr;
    }

    // Init form_connect and show it
    m_formConnect = new Form_Connect(this);
    connect(m_formConnect, &Form_Connect::signal_connectToHost, m_socket, &Socket::connectToHost);
    m_formConnect->setFixedSize(this->size());
    m_formConnect->setVisible(true);
}

void Main_Controller::slot_loginController_moveToUser()
{
    // Delete login_controller
    if(m_loginController == nullptr)
        return;

    m_loginController->deleteLater();
    m_loginController = nullptr;

    // Init user_controller and start it
    m_userController = new User_Controller(this);
    m_curController = m_userController;
    connect(m_userController, &User_Controller::signal_moveToGameHub, this, &Main_Controller::slot_userController_moveToGameHub);
    m_userController->setFixedSize(this->size());
    m_userController->setVisible(true);
}

void Main_Controller::slot_userController_moveToGameHub()
{
    // Delete user_controller
    if(m_userController == nullptr)
        return;

    m_userController->deleteLater();
    m_userController = nullptr;

    // Init gameHub_controller and start it
    m_gameHubController = new GameHub_Controller(this);
    m_curController = m_gameHubController;
    connect(m_gameHubController, &GameHub_Controller::signal_moveToUser, this, &Main_Controller::slot_gameHubController_moveToUser);
    connect(m_gameHubController, &GameHub_Controller::signal_moveToGame, this, &Main_Controller::slot_gameHubController_moveToGame);
    m_gameHubController->setFixedSize(this->size());
    m_gameHubController->setVisible(true);
}

void Main_Controller::slot_gameHubController_moveToUser()
{
    // Delete gameHub_controller
    if(m_gameHubController == nullptr)
        return;

    m_gameHubController->deleteLater();
    m_gameHubController = nullptr;

    // Init user_controller and start it
    m_userController = new User_Controller(this);
    m_curController = m_userController;
    connect(m_userController, &User_Controller::signal_moveToGameHub, this, &Main_Controller::slot_userController_moveToGameHub);
    m_userController->setFixedSize(this->size());
    m_userController->setVisible(true);
}

void Main_Controller::slot_gameHubController_moveToGame(int gameID)
{
    // Delete gameHub_controller
    if(m_gameHubController == nullptr)
        return;

    m_gameHubController->deleteLater();
    m_gameHubController = nullptr;

    // Init game_controller and start it
    m_gameController = new Game_Controller(this,gameID);
    m_curController = m_gameController;
    m_gameController->setFixedSize(this->size());
    m_gameController->setVisible(true);
}
