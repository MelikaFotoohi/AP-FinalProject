#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QVector>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonArray>

#include "resourcecard.h"
#include "developmentcard.h"
#include "building.h"
#include "trade.h"
#include "map.h"

namespace Ui {
class Player;
}


class Player : public QMainWindow
{
    Q_OBJECT
public:
    Ui::Player *ui;
    Player(Map* _map,QWidget *parent = nullptr);
    bool buySettlement();
    bool buyRoad();
    bool buyCity();
    void addSettlement(QPushButton*);
    void updateToCity(QPushButton*);
    void addRoad(QPushButton*);
    void getDevelopmentCard();
    void getResourceCard(tileType);
    void changeRobber();
    bool isSettlement(QPushButton*);
    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);
    QVector<QPushButton*> getSettlements();
    int isAdjacent(Tile* tile);

private:
    Map* map;

    QVector<QPushButton*> settlements;
    QVector<QPushButton*> cities;
    QVector<QPushButton*> roads;

    int fieldCard=0 , stoneCard=0, clayCard=0, pastureCard=0, forestCard=0;
    int victoryPointCard=0, KnightCard=0, roadBuildingCard=0, yearOfPlentyCard=0, monopolyCard=0;
    int bridgePiece=0, roadPiece=15, cityPiece=4, settlementPiece=5;
    int totalPoint;
    int PlayerID;
    int sumOfDices;

    QTcpSocket* clientSocket;
public slots:
    void goToTradeWindow();
    void showRoads();
    void showSetllement();
    void showCity();



};

#endif // PLAYER_H
