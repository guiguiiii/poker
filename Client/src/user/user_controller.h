#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "model/user_socket.h"
#include "view/form_start.h"
#include "view/form_personal.h"
#include "view/form_settings.h"

#include <QWidget>

class User_Controller : public QWidget
{
    Q_OBJECT
public:
    explicit User_Controller(QWidget *parent);

signals:
    // Move to GameHub_Controller
    void signal_moveToGameHub();

private:
    // TcpSocket pointer
    const User_Socket *m_userSocket;

private:
    // View pointers
    Form_Start *m_formStart;
    Form_Personal *m_formPersonal;
    Form_Settings *m_formSettings;

private slots:
    // Process signals from socket
    void rcv_getPersonal(const UserData &userData);
    void rcv_setPersonal(int status);

private slots:
    // Process signals from form_start
    void slot_formStart_moveToGameHub();
    void slot_formStart_moveToPersonal();
    void slot_formStart_moveToSettings();

    // Process signals from form_personal
    void slot_formPersonal_moveToStart();

    // Process signals from form_settings
/*    void slot_formSettings_setSettings();    */
    void slot_formSettings_moveToStart();
};

#endif // USER_CONTROLLER_H
