#include "move.h"
#include "pieces/bishoppiece.h"
#include "pieces/rookpiece.h"
#include "pieces/knightpiece.h"
#include "pieces/pawnpiece.h"
#include "pieces/queenpiece.h"
#include "pieces/kingpiece.h"
Move::Move(GameManager *manager)
    : manager(manager), isPromoted(false)
{

}

Move::Move(GameManager *manager, QPoint origin, QPoint destination, int option)
    : manager(manager), origin(origin), destination(destination), isPromoted(false), option(option){
}

void Move::commit(){
    source = manager->getPieceAt(origin);
    target = manager->getPieceAt(destination);
    if(!source) return;
    if(source->name=="P"
            &&((source->side==black&&destination.y()==7)
               ||(source->side==white&&destination.y()==0))){
        Side side = source->side;
        ChessPiece *replacedBy;
        switch(option){
        case 1:
            replacedBy = new RookPiece(manager,destination.x(),destination.y(),side);
            break;
        case 2:
            replacedBy =new BishopPiece(manager,destination.x(),destination.y(),side);
            break;
        case 3:
            replacedBy =new KnightPiece(manager,destination.x(),destination.y(),side);
            break;
        case 0:
        default:
            replacedBy =new QueenPiece(manager,destination.x(),destination.y(),side);
            break;
        }
        manager->removeItem(source);
        source->isAlive = false;
        manager->addItem(replacedBy);
        connect(replacedBy,SIGNAL(requestMove(ChessPiece*,QPoint,QPoint)),manager,SLOT(pieceTryToMove(ChessPiece*,QPoint,QPoint)));
        source = replacedBy;
        this->isPromoted = true;
    }

    if(target != nullptr){ // target found
        if(target->side == source->side){
            return;
        }else{
            // take enemy then move
            source->moveTo(destination);
            manager->removeItem(target);
            target->isAlive = false;
        }
    }else{
        // move
        source->moveTo(destination);

        if(source->name=="K"&&abs(destination.x()-origin.x())==2){
            // castling
            if(destination.x()-origin.x()<0){
                ChessPiece *rook = manager->getPieceAt(QPoint(0,destination.y()));
                rook->moveTo(QPoint(3,destination.y()));
                rook->update();
            }
            else{
                ChessPiece *rook = manager->getPieceAt(QPoint(7,destination.y()));
                rook->moveTo(QPoint(5,destination.y()));
                rook->update();
            }
        }
    }

    // check for checkmate
//    if(source->side==white && source->getMoveList().contains(manager->blackKing)){
//        manager->checkmate(black);
//    }else if(source->side==black && source->getMoveList().contains(manager->whiteKing)){
//        manager->checkmate(white);
//    }
    source->update();
    if(target) target->update();
}

void Move::revert(){
    if(!source) return;
    if(target != nullptr){
        // revert target
        source->moveTo(origin);
        manager->addItem(target);
        target->isAlive = true;
    }else{
        // move
        source->moveTo(origin);

        if(source->name=="K"&&abs(destination.x()-origin.x())==2){
            // castling
            if(destination.x()-origin.x()<0){
                ChessPiece *rook = manager->getPieceAt(QPoint(3,destination.y()));
                rook->moveTo(QPoint(0,destination.y()));
                rook->update();
            }
            else{
                ChessPiece *rook = manager->getPieceAt(QPoint(5,destination.y()));
                rook->moveTo(QPoint(7,destination.y()));
                rook->update();
            }
        }
    }
    if(isPromoted){
        Side side = source->side;
        ChessPiece *replacedBy = new PawnPiece(manager, origin.x(), origin.y(), side);
        manager->removeItem(source);
        manager->addItem(replacedBy);
        connect(replacedBy,SIGNAL(requestMove(ChessPiece*,QPoint,QPoint)),manager,SLOT(pieceTryToMove(ChessPiece*,QPoint,QPoint)));
        source = replacedBy;
    }
    source->update();
    if(target) target->update();
}
