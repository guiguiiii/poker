#include "poker.h"

#include <QTimer>
#include <QRandomGenerator>

Poker::Poker(QObject *parent, const QVector<int> &playerIDs)
    : QObject{parent}
{
    // 各阶段倒计时
    m_time_landlord = 15;
    m_time_playCard = 20;

    // 初始化
    m_playerIDs = playerIDs;
    m_playersCards.resize(3);

    // 发牌
    this->dealCard();
}

QVector<int> Poker::getPlayerIDs(int id)
{
    /* 返回房间内所有玩家的ID，
       把发送请求的玩家放在返回数组第一位，同时保持三人顺序不变。 */
    QVector<int> playerIDs;
    for(int i=0; playerIDs.size() < 3; i++){
        i = ( i == 3 ) ? 0 : i;
        if(m_playerIDs[i] == id or playerIDs.empty() == false)
            playerIDs.push_back(m_playerIDs[i]);
    }
    return playerIDs;
}

QVector<CardData> Poker::getCards(int id)
{
    // 若三人都获取手牌，游戏开始
    static int s_readyNum = 0;
    s_readyNum++;
    s_readyNum = ( s_readyNum == 3 ) ? 0 : s_readyNum;

    if(s_readyNum == 0)
        this->gameStart();

    // 返回手牌
    for(int i=0; i<3; i++)
        if(m_playerIDs[i] == id)
            return m_playersCards[i];
    return QVector<CardData>();
}

void Poker::becomeLandlord(int id, bool become)
{
    if(id != m_playerIDs[m_curIndex])
        return;

    // 若玩家选择不成为地主
    if(become == false){
        // Change m_curIndex
        m_curIndex++;
        m_curIndex = (m_curIndex == 3) ? 0 : m_curIndex;

        // 若当前玩家不选择成为地主，则轮到下一位
        if(m_curIndex != m_firstIndex){
            int playerID = m_playerIDs[m_curIndex];
            for(int &id: m_playerIDs)
                emit signal_checkBecomeLandlord(id,playerID,m_time_landlord);

        // 若三人无人选择成为地主，则重新开始
        }else{
            // 重新发牌
            this->dealCard();
            // 发送重新开始信息
            for(int &id: m_playerIDs)
                emit signal_restart(id);
        }

    // 若玩家选择成为地主
    }else{
        // 地主牌加入手牌
        for(int i=0; i<3; i++)
            if(m_playerIDs[i] == id){
                m_playersCards[i].append(m_landlordCards);
                std::sort(m_playersCards[i].begin(), m_playersCards[i].end());
                break;
            }

        // 发送玩家成为地主的信息
        for(int &playerID: m_playerIDs){
            emit signal_showLandlord(playerID,id);
            emit signal_showLandlordCards(playerID,m_landlordCards);
        }

        // 倒计时后发送等待玩家出牌信息
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=](){

            // 通过负一轮出空牌来开启出牌循环
            m_curIndex--;
            m_curIndex = ( m_curIndex == -1 ) ? 2 : m_curIndex;
            this->playCards(m_playerIDs[m_curIndex],QVector<CardData>());

            timer->deleteLater();
        });
        timer->start(3000);
    }
}

void Poker::playCards(int id, const QVector<CardData> &cards)
{
    /*temp*/
    /* （待完成）
       用户检测，手牌检测，牌型检测
       静态变量计时器 */

    // 移除手牌
    for(const CardData &cardData: cards)
        m_playersCards[m_curIndex].removeOne(cardData);

    // 当前出牌玩家下标递增
    m_curIndex++;
    m_curIndex = (m_curIndex == 3) ? 0 : m_curIndex;

    // 发送信息
    for(int i=0; i<3; i++){
        emit signal_showCards(m_playerIDs[i],id,cards);
        emit signal_waitForPlayCard(m_playerIDs[i],m_playerIDs[m_curIndex],m_time_playCard);
    }
}

void Poker::dealCard()
{
    // 清空数组
    m_landlordCards.resize(0);
    for(int i=0; i<3; i++)
        m_playersCards[i].resize(0);

    // 初始化 54 张牌
    QVector<CardData> cards;
    for(int i=0; i<13; i++)
        for(int j=1; j<5; j++){
            CardData card;
            card.setRank(static_cast<Rank>(i));
            card.setSuit(static_cast<Suit>(j));
            cards.push_back(card);
        }
    CardData blackJoker;
    blackJoker.setRank(Rank::BlackJoker);
    blackJoker.setSuit(Suit::null);
    cards.push_back(blackJoker);
    CardData redJoker;
    redJoker.setRank(Rank::RedJoker);
    redJoker.setSuit(Suit::null);
    cards.push_back(redJoker);

    // 洗牌
    for(int i=53; i>0; i--){
        int random = QRandomGenerator::global()->bounded(0,54);
        cards.swapItemsAt(i,random);
    }

    // 发牌
    for(int i=0; i<m_playersCards.size(); i++){
        QVector<CardData> playerCards = cards.mid(i*17,17);
        std::sort(playerCards.begin(), playerCards.end());
        m_playersCards[i].append(playerCards);
    }

    // 三张地主牌
    m_landlordCards.append(cards.mid(51,3));
    std::sort(m_landlordCards.begin(), m_landlordCards.end());
}

void Poker::gameStart()
{
    // 随机选择一位玩家。初始化成员变量
    int random = QRandomGenerator::global()->bounded(0,2);
    m_curIndex = random;
    m_firstIndex = random;

    // 发送信息，询问是否愿意成为地主。开启地主选择循环
    int playerID = m_playerIDs[random];
    for(int &id: m_playerIDs)
        emit signal_checkBecomeLandlord(id,playerID,m_time_landlord);
}
