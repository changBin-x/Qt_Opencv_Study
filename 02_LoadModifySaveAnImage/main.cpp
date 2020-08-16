#include <iostream>
#include <opencv2/opencv.hpp>

// using namespace std;

int main() {
  std::string imageName = "../yljFire.jpg";
  //以BGR格式读入图片
  cv::Mat image = cv::imread(imageName);
  if (image.empty())
    std::cout << "加载图片失败" << std::endl;
  cv::Mat grayImage;

  //把BGR图像转换为灰度图格式
  cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
  cv::imwrite("../grayImage.jpg", grayImage); //保存图片
  cv::namedWindow("YLJ", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
  cv::imshow("YLJ", image);
  cv::namedWindow("grayImage", cv::WINDOW_NORMAL | cv::WINDOW_FREERATIO);
  cv::imshow("grayImage", grayImage);
  cv::waitKey(0); //按0结束显示
  return 0;
}
