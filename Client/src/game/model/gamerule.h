#ifndef GAMERULE_H
#define GAMERULE_H

#include "carddata.h"

#include <QObject>

class GameRule : public QObject
{
    Q_OBJECT
public:
    explicit GameRule(QObject *parent);

public:
    void setPlayers(QVector<int> IDs);
    void setLandlord(int id);
    int getPlayerIndex(int id);

public:
    QVector<CardData> getSelectedCards();
    void playSelectedCards();
    void setLastCards(int id, const QVector<CardData> &cards);

public slots:
    void cardSelected(const CardData &card, bool selected);

signals:
    void signal_canPlayCard(bool ok);
    void signal_canPassPlayCard(bool ok);

private:
    QVector<int> m_IDs;
    QVector<CardData> m_myChosenCards;
    QVector<CardData> m_lastCards;
    int m_lastCardsOwner;
};

#endif // GAMERULE_H
