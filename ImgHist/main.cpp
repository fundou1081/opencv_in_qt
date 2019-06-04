#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histone(Mat& image);


int main(int argc, char *argv[])
{
    Mat image = imread("D:\\ttest.jpg");

    Mat dimage;
    Mat hsvimage;

    if(!image.data){
        cout<<"error"<<endl;return -1;
    }

    cvtColor(image,hsvimage,COLOR_BGR2HSV);

    int hueBinNum =30;
    int saturationBinNum    =   32;
    int histSize[]={hueBinNum,saturationBinNum};

    float hueRange[]={0,180};

    float saturationRange[] = {0,256};

    const float* ranges[]={hueRange,saturationRange};

    MatND   dstHist;
    int channels[]={0,1};

    calcHist(&hsvimage,
             1,
             channels,
             Mat(),
             dstHist,
             2,
             histSize,
             ranges,true,false);

    double maxValue =0;
    minMaxLoc(dstHist,0,&maxValue,0,0);

    int scale=10;

    Mat histImg = Mat::zeros(saturationBinNum*scale,hueBinNum*10,CV_8UC3);

    for(int hue=0;hue<hueBinNum;hue++)
        for(int saturation=0;saturation<saturationBinNum;saturation++)
        {
            float binValue = dstHist.at<float>(hue,saturation);
            int intensity = cvRound(binValue*255/maxValue);

            rectangle(histImg,Point(hue*scale,saturation*scale),
                      Point((hue+1)*scale-1,(saturation+1)*scale-1),
                    Scalar::all(intensity),FILLED);
        }

    imshow("ori",image);
    imshow("H-S",histImg);

    histone(image);

    waitKey(0);

    return 0;
}

void histone(Mat& image){

    MatND dstHist;
    int dims =1;
    float hrange[] ={0,255};
    const float* ranges[]={hrange};
    int size = 256;
    int channel = 1;

    calcHist(&image,1,&channel,Mat(),dstHist,dims,&size,ranges);

    int scale =1;

    Mat dimage(size*scale,size,CV_8U,Scalar(0));

    double minV= 0;
    double maxV=0;

    minMaxLoc(dstHist,&minV,&maxV,0,0);

    int hpt = saturate_cast<int>(0.9*size);
    for(int i=0;i<256;i++)
    {
        float binV=dstHist.at<float>(i);
        int realV = saturate_cast<int>(binV*hpt/maxV);
        rectangle(dimage,Point(i*scale,size-1),Point((i+1)*scale,size-realV),Scalar(255));
        cout << binV<<endl;
    }
    imshow("uuu",dimage);

}
