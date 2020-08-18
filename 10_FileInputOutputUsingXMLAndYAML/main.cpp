/***
 *      "Date": "2020-8-18 20:15:25",
 *      "LastEditTime": "",
 *      "Author": " Chang_Bin",
 *      "LastEditors": "Chang_Bin",
 *      "Email": "bin_chang@qq.com",
 *      "Description": "使用XML和YAML文件的文件输入和输出"
 */

#include <QCoreApplication>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <string>

class MyData {
public:
  MyData() : A(0), X(0), id() {}
  explicit MyData(int)
      : A(97), X(CV_PI), id("mydata1234") // 显式声明以避免隐式转换
  {}
  void write(cv::FileStorage &fs) const //编写此类的序列
  {
    fs << "{"
       << "A" << A << "X" << X << "id" << id << "}";
  }
  void read(const cv::FileNode &node) // 读取此类的序列
  {
    A = (int)node["A"];
    X = (double)node["X"];
    id = (std::string)node["id"];
  }

public: // 数据成员
  int A;
  double X;
  std::string id;
};

//必须定义这些写和读函数，才能使FileStorage中的序列工作
static void write(cv::FileStorage &fs, const std::string &, const MyData &x) {
  x.write(fs);
}
static void read(const cv::FileNode &node, MyData &x,
                 const MyData &default_value = MyData()) {
  if (node.empty())
    x = default_value;
  else
    x.read(node);
}

// 此函数会将我们的自定义类打印到控制台,运算符重载
static std::ostream &operator<<(std::ostream &out, const MyData &m) {
  out << "{ id = " << m.id << ", ";
  out << "X = " << m.X << ", ";
  out << "A = " << m.A << "}";
  return out;
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  std::string filename = "../outputfile.yaml";
  { // 写
    cv::Mat R = cv::Mat_<uchar>::eye(3, 3), T = cv::Mat_<double>::zeros(3, 1);

    //! [自定义IO输入]
    MyData m(1);
    //! [自定义IO输入]

    //! [打开]
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    // 或者:
    // cv::FileStorage fs;
    // fs.open(filename, cv::FileStorage::WRITE);
    //! [打开]

    //! [写入数字]
    fs << "iterationNr" << 100;
    //! [写入数字]
    //! [写入字符串]
    fs << "strings"
       << "["; // text - string sequence
    fs << "image1.jpg"
       << "Awesomeness"
       << "../../opencv430ForQtBuild_win64/data/baboon.jpg";
    fs << "]"; // 关闭序列
    //! [写入字符串]

    //! [写入映射]
    fs << "Mapping"; // 文本映射
    fs << "{"
       << "One" << 1;
    fs << "Two" << 2 << "}";
    //! [写入映射]

    fs << "R" << R; // cv::Mat
    fs << "T" << T;

    //! [自定义IO写入]
    fs << "MyData" << m; // your own data structures
    //! [自定义IO写入w]

    //! [关闭文件]
    fs.release(); // explicit close
    //!  [关闭文件]
    std::cout << "Write Done." << std::endl;
  }
  filename = "..\\outputfile.xml";
  { // 读
    std::cout << std::endl << "Reading: " << std::endl;
    cv::FileStorage fs;
    fs.open(filename, cv::FileStorage::READ);

    //! [读数字]
    int itNr;
    // fs["iterationNr"] >> itNr;
    itNr = (int)fs["iterationNr"];
    //! [读数字]
    std::cout << itNr;
    if (!fs.isOpened()) {
      std::cerr << "Failed to open " << filename << std::endl;
      return 1;
    }

    //! [读字符串]
    cv::FileNode n = fs["strings"]; // Read string sequence - Get node
    if (n.type() != cv::FileNode::SEQ) {
      std::cerr << "strings is not a sequence! FAIL" << std::endl;
      return 1;
    }

    cv::FileNodeIterator it = n.begin(),
                         it_end = n.end(); // Go through the node
    for (; it != it_end; ++it)
      std::cout << (std::string)*it << std::endl;
    //! [读字符串]

    //! [读映射]
    n = fs["Mapping"]; // Read mappings from a sequence
    std::cout << "Two  " << (int)(n["Two"]) << "; ";
    std::cout << "One  " << (int)(n["One"]) << std::endl << std::endl;
    //! [读映射]

    MyData m;
    cv::Mat R, T;

    //! [输入输出Mat]
    fs["R"] >> R; // 读 cv::Mat
    fs["T"] >> T;
    //! [输入输出Mat]
    //! [自定义IO]
    fs["MyData"] >> m; // 读取自定义结构体
    //! [自定义IO]

    std::cout << std::endl << "R = " << R << std::endl;
    std::cout << "T = " << T << std::endl << std::endl;
    std::cout << "MyData = " << std::endl << m << std::endl << std::endl;

    //显示节点不存在的默认行为
    //! [节点不存在]
    std::cout
        << "Attempt to read NonExisting (should initialize the data structure "
           "with its default).";
    fs["NonExisting"] >> m;
    std::cout << std::endl << "NonExisting = " << std::endl << m << std::endl;
    //! [节点不存在]
  }

  std::cout << std::endl
            << "Tip: Open up " << filename
            << " with a text editor to see the serialized data." << std::endl;
  return 0;
}
