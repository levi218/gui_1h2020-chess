#include "straightmovingpiece.h"

StraightMovingPiece::StraightMovingPiece(QObject *parent,int board_x, int board_y, Side side)
    : ChessPiece(parent,board_x,board_y,side)
{
    this->name = QString("/");
}

QList<QPoint> StraightMovingPiece::getMoveListInDir(int dir_x, int dir_y){
    QList<QPoint> result;
    int cur_x = board_x+dir_x;
    int cur_y = board_y+dir_y;

    while(cur_x>=0 && cur_x<8 && cur_y>=0 && cur_y<8){
        QPoint p(cur_x, cur_y);
        ChessPiece* pieceAtP = getGameManager()->getPieceAt(p);
        if(pieceAtP!=nullptr){
            if(pieceAtP->side!=side){
                result.push_back(p);
            }
            break;
        }else{
            result.push_back(p);
        }
        cur_x+=dir_x;
        cur_y+=dir_y;
    }
    return result;
}
