#include "winners.h"
#include "ui_winners.h"

winners::winners(QWidget *parent) : QMainWindow(parent) , ui(new Ui::winners)
{
    ui->setupUi(this);
    setWindowTitle("Score Board");


}
void winners::showWinners(QVector< QPair<QString , int>> players_score){
    setFixedSize(410  , 500);
    QPixmap bkgnd(":/new/prefix1/backgrounds/catan-background_seafarers.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QPixmap pixmap_medal1(":/new/prefix1/medal/medal_gold.png");
    ui->medal_1->setPixmap(pixmap_medal1);
    ui->medal_1->setMask(pixmap_medal1.mask());
    QPixmap pixmap_medal2(":/new/prefix1/medal/medal_silver.png");
    ui->medal_2->setPixmap(pixmap_medal2);
    ui->medal_2->setMask(pixmap_medal2.mask());
    QPixmap pixmap_medal3(":/new/prefix1/medal/medal_bronz.png");
    ui->medal_3->setPixmap(pixmap_medal3);
    ui->medal_3->setMask(pixmap_medal3.mask());

    ui->name_1->setText(players_score[0].first);
    ui->score_1->setText(QString::number(players_score[0].second));
    ui->name_2->setText(players_score[1].first);
    ui->score_2->setText(QString::number(players_score[1].second));
    ui->name_3->setText(players_score[2].first);
    ui->score_3->setText(QString::number(players_score[2].second));
    ui->name_4->setText(players_score[3].first);
    ui->score_4->setText(QString::number(players_score[3].second));
}
