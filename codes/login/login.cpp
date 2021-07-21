#include "login.h"
#include "ui_login.h"


login::login(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::login)
{

    ui->setupUi(this);
    QPixmap image(":/new/prefix1/backgrounds/images.jpeg");
    ui->label->setPixmap(image);
    ui->label->setMask(image.mask());
    setWindowTitle("Catan");
    setFixedSize(440 , 290);

}

void login::startGame(){}
login::~login()
{
    delete ui;
}
