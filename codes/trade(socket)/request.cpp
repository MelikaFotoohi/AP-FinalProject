#include "request.h"
#include "ui_request.h"
int sumOfRecievedCards = 0;
TCPSocket::TCPSocket(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TCPSocket) {
  ui->setupUi(this);
  setWindowTitle("Trade");
  socket = new QTcpSocket(this);
  message = new QMessageBox();
  setFixedSize( 550 , 400);
  QPixmap bkgnd(":/new/prefix1/3.jpg");
  bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Window, bkgnd);
  this->setPalette(palette);

  QPixmap pixmap_bank(":/new/prefix1/bank4.jpg");
  QPixmap pixmap_field(":/new/prefix1/grain.jpg");
  QPixmap pixmap_clay(":/new/prefix1/brick2.jpg");
  QPixmap pixmap_forest(":/new/prefix1/lumber.jpg");
  QPixmap pixmap_stone(":/new/prefix1/ors.jpg");
  QPixmap pixmap_pasture(":/new/prefix1/wool.jpg");


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

  connect(socket,SIGNAL(readyRead()),this,SLOT(recieve()));
  connect(ui->request, SIGNAL(clicked()), this, SLOT(waitForCheckingConditions()));
  connect(ui->back, SIGNAL(clicked()), this, SLOT(backToPlayer()));
}

TCPSocket::~TCPSocket() {
  socket->close();
  delete ui;
  delete socket;
}

void TCPSocket::connectToServer() {
  socket->connectToHost("127.0.0.1", 9000);
  if (socket->waitForConnected(3000)) {
    message->setText("Connected.");
    message->exec();
 //   ui->SendButton->setDisabled(false);
  } else {
    message->setText("Not Connected.");
    message->exec();
    this->close();
    return;
  }
}

void TCPSocket::send() {
  QByteArray Data;
 // Data.setNum(ui->InputLineEdit->text().toInt());
  socket->write(Data + "\n");
}
void TCPSocket::backToPlayer(){
    this->hide();
}

void TCPSocket::recieve()
{
    QByteArray Data;    
    qDebug() << "Reading:" << socket->bytesAvailable();
    Data = socket->readAll();
    QJsonDocument servers_answer = QJsonDocument::fromJson(Data);
    playerId = servers_answer[4].toInt();
    QVector<QCheckBox*> toWho {ui->checkBox1,ui->checkBox2,ui->checkBox3};
    ui->label_11->setText(servers_answer[playerId]["name"].toString());
    QVector<QLabel*> photoLabel {ui->label_61,ui->label_62,ui->label_63};
    QPixmap blue_person(":/new/prefix1/blue_person.png");
    QPixmap green_person(":/new/prefix1/green_person.png");
    QPixmap red_person(":/new/prefix1/red_person1.png");
    QPixmap yellow_person(":/new/prefix1/yellow_person.png");
    QVector<QPixmap> photos {blue_person,green_person,red_person,yellow_person};

    for(int i=0,j=0; i<4;i++){
        if(i!=playerId){
            toWho[j]->setText(servers_answer[i]["name"].toString());
            toWho[j]->setChecked(false);
            photoLabel[j]->setPixmap(photos[i]);
            photoLabel[j]->setMask(photos[i].mask());
            j++;
        }
        else{
            ui->label_66->setPixmap(photos[i]);
            ui->label_66->setMask(photos[i].mask());
        }
    }
    ui->checkBox4->setChecked(false);


    clayBank = servers_answer[5].toInt();
    fieldBank = servers_answer[6].toInt();
    forestBank = servers_answer[7].toInt();
    stoneBank = servers_answer[8].toInt();
    pastureBank = servers_answer[9].toInt();

    clayCard = servers_answer[10].toInt();
    fieldCard = servers_answer[11].toInt();
    forestCard = servers_answer[12].toInt();
    stoneCard = servers_answer[13].toInt();
    pastureCard = servers_answer[14].toInt();
    QVector<QSpinBox*> spins{ui->spinBox1,ui->spinBox2,ui->spinBox3,ui->spinBox4,ui->spinBox5,
                            ui->spinBox6,ui->spinBox7,ui->spinBox8,ui->spinBox9,ui->spinBox10};
    for(int i=0;i<spins.size();i++){
        spins[i]->setValue(0);
    }
    this->show();
}


void TCPSocket::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}

void TCPSocket::TradeRequest(bool back)
{
    if(back){
        this->hide();
    }

    QVector<QPair<tileType,QPair<int,int>>> cards {
        {clay,{ui->spinBox1->value(),ui->spinBox6->value()}},
        {field,{ui->spinBox2->value(),ui->spinBox7->value()}},
        {forest,{ui->spinBox3->value(),ui->spinBox8->value()}},
        {stone,{ui->spinBox4->value(),ui->spinBox9->value()}},
        {pasture,{ui->spinBox5->value(),ui->spinBox10->value()}} };

    QVector<bool> toWho {ui->checkBox1->isChecked(),ui->checkBox2->isChecked(),ui->checkBox3->isChecked(),ui->checkBox4->isChecked()};

    bool cantExchange = false;
    QVector<QPair<tileType,int>> playerCard = {{clay,clayCard},{field,fieldCard},
                                               {forest,forestCard},{stone,stoneCard},{pasture,pastureCard}};

    for(int i=0;i<cards.size();i++){
        if(cards[i].second.first > playerCard[i].second){
            cantExchange = true;
            QMessageBox::warning(this, tr("Warning"),
                tr("You dont have this cards right now"));
            return;;
        }
    }
    if(cantExchange){
        this->close();
    }

if(sumOfRecievedCards > 0){
    QVector<QPair<tileType,QPair<int,int>>> cards {
        {clay,{ui->spinBox1->value(),ui->spinBox6->value()}},
        {field,{ui->spinBox2->value(),ui->spinBox7->value()}},
        {forest,{ui->spinBox3->value(),ui->spinBox8->value()}},
        {stone,{ui->spinBox4->value(),ui->spinBox9->value()}},
        {pasture,{ui->spinBox5->value(),ui->spinBox10->value()}} };
    QJsonArray a;
    a.append(ui->checkBox1->isChecked());
    a.append(ui->checkBox2->isChecked());
    a.append(ui->checkBox3->isChecked());
    a.append(ui->checkBox4->isChecked());

    a.append(ui->spinBox1->value());
    a.append(ui->spinBox2->value());
    a.append(ui->spinBox3->value());
    a.append(ui->spinBox4->value());
    a.append(ui->spinBox5->value());
    a.append(ui->spinBox6->value());
    a.append(ui->spinBox7->value());
    a.append(ui->spinBox8->value());
    a.append(ui->spinBox9->value());
    a.append(ui->spinBox10->value());

    a.append(playerId);

    a.append(ui->checkBox1->text());
    a.append(ui->checkBox2->text());
    a.append(ui->checkBox3->text());



    QJsonDocument d(a);
    socket->write(d.toJson());
    this->hide();
}
}

void TCPSocket::waitForCheckingConditions()
{

    sumOfRecievedCards = ui->spinBox6->value() + ui->spinBox7->value()+ui->spinBox8->value()+ui->spinBox9->value()+ui->spinBox10->value();
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
                (ui->spinBox1->value() == clayBank &&
                 ui->spinBox2->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" brick with bank and receive one card in return!" ).arg(clayBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox1->value() != clayBank) &&
                 ui->spinBox2->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" brick with bank!" ).arg(clayBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox2->value() ==fieldBank &&
                 ui->spinBox1->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wheat with bank and receive one card in return!" ).arg(fieldBank));
       }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox2->value() != fieldBank &&
                 ui->spinBox1->value() == 0 && ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0))

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wheat with bank!" ).arg(fieldBank));
       }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox3->value() == forestBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                    ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wood with bank and receive one card in return!" ).arg(forestBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox3->value() != forestBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                    ui->spinBox4->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" wood with bank!" ).arg(forestBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox4->value() == stoneBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" ore with bank and receive one card in return!" ).arg(stoneBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox4->value() != stoneBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox5->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" ore with bank!" ).arg(stoneBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards !=1 &&
                (ui->spinBox5->value() == pastureBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" sheep with bank and receive one card in return!" ).arg(pastureBank));
        }
        else if(ui->checkBox4->isChecked() == true && sumOfRecievedCards ==1 &&
                (ui->spinBox5->value() != pastureBank) &&
                 ui->spinBox1->value() == 0 && ui->spinBox2->value() == 0 &&
                ui->spinBox3->value() == 0 && ui->spinBox4->value() == 0)

        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange \"%1\" sheep with bank!" ).arg(pastureBank));
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
