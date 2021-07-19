#ifndef REQUEST_H
#define REQUEST_H

#include <QMainWindow>
#include "tile.h"
class Player;

namespace Ui {
class Request;
}

class Request : public QMainWindow
{
    Q_OBJECT

public:
    explicit Request(QVector<QPair<tileType,QPair<int,int>>> cards,Player* other,Player* me,QWidget *parent = nullptr);
    bool seeRequest();
    Player* getPlayer(){return player;}
    ~Request();
public slots:
    void ok();
    void cancel();
private:
    Ui::Request *ui;
    Player* player;
    Player* me;
    Player* other;
    QVector<QPair<tileType,QPair<int,int>>> cards;
};

#endif // REQUEST_H
