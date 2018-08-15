/**
  * @file StartWindow.hpp
  * @brief Header of class StartWindow
  * @author J. Hager
  * */

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QRadioButton>
#include "boardsquare.h"
//#include "connects.h"

namespace Ui {
class StartWindow;
}

/// @brief class StartWindow which inherits from QWidget
class StartWindow : public QWidget
{
    Q_OBJECT

public:

    /// @brief Constructor: initializes StartWindow
    explicit StartWindow(QObject *parent = 0);

    /// @brief Destructor of StartWindow
    ~StartWindow();

    //Connects* con;

    /// @brief creates a new object for boardsquare
    BoardSquare* boardsquare;

    QString _qsLogindata;

signals:
    /** @brief signal clientClicked
     *
     *  Emits the host address and port to network for connection
     *  @param host address
     *  @param port address
     * */
    void clientClicked(QString, quint16);

    /** @brief signal serverClicked
     *
     *  Emits the port to network for connection
     *  @param port address
     */
    void serverClicked(quint16);

    /** @brief signal ButtonDisconnectClicked
     *
     *  Is emitted when the connection should be disconnected
     */
    void ButtonDisconnectClicked();

public slots:
    /** @brief slot on_pbstartgame_clicked
     *
     *  To open the boardsquare window
     */
    void on_pbstartgame_clicked();

    /** @brief slot on_pbquit_clicked
     *
     * To close the startwindow
     */
    void on_pbquit_clicked();

    /** @brief slot ButtonClientClicked
     *
     *  For the signal to emit the login data to network
     */
    void RadioButtonClicked();
    //void ButtonClientClicked();

    /** @brief slot chooseServer
     *
     *  If server is chosen, no host address can be entered
     */
    void chooseServer();

    /**
     * @brief slot chooseClient
     *
     * If client is chosen, host address and port can be entered
     */
    void chooseClient();

    /**
     * @brief slot SteadyConnect
     *
     * To enable the start button if a steady connection from the network exists
     */
    void SteadyConnect();

    /**
     * @brief slot Connectsuccessful
     *
     * To signal that
     */
   void Connectsuccessful();


    //void RadioButtonServerCLicked();
    //void ButtonServerClicked();
    //void setLogin();


private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
