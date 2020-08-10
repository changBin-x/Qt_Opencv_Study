/***
 *      "Date": "2020-08-09 20:56:32",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": "Load and Display an Image"
 */
#include <QCoreApplication>
#include <iostream>
//这个库文件基本包含了常用的库
#include <opencv2/opencv.hpp>
// opencv有专用的命名空间，为了不和其它库函数混淆，建议不用这个
// using namespacecv;
//  using namespace std;

int main(int argc, char *argv[]) {

  std::string imagePath = cv::samples::findFile(
      "E:\\computerVision\\OpencvStudy\\Qt_Opencv430_learning\\01_"
      "LoadAndDisplayAnImage\\yljFire.jpg"); //查找图片
  /**
   *cv::imread函数有两个参数：第一个是图片名，第二个是需要的图片的格式，格式有三种
   * (1)IMREAD_UNCHANGED (<0,-1) 以原样加载图像;
   * (2)IMREAD_GRAYSCALE(0)，相当于BGR2GRAY
   * (3)cv::IMREAD_COLOR(>0)参数表示以RGB模式读取图片，
   * 创建一个Mat对象保存加载的图片的数据（矩阵形式保存）
   */
  cv::Mat imgUnchanged = cv::imread(imagePath, cv::IMREAD_UNCHANGED);
  cv::Mat imgGrayScale = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
  cv::Mat imgColor = cv::imread(imagePath, cv::IMREAD_COLOR);

  if (imgColor.empty()) {
    std::cout << "读取图片失败:" << imagePath << std::endl;
  }
  /**
   * @brief 使用cv :: namedWindow函数创建一个OpenCV窗口
   * 创建后，这些窗口将由OpenCV自动管理。为此，需要指定窗口名称以及显示图像窗口的大小。
   * 如果不使用Qt，则WINDOW_AUTOSIZE是唯一受支持的窗口。在这种情况下，窗口大小为图像的原始大小，不允许调整尺寸！
   *可以在Qt上使用WINDOW_NORMAL来允许调整窗口大小。图像将根据当前窗口大小自行调整大小，通过使用|运算符，
   * 还可以指定是否要保持图像的宽高比（WINDOW_KEEPRATIO 或WINDOW_FREERATIO）。
   */
  cv::namedWindow("imgUnchanged", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
  cv::imshow("imgUnchanged",
             imgUnchanged); //在名为"imgUnchanged"的窗口上显示img
                            //  cv::imshow("imgGrayScale", imgGrayScale);
                            //  cv::imshow("imgColor ", imgColor);

  if (cv::waitKey(0) == 's') {
    cv::imwrite("imgUnchanged.jpg", imgUnchanged); //保存图片
    cv::destroyAllWindows();                       //关闭所有窗口
  }
  QCoreApplication a(argc, argv);

  //  return a.exec();
  return 0;
}
