# 如何使用OpenCV parallel_for_to并行化代码

## 目标
本教程的目的是向您展示如何使用OpenCV parallel_for_框架轻松地并行化代码。为了说明这个概念，我们将编写一个程序来绘制Mandelbrot集合，利用几乎所有可用的CPU负载。完整的教程代码在[这里](./main.cpp)。如果您想了解有关多线程的更多信息，由于本教程旨在保持简单性，您将必须参考参考书或课程。

## 前提

第一个前提条件是使用并行框架构建OpenCV。在OpenCV 3.2中，以下并行框架按该顺序可用：
   1.  英特尔线程构建模块（第3方库，应明确启用）
   2.  C=并行C / C ++编程语言扩展（应明确启用3rdparty库）
   3.  OpenMP（集成到编译器，应显式启用）
   4.  APPLE GCD（系统范围，自动使用（仅适用于APPLE））
   5.  Windows RT并发（系统范围，自动使用（仅Windows RT））
   6.  Windows并发（运行时的一部分，自动使用（仅Windows-MSVC ++> = 10））
   7.  Pthreads（如果可用）

如您所见，OpenCV库中可以使用几个并行框架。一些并行库是第三方库，必须在CMake中显式构建和启用（例如TBB，C =），其他并行库会随平台自动提供（例如APPLE GCD），但应该允许您直接或通过启用CMake中的选项访问并行框架，并重建库。

第二个（弱）前提条件更多地与您要完成的任务相关，因为并非所有计算都适用/可以并行运行。为了简单起见，可以将没有内存依赖性（没有可能的竞争条件）的，可以分为多个基本操作的任务轻松并行化。计算机视觉处理通常很容易并行化，因为在大多数情况下，一个像素的处理不依赖于其他像素的状态。

## 简单示例：绘制Mandelbrot集

我们将以绘制Mandelbrot集为例，以说明如何从常规顺序代码中轻松调整代码以并行化计算。

### 理论

数学家Adrien Douady以数学家Benoit Mandelbrot为名定义了Mandelbrot集。在图像处理领域以外，它已经广为人知，因为图像表示是一类分形的一个例子，它是一种数学模型，在每个刻度上都显示出重复的图案（甚至，Mandelbrot集在整个形状上都是自相似的，以不同的比例反复出现）。有关更深入的介绍，您可以查看相应的[Wikipedia文章](https://en.wikipedia.org/wiki/Mandelbrot_set)(建议查看百度百科)。在这里，我们将仅介绍绘制Mandelbrot集的公式（摘自上述Wikipedia文章）。

-------------------------------------------------------
Mandelbrot集是复平面中c的值的集合，在二次平面的迭代过程中0的轨迹仍为复平面。
<div align="center">
<img src="https://latex.codecogs.com/gif.latex?\begin{cases}&space;z_0&space;=&space;0&space;\\&space;z_{n&plus;1}&space;=&space;z_n^2&space;&plus;&space;c&space;\end{cases}" title="\begin{cases} z_0 = 0 \\ z_{n+1} = z_n^2 + c \end{cases}" />
</div>

也就是说，复数c是Mandelbrot集的一部分，如果当从z0=0开始并重复应用迭代时，zn的绝对值仍然是有界的，尽管n大。这也可以表示为
<div align="center">
<img src="https://latex.codecogs.com/gif.latex?\limsup_{n\to\infty}|z_{n&plus;1}|\leqslant2" title="\limsup_{n\to\infty}|z_{n+1}|\leqslant2" />
</div>

----------------------------------------------------------------

### 伪代码

生成Mandelbrot集表示形式的简单算法称为[“逃逸时间算法”](https://en.wikipedia.org/wiki/Mandelbrot_set#Escape_time_algorithm)。对于渲染图像中的每个像素，我们使用递归关系来测试复数是否在最大迭代次数内是否有界。不属于Mandelbrot集的像素将快速逃逸，而我们假定经过固定的最大迭代次数后，该像素才位于集合中。较高的迭代值将生成更详细的图像，但计算时间将相应增加。我们使用“逃逸”以描绘图像中像素值所需的迭代次数。
```
For each pixel (Px, Py) on the screen, do:
{
  x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2, 1))
  y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
  x = 0.0
  y = 0.0
  iteration = 0
  max_iteration = 1000
  while (x*x + y*y < 2*2  AND  iteration < max_iteration) {
    xtemp = x*x - y*y + x0
    y = 2*x*y + y0
    x = xtemp
    iteration = iteration + 1
  }
  color = palette[iteration]
  plot(Px, Py, color)
}
```
为了在伪代码和理论之间建立联系，我们有如下公式：
* <img src="https://latex.codecogs.com/gif.latex?z&space;=&space;x&space;&plus;&space;iy" title="z = x + iy" />
* <img src="https://latex.codecogs.com/gif.latex?z^2&space;=&space;x^2&space;&plus;&space;i2xy&space;-&space;y^2" title="z^2 = x^2 + i2xy - y^2" />
* <img src="https://latex.codecogs.com/gif.latex?c&space;=&space;x_0&space;&plus;&space;iy_0" title="c = x_0 + iy_0" />
  
  <div align="center">
<img src="./picture/how_to_use_OpenCV_parallel_for_640px-Mandelset_hires.png" />
</div>

在此图上，我们看到复数的实部在x轴上，虚部在y轴上。您可以看到，如果我们在特定位置进行缩放，则整个形状可以重复可见。

## 操作

### 逃逸时间算法的实现
```
int mandelbrot(const complex<float> &z0, const int max)
{
    complex<float> z = z0;
    for (int t = 0; t < max; t++)
    {
        if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) return t;
        z = z*z + z0;
    }
    return max;
}
```
在这里，我们使用[std::complex](http://en.cppreference.com/w/cpp/numeric/complex)模板类表示一个复数。此函数执行测试以检查像素是否已设置，并返回“逃逸”迭代。

### 顺序Mandelbrot的实现

```
void sequentialMandelbrot(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            float x0 = j / scaleX + x1;
            float y0 = i / scaleY + y1;
            complex<float> z0(x0, y0);
            uchar value = (uchar) mandelbrotFormula(z0);
            img.ptr<uchar>(i)[j] = value;
        }
    }
}
```

在此步骤中，我们依次遍历渲染图像中的像素以执行测试以检查该像素是否可能属于Mandelbrot集。

另一件事是使用以下方法将像素坐标转换为Mandelbrot集空间：
```
    Mat mandelbrotImg(4800, 5400, CV_8U);
    float x1 = -2.1f, x2 = 0.6f;
    float y1 = -1.2f, y2 = 1.2f;
    float scaleX = mandelbrotImg.cols / (x2 - x1);
    float scaleY = mandelbrotImg.rows / (y2 - y1);
```

最后，要将灰度值分配给像素，我们使用以下方法：
* 如果达到最大迭代次数，则该像素为黑色（假定该像素位于Mandelbrot集中），
* 否则，我们根据转义的迭代次数分配灰度值，并进行缩放以适合灰度范围。

```
int mandelbrotFormula(const complex<float> &z0, const int maxIter=500) {
    int value = mandelbrot(z0, maxIter);
    if(maxIter - value == 0)
    {
        return 0;
    }
    return cvRound(sqrt(value / (float) maxIter) * 255);
}
```

使用线性比例变换不足以看出灰度变化。为了解决这个问题，我们将通过使用平方根标度转换（参考自Jeremy D. Frens在他的[博客文章](http://www.programming-during-recess.net/2016/06/26/color-schemes-for-mandelbrot-sets/)）来增强感知能力：<img src="https://latex.codecogs.com/gif.latex?f&space;\left(&space;x&space;\right)&space;=&space;\sqrt{\frac{x}{\text{maxIter}}}&space;\times&space;255" title="f \left( x \right) = \sqrt{\frac{x}{\text{maxIter}}} \times 255" />

<div align="center">
<img src="./picture/how_to_use_OpenCV_parallel_for_sqrt_scale_transformation.png" />
</div>

绿色曲线对应一个简单的线性比例转换，蓝色曲线对应一个平方根比例转换，您可以观察它们的斜率如何提高最低值。

### 并行Mandelbrot实现

查看顺序实现时，我们可以注意到每个像素都是独立计算的。为了优化计算，我们可以利用现代处理器的多核架构并行执行多个像素计算。为了轻松实现这一点，我们将使用OpenCV [cv::parallel_for_](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#gaa42ec9937b847cb52a97c613fc894c4a)框架。
```
class ParallelMandelbrot : public ParallelLoopBody
{
public:
    ParallelMandelbrot (Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
        : m_img(img), m_x1(x1), m_y1(y1), m_scaleX(scaleX), m_scaleY(scaleY)
    {
    }
    virtual void operator ()(const Range& range) const CV_OVERRIDE
    {
        for (int r = range.start; r < range.end; r++)
        {
            int i = r / m_img.cols;
            int j = r % m_img.cols;
            float x0 = j / m_scaleX + m_x1;
            float y0 = i / m_scaleY + m_y1;
            complex<float> z0(x0, y0);
            uchar value = (uchar) mandelbrotFormula(z0);
            m_img.ptr<uchar>(i)[j] = value;
        }
    }
    ParallelMandelbrot& operator=(const ParallelMandelbrot &) {
        return *this;
    };
private:
    Mat &m_img;
    float m_x1;
    float m_y1;
    float m_scaleX;
    float m_scaleY;
};
```

第一件事是声明一个自定义类，该类继承自[cv::ParallelLoopBody](https://docs.opencv.org/4.3.0/d2/d74/classcv_1_1ParallelLoopBody.html)并重写虚拟void operator（）（const cv :: Range＆range）const。

operator（）中的作用范围代表将由单个线程处理的像素子集。该拆分自动完成以平均分配计算负载。我们必须将像素索引坐标转换为2D [row，col]坐标。还要注意，我们必须在Mat图像上保留一个参考，以便能够就地修改图像。

并行执行通过以下方式调用：
```
    ParallelMandelbrot parallelMandelbrot(mandelbrotImg, x1, y1, scaleX, scaleY);
    parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), parallelMandelbrot);
```

此处，范围表示要执行的操作总数，因此表示图像中的像素总数。要设置线程数，可以使用：[cv::setNumThreads](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#gae78625c3c2aa9e0b83ed31b73c6549c0)。您还可以使用[cv::parallel_for_](https://docs.opencv.org/4.3.0/db/de0/group__core__utils.html#gaa42ec9937b847cb52a97c613fc894c4a)中的nstripes参数指定拆分次数。例如，如果您的处理器有4个线程，则设置cv :: setNumThreads（2）或设置nstripes = 2应该与默认情况下的设置相同，它将使用所有可用的处理器线程，但只会将工作负载分配到两个线程上。

-------------------------------------
Note

C ++ 11标准允许通过简化ParallelMandelbrot类并将其替换为lambda表达式来简化并行实现：
```
    parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), [&](const Range& range){
        for (int r = range.start; r < range.end; r++)
        {
            int i = r / mandelbrotImg.cols;
            int j = r % mandelbrotImg.cols;
            float x0 = j / scaleX + x1;
            float y0 = i / scaleY + y1;
            complex<float> z0(x0, y0);
            uchar value = (uchar) mandelbrotFormula(z0);
            mandelbrotImg.ptr<uchar>(i)[j] = value;
        }
    });
```

--------------------------------------

### 结果

并行实现的性能取决于您拥有的CPU类型。例如，在4核/ 8线程CPU上，您可以期望将速度提高6.9倍左右。有很多因素可以解释为什么我们无法实现近8倍的加速。主要原因有：

* 创建和管理线程的开销，
* 后台进程并行运行，
* 4个硬件内核之间的差异，每个内核有2个逻辑线程，而8个硬件内核。

教程代码生成的结果图像（可以修改代码以使用更多迭代，并根据转义的迭代并使用调色板分配像素颜色，以使用更美观的图像）：

<div align="center">
<img src="./picture/Mandelbrot_parallel.png" />
</div>