#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;
using namespace cv;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    img_name = QFileDialog::getOpenFileName(this,tr("Open Img"),".",tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    if(img_name.length()<=0) return;

    qDebug()<<img_name;

    src =imread(img_name.toUtf8().data());
    namedWindow("src",WINDOW_NORMAL);
    if(!src.empty()){
        imshow("src",src);
    }

    //cvtColor(src,src,CV_BGR2RGB);
    img=QImage((const unsigned char*)(src.data),src.cols,src.rows,QImage::Format_RGB888 );
    ui->label->setPixmap(QPixmap::fromImage(img));
    //ui->label->resize(ui->label->pixmap()->size());
    ui->label->resize(500,500);
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}
