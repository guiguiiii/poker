#include "cardrule.h"

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
    else if(CardRule::isAircraftA(cards) == true)
        cardsType = "AircraftA";
    else if(CardRule::isAircraftB(cards) == true)
        cardsType = "AircraftB";
    else if(CardRule::isAircraftC(cards) == true)
        cardsType = "AircraftC";

    return cardsType;
}

bool CardRule::isBigger(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    QString cardsAType = CardRule::getCardsType(cardsA);
    QString cardsBType = CardRule::getCardsType(cardsB);

    if(cardsAType == "" or cardsBType == "")
        return false;

    // 炸弹处理
    if(cardsAType == "Bomb" and cardsBType != "Bomb")
        return true;
    else if(cardsAType != "Bomb" and cardsBType == "Bomb")
        return false;

    // 不同类型返回
    if(cardsAType != cardsBType)
        return false;

    // 同类型比较
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
    else if(cardsAType == "AircraftA")
        return CardRule::isBigger_aircraftA(cardsA,cardsB);
    else if(cardsAType == "AircraftB")
        return CardRule::isBigger_aircraftB(cardsA,cardsB);
    else if(cardsAType == "AircraftC")
        return CardRule::isBigger_aircraftC(cardsA,cardsB);
    return false;
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
    if(cards.size() != 2 and cards.size() != 4)
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
    if(cards.size() != 6 and cards.size() != 8)
        return false;

    int pairNum = 0;
    int fourExists = false;
    QVector<int> countVec = CardRule::numCount(cards);
    for(int count: countVec){
        if(count == 4){
            fourExists = true;

            if(cards.size() == 6)
                return true;
        }else if(count == 2)
            pairNum++;
    }

    if(fourExists == true and (pairNum == 2 or pairNum == 0))
        return true;
    else
        return false;
}

bool CardRule::isStraight(const QVector<CardData> &cards)
{
    if(cards.size() < 5)
        return false;

    for(int i=0; i<cards.size() -1; i++){
        if(cards[i].rank() == Rank::two)
            return false;
        if(static_cast<Rank>(cards[i].rank()) +1 != static_cast<Rank>(cards[i+1].rank()))
            return false;
    }

    return true;
}

bool CardRule::isConsecutivePairs(const QVector<CardData> &cards)
{
    if(cards.size() %2 != 0 or cards.size() < 6)
        return false;

    for(int i=0; i<cards.size() -1; i+=2){
        if(cards[i].rank() != cards[i+1].rank())
            return false;
        if(i+2 < cards.size() and static_cast<Rank>(cards[i].rank()) +1 != static_cast<Rank>(cards[i+2].rank()))
            return false;
    }

    return true;
}

bool CardRule::isAircraftA(const QVector<CardData> &cards)
{
    if(cards.size() %3 != 0 or cards.size() < 6)
        return false;

    for(int i=0; i<cards.size() -2; i+=3){
        if(cards[i].rank() != cards[i+1].rank() or cards[i+1].rank() != cards[i+2].rank())
            return false;
        if(i+3 < cards.size() and static_cast<Rank>(cards[i].rank()) +1 != static_cast<Rank>(cards[i+3].rank()))
            return false;
    }

    return true;
}

bool CardRule::isAircraftB(const QVector<CardData> &cards)
{
    if(cards.size() %4 != 0 or cards.size() < 8)
        return false;

    int maxSize = 1;
    int tempSize = 1;
    QVector<int> countVec = CardRule::numCount(cards);
    for(int i=0; i<countVec.size() -1; i++){
        if(countVec[i] >= 3 and countVec[i+1] >= 3){
            tempSize++;
            maxSize = ( tempSize > maxSize ) ? tempSize : maxSize;
        }else
            tempSize = 1;
    }

    if(maxSize == cards.size() / 4)
        return true;
    return false;
}

bool CardRule::isAircraftC(const QVector<CardData> &cards)
{
    if(cards.size() %5 != 0 or cards.size() < 10)
        return false;

    int threeNum = 0;
    int pairNum = 0;
    QVector<int> countVec = CardRule::numCount(cards);
    for(int i=0; i<countVec.size(); i++){
        if(countVec[i] == 2)
            pairNum++;
        else if(countVec[i] == 4)
            pairNum += 2;
        else if(countVec[i] == 3)
            threeNum++;
    }

    if(threeNum == pairNum and cards.size() / 5 == threeNum)
        return true;
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

bool CardRule::isBigger_aircraftA(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return cardsA.last() > cardsB.last();
}

bool CardRule::isBigger_aircraftB(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    int airSize = cardsA.size() /4;

    int indexA = 0, indexB = 0;
    QVector<int> countVecA = CardRule::numCount(cardsA);
    for(int size = 1; indexA < countVecA.size() -1; indexA++){
        if(countVecA[indexA] >= 3 and countVecA[indexA+1] >= 3)
            size++;
        else
            size = 1;
        if(size == airSize)
            break;
    }

    QVector<int> countVecB = CardRule::numCount(cardsB);
    for(int size = 1; indexB < countVecB.size() -1; indexB++){
        if(countVecB[indexB] >= 3 and countVecB[indexB+1] >= 3)
            size++;
        else
            size = 1;
        if(size == airSize)
            break;
    }

    return indexA > indexB;
}

bool CardRule::isBigger_aircraftC(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB)
{
    return CardRule::isBigger_aircraftB(cardsA,cardsB);
}

QVector<int> CardRule::numCount(const QVector<CardData> &cards)
{
    QVector<int> countVec(13,0);
    for(const CardData &card: cards)
        countVec[int(card.rank())]++;
    return countVec;
}
