#ifndef KNIGHTPIECE_H
#define KNIGHTPIECE_H

#include <chesspiece.h>

class KnightPiece : public ChessPiece
{
public:
    KnightPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
};

#endif // KNIGHTPIECE_H
