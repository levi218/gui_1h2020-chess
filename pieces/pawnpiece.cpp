#include "pawnpiece.h"

PawnPiece::PawnPiece(QObject *parent,int board_x, int board_y, Side side)
    : ChessPiece(parent,board_x,board_y,side)
{
    this->name = QString("P");
    if(this->side == black){
        this->image = QPixmap(":/images/b_pawn_png_128px.png");
    }else{
        this->image = QPixmap(":/images/w_pawn_png_128px.png");
    }
}

QList<QPoint> PawnPiece::getMoveList(){
    QList<QPoint> result;
    if(this->side==white){
        if(board_y==6){
            if(!getGameManager()->getPieceAt(QPoint(board_x, 5))){
                result.append(QPoint(board_x, 5));
                if(!getGameManager()->getPieceAt(QPoint(board_x, 4)))
                    result.append(QPoint(board_x, 4));
            }
        }else if(board_y>0){
            if(!getGameManager()->getPieceAt(QPoint(board_x, board_y-1)))
                result.append(QPoint(board_x, board_y-1));
        }
        // check for enemy
        ChessPiece *enemy = getGameManager()->getPieceAt(QPoint(board_x-1, board_y-1));
        if(enemy && enemy->side!=side)
            result.append(QPoint(board_x-1, board_y-1));
        enemy = getGameManager()->getPieceAt(QPoint(board_x+1, board_y-1));
        if(enemy && enemy->side!=side)
            result.append(QPoint(board_x+1, board_y-1));

    }else

    if(this->side==black){
        if(board_y==1){
            if(!getGameManager()->getPieceAt(QPoint(board_x, 2))){
                result.append(QPoint(board_x, 2));
                if(!getGameManager()->getPieceAt(QPoint(board_x, 3)))
                    result.append(QPoint(board_x, 3));
            }
        }else if(board_y<7){
            if(!getGameManager()->getPieceAt(QPoint(board_x, board_y+1)))
                result.append(QPoint(board_x, board_y+1));
        }
        // check for enemy

        ChessPiece *enemy = getGameManager()->getPieceAt(QPoint(board_x-1, board_y+1));
        if(enemy && enemy->side!=side)
            result.append(QPoint(board_x-1, board_y+1));
        enemy = getGameManager()->getPieceAt(QPoint(board_x+1, board_y+1));
        if(enemy && enemy->side!=side)
            result.append(QPoint(board_x+1, board_y+1));
    }
    return result;
}
