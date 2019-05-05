#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    img_name=QFileDialog::getOpenFileName(this,tr("Open Img"),".",tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    src = imread(img_name.toStdString());
    namedWindow("src");
    imshow("src",src);
    Mat dst;
    cvtColor(src,dst,CV_BGR2RGB);
    namedWindow("dst");
    imshow("dst",dst);
}
