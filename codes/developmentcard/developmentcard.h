#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H
#include "card.h"

enum developmentCard {victoryPointCard, KnightCard, roadBuildingCard, yearOfPlentyCard, monopolyCard  };

class DevelopmentCard : public Card
{
public:
    DevelopmentCard(developmentCard developmentType);
    void draw();
    void checkMaxCount();

private:
    QString name;
    developmentCard developmentType;
};

#endif // DEVELOPMENTCARD_H
