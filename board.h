#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsItem>
class Board : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
private:
    int SIZE = 64;
//    QPixmap image;
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // CHESSPIECE_H
