#include "gamerule.h"

#include "cardrule.h"

GameRule::GameRule(QObject *parent)
    : QObject{parent}
{

}

void GameRule::setPlayers(QVector<int> IDs)
{
    m_IDs = IDs;
}

void GameRule::setLandlord(int id)
{
    m_lastCardsOwner = id;
}

int GameRule::getPlayerIndex(int id)
{
    for(int i=0; i<m_IDs.size(); i++)
        if(m_IDs[i] == id)
            return i;
    return 0;
}

QVector<CardData> GameRule::getSelectedCards()
{
    return m_myChosenCards;
}

void GameRule::playSelectedCards()
{
    m_myChosenCards.resize(0);
}

void GameRule::setLastCards(int id, const QVector<CardData> &cards)
{
    // 更新
    if(cards.size() != 0){
        m_lastCards = cards;
        m_lastCardsOwner = id;
    }

    // 若轮到我的回合，初始设置出牌按钮为不可用状态。
    int nextPlayer = this->getPlayerIndex(id) + 1;
    nextPlayer = ( nextPlayer == 3 ) ? 0 : nextPlayer;
    if(nextPlayer == 0){
        emit signal_canPlayCard(false);

        // 若上一个出牌者是自身，则设置跳过按钮为不可用状态。（即另外两人都跳过，我随意出牌，且不可跳过）
        if(m_lastCardsOwner == m_IDs[0])
            emit signal_canPassPlayCard(false);
        else
            emit signal_canPassPlayCard(true);
    }
}

void GameRule::cardSelected(const CardData &cardData, bool choose)
{
    // 更新 'm_myChosenCards' 数组，并排序
    if(choose == false)
        m_myChosenCards.removeOne(cardData);
    else{
        m_myChosenCards.push_back(cardData);
        std::sort(m_myChosenCards.begin(),m_myChosenCards.end());
    }

    /*  若我的选中的若干牌比上一次被打出的牌大，则设置出牌按钮为可用状态。
        若上次的出牌人是自身（即另外两人都跳过，我随意出牌），则选中的若干牌为若干牌型的其中一种，即可出牌。  */
    if(CardRule::isBigger(m_myChosenCards,m_lastCards) == true)
        emit signal_canPlayCard(true);
    else if(CardRule::getCardsType(m_myChosenCards) != "" and m_lastCardsOwner == m_IDs[0])
        emit signal_canPlayCard(true);
    else
        emit signal_canPlayCard(false);
}
