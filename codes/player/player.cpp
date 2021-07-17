#include "player.h"
#include "ui_Player.h"

Player::Player(Map* _map,QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::Player)
{
    map = _map;
    ui->setupUi(this);
    connect(ui->trade, SIGNAL(clicked()), this, SLOT(goToTradeWindow()));
    connect(ui->road, SIGNAL(clicked()), this, SLOT(showRoads()));
    connect(ui->settlement, SIGNAL(clicked()), this, SLOT(showSetllement()));
    connect(ui->city, SIGNAL(clicked()), this, SLOT(showCity()));
//    connect(ui->city, SIGNAL(clicked()), this, SLOT(serverGetCity()));

}

void Player::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}
bool Player::buySettlement(){
    if(settlementPiece > 3){
        return true;
    }
    if(clayCard && forestCard && pastureCard && fieldCard ){
        return true;
    }
    return false;
}

void Player::addSettlement(QPushButton* p){
    settlements.push_back(p);
    settlementPiece--;
    qDebug() << "settlemt added";
}

bool Player::buyRoad(){
    if(settlementPiece > 13){
        return true;
    }
    if(clayCard && forestCard){
        return true;
    }
    return false;
}

QVector<QPushButton*> Player::getSettlements(){
    return settlements;

}

bool Player::buyCity(){
    if(fieldCard > 1 && stoneCard > 2)
        return true;
    return false;

}
void Player::updateToCity(QPushButton* p){
    int i=0;
    for(;i<settlements.size();i++){
        if(settlements[i]==p)
            break;
    }
    settlements.removeAt(i);
    cities.push_back(p);
}
void Player::addRoad(QPushButton* p){
    roads.push_back(p);
}
void Player::getDevelopmentCard(){

}
void Player::changeRobber(){

}
void Player::getResourceCard(tileType t){
    if (t==field){
        fieldCard++;
    }
    else if(t==stone){
        stoneCard++;
    }
    else if(t==clay){
        clayCard++;
    }
    else if(t==pasture){
        pastureCard++;
    }
    else if(t==forest){
        forestCard++;
    }
    qDebug() << "field card ::" << fieldCard ;
    qDebug() << "stone card ::" << stoneCard ;
    qDebug() << "clay card ::" << clayCard ;
    qDebug() << "pasture card ::" << pastureCard ;
    qDebug() << "forest card ::" << forestCard ;
}



QJsonArray toJson(const std::vector<unsigned short>& myVec) {
    QJsonArray result;
    std::copy (myVec.begin(), myVec.end(), std::back_inserter(result));
    return result;
}


void Player:: goToTradeWindow()
{
    Trade *x = new Trade();
    x->show();
    this->close();
}

void Player::showRoads(){
    if(buyRoad())
        map->setUnHide(map->getAvailableEdges());
}

void Player::showSetllement(){
    if(buySettlement())
         map->setUnHide(map->getAvailableVertexs());
}

void Player::showCity(){
   if(buyCity())
       map->setUnHide(settlements);
}

bool Player::isSettlement(QPushButton(* p)){
    if(settlements.contains(p))
        return true;
    return false;
}
int Player::isAdjacent(Tile* tile){
    int n=0;
    for(int i=0;i<settlements.size();i++){
        if(abs((tile->getLocation()->x()+60) - settlements[i]->x() ) < 85 && abs((tile->getLocation()->y()+70) - settlements[i]->y() ) < 85 ){
            n++;
            qDebug() << tile->getLocation() ;
        }
    }
    return n;

}
