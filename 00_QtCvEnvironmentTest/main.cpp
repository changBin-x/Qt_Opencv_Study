#include "mainwindow.h"

#include <QApplication>
using namespace cv;
int main(int argc, char *argv[]) {
  //  QApplication a(argc, argv);
  //    MainWindow w;
  //    w.show();

  cv::Mat image = cv::imread("../../opencv430ForQtBuild_win64/data/notes.png");
  cv::imshow("First Test", image);
  //  cvNamedWindow("window", CV_WINDOW_NORMAL);
  cv::waitKey(0);
  //  return a.exec();
  return 0;
}
