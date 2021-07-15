#ifndef RESOURCECARD_H
#define RESOURCECARD_H
#include "card.h"

enum resourceCard { WoodCard, wheatCard, sheepCrad, brickCard, stoneCard };

class ResourceCard : public Card
{
public:
    ResourceCard(resourceCard resourceType);
    void draw();
    void checkMaxCount();
private:
    QString name;
    resourceCard resourceType;
};

#endif // RESOURCECARD_H
