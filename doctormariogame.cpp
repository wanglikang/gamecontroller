#include "doctormariogame.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
DoctorMarioGame::DoctorMarioGame(QWidget *parent) :
    QMainWindow(parent)
{
    createWidget();
    createMenu();
    createConnects();
    resize(550,450);
    this->setWindowTitle(tr("DoctorMario"));
}

void DoctorMarioGame::createWidget()
{

    centerWidget=new QWidget();
    game= new DoctorMario();
    pauseButton=new QPushButton(tr("Pause"));
    newGameButton=new QPushButton(tr("New Game"));
    startButton =new QPushButton(tr("startGame"));
    virusLabel=new QLabel(tr("Virus number:"));
    virusNum =new QLCDNumber(3);

    levelLabel=new QLabel(tr("Level:"));
    levelNum=new QLCDNumber(2);

    marioPic=new QLabel();
    QPixmap *pic=new QPixmap(":/new/mario.png");
    *pic=pic->scaled(QSize(pic->width()/2,pic->height()/2),
                Qt::KeepAspectRatio);
    marioPic->setPixmap(*pic);
    //marioPic->setScaledContents(true);
   // marioPic->resize(100,336);

    mainLayout=new QHBoxLayout();

    rightLayout=new QVBoxLayout();
    leftLayout =new QVBoxLayout();
    leftLayout->addWidget(levelLabel);
    leftLayout->addWidget(levelNum);
    leftLayout->addSpacing(100);
    //leftLayout->addStretch(1);
    leftLayout->addWidget(virusLabel);
    leftLayout->addWidget(virusNum);
    //rightLayout->addWidget(newGameButton);
    //rightLayout->addWidget(pauseButton);
    rightLayout->addWidget(marioPic);

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(game);
    mainLayout->addLayout(rightLayout);

    centerWidget->setLayout(mainLayout);
    this->setCentralWidget(centerWidget);
}

void DoctorMarioGame::createMenu()
{
    QMenuBar *mainMenuBar=new QMenuBar();

    QMenu *gameMenu=new QMenu(tr("Game"));

    QAction *newGameAction=new QAction(tr("new Game"),0);
    QAction *startAction=new QAction(tr("Start"),0);
    QAction *pauseAction=new QAction(tr("Pause"),0);
    pauseAction->setCheckable(true);
    QAction *exitAction=new QAction(tr("Exit"),0);

    gameMenu->addAction(newGameAction);
    gameMenu->addSeparator();
    gameMenu->addAction(startAction);
    gameMenu->addAction(pauseAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);

    QMenu *settingMenu =new QMenu(tr("Setting"));
    QAction *showGridAction  =new QAction(tr("ShowGrid"),0);
    QAction *levelSetAction  =new QAction(tr("Level"),0);
    showGridAction->setCheckable(true);

    settingMenu->addAction(showGridAction);
    settingMenu->addAction(levelSetAction);

    QMenu *helpMenu=new QMenu(tr("Help"));
    QAction *aboutAction=new QAction(tr("About"),0);
    QAction *aboutQtAction=new QAction(tr("About QT"),0);

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    mainMenuBar->addMenu(gameMenu);
    mainMenuBar->addMenu(settingMenu);
    mainMenuBar->addMenu(helpMenu);

    this->setMenuBar(mainMenuBar);

    connect(newGameAction,SIGNAL(triggered()),game,SLOT(resetGame()));
    connect(startAction,SIGNAL(triggered()),game,SLOT(startGame()));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(pauseAction,SIGNAL(triggered(bool)),game,SLOT(setPause(bool)));
    connect(showGridAction,SIGNAL(triggered(bool)),game,SLOT(setGirdShow(bool)));
    connect(levelSetAction,SIGNAL(triggered()),this,SLOT(levelSetting()));

    connect(aboutQtAction,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutDoctorMario()));

    //connect(newGameAction,SIGNAL(triggered()),game)

}

void DoctorMarioGame::aboutDoctorMario()
{
    AboutDialog dlg;
    dlg.exec();
}

void DoctorMarioGame::updateStatus(int virus_Num, int level)
{
    virusNum->display(virus_Num);
    levelNum->display(level);
}

void DoctorMarioGame::createConnects()
{
    connect(game,SIGNAL(virusChanged(int,int)),this,SLOT(updateStatus(int,int)));
}

void DoctorMarioGame::levelSetting()
{
    QInputDialog dlg;
    dlg.setInputMode(QInputDialog::IntInput);
    dlg.setIntMaximum(20);
    dlg.setIntMinimum(1);
    int level=game->gameLevel();
    level=dlg.getInt(this,tr("Level Select"),tr("Level:"),level,1,25);
    if(game->running()){
        int r=QMessageBox::question(this,tr("Restart the Game?"),tr("Setting the level need to restart the game,YES to continue,NO to cancel"),
                                    QMessageBox::Yes|QMessageBox::No);
        if(r==QMessageBox::Yes)
            game->setGameLevel(level);
    }else{
        game->setGameLevel(level);

    }
}

void DoctorMarioGame::aboutQt()
{
    QMessageBox::aboutQt(this,tr("aboutQt"));
}
