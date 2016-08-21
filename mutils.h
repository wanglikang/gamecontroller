#ifndef MUTILS_H
#define MUTILS_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;
#define PI 3.141592653
class mUtils : public QThread
{
    Q_OBJECT

public :
    VideoCapture *vc;
public:
    explicit mUtils(QObject *parent = 0);
    ~mUtils(void);
public:


signals:
    void toshowPic(Mat);


public slots:
    void tocreatemodel(void);
    void startToRun(void);
protected:
    void run();

public:
    int scaledWidth;
    Point *mpoints;
    Mat cur;
    Mat hsv_pic;
    Mat dst;
    Mat hue_image;
    Mat cur_hue;
    Mat cur_hsv;
    MatND backproj;
    Mat threResult;
    MatND hist;
    Mat model;
    Mat srcImg;

    Point *old_centers;


public:
    void k_means(Point *points,int points_num,Point* resultPoint,int k);
    bool isEnoughClose(float *arr,int threshold,int k);
    void countPoint(Mat mat,int &n,int thresh);
    int diss(Point p1,Point p2);
    void loadMat(Mat);
    bool isHandPos(Rect picrect,Point point,int ignoreangle);
    void sendAChar(char ch);
    void drawControl(Mat canvas,Rect rect,int dir);
    void createModel(VideoCapture vc);
    void loadsrcImg(Mat srcImage);
    void run_k_means(Point *resultPoints,int k);
    void drawKMeansResult(Mat toshowImage,Point *resultPoints,int k);
    int judgedir(Point *oldleft,Point *oldright,Point *curleft,Point *curright,double fps,double move_threshold);
    void getSrcImgFromVideo(Mat &msrcimg);


};

#endif // MUTILS_H
