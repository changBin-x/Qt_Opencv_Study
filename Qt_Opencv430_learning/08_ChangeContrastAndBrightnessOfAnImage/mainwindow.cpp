/***
 *      "Date": "2020-8-16 11:31:38",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": "改变图像对比度和亮度示例"
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  alpha = 1.0;
  beta = 0;
  this->setWindowTitle("改变图像对比度和亮度");
  //!控件初始化
  ui->lineEdit_contrast->setReadOnly(1);
  ui->lineEdit_contrast->setText(QString::number(1.0));
  ui->lineEdit_brightness->setReadOnly(1);
  ui->lineEdit_brightness->setText(QString::number(0));

  //α设置为1.0~3.0，
  ui->hSlider_contrast->setMinimum(10);
  ui->hSlider_contrast->setMaximum(30);
  ui->hSlider_contrast->setValue(10);
  ui->hSlider_contrast->setSingleStep(1);
  ui->hSlider_contrast->setPageStep(1);
  //β设置为0~100
  ui->hSlider_brightness->setMinimum(0);
  ui->hSlider_brightness->setMaximum(100);
  ui->hSlider_brightness->setValue(0);
  ui->hSlider_brightness->setSingleStep(1); //键盘滑动时的步长
  ui->hSlider_brightness->setPageStep(5);   //鼠标滑动时的步长

  ui->label_srcImg->clear();
  ui->label_dstImg->clear();
  //!控件初始化

  //显示原图像
  srcImg = cv::imread("../../opencv430ForQtBuild_win64/data/lena.jpg",
                      cv::IMREAD_COLOR);
  if (srcImg.empty()) {
    ui->label_srcImg->setText("加载图片失败");
    ui->label_srcImg->setStyleSheet("color:#F46A4E");
    return;
  }
  //重设图片大小
  dsize = cv::Size(ui->label_srcImg->width(), ui->label_srcImg->height());
  cv::Mat tempSrcImg;
  cv::resize(srcImg, tempSrcImg, dsize);
  //注意:此处使用了QImage::Format_BGR888而不是QImage::Format_RGB888
  QImage srcImage =
      QImage((const uchar *)tempSrcImg.data, tempSrcImg.cols, tempSrcImg.rows,
             tempSrcImg.step, QImage::Format_BGR888);
  ui->label_srcImg->setPixmap(QPixmap::fromImage(srcImage));
  ui->label_dstImg->setPixmap(QPixmap::fromImage(srcImage));
  //创建新图片
  dstImg = cv::Mat::zeros(srcImg.size(), srcImg.type());
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief 改变图像亮度和对比度
 * @param alpha
 * @param beta
 */
void MainWindow::changeImage(double alpha, int beta) {
  for (int y = 0; y < srcImg.rows; y++) {           //遍历每一行
    for (int x = 0; x < srcImg.cols; x++) {         //遍历每一列
      for (int c = 0; c < srcImg.channels(); c++) { //遍历每一个通道
        dstImg.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
            alpha * srcImg.at<cv::Vec3b>(y, x)[c] + beta);
      }
    }
  }
  cv::Mat tempDstImg;
  cv::resize(dstImg, tempDstImg, dsize);
  QImage dstImage =
      QImage((const uchar *)tempDstImg.data, tempDstImg.cols, tempDstImg.rows,
             tempDstImg.step, QImage::Format_BGR888);
  ui->label_dstImg->setPixmap(QPixmap::fromImage(dstImage));
}

/**
 * @brief 对比度滑动条移动时的动作
 * @param position
 */
void MainWindow::on_hSlider_contrast_sliderMoved(int position) {
  alpha = position / 10.0; //由于QSlider步长只能为整数，所以对数值进行缩放
  ui->lineEdit_contrast->setText(QString::number(alpha, 'f', 1));
  changeImage(alpha, beta);
}

/**
 * @brief 亮度滑动条移动时的动作
 * @param position
 */
void MainWindow::on_hSlider_brightness_sliderMoved(int position) {
  beta = position;
  ui->lineEdit_brightness->setText(QString::number(beta));
  changeImage(alpha, beta);
}
