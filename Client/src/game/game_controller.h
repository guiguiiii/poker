#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "model/game_socket.h"
#include "model/gamerule.h"
#include "view/form_game.h"

#include <QWidget>

class Game_Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Game_Controller(QWidget *parent, int gameID);

private:
    // TcpSocket pointer
    const Game_Socket *m_gameSocket;

    // Model pointers
    int m_gameID;
    GameRule *m_gameRule;

private:
    // View pointers
    Form_Game *m_formGame;

private slots:
    // Process signals from socket
    void rcv_getPlayers(const QVector<PublicData> &players);
    void rcv_getCards(const QVector<CardData> &cards);
    void rcv_checkBecomeLandlord(int id, int time);
    void rcv_restart();
    void rcv_showLandlord(int id);
    void rcv_showLandlordCards(const QVector<CardData> &cards);
    void rcv_showCards(int id, const QVector<CardData> &cards);
    void rcv_waitForPlayCard(int id, int time);

private slots:
    // Process signals from gameRule
    void slot_gameRule_canPlayCard(bool ok);
    void slot_gameRule_canPassPlayCard(bool ok);

private slots:
    // Process signals from form_game
    void slot_formGame_becomeLandlord(bool become);
    void slot_formGame_playCards();
    void slot_formGame_pass();
};

#endif // GAME_CONTROLLER_H
