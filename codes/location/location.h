#ifndef LOCATION_H
#define LOCATION_H
#include <QVector>
enum location {edge, vertice, tile};
class Location
{
public:
    Location(int x, int y, location);
    Location();
    QVector<Location> getADjacent();
    void findAdjacent();
    int distance(Location);
private:
    int x;
    int y;
    location locationType;

};

#endif // LOCATION_H
