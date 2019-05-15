#ifndef WIDGET_H

#define WIDGET_H

#include <QWidget>
#include "qfiledialog.h"
#include "opencv2/opencv.hpp"
#include "qdebug.h"
#include <QImage>
using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void displayMat(Mat image);

private:
    Ui::Widget *ui;
    cv::Mat image;
};

#endif // WIDGET_H
