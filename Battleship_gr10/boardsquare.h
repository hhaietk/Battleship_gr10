/**
  * @file boardsquare.hpp
  * @brief Header of class BoardSquare
  * @author J. Hager
  * */

#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QDialog>
#include <QTextStream>
#include <QPixmap>
#include <iostream>
#include <vector>
#include <QVBoxLayout>
#include <QTextEdit>
#include <memory>
#include "button.h"
//#include "game.h"

namespace Ui {
class BoardSquare;
}

/// @brief Class BoardSquare
class BoardSquare : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor: initializes list
     */
    explicit BoardSquare(QObject *parent = 0);

    /// @brief Destructor of BoardSquare
    ~BoardSquare();

    /** @brief vector of pairs playerme
     *  @param saves the coordinates of the own board
     * **/
    std::vector<std::pair<int,int>> playerme;

    /** @brief vector of pairs playeropponent
     *  @param saves the coordinates of the opponent board
     * */
    std::vector<std::pair<int,int>> playeropponent;

    std::vector<Button*> position1;
    std::vector<Button*> position2;


private:
    Ui::BoardSquare *ui;

    /// @brief a private variable for counting clicks of QPushbuttons for destroyer ship setting
    int counterdestroyer;
    /// @brief a private variable for counting clicks of QPushbuttons for destroyer ship setting
    int countersubmarine;
    /// @brief a private variable for counting clicks of QPushbuttons for destroyer ship setting
    int countercruiser;
    /// \brief a private variable to signal if game is won or lost
    bool Wewin;


signals:
    /** @brief signal buttonPressed1 for emitting coordinates of press QPushbutton
     *  @param integer parameter for x coordinate of own board
     *  @param integer parameter for y coordinate of own board
     * */
    void buttonPressed1(int, int);

    /** @brief signal buttonPressed2 with integer parameters
     *  @param integer parameter for x coordinate of opponent board
     *  @param integer parameter for y coordinate of opponent board
     * */
    void buttonPressed2(int, int);

    /** @brief signal signalChatToNetwork
     *
     * */
    void signalChatToNetwork(QString);

    /** @brief signal length
     *  @param emits the length of each ship after pressing appropiate button
     * */
    void length(int);

    /** @brief signal sendquit
     *
     *  is emitted, if quit game button in boardquare is pressed
     * */
    void sendquit();

    /**
     * @brief signal startgame
     *
     * is emitted, if start button in boardsquare is pressed
     */
     void startgame();

     /**
      * @brief signal testshipsetting
      *
      * To test if all 10 ships are set
      */
     void testshipsetting();




public slots:

     void setshipstest();
    /** @brief slot length
     *
     * */
    void send();

    /** @brief slot receive
     *
     * */
    void receive(QString messagereceived);

    /**
     * @brief slot hitmyfield
     *
     * To signal if a part of a ship from player1 is hit
     * @param x: x coordinate
     * @param y: y coordinate
     */
    void hitmyfield(int x,int y);

    /**
     * @brief slot missmyfield
     *
     * To signal if no part of a ship from player1 is hit
     * @param x: x coordinate
     * @param y: y coordinate
     */
    void missmyfield(int x, int y);

    /**
     * @brief slot hitopponentfield
     *
     * To signal if a part of a ship from player2 is hit
     * @param x: x coordinate
     * @param y: y coordinate
     */
    void hitopponentfield(int x,int y);

    /**
     * @brief slot missopponentfield
     *
     * To signal if no part of a ship from player2 is hit
     * @param x: x coordinate
     * @param y: y coordinate
     */
    void missopponentfield(int x,int y);

    /**
     * @brief slot shipsetting
     *
     * To highlight the position where a ship is set
     * @param x: x position
     * @param y: y position
     */
    void shipsetting(int x, int y);

    /** @brief slot ButtonStartClicked
     *
     *  For signaling to start the game
     * */
    void ButtonStartClicked();

    /** @brief slot wrongposition
     *
     *  If a unallowed position for ship setting is pressed
     **/
    void wrongposition();

    /**
     * @brief slot GameisOver
     *
     * To signal the end of game
     */
    void GameisOver(bool);

    /**
     * @brief slot startgame
     *
     * To signal all 10 ships are set
     */
    void startgamebtn();

    /**
     * @brief allshipsset
     *
     * To check if all ships are set
     */
    void allshipsset();

    /**
     * @brief disablestartopp
     *
     * Enables the board to start the game
     */
    void disablestartopp();

    /**
     * @brief reableshipset
     *
     * If ship setting is not done, the board is enabled again
     */
    void reableshipset();

    /**
     * @brief slot quit
     *
     * For emitting the signal sendquit to end the game
     */
    void quit();

    //tests
    //void dummycolor(int x, int y);
    //void testMyButtons();
    // void outputtest(int x, int y);


    /// @brief slot on_pbsubmarine_clicked
    void on_pbsubmarine();

    /// @brief slot on_pbbattleship_clicked
    void on_pbbattleship();

    /// @brief slot on_pbcruiser_clicked
    void on_pbcruiser();

    /// @brief slot on_pbdestroyer_clicked
    void on_pbdestroyer();
};

#endif // BOARDSQUARE_H
