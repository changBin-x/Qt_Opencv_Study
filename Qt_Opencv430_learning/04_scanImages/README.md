# [如何使用OpenCV扫描图像？查寻表和测量时间](https://docs.opencv.org/4.3.0/db/da5/tutorial_how_to_scan_images.html)

## 目标
针对以下问题寻求答案：
* 如何遍历图像的每个像素？
* OpenCV矩阵值如何存储？
* 如何衡量算法的性能？
* 什么是查询表，为什么要使用它们？
## 测试案例
让我们考虑一种简单的减色方法。通过使用C和C++中无符号char类型矩阵项存储像素，像素通道最多可以具有256个不同的值。对于三通道图像，这可能会导致形成太多的颜色（精确到1600万）。使用如此多的色调可能会严重降低我们的算法性能。然而，有时仅使用这些颜色值的极小一部分就足以获得相同的最终结果。

在这种情况下，通常会减少色彩空间。这意味着我们将色彩空间当前值除以新的输入值，最终得到更少的色彩。例如，零与九之间的每个值取新值零，十与十九之间的每个值取十，依此类推。

当把uchar（无符号char-aka值，介于0和255之间）值除以int值时，结果也将为char。这些值只能是char值。因此，任何分数值都将进行四舍五入。利用这一点，可以将uchar域中的上层操作表示为：
$$I_{new}=(\frac{I_{old}}{10})*10$$

一种简单的色彩空间缩小算法即是遍历一个图像矩阵中的每一个像素值并对像素值引用上面的公式。值得注意的是，我们进行除法和乘法运算，这些操作对于系统来说是昂贵的。如果可能的话，值得使用更简单的操作来避免消耗系统资源，例如一些减法，加法或最好是简单的赋值。此外，请注意，上层操作只有有限数量的输入值。在uchar体系中，最大值256。

因此，对于较大的图像，明智的做法是事先计算所有可能的值，并且在分配过程中，只需使用查找表进行分配即可。查找表是简单的数组（具有一个或多个维度），对于给定的输入值，该表保留最终的输出值。它的优势在于我们不需要进行计算，只需要读取结果即可。

我们的测试用例程序（以及下面的代码示例）将执行以下操作：读取作为命令行参数（可以是彩色或灰度）传递的图像，并使用给定的命令行参数整数值应用缩小值。在OpenCV中，目前有三种主要方法逐像素处理图像。为了使事情变得更有趣，我们将使用这些方法中的每一种对图像进行扫描，并打印出花费的时间。

您可以在[此处](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/core/how_to_scan_images/how_to_scan_images.cpp)下载完整的源代码，也可以在核心部分的cpp教程代码的OpenCV的示例目录中查找它。

最后一个参数是可选的。如果给定图像将以灰度格式加载，否则将使用BGR颜色空间。第一件事是计算查找表。

```
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }
    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));
```

在这里，我们首先使用C ++ stringstream类将第三个命令行参数从文本转换为整数格式。然后，我们使用简单的形式和上面的公式来计算查找表。这里没有OpenCV库里的特定函数或数据。

如何衡量时间？，OpenCV提供了两个简单的函数来实现[cv :: getTickCount()](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#gae73f58000611a1af25dd36d496bf4487)和[cv :: getTickFrequency()](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#ga705441a9ef01f47acdc55d87fbe5090c)。第一个返回特定事件（例如自引导系统以来）以来系统CPU的时钟脉冲数。秒数表示CPU在秒内发出脉冲的次数。因此，测量两次操作之间经过的时间很容易：
```
double t = (double)getTickCount();
// do something ...
t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t << endl;
```

## 图像矩阵如何存储在内存中？

正如您已经在[《 Mat-基础图像容器》](../03_BasicImageContainerMat)教程中阅读的那样，矩阵的大小取决于所使用的颜色系统.更准确地说，这取决于使用的通道数。如果是灰度图像，有以下内容：

<img style="display: block; margin: 0 auto;" src="./pictures/tutorial_how_matrix_stored_1.png" alt="" />



对于多通道图像，列包含的子列与通道数一样多。例如，对于BGR色彩系统：

<img style="display: block; margin: 0 auto;" src="./pictures/tutorial_how_matrix_stored_2.png" alt="" />


请注意，通道的顺序是相反的：BGR而不是RGB。因为在许多情况下，内存足够大，可以以连续的方式存储行，所以这些行可以一个接一个地跟随，从而创建单个长行。因为所有内容都在一个接一个的位置，这可能有助于加快扫描过程。我们可以使用[cv :: Mat :: isContinuous()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#aa90cea495029c7d1ee0a41361ccecdf3)函数询问矩阵是否是这种情况。继续进行下一节查找示例。


## 高效的方法

在性能方面，C风格operator []（指针）访问最高效。因此，我们推荐的**最有效**的分配方法是：
```
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;
    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}
```

在这里，我们基本上只是获得一个指向每一行开始的指针，并一直进行到结束为止。在特殊情况下，矩阵是以连续方式存储的，我们只需要一次请求指针，然后一直到最后。对于彩色图像，我们需要注意：彩色图像有三个通道，因此我们需要在每行中遍历三倍以上的元素。

还有另一种方式。Mat对象的data数据成员将指针返回到第一行第一列。如果此指针为null，则在该对象中没有有效输入。这是检查图像加载是否成功的最简单方法。如果存储是连续的，我们可以使用这种方式来遍历整个数据指针。如果是灰度图像，则如下所示：
```
uchar* p = I.data;
for( unsigned int i = 0; i < ncol*nrows; ++i)
    *p++ = table[*p];
```
两种方式得到的结果相同。但是，此代码以后很难阅读。后续更新维护程序也更困难。此外，在实践中，这两种方法的性能相同（因为大多数现代编译器可能会自动为您提供这种小的优化技巧）。所以，推荐使用第一种方法。

## 迭代器方法（安全）
在采取上述的有效方法的情况下，需要确保遍历了正确数量的uchar字段，还需要确保能够跳过行与行之间可能出现的坑（这是什么坑？不太明白）。迭代器方法被认为是一种更安全的方法，因为它从用户那里接管了这些任务。

您需要做的就是查询图像矩阵的开始和结尾，然后增加Begin迭代器，直到到达end。要获取迭代器指向的值，请使用*运算符（在其前面添加）。
```
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }
    return I;
}
```

对于彩色图像，每列有三个uchar类型，这可以视为uchar类型的短向量，该短向量在OpenCV中可以使用\<Vec3b>表示。

## 参考返回值，即时计算地址

不建议使用最终方法扫描图像。它可以获取或修改图像中的随机元素。它的基本用法是指定要访问的项目的行和列号。在之前的扫描方法中，查看图像的类型很重要。使用这种方法需要手动指定在自动查找中使用的类型。对于以下源代码（+ [cv :: Mat :: at()](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#aa5d20fc86d41d59e4d71ae93daee9726)函数的用法），可以在灰度图像的情况下观察到这一点：
```
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3:
        {
         Mat_<Vec3b> _I = I;
         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }
    return I;
}
```
该函数使用输入类型进行坐标计算，并计算出查询项目的地址，然后返回对该地址的引用。获得该值时，其可以是一个常数，而在设置该值时，它可以是非常数。**仅作为调试模式**下的安全步骤中，*检查输入的坐标是否有效并确实存在。如果不是这种情况，在错误的标准输出流上也能得到很好的输出消息。与释放模式（指的是其它方法的指针可以即时释放）下的有效方式相比，使用此方式的唯一区别是，对于图像的每个元素，都获得一个新的行指针，并使用新的行指针获取我们使用C运算符[]获取列元素的内容。

如果使用此方法对图像进行多次查找，则为每个访问输入类型和at关键字麻烦并且很耗时。为了解决此问题，OpenCV具有[cv :: Mat_](https://docs.opencv.org/4.3.0/df/dfc/classcv_1_1Mat__.html)数据类型。它与Mat相同，但需要在定义时通过查看数据矩阵的方式指定数据类型，可以使用operator（）快速访问项目。cv :: Mat_定义方法可以使数据很容易在常用的的cv :: Mat数据类型之间转换。在之前彩色图像示例中，您可以查看此功能的用法。但是，必须注意，使用cv :: Mat :: at函数可以完成相同的操作（而且具有相同的运行速度）。对于懒人来说，[cv :: Mat :: at](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#aa5d20fc86d41d59e4d71ae93daee9726)方法需要写的代码要少得多。