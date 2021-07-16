#ifndef LOCATION_H
#define LOCATION_H
#include <QVector>

enum locationType {edge, vertice, tile};

class Location
{
public:
    Location(int _x, int _y, locationType);
    Location();
    QVector<Location> getADjacent();
    int getX();
    int getY();
    void findAdjacent();
    int distance(Location);
private:
    int x;
    int y;
    locationType type;

};

#endif // LOCATION_H
