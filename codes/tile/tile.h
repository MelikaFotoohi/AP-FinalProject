#ifndef TILE_H
#define TILE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "resourcecard.h"
#include "location.h"

enum tileType { field, stone, clay, pasture, forest, desert};

class Tile : public QWidget
{
    Q_OBJECT
public:
    Tile(tileType, int, QLabel*);
    ResourceCard getResource();
    QLabel* getLocation();
    tileType getType();
    int getToken();
    void changeRobber(bool);
    bool checkRobber();

private:
    QLabel* location;
    ResourceCard resource();
    int numberToken;
    tileType type;
    bool robberIsHere = false;

signals:

};

#endif // TILE_H
