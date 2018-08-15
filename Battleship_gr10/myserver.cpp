/**
  * @file myserver.cpp
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#include "myserver.h"

MyServer::MyServer(QObject *parent) :
Network(parent){

}

/// Server listens until client is connected
void MyServer::newIncomingConnection()
{
    setSocket(server->nextPendingConnection());
    qDebug().nospace() << "New incoming connection received.";
    this->server->close();
    qDebug().nospace() << "Socket is there. Stopping listening...";
    this->socketStateChanged(socket->state());
}

/// Creating new server
void MyServer::startServer(quint16 port)
{
    this->server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &MyServer::newIncomingConnection);
    if(!server->listen(QHostAddress::Any, port))
    {
        qDebug().nospace() << "Server could not start!";
    }
    else
    {
        qDebug().nospace() << "Server started. Listening...";
    }
}
