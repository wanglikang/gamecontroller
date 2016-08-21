#include "mainwindow.h"
#include <QApplication>
#include <doctormariogame.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DoctorMarioGame game;
    game.show();


    return a.exec();
}
