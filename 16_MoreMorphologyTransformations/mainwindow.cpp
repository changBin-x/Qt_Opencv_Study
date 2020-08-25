#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("更多图像变换示例");

  src = cv::imread("../../opencv430ForQtBuild_win64/data/baboon.jpg",
                   cv::IMREAD_COLOR);
  showImage(src);
}

void MainWindow::showImage(cv::Mat img) {
  QImage Image = QImage((const uchar *)img.data, img.cols, img.rows, img.step,
                        QImage::Format_RGB888)
                     .rgbSwapped();
  ui->label_image->setPixmap(QPixmap::fromImage(Image));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  //因为MORPH_X:2,3,4,5,6
  cv::Mat dst;
  int operation = ui->comboBox_operator->currentIndex() + 2;
  cv::Mat element = cv::getStructuringElement(
      cv::MORPH_ELLIPSE, cv::Size(2 * position + 1, 2 * position + 1),
      cv::Point(position, position));
  cv::morphologyEx(src, dst, operation, element);
  showImage(dst);
}

void MainWindow::on_comboBox_operator_currentIndexChanged(int index) {
  Q_UNUSED(index);
  ui->label_image->clear();
  ui->horizontalSlider->setValue(0);
  showImage(src);
}
