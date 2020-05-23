#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QTcpServer>
#include "gamemanager.h"
#include <chesspiece.h>
#include "pieces/kingpiece.h"
#include "pieces/pawnpiece.h"
#include "move.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent, QTcpSocket* socket, Side side);
    ~MainWindow();
protected:
     void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    GameManager *gameManager;
//    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    void nextTurn(Move *move);
signals:
    void windowClosed();
private slots:
    void onIncomingPacket();
    void onPieceMoved(Move *move);
//    void onCastling(ChessPiece* piece, bool isKingSide);
    void onPromotion(QPoint origin, QPoint destination);
};

#endif // MAINWINDOW_H
