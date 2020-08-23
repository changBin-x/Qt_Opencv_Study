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
  void dispalyCaption(QLabel *label, cv::Mat img);

private slots:
  void on_hSlider_kernelSize_sliderMoved(int position);

private:
  Ui::MainWindow *ui;
  cv::Mat srcImg, element;
  cv::Size dsize;
  int erosionElem, erosionSize;
  int dilationElem, dilationSize;
  int maxElem, maxKernelSize;
};
#endif // MAINWINDOW_H
