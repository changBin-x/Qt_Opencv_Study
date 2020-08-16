# [Mat-基础的图像容器](https://docs.opencv.org/4.3.0/d6/d6d/tutorial_mat_the_basic_image_container.html)


## 目标

从现实世界中获取数字图像有多种方法：数码相机，扫描仪，计算机断层扫描和磁共振成像等等。
<br>在每种情况下，人类看到的都是图像。但是，将其转换为数字设备时，记录的是图像每个点的数值。</br>


获取和存储像素值的方法可能会根据需求而有所不同，但最终，计算机中的所有图像都可能被简化为数值矩阵和描述矩阵本身的其他信息。
<br>OpenCV是一个计算机视觉库，其主要重点是处理和操纵此信息。因此，需要熟悉的第一件事是OpenCV如何存储和处理图像。
</br>

## Mat


OpenCV自2001年以来一直存在。那时，库是围绕C接口构建的，为了将图像存储在内存中，他们使用了称为IplImage的C结构。在大多数较旧的教程和教学资料中都会看到的内容。问题在于，它带有了所有C语言的缺点。最大的问题是手动内存管理。
<br>它基于以下假设：用户负责处理内存分配和释放。尽管对于较小的程序这不是问题，但是一旦代码库增长，处理所有这些问题将变得更加困难，而不是专注于解决开发目标。</br>


幸运的是，C++出现了，并引入了类的概念，从而通过（或多或少的）自动内存管理使用户更轻松。好消息是C++与C完全兼容，因此进行更改不会引起兼容性问题。因此，OpenCV 2.0引入了一个新的C ++接口，该接口提供了一种新的工作方式，这意味着用户无需费心处理内存管理，从而使代码简洁（写的少但是能获得更多功能）。C ++接口的主要缺点是目前许多嵌入式开发系统仅支持C。因此，除非您以嵌入式平台为目标，否则没有必要使用旧方法（除非你是受虐狂程序员并且您正在自讨苦吃）。


需要了解Mat的第一件事是，不再需要手动分配其内存并在不需要时立即释放它。尽管仍然可以这样做，但是大多数OpenCV函数都会自动分配其输出数据。如果传递一个已经存在的Mat对象，该对象已经为矩阵分配了所需的空间，那么它将被重用。换句话说，我们始终仅使用执行任务所需的内存。


Mat基本上是一类，具有两个数据部分：矩阵头（包含诸如矩阵大小，用于存储的方法，用于存储矩阵的地址之类的信息，等等）和指向包含像素值的矩阵的指针（根据选择的存储方法采用任何尺寸）。矩阵头部空间的大小是恒定的，但是矩阵本身的大小可能因图像而异，通常会增加几个数量级。


OpenCV是图像处理库。它包含大量图像处理功能。为了解决计算难题，大多数情况下，您最终将使用库的多个功能。因此，将图像传递给函数是一种常见的做法。我们不要忘记我们正在谈论图像处理算法，该算法往往需要大量的计算。我们要做的最重要的事是通过减少对较大图像的不必要的复制来进一步提升程序运算速度。


为了解决此问题，OpenCV使用参考计数系统。虽然每个Mat对象都有其自己的头部，但是可以通过使两个Mat对象的矩阵指针指向同一地址来共享一个矩阵。此外，复制运算符只会将**头部**和**指针**复制到大型矩阵，而不是数据本身。

```
Mat A, C;                          // 只创建头部
A = imread(argv[1], IMREAD_COLOR); //（分配矩阵）
Mat B(A);                                 // 使用复制构造的方法
C = A;                                    // 赋值运算
```


最后，所有上述对象都指向同一个数据矩阵A，使用其中任何一个方法修改A也会影响所有其他对象。实际上，不同的对象仅提供对相同基础数据A的不同访问方法。但是，它们的头部部分是不同的。可以创建仅引用完整数据的一部分的头部。例如，要在图像中创建关注区域（ROI），只需创建具有新边界的新标题即可：


```
Mat D (A, Rect(10, 10, 100, 100) ); // 使用矩形
Mat E = A(Range::all(), Range(1,3)); // 使用行和列边界
```

矩阵本身是否可能属于多个Mat对象，这些对象将在不再需要矩阵时负责清理矩阵。简短的答案是：使用它的最后一个对象。这是通过使用引用计数机制来处理的。每当有人复制Mat对象的标题时，矩阵的计数器就会增加。每当清理标题时，此计数器都会减少。当计数器达到零时，矩阵被释放。有时您也需要复制矩阵本身，因此OpenCV提供了[cv :: Mat :: clone()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#adff2ea98da45eae0833e73582dd4a660)和[cv :: Mat :: copyTo()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77)函数。

```
Mat F = A.clone();
Mat G;
A.copyTo(G);
```
现在修改F或G不会影响A的标题所指向的矩阵。需要记住的是:


*  OpenCV函数输出的图像是自动分配空间的（除非另有说明）；
*  使用C ++接口的OpenCV无需考虑进行内存管理；
*  赋值运算符和复制构造方法仅复制标头;
*  可以使用[cv :: Mat :: clone()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#adff2ea98da45eae0833e73582dd4a660)和[cv :: Mat :: copyTo()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77)函数复制图像的基础矩阵。

## 存储方法


这是关于如何存储像素值的。您可以选择色彩空间和使用的数据类型。颜色空间是指我们如何组合颜色成分以编码给定颜色。最简单的一种是灰度，其中我们可以使用的颜色是黑色和白色。这些的组合使我们可以创建许多灰色阴影。


对于存储多种色彩的图片，有更多的方法可供选择。每种方法都将其分解为三个或四个基本组成部分，我们可以使用它们的组合来创建其他组成部分。最受欢迎的是RGB，主要是因为这也是我们的眼睛如何建立颜色的方式。它的基色是红色，绿色和蓝色。为了编码颜色的透明度，有时会添加第四个元素：alpha（A）。


但是，还有许多其他颜色系统各有各的优点：

* RGB是最常见的颜色，因为我们的眼睛使用类似的颜色，但是请记住，OpenCV标准显示系统使用BGR颜色空间来组合颜色（**红色和蓝色通道已互换位置**）。
* HSV和HLS将颜色分解为它们的色相，饱和度和值/亮度分量，这是我们描述颜色的更自然的方式。例如，您可能会忽略最后一个分量，从而使算法对输入图像的光照条件不太敏感。
* 流行的JPEG图像格式使用YCrCb。
* CIE L * a * b *是感知上统一的颜色空间，如果您需要测量给定颜色与另一种颜色之间的距离，它会派上用场。
  

每个构建组件都有其自己的有效域，这决定使用的数据类型。我们如何存储组件定义了我们对其组件域的控制。可能的最小数据类型是char，表示一个字节或8位。这可以是无符号的（因此可以存储从0到255的值）或有符号的（从-127到+127的值）。尽管在三个分量的情况下，这已经给出了1600万种可能的颜色来表示（例如在RGB情况下），我们仍可以通过使用float（4字节= 32位）或double（8字节= 64位）数据来获得更好的控制每个组件的类型。不过，请记住，增加组件的大小也会增加内存中整个图片的大小。

## 显式创建Mat对象

在[“加载，修改和保存图像”](../02_LoadModifySaveAnImage/main.cpp)教程中，您已经学习了如何使用cv :: imwrite（）函数将矩阵写入图像文件。但是，出于调试目的，查看实际值要方便得多。您可以使用Mat的<<操作符执行此操作。请注意，这仅适用于二维矩阵。

尽管Mat确实可以很好地用作图像容器，但它也是通用的矩阵类。因此，可以创建和操纵多维矩阵。您可以通过多种方式创建Mat对象：
* [cv :: Mat :: Mat](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#af1d014cecd1510cdf580bf2ed7e5aafc)构造函数
  ```
    Mat M(2,2, CV_8UC3, Scalar(0,0,255));
    cout << "M = " << endl << " " << M << endl << endl;
  ```
     对于二维和多通道图像，我们首先定义其大小：计算的行数和列数。
     <br>然后，我们需要指定用于存储元素的数据类型以及每个矩阵点的通道数。为此，我们根据以下约定构造了多个定义：</br>
     ```
     CV_[每个项目的位数][有无符号][类型前缀]C[通道数]
     ```
     例如，CV_8UC3表示我们使用8位长的无符号字符类型，每个像素都由其中的三个来形成三个通道。预定义了最多四个通道的类型。[cv :: Scalar](https://docs.opencv.org/4.3.0/dc/d84/group__core__basic.html#ga599fe92e910c027be274233eccad7beb)是四元素短向量。指定它，您可以使用自定义值初始化所有矩阵点。如果需要更多内容，可以使用上方的宏创建类型，在括号中设置通道号，如下所示。
* 使用C / C ++数组并通过构造函数进行初始化
    ```
    int sz[3] = {2,2,2};
    Mat L(3,sz, CV_8UC(1), Scalar::all(0));
    ```

    上面的示例显示了如何创建一个二维以上的矩阵。指定其尺寸，然后传递一个包含每个尺寸大小的指针，其余的保持不变。
* [cv :: Mat :: create](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a55ced2c8d844d683ea9a725c60037ad0)函数：
    ```
      M.create(4,4, CV_8UC(2));
      cout << "M = "<< endl << " "  << M << endl << endl;
    ```
    您不能使用此构造函数初始化矩阵值。如果新的大小不适合旧的大小，它将仅重新分配其矩阵数据存储器。
* MATLAB样式初始值设定项：[cv :: Mat :: zeros](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a0b57b6a326c8876d944d188a46e0f556)，[cv :: Mat :: ones](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a69ae0402d116fc9c71908d8508dc2f09)，[cv :: Mat :: eye](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a2cf9b9acde7a9852542bbc20ef851ed2)。指定要使用的大小和数据类型：
  ```
    Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;
    Mat O = Mat::ones(2, 2, CV_32F);
    cout << "O = " << endl << " " << O << endl << endl;
    Mat Z = Mat::zeros(3,3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl << endl;
  ```
* 对于小型矩阵，可以使用逗号分隔的初始值设定项或初始值设定项列表（在最后一种情况下需要C ++ 11支持）：
  ```
      Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;
    C = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
    cout << "C = " << endl << " " << C << endl << endl;
  ```
* 为现有的Mat对象和[cv :: Mat :: clone](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#adff2ea98da45eae0833e73582dd4a660)或[cv :: Mat :: copyTo](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77)创建新的头部
  ```
    Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;
  ```
    * 注意：
        <br>可以使用[cv :: randu()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga1ba1026dca0807b27057ba6a49d258c0)函数用随机值填充矩阵，需要为随机值指定一个上限和下限：</br>
        ```
            Mat R = Mat(3, 2, CV_8UC3);
            randu(R, Scalar::all(0), Scalar::all(255));
        ```
## 格式化输出
在上面的示例中，您可以看到默认的格式设置选项。但是，OpenCV允许格式化矩阵输出：

* 默认：
  ```
  cout << "R (default) = " << endl << R << endl << endl;
  ```
* python格式：
  ```
   cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;
  ```
* 逗号分隔值（CSV）：
  ```
  cout << "R (csv)     = " << endl << format(R, Formatter::FMT_CSV   ) << endl << endl;
  ```
* Numpy格式：
  ```
   cout << "R (numpy)   = " << endl << format(R, Formatter::FMT_NUMPY ) << endl << endl;
  ```
* C格式
  ```
  cout << "R (c) = " << endl << format(R, Formatter::FMT_C ) << endl << endl;
  ```
## 其他数据结构的输出
OpenCV也通过<<运算符支持其他常见OpenCV数据结构的输出：
* 2D Point:
  ```
    Point2f P(5, 1);
    cout << "Point (2D) = " << P << endl << endl;
  ```
* 3D Point
  ```
    Point3f P3f(2, 6, 7);
    cout << "Point (3D) = " << P3f << endl << endl;
  ```
* 通过cv::Mat输出std::Vector
  ```
    vector<float> v;
    v.push_back( (float)CV_PI);   v.push_back(2);    v.push_back(3.01f);
    cout << "Vector of floats via Mat = " << Mat(v) << endl << endl;
  ```
* 点的std::vector
  ```
      vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i)
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
    cout << "A vector of 2D Points = " << vPoints << endl << endl;
  ```

可以在[这里](./main.cpp)找到全部的例程,其来源于[官方例程](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/core/mat_the_basic_image_container/mat_the_basic_image_container.cpp)