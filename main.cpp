#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include "localmultiplayer.h"
#include "promotion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;


    LocalMultiplayer w;
    w.show();

    return a.exec();
}
