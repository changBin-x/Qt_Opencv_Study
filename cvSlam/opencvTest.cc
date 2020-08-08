/*
 * @Date: 2020-08-05 15:07:16
 * @LastEditTime: 2020-08-05 15:20:43
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
 */
#include "opencv2/opencv.hpp"
using namespace cv;
int main() {
  namedWindow("playMp4", WINDOW_AUTOSIZE);
  VideoCapture cap;
  cap.open(
      "E:\\0Project\\ivis_"
      "test\\software\\PictureDetectDemo\\VideoWarning\\test.mp4");
  Mat frame;
  while (1) {
    cap >> frame;
    if (frame.empty()) break;
    imshow("Examp", frame);
    if (waitKey(33) >= 0) break;
  }
  return 0;
}