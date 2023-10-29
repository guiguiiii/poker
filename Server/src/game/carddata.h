#ifndef CARDDATA_H
#define CARDDATA_H

enum Rank{
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    Jack,
    Queen,
    King,
    Ace,
    two,
    BlackJoker,
    RedJoker
};

enum Suit{
    null,
    diamond,
    club,
    heart,
    spade
};

class CardData
{
public:
    CardData();
    CardData(const Rank &rank, const Suit &suit);
    bool operator<(const CardData &cardData) const;
    bool operator>(const CardData &cardData) const;
    bool operator==(const CardData &cardData) const;

    Rank rank() const;
    void setRank(const Rank &newRank);
    Suit suit() const;
    void setSuit(const Suit &newSuit);

private:
    Rank m_rank;
    Suit m_suit;
};

#endif // CARDDATA_H
