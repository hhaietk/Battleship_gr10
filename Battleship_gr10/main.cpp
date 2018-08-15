#include "connects.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // StartWindow w;
    Connects con;
    //w.show();

    //test
    //QObject::connect(w.boardsquare, &BoardSquare::buttonPressed1, w.boardsquare, &BoardSquare::outputtest);

    return a.exec();
}
