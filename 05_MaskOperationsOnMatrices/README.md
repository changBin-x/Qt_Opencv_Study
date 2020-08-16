# 对矩阵进行Mask(蒙版,掩码)运算
对矩阵进行掩码操作非常简单。这个方法是，根据Mask矩阵（也称为内核）重新计算图像中每个像素的值。此Mask保留的值将调整相邻像素（和当前像素）对新像素值的影响程度。从数学的角度来看，我们对图片使用指定的值进行加权平均。

## 测试案例

思考一下图像对比度增强方法的问题。基本上，我们希望对图像的每个像素应用以下公式：

<img style="align: center" src="./pictures/formula.png" alt="" />

第一种表示法是使用公式，而第二种表示法是使用掩码。第二种方法是第一种表示法的精简版本。通过将mask矩阵的中心（用零零索引表示的大写形式）放在要计算的像素上，然后对像素值乘以重叠的矩阵值求和，即可使用mask。在矩阵较大的情况下，后一种表示法更容易查找。

## 代码
您可以从[此处](https://raw.githubusercontent.com/opencv/opencv/master/samples/cpp/tutorial_code/core/mat_mask_operations/mat_mask_operations.cpp)下载此源代码，也可以在以下位置查看OpenCV源代码库示例目录：
$$samples/cpp/tutorial_code/core/mat_mask_operations/mat_mask_operations.cpp.$$

## 基本方法

现在让我们看看如何通过使用遍历基本像素的方法或通过使用[filter2D()](https://docs.opencv.org/4.3.0/d5/df1/group__imgproc__hal__functions.html#ga42c2468ab3a1238fbf48458c57169081)函数来实现mask操作。

执行此操作的函数如下：
```
void Sharpen(const Mat& myImage,Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);
        uchar* output = Result.ptr<uchar>(j);
        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}
```

首先，确保输入图像数据为无符号字符(unsigned char)格式。为此，我们使用[cv::CV_Assert](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#gaf62bcd90f70e275191ab95136d85906b)函数，当其中的表达式为false时将引发错误。
```
CV_Assert(myImage.depth() == CV_8U);  // 只接受uchar图片参数
```

该函数创建与输入具有相同大小和类型的输出图像。如在[存储图像](../04_scanImages/)部分中所示，根据通道的数量，矩阵可能会有一个或多个子列。

通过指针遍历图像通道，因此图像元素的总数取决于通道数目。
```
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
```

使用普通的C[]运算符来访问像素。因为我们需要同时访问多个行，所以我们将获取每个行的指针（上一行，当前一行和下一行）。 我们需要另一个指向将要保存计算的位置的指针。然后，只需使用[]运算符访问正确的项目。为了使输出指针向前移动，我们只需在每次操作后增加输出指针的值（一个字节）即可：
```
    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);
        uchar* output = Result.ptr<uchar>(j);
        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
```

在图像的边界上，上面的上方的符号会表示不存在像素位置（如-1 - -1）。在这些点处，公式是不确定的。一个简单的解决方案是不在这些点上应用内核，例如，将边界上的像素设置为零：
```
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
```

## filter2D函数

应用此类过滤器(filters,滤波器)在图像处理中非常普遍，以至于OpenCV中有一个函数将负责应用mask（在某些地方也称为内核）。为此，您首先需要定义一个保存掩码的对象：

```
    Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);
```
然后调用[filter2D()](https://docs.opencv.org/4.3.0/d5/df1/group__imgproc__hal__functions.html#ga42c2468ab3a1238fbf48458c57169081)函数，以指定要使用的输入，输出图像和内核：
```
filter2D( src, dst1, src.depth(), kernel );
```

该函数甚至还有第五个可选参数来指定内核的中心;在将滤镜像素存储到K中之前，第六个参数向滤波后的像素添加一个可选值;第七个参数用于确定未定义操作的区域中的操作（边界）。

此函数更短，更简单，并且由于进行了一些优化，因此通常比手动编码方法要快。例如，在我的测试中，第二个仅花费13毫秒，而第一个花费31毫秒。耗时大有不同。