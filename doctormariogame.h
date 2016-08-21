#ifndef DOCTORMARIOGAME_H
#define DOCTORMARIOGAME_H

#include <QMainWindow>
#include <doctormario.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>

#include "aboutdialog.h"

class DoctorMarioGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit DoctorMarioGame(QWidget *parent = 0);

signals:

public slots:

private slots:
    void updateStatus(int virus_Num,int level);
    void levelSetting();
    void aboutQt();
    void aboutDoctorMario();
private:
    void createMenu();
    void createWidget();
    void createConnects();



    DoctorMario *game;
    QPushButton *pauseButton;
    QPushButton *newGameButton;
    QPushButton *startButton;


    QLabel *virusLabel;
    QLCDNumber *virusNum;

    QLabel *levelLabel;
    QLCDNumber *levelNum;

    QLabel *marioPic;

    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QVBoxLayout *leftLayout;

    QWidget *centerWidget;

};

#endif // DOCTORMARIOGAME_H
