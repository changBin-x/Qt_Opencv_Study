#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("傅里叶变换示例");
  //读取灰度图像
  srcImg = cv::imread("../../opencv430ForQtBuild_win64/data/lena.jpg",
                      cv::IMREAD_GRAYSCALE);
  if (srcImg.empty()) {
    qDebug() << "读取图像失败";
  }

  //重设图片大小
  cv::Size dsize;
  dsize = cv::Size(ui->lbl_srcImg->width(), ui->lbl_srcImg->height());
  cv::Mat tempSrcImg;
  cv::resize(srcImg, tempSrcImg, dsize);
  //注意:此处使用了 QImage::Format_Grayscale8
  QImage srcImage =
      QImage((const uchar *)tempSrcImg.data, tempSrcImg.cols, tempSrcImg.rows,
             tempSrcImg.step, QImage::Format_Grayscale8);
  ui->lbl_srcImg->setPixmap(QPixmap::fromImage(srcImage)); //显示灰度图像
  //傅里叶变换操作
  dftOperation(srcImg);
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief 对图片进行离散傅里叶操作
 * @param srcImg
 */
void MainWindow::dftOperation(cv::Mat srcImg) {
  //扩展图像
  cv::Mat padded; //将输入图像扩展到最佳尺寸
  int m = cv::getOptimalDFTSize(srcImg.rows);
  int n = cv::getOptimalDFTSize(srcImg.cols);
  cv::copyMakeBorder(srcImg, padded, 0, m - srcImg.rows, 0, n - srcImg.cols,
                     cv::BORDER_CONSTANT, cv::Scalar::all(0));

  //复部和实部
  cv::Mat planes[] = {cv::Mat_<float>(padded),
                      cv::Mat::zeros(padded.size(), CV_32F)};
  cv::Mat complexI;
  cv::merge(planes, 2, complexI); //将零添加到展开的另一个平面

  // dft
  cv::dft(complexI, complexI); //这样结果可以适合源矩阵

  //计算幅度并转换到对数刻度
  // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
  //幅度
  cv::split(complexI, planes); // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
  cv::magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
  cv::Mat magI = planes[0];

  magI += cv::Scalar::all(1); //换到对数刻度
  cv::log(magI, magI);

  //裁剪-重排
  magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

  //重新排列傅立叶图像的象限，以使原点位于图像中心
  int cx = magI.cols / 2;
  int cy = magI.rows / 2;
  //为每个象限创建一个ROI
  cv::Mat q0(magI, cv::Rect(0, 0, cx, cx));   //左上方
  cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));  // 右上
  cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));  // 左下方
  cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // 右下

  cv::Mat temp; //交换象限（左上角-右下角）
  q0.copyTo(temp);
  q3.copyTo(q0);
  temp.copyTo(q3);

  q1.copyTo(temp);
  q2.copyTo(q1);
  temp.copyTo(q2);

  //归一化
  //将具有浮点值的矩阵转换为可见的图像形式（在0和1之间的浮点数）。
  //注意这和官网的教程不一致，是为了能用QImage显示，参见第03节
  cv::normalize(magI, magI, 0, 255, cv::NORM_MINMAX, -1);
  //  qDebug() << magI.type();     //此处Mat的类型为5，即CV_32F
  magI.convertTo(magI, CV_8U); //再进行一次转换是为了能用QImage显示
  cv::Mat tempMagI;
  cv::Size dsize1 = cv::Size(ui->lbl_magImg->width(), ui->lbl_magImg->height());
  cv::resize(magI, tempMagI, dsize1);
  //注意:此处使用了 QImage::Format_Grayscale8
  QImage magImage =
      QImage((const uchar *)tempMagI.data, tempMagI.cols, tempMagI.rows,
             tempMagI.step, QImage::Format_Grayscale8);
  ui->lbl_magImg->setPixmap(QPixmap::fromImage(magImage)); //显示灰度图像
}
