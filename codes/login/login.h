#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
     login(QWidget *parent = nullptr);
      Ui::login *ui;
    ~login();
public slots:
     void startGame();

private:

};

#endif // LOGIN_H
