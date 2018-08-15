/**
  * @file myserver.h
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */


#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCore>
#include <QtNetwork>
#include "network.h"


class MyServer : public Network
{
    Q_OBJECT

public:
    MyServer(QObject *parent = 0);



private:
    /**
     * @brief object server
     * */
    QTcpServer * server;

signals:

public slots:
    /**
     * @brief startServer slot that creates server with port
     * */
    void startServer(quint16);
    /**
     * @brief newIncomingConnection slot that makes the server listen for connections
     * */
    void newIncomingConnection();


};


#endif // MYSERVER_H
