#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "tile.h"
#include "robber.h"

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    tileType TileType(int n);
    QVector<tileType> getAdjacent(QPushButton* p);
    ~Map();

private:
    QVector<Tile*> tiles;
    QVector<QLabel*> labels;
    QVector<QPushButton*> vertexs;
    QVector<QPushButton*> edges;
    Robber robber();
    Ui::Map *ui;
};

#endif // MAP_H
