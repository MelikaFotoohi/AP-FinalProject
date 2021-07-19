#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QTcpServer>
#include <QMainWindow>
#include "player.h"
#include "Map.h"
#include "bank.h"
#include "thread.h"
#include "dice.h"
#include "trade.h"
#include "login.h"
#include "winners.h"

#include <QSignalMapper>
#include <QMessageBox>

class Game : public QMainWindow
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void startGame();
    void checkWinner();
    void showWinner();
    void settlementConnect();
    void roadConnect();
    void monopolyConnect();
    void yearOfPlentyConnect();


private:
    QVector<Login*>logins;
    QSignalMapper *signalMapper;
    QVector<Player*> players;
    Player* player1;
    Player* player2;
    Player* player3;
    Player* player4;

    Map* map;
    Bank* bank;
    Dice* dice;

    bool start;

    static int diceNum;
    static int currPlayer;
    static int gameStarted_;
    static int player_;



public slots:
    void goToLogin(int);
    void giveCardRoll();
    void playerTurn();
    void gotoRoll();
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
