#include "chesspiece.h"
#include "kingpiece.h"
KingPiece::KingPiece(QObject *parent,int board_x, int board_y, Side side)
    : ChessPiece(parent,board_x,board_y,side)
{
    this->name = QString("K");
    if(this->side == black){
        this->image = QPixmap(":/images/b_king_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_king_png_128px.png");
    }
}

QList<QPoint> KingPiece::getMoveList(){
    QList<QPoint> result;
    for(int i=board_x-1;i<=board_x+1;i++){
        for(int j=board_y-1;j<=board_y+1;j++){
            QPoint p(i, j);
            if(p.x()>=0 && p.x()<8
                    && p.y()>=0 && p.y()<8
                    && !(i==board_x && j==board_y)){
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
    if(!isMoved){
        // check queen-side rook
        ChessPiece *rook = getGameManager()->getPieceAt(QPoint(0,board_y));
        if(!rook->isMoved
                &&!getGameManager()->getPieceAt(QPoint(1,board_y))
                &&!getGameManager()->getPieceAt(QPoint(2,board_y))
                &&!getGameManager()->getPieceAt(QPoint(3,board_y))){
            result.push_back(QPoint(2,board_y));
        }
        // check king-side rook
        rook = getGameManager()->getPieceAt(QPoint(7,board_y));
        if(!rook->isMoved
                &&!getGameManager()->getPieceAt(QPoint(6,board_y))
                &&!getGameManager()->getPieceAt(QPoint(5,board_y))){
            result.push_back(QPoint(6,board_y));
        }
    }
    return result;
}

bool KingPiece::inCheck(){
    QPoint king_pos(board_x,board_y);
    for(QGraphicsItem *p : getGameManager()->items()){
        if(dynamic_cast<ChessPiece*>(p)!=nullptr){
            ChessPiece *piece = (ChessPiece*) p;
            if(piece->side!=side && piece->getMoveList().contains(king_pos)){
                return true;
            }
        }
    }
    return false;
}
