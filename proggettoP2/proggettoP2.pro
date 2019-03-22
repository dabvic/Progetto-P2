#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T21:38:25
#
#-------------------------------------------------

QT       += core gui \
             multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proggettoP2
TEMPLATE = app


SOURCES += \
    Game.cpp \
    main.cpp \
    Drops.cpp \
    Container.cpp \
    Health.cpp \
    Player.cpp \
    Score.cpp \
    Spawner.cpp \
    scoremanager.cpp \
    users.cpp

HEADERS  += \
    Game.h \
    Drops.h \
    Score.h \
    Player.h \
    Health.h \
    Spawner.h \
    Container.h \
    scoremanager.h \
    users.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
