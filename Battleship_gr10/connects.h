#ifndef CONNECTS_H
#define CONNECTS_H

//#include "boardsquare.h"
#include "button.h"
#include "startwindow.h"
#include "game.h"
#include "myclient.h"
#include "myserver.h"
#include "controller.h"
#include <QObject>

/// @brief class Connects
class Connects : public QObject
{
    Q_OBJECT
 public:

    /// @brief Constructor: Connects
    Connects();

    /// @brief creates a new object for Game
    game *Game;

    /// @brief creates a new object for StartWindow
    StartWindow* startwindow;

    /// @brief creates a new object for controller
    controller* contr;

   // MyClient* clientptr;
    //MyServer* serverptr;
    //Network* networkptr;



    //BoardSquare *boardsquare;

public slots:

    /**
     * @brief slot quitgame
     *
     * To close boardquare window and end the game
     */
    void quitgame();
//  void mkConnect();

};

#endif // CONNECTS_H

