#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Opencv的随机数和文本示例");
  NUMBER = 100;
  DELAY = 5;
  windowWidth = 900;
  windowHeight = 600;
  x1 = -windowWidth / 2;
  x2 = windowWidth * 3 / 2;
  y1 = windowHeight / 2;
  y2 = windowHeight * 3 / 2;

  drawAllImgs();
}

Scalar MainWindow::randomColor(RNG &rng) {
  int icolor = (unsigned)rng;
  return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

/**
 * @brief 绘制随机线条
 * @param image
 * @param window_name
 * @param rng
 * @return
 */
int MainWindow::Drawing_Random_Lines(Mat image, char *window_name, RNG rng) {
  Point pt1, pt2;

  for (int i = 0; i < NUMBER; i++) {
    pt1.x = rng.uniform(x1, x2);
    pt1.y = rng.uniform(y1, y2);
    pt2.x = rng.uniform(x1, x2);
    pt2.y = rng.uniform(y1, y2);

    line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::Drawing_Random_Rectangles(Mat image, char *window_name,
                                          RNG rng) {
  Point pt1, pt2;
  int lineType = 8;
  int thickness = rng.uniform(-3, 10);

  for (int i = 0; i < NUMBER; i++) {
    pt1.x = rng.uniform(x1, x2);
    pt1.y = rng.uniform(y1, y2);
    pt2.x = rng.uniform(x1, x2);
    pt2.y = rng.uniform(y1, y2);

    rectangle(image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);

    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::Drawing_Random_Ellipses(Mat image, char *window_name, RNG rng) {
  int lineType = 8;

  for (int i = 0; i < NUMBER; i++) {
    Point center;
    center.x = rng.uniform(x1, x2);
    center.y = rng.uniform(y1, y2);

    Size axes;
    axes.width = rng.uniform(0, 200);
    axes.height = rng.uniform(0, 200);

    double angle = rng.uniform(0, 180);

    ellipse(image, center, axes, angle, angle - 100, angle + 200,
            randomColor(rng), rng.uniform(-1, 9), lineType);

    imshow(window_name, image);
    cv2QImage(image);

    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::Drawing_Random_Polylines(Mat image, char *window_name,
                                         RNG rng) {
  int lineType = 8;

  for (int i = 0; i < NUMBER; i++) {
    Point pt[2][3];
    pt[0][0].x = rng.uniform(x1, x2);
    pt[0][0].y = rng.uniform(y1, y2);
    pt[0][1].x = rng.uniform(x1, x2);
    pt[0][1].y = rng.uniform(y1, y2);
    pt[0][2].x = rng.uniform(x1, x2);
    pt[0][2].y = rng.uniform(y1, y2);
    pt[1][0].x = rng.uniform(x1, x2);
    pt[1][0].y = rng.uniform(y1, y2);
    pt[1][1].x = rng.uniform(x1, x2);
    pt[1][1].y = rng.uniform(y1, y2);
    pt[1][2].x = rng.uniform(x1, x2);
    pt[1][2].y = rng.uniform(y1, y2);

    const Point *ppt[2] = {pt[0], pt[1]};
    int npt[] = {3, 3};

    polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1, 10),
              lineType);

    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }
  return 0;
}

int MainWindow::Drawing_Random_Filled_Polygons(Mat image, char *window_name,
                                               RNG rng) {
  int lineType = 8;

  for (int i = 0; i < NUMBER; i++) {
    Point pt[2][3];
    pt[0][0].x = rng.uniform(x1, x2);
    pt[0][0].y = rng.uniform(y1, y2);
    pt[0][1].x = rng.uniform(x1, x2);
    pt[0][1].y = rng.uniform(y1, y2);
    pt[0][2].x = rng.uniform(x1, x2);
    pt[0][2].y = rng.uniform(y1, y2);
    pt[1][0].x = rng.uniform(x1, x2);
    pt[1][0].y = rng.uniform(y1, y2);
    pt[1][1].x = rng.uniform(x1, x2);
    pt[1][1].y = rng.uniform(y1, y2);
    pt[1][2].x = rng.uniform(x1, x2);
    pt[1][2].y = rng.uniform(y1, y2);

    const Point *ppt[2] = {pt[0], pt[1]};
    int npt[] = {3, 3};

    fillPoly(image, ppt, npt, 2, randomColor(rng), lineType);

    //    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }
  return 0;
}

int MainWindow::Drawing_Random_Circles(Mat image, char *window_name, RNG rng) {
  int lineType = 8;

  for (int i = 0; i < NUMBER; i++) {
    Point center;
    center.x = rng.uniform(x1, x2);
    center.y = rng.uniform(y1, y2);

    circle(image, center, rng.uniform(0, 300), randomColor(rng),
           rng.uniform(-1, 9), lineType);

    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::Displaying_Random_Text(Mat image, char *window_name, RNG rng) {
  int lineType = 8;

  for (int i = 1; i < NUMBER; i++) {
    Point org;
    org.x = rng.uniform(x1, x2);
    org.y = rng.uniform(y1, y2);

    putText(image, "Testing text rendering", org, rng.uniform(0, 8),
            rng.uniform(0, 100) * 0.05 + 0.1, randomColor(rng),
            rng.uniform(1, 10), lineType);

    imshow(window_name, image);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::Displaying_Big_End(Mat image, char *window_name, RNG rng) {
  Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
  Point org((windowWidth - textsize.width) / 2,
            (windowHeight - textsize.height) / 2);
  int lineType = 8;

  Mat image2;

  for (int i = 0; i < 255; i += 2) {
    image2 = image - Scalar::all(i);
    putText(image2, "OpenCV forever!", org, FONT_HERSHEY_COMPLEX, 3,
            Scalar(i, i, 255), 5, lineType);

    imshow(window_name, image2);
    cv2QImage(image);
    if (waitKey(DELAY) >= 0) {
      return -1;
    }
  }

  return 0;
}

int MainWindow::drawAllImgs() {
  int c;

  /// Start creating a window
  char window_name[] = "Drawing_2 Tutorial";

  /// Also create a random object (RNG)
  RNG rng(0xFFFFFFFF);

  /// Initialize a matrix filled with zeros
  Mat image = Mat::zeros(windowHeight, windowWidth, CV_8UC3);
  /// Show it in a window during DELAY ms
  imshow(window_name, image);
  cv2QImage(image);
  waitKey(DELAY);

  /// Now, let's draw some lines
  c = Drawing_Random_Lines(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Go on drawing, this time nice rectangles
  c = Drawing_Random_Rectangles(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Draw some ellipses
  c = Drawing_Random_Ellipses(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Now some polylines
  c = Drawing_Random_Polylines(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Draw filled polygons
  c = Drawing_Random_Filled_Polygons(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Draw circles
  c = Drawing_Random_Circles(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Display text in random positions
  c = Displaying_Random_Text(image, window_name, rng);
  if (c != 0)
    return 0;

  /// Displaying the big end!
  c = Displaying_Big_End(image, window_name, rng);
  if (c != 0)
    return 0;

  waitKey(0);
  return 0;
}

//把opencv的mat转换为QImage
void MainWindow::cv2QImage(Mat img) {
  QImage rookImage = QImage((const uchar *)img.data, img.cols, img.rows,
                            img.step, QImage::Format_RGB888)
                         .rgbSwapped();
  ui->label_img->setPixmap(QPixmap::fromImage(rookImage));
}

MainWindow::~MainWindow() { delete ui; }
