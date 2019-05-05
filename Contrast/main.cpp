#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void on_ContrastAndBright(int , void *);

int g_nContrastValue;
int g_nBrightValue;
Mat g_image,g_dimage;

int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg");

    if(!g_image.data){
        cout<<"error"<<endl;return -1;
    }

    g_dimage=Mat::zeros(g_image.size(),g_image.type());
    g_nContrastValue=80;
    g_nBrightValue=80;

    namedWindow("after",1);

    createTrackbar("Contrast","after",&g_nContrastValue,300,on_ContrastAndBright);
    createTrackbar("Bright","after",&g_nBrightValue,200,on_ContrastAndBright);

    on_ContrastAndBright(g_nContrastValue,0);
    on_ContrastAndBright(g_nBrightValue,0);

    while(char(waitKey(1))!='q'){}

    return 0;
}
static void on_ContrastAndBright(int,void *){

    namedWindow("ori",1);
    for(int y=0;y<g_image.rows;y++){
        for(int x=0;x<g_image.cols;x++){
            for(int c=0;c<3;c++){
                g_dimage.at<Vec3b>(y,x)[c]=saturate_cast<uchar>((g_nContrastValue*0.01)*g_image.at<Vec3b>(y,x)[c]+g_nBrightValue);
            }
        }
    }
    imshow("ori",g_image);
    imshow("after",g_dimage);
}
