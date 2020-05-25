#include "knightpiece.h"

KnightPiece::KnightPiece(QObject *parent,int board_x, int board_y, Side side)
    : ChessPiece(parent,board_x,board_y,side)
{
    this->name = QString("N");
    if(this->side == black){
        this->image = QPixmap(":/images/b_knight_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_knight_png_128px.png");
    }
}

QList<QPoint> KnightPiece::getMoveList(){
    QList<QPoint> result;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(((abs(board_x-x)==1 && abs(board_y-y) ==2) || (abs(board_x-x)==2 && abs(board_y-y) ==1)) && !(x==board_x && y==board_y)){
                QPoint p(x,y);
                ChessPiece* pieceAtP = getGameManager()->getPieceAt(p);
                if(pieceAtP!=nullptr){
                    if(pieceAtP->side!=side){
                        result.push_back(p);
                    }
                }else{
                    result.push_back(p);
                }
            }
        }
    }
    return result;
}
