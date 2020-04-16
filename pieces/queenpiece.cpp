#include "queenpiece.h"
#include "rookpiece.h"
#include "bishoppiece.h"
QueenPiece::QueenPiece(QObject *parent,int board_x, int board_y, Side side)
    : StraightMovingPiece(parent,board_x,board_y,side)
{
    this->name = QString("Q");
    if(this->side == black){
        this->image = QPixmap(":/images/b_queen_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_queen_png_128px.png");
    }
}


QList<QPoint> QueenPiece::getMoveList(){
    QList<QPoint> result;
    result.append(getMoveListInDir(-1,-1));
    result.append(getMoveListInDir(1,-1));
    result.append(getMoveListInDir(-1,1));
    result.append(getMoveListInDir(1,1));
    result.append(getMoveListInDir(-1,0));
    result.append(getMoveListInDir(1,0));
    result.append(getMoveListInDir(0,1));
    result.append(getMoveListInDir(0,-1));
    return result;
}
