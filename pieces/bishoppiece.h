#ifndef BISHOPPIECE_H
#define BISHOPPIECE_H

#include "straightmovingpiece.h"
class BishopPiece : public StraightMovingPiece
{
public:
    BishopPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
};

#endif // BISHOPPIECE_H
