#include <QObject>
#include <QApplication>
#include <QProcess>
#include "connects.h"
#include "boardsquare.h"
#include "button.h"
#include "game.h"
//#include "startwindow.h"

Connects::Connects()
        : QObject(nullptr)
{
    startwindow = new StartWindow(this);
    //boardsquare = new BoardSquare(this);
    Game = new game(this);
    contr = new controller(this);

    //clientptr = new MyClient(this);
    //serverptr = new MyServer(this);
    //networkptr = new Network(this);


    startwindow->show();
//    mkConnect();

    /*##################################
     * Connects between Network and GUI
     *##################################*/


   connect(startwindow, &StartWindow::clientClicked, contr, &controller::createClient);
   connect(startwindow, &StartWindow::serverClicked, contr, &controller::createServer);
   connect(startwindow, &StartWindow::ButtonDisconnectClicked, contr , &controller::CdisconnectFromServer);


//   connect(clientptr, &MyClient::startready, startwindow, &StartWindow::Loginsuccessful);
   connect(startwindow->boardsquare, &BoardSquare::startgame, contr, &controller::CmsgBegin);
   connect(contr, &controller::Cconnected, startwindow, &StartWindow::Connectsuccessful);
   connect(contr, &controller::CmsgBegin, startwindow->boardsquare, &BoardSquare::disablestartopp);


    /*##################################
     * Connects between Logic and Network
     *##################################*/

    connect( Game, &game::Shoot, contr, &controller::CmsgShoot);
    connect( Game, &game::answerShot, contr, &controller::CmsgResponseShoot);
    //connect(Game, &game::answerShotMissHit,contr,&controller::CmsgResponseShoot)
    connect( contr, &controller::CsigResponseShoot, Game, &game::ResponseRequest);
    connect( contr, &controller::CsigShoot, Game, &game::ResponseShoot);


  connect(contr,&controller::sigFALSE, Game, &game::setMYTURN);




    /*##################################
     * Connects between Logic and GUI
     *##################################*/


    connect(startwindow->boardsquare, &BoardSquare::sendquit, this, &Connects::quitgame );

    connect( Game, &game::WrongClick, startwindow->boardsquare, &BoardSquare::wrongposition);
    connect(Game , &game::BetweenPoints, startwindow->boardsquare, &BoardSquare::shipsetting);

    connect(startwindow->boardsquare, &BoardSquare::buttonPressed1, Game , &game::ReceivePos);
    connect(startwindow->boardsquare, &BoardSquare::buttonPressed2, Game , &game::m_shoot);

    connect(startwindow->boardsquare, &BoardSquare::length, Game , &game::ActLength);

    connect(Game , &game::HitFromOpp , startwindow->boardsquare, &BoardSquare::hitmyfield);
    connect(Game , &game::MissFromOpp, startwindow->boardsquare, &BoardSquare::missmyfield);
    connect(Game , &game::mHit , startwindow->boardsquare, &BoardSquare::hitopponentfield);
    connect(Game ,&game::mMiss , startwindow->boardsquare, &BoardSquare::missopponentfield);
    connect(Game, &game::GameOver, startwindow->boardsquare, &BoardSquare::GameisOver);

    connect(Game, &game::ShipSetDone, startwindow->boardsquare, &BoardSquare::startgamebtn);
    connect(startwindow->boardsquare, &BoardSquare::testshipsetting, Game, &game::isAllShipPlaced);
    connect(Game, &game::ShipSetNotDone, startwindow->boardsquare, &BoardSquare::reableshipset);

}

void Connects::quitgame()
{
    /*startwindow->boardsquare->close();
    startwindow->close();
    startwindow = new StartWindow(this);
    startwindow->show();
    Game = new game(this);
    mkConnect();*/

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
