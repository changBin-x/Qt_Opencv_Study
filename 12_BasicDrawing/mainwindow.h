#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  void myEllipse(cv::Mat img, double angle);
  void myFilledCircle(cv::Mat img, cv::Point center);
  void myPolygon(cv::Mat img);
  void myLine(cv::Mat img, cv::Point start, cv::Point end);
  void drawImage();
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  int w;
};
#endif // MAINWINDOW_H
