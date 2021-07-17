#include "game.h"
#include "ui_Player.h"
#include "ui_map.h"
#include <QDebug>

int Game::diceNum = 2;
int Game::gameStarted_ = 0;
int Game::player_ = 0;
int Game::builds_ = 0;

Game::Game(QObject *parent) : QTcpServer(parent)
{
    map = new Map();
    map->show();

    bank = new Bank();

    player1 = new Player(map);
    player2 = new Player(map);
    player3 = new Player(map);
    player4 = new Player(map);

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    player1->show();
    player2->show();
    player3->show();
    player4->show();
    for(int i=0;i<players.size();i++){
        Print(players[i]->ui);
    }

    settlementConnect();
    roadConnect();

    connect(map->ui->Dice_1 , SIGNAL(clicked()) , this , SLOT(gotoRoll()));
    connect(map->ui->Dice_2 , SIGNAL(clicked()) , this , SLOT(gotoRoll()));
}

void Game::gotoRoll(){
    dice->roll();
}

/*give card after dice rolled*/
void Game::giveCardRoll(){
    qDebug() << "abcdefghijk" ;
    QVector<Tile*> tiles = map->getTiles();
    for(int i=0;i<map->getTiles().size();i++){
        if(tiles[i]->getToken() == diceNum){
            for(int j=0;j<players.size();j++){
                bank->giveCardToWhom(tiles[i],players[j]);
            }
        }
    }
}

/* connect pushButton settlement */
void Game::settlementConnect(){
    for(int i=0;i<map->getAvailableVertexs().size();i++){
        signalMapper = new QSignalMapper(this);
        connect(map->getAvailableVertexs()[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(map->getAvailableVertexs()[i],map->getAvailableVertexs()[i]);
        connect(signalMapper, SIGNAL(mappedObject(QObject*)),this, SLOT(slectedSetllement(QObject*)));
    }
}

/* connect pushButton road */
void Game::roadConnect(){
    for(int i=0;i<map->getAvailableEdges().size();i++){
        signalMapper = new QSignalMapper(this);
        connect(map->getAvailableEdges()[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(map->getAvailableEdges()[i],map->getAvailableEdges()[i]);
        connect(signalMapper, SIGNAL(mappedObject(QObject*)),this, SLOT(slectedRoad(QObject*)));
    }
}

void Game::slectedBuilding(QObject* p){
    QPushButton* building = qobject_cast<QPushButton*>(p);
    int isSettlement = -1;
    for(int i=0;i<players.size();i++){
        if(players[i]->isSettlement(building))
            isSettlement = i;
    }
    if(isSettlement == -1)
        slectedSetllement(building);
    else{
        if(player_ == isSettlement)
            slectedCity(building);
    }

}
/* get selected settlement */
void Game::slectedSetllement(QObject* p){
    QPushButton* house = qobject_cast<QPushButton*>(p);
    if(player1->buySettlement() && player_ == 0){
        QPixmap home("/Users/macbook/Desktop/home1.jpeg");
        QIcon homeIcon(home);
        house->setIcon(homeIcon);
        house->setIconSize(home.rect().size());
        player1->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    else if(player2->buySettlement() && player_ == 1){
        QPixmap home("/Users/macbook/Desktop/home2.jpeg");
        QIcon homeIcon(home);
        house->setIcon(homeIcon);
        house->setIconSize(home.rect().size());
        player2->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    else if(player3->buySettlement() && player_ == 2){
        QPixmap home("/Users/macbook/Desktop/home3.jpeg");
        QIcon homeIcon(home);
        house->setIcon(homeIcon);
        house->setIconSize(home.rect().size());
        player3->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    else if(player4->buySettlement() && player_ == 3){
        QPixmap home("/Users/macbook/Desktop/home4.jpeg");
        QIcon homeIcon(home);
        house->setIcon(homeIcon);
        house->setIconSize(home.rect().size());
        player4->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    map->setHide(map->getAvailableVertexs());
}

void Game::slectedCity(QObject* p){
    QPushButton* city = qobject_cast<QPushButton*>(p);
    if(player1->buyCity() && player_ == 0){
        QPixmap home("/Users/macbook/Desktop/yellow_city.jpeg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player1->updateToCity(city);
        bank->cityBought();
    }
    else if(player2->buyCity() && player_ == 1){
        QPixmap home("/Users/macbook/Desktop/blue_city.jpeg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player2->updateToCity(city);
        bank->cityBought();
    }
    else if(player3->buyCity() && player_ == 2){
        QPixmap home("/Users/macbook/Desktop/green_city.jpeg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player2->updateToCity(city);
        bank->cityBought();
    }
    else if(player4->buyCity() && player_ == 3){
        QPixmap home("/Users/macbook/Desktop/red_city.jpeg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player2->updateToCity(city);
        bank->cityBought();
    }
}

void Game::slectedRoad(QObject* p){
    QPushButton* road = qobject_cast<QPushButton*>(p);
    if(player1->buyRoad() && player_ == 0){
        road->setStyleSheet("background-color: rgb(255,0,0);");
        player1->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player1->buyRoad() && player_ == 1){
        road->setStyleSheet("background-color: rgb(0,255,0);");
        player2->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player1->buyRoad() && player_ == 2){
        road->setStyleSheet("background-color: rgb(0,0,255);");
        player3->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player1->buyRoad() && player_ == 3){
        road->setStyleSheet("background-color: rgb(255,255,0);");
        player4->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    map->setHide(map->getAvailableEdges());
}

void Game::Print(Ui::Player* ui)
{
    connect(ui->finish,SIGNAL(clicked()),this,SLOT(playerTurn()));
    connect(ui->roll, SIGNAL(clicked()) , this , SLOT(giveCardRoll()));
}

void Game::startGame(){

}

void Game::playerTurn(){
    if(player_ == 0){
        player_ = 1;
    }else if(player_ == 1){
        player_ = 2;
    }else if(player_ == 2){
        player_ = 3;
    }else if(player_ == 3){
        player_ = 0;
    }
}

void Game::checkWining(){

}
