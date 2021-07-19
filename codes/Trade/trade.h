#ifndef TRADE_H
#define TRADE_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

#include "player.h"
#include "Map.h"
#include "bank.h"

namespace Ui {
class Trade;
}

class Trade : public QMainWindow
{
    Q_OBJECT

public:
    Trade(Bank* bank,QVector<Player*>, int, Map* map, QWidget *parent = nullptr);
    ~Trade();

    void setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button);
    int givePlayerId(QString name);

public slots:
    void TradeRequest(bool);
    void waitForCheckingConditions();

private:
    Ui::Trade *ui;
    Map* map;
    int playerId;
    QVector<Player*> players;
    Bank* bank;

};

#endif // TRADE_H


