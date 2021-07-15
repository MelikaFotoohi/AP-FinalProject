#ifndef DICE_H
#define DICE_H

#include <QWidget>

class Dice : public QWidget
{
    Q_OBJECT
public:
    Dice(QWidget *parent = nullptr);
    void roll();
    void draw();

private:
    int value;
signals:

};

#endif // DICE_H
