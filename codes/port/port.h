#ifndef PORT_H
#define PORT_H

#include <QWidget>

enum port {normalPort, woodPort, wheatPort, sheepPort, brickPort, stonePort };

class Port : public QWidget
{
    Q_OBJECT
public:
    Port(port portType, QWidget *parent = nullptr);
    void draw();
    void chengeCondition();
private:
    port portType;

};

#endif // PORT_H
