/***
 *      "Date": "2020-08-10 18:50:33",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": "如何扫描图像"
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>

using namespace std;

cv::Mat &ScanImageAndReduceC(cv::Mat &I, const uchar *table);
cv::Mat &ScanImageAndReduceIterator(cv::Mat &I, const uchar *table);
cv::Mat &ScanImageAndReduceRandomAccess(cv::Mat &I, const uchar *table);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "参数不足" << endl;
    return -1;
  }

  cv::Mat I, J;
  if (argc == 4 && !strcmp(argv[3], "G"))
    I = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  else
    I = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (I.empty()) {
    cout << "图片" << argv[1] << "无法被加载" << endl;
    return -1;
  }
  //![按比例缩小像素值]
  int divideWith = 0;
  stringstream s; //把输入的字符串转换为数字
  s << argv[2];
  s >> divideWith;
  if (!s || !divideWith) {
    cout << "输入的数字无效" << endl;
    return -1;
  }
  uchar table[256];
  for (int i = 0; i < 256; ++i) {
    table[i] = (uchar)(divideWith * (i / divideWith));
  }
  //! [按比例缩小像素值]
  const int times = 100;
  double t;
  t = (double)cv::getTickCount();
  for (int i = 0; i < times; ++i) {
    cv::Mat clone_i = I.clone();
    J = ScanImageAndReduceC(clone_i, table);
  }
  t = 1000 * ((double)cv::getTickCount() - t) / cv::getTickFrequency();
  t /= times;
  cout << "用C运算符[]减少的(平均运行)时间 : " << times << t << " ms." << endl;
  //![查找表初始化]
  cv::Mat lookUpTable(1, 256, CV_8U);
  uchar *p = lookUpTable.ptr();
  for (int i = 0; i < 256; ++i)
    p[i] = table[i];
  //![查找表初始化]
  t = (double)cv::getTickCount();

  for (int i = 0; i < times; ++i) {
    //![使用查找表]
    cv::LUT(I, lookUpTable, J);
    //! [使用查找表]
  }
  t = 1000 * ((double)cv::getTickCount() - t) / cv::getTickFrequency();
  t /= times;
  cout << "用LTU函数减少的(平均运行)时间 : " << times << t << " ms." << endl;
  return 0;
}

/**
 * @brief C风格operator []（指针）扫描图像
 * @param I
 * @param table
 * @return
 */
cv::Mat &ScanImageAndReduceC(cv::Mat &I, const uchar *table) {
  //只接受char类型的矩阵
  CV_Assert(I.depth() == CV_8U);
  int channels = I.channels();
  int nRows = I.rows;            //高，行
  int nCols = I.cols * channels; //宽，列
  if (I.isContinuous()) {
    nCols *= nRows;
    nRows = 1;
  }
  int i, j;
  uchar *p;
  for (i = 0; i < nRows; ++i) {
    p = I.ptr<uchar>(i);
    for (j = 0; j < nCols; ++j) {
      p[j] = table[p[j]];
    }
  }
  return I;
}

/**
 * @brief 扫描图像并且减少迭代次数
 * @param I
 * @param table
 * @return
 */
cv::Mat &ScanImageAndReduceIterator(cv::Mat &I, const uchar *const table) {
  // accept only char type matrices
  CV_Assert(I.depth() == CV_8U);

  const int channels = I.channels();
  switch (channels) {
  case 1: {
    cv::MatIterator_<uchar> it, end;
    for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
      *it = table[*it];
    break;
  }
  case 3: {
    cv::MatIterator_<cv::Vec3b> it, end;
    for (it = I.begin<cv::Vec3b>(), end = I.end<cv::Vec3b>(); it != end; ++it) {
      (*it)[0] = table[(*it)[0]];
      (*it)[1] = table[(*it)[1]];
      (*it)[2] = table[(*it)[2]];
    }
  }
  }

  return I;
}

/**
 * @brief 扫描图像并减少随机访问
 * @param I
 * @param table
 * @return
 */
cv::Mat &ScanImageAndReduceRandomAccess(cv::Mat &I, const uchar *const table) {
  // accept only char type matrices
  CV_Assert(I.depth() == CV_8U);

  const int channels = I.channels();
  switch (channels) {
  case 1: {
    for (int i = 0; i < I.rows; ++i)
      for (int j = 0; j < I.cols; ++j)
        I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
    break;
  }
  case 3: {
    cv::Mat_<cv::Vec3b> _I = I;

    for (int i = 0; i < I.rows; ++i)
      for (int j = 0; j < I.cols; ++j) {
        _I(i, j)[0] = table[_I(i, j)[0]];
        _I(i, j)[1] = table[_I(i, j)[1]];
        _I(i, j)[2] = table[_I(i, j)[2]];
      }
    I = _I;
    break;
  }
  }

  return I;
}
