#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QPixmap>
#include <opencv2/opencv.hpp>
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  static Scalar randomColor(RNG &rng);
  int Drawing_Random_Lines(Mat image, char *window_name, RNG rng);
  int Drawing_Random_Rectangles(Mat image, char *window_name, RNG rng);
  int Drawing_Random_Ellipses(Mat image, char *window_name, RNG rng);
  int Drawing_Random_Polylines(Mat image, char *window_name, RNG rng);
  int Drawing_Random_Filled_Polygons(Mat image, char *window_name, RNG rng);
  int Drawing_Random_Circles(Mat image, char *window_name, RNG rng);
  int Displaying_Random_Text(Mat image, char *window_name, RNG rng);
  int Displaying_Big_End(Mat image, char *window_name, RNG rng);
  int drawAllImgs();
  void cv2QImage(Mat img);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  int NUMBER, DELAY;
  int windowWidth, windowHeight, x1, x2, y1, y2;
};
#endif // MAINWINDOW_H
