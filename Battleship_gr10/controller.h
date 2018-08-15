/**
  * @file controller.h
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "myclient.h"
#include "myserver.h"

class controller : public QObject
{
    Q_OBJECT
public:
    explicit controller(QObject *parent = 0);
    /**
     * @brief server
     */
    MyServer* server;
    /**
     * @brief client
     */
    MyClient* client;
    /**
     * @param isServer
     */
    bool isServer;

signals:

    /**
     * @brief Cconnected signal for client is connected
     * */
    void Cconnected();
    /**
     * @brief Cdisconnected signal for client is disconnected
     * */
    void Cdisconnected();
    /**
     * @brief Cstartready signal that makes start button usable
     * */
    void Cstartready();
    /**
     * @brief CsigParam signal goes to client/server
     * */
    void CsigParam();
    /**
     * @brief CsigBegin signal goes to client/server
     * */
    void CsigBegin();
    /**
     * @brief sigFALSE signal goes to gui
     * */
    void sigFALSE();
    /**
     * @brief CsigShoot signals that shoot was recieved
     * */
    void CsigShoot(quint8 a, quint8 b);
    /**
     * @brief CsigResponseRequest signals that a response to a request was recieved
     * */
    void CsigResponseRequest(quint8 a);
    /**
     * @brief CsigResponseShoot signals that a response to a shoot was recieved
     * */
    void CsigResponseShoot(std::vector<quint8> a);
    /**
     * @brief CmsgParam signals that parameters were sent
     * */
    void CmsgParam(quint8 size, quint8 ship1, quint8 ship2, quint8 ship3, quint8 ship4);
    /**
     * @brief CmsgBegin signals that gamestart was sent
     * */
    void CmsgBegin();
    /**
     * @brief CmsgShoot signals that shoot was sent
     * */
    void CmsgShoot(quint8 x, quint8 y);
    /**
     * @brief CmsgResponseRequest signals that a response to a request was sent
     * */
    void CmsgResponseRequest(quint8 requeststatus);
    /**
     * @brief CmsgResponseShoot signals that a response to a shoot was sent
     * */
    void CmsgResponseShoot(quint8 shootvalue, std::vector<std::pair<int, int>> vector);

public slots:

    /**
     * @brief slot that disconnects the client from the server
     * */
    void CdisconnectFromServer();
    /**
     * @brief slot that creates the server, requires port
     * */
    void createServer(quint16 port);
    /**
     * @brief slot that creates the client, requires address and port
     * */
    void createClient(QString IP, quint16 port);
};

#endif // CONTROLLER_H
