#ifndef DICE_H
#define DICE_H

#include <QWidget>
#include "Map.h"
#include "player.h"
class Dice : public QWidget
{
    Q_OBJECT
public:
    explicit Dice(Map* _map,QWidget *parent = nullptr);
public slots:
    int roll();
private:
    static int diceNum;
    Map* map;
    Ui::Map *ui;
};

#endif // DICE_H
