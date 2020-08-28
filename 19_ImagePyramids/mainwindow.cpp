#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("金字塔示例");
  this->statusBar()->hide();
  ui->lbl_img->clear();
  imgOperation();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::imgOperation() {
  src = cv::imread("../../opencv430ForQtBuild_win64/data/chicky_512.png");
  if (src.empty()) {
    ui->lbl_img->setText("打开图片失败");
    return;
  }
  cv::Size dsize = cv::Size(256, 256);
  cv::resize(src, src, dsize);
  this->resize(280, 320); //重设窗口大小

  QImage Image = QImage((const uchar *)src.data, src.cols, src.rows, src.step,
                        QImage::Format_BGR888);
  ui->lbl_img->setPixmap(QPixmap::fromImage(Image));
}

/**
 * @brief 显示原图
 */
void MainWindow::on_pBtn_showSrc_clicked() {
  this->resize(280, 320); //重设窗口大小
  ui->lbl_img->resize(256, 256);
  QImage Image = QImage((const uchar *)src.data, src.cols, src.rows, src.step,
                        QImage::Format_BGR888);
  ui->lbl_img->setPixmap(QPixmap::fromImage(Image));
}

/**
 * @brief 放大一倍
 */
void MainWindow::on_pBtn_zoomOut_clicked() {
  cv::Mat zoomOut;
  this->resize(532, 572);
  ui->lbl_img->resize(512, 512);

  cv::pyrUp(src, zoomOut, cv::Size(512, 512));
  QImage Image = QImage((const uchar *)zoomOut.data, zoomOut.cols, zoomOut.rows,
                        zoomOut.step, QImage::Format_BGR888);
  ui->lbl_img->setPixmap(QPixmap::fromImage(Image));
}

/**
 * @brief 缩小1倍
 */
void MainWindow::on_pBtn_zoomIn_clicked() {
  cv::Mat zoomIn;
  this->resize(148, 188);
  ui->lbl_img->resize(128, 128);
  cv::pyrDown(src, zoomIn, cv::Size(128, 128));
  QImage Image = QImage((const uchar *)zoomIn.data, zoomIn.cols, zoomIn.rows,
                        zoomIn.step, QImage::Format_BGR888);
  ui->lbl_img->setPixmap(QPixmap::fromImage(Image));
}
