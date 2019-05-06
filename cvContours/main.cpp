#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat g_image,g_dimage,g_gimage;

static void on_Canny(int , void *);
int g_th1,g_th2,g_size;

int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg",1);
    if(!g_image.data){
        cout<<"error"<<endl;return -1;}

    cvtColor(g_image,g_image,COLOR_BGR2GRAY);
    equalizeHist(g_image,g_image);

    namedWindow("origin",WINDOW_KEEPRATIO);
    imshow("origin",g_image);

    namedWindow("canny",WINDOW_KEEPRATIO);
    g_th1 = 32;
    g_th2 = 100;
    g_size= 1;
    g_dimage.create(g_image.size(),g_image.type());
    createTrackbar("gth1","canny",&g_th1,200,on_Canny,0);
    createTrackbar("gth2","canny",&g_th2,200,on_Canny,0);
    createTrackbar("gsize","canny",&g_size,3,on_Canny,0);
    on_Canny(g_size,0);



    waitKey(0);
    return 0;
}

void on_Canny(int ,void*){
    int size = g_size*2+1;
    if(size<=3) size=3;
    //Canny(g_image,g_dimage,g_th1,g_th2,size);
    imshow("canny",g_dimage);
    g_dimage=g_image > g_th1;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(g_dimage,contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_SIMPLE);
    int index=0;
    for(;index>=0;index=hierarchy[index][0]){
        Scalar color(rand()&255,rand()&255,rand()&255);
        drawContours(g_dimage,contours,index,color,FILLED,8,hierarchy);

    }
    imshow("contours",g_dimage);
}
