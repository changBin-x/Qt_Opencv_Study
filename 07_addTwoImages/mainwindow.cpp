/***
 *      "Date": "2020-8-15 13:40:53",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": 合成图片操作
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("图片线性混合示例");
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief 加载图片1
 */
void MainWindow::on_pBtn_loadImg1_clicked() {

  img1 = cv::imread("../../opencv430ForQtBuild_win64/data/LinuxLogo.jpg");

  if (img1.empty()) {
    QMessageBox::critical(this, "错误", "加载LinuxLogo失败", QMessageBox::Yes,
                          QMessageBox::Yes);
    return;
  }

  //重设图像大小为显示框的大小
  cv::Size dsize1 = cv::Size(ui->graphicsView_img1->width() - 8,
                             ui->graphicsView_img1->height() - 6);
  cv::Mat tempImg1;
  cv::resize(img1, tempImg1, dsize1);

  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换时需要rgbSwapped()将通道更改。
  QImage image1 = QImage((const uchar *)tempImg1.data, tempImg1.cols,
                         tempImg1.rows, QImage::Format_RGB888)
                      .rgbSwapped();
  QGraphicsScene *scene = new QGraphicsScene;
  scene->addPixmap(QPixmap::fromImage(image1));
  ui->graphicsView_img1->setScene(scene);
}

/**
 * @brief 加载图片1
 */
void MainWindow::on_pBtn_loadImg2_clicked() {
  img2 = cv::imread("../../opencv430ForQtBuild_win64/data/WindowsLogo.jpg");

  if (img2.empty()) {
    QMessageBox::critical(this, "错误", "加载WindowsLogo失败", QMessageBox::Yes,
                          QMessageBox::Yes);
    return;
  }

  //重设图像大小为显示框的大小
  cv::Size dsize2 = cv::Size(ui->graphicsView_img2->width() - 8,
                             ui->graphicsView_img2->height() - 6);
  cv::Mat tempImg2;
  cv::resize(img2, tempImg2, dsize2);

  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换时需要rgbSwapped()将通道更改。
  QImage image2 = QImage((const uchar *)tempImg2.data, tempImg2.cols,
                         tempImg2.rows, QImage::Format_RGB888)
                      .rgbSwapped();
  QGraphicsScene *scene = new QGraphicsScene;
  scene->addPixmap(QPixmap::fromImage(image2));
  ui->graphicsView_img2->setScene(scene);
}

/**
 * @brief 设置alpha的值
 */
void MainWindow::on_pBtn_setAlpha_clicked() {
  if (ui->lineEdit_alpha->text().isNull()) {
    alpha = 0.0;
  }
  alpha = ui->lineEdit_alpha->text().toDouble();
  if (alpha < 0.0) {
    alpha = 0.0;
  }
  if (alpha > 1.0) {
    alpha = 1.0;
  }
}

/**
 * @brief 合成两幅图片
 */
void MainWindow::on_pBtn_addImgs_clicked() {
  double beta = (1.0 - alpha);
  cv::Mat dstImg;
  cv::addWeighted(img1, alpha, img2, beta, 0.0, dstImg);

  //重设图像大小为显示框的大小
  cv::Size dsize = cv::Size(ui->graphicsView_addedImg->width() - 8,
                            ui->graphicsView_addedImg->height() - 6);
  cv::Mat tempDstImg;
  cv::resize(dstImg, tempDstImg, dsize);

  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换时需要rgbSwapped()将通道更改。
  QImage dstImage = QImage((const uchar *)tempDstImg.data, tempDstImg.cols,
                           tempDstImg.rows, QImage::Format_RGB888)
                        .rgbSwapped();
  QGraphicsScene *scene = new QGraphicsScene;
  scene->addPixmap(QPixmap::fromImage(dstImage));
  ui->graphicsView_addedImg->setScene(scene);
}
