#include "game.h"
#include "ui_Player.h"
#include "ui_map.h"
#include "ui_login.h"
#include <QDebug>

int Game::diceNum = 2;
int Game::player_ = 0;
int Game::count = 0;

Game::Game(QWidget *parent) :
    QTcpServer(parent)
{
    map = new Map();
//    map->show();

    bank = new Bank(map);

    dice = new Dice(map);

    QPixmap blue(":/new/prefix1/players/blue_person.png");
    QPixmap green(":/new/prefix1/players/green_person.png");
    QPixmap red(":/new/prefix1/players/red_person1.png");
    QPixmap yellow(":/new/prefix1/players/yellow_person.png");

    player1 = new Player(blue , "player 1",bank,map);
    player2 = new Player(green , "player 2",bank,map);
    player3 = new Player(red , "player 3",bank,map);
    player4 = new Player(yellow ,"player 4",bank,map);
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
    robberConnect();
}

void Game::goToLogin(int i){
    if(logins[i]->ui->led_username->text()!="")
          players[i]->setName(logins[i]->ui->led_username->text());
    if(i==0)
    {
        player1->setWindowTitle(players[i]->getName());
        map->ui->label_31->setText(players[i]->getName());
    }
    if(i==1)
    {
        player2->setWindowTitle(players[i]->getName());
        map->ui->label_32->setText(players[i]->getName());
    }
    if(i==2){
        player3->setWindowTitle(players[i]->getName());
        map->ui->label_33->setText(players[i]->getName());
    }
    if(i==3){
        player4->setWindowTitle(players[i]->getName());
        map->ui->label_34->setText(players[i]->getName());
    }
    logins[i]->close();
    players[i]->show();
    if(i!=0)
        players[i]->enablePushButtons(false);
    if(i==3)
        map->show();
}

void Game::gotoRoll(){
    diceNum = dice->roll();
    for(int i=0;i<players.size();i++)
        players[i]->ui->roll->setDisabled(true);
    //map->ui->diceNum->setText(QString::number(diceNum));
    if(diceNum!=7){
        for(int i= 0; i< map->getTokens().size() ; i++){
                map->getTokens()[i]->setEnabled(false);
        }
        giveCardRoll();
    }
    else{
        for(int i= 0; i< map->getTokens().size() ; i++){
            if(map->getTokens()[i] != map->getRobberToken())
                map->getTokens()[i]->setEnabled(true);
        }
    }
}
void Game::robberConnect(){
    for(int i=0;i<map->getTokens().size();i++){
        signalMapper = new QSignalMapper(this);
        connect(map->getTokens()[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(map->getTokens()[i],map->getTokens()[i]);
        connect(signalMapper, SIGNAL(mappedObject(QObject*)),this, SLOT(robberSelected(QObject*)));
    }
}
void Game::robberSelected(QObject* t){
    for(int i=0; i<map->getTokens().size(); i++){
            map->getTokens()[i]->setEnabled(false);
    }
     int pre = map->getTokens().indexOf(map->getRobberToken());
     map->getTiles()[pre]->changeRobber(false);

     QPushButton* token = qobject_cast<QPushButton*>(t);
     int cur = map->getTokens().indexOf(token);
     map->setRobberToken(token);
     map->getTiles()[cur]->changeRobber(true);
     map->ui->robber->move(token->x() + 40 ,token->y() - 30);
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

void Game::setColorForRoads(Player *thePlayer, QPushButton * roadPB) {

    thePlayer->addRoad(roadPB);
    map->removeEdge(roadPB);
    bank->roadBought();
}

/* get selected settlement */
void Game::slectedSetllement(QObject* p){
    QPushButton* house = qobject_cast<QPushButton*>(p);
    if(player1->buySettlement() && player_ == 0){
        QPixmap pixmap_home(":/new/prefix1/pieces/blue_settlement.png");
        setColorForSettlements(player1, pixmap_home, house);
        if(count == 0 || count == 4)
                   player1->ui->settlement->setDisabled(true);
    }
    else if(player2->buySettlement() && player_ == 1){
        QPixmap pixmap_home(":/new/prefix1/pieces/green_settlement.png");
        setColorForSettlements(player2, pixmap_home, house);
        if(count == 1 || count == 5)
                   player1->ui->settlement->setDisabled(true);
    }
    else if(player3->buySettlement() &&player_ == 2){
        QPixmap pixmap_home(":/new/prefix1/pieces/red_settlement.png");
        setColorForSettlements(player3, pixmap_home, house);
        if(count == 2 || count == 6)
                   player3->ui->settlement->setDisabled(true);
    }
    else if(player4->buySettlement() && player_ == 3){
        QPixmap pixmap_home(":/new/prefix1/pieces/yellow_settlement.png");
        setColorForSettlements(player4, pixmap_home, house);
        if(count == 3)
                   player4->ui->settlement->setDisabled(true);
    }
    map->setHide(map->getAvailableVertexs());
}

void Game::slectedCity(QObject* p){
    QPushButton* city = qobject_cast<QPushButton*>(p);
    if(player1->buyCity() && player_ == 0){
        QPixmap pix(":/new/prefix1/pieces/blue_city.png");
        setColorForCities(player1, pix, city);
    }
    else if(player2->buyCity() && player_ == 1){
        QPixmap home(":/new/prefix1/pieces/green_city.png");
        setColorForCities(player2, home, city);
    }
    else if(player3->buyCity() && player_ == 2){
        QPixmap home(":/new/prefix1/pieces/red_city.png");
        setColorForCities(player3, home, city);
    }
    else if(player4->buyCity() && player_ == 3){
        QPixmap home(":/new/prefix1/pieces/yellow_city.png");
        setColorForCities(player4, home, city);
    }
}

void Game::slectedRoad(QObject* p){
    QPushButton* road = qobject_cast<QPushButton*>(p);
    if(player1->buyRoad() && player_ == 0){
        road->setStyleSheet("background-color:rgb(0,21,255)");
        setColorForRoads(player1,  road);
        if(count == 0 || count == 4)
                   player1->ui->road->setDisabled(true);

    }
    else if(player2->buyRoad() && player_ == 1){
        road->setStyleSheet("background-color:rgb(28,137,66)");
        setColorForRoads(player2,  road);
        if(count == 1 || count == 5)
                   player2->ui->settlement->setDisabled(true);

    }
    else if(player3->buyRoad() && player_ == 2){
        road->setStyleSheet("background-color:rgb(255,0,0)");
        setColorForRoads(player3, road);
        if(count == 2 || count == 6)
                   player3->ui->settlement->setDisabled(true);
    }
    else if(player4->buyRoad() && player_ == 3){
        road->setStyleSheet("background-color:rgb(255,238,0)");
        setColorForRoads(player4, road);
        if(count == 3)
                   player4->ui->settlement->setDisabled(true);
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
    QJsonArray a;
    QJsonObject p1,p2,p3,p4;
    p1["name"] = player1->getName();
    p1["id"] = 0;
    p2["name"] = player2->getName();
    p2["id"] = 1;
    p3["name"] = player3->getName();
    p3["id"] = 2;
    p4["name"] = player4->getName();
    p4["id"] = 3;
    a.append(p1);
    a.append(p2);
    a.append(p3);
    a.append(p4);
    a.append(i);
    a.append(players[i]->getClayBank());
    a.append(players[i]->getFieldBank());
    a.append(players[i]->getForestBank());
    a.append(players[i]->getStoneBank());
    a.append(players[i]->getPastureBank());
    a.append(players[i]->getCardsNum()[0].second);
    a.append(players[i]->getCardsNum()[1].second);
    a.append(players[i]->getCardsNum()[2].second);
    a.append(players[i]->getCardsNum()[3].second);
    a.append(players[i]->getCardsNum()[4].second);

    QJsonDocument d(a);
    QFile f("/Users/macbook/Desktop/1.json");
    f.open(QIODevice::WriteOnly);
    f.write(d.toJson());
    emit write(d.toJson());
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

void Game::changeTurn(Player* pre,Player* cur){
    map->ui->playing->setText(cur->getName() + " turn");
    pre->enablePushButtons(false);
    cur->enablePushButtons(true);
    checkLargestArmy();
    cur->update();
    if(count < 6)
        cur->ui->roll->setDisabled(true);
    count++;
}

void Game::playerTurn(){
    player1->enablePushButtons(false);
    player2->enablePushButtons(false);
    player3->enablePushButtons(false);
    player4->enablePushButtons(false);
    if(player_==0)
        map->ui->label_39->setText(QString::number(player1->getTotalPoint()));
    if(player_==1)
        map->ui->label_40->setText(QString::number(player2->getTotalPoint()));
    if(player_==2)
        map->ui->label_41->setText(QString::number(player3->getTotalPoint()));
    if(player_==3)
        map->ui->label_42->setText(QString::number(player4->getTotalPoint()));
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
        changeTurn(player4,player4);
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

void Game::sort(QVector<QPair<QString , int>> players_score){
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

void Game::checkLargestArmy(){

    QVector<QPair<QString , int>> knights_numbers{{"player1" , player1->getKnights()} , {"player2" , player2->getKnights()} , {"player3" , player3->getKnights()} , {"player4" , player4->getKnights()}};
    sort(knights_numbers);
    if(knights_numbers[0].second != knights_numbers[1].second){
       if(knights_numbers[0].first == "player1" && knights_numbers[0].second >= 3){

            player1->setLargestArmy(true);
            player2->setLargestArmy(false);
            player2->setLargestArmy(false);
            player2->setLargestArmy(false);

       }
       if(knights_numbers[0].first == "player2" && knights_numbers[0].second >= 3){
            player1->setLargestArmy(false);
            player2->setLargestArmy(true);
            player2->setLargestArmy(false);
            player2->setLargestArmy(false);

       }
       if(knights_numbers[0].first == "player3" && knights_numbers[0].second >= 3){
            player1->setLargestArmy(false);
            player2->setLargestArmy(false);
            player2->setLargestArmy(true);
            player2->setLargestArmy(false);

       }
       if(knights_numbers[0].first == "player4" && knights_numbers[0].second >= 3){
            player1->setLargestArmy(false);
            player2->setLargestArmy(false);
            player2->setLargestArmy(false);
            player2->setLargestArmy(true);

       }
       for(int i = 0; i < players.size(); i++){
           players[i]->update();
       }

    }
}

void Game::showWinner(){
   winners* w = new winners();
    QVector<QPair< QString , int>> players_score{{player1->getName() , player1->getTotalPoint()} , {player2->getName() , player2->getTotalPoint()} , {player3->getName() , player3->getTotalPoint()} , {player4->getName() , player4->getTotalPoint()}};
    sort(players_score);
    player1->close();
    player2->close();
    player3->close();
    player4->close();
    map->close();

    w->show();
   w->showWinners(players_score);
}

void Game::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    Worker *worker=new Worker(socketDescriptor);
    QThread *workerThread=new QThread;
    workerThreads.append(workerThread);
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this,SIGNAL(write(QByteArray)),worker,SLOT(writeToSocket(QByteArray)));
    connect(worker,SIGNAL(readFromSocket(QJsonDocument,qintptr)),this,SLOT(read(QJsonDocument,qintptr)));
    connect(this, &Game::run, worker, &Worker::start);
    workerThread->start();
    emit run();
}

void Game::startServer()
{  int port = 9000;
    if (!this->listen(QHostAddress::Any, port)) {
      qDebug() << "Could not start server";
    } else {
      qDebug() << "Listening to port " << port << "...";
    }
}

int Game::givePlayerId(QString name){
    for(int i=0;i<players.size();i++){
        if(name == players[i]->getName())
            return i;
    }
}
void Game::read(QJsonDocument a, qintptr descriptor)
{
    QVector<int> toWho {a[0].toBool(),a[1].toBool(),a[2].toBool(),a[3].toBool()};
    QVector<QPair<tileType,QPair<int,int>>> cards {
        {clay,{a[4].toInt(),a[9].toInt()}},
        {field,{a[5].toInt(),a[10].toInt()}},
        {forest,{a[6].toInt(),a[11].toInt()}},
        {stone,{a[7].toInt(),a[12].toInt()}},
        {pasture,{a[8].toInt(),a[13].toInt()}} };
    int playerId = a[14].toInt();
        if(toWho[3]){
            for(int i=0;i<cards.size();i++){
                if(cards[i].second.first != 0){
                    for(int j=0;j<cards[i].second.first;j++){
                        bank->getCardFromPlayer(cards[i].first);
                        players[playerId]->giveResourceCard(cards[i].first);
                    }
                }
                if(cards[i].second.second == 1){
                    bank->giveResCardToPlayer(cards[i].first);
                    players[playerId]->getResourceCard(cards[i].first);
                }
            }
        }
        QVector<QPair<tileType,int>> p2Cards {{clay,a[9].toInt()},{field,a[10].toInt()},
            {forest,a[11].toInt()},{stone,a[12].toInt()},{pasture,a[13].toInt()}};

        if(toWho[0] && players[givePlayerId(a[15].toString())]->checkRequset(p2Cards))
            players[givePlayerId(a[15].toString())]->showRequest(cards,players[playerId]);

        if(toWho[1] && players[givePlayerId(a[16].toString())]->checkRequset(p2Cards))
            players[givePlayerId(a[16].toString())]->showRequest(cards,players[playerId]);

        if(toWho[2] && players[givePlayerId(a[17].toString())]->checkRequset(p2Cards))
            players[givePlayerId(a[17].toString())]->showRequest(cards,players[playerId]);
}
Game::~Game(){
    delete map;
    delete bank;
    delete dice;
    delete player1;
    delete player2;
    delete player3;
    delete player4;
    for(auto &workerThread:workerThreads){
        workerThread->quit();
        workerThread->wait();
        delete workerThread;
    }
}
