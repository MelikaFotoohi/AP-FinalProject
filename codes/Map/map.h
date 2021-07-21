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
    void randomMap(QVector<QPixmap>,QVector<QPixmap>);
    tileType TileType(int);
    QVector<Tile*> getTiles();
    QVector<QPushButton*> getAvailableVertexs();
    QVector<QPushButton*> getAvailableEdges();
    QVector<QPushButton*> getTokens();
    QPushButton* getRobberToken();
    void setRobberToken(QPushButton*);
    void setHide(QVector<QPushButton*>);
    void setUnHide(QVector<QPushButton*>);
    void removeVertex(QPushButton*);
    void removeEdge(QPushButton*);
    bool tilesNumbers(int, QVector<int>);
    bool tokenNumbers(int , QVector<int>);
    QVector<QPair<tileType,QPair<QPushButton*,QPushButton*>>> getPorts();
    ~Map();

private:
    QSignalMapper *signalMapper;

    QVector<Tile*> tiles;
    QVector<QLabel*> labels;
    QPushButton* robberToken;
    QVector<QPushButton*> vertexs;
    QVector<QPushButton*> edges;
    QVector<QPushButton*> tokens;
    QVector<QPushButton*> vertexsAvailable;
    QVector<QPushButton*> edgesAvailable;
    QVector<QPair<tileType,QPair<QPushButton*,QPushButton*>>> ports;

};

#endif // MAP_H
