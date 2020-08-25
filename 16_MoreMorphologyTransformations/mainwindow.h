#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
  void showImage(cv::Mat img);
  ~MainWindow();

private slots:
  void on_horizontalSlider_sliderMoved(int position);

  void on_comboBox_operator_currentIndexChanged(int index);

private:
  Ui::MainWindow *ui;
  cv::Mat src;
};
#endif // MAINWINDOW_H
