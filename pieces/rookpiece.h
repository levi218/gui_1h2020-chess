#ifndef ROOKPIECE_H
#define ROOKPIECE_H

#include "straightmovingpiece.h"
class RookPiece : public StraightMovingPiece
{
public:
    RookPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
};

#endif // ROOKPIECE_H
