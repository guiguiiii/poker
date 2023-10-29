#include "carddata.h"

CardData::CardData()
{

}

CardData::CardData(const Rank &rank, const Suit &suit) : m_rank(rank),
    m_suit(suit)
{}

bool CardData::operator<(const CardData &cardData) const
{
    if(m_rank < cardData.rank())
        return true;
    else if(m_rank > cardData.rank())
        return false;
    else
        return m_suit < cardData.suit();
}

bool CardData::operator>(const CardData &cardData) const
{
    if(m_rank > cardData.rank())
        return true;
    else if(m_rank < cardData.rank())
        return false;
    else
        return m_suit > cardData.suit();
}

bool CardData::operator==(const CardData &cardData) const
{
    return m_rank == cardData.rank() and m_suit == cardData.suit();
}

Rank CardData::rank() const
{
    return m_rank;
}

void CardData::setRank(const Rank &newRank)
{
    m_rank = newRank;
}

Suit CardData::suit() const
{
    return m_suit;
}

void CardData::setSuit(const Suit &newSuit)
{
    m_suit = newSuit;
}
