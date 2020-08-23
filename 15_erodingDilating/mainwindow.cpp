#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("图像的腐蚀和膨胀操作实例");

  erosionElem = erosionSize = dilationElem = dilationSize = 0;
  ui->label_kernelValue->setText(QString::number(dilationSize));
  maxElem = 2;
  maxKernelSize = 21;
  dsize = cv::Size(ui->label_srcImg->width(), ui->label_srcImg->height());
  srcImg = cv::imread("../../opencv430ForQtBuild_win64/data/LinuxLogo.jpg");
  dispalyCaption(ui->label_srcImg, srcImg);
  dispalyCaption(ui->label_erosionImg, srcImg);
  dispalyCaption(ui->label_dilationImg, srcImg);
}
void MainWindow::dispalyCaption(QLabel *label, cv::Mat img) {
  cv::resize(img, img, dsize);
  QImage Image = QImage((const uchar *)img.data, img.cols, img.rows, img.step,
                        QImage::Format_RGB888)
                     .rgbSwapped();
  label->setPixmap(QPixmap::fromImage(Image));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_hSlider_kernelSize_sliderMoved(int position) {
  cv::Mat erosionImg, dilationImg;
  dilationSize = 2 * position + 1;
  erosionSize = 2 * position + 1;
  qDebug() << "dilationSize=" << dilationSize
           << "\terosionSize=" << erosionSize;
  element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                      cv::Size(erosionSize, erosionSize),
                                      cv::Point(position, position));
  //腐蚀操作
  cv::erode(srcImg, erosionImg, element);
  dispalyCaption(ui->label_erosionImg, erosionImg);
  //膨胀操作
  cv::dilate(srcImg, dilationImg, element);
  dispalyCaption(ui->label_dilationImg, dilationImg);
  ui->label_kernelValue->setText(QString::number(dilationSize));
}
