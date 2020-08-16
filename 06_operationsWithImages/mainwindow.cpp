/***
 *      "Date": "2020-8-14 20:27:12",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": 图像基本操作
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("图像基本操作");
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief 加载并显示图像
 * @param checked
 */
void MainWindow::on_pBtn_loadImg_clicked() {
  QString dlgTitle = "打开图片"; //设置选择图片的窗口的标题
  QString filter = "图片(*png *jpg *bmp)";        //文件过滤器
  QFileDialog::Options dlgOptions;                //对话框选项
  dlgOptions |= QFileDialog::DontUseNativeDialog; //不使用原始对话框，
                                                  //即使用QT的子窗口作为对话框
  QString selectedFilter;
  imgFileName =
      QFileDialog::getOpenFileName(this, dlgTitle, "", filter, &selectedFilter,
                                   dlgOptions); //保存选择的图片路径
  ui->lineEdit_imgFileName->clear();
  ui->lineEdit_imgFileName->setText(imgFileName); //显示图片名字
  std::string imgFileNameStr = imgFileName.toLatin1().data(); //转化为标准字符串

  img = cv::imread(imgFileNameStr);
  grayImg = cv::imread(imgFileNameStr, cv::IMREAD_GRAYSCALE);

  if (img.empty()) {
    ui->lbl_showImg->setText("图片加载失败");
    ui->lbl_showImg->setStyleSheet("color:#7c828e");
  }

  //重设图像大小为显示框的大小
  cv::Size dsize =
      cv::Size(ui->lbl_showImg->width(), ui->lbl_showImg->height());
  cv::Mat img1;
  cv::resize(img, img1, dsize);

  cv::Size dsizeGray =
      cv::Size(ui->lbl_showGrayImg->width(), ui->lbl_showGrayImg->height());
  cv::Mat grayImg1;
  cv::resize(grayImg, grayImg1, dsizeGray);

  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换前需要将通道更改。
  cv::Mat rgbImg;
  cv::cvtColor(img1, rgbImg, cv::COLOR_BGR2RGB);
  QImage image = QImage((const uchar *)rgbImg.data, rgbImg.cols, rgbImg.rows,
                        rgbImg.step, QImage::Format_RGB888);

  cv::Mat gray2rgbImg;
  cv::cvtColor(grayImg1, gray2rgbImg, cv::COLOR_GRAY2RGB);
  QImage grayImage =
      QImage((const uchar *)gray2rgbImg.data, gray2rgbImg.cols,
             gray2rgbImg.rows, rgbImg.step, QImage::Format_RGB888);

  //显示图像
  ui->lbl_showImg->setPixmap(QPixmap::fromImage(image));
  // Bug:此处显示的灰度图像
  ui->lbl_showGrayImg->setPixmap(QPixmap::fromImage(grayImage));

  /*
   * //单通道
  cv::Scalar intensity = img.at<uchar>(30, 50);
  //  cv::Scalar intensity = img.at<uchar>(Point(x, y));
  */
  //访问具有BGR颜色顺序的3通道图像的像素强度值
  cv::Vec3f intensity = img.at<cv::Vec3f>(30, 50);
  QString showIntensityStr =
      QString("(50,30)处图像的像素强度值为:blue=%1,green=%2,red=%3")
          .arg(intensity.val[0])
          .arg(intensity.val[1])
          .arg(intensity.val[2]);

  ui->textBrowser_imgInfo->insertPlainText(showIntensityStr);

  //利用cv::projectPoints和cv::Mat::at方法访问像素强度值
  std::vector<cv::Point2f> points;
  cv::Mat pointsMat = cv::Mat(points).reshape(1);
  cv::Point2f point = pointsMat.at<cv::Point2f>(50, 30);
}

void MainWindow::on_pBtn_saveImgCpy_clicked() {
  QFileInfo fileInfo = QFileInfo(imgFileName); //获取文件信息
  //这个方法把路径写死了，可以探索更加灵活的保存方法（类似于从任意途径加载图片）
  QString savedImgName = fileInfo.absolutePath() + "/" + fileInfo.baseName() +
                         "-copy." +
                         fileInfo.suffix(); //另存为副本,路径中不能有汉字
  std::string savedImgNameStr =
      savedImgName.toLatin1().data(); // QString转化为标准字符串
  cv::imwrite(savedImgNameStr, img);  //图像另存
}
