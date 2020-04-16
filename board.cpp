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
    for(int i =0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2){
                painter->fillRect(i*SIZE,j*SIZE,SIZE,SIZE,QColor(179,141,114));
            }else{
                painter->fillRect(i*SIZE,j*SIZE,SIZE,SIZE, QColor(255,231,214));
            }
        }
    }
}

QRectF Board::boundingRect() const{
    return QRectF(0,0,8*SIZE,8*SIZE);
}
