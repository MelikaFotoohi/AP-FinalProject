#include "trade.h"
#include "ui_trade.h"

Trade::Trade(Bank* _bank,QVector<Player*> _players, int id,Map* _map,QWidget *parent) : QMainWindow(parent), ui(new Ui::Trade)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/new/prefix1/backgrounds/3.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setFixedSize( 615 , 435);


    map = _map;
    players = _players;
    playerId = id;
    bank = _bank;

    ui->label_11->setText(players[playerId]->getName());
    ui->label_66->setPixmap(players[playerId]->getPhoto());
    ui->label_66->setMask(players[playerId]->getPhoto().mask());

    QVector<QCheckBox*> playersName {ui->checkBox1,ui->checkBox2,ui->checkBox3};
    QVector<QLabel*> playersPhoto {ui->label_61 , ui->label_62 , ui->label_63};
    for(int i=0,j=0;i<players.size();i++){
        if(i!=id){
            playersName[j]->setText(players[i]->getName());
            playersPhoto[j]->setPixmap(players[j]->getPhoto());
            playersPhoto[j]->setMask(players[j]->getPhoto().mask());
            j++;
        }
    }


    QPixmap pixmap_bank(":/new/prefix1/icons/bank4.jpg");
    QPixmap pixmap_field(":/new/prefix1/cut/grain.jpg");
    QPixmap pixmap_clay(":/new/prefix1/cut/brick2.jpg");
    QPixmap pixmap_forest(":/new/prefix1/cut/lumber.jpg");
    QPixmap pixmap_stone(":/new/prefix1/cut/ors.jpg");
    QPixmap pixmap_pasture(":/new/prefix1/cut/wool.jpg");

    ui->label_64->setPixmap(pixmap_bank);
    ui->label_64->setMask(pixmap_bank.mask());
    ui->label5->setPixmap(pixmap_clay);
    ui->label5->setMask(pixmap_clay.mask());
    ui->label6->setPixmap(pixmap_field);
    ui->label6->setMask(pixmap_field.mask());
    ui->label7->setPixmap(pixmap_forest);
    ui->label7->setMask(pixmap_forest.mask());
    ui->label8->setPixmap(pixmap_stone);
    ui->label8->setMask(pixmap_stone.mask());
    ui->label9->setPixmap(pixmap_pasture);
    ui->label9->setMask(pixmap_pasture.mask());

    ui->label13->setPixmap(pixmap_clay);
    ui->label13->setMask(pixmap_clay.mask());
    ui->label14->setPixmap(pixmap_field);
    ui->label14->setMask(pixmap_field.mask());
    ui->label15->setPixmap(pixmap_forest);
    ui->label15->setMask(pixmap_forest.mask());
    ui->label16->setPixmap(pixmap_stone);
    ui->label16->setMask(pixmap_stone.mask());
    ui->label17->setPixmap(pixmap_pasture);
    ui->label17->setMask(pixmap_pasture.mask());







    connect(ui->request, SIGNAL(clicked()), this, SLOT(waitForCheckingConditions()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(backToPlayer()));
}
void Trade::backToPlayer(){
    this->close();
}



void Trade::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}

int Trade::givePlayerId(QString name){
    for(int i=0;i<players.size();i++){
        if(name == players[i]->getName())
            return i;
    }
}
void Trade::TradeRequest(bool back)
{
    if(back){
        this->close();
    }

    QVector<QPair<tileType,QPair<int,int>>> cards {
        {clay,{ui->spinBox1->value(),ui->spinBox6->value()}},
        {field,{ui->spinBox2->value(),ui->spinBox7->value()}},
        {forest,{ui->spinBox3->value(),ui->spinBox8->value()}},
        {stone,{ui->spinBox4->value(),ui->spinBox9->value()}},
        {pasture,{ui->spinBox5->value(),ui->spinBox10->value()}} };

    QVector<bool> toWho {ui->checkBox1->isChecked(),ui->checkBox2->isChecked(),ui->checkBox3->isChecked(),ui->checkBox4->isChecked()};

    bool cantExchange = false;
    QVector<QPair<tileType,int>> playerCard = players[playerId]->getCardsNum();

    for(int i=0;i<cards.size();i++){
        if(cards[i].second.first >= playerCard[i].second){
            cantExchange = true;
            break;
        }
    }
    if(cantExchange){
        this->close();
    }

    if(ui->checkBox4->isChecked()){
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
        this->close();
    }
    QVector<QPair<tileType,int>> p2Cards {{clay,ui->spinBox6->value()},{field,ui->spinBox7->value()},
                                          {forest,ui->spinBox8->value()},{stone,ui->spinBox9->value()},{pasture,ui->spinBox10->value()}};
    if(ui->checkBox1->isChecked() && players[givePlayerId(ui->checkBox1->text())]->checkRequset(p2Cards))
        players[givePlayerId(ui->checkBox1->text())]->showRequest(cards,players[playerId]);

    if(ui->checkBox2->isChecked() && players[givePlayerId(ui->checkBox2->text())]->checkRequset(p2Cards))
        players[givePlayerId(ui->checkBox2->text())]->showRequest(cards,players[playerId]);

    if(ui->checkBox3->isChecked() && players[givePlayerId(ui->checkBox3->text())]->checkRequset(p2Cards))
        players[givePlayerId(ui->checkBox3->text())]->showRequest(cards,players[playerId]);


    this->close();
}

void Trade::waitForCheckingConditions()
{

    int sumOfRecievedCards = ui->spinBox6->value() + ui->spinBox7->value()+ui->spinBox8->value()+ui->spinBox9->value()+ui->spinBox10->value();
    int sumOfGivenCards = ui->spinBox1->value()+ ui->spinBox2->value()+ui->spinBox3->value()+ui->spinBox4->value()+ui->spinBox5->value();


        if((ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 && ui->spinBox3->value() == 0
        && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0) && (ui->spinBox6->value() != 0 ||
        ui->spinBox7->value() != 0 || ui->spinBox8->value() != 0 || ui->spinBox9->value() != 0 || ui->spinBox10->value() != 0))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You cannot just recieve cards. It must be two-sided."));
        }


        else if((ui->spinBox6->value() == 0 && ui->spinBox7->value() == 0 && ui->spinBox8->value() == 0 && ui->spinBox9->value() == 0
             && ui->spinBox10->value() == 0) && (ui->spinBox1->value() != 0 || ui->spinBox2->value() != 0
                || ui->spinBox3->value() != 0 || ui->spinBox4->value() != 0 || ui->spinBox5->value() != 0))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You cannot just get cards. It must be two-sided!"));
        }


        else if((ui->spinBox1->value() == 4 || ui->spinBox2->value() == 4 || ui->spinBox3->value() == 4
                || ui->spinBox4->value() == 4 || ui->spinBox5->value() == 4) && (ui->checkBox1->isChecked() == true
                    || ui->checkBox2->isChecked() == true || ui->checkBox3->isChecked() == true))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange 4 cards only with the bank!"));
        }

        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox1->value() == players[playerId]->getClayBank() &&
                 ui->spinBox2->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" brick with bank and receive one card in return!" ).arg(players[playerId]->getClayBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox1->value() != players[playerId]->getClayBank() &&
                 ui->spinBox2->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" brick with bank!" ).arg(players[playerId]->getClayBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox2->value() == players[playerId]->getFieldBank() &&
                 ui->spinBox1->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wheat with bank and receive one card in return!" ).arg(players[playerId]->getFieldBank()));
       }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox2->value() != players[playerId]->getFieldBank() &&
                 ui->spinBox1->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wheat with bank!" ).arg(players[playerId]->getFieldBank()));
       }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox3->value() == players[playerId]->getForestBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                    ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wood with bank and receive one card in return!" ).arg(players[playerId]->getForestBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox3->value() != players[playerId]->getForestBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                    ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wood with bank!" ).arg(players[playerId]->getForestBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox4->value() == players[playerId]->getStoneBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" ore with bank and receive one card in return!" ).arg(players[playerId]->getStoneBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox4->value() != players[playerId]->getStoneBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" ore with bank!" ).arg(players[playerId]->getStoneBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox5->value() == players[playerId]->getPastureBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" sheep with bank and receive one card in return!" ).arg(players[playerId]->getPastureBank()));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox5->value() != players[playerId]->getPastureBank()) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" sheep with bank!" ).arg(players[playerId]->getPastureBank()));
        }


        else if ((sumOfGivenCards!=0 && sumOfRecievedCards !=0 &&  ui->checkBox1->isChecked() == false && ui->checkBox2->isChecked() == false
                        && ui->checkBox3->isChecked() == false && ui->checkBox4->isChecked() == false))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to choose players who you want to change card with!"));
        }


        else if(sumOfGivenCards==0 && sumOfRecievedCards==0 && ui->checkBox1->isChecked() == false && ui->checkBox2->isChecked() == false
                && ui->checkBox3->isChecked() == false && ui->checkBox4->isChecked() == false)
        {
            QMessageBox messageBox(QMessageBox::Question,tr("close window"),tr("Exit the trade window?"),QMessageBox::Yes | QMessageBox::No,NULL);
            messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
            messageBox.setButtonText(QMessageBox::No, tr("No"));

            if( messageBox.exec() == QMessageBox::Yes)
                TradeRequest(1);
        }

        else TradeRequest(0);
}

Trade::~Trade()
{
    delete ui;
}

