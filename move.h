#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include "gamemanager.h"
#include <QPoint>
#include "chesspiece.h"
#include <QDataStream>
class ChessPiece;
class GameManager;
class Move : public QObject
{
    Q_OBJECT
public:
    explicit Move(GameManager *manager);
    Move(GameManager *manager, QPoint origin, QPoint destination, int option = 0);
    GameManager *manager;
    ChessPiece *source;
    ChessPiece *target;
    QPoint origin;
    QPoint destination;
    bool isPromoted;
    int option;
    void commit();
    void revert();
    friend QDataStream& operator<<(QDataStream& out, const Move& r){
        out<<r.origin<< r.destination << r.option;
        return out;
    }
    friend QDataStream& operator>>(QDataStream& in, Move& r){
        in>>r.origin>> r.destination >> r.option;
        return in;
    }
signals:

public slots:
};

#endif // MOVE_H
