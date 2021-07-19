#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QVector>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonArray>
#include <QMessageBox>

#include "resourcecard.h"
#include "developmentcard.h"
#include "building.h"
#include "card.h"
#include "Map.h"

class Request;

namespace Ui {
class Player;
}


class Player : public QMainWindow
{
    Q_OBJECT
public:
    Ui::Player *ui;
    Player(QString _name, Map* _map, QWidget *parent = nullptr);

    bool buySettlement();
    bool buyRoad();
    bool buyCity();
    bool buyDevelopment();

    bool isSettlement(QPushButton*);
    int isAdjacent(Tile* tile);

    int getTotalPoint();

    void addSettlement(QPushButton*);
    void updateToCity(QPushButton*);
    void addRoad(QPushButton*);

    void getDevelopmentCard(developmentType);

    void getResourceCard(tileType);
    void giveResourceCard(tileType);

    int giveMonopoly(tileType);
    void getMonopoly(tileType,int);

    void showRequest(QVector<QPair<tileType,QPair<int,int>>> cards, Player* p);

    void changeRobber();

    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);

    void enablePushButtons(bool);

    void update();
    QString getName();

    QVector<QPushButton*> getSettlements();
    QVector<QPair<tileType,int>> getCardsNum();

    void setName(QString);
    Request* getRequsr(){return request;}




private:

    int plyareID;
    QString name;
    Map* map;
    Request* request;


    QVector<QPushButton*> settlements;
    QVector<QPushButton*> cities;
    QVector<QPushButton*> roads;

    int fieldCard=4 , stoneCard=4, clayCard=4, pastureCard=4, forestCard=4;
    int victoryPointCard=0, KnightCard=0, roadBuildingCard=0, yearOfPlentyCard=0, monopolyCard=0;
    int bridgePiece=0, roadPiece=15, cityPiece=4, settlementPiece=5;
    int totalPoint = 0;
    int PlayerID;
    int sumOfDices;


public slots:

    void showRoads();
    void showSetllement();
    void showCity();



signals:



};

#endif // PLAYER_H
