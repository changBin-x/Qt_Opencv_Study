#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
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

private slots:
  void on_pBtn_loadImg1_clicked();

  void on_pBtn_loadImg2_clicked();

  void on_pBtn_setAlpha_clicked();

  void on_pBtn_addImgs_clicked();

private:
  Ui::MainWindow *ui;
  cv::Mat img1, img2;
  double alpha;
};
#endif // MAINWINDOW_H
