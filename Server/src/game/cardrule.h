#ifndef CARDRULE_H
#define CARDRULE_H

#include "carddata.h"

#include <QVector>

class CardRule
{
public:
    CardRule();
    static QString getCardsType(const QVector<CardData> &cards);
    static bool isBigger(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);

private:
    static bool isSingle(const QVector<CardData> &cards);
    static bool isPair(const QVector<CardData> &cards);
    static bool isBomb(const QVector<CardData> &cards);
    static bool isThreeOfAKind(const QVector<CardData> &cards);
    static bool isThreeWithOne(const QVector<CardData> &cards);
    static bool isThreeWithPair(const QVector<CardData> &cards);
    static bool isFourWithTwo(const QVector<CardData> &cards);
    static bool isStraight(const QVector<CardData> &cards);
    static bool isConsecutivePairs(const QVector<CardData> &cards);
    static bool isAircraft(const QVector<CardData> &cards);

private:
    // * 默认两组牌都通过了牌型判断 *
    static bool isBigger_single(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_pair(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_bomb(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_threeOfAKind(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_threeWithOne(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_threeWithPair(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_fourWithTwo(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_straight(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_consecutivePairs(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
    static bool isBigger_aircraft(const QVector<CardData> &cardsA, const QVector<CardData> &cardsB);
};

#endif // CARDRULE_H
