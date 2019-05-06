#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat g_image,g_dimage,g_gimage;
int rho,ths,srn,stn;
double tha;
vector<Vec2f> lines;
vector<Vec4i> linesp;
vector<Vec3f> circles;

void on_HoughL(int, void*){
    HoughLines(g_dimage,lines,rho,tha,ths,srn,stn);
    for(int i=0;i<lines.size();i++){

        float r=lines[i][0],t=lines[i][1];
        Point p1,p2;
        double a= cos(t),b=sin(t);
        double x0=a*r,y0=b*r;
        p1.x=cvRound(x0+1000*(-b));
        p1.y=cvRound(y0+1000*(a));
        p2.x=cvRound(x0-1000*(-b));
        p2.y=cvRound(y0-1000*(a));
        line(g_dimage,p1,p2,Scalar(255,255,0),1,LINE_AA);
        cout<<i<<endl;
        //if(i==2) break;
    }
    imshow("after Hough",g_dimage);
}

void on_HoughP(int, void*){
    HoughLinesP(g_dimage,linesp,rho,tha,ths,80,50);
    for(int i=0;i<linesp.size();i++){
        Vec4i l = linesp[i];
        line(g_dimage,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,255,0),1,LINE_AA);
    }
    imshow("after Hough",g_dimage);
}

void on_HoughC(int, void*){
    HoughCircles(g_dimage,circles,HOUGH_GRADIENT,1,10,200,100,0,0);
    for(int i=0;i<circles.size();i++){
        Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
        int r = cvRound(circles[i][2]);
        circle(g_dimage,center,3,Scalar(255,0,0),-1,8,0);
        circle(g_dimage,center,r,Scalar(100,100,200),3,8,0);
    }
    imshow("after Hough",g_dimage);
}



int main(int argc, char *argv[]){

    g_image = imread("D:\\ccc.jpg",1);
    if(!g_image.data){
        cout<<"error"<<endl;return -1;}
    namedWindow("origin",WINDOW_KEEPRATIO);
    imshow("origin",g_image);

    cvtColor(g_image,g_dimage,CV_BGR2GRAY);

    Canny(g_dimage,g_dimage,50,200,3);

    rho=1;
    tha=CV_PI/180;
    ths=500;
    srn=0;
    stn=0;

    namedWindow("after Hough",WINDOW_KEEPRATIO);
    createTrackbar("ths","after Hough",&ths,900,on_HoughC,0);
    on_HoughC(0,0);


    waitKey(0);
    return 0;
}
