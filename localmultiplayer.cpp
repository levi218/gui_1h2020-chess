#include "localmultiplayer.h"
#include "ui_localmultiplayer.h"
#include "mainwindow.h"
#include <QMessageBox>
LocalMultiplayer::LocalMultiplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LocalMultiplayer)
{
    ui->setupUi(this);
}

LocalMultiplayer::~LocalMultiplayer()
{
    delete ui;
}

void LocalMultiplayer::on_btnHost_clicked()
{
    if(tcpServer==nullptr){
        tcpServer = new QTcpServer(this);
        connect(tcpServer, &QTcpServer::newConnection, this, &LocalMultiplayer::onClientConnected);
        if (!tcpServer->listen(QHostAddress::Any, ui->txtPort->text().toInt())) {
            QMessageBox::critical(this, tr("Fortune Server"),
                                  tr("Unable to start the server: %1.")
                                  .arg(tcpServer->errorString()));
            //        close();
            return;
        }
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                    ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        statusBar()->showMessage(tr("Listenning on: %1:%2")
                                 .arg(ipAddress).arg(tcpServer->serverPort()));
        ui->txtPort->setEnabled(false);
        ui->btnHost->setText("Stop listenning");
    }else{
        stopListenning();
    }
}
void LocalMultiplayer::stopListenning(){
    qDebug() << "stopped listenning";
    if(tcpServer){
        if(tcpServer->isListening()){
             tcpServer->close();
        }
        tcpServer->deleteLater();
        tcpServer = nullptr;
    }
    ui->txtPort->setEnabled(true);
    ui->btnHost->setText("Host");
    statusBar()->showMessage("Disconnected");

    qDebug() << "finished listenning";
}
void LocalMultiplayer::onClientDisconnected(){
    qDebug() << "client disconnected";
    if(currentGame){
        delete currentGame;
        currentGame = nullptr;
    }
    show();
    if(tcpServer){
        stopListenning();
    }
    qDebug() << "finished disconnect";
}

void LocalMultiplayer::onClientConnected(){
    // check exist
    tcpSocket = tcpServer->nextPendingConnection();
    tcpServer->close();
    connect(tcpSocket, &QAbstractSocket::disconnected,
            this, &LocalMultiplayer::onClientDisconnected);
    connect(tcpSocket, &QAbstractSocket::disconnected,
            tcpSocket, &QObject::deleteLater);
    currentGame = new MainWindow(nullptr,tcpSocket, Side::white);
    connect(currentGame,&MainWindow::windowClosed,this,&LocalMultiplayer::onClientGameClosed);
    currentGame->show();
    hide();
}

void LocalMultiplayer::onConnectedToServer(){
    currentGame = new MainWindow(nullptr,tcpSocket, Side::black);
    connect(currentGame,&MainWindow::windowClosed,this,&LocalMultiplayer::onClientGameClosed);
    currentGame->show();
    hide();
}

void LocalMultiplayer::onClientGameClosed(){
    qDebug() << "onclientClosed";
    if(currentGame){
        delete currentGame;
        currentGame = nullptr;
    }
    if(tcpSocket!=nullptr){
        tcpSocket->disconnectFromHost();
    }
    statusBar()->showMessage("Disconnected");
    show();
    qDebug() << "finished onclientClosed";
}

void LocalMultiplayer::on_btnJoin_clicked()
{
    if(tcpServer){
        stopListenning();
    }
    //check exist
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::connected, this, &LocalMultiplayer::onConnectedToServer);
    connect(tcpSocket, &QAbstractSocket::disconnected,
            this, &LocalMultiplayer::onClientDisconnected);
    tcpSocket->connectToHost(ui->txtHostIp->text(),ui->txtHostPort->text().toInt());
}

void LocalMultiplayer::on_btnPlayLocal_clicked()
{
    if(tcpServer){
        stopListenning();
    }
    currentGame = new MainWindow(nullptr);
    connect(currentGame,&MainWindow::windowClosed,this,&LocalMultiplayer::onClientGameClosed);
    currentGame->show();
    hide();
}
