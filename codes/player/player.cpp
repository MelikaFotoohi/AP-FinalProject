#include "player.h"
#include "ui_Player.h"
#include "request.h"
#include "bank.h"

Player::Player(QString _name,Bank* _bank, Map* _map,QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::Player)
{
    ui->setupUi(this);
    map = _map;
    name = _name;
    bank = _bank;

    ui->victoryPoint->setEnabled(false);
    ui->knight->setEnabled(false);
    ui->roadBuilding->setEnabled(false);
    update();

    QPixmap pixmap("/Users/macbook/Desktop/images/resource cards/brick1.jpg");
    QIcon ButtonIcon(pixmap);
    setIconForPushButton(pixmap, ButtonIcon, ui->clay);

    QPixmap pixmap2("/Users/macbook/Desktop/images/resource cards/grain1.jpg");
    QIcon ButtonIcon2(pixmap2);
    setIconForPushButton(pixmap2, ButtonIcon2, ui->field);

    QPixmap pixmap3("/Users/macbook/Desktop/images/resource cards/lumber1.jpg");
    QIcon ButtonIcon3(pixmap3);
    setIconForPushButton(pixmap3, ButtonIcon3, ui->forest);

    QPixmap pixmap4("/Users/macbook/Desktop/images/resource cards/ore1.jpg");
    QIcon ButtonIcon4(pixmap4);
    setIconForPushButton(pixmap4, ButtonIcon4, ui->stone);

    QPixmap pixmap5("/Users/macbook/Desktop/images/resource cards/wool1.jpg");
    QIcon ButtonIcon5(pixmap5);
    setIconForPushButton(pixmap5, ButtonIcon5, ui->pasture);

    QPixmap pixmap6("/Users/macbook/Desktop/images/development cards/knight.jpg");
    QIcon ButtonIcon6(pixmap6);
    setIconForPushButton(pixmap6, ButtonIcon6, ui->knight);

    QPixmap pixmap7("/Users/macbook/Desktop/images/development cards/monopoly.jpg");
    QIcon ButtonIcon7(pixmap7);
    setIconForPushButton(pixmap7, ButtonIcon7, ui->monopoly);

    QPixmap pixmap8("/Users/macbook/Desktop/images/development cards/road_building.jpg");
    QIcon ButtonIcon8(pixmap8);
    setIconForPushButton(pixmap8, ButtonIcon8, ui->roadBuilding);

    QPixmap pixmap9("/Users/macbook/Desktop/images/development cards/year_of_plenty.jpg");
    QIcon ButtonIcon9(pixmap9);
    setIconForPushButton(pixmap9, ButtonIcon9, ui->yearOfPlenty);

    QPixmap pixmap10("/Users/macbook/Desktop/images/development cards/victory_point.jpg");
    QIcon ButtonIcon10(pixmap10);
    setIconForPushButton(pixmap10, ButtonIcon10, ui->victoryPoint);

    QPixmap pixmap13("/Users/macbook/Desktop/images/piecesIcon/theHouse.jpg");
    QIcon ButtonIcon13(pixmap13);
    setIconForPushButton(pixmap13, ButtonIcon13, ui->settlement);

    QPixmap pixmap14("/Users/macbook/Desktop/images/piecesIcon/theCity.jpg");
    QIcon ButtonIcon14(pixmap14);
    setIconForPushButton(pixmap14, ButtonIcon14, ui->city);

    QPixmap pixmap15("/Users/macbook/Desktop/images/piecesIcon/theRoad.jpg");
    QIcon ButtonIcon15(pixmap15);
    setIconForPushButton(pixmap15, ButtonIcon15, ui->road);

    connect(ui->road, SIGNAL(clicked()), this, SLOT(showRoads()));
    connect(ui->settlement, SIGNAL(clicked()), this, SLOT(showSetllement()));
    connect(ui->city, SIGNAL(clicked()), this, SLOT(showCity()));

}

void Player::setName(QString _name){
    name = _name;
    ui->username->setText(name);
}

void Player::update(){
    if(monopolyCard<1){
        ui->monopoly->setEnabled(false);
    }else
        ui->monopoly->setEnabled(true);
    if(yearOfPlentyCard<1){
        ui->yearOfPlenty->setEnabled(false);
    }else
        ui->yearOfPlenty->setEnabled(true);
    if(clayCard < 0)
        clayCard = 0;
    if(forestCard < 0)
        forestCard = 0;
    if(pastureCard < 0)
        pastureCard = 0;
    if(stoneCard < 0)
        stoneCard = 0;
    if(fieldCard < 0)
        fieldCard = 0;
    ui->clayNum->setText(QString::number(clayCard));
    ui->forestNum->setText(QString::number(forestCard));
    ui->pastureNum->setText(QString::number(pastureCard));
    ui->stoneNum->setText(QString::number(stoneCard));
    ui->fieldNum->setText(QString::number(fieldCard));
    ui->cityNum->setText(QString::number(cityPiece));
    ui->settlementNum->setText(QString::number(settlementPiece));
    ui->roadNum->setText(QString::number(roadPiece));
    ui->knightNum->setText(QString::number(KnightCard));
    ui->monopolyNum->setText(QString::number(monopolyCard));
    ui->roadBuildingNum->setText(QString::number(roadBuildingCard));
    ui->victoryPointNum->setText(QString::number(victoryPointCard));
    ui->yearOfPlentyNum->setText(QString::number(yearOfPlentyCard));

}
int Player::getTotalPoint(){
    return totalPoint;
}

void Player::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}

bool Player::buyDevelopment(){
    if(fieldCard && pastureCard && stoneCard)
       return true;
    return false;
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

bool Player::buyRoad(){
    if(roadPiece > 13){
        return true;
    }
    if(clayCard && forestCard){
        return true;
    }
 //   QMessageBox::warning(this, tr("warning"), tr("you can't buy a road"));
    return false;
}


void Player::addSettlement(QPushButton* p){
    settlements.push_back(p);
    totalPoint++;
    p->setDisabled(true);
    qDebug() << settlementPiece;
    if(settlementPiece < 4){
        clayCard--;
        forestCard--;
        pastureCard--;
        fieldCard--;
    }
    if(settlementPiece == 4){
        QVector<Tile*> tiles = map->getTiles();
//        for(int i=0;i<settlements.size();i++){
//            if(abs((tile->getLocation()->x()+65) - (settlements[i]->x()+10) ) < 100 &&
//                    abs((tile->getLocation()->y()+75) - (settlements[i]->y()+12) ) < 100 ){
//                n++;

//            }
//        }
        for(int i=0 ; i<map->getTiles().size() ; i++){
            qDebug() << tiles[i]->getLocation()->x() << "  " << tiles[i]->getLocation()->y() ;
            qDebug() << p->x() << "  " << p->y() << "\n\n";
            if( abs((tiles[i]->getLocation()->x()+65) - (p->x()+10)) < 100 &&
                 abs((tiles[i]->getLocation()->y()+75) - (p->y()+12)) < 100){
              getResourceCard(tiles[i]->getType());
              bank->getCardFromPlayer(tiles[i]->getType());
            }
        }
    }
    settlementPiece--;
    update();
    if(map->getPorts()[0].second.first == p || map->getPorts()[0].second.second == p)
        clayBank = 2;
    else if(map->getPorts()[1].second.first == p || map->getPorts()[1].second.second == p)
        pastureBank = 2;
    else if(map->getPorts()[2].second.first == p || map->getPorts()[2].second.second == p)
        stoneBank = 2;
    else if(map->getPorts()[3].second.first == p || map->getPorts()[3].second.second == p)
        forestBank = 2;
    else if(map->getPorts()[4].second.first == p || map->getPorts()[4].second.second == p)
        fieldBank = 2;
    else if(map->getPorts()[5].second.first == p || map->getPorts()[5].second.second == p){
        if(clayBank!=2) clayBank = 3;
        if(pastureBank!=2) pastureBank = 3;
        if(stoneBank!=2) stoneBank = 3;
        if(forestBank!=2) forestBank = 3;
        if(fieldBank!=2) fieldBank = 3;
    }
    cityCount++;
}


QVector<QPushButton*> Player::getSettlements(){
    return settlements;
}

bool Player::buyCity(){
    if(cityCount > 0)
        return true;
    else{
    QMessageBox::warning(this, tr("warning"), tr("you can't buy a city"));
    return false;
    }
    if(fieldCard > 1 && stoneCard > 2)
        return true;
    else{
        QMessageBox::warning(this, tr("warning"), tr("there is no settleme in board"));
        return false;
    }
}

void Player::updateToCity(QPushButton* p){
    if(buyCity()){
    int i=0;
    for(; i<settlements.size() ;i++){
        if(settlements[i]==p)
            break;
    }
    settlements.removeAt(i);
    p->setEnabled(false);
    cities.push_back(p);
    cityPiece--;
    fieldCard-=2;
    stoneCard-=3;
    totalPoint++;
    cityCount--;
    update();}
}

void Player::addRoad(QPushButton* p){
    roads.push_back(p);
    p->setDisabled(true);
    if(roadPiece < 14){
        clayCard--;
        forestCard--;
    }
    roadPiece--;
    update();
}

void Player::getDevelopmentCard(developmentType dt){
        if(dt==victoryPoint){
            totalPoint++;
            victoryPointCard++;
        }
        else if(dt==Knight){
            KnightCard++;
        }
        else if(dt==roadBuilding){
            roadBuildingCard++;
        }
        else if(dt==yearOfPlenty){
            yearOfPlentyCard++;
        }
        else if(dt==monopoly){
            monopolyCard++;
        }
    fieldCard--;
    pastureCard--;
    stoneCard--;
    update();
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
    update();
    qDebug() << PlayerID << "//////////////////////////";
    qDebug() << "field card ::" << fieldCard ;
    qDebug() << "stone card ::" << stoneCard ;
    qDebug() << "clay card ::" << clayCard ;
    qDebug() << "pasture card ::" << pastureCard ;
    qDebug() << "forest card ::" << forestCard ;
}

void Player::enablePushButtons(bool mode){
   ui->clay->setEnabled(mode);
   ui->forest->setEnabled(mode);
   ui->stone->setEnabled(mode);
   ui->pasture->setEnabled(mode);
   ui->field->setEnabled(mode);
   ui->knight->setEnabled(mode);
   ui->monopoly->setEnabled(mode);
   ui->yearOfPlenty->setEnabled(mode);
   ui->victoryPoint->setEnabled(mode);
   ui->roadBuilding->setEnabled(mode);

   ui->city->setEnabled(mode);
   ui->settlement->setEnabled(mode);
   ui->road->setEnabled(mode);
   ui->turn->setEnabled(mode);
   ui->trade->setEnabled(mode);
   ui->roll->setEnabled(mode);
   ui->development->setEnabled(mode);
}

void Player::giveResourceCard(tileType t){
    qDebug() << "player give res" << t;
    if (t==field && fieldCard >= 1){
        fieldCard--;
    }
    else if(t==stone && stoneCard >= 1){
        stoneCard--;
    }
    else if(t==clay && clayCard >= 1){
        clayCard--;
    }
    else if(t==pasture && pastureCard >= 1){
        pastureCard--;
    }
    else if(t==forest && forestCard >= 1){
        forestCard--;
    }
    update();
}

int Player::giveMonopoly(tileType t){
    int n = 0;
    if (t==field){
        n = fieldCard;
        fieldCard = 0;
    }
    else if(t==stone){
        n = stoneCard;
        stoneCard = 0;
    }
    else if(t==clay){
        n = clayCard;
        clayCard = 0;
    }
    else if(t==pasture){
        n = pastureCard;
        pastureCard = 0;
    }
    else if(t==forest){
        n = forestCard;
        forestCard = 0;
    }
    update();
    return n;
}

void Player::getMonopoly(tileType t, int n){
    if (t==field){
        fieldCard += n ;
    }
    else if(t==stone){
        stoneCard += n;
    }
    else if(t==clay){
        clayCard += n;
    }
    else if(t==pasture){
        pastureCard += n;
    }
    else if(t==forest){
        forestCard += n;
    }
    monopolyCard--;
    update();
}

void Player::useYearOfPlenty(tileType t1,tileType t2){
    getResourceCard(t1);
    getResourceCard(t2);
    yearOfPlentyCard--;
    update();
}

void Player::showRoads(){
    if(buyRoad()){
        for(int i=0;i<roads.size();i++){
            for(int j=0;j<map->getAvailableEdges().size();j++){
                if(abs(roads[i]->x() - map->getAvailableEdges()[j]->x()) < 75 &&
                        abs(roads[i]->y() - map->getAvailableEdges()[j]->y()) < 75){
                    map->getAvailableEdges()[j]->setVisible(true);
                }
            }
        }
        for(int i=0;i<settlements.size();i++){
            for(int j=0;j<map->getAvailableEdges().size();j++){
                if(abs(settlements[i]->x() - map->getAvailableEdges()[j]->x()) < 55 &&
                        abs(settlements[i]->y() - map->getAvailableEdges()[j]->y()) < 55){
                    map->getAvailableEdges()[j]->setVisible(true);
                }
            }
        }
    }
    else QMessageBox::warning(this, tr("Warning"),
                tr("You don't have enough cards to buy a road!"));
}

void Player::showSetllement(){
    if(buySettlement()){
        if(settlementPiece > 3){
            map->setUnHide(map->getAvailableVertexs());
        }
        else{
            for(int i=0; i<roads.size(); i++){
                for(int j=0; j<map->getAvailableVertexs().size(); j++){
                    if(abs(roads[i]->x() - map->getAvailableVertexs()[j]->x()) < 55 &&
                            abs(roads[i]->y() - map->getAvailableVertexs()[j]->y()) < 55){
                        map->getAvailableVertexs()[j]->setVisible(true);
                    }
                }
            }
        }
    }
    else QMessageBox::warning(this, tr("Warning"),
                tr("You don't have enough cards to buy  a house!"));
}

void Player::showCity(){
   if(buyCity()){
       for(int i=0 ; i<settlements.size(); i++)
           settlements[i]->setEnabled(true);
   }
   else QMessageBox::warning(this, tr("Warning"),
              tr("You don't have enough cards to buy  a city!"));
}

bool Player::isSettlement(QPushButton(* p)){
    if(settlements.contains(p))
        return true;
    return false;
}

int Player::isAdjacent(Tile* tile){
    int n=0;
    for(int i=0;i<settlements.size();i++){
        if(abs((tile->getLocation()->x()+65) - (settlements[i]->x()+10) ) < 100 &&
                abs((tile->getLocation()->y()+75) - (settlements[i]->y()+12) ) < 100 ){
            n++;

        }
    }
    for(int i=0;i<cities.size();i++){
        if(abs((tile->getLocation()->x()+65) - (cities[i]->x()+10) ) < 100 &&
                abs((tile->getLocation()->y()+75) - (cities[i]->y()+12) ) < 100 ){
            n+=2;
        }
    }
    return n;
}

QVector<QPair<tileType,int>> Player::getCardsNum(){
    QVector<QPair<tileType,int>> cards {{clay,clayCard}, {field,fieldCard},{forest,forestCard},
                                        {stone,stoneCard},{pasture,pastureCard}};
    return cards;
}

QString Player::getName(){
    return name;
}
bool Player::checkRequset(QVector<QPair<tileType,int>> cards){
    if(cards[0].second > clayCard)
        return false;
    if(cards[1].second > fieldCard)
        return false;
    if(cards[2].second > forestCard)
        return false;
    if(cards[3].second > stoneCard)
        return false;
    if(cards[4].second > pastureCard)
        return false;
    return true;
}
void Player::showRequest(QVector<QPair<tileType,QPair<int,int>>> cards, Player* p){
    Request* requst = new Request(cards,p,this);
    requst->show();
}
int Player::getClayBank(){
    qDebug() << clayBank;
    return  clayBank;
}
int Player::getForestBank(){
    return forestBank;
}
int Player::getStoneBank(){
    return stoneBank;
}
int Player::getPastureBank(){
    return pastureBank;
}
int Player::getFieldBank(){
    return fieldBank;
}
