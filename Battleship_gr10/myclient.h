/**
  * @file myclient.h
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */


#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDataStream>
#include <QtCore>
#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include "network.h"

class MyClient : public Network
{
    Q_OBJECT

public:
    MyClient(QObject *parent = 0);


public slots:
    /**
     * @brief slot that disconnects the client
     * */
    void disconnectFromServer();
    /**
     * @brief slot that connects the client
     * */
    void connectToServer(QString IP, quint16 port);
};

#endif // MYCLIENT_H
