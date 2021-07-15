#ifndef SPECIALCARD_H
#define SPECIALCARD_H

#include "card.h"

enum specialCard {longestRoadCard, lrgerstArmyCard };

class SpecialCard :  public Card
{
public:
    SpecialCard(specialCard specialType);
    void compareRoads();
    void draw();
    void checkMaxCount();

private:
    int lingestRoad;
    QString name;
    specialCard specialType;
};

#endif // SPECIALCARD_H
