#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "board.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
     Login(QWidget *parent = nullptr);
    ~Login();
public slots:
     void openBoard();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
