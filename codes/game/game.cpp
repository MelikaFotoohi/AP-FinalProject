#include "game.h"
#include "ui_player.h"
#include "ui_Map.h"
#include "ui_login.h"
#include <QDebug>

int Game::diceNum = 2;
int Game::gameStarted_ = 0;
int Game::player_ = 0;


Game::Game(QWidget *parent) :
    QMainWindow(parent)

{
    map = new Map();
    map->show();

    bank = new Bank();

    dice = new Dice(map);
    player1 = new Player("player 1",map);
    player2 = new Player("player 2",map);
    player3 = new Player("player 3",map);
    player4 = new Player("player 4",map);
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    Login* l1 = new Login();
    Login* l2 = new Login();
    Login* l3 = new Login();
    Login* l4 = new Login();
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

        tradeConnect(i);
    }
    settlementConnect();
    roadConnect();
    monopolyConnect();
    yearOfPlentyConnect();
    connect(map->ui->Dice_1 , SIGNAL(clicked()) , this , SLOT(gotoRoll()));
    connect(map->ui->Dice_2 , SIGNAL(clicked()) , this , SLOT(gotoRoll()));
}
void Game::goToLogin(int i){
    players[i]->setName(logins[i]->ui->led_username->text());
    logins[i]->close();
    players[i]->show();

}

void Game::gotoRoll(){

    diceNum = dice->roll();
    giveCardRoll();
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
    players[i]->getResourceCard(bank->giveResCard());
    players[i]->getResourceCard(bank->giveResCard());
}

/*give card after dice rolled*/
void Game::giveCardRoll(){

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


/* get selected settlement */
void Game::slectedSetllement(QObject* p){
    QPushButton* house = qobject_cast<QPushButton*>(p);
    if(player1->buySettlement() && player_ == 0){
        QPixmap pixmap_home("/Users/golnoush/Desktop/University/term 2/AP/AP_project/red_settlement.png");
        QIcon homeIcon(pixmap_home);
        house->setIcon(homeIcon);
        house->setIconSize(pixmap_home.rect().size());
        player1->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    else if(player2->buySettlement() && player_ == 1){
        QPixmap pixmap_home("/Users/golnoush/Desktop/University/term 2/AP/AP_project/green_settlement.png");
        QIcon homeIcon(pixmap_home);
        house->setIcon(homeIcon);
        house->setIconSize(pixmap_home.rect().size());
        player2->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();
    }
    else if(player3->buySettlement() &&player_ == 2){
        QPixmap pixmap_home("/Users/golnoush/Desktop/University/term 2/AP/AP_project/blue_settlement.png");
        QIcon homeIcon(pixmap_home);
        house->setIcon(homeIcon);
        house->setIconSize(pixmap_home.rect().size());
        player3->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();

    }
    else if(player4->buySettlement() && player_ == 3){
        QPixmap pixmap_home("/Users/golnoush/Desktop/University/term 2/AP/AP_project/yellow_settlement.png");
        QIcon homeIcon(pixmap_home);
        house->setIcon(homeIcon);
        house->setIconSize(pixmap_home.rect().size());
        player4->addSettlement(house);
        map->removeVertex(house);
        bank->settlementBought();

    }
    map->setHide(map->getAvailableVertexs());
}

void Game::slectedCity(QObject* p){
    QPushButton* city = qobject_cast<QPushButton*>(p);
    if(player1->buyCity() && player_ == 0){
        QPixmap pix("/Users/macbook/Desktop/images/pieces/blue_city.jpg");
        QIcon icon(pix);
        city->setIcon(icon);
        city->setIconSize(pix.rect().size());
        player1->updateToCity(city);
        bank->cityBought();
    }
    else if(player2->buyCity() && player_ == 1){
        QPixmap home("/Users/macbook/Desktop/images/pieces/green_city.jpg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player2->updateToCity(city);
        bank->cityBought();
    }
    else if(player3->buyCity() && player_ == 2){
        QPixmap home("/Users/macbook/Desktop/images/pieces/red_city.jpg");
        QIcon homeIcon(home);
        city->setIcon(homeIcon);
        city->setIconSize(home.rect().size());
        player2->updateToCity(city);
        bank->cityBought();
    }
    else if(player4->buyCity() && player_ == 3){
        QPixmap home("/Users/macbook/Desktop/images/pieces/yellow_city.jpg");
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
        QPixmap pixmap_road("/Users/golnoush/Desktop/University/term 2/AP/AP_project/red_road.png");
        QIcon roadIcon(pixmap_road);
        road->setIcon(roadIcon);
        road->setIconSize(pixmap_road.rect().size());
        player1->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player2->buyRoad() && player_ == 1){
        QPixmap pixmap_road("/Users/golnoush/Desktop/University/term 2/AP/AP_project/green_road.png");
        QIcon roadIcon(pixmap_road);
        road->setIcon(roadIcon);
        road->setIconSize(pixmap_road.rect().size());
        player2->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player3->buyRoad() && player_ == 2){
        QPixmap pixmap_road("/Users/golnoush/Desktop/University/term 2/AP/AP_project/blue_road.png");
        QIcon roadIcon(pixmap_road);
        road->setIcon(roadIcon);
        road->setIconSize(pixmap_road.rect().size());
        player3->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
    }
    else if(player4->buyRoad() && player_ == 3){
        QPixmap pixmap_road("/Users/golnoush/Desktop/University/term 2/AP/AP_project/yellow_road.png");
        QIcon roadIcon(pixmap_road);
        road->setIcon(roadIcon);
        road->setIconSize(pixmap_road.rect().size());
        player4->addRoad(road);
        map->removeEdge(road);
        bank->roadBought();
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
    QAbstractButton* pstone = msgBox.addButton(tr("ORE"), QMessageBox::YesRole);
    QAbstractButton* pclay = msgBox.addButton(tr("BRICK"), QMessageBox::YesRole);
    QAbstractButton* pfield = msgBox.addButton(tr("WHEAT"), QMessageBox::YesRole);
    QAbstractButton* pforest = msgBox.addButton(tr("WOOD"), QMessageBox::YesRole);
    QAbstractButton* ppasture = msgBox.addButton(tr("SHEEP"), QMessageBox::YesRole);

    msgBox.exec();
    int num=0;
    if (msgBox.clickedButton()==pstone) {
        for(int i=0;i<players.size();i++){
            if(n!=i){
               num += players[i]->giveMonopoly(stone);
            }
        }
        players[n]->getMonopoly(stone,num);
    }
    if (msgBox.clickedButton()==pclay){
        for(int i=0;i<players.size();i++){
            if(n!=i){
               num += players[i]->giveMonopoly(clay);
            }
        }
        players[n]->getMonopoly(clay,num);
    }
    if (msgBox.clickedButton()==pfield){
        for(int i=0;i<players.size();i++){
            if(n!=i){
               num += players[i]->giveMonopoly(field);
            }
        }
        players[n]->getMonopoly(field,num);
    }
    if (msgBox.clickedButton()==pforest){
        for(int i=0;i<players.size();i++){
            if(n!=i){
               num += players[i]->giveMonopoly(forest);
            }
        }
        players[n]->getMonopoly(forest,num);
    }
    if (msgBox.clickedButton()==ppasture){
        for(int i=0;i<players.size();i++){
            if(n!=i){
               num += players[i]->giveMonopoly(pasture);
            }
        }
        players[n]->getMonopoly(pasture,num);
    }
}

void Game::startGame(){

}

void Game::playerTurn(){
    if(player_ == 0){
        player_ = 1;
        player1->enablePushButtons(false);
        player2->enablePushButtons(true);
        player3->enablePushButtons(false);
        player1->enablePushButtons(false);

    }else if(player_ == 1){

        player_ = 2;
        player1->enablePushButtons(false);
        player2->enablePushButtons(false);
        player3->enablePushButtons(true);
        player1->enablePushButtons(false);
    }else if(player_ == 2){

        player_ = 3;
        player1->enablePushButtons(false);
        player2->enablePushButtons(false);
        player3->enablePushButtons(false);
        player1->enablePushButtons(true);
    }else if(player_ == 3){

        player_ = 0;
        player1->enablePushButtons(true);
        player2->enablePushButtons(false);
        player3->enablePushButtons(false);
        player1->enablePushButtons(false);
    }
    checkWinner();
}



void Game::checkWinner(){
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

    winners* w = new winners();
    QVector<QPair< QString , int>> players_score{{"player1" , player1->getTotalPoint()} , {"player2" , player2->getTotalPoint()} , {"player3" , player3->getTotalPoint()} , {"player4" , player4->getTotalPoint()}};
    sort(players_score);
    player1->close();
    player2->close();
    player3->close();
    player4->close();
    map->close();

    w->show();
    w->showWinners(players_score);



}
