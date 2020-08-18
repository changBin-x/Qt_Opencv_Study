<!--
 * @Date: 2020-08-18 19:29:13
 * @LastEditTime: 2020-08-18 21:36:05
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
-->
# 目标

* 如何使用YAML或XML文件将文本条目打印和读取到文件和OpenCV中？
* 同样的情况下怎么保存为OpenCV数据结构？
* 如何针对自定义的数据结构执行此操作？
* OpenCV数据结构的用法，例如[cv::FileStorage](https://docs.opencv.org/4.3.0/da/d56/classcv_1_1FileStorage.html)，[cv::FileNode](https://docs.opencv.org/4.3.0/de/dd9/classcv_1_1FileNode.html)或[cv::FileNodeIterator](https://docs.opencv.org/4.3.0/d7/d4e/classcv_1_1FileNodeIterator.html)。

# 代码说明

在这里，我们仅讨论XML和YAML文件输入。您的输出（及其相应的输入）文件可能仅具有这些扩展名之一，并且扩展名来自此。它们是您可以序列化的两种数据结构：映射（如STL映射和Python字典）和元素序列（如STL矢量）。两者之间的区别在于，在映射中，每个元素都有一个您可以访问的唯一的名称。对于序列，您需要遍历它们以查询特定项目。

1. **XML/YAML文件打开和关闭。**在将任何内容写入此类文件之前，需要先将其打开，最后将其关闭。OpenCV中的XML/YAML数据结构是[ cv::FileStorage](https://docs.opencv.org/4.3.0/da/d56/classcv_1_1FileStorage.html).要指定绑定到硬盘上的结构文件，可以使用其构造函数或以下函数的[open()](https://docs.opencv.org/4.3.0/d6/dee/group__hdf5.html#ga243d7e303690af3c5c3686ca5785205e)函数：
   ```
        FileStorage fs(filename, FileStorage::WRITE);
        // 或者:
        // FileStorage fs;
        // fs.open(filename, FileStorage::WRITE);
   ```
   两种方法的函数的第二个参数都是常量，该常量指定了对文件进行操作的类型：WRITE, READ 或者 APPEND.文件名中指定的扩展名也决定了将使用的输出格式。如果指定扩展名，例如* .xml.gz *，则输出可能被压缩。
   
   当[cv::FileStorage](https://docs.opencv.org/4.3.0/da/d56/classcv_1_1FileStorage.html)对象销毁时，文件自动关闭。但是，您可以使用release函数显式调用此方法：
   ```
   fs.release();                                       // 显式关闭
   ```
2. **文本和数字的输入和输出。**在C ++中，数据结构使用STL库中的<<操作符。在Python中，改用[cv::FileStorage::write()](https://docs.opencv.org/4.3.0/da/d56/classcv_1_1FileStorage.html#a3efd38c576bac8b66281826f0a2642e7)。要输出任何类型的数据结构，我们首先需要指定其名称。我们只需在C ++中将其名称推送到流中即可。在Python中，写函数的第一个参数是名称。对于基本类型，您可以在值后面加上数值:
   ```
   fs << "iterationNr" << 100;
   ```
读入是一个简单的寻址（通过[]运算符）和强制转换操作，或者是通过>>运算符进行读取。在Python中，我们使用getNode()寻址并使用real()： 
    ```
        int itNr;
        //fs["iterationNr"] >> itNr;
        itNr = (int) fs["iterationNr"];
    ```
3. **OpenCV数据结构的输入/输出。**它们与基本的C ++和Python类型完全一样:
   ```
           Mat R = Mat_<uchar>::eye(3, 3),
            T = Mat_<double>::zeros(3, 1);
   ```
   ```
        fs << "R" << R;                                      // cv::Mat
        fs << "T" << T;
   ```
   ```
        fs["R"] >> R;                                      // 读 cv::Mat
        fs["T"] >> T;
   ```
4. **向量（数组）和关联映射的输入/输出。**正如我之前提到的，我们也可以输出映射和序列（数组，向量）。我们首先打印变量的名称，然后我们必须指定输出是序列还是映射。
   
对于第一个元素之前的序列，打印"["字符，最后一个元素之后的字符"]"。使用Python时，“]”字符可以写为序列名称或序列的最后一个元素，具体取决于元素的数量：
```
        fs << "strings" << "[";                              // 文本 - 字符串序列
        fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg";
        fs << "]";                                           // 关闭序列
```

对于映射，操作是相同的，但是现在我们使用“ {”和“}”标识符：

```
        fs << "Mapping";                              // 文本 - 映射
        fs << "{" << "One" << 1;
        fs <<        "Two" << 2 << "}";
```
要读取这些内容，我们使用[cv::FileNode](https://docs.opencv.org/4.3.0/de/dd9/classcv_1_1FileNode.html)和[cv::FileNodeIterator](https://docs.opencv.org/4.3.0/d7/d4e/classcv_1_1FileNodeIterator.html)数据结构。[cv::FileStorage](https://docs.opencv.org/4.3.0/da/d56/classcv_1_1FileStorage.html)类（或Python中的getNode()函数）的[]运算符返回[cv::FileNode](https://docs.opencv.org/4.3.0/de/dd9/classcv_1_1FileNode.html)数据类型。如果节点是顺序的，我们可以使用[cv::FileNodeIterator](https://docs.opencv.org/4.3.0/d7/d4e/classcv_1_1FileNodeIterator.html)来遍历所有项目。在Python中，[at()](https://docs.opencv.org/4.3.0/d5/d50/group__videostab.html#ga64715f89ad837e2b6b5649d0f833172d)函数可用于寻址序列的元素，而size()函数可返回序列的长度：
```
        FileNode n = fs["strings"];                         // R读取字符串序列-获取节点
        if (n.type() != FileNode::SEQ)
        {
            cerr << "strings is not a sequence! FAIL" << endl;
            return 1;
        }
        FileNodeIterator it = n.begin(), it_end = n.end(); // 遍历节点
        for (; it != it_end; ++it)
            cout << (string)*it << endl;
```
对于地图，您可以再次使用[]运算符（Python中的[at()](https://docs.opencv.org/4.3.0/d5/d50/group__videostab.html#ga64715f89ad837e2b6b5649d0f833172d)函数）来访问给定的项（也可以使用>>运算符）：
```
        n = fs["Mapping"];                                // 从序列中读取映射
        cout << "Two  " << (int)(n["Two"]) << "; ";
        cout << "One  " << (int)(n["One"]) << endl << endl;
```
5. 读写自定义的数据结构。假设您有一个数据结构，例如：
   ```
    class MyData
    {
    public:
      MyData() : A(0), X(0), id() {}
    public:   // 数据成员
    int A;
    double X;
    string id;
    };
   ```
   在C ++中，可以通过在类的内部和外部添加读取和写入函数，通过OpenCV I/O XML / YAML接口（与OpenCV数据结构的情况一样）对此序列化。在Python中，您可以通过在类内部实现读写功能来接近此情况。对于类内部：
   ```
       void write(FileStorage& fs) const                        //编写此类的序列
    {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}";
    }
    void read(const FileNode& node)                          //读取此类的序列
    {
        A = (int)node["A"];
        X = (double)node["X"];
        id = (string)node["id"];
    }
   ```
   在C ++中，您需要在类外添加以下函数定义：
   ```
   static void write(FileStorage& fs, const std::string&, const MyData& x)
    {
    x.write(fs);
    }
    static void read(const FileNode& node, MyData& x, const MyData& default_value = MyData()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
    }
   ```
   在这里您可以观察到，在读取部分中，我们定义了如果用户尝试读取不存在的节点会发生什么。在这种情况下，我们只返回默认的初始化值，但是更复杂的解决方案是例如返回对象ID的负一个值。

   添加完这四个函数后，请使用>>运算符进行写入，并使用<<运算符进行读取（或为Python定义的输入/输出函数）：
   ```
   MyData m(1);
   ```
   ```
   fs << "MyData" << m;
   ```
   ```
   fs["MyData"] >> m;  
   ```
   或尝试读取不存在的内容：
   ```
   cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
    fs["NonExisting"] >> m;
    cout << endl << "NonExisting = " << endl << m << endl;
   ```
