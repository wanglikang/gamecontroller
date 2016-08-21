#include "doctormario.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QShortcut>
#include <QtAlgorithms>
#include <QKeyEvent>


DoctorMario::DoctorMario(QWidget *parent)
    : QWidget(parent)
{
    resize(width,height);
    qDebug()<<width<<"  "<<height;
    qDebug()<<rect();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    mainTimer=new QTimer();
    level=1;
    gridShow=false;
    QWidget::setMaximumSize(width,height);

    connect(mainTimer,SIGNAL(timeout()),this,SLOT(mainTimerOut()));

    initGame();


/////////////////////////////////原程序使用热键方式监听键盘事件，，，，一般的键盘监听事件无法进行响应
//    QShortcut *keyUp=new QShortcut(QKeySequence(Qt::Key_Up),this);
//    QShortcut *keyDown=new QShortcut(QKeySequence(Qt::Key_Down),this);
//    QShortcut *keyRight=new QShortcut(QKeySequence(Qt::Key_Right),this);
//    QShortcut *keyLeft=new QShortcut(QKeySequence(Qt::Key_Left),this);

    //////////////////////////////////处理键盘事件，上下左右，///
    //connect(keyUp,SIGNAL(activated()),this,SLOT(pillRotate()));
    //connect(keyDown,SIGNAL(activated()),this,SLOT(pillFalling()));
    //connect(keyRight,SIGNAL(activated()),this,SLOT(pillMoveRight()));
    //connect(keyLeft,SIGNAL(activated()),this,SLOT(pillMoveLeft()));
    ///////////////////////////////////////////////////////////

    setFocusPolicy(Qt::StrongFocus);
}

void DoctorMario::setGirdShow(bool show){
    gridShow=show;
    update();
}

DoctorMario::~DoctorMario()
{

}

void DoctorMario::setPause(bool p)
{
    if(gameRunning){
        pause=p;
        if(p)
            mainTimer->stop();
        else
            mainTimer->start();
    }
    update();

}

void DoctorMario::resetGame()
{
    initGame();

}

void DoctorMario::winTheGame()
{
    qDebug()<<"win!";
    win=true;
    mainTimer->stop();
    update();
}

void DoctorMario::makePills()
{
    fallPills.way=Up;
    fallPills.falling=false;
    fallPills.pill[0]=PillOrVirus(5*eachGridWidth,0,pill);
    fallPills.pill[1]=PillOrVirus(6*eachGridWidth,0,pill);
    if((!tryMoveTo(5*eachGridWidth,0))||(!tryMoveTo(6*eachGridWidth,0)))
        gameOver();
    else
        fallPills.falling=true;
}

void DoctorMario::gameOver()
{
    mainTimer->stop();
    gameEnd=true;
}

int DoctorMario::calTimer(int level)
{
    return 1;
}

void DoctorMario::startGame()
{
    mainTimer->start(1000);
    makePills();
    gameRunning=true;
    win=false;
    pause=false;
    update();
}

void DoctorMario::initGame()
{
    win=false;
    gameEnd=false;
    gameRunning=false;
    pause=false;
    data.clear();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    fallPills.falling=false;
    virusNum=0;
    for(int i=0;i<level*4;i++)
    {
        PillOrVirus *temp=new PillOrVirus(qrand()%(width/eachGridWidth)*eachGridWidth,
                                          ((qrand()%(height/2/eachGridWidth))+height/eachGridWidth/2)*eachGridWidth,
                                          virus);
        QList<PillOrVirus>::iterator iter=data.begin();
        bool ok=true;
        for(;iter!=data.end();iter++){
            if((temp->loc_x==(*iter).loc_x)&&(temp->loc_y==(*iter).loc_y)){
                ok=false;
                break;
            }
        }
        if(ok){
            data.append(*temp);
            virusNum++;
            qDebug()<<(*temp).loc_x<<","<<(*temp).loc_y<<"   col:"<<(*temp).color;
        }else{
            delete temp;
            i--;
            continue;
        }
    }

    virusChanged(virusNum,level);
    update();
}

void DoctorMario::mainTimerOut()
{
    pillFalling();
}

void DoctorMario::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
    painter.drawLine(0,0,0,height);
    painter.drawLine(0,0,width,0);
    painter.drawLine(width,height,width,0);
    painter.drawLine(width,height,0,height);
    if(gridShow){
        for(int i=0;i*eachGridWidth<=width;i++){
            painter.drawLine(QPoint(i*eachGridWidth,0),QPoint(i*eachGridWidth,height));
        }
        for(int i=0;i*eachGridWidth<=height;i++){
            painter.drawLine(QPoint(0,i*eachGridWidth),QPoint(width,i*eachGridWidth));
        }
    }

    if(!data.empty()){
        for(QList<PillOrVirus>::const_iterator iter=data.begin();iter!=data.end();iter++){
            if((*iter).kind==virus){
                switch((*iter).color){
                case yellow:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/yellow.png"));
                    break;
                case blue:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/blue.png"));
                    break;
                case red:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/red.png"));
                    break;
                }
            }else if((*iter).kind==pill){
                switch((*iter).color){
                case yellow:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/xyellow.png"));
                    break;
                case blue:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/xblue.png"));
                    break;
                case red:
                    painter.drawPixmap((*iter).loc_x,(*iter).loc_y,QPixmap(":/new/xred.png"));
                    break;
                }
            }

        }
        //painter.setBrush(QBrush(Qt::green,Qt::SolidLine));
    }
    if(fallPills.falling&&win==false){
        QPixmap pic;
        switch(fallPills.pill[0].color){
        case yellow:pic.load(":/new/xyellow.png");break;
        case blue:pic.load(":/new/xblue.png");break;
        case red:pic.load(":/new/xred.png");break;
        }
        painter.drawPixmap(fallPills.pill[0].loc_x,fallPills.pill[0].loc_y,pic);
        switch(fallPills.pill[1].color){
        case yellow:painter.drawPixmap(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y,QPixmap(":/new/xyellow.png"));break;
        case blue:painter.drawPixmap(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y,QPixmap(":/new/xblue.png"));break;
        case red:painter.drawPixmap(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y,QPixmap(":/new/xred.png"));break;
        }
    }
    QFont font("Times", 20, QFont::Bold);

    painter.setFont(font);
    if(gameEnd){
        painter.drawText(width/4,height/2,tr("GameOver!"));
    }
    if(pause){
        painter.drawText(width/4,height/2,tr("Pause!"));
    }
    if(win){
        painter.drawText(width/4,height/2,tr("congratulations!"));
    }
}

bool DoctorMario::tryMoveTo(int x, int y)
{
    if(x<0||x>=width)
        return false;
    if(y<0||y>=height)
        return false;
    QList<PillOrVirus>::iterator iter =data.begin();
    for(;iter!=data.end();iter++){
        if(((*iter).loc_x==x)&&((*iter).loc_y==y))
            return false;
    }
    return true;
}

void DoctorMario::pillFalling()
{
    if(fallPills.falling){
        if(tryMoveTo(fallPills.pill[0].loc_x,fallPills.pill[0].loc_y+eachGridWidth)&&
           (tryMoveTo(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y+eachGridWidth))){
              fallPills.pill[0].makeMoveTo(fallPills.pill[0].loc_x,fallPills.pill[0].loc_y+eachGridWidth);
              fallPills.pill[1].makeMoveTo(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y+eachGridWidth);
          }else{
              fallPills.falling=false;
              data.append(fallPills.pill[0]);
              data.append(fallPills.pill[1]);
              QList<PillOrVirus>::iterator iter_1=data.end();
              iter_1--;
              QList<PillOrVirus>::iterator iter_2=data.end();
              iter_2--;
              iter_2--;

              (*iter_1).linkTo=&(*iter_2);
              (*iter_2).linkTo=&(*iter_1);


              pillWorkOut(fallPills.pill[0].loc_x,fallPills.pill[0].loc_y,fallPills.pill[0].color);
              pillWorkOut(fallPills.pill[1].loc_x,fallPills.pill[1].loc_y,fallPills.pill[1].color);
              makePills();
          }
      }else{
          return ;
      }
    //qDebug()<<"falling";
    update();
}

void DoctorMario::pillMoveLeft()
{
    if(!fallPills.falling)
        return ;
    if(fallPills.falling){
        if(tryMoveTo(fallPills.pill[0].loc_x-eachGridWidth,fallPills.pill[0].loc_y))
            if(tryMoveTo(fallPills.pill[1].loc_x-eachGridWidth,fallPills.pill[1].loc_y)){
              fallPills.pill[0].makeMoveTo(fallPills.pill[0].loc_x-eachGridWidth,fallPills.pill[0].loc_y);
              fallPills.pill[1].makeMoveTo(fallPills.pill[1].loc_x-eachGridWidth,fallPills.pill[1].loc_y);
        }
    }
    //qDebug()<<"left";
    update();

}

void DoctorMario::pillMoveRight()
{
    if(!fallPills.falling)
        return ;
    if(fallPills.falling){
        if(tryMoveTo(fallPills.pill[0].loc_x+eachGridWidth,fallPills.pill[0].loc_y))
            if(tryMoveTo(fallPills.pill[1].loc_x+eachGridWidth,fallPills.pill[1].loc_y)){
              fallPills.pill[0].makeMoveTo(fallPills.pill[0].loc_x+eachGridWidth,fallPills.pill[0].loc_y);
              fallPills.pill[1].makeMoveTo(fallPills.pill[1].loc_x+eachGridWidth,fallPills.pill[1].loc_y);
        }
    }
    //qDebug()<<"left";
    update();
}

void DoctorMario::pillRotate()
{
    if(!fallPills.falling)
        return ;
    if(fallPills.way==Up){
        int loc,loc2;
        if(fallPills.pill[0].loc_x<fallPills.pill[1].loc_x){
            loc=0;
            loc2=1;
        }else{
            loc=1;
            loc2=0;
        }
        if(tryMoveTo(fallPills.pill[loc].loc_x,fallPills.pill[loc].loc_y+eachGridWidth)){
            fallPills.pill[loc2].makeMoveTo(fallPills.pill[loc].loc_x,fallPills.pill[loc].loc_y+eachGridWidth);
            fallPills.way=Right;
        }
    }else if(fallPills.way==Right){
        int loc,loc2;
        if(fallPills.pill[0].loc_y<fallPills.pill[1].loc_y){
            loc=0;
            loc2=1;
        }else{
            loc=1;
            loc2=0;
        }
        if(tryMoveTo(fallPills.pill[loc].loc_x-eachGridWidth,fallPills.pill[loc].loc_y)){
            fallPills.pill[loc2].makeMoveTo(fallPills.pill[loc].loc_x-eachGridWidth,fallPills.pill[loc].loc_y);
            fallPills.way=Down;
        }
    }else if(fallPills.way==Down){
        int loc,loc2;
        if(fallPills.pill[0].loc_x>fallPills.pill[1].loc_x){
            loc=0;
            loc2=1;
        }else{
            loc=1;
            loc2=0;
        }
        if(tryMoveTo(fallPills.pill[loc].loc_x,fallPills.pill[loc].loc_y-eachGridWidth)){
            fallPills.pill[loc2].makeMoveTo(fallPills.pill[loc].loc_x,fallPills.pill[loc].loc_y-eachGridWidth);
            fallPills.way=Left;
        }
    }else if(fallPills.way==Left){
        int loc,loc2;
        if(fallPills.pill[0].loc_y>fallPills.pill[1].loc_y){
            loc=0;
            loc2=1;
        }else{
            loc=1;
            loc2=0;
        }
        if(tryMoveTo(fallPills.pill[loc].loc_x+eachGridWidth,fallPills.pill[loc].loc_y)){
            fallPills.pill[loc2].makeMoveTo(fallPills.pill[loc].loc_x+eachGridWidth,fallPills.pill[loc].loc_y);
            fallPills.way=Up;
        }
    }
    update();
}

int DoctorMario::pillDown(PillOrVirus &pill)
{
    int count=0;

    if(!pill.linkTo){
        while(tryMoveTo(pill.loc_x,pill.loc_y+eachGridWidth)){
            pill.makeMoveTo(pill.loc_x,pill.loc_y+eachGridWidth);

            count++;
        }
        update();
    }else{

         if(pill.loc_y==(*pill.linkTo).loc_y){//pill and its link has the same loc_y,in a same line
            qDebug()<<"hello~";
            int temp_x,temp_y;
            bool link=false;
            while((tryMoveTo((*(pill.linkTo)).loc_x,(*(pill.linkTo)).loc_y+eachGridWidth))
                &&(tryMoveTo(pill.loc_x,pill.loc_y+eachGridWidth))){
                if(!link){
                    link=true;
                    temp_x=(*pill.linkTo).loc_x;
                    temp_y=(*pill.linkTo).loc_y;
                }
                pill.makeMoveTo(pill.loc_x,pill.loc_y+eachGridWidth);

                (*pill.linkTo).makeMoveTo((*pill.linkTo).loc_x,(*pill.linkTo).loc_y+eachGridWidth);
                count++;
            }
            if(link){
                qDebug()<<"pillsDown";
                pillsDown(temp_x,temp_y);
            }
        }else{
            int temp_x,temp_y;
            bool link=false;
            int bottom_y=qMax(pill.loc_y,(*pill.linkTo).loc_y);
            int top_y   =qMin(pill.loc_y,(*pill.linkTo).loc_y);
            while(tryMoveTo(pill.loc_x,bottom_y+eachGridWidth)){
                if(!link){
                    link=true;
                    temp_x=pill.loc_x;
                    temp_y=top_y;
                }
                pill.makeMoveTo(pill.loc_x,pill.loc_y+eachGridWidth);
                (*pill.linkTo).makeMoveTo((*pill.linkTo).loc_x,(*pill.linkTo).loc_y+eachGridWidth);
                count++;
            }
            if(link){
                pillsDown(temp_x,temp_y);
            }
        }

       // return -1;//indicate that this pill has a link.
    }
    return count;
}

void DoctorMario::pillsDown(int x, int y)//be careful that this point should point to this dismiss pill's below
{
    static int i=0;
    //qDebug()<<i++<<":"<<"x="<<x<<",y="<<y;
    QList<PillOrVirus>::iterator iter=data.begin();
    int downGrid=0;
    int num=0;
    for(int n=1;iter!=data.end();){
        //qDebug()<<"x:"<<(*iter).loc_x<<",y:"<<(*iter).loc_y;
        if((*iter).loc_x==x&&(y-(*iter).loc_y)==n*eachGridWidth){
            int down=pillDown(*iter);
            //qDebug()<<"down="<<down;
            if(!down){
                break;
            }else if(down!=-1){
                downGrid=down;
                n++;
                num++;
                iter=data.begin();
                continue;
            }else if(down==-1){//no way this could happen..
               // QList<PillOrVirus>::iterator temp=data.begin();
                //PillOrVirus link=
                //pillsDown()
                break ;
               // if(pillDown(*))
            }
        }
        iter++;
    }

    if(downGrid){
        qDebug()<<"downGrid="<<downGrid;
        qDebug()<<"num=     "<<num;
        for(int i=0;i<num;i++){
            QList<PillOrVirus>::iterator temp=data.begin();
            for(;temp!=data.end();temp++){
                if(((*temp).loc_x==x)&&((*temp).loc_y==(y+eachGridWidth*(downGrid-1)-i*eachGridWidth)))
                    break;
            }
            if(temp!=data.end()){
                pillWorkOut(x,y+eachGridWidth*(downGrid-1)-i*eachGridWidth,(*temp).color);//should the downGrid-1??
                qDebug()<<"pillWorkOut("<<x<<","<<y+eachGridWidth*(downGrid-1)-i*eachGridWidth<<","<<(*temp).color;
            }
        }
    }
}

int DoctorMario::gameLevel()const
{
    return level;
}

void DoctorMario::updateStatusChange()
{
    emit virusChanged(virusNum,level);
}

void DoctorMario::setGameLevel(int l)
{
    level=l;
    this->resetGame();
    updateStatusChange();

}

bool DoctorMario::running()const
{
    return gameRunning;
}

int DoctorMario::pillWorkOut(int x, int y, col pCol)
{
    if(data.empty())
        return 0;

    int count =0;
    QList<PillOrVirus>::iterator iter=data.begin();
    int up=0;
    int down=0;
    int i=0;



    for(int n=0;iter!=data.end();){//serchFor waydown
        if((*iter).color==pCol&&(*iter).loc_x==x){
            if(((*iter).loc_y-y)==(1+n)*eachGridWidth){
                n++;
                down=n;
                iter=data.begin();
                continue;
            }
        }
        iter++;
    }
    iter=data.begin();
    for(int n=0;iter!=data.end();){//serchFor wayup
        if((*iter).color==pCol&&(*iter).loc_x==x){
            if((y-(*iter).loc_y)==(1+n)*eachGridWidth){
                n++;
                up=n;
                iter=data.begin();
                continue;
            }
        }
        iter++;
    }
    int left=0;
    int right=0;
    iter=data.begin();
    for(int n=0;iter!=data.end();){//serchFor wayright
        if((*iter).color==pCol&&(*iter).loc_y==y){
            if(((*iter).loc_x-x)==(1+n)*eachGridWidth){
                n++;
                right=n;
                iter=data.begin();
                continue;
            }
        }
        iter++;
    }
    iter=data.begin();
    for(int n=0;iter!=data.end();){//serchFor wayleft
        if((*iter).color==pCol&&(*iter).loc_y==y){
            if((x-(*iter).loc_x)==(1+n)*eachGridWidth){
                n++;
                left=n;
                iter=data.begin();
                continue;
            }
        }
        iter++;
    }


    int x1=width;
    int y1=height;
    int x2=0;
    int y2=0;

    QList<PillOrVirus>deletes;
    QList<PillOrVirus>links;

    int kills=0;

    if((up+down)>=3){
        qDebug()<<"up+down=:"<<up<<"+"<<down;
        int y_top=y-up*eachGridWidth;
        int y_bottom=y+down*eachGridWidth;
        QList<PillOrVirus *>toDisLink;
        for(iter=data.begin();iter!=data.end();iter++){
            if((*iter).loc_x==x){
                if((*iter).loc_y<=y_bottom&&(*iter).loc_y>=y_top){
                    if((*iter).linkTo){
                        //(*iter).disableLink();
                        toDisLink.append((*iter).linkTo);
                        qDebug()<<(*iter).linkTo;
                        //pillDown(*((*iter).linkTo));

                    }
                    (*iter).pillKill=true;
                    if((*iter).kind==virus)
                        kills++;

                    //record the min x,y and max x,y for fillsDown();
                    if((*iter).loc_x<=x1){
                        x1=(*iter).loc_x;
                    }
                    if((*iter).loc_y<=y2){
                        y1=(*iter).loc_y;
                    }
                    if((*iter).loc_x>=x2){
                        x2=(*iter).loc_x;
                    }
                    if((*iter).loc_y>=y2){
                        y2=(*iter).loc_y;
                    }
                    //iter=data.erase(iter);
                    //iter--;
                }
            }
        }

        for(QList<PillOrVirus *>::iterator iter_p=toDisLink.begin();iter_p!=toDisLink.end();iter_p++){
            if((*(*iter_p)).pillKill){//error happen here...
                iter_p=toDisLink.erase(iter_p);
                iter_p--;
            }
        }


        for(iter=data.begin();iter!=data.end();iter++){
            if((*iter).pillKill==true){
                (*iter).disableLink();
                deletes.append(*iter);
                iter=data.erase(iter);
                iter--;

            }
        }
        qDebug()<<toDisLink.count()<<"!!";
        if(!toDisLink.empty()){
            QList<PillOrVirus *>::iterator iter_p=toDisLink.begin();
            for(;iter_p!=toDisLink.end();iter_p++){
                links.append(**iter_p);
            }
        }
    }

    if((left+right)>=3){
        qDebug()<<"lefthRIght";
        int x_left=x-left*eachGridWidth;
        int x_right=x+right*eachGridWidth;
        QList<PillOrVirus *>toDisLink;
        for(iter=data.begin();iter!=data.end();iter++){
            if((*iter).loc_y==y){
                if((*iter).loc_x<=x_right&&(*iter).loc_x>=x_left){
                    if((*iter).linkTo){
                        //(*iter).disableLink();
                        toDisLink.append((*iter).linkTo);
                        qDebug()<<(*iter).linkTo;
                        //pillDown(*((*iter).linkTo));

                    }
                    (*iter).pillKill=true;
                    if((*iter).kind==virus)
                        kills++;
                    //iter=data.erase(iter);
                   // iter--;
                }
            }
        }
        for(QList<PillOrVirus *>::iterator iter_p=toDisLink.begin();iter_p!=toDisLink.end();iter_p++){
            if((*(*iter_p)).pillKill){
                iter_p=toDisLink.erase(iter_p);
                iter_p--;
            }
        }

        for(iter=data.begin();iter!=data.end();iter++){
            if((*iter).pillKill==true){
                (*iter).disableLink();
                deletes.append(*iter);
                iter=data.erase(iter);
                iter--;

            }
        }
        if(!toDisLink.empty()){
            QList<PillOrVirus *>::iterator iter_p=toDisLink.begin();
            for(;iter_p!=toDisLink.end();iter_p++){
                links.append(**iter_p);

                //if(qBinaryFind(deletes.begin(),deletes.end(),(*(*(iter_p))))!=deletes.end())
                  //  deletes.append(*(*iter_p));
                //pillDown(*(*iter_p));
            }
        }
    }
    qDebug()<<"deletes.count"<<deletes.count();
    if(!deletes.empty()){
        QList<PillOrVirus>::iterator p=deletes.begin();
        for(;p!=deletes.end();p++){
            pillsDown((*p).loc_x,(*p).loc_y);

        }
    }
    if(!links.empty()){
        QList<PillOrVirus>::iterator p=links.begin();
        for(;p!=links.end();p++){
            pillsDown((*p).loc_x,(*p).loc_y+eachGridWidth);
        }
    }

    if(kills){
        virusNum-=kills;
        emit virusChanged(virusNum,level);
        if(virusNum==0)
            winTheGame();
    }

    if(left+right>=3)
        count+=left+right+1;
    if((up+down)>=3)
        count+=up+down;
    if(count>=4)
        update();


    return count;
}


int DoctorMario::twoPillsDown(PillOrVirus *pill)
{
return 0;
}

QSize DoctorMario::sizeHint() const
{
    return QSize(width,height);
}

PillOrVirus::PillOrVirus(int x, int y, k initKind, col initColor)
{
    pillKill=false;
    kind=initKind;
    color=initColor;
    loc_x=x;
    loc_y=y;
    linkTo=0;
}

PillOrVirus::PillOrVirus(int x, int y, col initColor)
{
    pillKill=false;
    kind=static_cast<k>(qrand()%2);
    color=initColor;
    loc_x=x;
    loc_y=y;
    linkTo=0;
}

PillOrVirus::PillOrVirus(int x,int y)
{
    pillKill=false;
    kind=static_cast<k>(qrand()%2);
    color=static_cast<col>(qrand()%3);
    loc_x=x;
    loc_y=y;
    linkTo=0;
}

PillOrVirus::PillOrVirus(int x,int y,k initKind)
{
    pillKill=false;
    kind=initKind;
    color=static_cast<col>(qrand()%3);
    loc_x=x;
    loc_y=y;
    linkTo=0;
}

void PillOrVirus::makeMoveTo(int x, int y)
{
    //qDebug()<<"move";
    loc_x=x;
    loc_y=y;

    //linkTo=0;
}

void PillOrVirus::disableLink()
{
    if(kind==pill){
        if(linkTo)
            linkTo->linkTo=0;
    }
}


void DoctorMario::keyPressEvent(QKeyEvent *k ){
    qDebug()<<"a key event happened!";
    switch(k->key()){
        case Qt::Key_Up:
    pillRotate();
    break;
        case Qt::Key_Down:
    pillFalling();
    break;
        case Qt::Key_Left:
    pillMoveLeft();
    break;
        case Qt::Key_Right:
    pillMoveRight();
    break;
    default:
        break;
    }
    QWidget::keyPressEvent(k);
}
