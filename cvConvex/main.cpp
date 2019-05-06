#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat g_image,g_dimage,g_gimage;

int g_th1,g_th2,g_size;

int main(int argc, char *argv[]){

    g_image.create(600,600,CV_8UC3);
    RNG& rng=theRNG();

    while(1){

        char key;
        int count =(unsigned)rng%100+3;
        vector<Point> points;

        for(int i=0;i<count;i++)
        {
            Point point;
            point.x=rng.uniform(g_image.cols/4,g_image.rows*3/4);
            point.y=rng.uniform(g_image.rows/4,g_image.cols*3/4);
            points.push_back(point);
        }

        vector<int> hull;
        convexHull(Mat(points),hull,true);

        g_image = Scalar::all(0);
        for(int i=0; i<count;i++)
            circle(g_image,points[i],3,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),FILLED,LINE_AA);

        int hullcount  = (int)hull.size();
        Point point0=points[hull[hullcount-1]];

        for(int i=0;i<hullcount;i++)
        {
            Point point = points[hull[i]];
            line(g_image,point0,point,Scalar(255,255,255),2,LINE_AA);
            point0=point;
        }

        Rect rec;
        rec = boundingRect(points);
        rectangle(g_image,rec,Scalar(150,150,150),1,LINE_AA,0);

        Point2f cc;
        float  rr;
        minEnclosingCircle(points,cc,rr);
        circle(g_image,cc,rr,Scalar(255,0,0),1,LINE_AA);

        vector<Point> tri;
        minEnclosingTriangle(points,tri);
        point0=tri[2];
        for(int i=0;i<(int)tri.size();i++)
        {
            Point tt = tri[i];
            line(g_image,point0,tt,Scalar(255,0,255),2,LINE_AA);
            point0=tt;
        }


        imshow("point",g_image);

        key=(char)waitKey();
    }


    waitKey(0);
    return 0;
}
