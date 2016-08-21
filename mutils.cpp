#include "mutils.h"
#include <QDebug>

mUtils::mUtils(QObject *parent) : QThread(parent)
{
    mpoints = new Point[100000];
    vc = new VideoCapture(1);

   old_centers = (Point*)malloc(sizeof(Point)*(3+1));

}

mUtils::~mUtils(void)
{
    if(vc)
        vc->release();
}


void mUtils::tocreatemodel(void){
    createModel(*vc);

}

void mUtils::startToRun(void){
    this->start();
}
void mUtils::getSrcImgFromVideo(Mat &msrcimg){
    *vc>>msrcimg;
    //msrcimg = imread("///////filename//");

}

void mUtils::run(){

try{

        static	Point* resultPoints = new Point[5];
        Point old_leftHandPoint,old_rightHandPoint;
        //vc = new VideoCapture("d:\\WIN_20160819_14_39_28_Pro.mp4");
        double fps;
        double  t;
        while(true){
            t = getTickCount();

            //*vc>>srcImg;
            getSrcImgFromVideo(srcImg);
            //loadsrcImg(srcImg);

            Mat gray;
            if (srcImg.channels() == 3) {
                cvtColor(srcImg, gray, CV_BGR2GRAY);
            }
            else if (srcImg.channels() == 4) {
                cvtColor(srcImg, gray, CV_BGRA2GRAY);
            }
            else {
                // Access the input image directly, since it is already grayscale.
                gray = srcImg;
            }

            Mat toshowImage;

            resize(gray, toshowImage, Size(320,240));

            //qDebug()<<"start to run k means";
            run_k_means(resultPoints,3);
            //qDebug()<<"k-means done!";
            ///////////KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKMMMMMMEEEEEEAAAAAAAAANNNNNNNNNSSS
            drawKMeansResult(toshowImage,resultPoints,3);
            imshow("finalResult",toshowImage);

            Mat finalresult;

            Point cur_leftHandPoint,cur_rightHandPoint;
            resize(srcImg,finalresult,Size(toshowImage.cols,toshowImage.rows));
            int ignoreangle = 30;
            Rect picrect(Point(0,0),Point(finalresult.cols,finalresult.rows));

            {

                line(finalresult,Point(finalresult.cols/2,finalresult.rows*0.4),
                    Point(finalresult.cols/2,finalresult.rows*0.6),Scalar(100,100,0),3);

                line(finalresult,Point(finalresult.cols/2,finalresult.rows*0.4),
                    Point(finalresult.cols/2-finalresult.rows*0.4*tan(ignoreangle*PI/180),0),
                     Scalar(100,100,0),3);
                line(finalresult,Point(finalresult.cols/2,finalresult.rows*0.4),
                    Point(finalresult.cols/2+finalresult.rows*0.4*tan(ignoreangle*PI/180),0),
                     Scalar(100,100,0),3);

                line(finalresult,Point(finalresult.cols/2,finalresult.rows*0.6),
                    Point(finalresult.cols/2-finalresult.rows*0.4*tan(ignoreangle*PI/180),
                          finalresult.rows),Scalar(100,100,0),3);
                line(finalresult,Point(finalresult.cols/2,finalresult.rows*0.6),
                    Point(finalresult.cols/2+finalresult.rows*0.4*tan(ignoreangle*PI/180),
                          finalresult.rows),Scalar(100,100,0),3);
            }


                for(int q = 0;q<3;q++){
                    if(isHandPos(picrect,resultPoints[q],ignoreangle)){
                        circle(finalresult,resultPoints[q],30,Scalar(255,100,200),3);
                        if(resultPoints[q].x > finalresult.cols/2)
                            cur_rightHandPoint = resultPoints[q];
                        if(resultPoints[q].x < finalresult.cols/2)
                            cur_leftHandPoint = resultPoints[q];
                    }
                }


        double move_threshold = 1.0;
        int dir = 0;


        t = (getTickCount() - t) / getTickFrequency();
        fps = 1/t;

        qDebug()<<"fps:"<<1/t;
        Rect rect(finalresult.cols*0.15,finalresult.rows*0.7,80,80);


        dir = judgedir(&old_leftHandPoint,&old_rightHandPoint,&cur_leftHandPoint,&cur_rightHandPoint,fps,move_threshold);
//        dir = 0;
//        sendAChar(0x27);



        drawControl(finalresult,rect,dir);
        imshow("show hand position:",finalresult);
        if(dir != 0)
            waitKey(100);
        waitKey(10);
        }
}catch(exception e)
    {
       qDebug()<<"errorororor::"<<e.what();
    }
}

int mUtils::judgedir(Point *oldleft,Point *oldright,Point *curleft,Point *curright,double fps,double move_threshold){
    /*
//    if((curleft->x - oldleft->x)/fps > move_threshold){////////////////////向左边;
//        sendAChar('A');
//        *oldleft = *curleft;
//       return  4;
//    }else
//    if((curright->x - oldright->x)/fps > move_threshold){//////////////向右边;
//        sendAChar('D');
//        *oldright = *curright;
//       return   2;
//    }else

//    if((oldleft->y - curleft->y)/fps > move_threshold+2){/////////////////上;
//        sendAChar('W');
//        *oldleft = *curleft;
//        return  1;
//    }else
//    if((oldright->y - curright->y)/fps > move_threshold+2){////////////////上;
//        sendAChar('W');
//        *oldright = *curright;
//        return 1;
//    }else

//    if((curleft->y - oldleft->y)/fps > move_threshold+2){/////////////////下;
//        sendAChar('S');
//        *oldleft = *curleft;
//        return 3;
//    }else
//    if((curright->y - oldright->y)/fps > move_threshold+2){////////////////下;
//        sendAChar('S');
//        *oldright = *curright;
//        return 3;
//    }
*/

    int dir = 0;
    if(curright->x > 0.8*320 && oldright->x < 0.8*320){
        sendAChar(0x25);
        dir = 4;
    }else if(curleft->x < 0.2*320 && oldleft->x >0.2*320){
        sendAChar(0x27);
        dir = 2;
    }else

    if(curright->y > 0.25*240 && oldright->y < 0.25*240){
        sendAChar(0x26);
        dir = 1;
    }else if(curleft->y < 0.25*240 && oldleft->y >0.25*240){
        sendAChar(0x26);
        dir = 1;
    }else if(curright->y > 0.75*240 && oldright->y < 0.75*240){
        sendAChar(0x28);
        dir = 3;
    }else if(curleft->y < 0.75*240 && oldleft->y > 0.75*240){
        sendAChar(0x28);
        dir = 3;
    }

    *oldleft = *curleft;
    *oldright = *curright;

    return dir;

}

void mUtils::drawControl(Mat canvas,Rect rect,int dir){
    Point center;
    center.x = rect.x + rect.width/2;
    center.y = rect.y + rect.height/2;
    int lengh = rect.width/2;

    circle(canvas,center,lengh,Scalar(0,200,50),5);
    line(canvas,Point(center.x - lengh*sin(45*PI/180),center.y - lengh*sin(45*PI/180)),
        Point(center.x + lengh*sin(45*PI/180),center.y + lengh*sin(45*PI/180)),Scalar(0,0,255),3);
    line(canvas,Point(center.x + lengh*sin(45*PI/180),center.y - lengh*sin(45*PI/180)),
        Point(center.x - lengh*sin(45*PI/180),center.y + lengh*sin(45*PI/180)),Scalar(0,0,255),3);

    line(canvas,Point(0.2*320,0),Point(0.2*320,240),Scalar(123,234,2),2);
    line(canvas,Point(0.8*320,0),Point(0.8*320,240),Scalar(123,234,2),2);
    line(canvas,Point(0,0.25*240),Point(320,0.25*240),Scalar(123,234,2),2);
    line(canvas,Point(0,0.75*240),Point(320,0.75*240),Scalar(123,234,2),2);
    int startangle = 0;
    int endangle = startangle;
    switch(dir){
        case 1:
            startangle = 225;
            break;
        case 2:
            startangle = 315;
            break;
        case 3:
            startangle = 45;
            break;
        case 4:
            startangle = 135;
            break;
        default:
            startangle = 0;
            break;
    }
////////////////////////startangle、endangle参数是角度制，，45°，90°等
    if(dir != 0){
        endangle = startangle+90;
        ellipse(canvas,center,Size(lengh,lengh),0,startangle,endangle,Scalar(122,2,222),-1,4);
    }


}

bool mUtils::isHandPos(Rect picrect,Point point,int ignoreangle){

    float a,b;
    int angle;


        if(point.y < picrect.height/2){
            a = abs(point.x -picrect.width/2);
            b = abs(picrect.height*0.4 - point.y);
        }else{
            a = abs(point.x - picrect.width/2);
            b = abs(point.y - picrect.height*0.6);
        }

        angle = (atan(a/b))*180/PI;
        if(angle > ignoreangle)
            return true;
        else return false;
}

void mUtils::sendAChar(char ch){
    keybd_event(16,0,0,0);
    keybd_event(ch,0,0,0);
    keybd_event(ch,0,KEYEVENTF_KEYUP,0);
    keybd_event(16,0,KEYEVENTF_KEYUP,0);

}


void mUtils::k_means(Point *points,int points_num,Point* resultPoint,int k){
    //初始化多个聚类中心;
    //4个聚类中心

    static Point
        *centerPoints;
    centerPoints = (Point*)malloc(sizeof(Point)*(k));

    //初始化聚类中心
    for(int q = 0;q<k;q++){
        centerPoints[q] = old_centers[q];
    }



    float dis[5];
    do{

       // qDebug()<<"do\n";
        //每个新聚类中心的所含的点数
        int center_count[5];
        for(int q = 0;q<k;q++)
            center_count[q] = 1;

        //每个新聚类中心的X,Y和
        float sum[5][2];
        for(int z = 0;z<k;z++)
            for(int a = 0;a<2;a++)
                sum[z][a] = 0;

        //遍历数据集中的每一个点，，
        //计算新聚类中心
        for(int q = 0;q<points_num;q++){

            //计算点q距离每个聚类中心的距离
            for(int x = 0;x < k;x++){
                dis[x] = ((points[q].x - centerPoints[x].x)*(points[q].x - centerPoints[x].x)
                    + (points[q].y - centerPoints[x].y)*(points[q].y - centerPoints[x].y));
            }
            /////////求出点q输入哪一个中心
            int min = dis[0];
            int min_num = 0;
            for(int mi = 0;mi<k;mi++){
                if(min>dis[mi]){
                    min_num = mi;
                    min = dis[mi];
                }
            }
            //为下一步移动聚类中心做准备
            //统计属于此聚类中心的x,y坐标，，，
            center_count[min_num]++;
            sum[min_num][0] += points[q].x;
            sum[min_num][1] += points[q].y;

        }
        //移动新距离中心
        for(int x = 0;x<k;x++){
            //将老中心设置为当前中心，
            old_centers[x] = centerPoints[x];

            //移动聚类中心至新的中心
            centerPoints[x].x = sum[x][0]/center_count[x];
            centerPoints[x].y = sum[x][1]/center_count[x];
            //判断老聚类中心距离新中心的距离，，，为是否进行下次运算做准备

            dis[x] = diss(old_centers[x],centerPoints[x]);
        }
    }while(!isEnoughClose(dis,30,3));

    //返回统计到的聚类中心至resultPoints数组中
    for(int x = 0;x<k;x++)
        resultPoint[x] = centerPoints[x];
}

bool mUtils::isEnoughClose(float *arr,int threshold,int k){
    for(int q = 0;q<k;q++)
        if(arr[q] > threshold)
            return false;
    return true;
}

void mUtils::countPoint(Mat mat,int &n,int thresh){
    n = 0;
    int rows = mat.rows;
    int cols = mat.cols;
    for(int q = 0;q<rows;q++){
        uchar* ptr = mat.ptr<uchar>(q);
        for(int p = 0;p<cols;p++){
            if(ptr[p]>thresh){
                mpoints[n] = Point(p,q);
                n++;
            }
        }
    }
}

int mUtils::diss(Point p1,Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
    ////原来写错了，，，写成了x^2的形式
}

void mUtils::run_k_means(Point *resultPoints,int k){

    cvtColor(model,hsv_pic,COLOR_RGB2HSV);
    hue_image.create(model.size(),model.depth());
    int ch[] = {0,0};
    mixChannels(&hsv_pic,1,&hue_image,1,ch,1);
    int histSize = 5;
    float hue_range[] = {0,180};
    const float * ranges = {hue_range};
    calcHist(&hue_image,1,0,Mat(),hist,1,&histSize,&ranges,true,false);
    normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());
    resize(srcImg,cur,Size(320,240));
    cvtColor(cur,cur_hsv,COLOR_RGB2HSV);
    cur_hue.create(cur_hsv.size(),cur_hsv.depth());
    mixChannels(&cur_hsv,1,&cur_hue,1,ch,1);
    calcBackProject(&cur_hue,1,0,hist,backproj,&ranges,1,true);

    threResult = backproj>250;
    erode(threResult,threResult,getStructuringElement(MORPH_RECT,Size(3,3)));
    imshow("ecode:",threResult);

    medianBlur(threResult,threResult,7);
    resize(threResult,threResult,Size(32,24));
    resize(threResult,threResult,Size(320,240));
    threResult = backproj>250;
    medianBlur(threResult,threResult,11);
    imshow("medianBlur:",threResult);
    int n  = 0;
    countPoint(threResult,n,250);

    k_means(mpoints,n,resultPoints,k);

}

void mUtils::loadsrcImg(Mat srcImg){
    this->srcImg = srcImg;
}

void mUtils::createModel(VideoCapture vc){

    Mat temp;
    int keycode;
    time_t mtime;
    time_t old_time;
    time(&old_time);
    int backcount = 10;
    char str[4];
    Rect captureRect(Point(190,110),Point(290,210));
    while(true){
        vc>>temp;
        resize(temp,temp,Size(480,320));
        rectangle(temp,captureRect,Scalar(100,200,45),3);
        putText(temp,"please put you hand below",Point(100,80),0,0.8,Scalar(0,0,100),1);
        sprintf(str,"%d",backcount);
        putText(temp,str,Point(50,40),0,1.2,Scalar(100,100,0),5);

        time(&mtime);
        if(mtime>old_time){
            backcount--;
            old_time = mtime;
            if(backcount<0)
                break;
        }
        imshow("show you hand,please!",temp);
        keycode = waitKey(10);
        if(keycode == ' ')
            break;

    }
    model = temp(captureRect);
    //resize(model,model,Size(480,320));
    imshow("model:",model);
    waitKey(1000);
    destroyAllWindows();

/////////////////////////////////////////
//model = imread("d:\\pic1.jpg");

}

void mUtils::drawKMeansResult(Mat toshowImage,Point *resultPoints,int k){

    for(int q = 0 ;q <k;q++){
        circle(toshowImage,resultPoints[q],20,Scalar(255,255,255),5);

        if(q < k - 1)
            line(toshowImage,resultPoints[q],resultPoints[q+1],Scalar(0,0,255),1);
        else
            line(toshowImage,resultPoints[q],resultPoints[0],Scalar(0,0,255),1);
    }

}

