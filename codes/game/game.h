#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QSignalMapper>


#include "player.h"
#include "map.h"
#include "bank.h"
#include "dice.h"
#include "trade.h"
#include "login.h"
#include "winners.h"
#include <QMessageBox>

class Game : public QMainWindow
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void checkWining();
    void settlementConnect();
    void roadConnect();
    void monopolyConnect();
    void yearOfPlentyConnect();
    void robberConnect();
    void showWinner();
    void changeTurn(Player* pre,Player* cur);
    void setColorForSettlements(Player* thePlayer, QPixmap pixmap, QPushButton* housePB);
    void setColorForCities(Player * thePlayer, QPixmap pixmap, QPushButton * cityPB);
    void setColorForRoads(Player *thePlayer, QPushButton * roadPB);
    void checkGettingMonopoly(tileType type, int n , int num);
    void sort(QVector<QPair<QString , int>>);
    void checkLargestArmy();
    ~Game();
private:
    QSignalMapper *signalMapper;
    QVector<Player*> players;
    QVector<login*> logins;
    Player* player1;
    Player* player2;
    Player* player3;
    Player* player4;

    Map* map;
    Bank* bank;
    Dice* dice;

    bool start;

    static int diceNum;
    static int player_;
    static int count;

public slots:
    void goToLogin(int);
    void giveCardRoll();
    void playerTurn();
    void gotoRoll();
    void robberSelected(QObject*);
    void slectedBuilding(QObject*);
    void slectedSetllement(QObject*);
    void slectedCity(QObject*);
    void slectedRoad(QObject*);
    void tradeConnect(int);
    void goToTradeWindow(int);
    void getDevelopment();
    void getMonopoly(int);
    void getYeatOfPlenty(int);

};

#endif // GAME_H
