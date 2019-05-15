#include "widget.h"
#include "ui_widget.h"

using namespace  cv;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image(*.jpg)"));
    qDebug() << filename <<endl;
    image = cv::imread(filename.toStdString());
    displayMat(image);
}

void Widget::displayMat(Mat image){
    Mat rgb;
    QImage img;
    cvtColor(image,rgb,COLOR_BGR2RGB);
    img = QImage((const unsigned char*)(rgb.data),rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
    ui->scrollAreaWidgetContents->setGeometry(0,0,img.width(),img.height());

    QPixmap pix2 = QPixmap::fromImage(img);
    pix2=pix2.scaled(ui->label_2->size());
    ui->label_2->setPixmap(pix2);
}
