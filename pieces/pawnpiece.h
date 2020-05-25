#ifndef PAWNPIECE_H
#define PAWNPIECE_H

#include "chesspiece.h"
class PawnPiece : public ChessPiece
{
public:
    PawnPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
};

#endif // PAWNPIECE_H
