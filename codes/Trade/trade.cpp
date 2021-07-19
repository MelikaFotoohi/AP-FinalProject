#include "trade.h"
#include "ui_trade.h"

Trade::Trade(Bank* _bank,QVector<Player*> _players, int id,Map* _map,QWidget *parent) : QMainWindow(parent), ui(new Ui::Trade)
{
    ui->setupUi(this);
    map = _map;
    players = _players;
    playerId = id;
    bank = _bank;

    ui->label_55->setText(players[playerId]->getName());
    QVector<QCheckBox*> playersName {ui->checkBox1,ui->checkBox2,ui->checkBox3};
    for(int i=0,j=0;i<players.size();i++){
        if(i!=id){
            playersName[j]->setText(players[i]->getName());
            j++;
        }
    }

    connect(ui->request, SIGNAL(clicked()), this, SLOT(waitForCheckingConditions()));
}

Trade::~Trade()
{
    delete ui;
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
        players[playerId]->show();
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
        players[playerId]->show();
        this->close();
    }

    if(ui->checkBox4->isChecked()){
        for(int i=0;i<cards.size();i++){
            if(cards[i].second.first == 4){
                for(int j=0;j<4;j++){
                    bank->getCardFromPlayer(cards[i].first);
                    players[playerId]->giveResourceCard(cards[i].first);
                }
            }
            if(cards[i].second.second == 1){
                bank->giveResCardToPlayer(cards[i].first);
                players[playerId]->getResourceCard(cards[i].first);
            }
        }
        players[playerId]->show();
        this->close();
    }
    if(ui->checkBox1->isChecked())
        players[givePlayerId(ui->checkBox1->text())]->showRequest(cards,players[playerId]);
    if(ui->checkBox2->isChecked())
        players[givePlayerId(ui->checkBox2->text())]->showRequest(cards,players[playerId]);
    if(ui->checkBox3->isChecked())
        players[givePlayerId(ui->checkBox3->text())]->showRequest(cards,players[playerId]);

    players[playerId]->show();
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


        else if((ui->spinBox1->value() == 4 || ui->spinBox2->value() == 4 || ui->spinBox3->value() == 4
                 || ui->spinBox4->value() == 4 || ui->spinBox5->value() == 4) && sumOfRecievedCards != 1)
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to give 4 cards to the bank and receive one card in return!"));
        }


        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 && sumOfGivenCards!=4)
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You must have 4 cards to exchange with bank!"));
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

