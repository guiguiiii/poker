#include "game.h"

#include "src/common/public_file.h"

Game::Game(QObject *parent)
    : QObject{parent}
{

}

int Game::newGame(const QVector<int> &playerIDs)
{
    // 获取一个不存在的游戏号
    for(int gameID=1; gameID<INT_MAX; gameID++){
        if(m_pokers.contains(gameID))
            continue;

        // 创建游戏
        Poker *poker = new Poker(this,playerIDs);
        connect(poker, &Poker::signal_checkBecomeLandlord, this, &Game::signal_checkBecomeLandlord);
        connect(poker, &Poker::signal_restart, this, &Game::signal_restart);
        connect(poker, &Poker::signal_showLandlord, this, &Game::signal_showLandlord);
        connect(poker, &Poker::signal_showLandlordCards, this, &Game::signal_showLandlordCards);
        connect(poker, &Poker::signal_showCards, this, &Game::signal_showCards);
        connect(poker, &Poker::signal_waitForPlayCard, this, &Game::signal_waitForPlayCard);

        m_pokers.insert(gameID,poker);
        return gameID;
    }

    return -1;
}

QVector<PublicData> Game::getPlayers(int id, int gameID)
{
    QVector<int> playerIDs = m_pokers.value(gameID)->getPlayerIDs(id);
    QVector<PublicData> players;
    for(const int &id: playerIDs)
        players.push_back(Public_File::publicData(id));
    return players;
}

QVector<CardData> Game::getCards(int id, int gameID)
{
    return m_pokers.value(gameID)->getCards(id);
}

void Game::becomeLandlord(int id, int gameID, bool become)
{
    m_pokers.value(gameID)->becomeLandlord(id,become);
}

void Game::playCards(int id, int gameID, const QVector<CardData> &cards)
{
    m_pokers.value(gameID)->playCards(id,cards);
}
