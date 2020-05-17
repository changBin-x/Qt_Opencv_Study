/*
 * @Date: 2020-05-14 20:59:43
 * @LastEditTime: 2020-05-15 18:00:49
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description:测试eigen和 opencv环境
 */

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main() {
  // Mat A;
  int row = 3;
  int col = 4;
  Mat A(row, col, CV_8UC1, Scalar(0));
  cout << "test Matrix=\n" << A << endl;
  Mat img = imread("D:\\opencv\\examples\\cvSlam\\ylj.jpg");
  imshow("image", img);
  waitKey(0);
  return 0;
}