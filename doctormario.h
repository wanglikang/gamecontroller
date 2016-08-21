#ifndef DOCTORMARIO_H
#define DOCTORMARIO_H

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QList>
#include <QTimer>
#include <QTime>


enum k {pill=0,virus=1};
enum col {red=0,yellow=1,blue=2};
enum status{Up,Right,Down,Left};


class PillOrVirus
{

public:
    PillOrVirus(){pillKill=false;linkTo=0;}
    //PillOrVirus(){;}
    PillOrVirus(int x,int y,k initKind,col initColor);
    PillOrVirus(int x ,int y,k initKind);
    PillOrVirus(int x,int y,col initColor);
    PillOrVirus(int x,int y);
    void disableLink();
    void makeMoveTo(int x,int y);

    int loc_x,loc_y;
    k kind;
    bool pillKill;
    col color;
    PillOrVirus *linkTo;

};

struct fallPill
{

    PillOrVirus pill[2];
    bool falling;
    status way;
};

class DoctorMario : public QWidget
{
    Q_OBJECT

    enum {eachGridWidth=20,width=240,height=360};


protected:
    void paintEvent(QPaintEvent *);

public slots:
    int gameLevel()const;
    void setGameLevel(int );
    void startGame();
    void setPause(bool );
    void resetGame();
    void setGirdShow(bool);

public:
    bool running()const;
    DoctorMario(QWidget *parent = 0);
    bool tryMoveTo(int x,int y);
    QSize sizeHint() const;

    ~DoctorMario();
public:
    void pillFalling(void);
    void pillMoveLeft(void);
    void pillMoveRight(void);
    void pillRotate(void);
protected:
    void keyPressEvent(QKeyEvent *k );

signals:
    void virusChanged(int virus_num,int level);
    void aaaa(void);

private slots:
    void updateStatusChange();
    int calTimer(int level);
    void gameOver();
    void initGame();

   // void erase(PillOrVirus sth);


    void mainTimerOut();


private:
    void winTheGame();
    int pillDown(PillOrVirus &pill);
    int twoPillsDown(PillOrVirus *pill);
    void pillsDown(int x,int y);
    int virusNum;
    int level;
    int pillWorkOut(int x,int y,col pCol);
    bool gameEnd;
    void makePills();
    fallPill fallPills;
    QList<PillOrVirus>data;
    QTimer *mainTimer;
    bool pause;
    bool gameRunning;
    bool gridShow;
    bool win;


};

#endif // DOCTORMARIO_H
