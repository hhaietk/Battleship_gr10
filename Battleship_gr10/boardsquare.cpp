#include "boardsquare.h"
#include "ui_boardsquare.h"
#include "button.h"
//#include "startwindow.h"
#include <QLayout>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <iostream>
#include <memory>
#include "QMessageBox"


//BoardSquare::BoardSquare(QWidget *parent) :
//    QDialog(parent),

BoardSquare::BoardSquare(QObject *parent) :
        QDialog(dynamic_cast<QWidget*>(parent)),
    ui(new Ui::BoardSquare)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QPixmap pixlose(":/losepic.jpg");
    pixlose = pixlose.scaled(QSize(ui->llose->size()));
    ui->llose->setPixmap(pixlose);
    ui->llose->hide();

    QPixmap pixwin(":/Winpic.jpg");
    pixwin = pixwin.scaled(QSize(ui->lwin->size()));
    ui->lwin->setPixmap(pixwin);
    ui->lwin->hide();

    QPixmap pixback(":/backpic.jpg");
    pixback = pixback.scaled(QSize(ui->lbackground->size()));
    ui->lbackground->setPixmap(pixback);
    ui->pbstart->setDisabled(true);

    QFont lcha("Times New Roman", 12, QFont::Bold);
    ui->lchat->setFont(lcha);

    counterdestroyer = 0;
    countersubmarine = 0;
    countercruiser = 0;


   // ui->pbstart->setDisabled(true);
    ui->pbcruiser->setDisabled(true);
    ui->pbdestroyer->setDisabled(true);
    ui->pbsubmarine->setDisabled(true);


    ui->gridLayout->setSpacing(0);
    for (int x=0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            //const QSize btnSize = QSize(40,40);/////
            Button *button = new Button(1, 1);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            //button->setFixedSize(button->size()); ////////////                                    //maybe if the buttons are changing size
            //button->setStyleSheet("QPushButton {""background-color: blue""}");
            button->setDisabled(true);
            button->setStyleSheet("background-color: rgb(0,0,153)");
            position1.push_back(button);                                                             //save position in a vector for later position access (for later slots)
            ui->gridLayout->addWidget(button,x,y);
            connect(button, &QPushButton::clicked, [=](){emit buttonPressed1(x, y);});              //Lambda function for position to logic playerme
            //connect(this , &BoardSquare::buttonPressed1, this, &BoardSquare::dummycolor);         //test function to test coloring
            playerme.emplace_back(x,y);
        }
    }

    for (int x=0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            //const QSize btnSize = QSize(50,50);
            Button *button = new Button(1,1);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            //button->setFixedSize(btnSize);
            button->setDisabled(true);
            position2.push_back(button);
            ui->gridLayout_2->addWidget(button, x,y);                                   //.get() because of shared_ptr
            ui->gridLayout_2->setSpacing(0);
            connect(button, &QPushButton::clicked, [=](){emit buttonPressed2(x, y);});  //Lambda function for position to logic playeropponent
            playeropponent.emplace_back(x,y);                                           //playeropponent.push_back({i,j});
            button->setStyleSheet("background-color: rgb(0,0,153)");
        }
    }


    connect(ui->pbstart, &QPushButton::clicked, this, &BoardSquare::ButtonStartClicked);
    connect(ui->pbsend, &QPushButton::clicked, this, &BoardSquare::send);



     //connect for length of ships
    connect(ui->pbbattleship, &QPushButton::clicked, [=](){emit length(5);});
    connect(ui->pbcruiser, &QPushButton::clicked, [=](){emit length(4);});
    connect(ui->pbdestroyer, &QPushButton::clicked, [=](){emit length(3);});
    connect(ui->pbsubmarine, &QPushButton::clicked, [=](){emit length(2);});

    connect(ui->pbquitgame, &QPushButton::clicked, this, &BoardSquare::quit);

    connect(ui->pbbattleship, &QPushButton::clicked, this, &BoardSquare::on_pbbattleship);
    connect(ui->pbcruiser, &QPushButton::clicked, this, &BoardSquare::on_pbcruiser);
    connect(ui->pbdestroyer, &QPushButton::clicked, this, &BoardSquare::on_pbdestroyer);
    connect(ui->pbsubmarine, &QPushButton::clicked, this, &BoardSquare::on_pbsubmarine);

    connect(ui->pbsend, &QPushButton::clicked, this, &BoardSquare::GameisOver);
    connect(ui->pbtest, &QPushButton::clicked, this, &BoardSquare::setshipstest);
    connect(ui->pbshipset, &QPushButton::clicked, this, &BoardSquare::allshipsset);
    //test for positions(x,y)->textmessage to chat window(tbtext)
    //connect(this, &BoardSquare::buttonPressed1, this, &BoardSquare::outputtest);
    //test function (for reaching correct pushed button)
    //connect(ui->pbdisconnect, &QPushButton::clicked, this, &BoardSquare::testMyButtons);
}

BoardSquare::~BoardSquare()
{
    delete ui;
}

void BoardSquare::setshipstest()
{
    emit length(5);
    emit buttonPressed1(0, 0);
    emit buttonPressed1(0, 4);
    emit length(4);
    emit buttonPressed1(1, 0);
    emit buttonPressed1(1, 3);
    emit length(4);
    emit buttonPressed1(2, 0);
    emit buttonPressed1(2, 3);
    emit length(3);
    emit buttonPressed1(3, 0);
    emit buttonPressed1(3, 2);
    emit length(3);
    emit buttonPressed1(4, 0);
    emit buttonPressed1(4, 2);
    emit length(3);
    emit buttonPressed1(5, 0);
    emit buttonPressed1(5, 2);
    emit length(2);
    emit buttonPressed1(6, 0);
    emit buttonPressed1(6, 1);
    emit length(2);
    emit buttonPressed1(7, 0);
    emit buttonPressed1(7, 1);
    emit length(2);
    emit buttonPressed1(8, 0);
    emit buttonPressed1(8, 1);
    emit length(2);
    emit buttonPressed1(9, 0);
    emit buttonPressed1(9, 1);

}

/*##############################################################
 *      Counter functions for shipsetting pushbuttons
 *##############################################################*/

void BoardSquare::on_pbbattleship()
{
    ui->pbbattleship->setDisabled(true);
    ui->pbcruiser->setDisabled(true);
    ui->pbdestroyer->setDisabled(true);
    ui->pbsubmarine->setDisabled(true);
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
    }
    static int i=0;
    i++;
            if (i==1)
    {
        ui->pbbattleship->setDisabled(true);
//        ui->pbcruiser->setEnabled(true);
    }
}

void BoardSquare::on_pbcruiser()
{
    ui->pbcruiser->setDisabled(true);
    ui->pbdestroyer->setDisabled(true);
    ui->pbsubmarine->setDisabled(true);
    countercruiser++;
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
    }
    //static int countercruiser=0;

//            if (i==2)
//    {
//        ui->pbcruiser->setDisabled(true);
//        ui->pbdestroyer->setEnabled(true);
//    }
}

void BoardSquare::on_pbdestroyer()
{
    ui->pbcruiser->setDisabled(true);
    ui->pbdestroyer->setDisabled(true);
    ui->pbsubmarine->setDisabled(true);
    counterdestroyer++;
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
    }
    //static int counterdestroyer=0;

//            if (counterdestroyer==3)
//    {
//        ui->pbdestroyer->setDisabled(true);
//        ui->pbsubmarine->setEnabled(true);
//    }
}

void BoardSquare::on_pbsubmarine()
{
    ui->pbcruiser->setDisabled(true);
    ui->pbdestroyer->setDisabled(true);
    ui->pbsubmarine->setDisabled(true);
    countersubmarine++;
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
    }
    //static int countersubmarine=0;
//            if (i==4)
//    {
//        ui->pbsubmarine->setDisabled(true);
//        ui->pbstart->setEnabled(true);
//    }
}

void BoardSquare::allshipsset()
{
    ui->pbshipset->setDisabled(true);
    emit testshipsetting();
}

void BoardSquare::disablestartopp()
{
    ui->pbstart->setDisabled(true);
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout_2->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
     }
}

void BoardSquare::startgamebtn()
{
    ui->pbstart->setEnabled(true);
}

void BoardSquare::ButtonStartClicked()
{
    ui->pbstart->setDisabled(true);
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->disconnect();
        }
    }
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout_2->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
    }
    emit startgame();
}

/*#####################################################################
 *              shipsetting
 *#####################################################################*/

void BoardSquare::wrongposition()
{
    ui->tbtext->append("Unallowed position");
}


void BoardSquare::shipsetting(int x, int y)
{
    ui->pbtest->setDisabled(true);
    auto tmpbtn = ui->gridLayout->itemAtPosition(x,y)->widget();
    //tmpbtn->setFixedSize(tmpbtn->size());
    tmpbtn->clearFocus();
//    static int countnumberships = 0;
//    countnumberships++;

//    if(countnumberships == 1)
//    {
//        tmpbtn->setStyleSheet("background-color: rgb(130,130,130)");
//    }
//    else if(countnumberships == 2)
//    {

//    }
//    else if(countnumberships == 3)
//    {

//    }
//    else if(countnumberships == 4)
//    {

//    }
//    else if(countnumberships == 5)
//    {

//    }
//    else if(countnumberships == 6)
//    {

//    }
//    else if(countnumberships == 7)
//    {

//    }
//    else if(countnumberships == 8)
//    {

//    }
//    else if(countnumberships == 9)
//    {

//    }
//    else if(countnumberships == 10)
//    {

//    }


    tmpbtn->setStyleSheet("background-color: rgb(130,130,130)");
    tmpbtn->disconnect();
    ui->pbcruiser->setEnabled(true);
    ui->pbdestroyer->setEnabled(true);
    ui->pbsubmarine->setEnabled(true);
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setDisabled(true);
        }
    }
    if(countercruiser == 2)
    {
        ui->pbcruiser->setDisabled(true);
    }

    if(counterdestroyer ==3)
    {
        ui->pbdestroyer->setDisabled(true);
    }

    if(countersubmarine == 4)
    {
        ui->pbsubmarine->setDisabled(true);
    }
}




/*#####################################################################
 *              game phase My Field
 *#####################################################################*/

void BoardSquare::missmyfield(int x, int y)
{
   //if(Statuscode == 0)
   {
        QPixmap pixmiss(":/wasserpic.jpg");
        QIcon icon(pixmiss);
        position1[x*10+y]->setFixedSize(( position1[x*10+y])->size());
        position1[x*10+y]->setIconSize(0.9*(position1[x*10+y]->size()));
        position1[x*10+y]->setIcon(icon);


       auto tmpbtn = ui->gridLayout->itemAtPosition(x,y)->widget();
       tmpbtn->clearFocus();
       //tmpbtn->setStyleSheet("background-color: rgb(58,114,212)");
       tmpbtn->disconnect();
   }
}

void BoardSquare::hitmyfield(int x,int y)
{
    //if(Statuscode == 1 || Statuscode == 2)
    {
        QPixmap pixexp(":/explos.jpeg");
        QIcon icon(pixexp);
        position1[x*10+y]->setFixedSize(( position1[x*10+y])->size());
        position1[x*10+y]->setIconSize(0.9*(position1[x*10+y]->size()));
        position1[x*10+y]->setIcon(icon);

        auto tmpbtn = ui->gridLayout->itemAtPosition(x,y)->widget();
        tmpbtn->clearFocus();
        //tmpbtn->setStyleSheet("background-color: rgb(198,0,0)");
        tmpbtn->disconnect();
    }
}

//void BoardSquare::dumpwholeship()
//{

//}


/*#####################################################################
 *              game phase Opponent Field
 *#####################################################################*/

void BoardSquare::missopponentfield(int x, int y)
{
//    if(Statuscode == 0)
    {
    QPixmap pixmiss(":/wasserpic.jpg");
    QIcon icon(pixmiss);
    position2[x*10+y]->setFixedSize(( position1[x*10+y])->size());
    position2[x*10+y]->setIconSize(0.9*(position1[x*10+y]->size()));
    position2[x*10+y]->setIcon(icon);

    auto tmpbtn = ui->gridLayout_2->itemAtPosition(x,y)->widget();
    tmpbtn->clearFocus();
    //tmpbtn->setStyleSheet("background-color: rgb(58,114,212)");
    tmpbtn->disconnect();
    }

}

void BoardSquare::hitopponentfield(int x, int y)
{
    {
    auto tmpbtn = ui->gridLayout_2->itemAtPosition(x,y)->widget();
    QPixmap pixexp(":/explos.jpeg");
    QIcon icon(pixexp);
    position2[x*10+y]->setFixedSize(( position1[x*10+y])->size());
    position2[x*10+y]->setIconSize(0.9*(position1[x*10+y]->size()));
    position2[x*10+y]->setIcon(icon);

    tmpbtn->clearFocus();
    //tmpbtn->setStyleSheet("background-color: rgb(198,0,0)");
    tmpbtn->disconnect();
    }
}

/*#####################################################################
                    GAME IS OVER
  #####################################################################*/

void BoardSquare::GameisOver(bool wewin)
{
   if (wewin == true)
    {
           ui->lwin->show();
    }
    else
    {
       ui->llose->show();
    }
}



/*#####################################################################
                    CHAT
  #####################################################################*/

void BoardSquare::send()
{
    ui->tbtext->append("send: "+ ui->lemessage->text());
    emit signalChatToNetwork(ui->lemessage->text());
    ui->lemessage->clear();
}

void BoardSquare::receive(QString messagereceived)
{
    ui->tbtext->append("receive: " + messagereceived);
}

void BoardSquare::quit()
{
    emit sendquit();
}

void BoardSquare::reableshipset()
{
    for (int x =0; x<10; x++)
    {
        for (int y=0; y<10; y++)
        {
            ui->gridLayout->itemAtPosition(x,y)->widget()->setEnabled(true);
        }
     }
}


/*#####################################################################
 *            DUMMY FUNCTIONS
 * ####################################################################*/
//dummy function 1
//void BoardSquare::dummycolor(int x, int y)
//{
//    position1[x*10+y]->clearFocus();    // [width * row + col] = position of pushed button
//    position1[x*10+y]->setStyleSheet("background-color:red");
//    position1[x*10+y]->setDisabled(true);
//}

//dummy fuction 2
//void BoardSquare::testMyButtons() {
//    int x = 2, y = 2;

//    auto btn =  ui->gridLayout->itemAtPosition(x, y)->widget();
//    btn->setStyleSheet("background-color:red");
//    btn->setDisabled(true);
//}

//dummy function 3 for position->textmessage to chat window(tbtext)
//void BoardSquare::outputtest(int x, int y)
//{
//    QString blub;
//    QString var = QString::number(x);
//    blub.append(var);
//    blub.append(" ");
//    var = QString::number(y);
//    blub.append(var);
//    ui->tbtext->append(blub);
//}





