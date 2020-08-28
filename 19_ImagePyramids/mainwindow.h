#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
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
  void imgOperation();

private slots:
  void on_pBtn_showSrc_clicked();

  void on_pBtn_zoomOut_clicked();

  void on_pBtn_zoomIn_clicked();

private:
  Ui::MainWindow *ui;
  cv::Mat src;
};
#endif // MAINWINDOW_H
