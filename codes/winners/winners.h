#ifndef WINNERS_H
#define WINNERS_H

#include <QMainWindow>


namespace Ui{ class winners;}
class winners : public QMainWindow
{
    Q_OBJECT
public:
    explicit winners(QWidget *parent = nullptr);
    void showWinners(QVector< QPair<QString , int>>);
private:
    Ui::winners* ui;

signals:

};

#endif // WINNERS_H
