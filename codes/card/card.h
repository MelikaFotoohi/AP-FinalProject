#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>

enum developmentType {victoryPoint, Knight, roadBuilding, yearOfPlenty, monopoly };
enum resourceType {fieldCard, stoneCard, clayCard, pastureCard, forestCard };
enum specialType {longestRoadCard, largerstArmyCard };

class Card : public QWidget
{
    Q_OBJECT
public:
    Card(QWidget *parent = nullptr, QString str1 = "", QString str2 = "");
    void virtual draw() =0;
    void virtual checkMaxCount() =0;
private:
    QString name;
    QString description;
    int numPlayerCard;

signals:

};

#endif // CARD_H
