#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QPoint>
#include "side.h"
#include "gamemanager.h"
class GameManager;
class ChessPiece : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ChessPiece(QObject *parent = 0,int board_x=0, int board_y=0, Side side=Side::black);
    QString name;
    int board_x;
    int board_y;
    Side side;
    bool isAlive;
    bool isSelected;
    bool isMoved;
    virtual QList<QPoint> getMoveList();
    QPixmap image;
    void moveTo(QPoint dest);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    GameManager* getGameManager();
private:
    int SIZE = 64;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
signals:
    void requestMove(ChessPiece* piece, QPoint prev, QPoint cur);
public slots:
};

#endif // CHESSPIECE_H
