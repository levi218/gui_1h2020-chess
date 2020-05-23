#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "chesspiece.h"
#include "board.h"
#include <QDebug>
#include "gamemanager.h"
#include <QtNetwork>
#include <QMessageBox>
#include "promotion.h"
#include <QString>

int rows = 0, cols = 2;
QString gameHistory;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameManager = new GameManager();
    ui->graphicsView->setScene(gameManager);
    QStringList headers = { "White", "Black" };    
    ui->tblHistory->setHorizontalHeaderLabels(headers);
    connect(gameManager,&GameManager::pieceMoved, this, &MainWindow::onPieceMoved);
    connect(gameManager,&GameManager::pawnReachFinalRow, this, &MainWindow::onPromotion);
}
MainWindow::MainWindow(QWidget *parent, QTcpSocket* socket, Side side): MainWindow(parent){
    tcpSocket = socket;
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::onIncomingPacket);
    gameManager->mySide = side;
    if(gameManager->mySide==black){
        QTransform t;
        t.rotate(180);
        ui->graphicsView->setTransform(t);
    }
}

MainWindow::~MainWindow()
{
//    qDebug()<<"destroying window";
    delete ui;
}

void MainWindow::onIncomingPacket(){
    QDataStream stream(tcpSocket);

    stream.setVersion(QDataStream::Qt_5_7);
    stream.startTransaction();
    Move *move = new Move(gameManager);
    stream >> (*move);

    if(!stream.commitTransaction()){
        return;
    }
    move->commit();
    gameManager->history.push_back(move);
    nextTurn(move);
    ui->graphicsView->update();
//    gameManager->update();
//    ui->graphicsView->viewport()->repaint();
}
void MainWindow::closeEvent(QCloseEvent *){
    emit windowClosed();
}

void MainWindow::onPromotion(QPoint origin, QPoint destination){
    // ask for which piece to promote to
    Promotion dialog;
    dialog.setModal(true);
    dialog.exec();
    int type = dialog.getCheckedId();

    gameManager->promote(origin, destination,type);
}
void MainWindow::nextTurn(Move *move){
    QString newPosition;

    if(move->source->name != "P"){
        newPosition = move->source->name;
        if(move->target!=nullptr){//attack
            newPosition += 'x' +QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y()+1);
        }
        else{
            newPosition += QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y()+1);
        }
    }
    else{
        if(move->target!=nullptr){
            newPosition = QChar::fromLatin1(move->origin.x()+'a')+'x' +QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y()+1);
        }
        else{
            newPosition = QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y()+1);
        }
        if(move->isPromoted){
            switch(move->option){
            case 1:
                newPosition += "=R";
                break;
            case 2:
                newPosition += "=B";
                break;
            case 3:
                newPosition += "=K";
            case 0:
            default:
                newPosition += "=Q";
                break;
            }
        }
    }

    if(gameManager->isCheckmated(gameManager->mySide)){
        newPosition = newPosition + "+";
    }

    if(move->source->name=="K"&&abs(move->destination.x()-move->origin.x())==2){
        // castling
        if(move->destination.x()-move->origin.x()<0){
            newPosition = "O-O";
        }
        else{
            newPosition = "O-O-O";
        }
    }    

    if(gameManager->currentSide == Side::black) {
        gameManager->currentSide = Side::white;
        ui->lblTurn->setText(tr("White turn!"));
        if(!tcpSocket) gameManager->mySide = Side::white;
        ui->tblHistory->setRowCount(gameManager->turnNumber);

        ui->tblHistory->setItem(gameManager->turnNumber-1,1,
                                new QTableWidgetItem(newPosition));
//
//        rows = gameManager->turnNumber;
//        gameHistory[rows][0] = move->source->name + QChar::fromLatin1(move->destination.x()+'a') + QString::number(move->destination.y()+1);
//        qDebug() << gameHistory;
    }
    else{
        gameManager->currentSide = Side::black;
        if(!tcpSocket) gameManager->mySide = Side::black;
        ui->lblTurn->setText(tr("Black turn!"));
        gameManager->turnNumber +=1;
        ui->tblHistory->setRowCount(gameManager->turnNumber);
        ui->tblHistory->setItem(gameManager->turnNumber-1,0,new QTableWidgetItem(newPosition));
    }


    if(gameManager->isCheckmated(gameManager->currentSide)){
        QMessageBox::information(this, tr("Game Over"),
                              tr("%1 won the game")
                              .arg(gameManager->currentSide==black?"White ":"Black "));
        this->close();
    }
    // rotate board if needed
    if(gameManager->mySide==white){
        QTransform t;
        t.rotate(0);
        ui->graphicsView->setTransform(t);
    }else{
        QTransform t;
        t.rotate(180);
        ui->graphicsView->setTransform(t);
    }
}

void MainWindow::onPieceMoved(Move *move){
    if(tcpSocket!=nullptr){
        QByteArray block;
        QDataStream stream(&block,QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_7);
        stream<<(*move);
        tcpSocket->write(block);
    }

    nextTurn(move);
    ui->graphicsView->update();
}
