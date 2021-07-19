#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPair>
#include <QSignalMapper>

#include "tile.h"
#include "robber.h"

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    Ui::Map *ui;
    explicit Map(QWidget *parent = nullptr);
    void randomMap(QVector<QPixmap>,QVector<QPixmap> pixs_nums);
    bool tilesNumbers(int , QVector<int>);
    bool tokenNumbers(int , QVector<int>);
    tileType TileType(int n);
    QVector<Tile*> getTiles();
    QVector<QPushButton*> getAvailableVertexs();
    QVector<QPushButton*> getAvailableEdges();
    void setHide(QVector<QPushButton*>);
    void setUnHide(QVector<QPushButton*>);
    void removeVertex(QPushButton*);
    void removeEdge(QPushButton*);
    QVector<QLabel*> rollNumTile(int num);
    ~Map();

public slots:
//    QVector<QPair<tileType,int>> getAdjacentVertex(QPushButton* p);
//    QVector<QPair<int,int>> getAdjacentTile(QObject* p);
    void moveRobber(int);

private:
    QSignalMapper *signalMapper;

    QVector<Tile*> tiles;
    QVector<QLabel*> labels;

    QVector<QPushButton*> vertexs;
    QVector<QPushButton*> edges;
    QVector<QPushButton*> tokens;
    QVector<QPushButton*> vertexsAvailable;
    QVector<QPushButton*> edgesAvailable;
    Robber robber();

};

#endif // MAP_H
