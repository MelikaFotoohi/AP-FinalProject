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
#include "map.h"

class Bank;
class Requst;

namespace Ui {
class Player;
}


class Player : public QMainWindow
{
    Q_OBJECT
public:
    Ui::Player *ui;
    Player(QString _name,Bank* bank, Map* _map, QWidget *parent = nullptr);

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

    void useYearOfPlenty(tileType,tileType);

    void showRequest(QVector<QPair<tileType,QPair<int,int>>> cards, Player* p);

    void changeRobber();

    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);

    void update();
    void enablePushButtons(bool);
    QString getName();

    QVector<QPushButton*> getSettlements();
    QVector<QPair<tileType,int>> getCardsNum();

    void setName(QString);
    Requst* getRequsr(){return request;}
    bool checkRequset(QVector<QPair<tileType,int>>);
    int getClayBank();
    int getForestBank();
    int getStoneBank();
    int getPastureBank();
    int getFieldBank();

private:
    int plyareID;
    QString name;

    Map* map;
    Bank* bank;
    Requst* request;

    QVector<QPushButton*> settlements;
    QVector<QPushButton*> cities;
    QVector<QPushButton*> roads;

    int fieldCard=0 , stoneCard=0, clayCard=0, pastureCard=0, forestCard=0;
    int victoryPointCard=0, KnightCard=0, roadBuildingCard=0, yearOfPlentyCard=0, monopolyCard=2;
    int bridgePiece=0, roadPiece=15, cityPiece=4, settlementPiece=5;
    int totalPoint = 0;
    int PlayerID;
    int sumOfDices;
    int clayBank = 4, forestBank = 4, stoneBank = 4, pastureBank = 4, fieldBank = 4;
    int cityCount = 0;

public slots:

    void showRoads();
    void showSetllement();
    void showCity();

signals:



};

#endif // PLAYER_H
