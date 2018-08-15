/**
  * @file game.hpp
  * @brief Header of class game
  * @author Hoang Hai Ngo
  * */

#ifndef GAME_H
#define GAME_H

#define MISS 0x00
#define HIT 0x01
#define HITandSUNK 0x02
#define HITandEND 0x03
#define NOTYOURTURN 0x10
#define NOTONBOARD 0x11
#define ERROR 0x20

#include <QObject>
#include "variables.h"

/// @brief Class BoardSquare
class game : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Constructor: initializes list
     */
    explicit game(QObject *parent);


    /**
     * @brief endPoint: decide if it's the second click
     */
    bool endPoint = false;


private:


    /**
     * @brief state of whole board
     */

    squarestate boardstate[10][10] = {{empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty},
                                     {empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}};

    /**
     * @brief ship_position vector to store temporary ship position
     */
    std::vector<std::pair<int, int>> ship_position;


    /**
     * @brief MeWin tell I won or lost
     */
    bool MeWin;

    /**
     * @brief mLength the length of ship
     */
    int mLength;

    /**
     * @brief myTurn decide if it's my Turn
     */
    bool myTurn = true;

    /**
     * @brief xFirstClick, yFirstClick coordinate of first click
     */
    int xFirstClick;
    int yFirstClick;

    /**
     * @brief xShoot, yShoot coordinate of last shot
     */
    int xShoot;
    int yShoot;

    /**
     * @brief ship_square_count count all ship squares
     */
    int ship_square_count = 0;

    /**
     * @brief _cruiser, _destroyer, _submarine
     */
    int _cruiser = 0;
    int _destroyer = 0;
    int _submarine = 0;

    /**
     * @brief m_ship_count count the number of my ships and opponent's ships
     */
    int m_ship_count = 10;
    int opp_ship_count = 10;


    /**
     * @brief count_battleship
     */
    int count_battleship = 0;
    int count_cruiser = 0;
    int count_cruiser2 = 0;
    int count_destroyer = 0;
    int count_destroyer2 = 0;
    int count_destroyer3 = 0;
    int count_submarine = 0;
    int count_submarine2 = 0;
    int count_submarine3 = 0;
    int count_submarine4 = 0;


    /**
     * @brief no_submarines
     *
     *
     */
    int no_submarines = 0;
    int no_destroyer = 0;
    int no_cruiser = 0;

    /**
     * @brief blub blank vector
     */

    std::vector<std::pair<int, int>> blub;

    //conditions to set the ship

    /**
     * @brief isValidPos check if the position of the second click in row or collum with the first
     */

    bool isValidPos(int x1, int y1, int x2, int y2);

    /**
     * @brief isInBoard check if the click still on board
     * @param x
     * @param y
     * @return
     */
    bool isInBoard(int x, int y);

    /**
     * @brief onAnotherShip check if the ship is over another
     * @return
     */
    bool onAnotherShip();

    /**
     * @brief isDistanceCorrect check if the distance between 2 clicks match the length of the ship
     * @param aFirst
     * @param bFirst
     * @param a
     * @param b
     * @return
     */
    bool isDistanceCorrect(int aFirst, int bFirst, int a, int b);

    /**
     * @brief setBoard place ship in boardstate matrix
     */
    void setBoard();

    /**
     * @brief resetStartPoint reset the start and end point coordinates
     */
    void resetStartPoint();

    /**
     * @brief getShip get the position of ship as vector
     * @param ship
     * @return
     */

    std::vector<std::pair<int, int>> getShip(squarestate ship);

    /**
     * @brief RemoveMyShip remove my ship and decrease the my ship counter
     * @return
     */
    bool RemoveMyShip();

    /**
     * @brief RemoveOppShip remove opponent'sship and decrease opponent'sship counter
     */
    void RemoveOppShip();

    /**
     * @brief sendStatusCode send the status code together with the ship's location as vector
     * @param ship_network
     */
    void sendStatusCode(std::vector<std::pair<int, int> > ship_network);

signals:

    //for GUI

    /**
     * @brief WrongClick(); Second Click is not valid
     */
    void WrongClick();

    /**
     * @brief BetweenPoints give to the GUI all coordinates of ship
     * @param x
     * @param y
     */
    void BetweenPoints(int x, int y);

    /**
     * @brief GameOver signal the GUI that game ends
     */
    void GameOver(bool);

    /**
     * @brief HitFromOpp signal that Opponent hit my ship
     * @param x
     * @param y
     */
    void HitFromOpp(int x, int y);

    /**
     * @brief MissFromOpp signal that Opponent miss
     * @param x
     * @param y
     */
    void MissFromOpp(int x, int y);

    /**
     * @brief mHit I hit opponent'ship
     * @param x
     * @param y
     */
    void mHit(int x, int y);

    /**
     * @brief mMiss I miss opponent's ship
     * @param x
     * @param y
     */
    void mMiss(int x, int y);

    /**
     * @brief errormsg signal error
     */
    void errormsg();

    /**
     * @brief ShipSetNotDone signal that we didn't set all the ship
     */
    void ShipSetNotDone();

    /**
     * @brief ShipSetDone signal that we set all the ship
     */
    void ShipSetDone();

    /**
     * @brief answerShot send back to opponent if his shot hit or miss
     * @param shootvalue
     * @param ship_network
     */
    void answerShot(quint8 shootvalue, std::vector<std::pair<int, int>> ship_network);

    /**
     * @brief answerShotMissHit
     */
    void answerShotMissHit(uint8_t);

    /**
     * @brief Shoot
     * @param x
     * @param y
     */
    void Shoot(int x, int y);


public slots:

    /**
    * @brief ReceivePos receive position of second click, check validity and save the ship
    * @param x
    * @param y
    */
   void ReceivePos(int x, int y);
   void setMYTURN();

   /**
    * @brief ActLength get ship length from GUI
    */
   void ActLength(int);
   //this my shoot from GUI

   /**
    * @brief m_shoot send my shoot to network
    * @param x
    * @param y
    */
   void m_shoot(int x, int y);

   /**
    * @brief isAllShipPlaced check if all ships are placed
    */
   void isAllShipPlaced();

   //this shoot from opponent received from network

   /**
    * @brief ResponseShoot
    * @param x
    * @param y
    */
   void ResponseShoot(int x, int y);

   /**
    * @brief ResponseRequest
    * @param ship_pos
    */

   void ResponseRequest(std::vector<quint8> ship_pos);

   /**
    * @brief printState
    */
   void printState();
};

#endif // GAME_H
