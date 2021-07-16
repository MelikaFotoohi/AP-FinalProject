#ifndef GAME_H
#define GAME_H

#include <QVector>

#include "player.h"
#include "map.h"
#include "bank.h"


class Game
{
public:
    Game();
    void checkWining();
    int playerTurn();
private:
    QVector<Player*> players;
    Map map;
    Bank bank;
    bool start;


};

#endif // GAME_H
