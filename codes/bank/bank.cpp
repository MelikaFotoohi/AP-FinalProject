#include "bank.h"

Bank::Bank(QWidget *parent) : QWidget(parent)
{

}

void Bank::settlementBought(){
    numClayCard++;
    numFieldCard++;
    numPastureCard++;
    numForestCard++;
}
void Bank::roadBought(){
    numClayCard++;
    numStoneCard++;
}
void Bank::cityBought(){
    numFieldCard += 2;
    numStoneCard += 3;
}
/* reduce num card */
void Bank::giveResCardToPlayer(tileType rt){
    if (rt==field){
        numFieldCard--;
    }
    else if(rt==stone){
        numStoneCard--;
    }
    else if(rt==clay){
        numClayCard--;
    }
    else if(rt==pasture){
        numPastureCard--;
    }
    else if(rt==forest){
        numForestCard--;
    }
}

void Bank::giveDevCardToPlayer(developmentType dt){
    if(dt==victoryPoint){
        numVictoryCard--;
    }
    else if(dt==Knight){
        numKnightCard--;
    }
    else if(dt==roadBuilding){
        numRoadBuildingCard--;
    }
    else if(dt==yearOfPlenty){
        numYearOfPlenty--;
    }
    else if(dt==monopoly){
        numMonopoy--;
    }

}
/* increase num card */
void Bank::getCardFromPlayer(resourceType rt){
    if (rt==fieldCard){
        numFieldCard++;
    }
    else if(rt==stoneCard){
        numStoneCard++;
    }
    else if(rt==clayCard){
        numClayCard++;
    }
    else if(rt==pastureCard){
        numPastureCard++;
    }
    else if(rt==forestCard){
        numForestCard++;
    }
}

/* checkinh players */
void Bank::giveCardToWhom(Tile* tile,Player* player){
    int n = player->isAdjacent(tile);
    for(int i =0; i<n;i++){
        qDebug() << "bankkk  whoom";
        player->getResourceCard(tile->getType());
        giveResCardToPlayer(tile->getType());

    }
}
