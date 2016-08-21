#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <mutils.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        util = new mUtils(this);

        gv1 = ui->GV2;
        QTimer *timer = new QTimer(this);
        QTimer::singleShot(2000,util,SLOT(tocreatemodel()));
        connect(timer,SIGNAL(timeout()),util,SLOT(startToRun()));
       // connect(util,SIGNAL(toshowPic(Mat)),this,SLOT(showGVMat(Mat)));

        timer->start(3000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGVMat(Mat){
    gv1->close();



}
