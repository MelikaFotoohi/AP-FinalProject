#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent):QWidget(parent) , ui(new Ui::Login){

    ui->setupUi(this);
    setWindowTitle("Catan");
    setFixedSize(440 , 290);
    connect(ui->pushButton , SIGNAL(clicked()) , this , SLOT(openBoard()));

}

void Login::openBoard(){

    Board *brd = new Board();
    this->close();
    brd->show();

}

Login::~Login()
{

}


