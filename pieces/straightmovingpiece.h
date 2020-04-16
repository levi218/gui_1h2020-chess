#ifndef STRAIGHTMOVINGPIECE_H
#define STRAIGHTMOVINGPIECE_H

#include "chesspiece.h"
class StraightMovingPiece: public ChessPiece
{
public:
    StraightMovingPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveListInDir(int dir_x, int dir_y);
};

#endif // STRAIGHTMOVINGPIECE_H
