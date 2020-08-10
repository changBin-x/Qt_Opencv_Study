#include "mainwindow.h"

#include <QApplication>
using namespace cv;
int main(int argc, char *argv[]) {
  //  QApplication a(argc, argv);
  //    MainWindow w;
  //    w.show();

  cv::Mat image = cv::imread("D:/opencv/examples/QtCvEnvironmentTest/test.jpg");
  cv::imshow("First Test", image);
  //  cvNamedWindow("window", CV_WINDOW_NORMAL);
  cv::waitKey(0);
  //  return a.exec();
  return 0;
}
