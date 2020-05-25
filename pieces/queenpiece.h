#ifndef QUEENPIECE_H
#define QUEENPIECE_H

#include "straightmovingpiece.h"
class QueenPiece : public StraightMovingPiece
{
public:
    QueenPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
};

#endif // QUEENPIECE_H
