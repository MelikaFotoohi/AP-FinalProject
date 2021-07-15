#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QVector>
#include "tile.h"

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    tileType TileType(int n);
    ~Map();

private:
    QVector<Tile*> tiles;
    Ui::Map *ui;
};

#endif // MAP_H
