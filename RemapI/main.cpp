#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void on_Remap(int , void*);
void on_warpAffine(int , void*);
void on_equ(int ,void*);

Mat g_image,g_dimage,g_gimage;

int main(int argc, char *argv[]){

    g_image = imread("D:\\test.jpg",1);
    if(!g_image.data){
        cout<<"error"<<endl;return -1;}
    namedWindow("origin",WINDOW_KEEPRATIO);
    imshow("origin",g_image);


    on_equ(0 , 0);

    waitKey(0);
    return 0;
}


void on_Remap(int , void*){
    Mat mapx,mapy;
    g_dimage.create(g_image.size(),g_image.type());
    mapx.create(g_image.size(),CV_32FC1);
    mapy.create(g_image.size(),CV_32FC1);

    for(int j=0;j<g_image.rows;j++){
        for(int i=0;i<g_image.cols;i++){
            mapx.at<float>(j,i)=static_cast<float>(2*(i-g_image.cols*0.25)+500);
            mapy.at<float>(j,i)=static_cast<float>(g_image.rows-j);
        }
    }

    remap(g_image,g_dimage,mapx,mapy,INTER_LINEAR,BORDER_CONSTANT,Scalar(0,0,0));

    imshow("after",g_dimage);
}

void on_warpAffine(int , void*)
{
    Point2f tri[3];
    Point2f dtri[3];

    tri[0]=Point2f(0,0);
    tri[1]=Point2f(0,g_image.rows);
    tri[2]=Point2f(g_image.cols,0);

    dtri[0]=Point2f(g_image.cols*0.5,g_image.rows*0.65);
    dtri[1]=Point2f(g_image.cols*0.25,g_image.rows*0.75);
    dtri[2]=Point2f(g_image.cols*0.35,g_image.rows*0.85);

    Mat warpMat = getAffineTransform(tri,dtri);
    cout << warpMat<<endl;

    warpAffine(g_image,g_dimage,warpMat,g_image.size());
    imshow("Affine",g_dimage);

    Point2f center(g_image.cols/2,g_image.rows/2);
    float angle =45;
    float scale = 0.5;

    Mat rotMat = getRotationMatrix2D(center,angle,scale);
    cout << rotMat<<endl;
    warpAffine(g_image,g_dimage,rotMat,g_image.size(),INTER_LANCZOS4);
    imshow("rot",g_dimage);

    Point2f rec[4];
    Point2f drec[4];

    rec[0]=Point2f(0,0);
    rec[1]=Point2f(0,g_image.rows);
    rec[2]=Point2f(g_image.cols,0);
    rec[3]=Point2f(g_image.cols,g_image.rows);

    drec[0]=Point2f(g_image.cols*0.1,g_image.rows*0.1);
    drec[1]=Point2f(0,g_image.rows);
    drec[2]=Point2f(g_image.cols,0);
    drec[2]=Point2f(g_image.cols*0.5,g_image.rows*0.8);

    Mat tran = getPerspectiveTransform(rec,drec);
    cout << tran<<endl;

    warpPerspective(g_image,g_dimage,tran,g_image.size());
    imshow("per",g_dimage);

}


void on_equ(int ,void*)
{
    vector<Mat> channels;
    Mat imageB,imageG,imageR;

    split(g_image,channels);
    imageB=channels.at(0);
    imageG=channels.at(1);
    imageR=channels.at(2);

    equalizeHist(imageB,imageB);
    equalizeHist(imageG,imageG);
    equalizeHist(imageR,imageR);

    merge(channels,g_dimage);

    imshow("equ",g_dimage);
}

