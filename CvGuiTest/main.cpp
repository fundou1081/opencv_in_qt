#include "mainwindow.h"
#include <QApplication>


using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug()<<QString::fromLocal8Bit("Test OK");

    waitKey(0);

    return a.exec();
}
