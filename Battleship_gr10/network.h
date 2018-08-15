/**
  * @file network.h
  * @brief Source of class network
  * @author Stefan Gebhardt
  * */

#ifndef NETWORK_H
#define NETWORK_H
#include <QTcpSocket>
#include <QDataStream>

class Network : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief network object
     * */
    explicit Network(QObject *parent = 0);

    QTcpSocket *socket;

    /// Sends data over stream
    QDataStream InOutStream;

    /**
     * @brief setSocket function that creates a socket
     * */
    void setSocket(QTcpSocket * socket);
    /**
     * @brief setSocket function that returns bool when connected/disconnected
     * */
    bool IsConnected = false;
    /**
     * @brief sendMessage test function that was used to send message over network
     * */
    void sendMessage(quint8 QByteArray);

signals:
    /**
     * @brief connected signal for client
     * */
    void connected();
    /**
     * @brief disconnected signal for client
     * */
    void disconnected();
    /**
     * @brief startready signal that makes startbutton usable in gui
     * */
    void startready();
    /**
     * @brief signals get passed through to the controller
     * */
    void sigParam();
    void netsigFALSE();
    void sigBegin();
    void sigShoot(quint8, quint8);
    void sigResponseRequest(quint8);
    void sigResponseShoot(std::vector<quint8>);

public slots:
    /// Returns error message if cant connect
    void connectionError(QAbstractSocket::SocketError socketError);
    /// readMessage reads incoming message
    void readMessage();
    /// socketStateChanged Returns socketstage
    void socketStateChanged(QAbstractSocket::SocketState state);
    /**
     * @brief slots send messages over network depending on cmd variable
     * */
    void msgParam(quint8 size, quint8 ship1, quint8 ship2, quint8 ship3, quint8 ship4);
    void msgBegin();
    void msgShoot(quint8 x, quint8 y);
    void msgResponseRequest(quint8 requeststatus);
    void msgResponseShoot(quint8 shootvalue, std::vector<std::pair<int, int>> vector);
};

#endif // NETWORK_H
