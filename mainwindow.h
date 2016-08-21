#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mutils.h>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public:
    mUtils *util;
    QGraphicsView *gv1;
public slots:
    void showGVMat(Mat);


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
