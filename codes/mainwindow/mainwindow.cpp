#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->centralWidget()->setStyleSheet("background-image:url(\"/catan.jpeg\"); background-position: center;");
    QPixmap pix("/catan-logo.png");
    ui->label->setPixmap(pix);
    this->setFixedSize(500 , 350);
    connect(ui->pushButton , SIGNAL(clicked()) , this , SLOT(openLoginPage()));

}
void MainWindow::openLoginPage(){
     Login *lgn = new Login();
     this->close();
     lgn->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}



