#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>

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
