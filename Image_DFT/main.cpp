#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void on_Proc(int , void *);


Mat g_image,g_dimage;

int g_nx1;
int g_nx2;


int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg",0);

    if(!g_image.data){
        cout<<"error"<<endl;return -1;}

    g_dimage=Mat::zeros(g_image.size(),g_image.type());

    //namedWindow("origin",1);
    //namedWindow("after",1);

    g_nx1=0;

    on_Proc(g_nx1,0);

    while(char(waitKey(1))!='q'){}

    return 0;
}
static void on_Proc(int,void *){

    //int m = getOptimalDFTSize(g_image.rows);
    //int n = getOptimalDFTSize(g_image.cols);

    int m=g_image.rows*2;
    int n=g_image.cols*2;

    Mat padded;
    copyMakeBorder(g_image,padded,0,m-g_image.rows,0,n-g_image.cols,BORDER_CONSTANT,Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};
    Mat complexI;
    merge(planes,2,complexI);
    dft(complexI,complexI);

    //
    Mat idft;

    dft(complexI,idft,DFT_REAL_OUTPUT);
    Mat iplanes[2];
    split(idft,iplanes);
    normalize(iplanes[0],iplanes[0],0,1,CV_MINMAX);
    namedWindow("idft",WINDOW_KEEPRATIO);
    imshow("idft",iplanes[0]);
    //


    split(complexI,planes);
    magnitude(planes[0],planes[1],planes[0]);
    Mat magnitudeImage = planes[0];

    magnitudeImage +=Scalar::all(1);
    log(magnitudeImage,magnitudeImage);

    magnitudeImage=magnitudeImage(Rect(0,0,magnitudeImage.cols & -2,magnitudeImage.rows & -2));

    int cx = magnitudeImage.cols/2;
    int cy = magnitudeImage.rows/2;

    Mat q0(magnitudeImage,Rect(0,0,cx,cy));
    Mat q1(magnitudeImage,Rect(cx,0,cx,cy));
    Mat q2(magnitudeImage,Rect(0,cy,cx,cy));
    Mat q3(magnitudeImage,Rect(cx,cy,cx,cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magnitudeImage,magnitudeImage,0,1,NORM_MINMAX);

    namedWindow("dft",WINDOW_KEEPRATIO);
    imshow("dft",magnitudeImage);
}
