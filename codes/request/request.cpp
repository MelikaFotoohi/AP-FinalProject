#include "request.h"
#include "ui_request.h"
#include "player.h"

Request::Request(QVector<QPair<tileType,QPair<int,int>>> _cards,Player* _other,Player* _me,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Request)
{
    other  = _other;
    me = _me;
    cards = _cards;
    ui->setupUi(this);
    setFixedSize(459 , 200);
    setWindowTitle("Request");

    QPixmap bkgnd(":/new/prefix1/desert.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->pushButton_3->setText("New request from " + other->getName() + " to " + me->getName());
    ui->clayGiveNum->setText(QString::number(cards[0].second.second));
    ui->clayRecNum->setText(QString::number(cards[0].second.first));

    ui->fieldGiveNum->setText(QString::number(cards[1].second.second));
    ui->fieldRecNum->setText(QString::number(cards[1].second.first));

    ui->forestGiveNum->setText(QString::number(cards[2].second.second));
    ui->forestRecNum->setText(QString::number(cards[2].second.first));

    ui->stoneGiveNum->setText(QString::number(cards[3].second.second));
    ui->stoneRecNum->setText(QString::number(cards[3].second.first));

    ui->pastureGiveNum->setText(QString::number(cards[4].second.second));
    ui->pastureRecNum->setText(QString::number(cards[4].second.first));

    QPixmap pixmap_field(":/new/prefix1/cut/grain.jpg");
    QPixmap pixmap_clay(":/new/prefix1/cut/brick2.jpg");
    QPixmap pixmap_forest(":/new/prefix1/cut/lumber.jpg");
    QPixmap pixmap_stone(":/new/prefix1/cut/ors.jpg");
    QPixmap pixmap_pasture(":/new/prefix1/cut/wool.jpg");

    ui->label->setPixmap(pixmap_clay);
    ui->label->setMask(pixmap_clay.mask());
    ui->label_2->setPixmap(pixmap_field);
    ui->label_2->setMask(pixmap_field.mask());
    ui->label_3->setPixmap(pixmap_forest);
    ui->label_3->setMask(pixmap_forest.mask());
    ui->label_4->setPixmap(pixmap_stone);
    ui->label_4->setMask(pixmap_stone.mask());
    ui->label_5->setPixmap(pixmap_pasture);
    ui->label_5->setMask(pixmap_pasture.mask());

    QPixmap pixmap_approve(":/new/prefix1/icons/icon_approve.jpg");
    QIcon Button_approve(pixmap_approve);
    ui->ok->setIcon(Button_approve);
    ui->ok->setIconSize(pixmap_approve.rect().size());


    QPixmap pixmap_cross(":/new/prefix1/icons/icon_cross.jpg");
    QIcon Button_cross(pixmap_cross);
    ui->cancel->setIcon(Button_cross);
    ui->cancel->setIconSize(pixmap_cross.rect().size());

    connect(ui->ok,SIGNAL(clicked()),this,SLOT(ok()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

void Request::ok(){
    for(int i=0;i<cards.size();i++){
        for(int j=0;j<cards[i].second.first;j++){
            me->getResourceCard(cards[i].first);
            other->giveResourceCard(cards[i].first);
        }
        for(int j=0;j<cards[i].second.second;j++){
            other->getResourceCard(cards[i].first);
            me->giveResourceCard(cards[i].first);
        }
    }
    this->close();
}


void Request::cancel(){
    this->close();
}
Request::~Request()
{
    delete ui;
}
