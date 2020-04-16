#include "chesspiece.h"
#include <QGraphicsItem>
#include <QPainter>
#include<QDebug>
#include <QGraphicsSceneMouseEvent>
#include "gamemanager.h"
ChessPiece::ChessPiece(QObject *parent,int board_x, int board_y, Side side)
    : QObject(parent), QGraphicsItem(),name(QString("default")),
      board_x(board_x),
      board_y(board_y),
      side(side),
      isAlive(true),
      isSelected(false),
      isMoved(false)
{
}
GameManager* ChessPiece::getGameManager(){
    return (GameManager*) this->parent();
}

void ChessPiece::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    if(isAlive){
        painter->save();
        painter->translate(((float)board_x+0.5f)*SIZE,((float)board_y+0.5f)*SIZE);
        if(getGameManager()->mySide==black){
            painter->rotate(180);
        }
        if(this->image.isNull()){
            // draw place holder if there are no image
            if(this->side == Side::black){
                painter->fillRect(-0.25f*SIZE+10,-0.25f*SIZE,SIZE/2,SIZE/2,Qt::black);
            }
            else{
                painter->fillRect(-0.25f*SIZE+10,-0.25f*SIZE,SIZE/2,SIZE/2,Qt::white);
            }
        }else{
            // draw image
            painter->drawPixmap(-0.5f*SIZE+10,-0.5f*SIZE,SIZE,SIZE,this->image);

        }
        painter->restore();
        if(this->isSelected){
            // draw place where we can move to
            for(QPoint cell : getMoveList()){
                 painter->fillRect(cell.x()*SIZE+10,cell.y()*SIZE,SIZE,SIZE, QColor(255,0,0,100));
            }

            // draw green border around selected piece
            painter->setPen(QPen(Qt::green, 3));
            painter->drawRect(board_x*SIZE+10,board_y*SIZE,SIZE,SIZE);
        }
        // draw boundingRect for testing
        painter->setPen(QPen(Qt::red, 1));
        painter->drawRect(this->boundingRect());
    }
}
QList<QPoint> ChessPiece::getMoveList(){
    QList<QPoint> result;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(!(i==board_x && j==board_y)){
                result.push_back(QPoint(i,j));
            }
        }
    }
    return result;
}

QRectF ChessPiece::boundingRect() const{
    if(this->isSelected){
        return QRectF(0,0,8*SIZE+10,8*SIZE);
    }else{
        return QRectF(board_x*SIZE+10,board_y*SIZE,SIZE,SIZE);
    }
}
void ChessPiece::moveTo(QPoint dest){
    this->isMoved = true;
    this->board_x = dest.x();
    this->board_y = dest.y();
    prepareGeometryChange();
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isSelected){
        // move the piece
        QPoint mousePos = event->scenePos().toPoint();
        QPoint dest(mousePos.x()/SIZE, mousePos.y()/SIZE);

        // check allowed cell
        if(getMoveList().contains(dest)){
            emit requestMove(this,QPoint(board_x,board_y),dest);
        }
    }

    // deselect/select
    this->isSelected = !this->isSelected;
    // set zValue so that selected pieces is on top, and update bounding rect to cover whole board
    if(this->isSelected) this->setZValue(99999); else this->setZValue(0);
    prepareGeometryChange();
    // call update to repaint the piece
//    this->update();
//    QGraphicsItem::mousePressEvent(event);
}
