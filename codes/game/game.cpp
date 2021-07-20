#include "game.h"
#include "ui_Player.h"
#include "ui_map.h"
#include "ui_login.h"
#include <QDebug>

int Game::diceNum = 2;
int Game::gameStarted_ = 0;
int Game::player_ = 0;
int Game::count = 0;

Game::Game(QWidget *parent) :
    QMainWindow(parent)
{
    map = new Map();
    map->show();

    bank = new Bank(map);

    dice = new Dice(map);

    player1 = new Player("player 1",bank,map);
    player2 = new Player("player 2",bank,map);
    player3 = new Player("player 3",bank,map);
    player4 = new Player("player 4",bank,map);
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    login* l1 = new login();
    login* l2 = new login();
    login* l3 = new login();
    login* l4 = new login();
    logins.push_back(l1);
    logins.push_back(l2);
    logins.push_back(l3);
    logins.push_back(l4);
    l1->show();
    l2->show();
    l3->show();
    l4->show();

    for(int i=0;i<logins.size();i++){
        signalMapper = new QSignalMapper(this);
        connect(logins[i]->ui->start,SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(logins[i]->ui->start,i);
        connect(signalMapper, SIGNAL(mappedInt(int)),this, SLOT(goToLogin(int)));
    }

    for(int i=0;i<players.size();i++){
        connect(players[i]->ui->turn,SIGNAL(clicked()),this,SLOT(playerTurn()));
        connect(players[i]->ui->development,SIGNAL(clicked()),this,SLOT(getDevelopment()));
        connect(players[i]->ui->roll , SIGNAL(clicked()) , this , SLOT(gotoRoll()));
        tradeConnect(i);
    }
    settlementConnect();
    roadConnect();
    monopolyConnect();
    yearOfPlentyConnect();
}
void Game::goToLogin(int i){
    players[i]->setName(QString::number(i));
    logins[i]->close();
    players[i]->show();
    if(i!=0)
        players[i]->enablePushButtons(false);
}
void Game::gotoRoll(){
    diceNum = dice->roll();
    map->ui->diceNum->setText(QString::number(diceNum));
    giveCardRoll();
//    for(int i=0;i<players.size();i++)
//        players[i]->ui->roll->setDisabled(true);
}

void Game::monopolyConnect(){
    for(int i=0;i<players.size();i++){
        signalMapper = new QSignalMapper(this);
        connect(players[i]->ui->monopoly,SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(players[i]->ui->monopoly,i);
        connect(signalMapper, SIGNAL(mappedInt(int)),this, SLOT(getMonopoly(int)));
    }
}
void Game::yearOfPlentyConnect(){
    for(int i=0;i<players.size();i++){
        signalMapper = new QSignalMapper(this);
        connect(players[i]->ui->yearOfPlenty,SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(players[i]->ui->yearOfPlenty,i);
        connect(signalMapper, SIGNAL(mappedInt(int)),this, SLOT(getYeatOfPlenty(int)));
    }
}

void Game::getYeatOfPlenty(int i){
    tileType t1 = bank->giveResCard();
    tileType t2 = bank->giveResCard();
    players[i]->useYearOfPlenty(t1,t2);
}

/*give card after dice rolled*/
void Game::giveCardRoll(){
    QVector<Tile*> tiles = map->getTiles();
    for(int i=0; i<map->getTiles().size(); i++){
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
        connect(signalMapper, SIGNAL(mappedObject(QObject*)),this, SLOT(slectedBuilding(QObject*)));
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
        if(players[i]->isSettlement(building)){
            isSettlement = i;
            break;
        }
    }
    if(isSettlement == -1)
        slectedSetllement(building);
    else{
        if(player_ == isSettlement)
            slectedCity(building);
    }
   // if(player_==0 && player1->isSettlement(building))
}

void Game::setColorForSettlements(Player* thePlayer, QPixmap pixmap, QPushButton* housePB) {
    QIcon icon(pixmap);
    housePB->setIcon(icon);
    housePB->setIconSize(pixmap.rect().size());
    thePlayer->addSettlement(housePB);
    map->removeVertex(housePB);
    bank->settlementBought();
}

void Game::setColorForCities(Player * thePlayer, QPixmap pixmap, QPushButton * cityPB) {
    QIcon homeIcon(pixmap);
    cityPB->setIcon(homeIcon);
    cityPB->setIconSize(pixmap.rect().size());
    thePlayer->updateToCity(cityPB);
    bank->cityBought();
}

void Game::setColorForRoads(Player *thePlayer, QPixmap pixmap, QPushButton * roadPB) {
    QIcon roadIcon(pixmap);
    roadPB->setIcon(roadIcon);
    roadPB->setIconSize(pixmap.rect().size());
    thePlayer->addRoad(roadPB);
    map->removeEdge(roadPB);
    bank->roadBought();
}

/* get selected settlement */
void Game::slectedSetllement(QObject* p){
    QPushButton* house = qobject_cast<QPushButton*>(p);
    if(player1->buySettlement() && player_ == 0){
        QPixmap pixmap_home("/Users/macbook/Desktop/images/pieces/blue_house.png");
        setColorForSettlements(player1, pixmap_home, house);
    }
    else if(player2->buySettlement() && player_ == 1){
        QPixmap pixmap_home("/Users/macbook/Desktop/images/pieces/green_house.png");
        setColorForSettlements(player2, pixmap_home, house);
    }
    else if(player3->buySettlement() &&player_ == 2){
        QPixmap pixmap_home("/Users/macbook/Desktop/images/pieces/red_house.png");
        setColorForSettlements(player3, pixmap_home, house);
    }
    else if(player4->buySettlement() && player_ == 3){
        QPixmap pixmap_home("/Users/macbook/Desktop/images/pieces/yellow_house.png");
        setColorForSettlements(player4, pixmap_home, house);
    }
    map->setHide(map->getAvailableVertexs());
}

void Game::slectedCity(QObject* p){
    QPushButton* city = qobject_cast<QPushButton*>(p);
    if(player1->buyCity() && player_ == 0){
        QPixmap pix("/Users/macbook/Desktop/images/pieces/blue_city.jpg");
        setColorForCities(player1, pix, city);
    }
    else if(player2->buyCity() && player_ == 1){
        QPixmap home("/Users/macbook/Desktop/images/pieces/green_city.jpg");
        setColorForCities(player2, home, city);
    }
    else if(player3->buyCity() && player_ == 2){
        QPixmap home("/Users/macbook/Desktop/images/pieces/red_city.jpg");
        setColorForCities(player3, home, city);
    }
    else if(player4->buyCity() && player_ == 3){
        QPixmap home("/Users/macbook/Desktop/images/pieces/yellow_city.jpg");
        setColorForCities(player4, home, city);
    }
}

void Game::slectedRoad(QObject* p){
    QPushButton* road = qobject_cast<QPushButton*>(p);
    if(player1->buyRoad() && player_ == 0){
        QPixmap pixmap_road("/Users/macbook/Desktop/images/pieces/blue_road.png");
        setColorForRoads(player1, pixmap_road, road);
    }
    else if(player2->buyRoad() && player_ == 1){
        QPixmap pixmap_road("/Users/macbook/Desktop/images/pieces/green_road.png");
        setColorForRoads(player2, pixmap_road, road);
    }
    else if(player3->buyRoad() && player_ == 2){
        QPixmap pixmap_road("/Users/macbook/Desktop/images/pieces/red_road.png");
        setColorForRoads(player3, pixmap_road, road);
    }
    else if(player4->buyRoad() && player_ == 3){
        QPixmap pixmap_road("/Users/macbook/Desktop/images/pieces/yellow_road.png");
        setColorForRoads(player4, pixmap_road, road);
    }
    map->setHide(map->getAvailableEdges());
}

void Game::tradeConnect(int i){
    signalMapper = new QSignalMapper(this);
    connect(players[i]->ui->trade,SIGNAL(clicked()),signalMapper,SLOT(map()));
    signalMapper->setMapping(players[i]->ui->trade,i);
    connect(signalMapper, SIGNAL(mappedInt(int)),this, SLOT(goToTradeWindow(int)));
}

void Game::goToTradeWindow(int i)
{
    Trade *trade = new Trade(bank,players,i,map);
    players[i]->close();
    trade->show();
}

void Game::getDevelopment(){
    if(player_ == 0 && player1->buyDevelopment()){
        developmentType dt = bank->giveDevCardToPlayer();
        player1->getDevelopmentCard(dt);
    }
    if(player_ == 1 && player2->buyDevelopment()){
        developmentType dt = bank->giveDevCardToPlayer();
        player2->getDevelopmentCard(dt);
    }
    if(player_ == 2 && player3->buyDevelopment()){
        developmentType dt = bank->giveDevCardToPlayer();
        player3->getDevelopmentCard(dt);
    }
    if(player_ == 3 && player4->buyDevelopment()){
        developmentType dt = bank->giveDevCardToPlayer();
        player4->getDevelopmentCard(dt);
    }
}

void Game::getMonopoly(int n){

    QMessageBox msgBox;
    msgBox.setText(tr("Choose a resource"));
    QAbstractButton* pstone = msgBox.addButton(tr("Ore"), QMessageBox::YesRole);
    QAbstractButton* pclay = msgBox.addButton(tr("Brick"), QMessageBox::YesRole);
    QAbstractButton* pfield = msgBox.addButton(tr("Wheat"), QMessageBox::YesRole);
    QAbstractButton* pforest = msgBox.addButton(tr("Wood"), QMessageBox::YesRole);
    QAbstractButton* ppasture = msgBox.addButton(tr("Sheep"), QMessageBox::YesRole);
    QAbstractButton* pcancel = msgBox.addButton(tr("CANCEL"), QMessageBox::YesRole);

    msgBox.exec();
    int num=0;
    if(msgBox.clickedButton()==pcancel)
        return;

    if (msgBox.clickedButton()==pstone)
        checkGettingMonopoly(stone, n , num);

    if (msgBox.clickedButton()==pclay)
        checkGettingMonopoly(clay, n , num);

    if (msgBox.clickedButton()==pfield)
        checkGettingMonopoly(field, n , num);

    if (msgBox.clickedButton()==pforest)
        checkGettingMonopoly(forest, n , num);

    if (msgBox.clickedButton()==ppasture)
        checkGettingMonopoly(pasture, n , num);
}
void Game::checkGettingMonopoly(tileType type, int n , int num)
{
    num =0;
    for(int i=0;i<players.size();i++){
        if(n!=i){
           num += players[i]->giveMonopoly(type);
        }
    }
    players[n]->getMonopoly(type,num);
}
void Game::startGame(){

}
void Game::changeTurn(Player* pre,Player* cur){
    map->ui->playing->setText(cur->getName() + " turn");
    pre->enablePushButtons(false);
    cur->enablePushButtons(true);
    count++;
}
void Game::playerTurn(){
    player1->enablePushButtons(false);
    player2->enablePushButtons(false);
    player3->enablePushButtons(false);
    player4->enablePushButtons(false);
    if(count < 4){
    if(player_ == 0){
        player_ = 1;
        changeTurn(player1,player2);
    }
    else if(player_ == 1){
        player_ = 2;
        changeTurn(player2,player3);
    }
    else if(player_ == 2){
        player_ = 3;
        changeTurn(player3,player4);
    }
    else if(player_ == 3){
        player_ = 3;
        count++;
    }
    checkWining();
    }

    else if(count < 8){
        if(player_ == 3){
            player_ = 2;
            changeTurn(player4,player3);
        }
        else if(player_ == 2){
            player_ = 1;
            changeTurn(player3,player2);
        }
        else if(player_ == 1){
            player_ = 0;
            changeTurn(player2,player1);
        }
        else if(player_ == 0){
            player_ = 1;
            changeTurn(player1,player2);
        }
        checkWining();
    }

    else{
        if(player_ == 0){
            player_ = 1;
            changeTurn(player1,player2);
        }
        else if(player_ == 1){
            player_ = 2;
            changeTurn(player2,player3);
        }
        else if(player_ == 2){
            player_ = 3;
            changeTurn(player3,player4);
        }
        else if(player_ == 3){
            player_ = 0;
            changeTurn(player4,player1);
        }
    }
}

void Game::checkWining(){
    if(player_ == 0 && player1->getTotalPoint() >= 10)
        showWinner();

    if(player_ == 1 && player2->getTotalPoint() >= 10)
        showWinner();

    if(player_ == 2 && player3->getTotalPoint() >= 10)
        showWinner();

    if(player_ == 3 && player4->getTotalPoint() >= 10)
        showWinner();

}
void sort(QVector<QPair<QString , int>> players_score){
    int temp;
    for(int i = 0; i < players_score.size(); i++){
        for(int j = 1; j < players_score.size(); j++){
            if(players_score[j].second > players_score[i].second){
                temp = players_score[i].second;
                players_score[i].second = players_score[j].second;
                players_score[j].second = temp;
            }
        }
    }
}
void Game::showWinner(){
//    winners* w = new winners();
    QVector<QPair< QString , int>> players_score{{"player1" , player1->getTotalPoint()} , {"player2" , player2->getTotalPoint()} , {"player3" , player3->getTotalPoint()} , {"player4" , player4->getTotalPoint()}};
    sort(players_score);
    player1->close();
    player2->close();
    player3->close();
    player4->close();
    map->close();

//    w->show();
//    w->showWinners(players_score);
}
