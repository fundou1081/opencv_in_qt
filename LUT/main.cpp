#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void ImageChange(Mat &img, const uchar* const lookup){
    int rows = img.rows;
    int cols = img.cols*img.channels();
    for(int i=0;i<rows;i++){
        uchar* p = img.ptr<uchar>(i);
        for(int j=0;j<cols;j++){
            p[j]=lookup[p[j]];
        }
    }
}

int main(int argc, char *argv[]){

    Mat image = imread("D:\\test.jpg");

    if(!image.data){
        cout<<"error"<<endl;return -1;
    }
    imshow("First",image);

    //建立查找表
    uchar lookup[256];
    for(int i=0; i<256; i++)
        lookup[i]=255-i;

    double time0=static_cast<double>(getTickCount());

    //ImageChange(image, lookup);

    time0=((double)getTickCount()-time0)/getTickFrequency();
    cout<<time0<<endl;
    imshow("Second",image);

    Mat lookUpTable(1,256,CV_8U);
    uchar *p=lookUpTable.data;
    for(int i=0;i<256;i++){
        p[i]=20*(i/20);
    }
    Mat dimage;
    time0=(double)getTickCount();
    LUT(image,lookUpTable,dimage);
    time0=((double)getTickCount()-time0)/getTickFrequency();
    cout<<time0<<endl;
    imshow("3rd",dimage);


    waitKey();

    return 0;
}
