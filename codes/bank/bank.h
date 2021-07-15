#ifndef BANK_H
#define BANK_H

#include <QWidget>

class Bank : public QWidget
{
    Q_OBJECT
public:
    explicit Bank(QWidget *parent = nullptr);
    void giveCardToPlayer();
    void getCardFromPlayer();
private:
    int numVictoryCard;
    int numberOfKnightCard;
    int numberOfRoadBuildingCard;
    int numYearOfPlenty;
    int numMonopoy;

    int numWoodCard;
    int numWheatCard;
    int numSheepCard;
    int numBrickCard;
    int numStoneCard;


    bool largestArmyCard;
    bool largestRoadCard;


signals:

};

#endif // BANK_H
