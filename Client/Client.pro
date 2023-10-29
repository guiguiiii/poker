QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/common/model/publicdata.cpp \
    src/common/view/widget_pfp.cpp \
    src/common/view/widget_confirm.cpp \
    src/common/view/widget_tips.cpp \
    src/common/pixtostr.cpp \
    src/game/game_controller.cpp \
    src/game/model/carddata.cpp \
    src/game/model/game_socket.cpp \
    src/game/model/gamerule.cpp \
    src/game/view/form_game.cpp \
    src/game/view/widget_cardbtn.cpp \
    src/game/view/widget_cardlbl.cpp \
    src/game/model/cardrule.cpp \
    src/gamehub/view/widget_playerinfo.cpp \
    src/gamehub/view/widget_loungeinfo.cpp \
    src/gamehub/view/form_lounge.cpp \
    src/gamehub/view/form_gamehub.cpp \
    src/gamehub/model/playerdata.cpp \
    src/gamehub/model/loungedata.cpp \
    src/gamehub/model/gamehub_socket.cpp \
    src/gamehub/gamehub_controller.cpp \
    src/user/view/widget_setpfp.cpp \
    src/user/view/form_settings.cpp \
    src/user/view/form_personal.cpp \
    src/user/view/form_start.cpp \
    src/user/model/userdata.cpp \
    src/user/model/user_socket.cpp \
    src/user/user_controller.cpp \
    src/login/view/form_signup.cpp \
    src/login/view/form_login.cpp \
    src/login/model/signupdata.cpp \
    src/login/model/logindata.cpp \
    src/login/model/login_socket.cpp \
    src/login/login_controller.cpp \
    src/main/view/form_connect.cpp \
    src/main/view/mainwindow.cpp \
    src/main/model/socketfactory.cpp \
    src/main/model/socket.cpp \
    src/main/main_controller.cpp \
    main.cpp

HEADERS += \
    src/common/model/publicdata.h \
    src/common/view/widget_pfp.h \
    src/common/view/widget_confirm.h \
    src/common/view/widget_tips.h \
    src/common/pixtostr.h \
    src/game/game_controller.h \
    src/game/model/carddata.h \
    src/game/model/game_socket.h \
    src/game/model/gamerule.h \
    src/game/view/form_game.h \
    src/game/view/widget_cardbtn.h \
    src/game/view/widget_cardlbl.h \
    src/game/model/cardrule.h \
    src/gamehub/view/widget_playerinfo.h \
    src/gamehub/view/widget_loungeinfo.h \
    src/gamehub/view/form_lounge.h \
    src/gamehub/view/form_gamehub.h \
    src/gamehub/model/playerdata.h \
    src/gamehub/model/loungedata.h \
    src/gamehub/model/gamehub_socket.h \
    src/gamehub/gamehub_controller.h \
    src/user/view/widget_setpfp.h \
    src/user/view/form_settings.h \
    src/user/view/form_personal.h \
    src/user/view/form_start.h \
    src/user/model/userdata.h \
    src/user/model/user_socket.h \
    src/user/user_controller.h \
    src/login/view/form_signup.h \
    src/login/view/form_login.h \
    src/login/model/signupdata.h \
    src/login/model/logindata.h \
    src/login/model/login_socket.h \
    src/login/login_controller.h \
    src/main/view/form_connect.h \
    src/main/view/mainwindow.h \
    src/main/model/socketfactory.h \
    src/main/model/socket.h \
    src/main/main_controller.h

FORMS += \
    src/common/view/widget_pfp.ui \
    src/common/view/widget_confirm.ui \
    src/common/view/widget_tips.ui \
    src/game/view/form_game.ui \
    src/game/view/widget_cardbtn.ui \
    src/game/view/widget_cardlbl.ui \
    src/gamehub/view/widget_playerinfo.ui \
    src/gamehub/view/widget_loungeinfo.ui \
    src/gamehub/view/form_lounge.ui \
    src/gamehub/view/form_gamehub.ui \
    src/user/view/widget_setpfp.ui \
    src/user/view/form_settings.ui \
    src/user/view/form_personal.ui \
    src/user/view/form_start.ui \
    src/login/view/form_signup.ui \
    src/login/view/form_login.ui \
    src/main/view/form_connect.ui \
    src/main/view/mainwindow.ui

RESOURCES += \
    resource.qrc

RC_FILE += \
    logo.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

