#include "cardrule.h"

CardRule::CardRule()
{

}

QString CardRule::getCardsType(const QVector<CardData> &cards)
{
    QString cardsType = "";
    if(CardRule::isSingle(cards) == true)
        cardsType = "Single";
    else if(CardRule::isPair(cards) == true)
        cardsType = "Pair";
    else if(CardRule::isBomb(cards) == true)
        cardsType = "Bomb";
    else if(CardRule::isThreeOfAKind(cards) == true)
        cardsType = "ThreeOfAKind";
    else if(CardRule::isThreeWithOne(cards) == true)
        cardsType = "ThreeWithOne";
    else if(CardRule::isThreeWithPair(cards) == true)
        cardsType = "ThreeWithPair";
    else if(CardRule::isFourWithTwo(cards) == true)
        cardsType = "FourWithTwo";
    else if(CardRule::isStraight(cards) == true)
        cardsType = "Straight";
    else if(CardRule::isConsecutivePairs(cards) == true)
        cardsType = "ConsecutivePairs";
    else if(CardRule::isAircraft(cards) == true)
        cardsType = "Aircraft";

    return cardsType;
}

bool CardRule::isBigger(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    QString cardsAType = CardRule::getCardsType(cardsA);
    QString cardsBType = CardRule::getCardsType(cardsB);

    if(cardsAType != cardsBType or cardsAType == "" or cardsBType == "")
        return false;
    else{
        if(cardsAType == "Single")
            return CardRule::isBigger_single(cardsA,cardsB);
        else if(cardsAType == "Pair")
            return CardRule::isBigger_pair(cardsA,cardsB);
        else if(cardsAType == "Bomb")
            return CardRule::isBigger_bomb(cardsA,cardsB);
        else if(cardsAType == "ThreeOfAKind")
            return CardRule::isBigger_threeOfAKind(cardsA,cardsB);
        else if(cardsAType == "ThreeWithOne")
            return CardRule::isBigger_threeWithOne(cardsA,cardsB);
        else if(cardsAType == "ThreeWithPair")
            return CardRule::isBigger_threeWithPair(cardsA,cardsB);
        else if(cardsAType == "FourWithTwo")
            return CardRule::isBigger_fourWithTwo(cardsA,cardsB);
        else if(cardsAType == "Straight")
            return CardRule::isBigger_straight(cardsA,cardsB);
        else if(cardsAType == "ConsecutivePairs")
            return CardRule::isBigger_consecutivePairs(cardsA,cardsB);
        else if(cardsAType == "Aircraft")
            return CardRule::isBigger_aircraft(cardsA,cardsB);
        else
            return false;
    }
}

bool CardRule::isSingle(const QVector<CardData> &cards)
{
    return cards.size() == 1;
}

bool CardRule::isPair(const QVector<CardData> &cards)
{
    return cards.size() == 2 and cards.at(0).rank() == cards.at(1).rank();
}

bool CardRule::isBomb(const QVector<CardData> &cards)
{
    if(cards.size() != 2 or cards.size() != 4)
        return false;

    if(cards[0].rank() == Rank::BlackJoker and cards[1].rank() == Rank::RedJoker)
        return true;

    if(cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[2].rank() == cards[3].rank())
        return true;

    return false;
}

bool CardRule::isThreeOfAKind(const QVector<CardData> &cards)
{
    return cards.size() == 3 and cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank();
}

bool CardRule::isThreeWithOne(const QVector<CardData> &cards)
{
    if(cards.size() != 4)
        return false;

    if(cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[2].rank() != cards[3].rank())
        return true;

    if(cards[0].rank() != cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[2].rank() == cards[3].rank())
        return true;

    return false;
}

bool CardRule::isThreeWithPair(const QVector<CardData> &cards)
{
    if(cards.size() != 5)
        return false;

    if(cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[3].rank() == cards[4].rank())
        return true;

    if(cards[0].rank() == cards[1].rank() and cards[2].rank() == cards[3].rank() and cards[3].rank() == cards[4].rank())
        return true;

    return false;
}

bool CardRule::isFourWithTwo(const QVector<CardData> &cards)
{
    if(cards.size() != 6 or cards.size() != 8)
        return false;

    if(cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[2].rank() == cards[3].rank())
        return true;

    if(cards[0].rank() == cards[1].rank() and cards[1].rank() == cards[2].rank() and cards[2].rank() == cards[3].rank()
        and cards[4].rank() == cards[5].rank() and cards[6].rank() == cards[7].rank())
        return true;

    return false;
}

bool CardRule::isStraight(const QVector<CardData> &cards)
{
    if(cards.size() < 5)
        return false;

    for(int i=0; i<cards.size() -1; i++){
        if(static_cast<Rank>(cards[i].rank()) +1 != static_cast<Rank>(cards[i+1].rank()))
            return false;
        if(cards[i].rank() == Rank::BlackJoker or cards[i].rank() == Rank::two)
            return false;
    }

    return true;
}

bool CardRule::isConsecutivePairs(const QVector<CardData> &cards)
{
    if(cards.size() %2 != 0 or cards.size() < 6)
        return false;

    for(int i=0; i<cards.size() -2; i+=2){
        if(cards[i].rank() != cards[i+1].rank()
            or static_cast<Rank>(cards[i].rank()) +1 != static_cast<Rank>(cards[i+2].rank()))
            return false;
    }

    return true;
}

bool CardRule::isAircraft(const QVector<CardData> &cards)
{
    /*
        temp
     */
    return false;

//    if(cards.size() < 6)
//        return false;

//    // 记录各数字的牌数
//    QMap<Rank,int> rankCounts;
//    for(const Card &card: cards)
//        rankCounts[card.rank()]++;

//    // 取牌数大于3的数字加入数组
//    QVector<Rank> triple;
//    for(auto it = rankCounts.begin(); it != rankCounts.end(); it++)
//        if(it.value() >= 3)
//            triple.push_back(it.key());

//    if(triple.size() < 3)
//        return false;

//    // 获取最大的连续的3张相同的数量
//    int maxNum = 0;
//    for(int i=0; i<triple.size() -1; i++){
//        if(static_cast<Rank>(triple[i]) +1 == static_cast<Rank>(triple[i+1])){

//        }
//    }

    return false;
}

bool CardRule::isBigger_single(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA[0] > cardsB[0];
}

bool CardRule::isBigger_pair(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA[1] > cardsB[1];
}

bool CardRule::isBigger_bomb(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    if(cardsA.size() == 2)
        return true;
    else if(cardsB.size() == 2)
        return false;
    else
        return cardsA[0] > cardsB[0];
}

bool CardRule::isBigger_threeOfAKind(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA[0] > cardsB[0];
}

bool CardRule::isBigger_threeWithOne(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return (( cardsA[0] == cardsA[1] ) ? cardsA[0] : cardsA[1] ) > (( cardsB[0] == cardsB[1] ) ? cardsB[0] : cardsB[1]);
}

bool CardRule::isBigger_threeWithPair(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return (( cardsA[1] == cardsA[2] ) ? cardsA[1] : cardsA[2] ) > (( cardsB[1] == cardsB[2] ) ? cardsB[1] : cardsB[2]);
}

bool CardRule::isBigger_fourWithTwo(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA[2] > cardsB[2];
}

bool CardRule::isBigger_straight(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA.last() > cardsB.last();
}

bool CardRule::isBigger_consecutivePairs(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA.last() > cardsB.last();
}

bool CardRule::isBigger_aircraft(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    /*
        temp
     */
    return false;
}
