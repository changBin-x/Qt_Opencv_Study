#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("图像模糊示例");
  ui->label_srcImg->clear();

  cv::Mat srcImg = cv::imread("../../opencv430ForQtBuild_win64/data/lena.jpg");
  if (srcImg.empty()) {
    ui->label_srcImg->setText("图片加载失败");
  }
  //显示原图像
  dispalyCaption(ui->label_srcImg, srcImg);

  homogeneousblur(srcImg);
  gaussianBlur(srcImg);
  median_Blur(srcImg);
  bilateralFilter(srcImg);
}

MainWindow::~MainWindow() { delete ui; }

int MainWindow::dispalyCaption(QLabel *label, cv::Mat img) {
  cv::Size dsize = cv::Size(256, 256);
  cv::resize(img, img, dsize);
  QImage Image = QImage((const uchar *)img.data, img.cols, img.rows, img.step,
                        QImage::Format_RGB888)
                     .rgbSwapped();
  label->setPixmap(QPixmap::fromImage(Image));
  return 0;
}

/**
 * @brief 同类模糊
 * @param srcImg
 */
void MainWindow::homogeneousblur(cv::Mat srcImg) {

  cv::Mat dstImg = cv::Mat::zeros(srcImg.size(), srcImg.type());

  cv::blur(srcImg, dstImg, cv::Size(5, 5));

  dispalyCaption(ui->label_homogeneous, dstImg);
}

/**
 * @brief 高斯模糊
 * @param srcImg
 */
void MainWindow::gaussianBlur(cv::Mat srcImg) {
  cv::Mat dstImg = cv::Mat::zeros(srcImg.size(), srcImg.type());

  cv::GaussianBlur(srcImg, dstImg, cv::Size(5, 5), 0, 0);

  dispalyCaption(ui->label_Gaussian, dstImg);
}

/**
 * @brief 中位模糊
 * @param srcImg
 */
void MainWindow::median_Blur(cv::Mat srcImg) {
  cv::Mat dstImg = cv::Mat::zeros(srcImg.size(), srcImg.type());
  cv::medianBlur(srcImg, dstImg, 5);
  dispalyCaption(ui->label_Median, dstImg);
}

/**
 * @brief 双边模糊
 * @param srcImg
 */
void MainWindow::bilateralFilter(cv::Mat srcImg) {
  cv::Mat dstImg = cv::Mat::zeros(srcImg.size(), srcImg.type());

  cv::bilateralFilter(srcImg, dstImg, 2, 10, 5);

  dispalyCaption(ui->label_Bilateral, dstImg);
}
