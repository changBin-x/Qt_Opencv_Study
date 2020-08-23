#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
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
  ~MainWindow();
  int dispalyCaption(QLabel *label, cv::Mat img);
  void homogeneousblur(cv::Mat srcImg);
  void gaussianBlur(cv::Mat srcImg);
  void median_Blur(cv::Mat srcImg);
  void bilateralFilter(cv::Mat srcImg);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
