#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

    FileStorage fs("test.xml",FileStorage::WRITE);
    fs<<"frameout"<<5;
    time_t rawtime;
    time(&rawtime);
    fs<<"Data"<<asctime(localtime(&rawtime));
    Mat Matrix = (Mat_<double>(3,3)<<1000,0,320,0,1000,240,0,0,1);
    fs << "Matrix" << Matrix;
    fs.release();
    printf("done");

    FileStorage fs2("test.xml",FileStorage::READ);

    int count=fs2["frameout"];

    string date;
    fs2["Data"]>>date;

    Mat m;
    fs2["Matrix"]>> m;

    cout<<count;
    cout<<date<<m;

    return 0;
}
