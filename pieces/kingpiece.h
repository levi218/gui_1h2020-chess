#ifndef KINGPIECE_H
#define KINGPIECE_H

#include "chesspiece.h"
class KingPiece : public ChessPiece
{
public:
    KingPiece(QObject *parent,int board_x, int board_y, Side side);
    virtual QList<QPoint> getMoveList();
    bool inCheck();
private:
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif // KINGPIECE_H
