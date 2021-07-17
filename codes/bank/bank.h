#ifndef BANK_H
#define BANK_H

#include <QWidget>
#include <QPushButton>
#include "tile.h"
#include "player.h"
#include "resourcecard.h"
#include "developmentcard.h"

class Bank : public QWidget
{
    Q_OBJECT
public:
    explicit Bank(QWidget *parent = nullptr);
    void giveResCardToPlayer(tileType);
    void giveDevCardToPlayer(developmentType);
    void getCardFromPlayer(resourceType);
    void giveCardToWhom(Tile* tile,Player* player);
    void settlementBought();
    void roadBought();
    void cityBought();


private:
    int numVictoryCard;
    int numKnightCard;
    int numRoadBuildingCard;
    int numYearOfPlenty;
    int numMonopoy;

    int numFieldCard;
    int numStoneCard;
    int numClayCard;
    int numPastureCard;
    int numForestCard;


    bool largestArmyCard;
    bool largestRoadCard;


signals:

};

#endif // BANK_H

