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
    qDebug()<<"destroying window";
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
void MainWindow::closeEvent(QCloseEvent *event){
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
    if(gameManager->currentSide == Side::black) {
        gameManager->currentSide = Side::white;
        ui->lblTurn->setText(tr("White turn!"));
        if(!tcpSocket) gameManager->mySide = Side::white;
        ui->tblHistory->setRowCount(gameManager->turnNumber);
        ui->tblHistory->setItem(gameManager->turnNumber-1,1,
                                new QTableWidgetItem(move->source->name + QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y())));
    }
    else{
        gameManager->currentSide = Side::black;
        if(!tcpSocket) gameManager->mySide = Side::black;
        ui->lblTurn->setText(tr("Black turn!"));
        gameManager->turnNumber +=1;
        ui->tblHistory->setRowCount(gameManager->turnNumber);
        ui->tblHistory->setItem(gameManager->turnNumber-1,0,new QTableWidgetItem(move->source->name + QChar::fromLatin1(move->destination.x()+'a')+QString::number(move->destination.y())));
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


void MainWindow::on_btnCHeck_clicked()
{
}

void MainWindow::on_btnCheck_clicked()
{
    gameManager->isCheckmated(white);
    gameManager->isCheckmated(black);

}
