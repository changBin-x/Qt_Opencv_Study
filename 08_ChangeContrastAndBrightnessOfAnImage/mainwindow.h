#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QImage>
#include <QMainWindow>
#include <QPixmap>
#include <iostream>
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
  void changeImage(double alpha, int beta);

private slots:
  void on_hSlider_contrast_sliderMoved(int position);

  void on_hSlider_brightness_sliderMoved(int position);

private:
  Ui::MainWindow *ui;
  double alpha;
  int beta;
  cv::Mat srcImg, dstImg;
  cv::Size dsize;
};
#endif // MAINWINDOW_H
