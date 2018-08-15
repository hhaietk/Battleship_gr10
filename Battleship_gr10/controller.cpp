/**
  * @file controller.cpp
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#include "controller.h"

controller::controller(QObject *parent) : QObject(parent)
{

}

// Controller is making sure only one client/server gets created, inherits from client.h server.h
void controller::CdisconnectFromServer()
{
    client->disconnectFromServer();
}

void controller::createServer(quint16 port)
{
    server = new MyServer();
    server->startServer(port);
    isServer = true;

    connect(server,&MyServer::connected,this,&controller::Cconnected);
    connect(server,&MyServer::disconnected,this,&controller::Cdisconnected);
    connect(server,&MyServer::sigParam,this,&controller::CsigParam);
    connect(server,&MyServer::sigBegin,this,&controller::CsigBegin);
    connect(server,&MyServer::netsigFALSE,this,&controller::sigFALSE);
    connect(server,&MyServer::sigShoot,this,&controller::CsigShoot);
    connect(server,&MyServer::sigResponseRequest,this,&controller::CsigResponseRequest);
    connect(server,&MyServer::sigResponseShoot,this,&controller::CsigResponseShoot);

    connect(this,&controller::CmsgParam,server,&MyServer::msgParam);
    connect(this,&controller::CmsgBegin,server,&MyServer::msgBegin);
    connect(this,&controller::CmsgShoot,server,&MyServer::msgShoot);
    connect(this,&controller::CmsgResponseRequest,server,&MyServer::msgResponseRequest);
    connect(this,&controller::CmsgResponseShoot,server,&MyServer::msgResponseShoot);

}

void controller::createClient(QString IP, quint16 port)
{
    client = new MyClient();
    client->connectToServer(IP, port);

    connect(client,&MyClient::connected,this,&controller::Cconnected);
    connect(client,&MyClient::disconnected,this,&controller::Cdisconnected);
    connect(client,&MyClient::sigParam,this,&controller::CsigParam);
    connect(client,&MyClient::sigBegin,this,&controller::CsigBegin);
    connect(server,&MyClient::netsigFALSE,this,&controller::sigFALSE);
    connect(client,&MyClient::sigShoot,this,&controller::CsigShoot);
    connect(client,&MyClient::sigResponseRequest,this,&controller::CsigResponseRequest);
    connect(client,&MyClient::sigResponseShoot,this,&controller::CsigResponseShoot);

    connect(this,&controller::CmsgParam,client,&MyClient::msgParam);
    connect(this,&controller::CmsgBegin,client,&MyClient::msgBegin);
    connect(this,&controller::CmsgShoot,client,&MyClient::msgShoot);
    connect(this,&controller::CmsgResponseRequest,client,&MyClient::msgResponseRequest);
    connect(this,&controller::CmsgResponseShoot,client,&MyClient::msgResponseShoot);
    isServer = false;
}
