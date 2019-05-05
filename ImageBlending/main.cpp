#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

    Mat image = imread("D:\\test.jpg");

    if(!image.data){
        cout<<"error"<<endl;return -1;
    }

    Mat dimage;
    vector<Mat> channels;
    Mat imageB,imageG,imageR;

    split(image,channels);
    imageB=channels.at(0);
    imageG=channels.at(1);
    imageR=channels.at(2);


    Mat Bimage,Gimage,Rimage;
    Mat Z=Mat::zeros(image.rows,image.cols,CV_8UC1);
    cout<<image.cols<<image.rows<<endl;
    channels.at(1)=Z;
    channels.at(2)=Z;
    merge(channels,Bimage);
    imshow("B",Bimage);

    channels.at(0)=Z;
    channels.at(1)=imageG;
    channels.at(2)=Z;
    merge(channels,Gimage);
    imshow("G",Gimage);

    channels.at(0)=Z;
    channels.at(1)=Z;
    channels.at(2)=imageR;
    merge(channels,Rimage);
    imshow("R",Rimage);


    waitKey(0);

    return 0;
}
