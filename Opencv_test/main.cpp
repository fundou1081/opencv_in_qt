#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    Mat img = imread("D:/image/desktop.jpg");
    namedWindow("测试opencv");
    imshow("test",img);
    printf("gg");
    waitKey(0);
    return 0;
}
