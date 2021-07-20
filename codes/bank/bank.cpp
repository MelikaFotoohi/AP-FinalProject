#include "bank.h"
#include "player.h"
Bank::Bank(Map* _map,QWidget *parent) : QWidget(parent)
{
    map = _map;
}

/* get cards for settlement */
void Bank::settlementBought(){
    numClayCard++;
    numFieldCard++;
    numPastureCard++;
    numForestCard++;
}

/* get cards for road */
void Bank::roadBought(){
    numClayCard++;
    numStoneCard++;
}

/* get cards for city */
void Bank::cityBought(){
    numFieldCard += 2;
    numStoneCard += 3;
}

/* give card to player (reduce num card) */
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

/* check development card for random*/
bool Bank::checkNumDev(int n){
    if(n%2==0 && numKnightCard < 1)
        return true;
    if((n==1 || n==3 || n==5) && numVictoryCard < 1)
        return true;
    if(n==7 && numRoadBuildingCard < 1)
        return true;
    if(n==9 && numYearOfPlenty < 1)
        return true;
    if(n==11 && numMonopoly < 1)
        return true;
    return false;
}

developmentType Bank::giveDevCardToPlayer(){
    int n = rand() % 12;
    while(checkNumDev(n)){
        n = rand()%5;
    }
    if((n==1 || n==3 || n==5)){
        numVictoryCard--;
        return victoryPoint;
    }
    else if(n%2==0){
        numKnightCard--;
        return Knight;
    }
    else if(n==7){
        numRoadBuildingCard--;
        return roadBuilding;
    }
    else if(n==9){
        numYearOfPlenty--;
        return yearOfPlenty;
    }
    else if(n==11){
        numMonopoly--;
        return monopoly;
    }

}

/* check resource card for random*/
bool Bank::checkNumRes(int n){
    if(n==0 && numFieldCard < 1)
        return true;
    if(n==1 && numStoneCard < 1)
        return true;
    if(n==2 && numClayCard < 1)
        return true;
    if(n==3 && numPastureCard < 1)
        return true;
    if(n==4 && numForestCard < 1)
        return true;
    return false;
}

/* give resource card randomly*/
tileType Bank::giveResCard(){
    int n = rand() % 5;
    while(checkNumRes(n)){
        n = rand()%5;
    }
    if (n==0){
        numFieldCard--;
        return field;
    }
    else if(n==1){
        numStoneCard--;
        return stone;
    }
    else if(n==2){
        numClayCard--;
        return clay;
    }
    else if(n==3){
        numPastureCard--;
        return pasture;
    }
    else if(n==4){
        numForestCard--;
        return forest;
    }
}

/* increase num card */
void Bank::getCardFromPlayer(tileType rt){
    if (rt==field){
        numFieldCard++;
    }
    else if(rt==stone){
        numStoneCard++;
    }
    else if(rt==clay){
        numClayCard++;
    }
    else if(rt==pasture){
        numPastureCard++;
    }
    else if(rt==forest){
        numForestCard++;
    }
}

/* checkinh players */
void Bank::giveCardToWhom(Tile* tile,Player* player){
    int n = player->isAdjacent(tile);
    for(int i =0; i<n;i++){
        player->getResourceCard(tile->getType());
        giveResCardToPlayer(tile->getType());
    }
}
