QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/common/publicdata.cpp \
    src/common/pixtostr.cpp \
    src/common/pfp.cpp \
    src/common/public_file.cpp \
    src/game/carddata.cpp \
    src/game/cardrule.cpp \
    src/game/game.cpp \
    src/game/game_server.cpp \
    src/game/poker.cpp \
    src/gamehub/playerdata.cpp \
    src/gamehub/loungedata.cpp \
    src/gamehub/lounge.cpp \
    src/gamehub/gamehub.cpp \
    src/gamehub/gamehub_server.cpp \
    src/user/userdata.cpp \
    src/user/user_file.cpp \
    src/user/user_server.cpp \
    src/login/logindata.cpp \
    src/login/signupdata.cpp \
    src/login/login_file.cpp \
    src/login/login_server.cpp \
    src/main/view/mainwindow.cpp \
    src/main/server.cpp \
    src/main/tcpserver.cpp \
    src/main/controller.cpp \
    main.cpp \

HEADERS += \
    src/common/publicdata.h \
    src/common/pixtostr.h \
    src/common/pfp.h \
    src/common/public_file.h \
    src/game/carddata.h \
    src/game/cardrule.h \
    src/game/game.h \
    src/game/game_server.h \
    src/game/poker.h \
    src/gamehub/playerdata.h \
    src/gamehub/loungedata.h \
    src/gamehub/lounge.h \
    src/gamehub/gamehub.h \
    src/gamehub/gamehub_server.h \
    src/user/userdata.h \
    src/user/user_file.h \
    src/user/user_server.h \
    src/login/logindata.h \
    src/login/signupdata.h \
    src/login/login_file.h \
    src/login/login_server.h \
    src/main/view/mainwindow.h \
    src/main/server.h \
    src/main/tcpserver.h \
    src/main/controller.h \

FORMS += \
    src/main/view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
