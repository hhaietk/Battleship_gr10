/**
  * @file myclient.cpp
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#include "myclient.h"

MyClient::MyClient(QObject *parent) :
Network(parent){

}
    
/// Connecting with server and checking portvalue
void MyClient::connectToServer(QString IP, quint16 port)
{
    // Creating socket
    setSocket(new QTcpSocket(this));
    qDebug().nospace() << this << "Connecting to port " << port << "\n";

    if(port < 1024)
    {
        qDebug().nospace() << this << "Bad Port.\n";
           return;
    }
    qDebug().nospace() << this << "Connecting with server.\n";    
    socket->connectToHost(IP, port);
}

/// Disconnecting from server
void MyClient::disconnectFromServer(){
    socket->disconnectFromHost();
    socket->deleteLater();
    emit disconnected();
}
