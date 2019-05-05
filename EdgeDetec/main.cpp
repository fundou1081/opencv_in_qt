#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void on_Canny(int , void *);
static void on_Sobel(int , void *);


Mat g_image,g_dimage,g_gimage;
int g_th1,g_th2,g_size;

Mat g_simage;
Mat g_limage;
Mat g_schimage;


int main(int argc, char *argv[]){

    g_image = imread("D:\\ttest.jpg",1);

    if(!g_image.data){
        cout<<"error"<<endl;return -1;}

    namedWindow("origin",WINDOW_KEEPRATIO);
    imshow("origin",g_image);

    cvtColor(g_image,g_gimage,COLOR_BGR2GRAY);
    blur(g_gimage,g_gimage,Size(3,3));

    namedWindow("canny",WINDOW_KEEPRATIO);
    g_th1 = 3;
    g_th2 = 9;
    g_size= 1;
    createTrackbar("gth1","canny",&g_th1,100,on_Canny,0);
    createTrackbar("gth2","canny",&g_th2,100,on_Canny,0);
    createTrackbar("gsize","canny",&g_size,3,on_Canny,0);
    on_Canny(g_size,0);


    Mat abs_grad_x,abs_grad_y;
    Sobel(g_image,g_simage,g_image.depth(),2,0,3,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_simage,abs_grad_x);
    imshow("x-after",abs_grad_x);
    Sobel(g_image,g_simage,g_image.depth(),0,2,3,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_simage,abs_grad_y);
    imshow("y-after",abs_grad_y);

    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,g_simage);
    imshow("xy-after",g_simage);

    Mat abs_limage;
    Laplacian(g_image,g_limage,g_image.depth(),3,1,0,BORDER_DEFAULT);
    convertScaleAbs(g_limage,abs_limage);
    imshow("laplacian0",g_limage);
    imshow("laplacian",abs_limage);


    Mat schx,schy;
    Scharr(g_image,schx,g_image.depth(),1,0,1,0,BORDER_DEFAULT);
    imshow("g-scharr-x",schx);
    Scharr(g_image,schy,g_image.depth(),0,1,1,0,BORDER_DEFAULT);
    imshow("g-scharr-y",schy);


    while(char(waitKey(1))!='q'){}
    return 0;
}

void on_Canny(int ,void*){
    int size = g_size*2+1;
    if(size<=3) size=3;
    Canny(g_gimage,g_dimage,g_th1,g_th2,size);
    imshow("canny",g_dimage);
}
void on_Mouse(int event, int x,int y, int , void*){

}
