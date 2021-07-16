#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QVector>
#include "resourcecard.h"
#include "developmentcard.h"
#include "building.h"
#include "trade.h"
#include "map.h"
class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);
    //Player();
    void draw();
    int update();
  //  map<tileNum, tileType> buildingResources;
    QVector<ResourceCard> giveCardToBank();
    void changeRobber();
private:
    QVector<ResourceCard> resource;
    QVector<DevelopmentCard> development;
    QVector<buildingType> buildings;
 //   Trade trade;
    int victoryPoint;
    int PlayerID;
    int sumOfDices;
signals:

};

#endif // PLAYER_H
