#ifndef DEVELOPMENTCARD_H
#define DEVELOPMENTCARD_H
#include "card.h"

enum developmentType {victoryPointCard, KnightCard, roadBuildingCard, yearOfPlentyCard, monopolyCard  };

class DevelopmentCard : public Card
{
public:
    DevelopmentCard(developmentType type);
    void draw();
    void checkMaxCount();

private:
    QString name;
    developmentType type;
};

#endif // DEVELOPMENTCARD_H
