#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include "side.h"
#include "move.h"
#include "chesspiece.h"

class ChessPiece;
class Move;
class GameManager : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = 0);
//    void movePiece(ChessPiece *piece, QPoint prev, QPoint cur, bool logged);
    ChessPiece* getPieceAt(QPoint pos);
    void newMatch();
    QList<Move*> history;
    int turnNumber;
    Side currentSide;
    Side mySide;
    ChessPiece *whiteKing;
    ChessPiece *blackKing;
    void promote(QPoint origin, QPoint destination, int type);
    void isCheckmated(Side side);
protected:
    QList<ChessPiece *> pieces;
signals:
//    void pieceMoved(ChessPiece* piece, QPoint prev, QPoint cur);
        void pieceMoved(Move *move);

//    void castling(ChessPiece* king, bool king_side);
    void pawnReachFinalRow(QPoint origin, QPoint destination);
public slots:
    void pieceTryToMove(ChessPiece* piece, QPoint prev, QPoint cur);
};

#endif // GAMEMANAGER_H
