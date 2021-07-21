#include "dice.h"
#include "ui_map.h"

int Dice::diceNum = 2;

Dice::Dice(Map* _map,QWidget *parent) : QWidget(parent)
{
    map = _map;
}
int Dice::roll(){
    QPixmap Dice1(":/new/prefix1/dice/dice_1.png");
    QPixmap Dice2(":/new/prefix1/dice/dice_2.png");
    QPixmap Dice3(":/new/prefix1/dice/dice_3.png");
    QPixmap Dice4(":/new/prefix1/dice/dice_4.png");
    QPixmap Dice5(":/new/prefix1/dice/dIce_5.png");
    QPixmap Dice6(":/new/prefix1/dice/dice_6.png");

    QVector<QPixmap> pix{Dice1 , Dice2 , Dice3 , Dice4 , Dice5 , Dice6};
    int i = rand() % 6;
    diceNum = i + 1;
    QIcon button1(pix[i]);
    map->ui->Dice_1->setIcon(button1);

    map->ui->Dice_1->setIconSize(pix[i].rect().size());

    i = rand() % 6;
    diceNum += i + 1;
    QIcon button2(pix[i]);
    map->ui->Dice_2->setIcon(button2);

    map->ui->Dice_2->setIconSize(pix[i].rect().size());
    return diceNum;
}
