#ifndef BANK_H
#define BANK_H

#include <QWidget>
#include <QPushButton>
#include "tile.h"
#include "resourcecard.h"
#include "developmentcard.h"
#include "map.h"
class Player;

class Bank : public QWidget
{
    Q_OBJECT
public:
    explicit Bank(Map* map,QWidget *parent = nullptr);
    void giveResCardToPlayer(tileType);
    developmentType giveDevCardToPlayer();
    tileType giveResCard();
    void getCardFromPlayer(tileType);
    void giveCardToWhom(Tile* tile,Player* player);
    void settlementBought();
    void roadBought();
    void cityBought();
    bool checkNumDev(int n);
    bool checkNumRes(int n);
//    void giveCardFirtTime(Player* p,Tile t);

private:
    Map* map;
    int numVictoryCard = 5;
    int numKnightCard = 14;
    int numRoadBuildingCard = 2;
    int numYearOfPlenty = 2;
    int numMonopoly = 2;

    int numFieldCard = 20;
    int numStoneCard = 20;
    int numClayCard = 20;
    int numPastureCard = 20;
    int numForestCard = 20;


    bool largestArmyCard;
    bool largestRoadCard;


signals:

};

#endif // BANK_H
