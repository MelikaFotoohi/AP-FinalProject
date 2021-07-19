#include "player.h"
#include "ui_player.h"
#include "request.h"


Player::Player(QString _name, Map* _map,QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::Player)
{
    map = _map;
    ui->setupUi(this);
    this->setFixedSize(630,380);
    ui->victoryPoint->setEnabled(false);
    ui->knight->setEnabled(false);
    update();

    this->centralWidget()->setStyleSheet( "background-image:url(\"/22.jpg\"); background-position: center;");




    QPixmap pixmap("/brick2.jpg");
    QIcon ButtonIcon(pixmap);
    setIconForPushButton(pixmap, ButtonIcon, ui->clay);

    QPixmap pixmap2("/grain2.jpg");
    QIcon ButtonIcon2(pixmap2);
    setIconForPushButton(pixmap2, ButtonIcon2, ui->field);

    QPixmap pixmap3("/lumber2.jpg");
    QIcon ButtonIcon3(pixmap3);
    setIconForPushButton(pixmap3, ButtonIcon3, ui->forest);

    QPixmap pixmap4("/ore2.jpg");
    QIcon ButtonIcon4(pixmap4);
    setIconForPushButton(pixmap4, ButtonIcon4, ui->stone);

    QPixmap pixmap5("/wool2.jpg");
    QIcon ButtonIcon5(pixmap5);
    setIconForPushButton(pixmap5, ButtonIcon5, ui->pasture);

    QPixmap pixmap6("/knight1.jpg");
    QIcon ButtonIcon6(pixmap6);
    setIconForPushButton(pixmap6, ButtonIcon6, ui->knight);

    QPixmap pixmap7("/monopoly1.jpg");
    QIcon ButtonIcon7(pixmap7);
    setIconForPushButton(pixmap7, ButtonIcon7, ui->monopoly);

    QPixmap pixmap8("/road_buildings1.jpg");
    QIcon ButtonIcon8(pixmap8);
    setIconForPushButton(pixmap8, ButtonIcon8, ui->roadBuilding);

    QPixmap pixmap9("/year_of_plenty1.jpg");
    QIcon ButtonIcon9(pixmap9);
    setIconForPushButton(pixmap9, ButtonIcon9, ui->yearOfPlenty);

    QPixmap pixmap10("/victory_point21.jpg");
    QIcon ButtonIcon10(pixmap10);
    setIconForPushButton(pixmap10, ButtonIcon10, ui->victoryPoint);

    QPixmap pixmap13("/road4.jpg");
    QIcon ButtonIcon13(pixmap13);
    setIconForPushButton(pixmap13, ButtonIcon13, ui->road);

    QPixmap pixmap14("/city2.jpg");
    QIcon ButtonIcon14(pixmap14);
    setIconForPushButton(pixmap14, ButtonIcon14, ui->city);

    QPixmap pixmap15("/house1.jpg");
    QIcon ButtonIcon15(pixmap15);
    setIconForPushButton(pixmap15, ButtonIcon15, ui->settlement);

    QPixmap pixmap16("/trade_icon.png");
    QIcon ButtonIcon16(pixmap16);
    setIconForPushButton(pixmap16, ButtonIcon16, ui->trade
                         );

    connect(ui->road, SIGNAL(clicked()), this, SLOT(showRoads()));
    connect(ui->settlement, SIGNAL(clicked()), this, SLOT(showSetllement()));
    connect(ui->city, SIGNAL(clicked()), this, SLOT(showCity()));


}

void Player::setName(QString _name){
    name = _name;
}

void Player::update(){
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
    QMessageBox::warning(this, tr("warning"), tr("you cant buy a development card"));
    return false;
}

bool Player::buySettlement(){


    if(settlementPiece > 3){
        return true;
    }
    if(!clayCard && !forestCard && !pastureCard && !fieldCard){
        return true;
    }
    QMessageBox::warning(this, tr("warning"), tr("you can't buy a settlement"));
    return false;


}
bool Player::buyRoad(){
    if(settlementPiece > 13){
        return true;
    }
    if(clayCard && forestCard){
        return true;
    }
    QMessageBox::warning(this, tr("warning"), tr("you can't buy a road"));
    return false;
}

void Player::addSettlement(QPushButton* p){
    settlements.push_back(p);

    totalPoint++;
    if(settlementPiece < 4){

        forestCard--;
        pastureCard--;
        fieldCard--;
        clayCard--;
    }
     settlementPiece--;
     update();
    qDebug() << "settlemt added";
}
QVector<QPushButton*> Player::getSettlements(){
    return settlements;

}

bool Player::buyCity(){
    if(fieldCard > 1 && stoneCard > 2)
        return true;
    QMessageBox::warning(this, tr("warning"), tr("you can't buy a city"));
    return false;

}

void Player::updateToCity(QPushButton* p){
    int i=0;
    for(;i<settlements.size();i++){
        if(settlements[i]==p)
            break;
    }
    settlements.removeAt(i);
    p->setEnabled(false);
    cities.push_back(p);
    cityPiece--;
    totalPoint++;
    update();
}

void Player::addRoad(QPushButton* p){
    roads.push_back(p);
    if(roadPiece < 14){
        clayCard--;
        forestCard--;
    }
    roadPiece--;
    update();
}


void Player::getDevelopmentCard(developmentType dt){

        if(dt==victoryPoint){
            qDebug() << "1";
            totalPoint++;
            victoryPointCard++;
        }
        else if(dt==Knight){
            qDebug() << "2";
            KnightCard++;
        }
        else if(dt==roadBuilding){
            qDebug() << "5";
            roadBuildingCard++;
        }
        else if(dt==yearOfPlenty){
            qDebug() << "3";
            yearOfPlentyCard++;
        }
        else if(dt==monopoly){
            qDebug() << "4";
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
}

void Player::giveResourceCard(tileType t){
    if (t==field && fieldCard >= 1){
        fieldCard--;
    }
    else if(t==stone && fieldCard >= 1){
        stoneCard--;
    }
    else if(t==clay && fieldCard >= 1){
        clayCard--;
    }
    else if(t==pasture && fieldCard >= 1){
        pastureCard--;
    }
    else if(t==forest && fieldCard >= 1){
        forestCard--;
    }
    update();
}

int Player::giveMonopoly(tileType t){
    int n;
    if (t==field){
        n = fieldCard;
        fieldCard = 0;
        update();
        qDebug() << n;
        return n;
    }
    else if(t==stone){
        n = stoneCard;
        stoneCard = 0;
        update();
        return n;
    }
    else if(t==clay){
        n = clayCard;
        clayCard = 0;
        update();
        return n;
    }
    else if(t==pasture){
        n = pastureCard;
        pastureCard = 0;
        update();
        return n;
    }
    else if(t==forest){
        n = forestCard;
        forestCard = 0;
        update();
        return n;
    }
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
QJsonArray toJson(const std::vector<unsigned short>& myVec) {
    QJsonArray result;
    std::copy (myVec.begin(), myVec.end(), std::back_inserter(result));
    return result;
}


void Player::showRoads(){
    if(buyRoad())
        map->setUnHide(map->getAvailableEdges());
    else QMessageBox::warning(this, tr("Warning"),
                tr("You don't have enough cards to buy a road!"));
}

void Player::showSetllement(){
    if(buySettlement())
         map->setUnHide(map->getAvailableVertexs());
    else QMessageBox::warning(this, tr("Warning"),
                tr("You don't have enough cards to buy  a house!"));
}

void Player::showCity(){
   if(buyCity())
       map->setUnHide(settlements);
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
        qDebug() << tile;
        qDebug() << tile->getLocation()->x() << "  " << tile->getLocation()->y() << "  "  ;
        qDebug() << settlements[i]->x() << "  " << settlements[i]->y();
        if(abs((tile->getLocation()->x()+85) - (settlements[i]->x()+10) ) < 100 && abs((tile->getLocation()->y()+75) - (settlements[i]->y()+12) ) < 100 ){
            n++;
            qDebug() << "is adjacent";
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

void Player::showRequest(QVector<QPair<tileType,QPair<int,int>>> cards, Player* p){
    Request* requst = new Request(cards,p,this);
    requst->show();
}
