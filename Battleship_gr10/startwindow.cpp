#include "startwindow.h"
#include "ui_startwindow.h"
#include "boardsquare.h"

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>


//StartWindow::StartWindow(QWidget *parent) :
//    QWidget(parent),
    StartWindow::StartWindow(QObject *parent) :
        QWidget(dynamic_cast<QWidget*> (parent)),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QPixmap pixstart(":/Startpic.jpg");
    pixstart = pixstart.scaled(QSize(ui->lwelcome->size()));
    ui->lwelcome->setPixmap(pixstart);

    ui->pbdisconnect->setDisabled(true);

    ui->pbstartgame->setDisabled(true);


    //necessary if buttons are Pushbuttons
    //connect(ui->pbclient, &QPushButton::clicked, this, &StartWindow::ButtonClientClicked);
    //connect(ui->pbserver, &QPushButton::clicked, this, &StartWindow::ButtonServerClicked);

     connect(ui->rbserver, &QRadioButton::clicked, this, &StartWindow::chooseServer);
     connect(ui->rbclient, &QRadioButton::clicked, this, &StartWindow::chooseClient);
     connect(ui->pbconnect, &QPushButton::clicked, this, &StartWindow::RadioButtonClicked);
     connect(ui->pbdisconnect, &QPushButton::clicked, [=](){emit ButtonDisconnectClicked();});
     //connect(network, &   ::startready, this, &StartWindow::SteadyConnect);

     //con = new Connects();
     boardsquare = new BoardSquare(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}


/*##########################################################
 *              set Login
 * #########################################################*/

//void StartWindow::Loginsuccessful()
//{
//    ui->pbstartgame->setEnabled(true);
//
//}

void StartWindow::Connectsuccessful()
{
    ui->tbconnectdisconnect->append("Connect successful");
    ui->pbconnect->setDisabled(true);
    ui->pbstartgame->setEnabled(true);
    ui->pbdisconnect->setEnabled(true);
}


//connect to boardsquare window (1.button insert slot->clicked())
void StartWindow::on_pbstartgame_clicked()
{
    //Modal approach: can't use first window after opening second one
    //BoardSquare boardsquare;  //create new object
    boardsquare->setModal(true);
    boardsquare->exec();

    //StartWindow will be closed after pbstartgame is pressed
//    boardsquare->show();
//    this->close();
}

void StartWindow::on_pbquit_clicked()
{
    close();
}

void StartWindow::chooseServer()
{
    ui->lehost->setDisabled(true);
}

void StartWindow::chooseClient()
{
    ui->lehost->setEnabled(true);
}

void StartWindow::RadioButtonClicked()
{
   if(ui->rbclient->isChecked())
   {
     //  port = ui->leport->text().toUShort();
     //  host = ui->lehost->text();
       //emit clientClickedhost(host);
       //emit clientClickedport(port);
       emit clientClicked(ui->lehost->text(), ui->leport->text().toUShort());
   }
   else if(ui->rbserver->isChecked())
   {
       //port = ui->leport->text().toUShort();
       emit serverClicked(ui->leport->text().toUShort());
       //emit serverClicked(ui->leport->text());
   }
}

void StartWindow::SteadyConnect()
{
    ui->pbstartgame->setEnabled(true);
}





/*##########################################################
 *           Solution for QPushbuttons
 * #########################################################*/

//void StartWindow::ButtonClientClicked()
//{
//   ui->pbclient->setDisabled(true);
//   ui->pbserver->setEnabled(true);

//   //emit clientClicked(ui->lehost->text(), ui->leport->text());
//}

//void StartWindow::ButtonServerClicked()
//{
//   ui->pbserver->setDisabled(true);
//   ui->pbclient->setEnabled(true);

//   //emit serverClicked(ui->leport->text());
     //emit serverCLicked(host, port);
//}






