/**
  * @file network.cpp
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{
    InOutStream.setByteOrder(QDataStream::BigEndian);
}

/// Testing sendMessage over network
void Network::sendMessage(quint8 something)
{
    qDebug().nospace() << "Sending data: " << QString::number(something);
    InOutStream << something << something;
}

/// Erroroutput
void Network::connectionError(QAbstractSocket::SocketError socketError)
{
    qDebug().nospace() << "Error. Could not connect. (Error Number: " << QString::number((qint32)socketError) << ")";
}

void Network::socketStateChanged(QAbstractSocket::SocketState state)
{
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        qDebug().nospace() << "Unconnected"; break;
    case QAbstractSocket::HostLookupState:
        qDebug().nospace() << "HostLookupState"; break;
    case QAbstractSocket::ConnectingState:
        qDebug().nospace() << "ConnectingState"; break;
    case QAbstractSocket::ConnectedState:
        qDebug().nospace() << "ConnectedState";
        emit connected(); emit startready();
       // connect(socket, &QAbstractSocket::readyRead, this, &Network::readMessage);
        IsConnected = true; break;
    case QAbstractSocket::BoundState:
        qDebug().nospace() << "BoundState"; break;
    case QAbstractSocket::ClosingState:
        qDebug().nospace() << "ClosingState";
        emit disconnected();
        IsConnected = false; break;
    case QAbstractSocket::ListeningState:
        qDebug().nospace() << "ListeningState"; break;
    default: break;
    }
}

/** Sending messages
 *  Message format
cmd | bytelength | value(s)**/

void Network::msgParam(quint8 size = 0x0a, quint8 ship1 = 0x01, quint8 ship2 = 0x02, quint8 ship3 = 0x03, quint8 ship4 = 0x04)
{
    quint8 cmd = 0x01, length = 0x06;
    InOutStream << cmd << length << size << size << ship1 << ship2 << ship3 << ship4;
    qDebug() << "Network::msgParam: " << (int)cmd << ", " << (int)length <<
                (int)size<< ", " << (int)ship1<< (int)ship2<< ", " << (int)ship3<< (int)ship4<< ", ";
}

void Network::msgBegin() //todo: connect to gui via buttons
{
    quint8 cmd = 0x02, length = 0x00;
    InOutStream << cmd << length;
    qDebug() << "Network::msgBegin(): " << cmd << ", " << length;
}

void Network::msgShoot(quint8 x, quint8 y) //connect to logic
{
    quint8 cmd = 0x03, length = 0x02;
    InOutStream << cmd << length << x << y;
    qDebug()  << "Network::msgShoot() " << cmd << ", " << length << x << ", " << y;
}

void Network::msgResponseRequest(quint8 requeststatus) //todo: connect to gui
{
    quint8 cmd = 0x10, length = 0x01;
    switch(requeststatus)
    {
        case 0x00: qDebug().nospace() << "Sending: Ok.\n"; break;
        case 0x01: qDebug().nospace() << "Sending: Declined or not ready.\n"; break;
        case 0x02: qDebug().nospace() << "Sending: Not supported.\n"; break;
        case 0x03: qDebug().nospace() << "Sending: Message incomplete\n"; break;
        case 0x04: qDebug().nospace() << "Sending: Timeout while waiting for acknowledgement.\n"; break;
        case 0x20: qDebug().nospace() << "Sending: Random error.\n"; break;
        default: break;
    }
    InOutStream << cmd << length << requeststatus;
}

void Network::msgResponseShoot(quint8 shootvalue, std::vector<std::pair<int, int> > vector) // todo: connect to logic
{
    quint8 cmd = 0x11, length = (2*vector.size()) + 0x01;
    switch(shootvalue)
    {
        case 0x00: qDebug().nospace() << "Sending: No hit.\n"; break;
        case 0x01: qDebug().nospace() << "Sending: Hit.\n"; break;
        case 0x02: qDebug().nospace() << "Sending: Hit and sunk.\n"; break;
        case 0x03: qDebug().nospace() << "Sending: Hit and finish, gameover.\n"; break;
        case 0x10: qDebug().nospace() << "Sending: Not your turn.\n"; break;
        case 0x11: qDebug().nospace() << "Sending: Out of field.\n"; break;
        case 0x20: qDebug().nospace() << "Sending: Random error.\n"; break;
        default: break;
    }
    InOutStream << cmd << length << shootvalue;
     qDebug()<<"S"<<cmd<<length<<shootvalue;
    for(auto i: vector)
    {
       qDebug()<<i.first<<i.second;
           InOutStream << (quint8) i.first << (quint8) i.second;
    }
}

/// Creating socket and set it up as a device
void Network::setSocket(QTcpSocket *newSocket)
{
    socket = newSocket;
    InOutStream.setDevice(socket);
    qDebug() << "Stream has set socket as device\n";
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionError(QAbstractSocket::SocketError)));
    connect(socket, &QTcpSocket::stateChanged, this, &Network::socketStateChanged);
    connect(socket, &QAbstractSocket::readyRead, this, &Network::readMessage);
}

/// Reads the message and sends it to logic
void Network::readMessage()
{
    quint8 cmd,length,temp;
    std::vector<quint8> storage;
    InOutStream >> cmd >>length;
    qDebug()<<"Network::readMessage() " << (int)cmd << "," << (int)length;
    if(socket->bytesAvailable()>=length)
    {
        for(uint i=0;i<length;i++)
           {
            InOutStream >> temp ;
            qDebug()<<temp;
            storage.push_back(temp);
            }
         switch(cmd){
            case 0x01:{
                if(storage.size() != 6){
                    msgResponseRequest(0x03);
                 }
                 else if(storage[0] != 0x0a || storage[1] != 0x0a || storage[2] != 0x01 || storage[3] != 0x02 || storage[4] != 0x03 || storage[5] != 0x04)
                         {
            msgResponseRequest(0x03);
                 } break;
             }
            case 0x02: emit sigBegin(); emit netsigFALSE(); break;
            case 0x03: emit sigShoot(storage[0], storage[1]); break;
            case 0x10: emit sigResponseRequest(storage[0]); break;
            case 0x11: emit sigResponseShoot(storage);
            default: break;
        }
    }
}
