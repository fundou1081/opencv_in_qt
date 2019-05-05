#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void on_Proc(int , void *);
static void on_ProcBlur(int , void *);
static void on_ProcGBlur(int ,void *);
static void on_ProcMedian(int ,void *);
static void on_ProcBilateral(int, void*);
static void on_ProcDilate(int, void*);
static void on_ProcErode(int, void*);

Mat g_image,g_dimage;

int g_para1;

int g_blur;

int g_gblur;
int g_gblurX;
int g_gblurY;
char gblurStr[20];
char gblurXStr[20];
char gblurYStr[20];

int g_median;

int g_d;
int g_color;
int g_space;

int g_dilate;
int g_erode;

int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg",1);

    if(!g_image.data){
        cout<<"error"<<endl;return -1;}
    g_dimage=Mat::zeros(g_image.size(),g_image.type());

    namedWindow("origin",WINDOW_KEEPRATIO);
    imshow("origin",g_image);

/*box filter
    g_para1=1;
    namedWindow("after",WINDOW_KEEPRATIO);
    createTrackbar("para1","after",&g_para1,500,on_Proc);
    on_Proc(g_para1,0);

*/

/*
    //blur
    g_blur=1;
    namedWindow("after blur",WINDOW_KEEPRATIO);
    createTrackbar("blur","after blur",&g_blur,500,on_ProcBlur);
    on_ProcBlur(g_blur,0);
*/
/*
    //gblur
    g_gblur=1;
    g_gblurX=0;
    g_gblurY=0;
    sprintf(gblurStr,"gblur");
    sprintf(gblurXStr,"gblurX");
    sprintf(gblurYStr,"gblurY");
    namedWindow("Gblur",WINDOW_KEEPRATIO);
    createTrackbar(gblurStr,"Gblur",&g_gblur,50,on_ProcGBlur);
    on_ProcGBlur(g_gblur,0);
    createTrackbar(gblurXStr,"Gblur",&g_gblurX,50,on_ProcGBlur);
    on_ProcGBlur(g_gblurX,0);
    createTrackbar(gblurYStr,"Gblur",&g_gblurY,50,on_ProcGBlur);
    on_ProcGBlur(g_gblurY,0);
*/

    /*
    g_median=1;
    namedWindow("Median",WINDOW_KEEPRATIO);
    createTrackbar("median","Median",&g_median,500,on_ProcMedian);
    on_ProcMedian(g_median,0);

*/
    g_d=60;
    g_color=25;
    g_space=25;
    namedWindow("bilateral",WINDOW_KEEPRATIO);
    createTrackbar("g_d","bilateral",&g_d,100,on_ProcBilateral);
    on_ProcBilateral(g_d,0);
    createTrackbar("g_color","bilateral",&g_color,500,on_ProcBilateral);
    on_ProcBilateral(g_color,0);
    createTrackbar("g_space","bilateral",&g_space,100,on_ProcBilateral);
    on_ProcBilateral(g_space,0);

    g_dilate=3;
    namedWindow("dilate",WINDOW_KEEPRATIO);
    createTrackbar("g_dilate","dilate",&g_dilate,300,on_ProcDilate);
    on_ProcDilate(g_dilate,0);

    Mat ele = (Mat_<int>(3,3)<<1,1,1,1,1,1,1,1,1);
    Mat element = getStructuringElement(MORPH_RECT,Size(3,3));
    cout<< element<<ele;

    g_erode=3;
    namedWindow("erode",WINDOW_KEEPRATIO);
    createTrackbar("g_erode","erode",&g_erode,300,on_ProcErode);
    on_ProcErode(g_erode,0);

    while(char(waitKey(1))!='q'){}
    return 0;
}

static void on_Proc(int,void *){
    if(g_para1>0)
        boxFilter(g_image,g_dimage,-1,Size(g_para1,g_para1));
    imshow("after",g_dimage);
}

static void on_ProcBlur(int,void *){
    if(g_blur>0)
        blur(g_image,g_dimage,Size(g_blur,g_blur));
    imshow("after blur",g_dimage);
}
static void on_ProcGBlur(int , void*){

    int s=g_gblur*2+1;
    if(g_gblur>0)
        GaussianBlur(g_image,g_dimage,Size(s,s),(double)g_gblurX,(double)g_gblurY);
    imshow("Gblur",g_dimage);
}
static void on_ProcMedian(int ,void *){
    int s=g_median*2+1;
    if(g_median>0)
        medianBlur(g_image,g_dimage,s);
    imshow("Median",g_dimage);
}
static void on_ProcBilateral(int ,void *){

    int s  = g_d-50;
    bilateralFilter(g_image,g_dimage,s,g_color,g_space);
    imshow("bilateral",g_dimage);
}

static void on_ProcDilate(int ,void *){
    if(g_dilate>0){
        Mat e = getStructuringElement(MORPH_ELLIPSE,Size(g_dilate,g_dilate));
        dilate(g_image,g_dimage,e);

        //Close
        Mat img;
        erode(g_dimage,img,e);
        imshow("Close",img);

        imshow("dilate",g_dimage);

        //black hat
        Mat blackhat = img - g_image;
        imshow("blackhat",blackhat);

        //Gradient
        Mat img1;
        erode(g_image,img1,e);
        Mat imgr = img1 - g_dimage;
        imshow("Gradient2",imgr);
    }
}

static void on_ProcErode(int ,void *){
    if(g_erode>0){
        Mat e = getStructuringElement(MORPH_ELLIPSE,Size(g_erode,g_erode));
        erode(g_image,g_dimage,e);
        //Open
        Mat img;
        dilate(g_dimage,img,e);
        imshow("Open",img);

        imshow("erode",g_dimage);

        //Top hat
        Mat tophat=g_image-img;
        imshow("tophat",tophat);

        //Gradient
        Mat img1;
        dilate(g_image,img1,e);
        Mat imgr = img1 - g_dimage;
        imshow("Gradient",imgr);
    }

}
