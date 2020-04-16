#include "rookpiece.h"

RookPiece::RookPiece(QObject *parent,int board_x, int board_y, Side side)
    : StraightMovingPiece(parent,board_x,board_y,side)
{
    this->name = QString("R");
    if(this->side == black){
        this->image = QPixmap(":/images/b_rook_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_rook_png_128px.png");
    }
}


QList<QPoint> RookPiece::getMoveList(){
    QList<QPoint> result;
    result.append(getMoveListInDir(0,-1));
    result.append(getMoveListInDir(0,1));
    result.append(getMoveListInDir(-1,0));
    result.append(getMoveListInDir(1,0));
    return result;
}
