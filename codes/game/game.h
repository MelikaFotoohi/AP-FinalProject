#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QTcpServer>
#include "player.h"
#include "map.h"
#include "bank.h"
#include "thread.h"
#include "dice.h"
#include <QSignalMapper>

class Game : public QTcpServer
{
    Q_OBJECT
public:
    Game(QObject *parent = 0);
    void startGame();

    void checkWining();
   // void startServer();
    void Print(Ui::Player *ui);
    void settlementConnect();
    void roadConnect();


private:
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
    static int builds_;

public slots:
    void giveCardRoll();
    void playerTurn();
    void gotoRoll();
    void slectedBuilding(QObject*);
    void slectedSetllement(QObject* p);
    void slectedCity(QObject* p);
    void slectedRoad(QObject* p);
protected:
  //  void incomingConnection(qintptr socketDescriptor);

};

#endif // GAME_H
