#-------------------------------------------------
#
# Project created by QtCreator 2018-03-13T20:46:34
#
#-------------------------------------------------

QT       += core gui  network

QMAKE_CXXFLAGS += -std=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Battleship
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        startwindow.cpp \
    boardsquare.cpp \
    button.cpp \
    game.cpp \
    connects.cpp \
    myclient.cpp \
    myserver.cpp \
    network.cpp \
    controller.cpp

HEADERS += \
        startwindow.h \
    boardsquare.h \
    button.h \
    game.h \
    variables.h \
    connects.h \
    myclient.h \
    myserver.h \
    network.h \
    controller.h

FORMS += \
        startwindow.ui \
    boardsquare.ui

RESOURCES += \
    pictures.qrc

DISTFILES +=
