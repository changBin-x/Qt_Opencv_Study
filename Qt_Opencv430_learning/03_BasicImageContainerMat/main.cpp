/*
 * @Date: 2020-08-10 09:58:19
 * @LastEditTime: 2020-08-10 15:12:44
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: 演示opencv中的基础图像容器:Mat
 */
#include <iostream>
#include <opencv2/core/hal/interface.h>
#include <opencv2/opencv.hpp>
using namespace std;

void help() {
  cout << "\n------------------------------------------------------------------"
          "---------"
       << endl
       << "This program shows how to create matrices(cv::Mat) in OpenCV and "
          "its serial"
       << " out capabilities" << endl
       << "That is, cv::Mat M(...); M.create and cout << M. " << endl
       << "Shows how output can be formatted to OpenCV, python, numpy, csv and "
          "C styles."
       << endl
       << "--------------------------------------------------------------------"
          "---------"
       << endl
       << endl;
}

int main() {
  help();
  cv::Mat M(2, 2, CV_8UC3, cv::Scalar(0, 0, 255)); //使用构造函数创建矩阵
  cout << "M=" << endl << " " << M << endl << endl;

  //使用create()函数创建矩阵
  M.create(4, 4, CV_8UC(2));
  cout << "M=" << endl << " " << M << endl << endl;

  //创建多维矩阵，不能通过<<运算符打印
  int sz[3] = {2, 2, 2};
  cv::Mat L(3, sz, CV_8UC(1), cv::Scalar::all(0));

  //创建MATLAB格式的单位矩阵、全1矩阵、零矩阵
  cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
  cout << "E=" << endl << " " << E << endl << endl;
  cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
  cout << "O=" << endl << " " << O << endl << endl;
  cv::Mat Z = cv::Mat::zeros(3, 3, CV_8UC1);
  cout << "Z=" << endl << " " << Z << endl << endl;

  //创建一个3x3双精度单位矩阵
  cv::Mat C = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  cout << "C=" << endl << " " << C << endl << endl;
  //用initializer_list方法创建一个3x3双精度单位矩阵
#ifdef CV_CXX11
  C = (cv::Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, -0})).reshape(3);
  cout << "C=" << endl << " " << C << endl << endl;
#endif

  //! clone
  cv::Mat rowClone = C.row(1).clone();
  cout << "rowClone=" << endl << " " << rowClone << endl << endl;
  //! clone

  //使用随机数填充矩阵
  //! random
  cv::Mat R = cv::Mat(3, 2, CV_8UC3);
  cv::randu(R, cv::Scalar::all(0), cv::Scalar::all(255));
  //! random

  //演示输出格式选项
  //![默认输出格式]
  cout << "R(default)=" << endl << " " << R << endl << endl;
  //![默认输出格式]
  //![python输出格式]
  cout << "R(python)=" << endl
       << cv::format(R, cv::Formatter::FMT_PYTHON) << endl
       << endl;
  //![python输出格式]
  //! [numpy输出格式]
  cout << "R(numpy)" << endl
       << cv::format(R, cv::Formatter::FMT_NUMPY) << endl
       << endl;
  //! [numpy输出格式]
  //! [csv输出格式]
  cout << "R(csv)" << endl
       << cv::format(R, cv::Formatter::FMT_CSV) << endl
       << endl;
  //! [csv输出格式]
  //! [matlab输出格式]
  cout << "R(matlab)" << endl
       << cv::format(R, cv::Formatter::FMT_MATLAB) << endl
       << endl;
  //! [matlab输出格式]
  //!  [c输出格式]
  cout << "R(c)" << endl << cv::format(R, cv::Formatter::FMT_C) << endl << endl;
  //! [c输出格式]

  //! [输出point2]
  cv::Point2f P(5, 1);
  cout << "Point(2D)=" << P << endl << endl;
  //! [输出point2]

  //! [输出point3]
  cv::Point3f P3f(2, 6, 7);
  cout << "Point(3D)=" << P3f << endl << endl;
  //! [输出point2]

  //![输出vector形式]
  vector<float> v;
  v.push_back((float)CV_PI);
  v.push_back(2);
  v.push_back(3.01f);
  cout << "vector of floats via Mat=" << cv::Mat(v) << endl << endl;
  //! [输出vector形式]

  //!  [输出vector-points形式]
  vector<cv::Point2f> vPoints(20);
  for (size_t i = 0; i < vPoints.size(); ++i) {
    vPoints[i] = cv::Point2f((float)(i * 5), (float)(i % 7));
  }
  cout << "A vector of 2D Points=" << vPoints << endl << endl;
  //! [输出vector-points形式]
  return 0;
}
