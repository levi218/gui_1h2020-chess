#include "bishoppiece.h"
#include "straightmovingpiece.h"
#include <QDebug>
BishopPiece::BishopPiece(QObject *parent,int board_x, int board_y, Side side)
    : StraightMovingPiece(parent,board_x,board_y,side)
{
    this->name = QString("B");
    if(this->side == black){
        this->image = QPixmap(":/images/b_bishop_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_bishop_png_128px.png");
    }
}

QList<QPoint> BishopPiece::getMoveList(){
    QList<QPoint> result;
    result.append(getMoveListInDir(-1,-1));
    result.append(getMoveListInDir(1,-1));
    result.append(getMoveListInDir(-1,1));
    result.append(getMoveListInDir(1,1));

    return result;
}
