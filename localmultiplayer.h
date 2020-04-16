#ifndef LOCALMULTIPLAYER_H
#define LOCALMULTIPLAYER_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QtNetwork>
namespace Ui {
class LocalMultiplayer;
}

class LocalMultiplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit LocalMultiplayer(QWidget *parent = 0);
    ~LocalMultiplayer();

private:
    Ui::LocalMultiplayer *ui;
    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    MainWindow *currentGame = nullptr;
    void stopListenning();
private slots:
    void on_btnHost_clicked();
    void on_btnJoin_clicked();
    void onClientConnected();
    void onConnectedToServer();
    void on_btnPlayLocal_clicked();
    void onClientDisconnected();
    void onClientGameClosed();
};

#endif // LOCALMULTIPLAYER_H
