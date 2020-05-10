#include "board.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "gamemanager.h"
Board::Board(QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setZValue(-1);
}
void Board::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug()<< "board clicked";
}
GameManager* Board::getGameManager(){
    return (GameManager*) this->parent();
}

void Board::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2){
                painter->fillRect(i*SIZE+OFFSET,j*SIZE+OFFSET,SIZE,SIZE,QColor(179,141,114));
            }else{
                painter->fillRect(i*SIZE+OFFSET,j*SIZE+OFFSET,SIZE,SIZE, QColor(255,231,214));
            }
        }
    }

    for (int i=0;i<8;i++){
        //row - the left side
        painter->save();
        if(getGameManager()->mySide==black){
            painter->translate(OFFSET,i*SIZE+SIZE/2+OFFSET);
            painter->rotate(180);
        }
        else{
            painter->translate(0,i*SIZE+SIZE/2+OFFSET);
        }
        painter->drawText( 0,0,QString::number(i+1));
        painter->restore();

        //row - the right side
        painter->save();
        if(getGameManager()->mySide==black){
            painter->translate(SIZE*8+2*OFFSET,i*SIZE+SIZE/2+OFFSET);
            painter->rotate(180);
        }
        else{
            painter->translate(SIZE*8+OFFSET,i*SIZE+SIZE/2+OFFSET);
        }
        painter->drawText( 0,0,QString::number(i+1));
        painter->restore();

        //column - top
        painter->save();
        if(getGameManager()->mySide==black){
            painter->translate(i*SIZE+SIZE/2+OFFSET,SIZE*8+OFFSET);
            painter->rotate(180);
        }
        else{
            painter->translate(i*SIZE+SIZE/2+OFFSET,OFFSET);
        }
        painter->drawText(0,0,QChar::fromLatin1(i+'A'));
        painter->restore();

        //column - bottom
        painter->save();
        if(getGameManager()->mySide==black){
            painter->translate(i*SIZE+SIZE/2+OFFSET,0);
            painter->rotate(180);
        }
        else{
            painter->translate(i*SIZE+SIZE/2+OFFSET,SIZE*8+2*OFFSET);
        }
        painter->drawText(0,0,QChar::fromLatin1(i+'A'));
        painter->restore();
    }
}

QRectF Board::boundingRect() const{
    return QRectF(0,0,8*SIZE+2*OFFSET,8*SIZE+2*OFFSET);
}
