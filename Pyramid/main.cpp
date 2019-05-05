#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat g_image,g_dimage,g_mimage,g_pimage;

int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg",1);
    if(!g_image.data){
        cout<<"error"<<endl;return -1;}

    g_dimage=Mat::zeros(512,512,g_image.type());
    resize(g_image,g_dimage,Size(),0.5,0.5,INTER_LANCZOS4);
    resize(g_dimage,g_mimage,Size(),2,2,INTER_NEAREST);

    pyrUp(g_dimage,g_pimage,Size(g_dimage.cols *2,g_dimage.rows*2));

    imshow("A",g_image);
    imshow("d",g_dimage);
    imshow("m",g_mimage);
    imshow("p",g_pimage);
    Mat re = g_mimage-g_image;
    threshold(re,re,1,255,THRESH_BINARY);
    imshow("re",re);

    Mat ree = g_pimage-g_image;
    threshold(ree,ree,1,255,THRESH_BINARY);
    imshow("ree",ree);


    waitKey(0);

    return 0;
}
