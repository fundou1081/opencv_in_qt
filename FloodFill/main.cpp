#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat g_image,g_dimage,g_mimage;

static void onMouse(int event, int x,int y, int, void*){

    if(event != EVENT_LBUTTONDOWN)  return;

    Point seed = Point(x,y);
    Rect ccomp;
    int area;
    int flag = 8|FLOODFILL_FIXED_RANGE|FLOODFILL_MASK_ONLY|(255<<8);

    area = floodFill(g_dimage,g_mimage,seed,Scalar(255,0,0),&ccomp,Scalar(5,5,5),Scalar(5,5,5),flag);
    //area = floodFill(g_dimage,seed,Scalar(255,0,0),&ccomp,Scalar(5,5,5),Scalar(5,5,5),flag);
    cout << seed<<area<<endl;
    imshow("after",g_dimage);
    imshow("mask",g_mimage);
}


int main(int argc, char *argv[]){

    g_image = imread("D:\\ttest.jpg",1);
    if(!g_image.data){
        cout<<"error"<<endl;return -1;}
    g_image.copyTo(g_dimage);
    g_mimage.create(g_image.rows+2,g_image.cols+2,CV_8UC1);
    g_mimage=Scalar::all(0);
    imshow("te",g_mimage);
    //threshold(g_mimage,g_mimage,1,64,THRESH_BINARY);
    imshow("te2",g_mimage);

    namedWindow("ori",WINDOW_AUTOSIZE);
    setMouseCallback("ori",onMouse,0);



    while(1){
        imshow("ori",g_image);
        waitKey(0);
    }

    return 0;
}
