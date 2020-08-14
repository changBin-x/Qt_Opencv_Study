#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QPixmap>
#include <iostream>
using namespace std;

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

private slots:
  void on_pBtn_loadImg_clicked();

  void on_pBtn_saveImgCpy_clicked();

private:
  Ui::MainWindow *ui;
  QString imgFileName;
  cv::Mat img, grayImg;
};
#endif // MAINWINDOW_H
