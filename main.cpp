#include "mainwindow.h"
#include <QApplication>
#include "localmultiplayer.h"
#include "promotion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LocalMultiplayer w;
    w.show();

    return a.exec();
}
