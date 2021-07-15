#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    this->setFixedSize(490,670);

    this->centralWidget()->setStyleSheet( "background-image:url(\"/Users/AHFB/Favorites/Desktop/catan images/background/22.jpg\"); background-position: center;");

    ui->playerUsernameLine->setText("player1");

    QPixmap pixmap("/Users/AHFB/Favorites/Desktop/catan images/resource cards/brick2.jpg");
    QIcon ButtonIcon(pixmap);
    setIconForPushButton(pixmap, ButtonIcon, ui->pushButton);

    QPixmap pixmap2("/Users/AHFB/Favorites/Desktop/catan images/resource cards/grain2.jpg");
    QIcon ButtonIcon2(pixmap2);
    setIconForPushButton(pixmap2, ButtonIcon2, ui->pushButton_2);

    QPixmap pixmap3("/Users/AHFB/Favorites/Desktop/catan images/resource cards/lumber2.jpg");
    QIcon ButtonIcon3(pixmap3);
    setIconForPushButton(pixmap3, ButtonIcon3, ui->pushButton_3);

    QPixmap pixmap4("/Users/AHFB/Favorites/Desktop/catan images/resource cards/ore2.jpg");
    QIcon ButtonIcon4(pixmap4);
    setIconForPushButton(pixmap4, ButtonIcon4, ui->pushButton_4);

    QPixmap pixmap5("/Users/AHFB/Favorites/Desktop/catan images/resource cards/wool2.jpg");
    QIcon ButtonIcon5(pixmap5);
    setIconForPushButton(pixmap5, ButtonIcon5, ui->pushButton_5);

    QPixmap pixmap6("/Users/AHFB/Favorites/Desktop/catan images/development cards/knight1.jpg");
    QIcon ButtonIcon6(pixmap6);
    setIconForPushButton(pixmap6, ButtonIcon6, ui->pushButton_6);

    QPixmap pixmap7("/Users/AHFB/Favorites/Desktop/catan images/development cards/monopoly1.jpg");
    QIcon ButtonIcon7(pixmap7);
    setIconForPushButton(pixmap7, ButtonIcon7, ui->pushButton_7);

    QPixmap pixmap8("/Users/AHFB/Favorites/Desktop/catan images/development cards/road_buildings1.jpg");
    QIcon ButtonIcon8(pixmap8);
    setIconForPushButton(pixmap8, ButtonIcon8, ui->pushButton_8);

    QPixmap pixmap9("/Users/AHFB/Favorites/Desktop/catan images/development cards/year_of_plenty1.jpg");
    QIcon ButtonIcon9(pixmap9);
    setIconForPushButton(pixmap9, ButtonIcon9, ui->pushButton_9);

    QPixmap pixmap10("/Users/AHFB/Favorites/Desktop/catan images/development cards/victory_point21.jpg");
    QIcon ButtonIcon10(pixmap10);
    setIconForPushButton(pixmap10, ButtonIcon10, ui->pushButton_10);

    QPixmap pixmap11("/Users/AHFB/Favorites/Desktop/catan images/special cards/largest_army.jpg");
    QIcon ButtonIcon11(pixmap11);
    setIconForPushButton(pixmap11, ButtonIcon11, ui->pushButton_11);

    QPixmap pixmap12("/Users/AHFB/Favorites/Desktop/catan images/special cards/longest_road.jpg");
    QIcon ButtonIcon12(pixmap12);
    setIconForPushButton(pixmap12, ButtonIcon12, ui->pushButton_12);

    QPixmap pixmap13("/Users/AHFB/Favorites/Desktop/catan images/pieces/road4.jpg");
    QIcon ButtonIcon13(pixmap13);
    setIconForPushButton(pixmap13, ButtonIcon13, ui->pushButton_13);

    QPixmap pixmap14("/Users/AHFB/Favorites/Desktop/catan images/pieces/city2.jpg");
    QIcon ButtonIcon14(pixmap14);
    setIconForPushButton(pixmap14, ButtonIcon14, ui->pushButton_14);

    QPixmap pixmap15("/Users/AHFB/Favorites/Desktop/catan images/pieces/house1.jpg");
    QIcon ButtonIcon15(pixmap15);
    setIconForPushButton(pixmap15, ButtonIcon15, ui->pushButton_15);

    QPixmap pixmap16("/Users/AHFB/Favorites/Desktop/catan images/trade_icon.png");
    QIcon ButtonIcon16(pixmap16);
    setIconForPushButton(pixmap16, ButtonIcon16, ui->pushButton_16);

    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(goToTradeWindow()));
}

void MainWindow::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: goToTradeWindow()
{
    tradewindow *x = new tradewindow();
    x->show();
    this->close();
}
