#include "board.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
Board::Board(QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setZValue(-1);
}
void Board::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug()<< "board clicked";
}

void Board::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    for (int i=0;i<8;i++){
        painter->drawText( 0,i*SIZE+SIZE/2,QString::number(i+1));
    }

    painter->drawText( 0*SIZE+SIZE/2+10,SIZE*8+10,"A");
    painter->drawText( 1*SIZE+SIZE/2+10,SIZE*8+10,"B");
    painter->drawText( 2*SIZE+SIZE/2+10,SIZE*8+10,"C");
    painter->drawText( 3*SIZE+SIZE/2+10,SIZE*8+10,"D");
    painter->drawText( 4*SIZE+SIZE/2+10,SIZE*8+10,"E");
    painter->drawText( 5*SIZE+SIZE/2+10,SIZE*8+10,"F");
    painter->drawText( 6*SIZE+SIZE/2+10,SIZE*8+10,"G");
    painter->drawText( 7*SIZE+SIZE/2+10,SIZE*8+10,"H");


    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2){
                painter->fillRect(i*SIZE+10,j*SIZE,SIZE,SIZE,QColor(179,141,114));
            }else{
                painter->fillRect(i*SIZE+10,j*SIZE,SIZE,SIZE, QColor(255,231,214));
            }
        }
    }
}

QRectF Board::boundingRect() const{
    return QRectF(0,0,8*SIZE+10,8*SIZE+10);
}
