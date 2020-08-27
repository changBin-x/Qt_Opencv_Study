#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("提取图像中垂直和水平直线示例");
  handleSrcImg();
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief 显示灰度图像
 * @param label
 * @param img
 */
void MainWindow::dispalyImage(QLabel *label, cv::Mat img) {
  cv::Size dsize = cv::Size(ui->lbl_srcImg->width(), ui->lbl_srcImg->height());
  cv::resize(img, img, dsize);
  QImage Image = QImage((const uchar *)img.data, img.cols, img.rows, img.step,
                        QImage::Format_Grayscale8);

  label->setPixmap(QPixmap::fromImage(Image));
}

/**
 * @brief 处理图像
 */
void MainWindow::handleSrcImg() {
  ui->lbl_srcImg->clear();
  src = cv::imread("../../opencv430ForQtBuild_win64/data/notes.png",
                   cv::IMREAD_COLOR);
  if (src.empty()) {
    ui->lbl_srcImg->setText("加载图片失败");
    return;
  }

  if (src.channels() == 3) {
    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
  }
  dispalyImage(ui->lbl_srcImg, src);

  //在灰色的bitwise_not处应用adaptiveThreshold，注意〜符号
  cv::Mat bw;
  cv::adaptiveThreshold(~src, bw, 255, cv::ADAPTIVE_THRESH_MEAN_C,
                        cv::THRESH_BINARY, 15, -2);
  dispalyImage(ui->lbl_bitwiseImg, bw);

  //创建将用于提取水平线和垂直线的图像
  cv::Mat horizontal = bw.clone();
  cv::Mat vertical = bw.clone();
  //在水平轴上指定尺寸
  int horizontalSize = horizontal.cols / 30;
  //创建用于通过形态学操作提取水平线的结构元素
  cv::Mat horizontalStructure =
      cv::getStructuringElement(cv::MORPH_RECT, cv::Size(horizontalSize, 1));
  //应用形态学运算
  cv::erode(horizontal, horizontal, horizontalStructure, cv::Point(-1, -1));
  cv::dilate(horizontal, horizontal, horizontalStructure, cv::Point(-1, -1));
  //显示提取到的水平线
  dispalyImage(ui->lbl_hLinesImg, horizontal);

  //在垂直轴上指定尺寸
  int verticalSize = vertical.rows / 30;
  //创建用于通过形态学操作提取垂直线的结构元素
  cv::Mat verticalStructure =
      cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, verticalSize));
  //应用形态学运算
  cv::erode(vertical, vertical, verticalStructure, cv::Point(-1, -1));
  cv::dilate(vertical, vertical, verticalStructure, cv::Point(-1, -1));
  //显示提取到的垂直线
  dispalyImage(ui->lbl_vLinesImg, vertical);

  //反转垂直图像
  cv::bitwise_not(vertical, vertical);
  dispalyImage(ui->lbl_bitwiseVLineImg, vertical);

  //----------------------根据逻辑提取边缘和平滑图像--------------------------------
  // Step1 提取边缘
  cv::Mat edges;
  cv::adaptiveThreshold(vertical, edges, 255, cv::ADAPTIVE_THRESH_MEAN_C,
                        cv::THRESH_BINARY, 3, -2);
  dispalyImage(ui->lbl_edgesImg, edges);
  // step2 膨胀边界
  cv::Mat kernel = cv::Mat::ones(2, 2, CV_8UC1);
  cv::dilate(edges, edges, kernel);
  dispalyImage(ui->lbl_dilateEdgesImg, edges);
  // Step3  src.copyTo(smooth)
  cv::Mat smooth;
  vertical.copyTo(smooth);
  // Step4 滤波
  cv::blur(smooth, smooth, cv::Size(2, 2));
  // Step5 smooth.copyTo(src, edges)
  smooth.copyTo(vertical, edges);
  //展示最终结果
  dispalyImage(ui->lbl_resultImg, vertical);
  //-------------------------------------------------------------------
}
