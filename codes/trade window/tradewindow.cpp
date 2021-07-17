#include "tradewindow.h"
#include "ui_tradewindow.h"

tradewindow::tradewindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::tradewindow)
{
    ui->setupUi(this);
    this->setFixedSize(371, 373);
    this->centralWidget()->setStyleSheet( "background-image:url(\"C:/Users/AHFB/Favorites/Desktop/catan images/background/22.jpg\"); background-position: center;");

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(waitForCheckingConditions()));
}

tradewindow::~tradewindow()
{
    delete ui;
}

void tradewindow::setIconForPushButton(QPixmap pix, QIcon icon, QPushButton* button)
{
    button->setIcon(icon);
    button->setIconSize(pix.rect().size());
    button->setText("");
}

void tradewindow::TradeRequest()
{
    MainWindow *x = new MainWindow;
    this->close();
    x->show();
}

void tradewindow::waitForCheckingConditions()
{
    int sumOfRecievedCards = ui->spinBox_6->value() + ui->spinBox_7->value()+ui->spinBox_8->value()+ui->spinBox_9->value()+ui->spinBox_10->value();
    int sumOfGivenCards = ui->spinBox->value()+ ui->spinBox_2->value()+ui->spinBox_3->value()+ui->spinBox_4->value()+ui->spinBox_5->value();


        if((ui->spinBox->value() == 0 && ui->spinBox_2->value() == 0 && ui->spinBox_3->value() == 0
        && ui->spinBox_4->value() == 0 && ui->spinBox_5->value() == 0) && (ui->spinBox_6->value() != 0 ||
        ui->spinBox_7->value() != 0 || ui->spinBox_8->value() != 0 || ui->spinBox_9->value() != 0 || ui->spinBox_10->value() != 0))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You cannot just recieve cards. It must be two-sided."));
        }


        else if((ui->spinBox_6->value() == 0 && ui->spinBox_7->value() == 0 && ui->spinBox_8->value() == 0 && ui->spinBox_9->value() == 0
             && ui->spinBox_10->value() == 0) && (ui->spinBox->value() != 0 || ui->spinBox_2->value() != 0
                || ui->spinBox_3->value() != 0 || ui->spinBox_4->value() != 0 || ui->spinBox_5->value() != 0))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You cannot just get cards. It must be two-sided!"));
        }


        else if((ui->spinBox->value() == 4 || ui->spinBox_2->value() == 4 || ui->spinBox_3->value() == 4
                || ui->spinBox_4->value() == 4 || ui->spinBox_5->value() == 4) && (ui->checkBox->isChecked() == true
                    || ui->checkBox_2->isChecked() == true || ui->checkBox_3->isChecked() == true))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to exchange 4 cards only with the bank!"));
        }


        else if((ui->spinBox->value() == 4 || ui->spinBox_2->value() == 4 || ui->spinBox_3->value() == 4
                 || ui->spinBox_4->value() == 4 || ui->spinBox_5->value() == 4) && sumOfRecievedCards != 1)
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to give 4 cards to the bank and receive one card in return!"));
        }


        else if(ui->checkBox_4->isChecked() == true && sumOfRecievedCards ==1 && sumOfGivenCards!=4)
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You must have 4 cards to exchange with bank!"));
        }


        else if ((sumOfGivenCards!=0 && sumOfRecievedCards !=0 &&  ui->checkBox->isChecked() == false && ui->checkBox_2->isChecked() == false
                        && ui->checkBox_3->isChecked() == false && ui->checkBox_4->isChecked() == false))
        {
            QMessageBox::warning(this, tr("Warning"),
                tr("You have to choose players who you want to change card with!"));
        }


        else if(sumOfGivenCards==0 && sumOfRecievedCards==0 && ui->checkBox->isChecked() == false && ui->checkBox_2->isChecked() == false
                && ui->checkBox_3->isChecked() == false && ui->checkBox_4->isChecked() == false)
        {
            QMessageBox messageBox(QMessageBox::Question,tr("close window"),tr("Exit the trade window?"),QMessageBox::Yes | QMessageBox::No,NULL);
            messageBox.setButtonText(QMessageBox::Yes, tr("Yes"));
            messageBox.setButtonText(QMessageBox::No, tr("No"));

            if( messageBox.exec() == QMessageBox::Yes)
                TradeRequest();
        }

        else TradeRequest();
}
