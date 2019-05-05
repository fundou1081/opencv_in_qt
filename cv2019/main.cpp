#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
     cout<<argv[0]<<endl;
     printf("%s",argv[0]);
     Mat image = imread("D:\\test.jpg");
     //cvNamedWindow("window", CV_WINDOW_NORMAL);
     //imshow("window",image);

     Mat dimage;
     cvtColor(image,dimage,COLOR_BGR2RGB);
     namedWindow("BGR2XXX");
     imshow("BGR2XXX",dimage);

     //Mat C=(Mat_<double>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
     //cout<<C;

     int divideWith=10;
     uchar tabel[256];
     for(int i=0;i<256;i++){
         table[i]=divideWith*(i/divideWith);
     }

     Mat lookUpTable(1,256,CV_8U);
     uchar *p=lookUpTable.data;
     for(int i=0;i<256;++i){
         p[i]=tabel[i];
     }

     waitKey(0);
 }


