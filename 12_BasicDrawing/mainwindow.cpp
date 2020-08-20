/***
 *      "Date": "",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": "简单的几何绘图"
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("简单的几何绘图");

  w = 400;
  drawImage();
}

/**
 * @brief 绘制不同角度的固定大小的椭圆
 * @param img
 * @param angle
 */
void MainWindow::myEllipse(cv::Mat img, double angle) {
  int thickness = 2;
  int lineType = 8;

  cv::ellipse(img, cv::Point(w / 2, w / 2), cv::Size(w / 4, w / 16), angle, 0,
              360, cv::Scalar(255, 0, 0), thickness, lineType);
}

/**
 * @brief 画一个固定大小的实心圆
 * @param img
 * @param center
 */
void MainWindow::myFilledCircle(cv::Mat img, cv::Point center) {
  cv::circle(img, center, w / 32, cv::Scalar(0, 0, 255), cv::FILLED,
             cv::LINE_8);
}

/**
 * @brief 画一个简单的凹多边形
 * @param img
 */
void MainWindow::myPolygon(cv::Mat img) {
  int lineType = cv::LINE_8;
  /**创建一些点**/
  cv::Point rookPoints[1][20];
  rookPoints[0][0] = cv::Point(w / 4, 7 * w / 8);
  rookPoints[0][1] = cv::Point(3 * w / 4, 7 * w / 8);
  rookPoints[0][2] = cv::Point(3 * w / 4, 13 * w / 16);
  rookPoints[0][3] = cv::Point(11 * w / 16, 13 * w / 16);
  rookPoints[0][4] = cv::Point(19 * w / 32, 3 * w / 8);
  rookPoints[0][5] = cv::Point(3 * w / 4, 3 * w / 8);
  rookPoints[0][6] = cv::Point(3 * w / 4, w / 8);
  rookPoints[0][7] = cv::Point(26 * w / 40, w / 8);
  rookPoints[0][8] = cv::Point(26 * w / 40, w / 4);
  rookPoints[0][9] = cv::Point(22 * w / 40, w / 4);
  rookPoints[0][10] = cv::Point(22 * w / 40, w / 8);
  rookPoints[0][11] = cv::Point(18 * w / 40, w / 8);
  rookPoints[0][12] = cv::Point(18 * w / 40, w / 4);
  rookPoints[0][13] = cv::Point(14 * w / 40, w / 4);
  rookPoints[0][14] = cv::Point(14 * w / 40, w / 8);
  rookPoints[0][15] = cv::Point(w / 4, w / 8);
  rookPoints[0][16] = cv::Point(w / 4, 3 * w / 8);
  rookPoints[0][17] = cv::Point(13 * w / 32, 3 * w / 8);
  rookPoints[0][18] = cv::Point(5 * w / 16, 13 * w / 16);
  rookPoints[0][19] = cv::Point(w / 4, 13 * w / 16);

  const cv::Point *ppt[1] = {rookPoints[0]};
  int npt[] = {20};

  cv::fillPoly(img, ppt, npt, 1, cv::Scalar(255, 255, 255), lineType);
}

/**
 * @brief 画一条简单的线
 * @param img
 * @param start
 * @param end
 */
void MainWindow::myLine(cv::Mat img, cv::Point start, cv::Point end) {
  int thickness = 2;
  int lineType = cv::LINE_8;

  cv::line(img, start, end, cv::Scalar(0, 0, 0), thickness, lineType);
}

/**
 * @brief 创建图像
 */
void MainWindow::drawImage() {
  //创建空白图像
  cv::Mat atomImg = cv::Mat::zeros(w, w, CV_8UC3);
  cv::Mat rookImg = cv::Mat::zeros(w, w, CV_8UC3);

  //画一个简单的原子
  myEllipse(atomImg, 90);
  myEllipse(atomImg, 0);
  myEllipse(atomImg, 45);
  myEllipse(atomImg, -45);
  //显示原子
  QImage atomImage = QImage((const uchar *)atomImg.data, atomImg.cols,
                            atomImg.rows, atomImg.step, QImage::Format_RGB888)
                         .rgbSwapped();
  ui->lbl_imgAtom->setPixmap(QPixmap::fromImage(atomImage));

  //画圆
  myFilledCircle(atomImg, cv::Point(w / 2, w / 2));

  //创建凸多边形
  myPolygon(rookImg);
  //画矩形
  cv::rectangle(rookImg, cv::Point(0, 7 * w / 8), cv::Point(w, w),
                cv::Scalar(0, 255, 255), cv::FILLED, cv::LINE_8);

  //创建几条线
  myLine(rookImg, cv::Point(0, 15 * w / 16), cv::Point(w, 15 * w / 16));
  myLine(rookImg, cv::Point(w / 4, 7 * w / 8), cv::Point(w / 4, w));
  myLine(rookImg, cv::Point(w / 2, 7 * w / 8), cv::Point(w / 2, w));
  myLine(rookImg, cv::Point(3 * w / 4, 7 * w / 8), cv::Point(3 * w / 4, w));
  QImage rookImage = QImage((const uchar *)rookImg.data, rookImg.cols,
                            rookImg.rows, rookImg.step, QImage::Format_RGB888)
                         .rgbSwapped();
  ui->lbl_imgRook->setPixmap(
      QPixmap::fromImage(rookImage)); //显示出来像一个核弹？
}

MainWindow::~MainWindow() { delete ui; }
