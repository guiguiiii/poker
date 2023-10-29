#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "src/login/login_controller.h"
#include "src/user/user_controller.h"
#include "src/gamehub/gamehub_controller.h"
#include "src/game/game_controller.h"
#include "view/form_connect.h"

#include <QWidget>

class Main_Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Controller(QWidget *parent);

private:
    Socket *m_socket;

private:
    QWidget *m_curController;
    Login_Controller *m_loginController;
    User_Controller *m_userController;
    GameHub_Controller *m_gameHubController;
    Game_Controller *m_gameController;

private:
    Form_Connect *m_formConnect;

private slots:
    void slot_socket_connected();
    void slot_socket_disconnected();

private slots:
    void slot_loginController_moveToUser();
    void slot_userController_moveToGameHub();
    void slot_gameHubController_moveToUser();
    void slot_gameHubController_moveToGame(int gameID);
};

#endif // MAIN_CONTROLLER_H
