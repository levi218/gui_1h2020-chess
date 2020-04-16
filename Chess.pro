#-------------------------------------------------
#
# Project created by QtCreator 2020-04-12T02:39:16
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chesspiece.cpp \
    board.cpp \
    gamemanager.cpp \
    pieces/knightpiece.cpp \
    pieces/pawnpiece.cpp \
    pieces/bishoppiece.cpp \
    pieces/rookpiece.cpp \
    pieces/kingpiece.cpp \
    pieces/queenpiece.cpp \
    pieces/straightmovingpiece.cpp \
    localmultiplayer.cpp \
    promotion.cpp \
    move.cpp

HEADERS  += mainwindow.h \
    chesspiece.h \
    board.h \
    gamemanager.h \
    side.h \
    pieces/knightpiece.h \
    pieces/pawnpiece.h \
    pieces/bishoppiece.h \
    pieces/rookpiece.h \
    pieces/kingpiece.h \
    pieces/queenpiece.h \
    pieces/straightmovingpiece.h \
    localmultiplayer.h \
    promotion.h \
    move.h

FORMS    += mainwindow.ui \
    localmultiplayer.ui \
    promotion.ui

RESOURCES += \
    resources.qrc
