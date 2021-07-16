#ifndef TILE_H
#define TILE_H

#include <QWidget>
#include "resourcecard.h"
#include "location.h"
enum tileType { field, stone, clay, pasture, forest, desert};
class Tile : public QWidget
{
    Q_OBJECT
public:
    Tile(tileType, int, Location*);
    ResourceCard getResource();
    Location* getLocation();
    tileType getType();
    void getRobber();
    bool checkRobber();

private:
    Location* location;
    ResourceCard resource();
    int numberToken;
    tileType type;
    bool robberIsHere = false;

signals:

};

#endif // TILE_H
