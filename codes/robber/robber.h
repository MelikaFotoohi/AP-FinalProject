#ifndef ROBBER_H
#define ROBBER_H

#include <QWidget>
#include "location.h"

class Robber : public QWidget
{
    Q_OBJECT
public:
    Robber(Location location,QWidget *parent = nullptr);
    void move(Location location);
    void draw();

private:
    Location location;
signals:

};

#endif // ROBBER_H
