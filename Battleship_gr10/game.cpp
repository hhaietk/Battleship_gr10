#include "game.h"
#include <QDebug>
#include <iostream>
#include <cmath>


game::game(QObject *parent)

{
    Q_UNUSED(parent)
}

//GUI sends shot, logic saves and send it to network
void game::m_shoot(int x, int y)
{
    qDebug() << "shoot" <<myTurn;
    //store the shot
    if (myTurn)
    {
        xShoot = x;
        yShoot = y;
        emit Shoot(x,y);
        myTurn=false;
    }
    //send to network

}

//listen to result of my shot from network
void game::ResponseRequest(std::vector<quint8> ship_pos)
{
    qDebug() << "game::ResponseRequest(): myTurn= " << myTurn;
 //  if(myTurn == false)
   // {
        if (ship_pos[0] == HIT) {
            emit mHit(xShoot, yShoot);
            xShoot = 0;
            yShoot = 0;
            myTurn = false;

        }
        else if (ship_pos[0] == MISS)
        {
            emit mMiss(xShoot, yShoot);
            xShoot = 0;
            yShoot = 0;
            myTurn = false;

        }
        else if (ship_pos[0] == HITandSUNK)
        {
            std::vector<std::pair<quint8, quint8>> shipCoord;
            for(uint idx = 1; idx < ship_pos.size(); idx += 2) {
                shipCoord.push_back({ship_pos[idx], ship_pos[idx + 1]});
            }

            //for(auto el : shipCoord)
            emit mHit(xShoot, yShoot);

            /*
            std::vector<quint8>::iterator it =ship_pos.begin();
            it++;
            while(it != ship_pos.end())
            {
                auto it2=it;
                it2++;
                emit mShipHit(*it, *it2);
                it=it+2;
            }
            */
            RemoveOppShip();
            myTurn = false;
        }

        else if (ship_pos[0] ==NOTYOURTURN)
        {
            //signal to GUI?

        }

        else if (ship_pos[0] ==NOTONBOARD)
        {
            //signal to GUI? how can a player not shoot on board??
        }

        else if (ship_pos[0] ==ERROR)
        {
            emit errormsg();  //then what?
        }
        else if (ship_pos[0] ==HITandEND)
        {
            MeWin = true;
            emit GameOver(MeWin);
        }
  //  }
}

//opponent network sends shot to logic
void game::ResponseShoot(int x, int y)
{
    qDebug() << "repshoot" <<myTurn;
    if (myTurn == false)
    {
        // this is opponent turn because I'm responding to his shot
        if(boardstate[x][y] != empty) //hit
        {
            switch (boardstate[x][y])
            {
                //unused case 'empty' to avoid compiler warning
                case empty: break;
                case battleship_set:
                    {   //myTurn = true;
                        count_battleship++;

                        if(count_battleship == 5) {
                            std::vector<std::pair<int, int>> ship_network = getShip(battleship_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);//HITandSUNK to network
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub); // also for network
                            emit HitFromOpp(x, y); // send to GUI (shot on my Board)

                        }
                    }
                    break;
                case cruiser_set:
                    {
                //myTurn = true;
                        count_cruiser++;
                        if(count_cruiser == 4) {
                            getShip(cruiser_set);
                            std::vector<std::pair<int, int>> ship_network = getShip(cruiser_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case cruiser2_set:
                    {
                //myTurn = true;
                        count_cruiser2++;
                        if(count_cruiser2 == 4) {
                            getShip(cruiser2_set);
                            std::vector<std::pair<int, int>> ship_network = getShip(cruiser2_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case destroyer_set:
                    {
                //myTurn = true;
                        count_destroyer++;
                        if(count_destroyer == 3) {
                            std::vector<std::pair<int, int>> ship_network = getShip(destroyer_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case destroyer2_set:
                    {
                //myTurn = true;
                        count_destroyer2++;
                        if(count_destroyer2 == 3) {
                            std::vector<std::pair<int, int>> ship_network = getShip(destroyer2_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case destroyer3_set:
                    {
                //myTurn = true;
                        count_destroyer3++;
                        if(count_destroyer3 == 3) {
                            std::vector<std::pair<int, int>> ship_network = getShip(destroyer3_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case submarine_set:
                    {
                //myTurn = true;
                        count_submarine++;
                        if(count_submarine == 2) {
                            std::vector<std::pair<int, int>> ship_network = getShip(submarine_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case submarine2_set:
                    {
                //myTurn = true;
                        count_submarine2++;
                        if(count_submarine2 == 2) {
                            std::vector<std::pair<int, int>> ship_network = getShip(submarine2_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case submarine3_set:
                    {
                //myTurn = true;
                        count_submarine3++;
                        if(count_submarine3 == 2) {
                            std::vector<std::pair<int, int>> ship_network = getShip(submarine3_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                    break;
                case submarine4_set:
                    {
                //myTurn = true;
                        count_submarine4++;
                        if(count_submarine4 == 2) {
                            std::vector<std::pair<int, int>> ship_network = getShip(submarine4_set);
                            sendStatusCode(ship_network);
                            emit HitFromOpp(x, y);
//                            RemoveMyShip();
                        }
                        else
                        {
                            emit answerShot(HIT,blub);
                            emit HitFromOpp(x, y);
                        }
                    }
                break;
            }
            myTurn = true;
        }
        else //miss
        {
            emit answerShot(MISS,blub);
            emit MissFromOpp(x, y);
            myTurn = true;
        }
    }
    else
    {
        // say not your turn, signal to gui or network?
    }
}

// Get Positions of two clicks from GUI to set the ship
void game::ReceivePos(int x, int y)
{
    if(endPoint == false)
    {
        //store the first click, enable to receive the second click
        xFirstClick = x;
        yFirstClick = y;
        endPoint = true;

        if(boardstate[xFirstClick][yFirstClick] != empty) {
            resetStartPoint();
            return;
        }

        return;
    }

    //Check the second click if it's valid
    if(!isValidPos(xFirstClick, yFirstClick, x, y) || !isInBoard(x,y) || (xFirstClick==x && yFirstClick==y) ||
            !isDistanceCorrect(xFirstClick, yFirstClick, x, y))
    {
        //invalid click, back to first click, delete the coordinates of FirstClick
        resetStartPoint();
        return;
    }
    else
    {
        //valid, save ship position in vector, check the validity of vector and send back coordinates to GUI
        if(yFirstClick == y) //vertical
        {
            if ((x - xFirstClick) > 0) //expand down
            {
                for(int i = xFirstClick; i < xFirstClick + mLength; i++)
                {
                    ship_position.push_back(std::make_pair(i,yFirstClick));
                }
                endPoint = false;
            }
            else
            {
                for(int i = xFirstClick; i > xFirstClick - mLength; i--) //expand up
                {
                    ship_position.push_back(std::make_pair(i,yFirstClick));
                }
                endPoint = false;
            }
        }
        else //horizontal
        {
            if ((y - yFirstClick) > 0) // expand left
            {
                for(int i = yFirstClick; i < yFirstClick + mLength; i++)
                {
                    ship_position.push_back(std::make_pair(xFirstClick,i));
                }
                endPoint = false;
            }
            else //expand right
            {
                for(int i = yFirstClick; i > yFirstClick - mLength; i--)
                {
                    ship_position.push_back(std::make_pair(xFirstClick,i));
                }
                endPoint = false;
            }
        }

        //above we check the validity of 2 clicks
        //we have a vector contains ship
        //now check if the ship is allowed to be here

        if(onAnotherShip())
        {
            //in case there was already a ship in that postion, clear the vector and go back to first click
            ship_position.clear();
            resetStartPoint();
            return;
        }
        else
        {
            //in case ship is allowed, change the Boardstate
            setBoard();
            xFirstClick = 0;
            yFirstClick = 0;
        }
    }
}

void game::setMYTURN()
{
    myTurn=false;
}

//Check if the endpoint valid (on the same row/collum with start point)
bool game::isValidPos(int x1, int y1, int x2, int y2)
{
    if(x1 == x2 || y1 == y2) {return true;}
    else return false;
}

//Check if the endpoint is still within the board
bool game::isInBoard(int x, int y)
{
    if (x < 0 || x > 9 || y < 0 || y > 9) {return false;}
    else return true;
}

//receive the length from GUI
void game::ActLength(int l)
{
    mLength = l;
}

//Check if two ships over each other by checking every square of the ship
bool game::onAnotherShip()
{
    for (auto i : ship_position) {
        if (boardstate[i.first][i.second] != empty) {return true;}
    }
    return false;
}

//check the distance between clicks is = length of ship
bool game::isDistanceCorrect(int aFirst, int bFirst, int a, int b)
{
    if (bFirst == b) //vertical
    {
        if (abs(aFirst - a) != (mLength-1)) {return false;}
    }
    else //horizontal
    {
        if (abs(bFirst - b) != (mLength-1)) {return false;}
    }
    return true;
}

//set the state of each square in Board
void game::setBoard()
{
    squarestate temp;

    switch (mLength)
    {
    case 5: temp = battleship_set;
        break;
    case 4:
        if(no_cruiser == 0)
            temp = cruiser_set;
        else if(no_cruiser == 1)
            temp = cruiser2_set;
        no_cruiser++;
        break;
    case 3: if(no_destroyer == 0)
            temp = destroyer_set;
        else if (no_destroyer ==1)
            temp = destroyer2_set;
        else if(no_destroyer == 2)
            temp = destroyer3_set;
        no_destroyer++;
        break;
    case 2:
        if(no_submarines == 0)
            temp = submarine_set;
        else if(no_submarines == 1)
            temp = submarine2_set;
        else if(no_submarines == 2)
            temp = submarine3_set;
        else if(no_submarines == 3)
            temp = submarine4_set;
        no_submarines++;
        break;
    }


    for (auto i : ship_position) {
        boardstate[i.first][i.second] = temp;
        emit BetweenPoints(i.first, i.second);
    }

    ship_position.clear();

    printState();
}

void game::resetStartPoint()
{
    xFirstClick = 0;
    yFirstClick = 0;
    endPoint = false;
    emit WrongClick();
}

// each time a ship is sunk run this to caculate the ships left,no ship left -> gameover
void game::RemoveOppShip()
{
        opp_ship_count--;
        if(opp_ship_count == 0)
        {
            MeWin = true;
            emit GameOver(MeWin); // I win
        }
        qDebug()<<"OP"<<opp_ship_count;

}

bool game::RemoveMyShip()
{
        m_ship_count--;
        if(m_ship_count == 0)
        {
            MeWin = false;
            emit GameOver(MeWin); //I lost
            return true;
        }

        qDebug()<<"MP"<<opp_ship_count;
        return false;

}

//get position of corresponding ship
std::vector<std::pair<int, int>> game::getShip(squarestate ship)
{
    std::vector<std::pair<int, int>> ship_network;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(boardstate[i][j] == ship)
            {
                ship_network.push_back(std::make_pair(i,j));
            }
        }
    }
    return ship_network;
}

//send the sunk ship location together with statuscode
void game::sendStatusCode(std::vector<std::pair<int, int>> ship_network)
{
//    std::vector<quint8> statusCode;
//    statusCode.push_back(HITandSUNK);
//    for (auto i=ship_network.begin();i!=ship_network.end();i++)
//    {
//        statusCode.push_back(i->first);
//        statusCode.push_back(i->second);
//    }

   // statusCode[1] = ship_network;
    qDebug() << "game::sendStatusCode";
    bool isFinished=RemoveMyShip();
    for(auto x : ship_network)
        qDebug() << "\t" << x.first << ", " << x.second;


    if(!isFinished) emit answerShot(HITandSUNK, ship_network); // send to network
    else emit answerShot(HITandEND,ship_network);
    //emit mShipHit();

}

// GUI press start and this slot check if all ship there
void game::isAllShipPlaced()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(boardstate[i][j] != empty){
               ship_square_count++;
            }
            qDebug() << "ship square count" << ship_square_count;
        }
    }



    if (ship_square_count == 30)
    {
        ship_square_count = 0;
        emit ShipSetDone();
    }
    else
    {
        emit ShipSetNotDone();
    }
}


void game::printState() {
    for(auto idxX = 0; idxX < 10; ++idxX) {
        for(auto idxY = 0; idxY < 10; ++idxY)
            std::cerr << boardstate[idxX][idxY] << " ";
        std::cerr << std::endl;
    }
}
