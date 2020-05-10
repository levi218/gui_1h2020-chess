#include "gamemanager.h"
#include <QGraphicsScene>
#include "board.h"
#include <QDebug>
#include "pieces/bishoppiece.h"
#include "pieces/kingpiece.h"
#include "pieces/knightpiece.h"
#include "pieces/pawnpiece.h"
#include "pieces/queenpiece.h"
#include "pieces/rookpiece.h"

GameManager::GameManager(QObject *parent) : QGraphicsScene(parent)
{
    this->currentSide = Side::white;
    this->mySide = Side::white;
    newMatch();
}
void GameManager::newMatch(){
    clear();
    this->addItem(new Board(this));
        // init black pieces;
    this->addItem(new RookPiece(this,0,0,Side::black)); // rook
    this->addItem(new KnightPiece(this,1,0,Side::black)); // knight
    this->addItem(new BishopPiece(this,2,0,Side::black)); // bishop
    this->addItem(new QueenPiece(this,3,0,Side::black)); // queen
    blackKing = new KingPiece(this,4,0,Side::black);
    this->addItem(blackKing); // king
    this->addItem(new BishopPiece(this,5,0,Side::black)); // bishop
    this->addItem(new KnightPiece(this,6,0,Side::black)); // knight
    this->addItem(new RookPiece(this,7,0,Side::black)); // rook
    for(int i =0;i<8;i++){
        this->addItem(new PawnPiece(this,i,1,Side::black)); // pawns
    }
    //    this->addItem(new PawnPiece(this,1,6,Side::black)); // pawn for testing promotion

    // init white pieces;
    this->addItem(new RookPiece(this,0,7,Side::white)); // rook
    this->addItem(new KnightPiece(this,1,7,Side::white)); // knight
    this->addItem(new BishopPiece(this,2,7,Side::white)); // bishop
    this->addItem(new QueenPiece(this,3,7,Side::white)); // queen
    whiteKing = new KingPiece(this,4,7,Side::white);
    this->addItem(whiteKing); // king
    this->addItem(new BishopPiece(this,5,7,Side::white)); // bishop
    this->addItem(new KnightPiece(this,6,7,Side::white)); // knight
    this->addItem(new RookPiece(this,7,7,Side::white)); // rook
    for(int i =0;i<8;i++){
        this->addItem(new PawnPiece(this,i,6,Side::white)); // pawns
    }
    //    this->addItem(new PawnPiece(this,1,1,Side::white)); // pawn for testing promotion

    //exp1
//    this->addItem(new BishopPiece(this,1,0,Side::black)); // bishop
//    blackKing = new KingPiece(this,2,0,Side::black);
//    this->addItem(blackKing); // king
//    this->addItem(new BishopPiece(this,1,4,Side::black)); // bishop
//    for(int i =0;i<3;i++){
//        this->addItem(new PawnPiece(this,i,1,Side::black)); // pawns
//    }

//    // init white pieces;
//    this->addItem(new RookPiece(this,3,7,Side::white)); // rook
//    this->addItem(new BishopPiece(this,5,3,Side::white)); // bishop
//    whiteKing = new KingPiece(this,4,7,Side::white);
//    this->addItem(whiteKing); // king
//    this->addItem(new PawnPiece(this,7,6,Side::white)); // pawns
//    this->addItem(new PawnPiece(this,5,6,Side::white)); // pawns
//    this->addItem(new PawnPiece(this,6,5,Side::white)); // pawns

//    exp2
//    blackKing = new KingPiece(this,6,5,Side::black);
//    this->addItem(blackKing); // king
//    this->addItem(new RookPiece(this,0,7,Side::black)); // rook

//    whiteKing = new KingPiece(this,4,7,Side::white);
//    this->addItem(whiteKing); // king

    for(QGraphicsItem *piece : this->items()){
        if(dynamic_cast<ChessPiece*>(piece))
            connect((ChessPiece*)piece,SIGNAL(requestMove(ChessPiece*,QPoint,QPoint)),this,SLOT(pieceTryToMove(ChessPiece*,QPoint,QPoint)));
    }
    this->turnNumber = 0;

}

bool GameManager::isCheckmated(Side side){
    KingPiece *king = side==white?(KingPiece *)whiteKing:(KingPiece *)blackKing;

    if(!king->inCheck()){
        // not checkmate
        qDebug() << "Not checkmated";
        return false;
    }
    //    //therefore if we get here on out, we are currently in check...

    for(QGraphicsItem *p : this->items()){
        if(dynamic_cast<ChessPiece*>(p)!=nullptr){
            ChessPiece *piece = (ChessPiece*) p;
            if(piece->side==side){
                // check each of our piece;
                for(QPoint dest : piece->getMoveList()){
                    Move m(this,QPoint(piece->board_x,piece->board_y),dest);
                    m.commit();
                    if(!king->inCheck()){
                        // can get out of checkmate
                        qDebug() << "Can get out of checkmate";
                        m.revert();
                        return false;
                    }
                    m.revert();
                }

            }
        }
    }
    // cant get out of checkmate
    qDebug() << "Cant get out of checkmate";
    return true;

}

void GameManager::promote(QPoint origin, QPoint destination, int type){
    Move * move = new Move(this,origin,destination,type);
    move->commit();
    emit pieceMoved(move);
    this->history.push_back(move);
    this->update();

}


ChessPiece* GameManager::getPieceAt(QPoint pos){
    for(QGraphicsItem *p : this->items()){
        if(dynamic_cast<ChessPiece*>(p)!=nullptr){
            if(pos.x() == ((ChessPiece*)p)->board_x
                    && pos.y() == ((ChessPiece*)p)->board_y){

                return ((ChessPiece*)p);
            }
        }
    }
    return nullptr;
}
void GameManager::pieceTryToMove(ChessPiece *piece, QPoint prev, QPoint cur){
    if(currentSide==mySide && piece->side==currentSide){
        if(piece->name=="P"
                &&((piece->side==black&&cur.y()==7)
                   ||(piece->side==white&&cur.y()==0))){
            emit pawnReachFinalRow(prev, cur);
        }else{
            Move * move = new Move(this,prev,cur);
            move->commit();
            emit pieceMoved(move);
            this->history.push_back(move);
            this->update();
        }
    }
}

