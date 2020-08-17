# 离散傅里叶变换
## 目标
我们将针对以下问题寻求答案：
* 什么是傅立叶变换，为什么要使用它？
* 在OpenCV中如何实现？
* 例如这些函数的使用方法:[copyMakeBorder()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga2ac1049c2c3dd25c2b41bffe17658a36) , [merge()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga7d7b4d6c6ee504b30a20b1680029c7b4) , [dft()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#gadd6cf9baf2b8b704a11b5f04aaf4f39d) , [getOptimalDFTSize()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga6577a2e59968936ae02eb2edde5de299) , [log()](https://docs.opencv.org/4.3.0/d7/dcc/group__core__utils__softfloat.html#gae5de78ee278fe88405c6dbc38502f7c1) 和[normalize()](https://docs.opencv.org/4.3.0/dc/d84/group__core__basic.html#ga1b6a396a456c8b6c6e4afd8591560d80) .

## 代码说明
傅立叶变换会将图像分解成其正弦和余弦分量。换句话说，它将图像从空间域转换到频率域。任何函数都可以用无限的正弦和余弦函数之和精确地近似。傅立叶变换是实现精确近似一种方法。数学上，二维图像的傅里叶变换为：
<div align="center">
<img src="https://latex.codecogs.com/gif.latex?F(k,l)&space;=&space;\displaystyle\sum\limits_{i=0}^{N-1}\sum\limits_{j=0}^{N-1}&space;f(i,j)e^{-i2\pi(\frac{ki}{N}&plus;\frac{lj}{N})}" title="F(k,l) = \displaystyle\sum\limits_{i=0}^{N-1}\sum\limits_{j=0}^{N-1} f(i,j)e^{-i2\pi(\frac{ki}{N}+\frac{lj}{N})}" />
<img src="https://latex.codecogs.com/gif.latex?e^{ix}&space;=&space;\cos{x}&space;&plus;&space;i\sin&space;{x}" title="e^{ix} = \cos{x} + i\sin {x}" />
</div>

其中，f是其空间域中的图像值，F是f在频率域中的变换。转换的结果是复数。可以通过*实部*图像和*复部*图像或通过*幅值*和*相位*图像显示转换结果。但是，在整个图像处理算法中，只有*幅值*图像更有意义，因为它包含了我们需要的有关图像几何结构的所有信息。但是，如果您打算用这些形式对图像进行一些修改，然后需要对其进行重新转换，则必须同时保留这两种形式。

在此示例中，我将展示如何计算和显示傅立叶变换的*幅值*图像。图像是数字图像的情况下傅里叶变换是离散的。这意味着像素可能会从给定的域值中获取一个值。例如，在基本灰度图像中，图像值通常在零到255之间。因此，傅立叶变换也必须是离散类型，这称为离散傅立叶变换（DFT）。每当需要从几何角度确定图像的结构时，就需要使用DFT。以下是要执行的步骤（对于灰度输入图像I）：
### 放大图像至最佳尺寸

DFT的性能取决于图像大小。对于数字二、三和五的倍数的图像，它往往是最快的（想一下为什么）。因此，要获得最佳性能，通常最好将边框值填充到图像上以获得具有此类特征的尺寸。[getOptimalDFTSize()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga6577a2e59968936ae02eb2edde5de299)返回此最佳大小，我们可以使用[copyMakeBorder()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#ga2ac1049c2c3dd25c2b41bffe17658a36)函数扩展图像的边框（附加的像素初始化为零）：
```
    Mat padded;                            //将输入图像扩展到最佳尺寸
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // 在边界上添加零值
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
```

### 兼顾复数和实数值

傅立叶变换的结果是复数。这意味着对于每个图像值，结果是两个图像值（实部和复部各分量一个）。而且，频域范围比其对应空间的范围大得多。因此，我们通常至少以*float*格式存储这些内容。因此，我们将输入图像转换为此类型，并使用另一个通道将其扩展以容纳复数值:

```
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // 将零添加到展开的另一个平面
```

### 进行离散傅立叶变换
实时计算（输入与输出相同）：
```
 dft(complexI, complexI);            //这样结果可以适合源矩阵
```

### 将实部和复部的值转换为幅度
复数具有实部（Re）和复部（虚数-Im）。DFT的结果是复数。DFT的幅值为：
<div align="center">
<img src="https://latex.codecogs.com/gif.latex?M&space;=&space;\sqrt[2]{&space;{Re(DFT(I))}^2&space;&plus;&space;{Im(DFT(I))}^2}" title="M = \sqrt[2]{ {Re(DFT(I))}^2 + {Im(DFT(I))}^2}" />
</div>

转换为OpenCV代码:
```
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];
```
### 换算到对数刻度
事实证明，傅立叶系数的动态范围太大，无法在屏幕上显示。有一些小的和一些大的变化值，我们不能以原来的幅值形式观察到。因此，大的值将全部变成白点，而小的值变成黑点。要使用灰度值进行可视化，我们可以将线性比例转换为对数比例：
<div align="center">
<img src="https://latex.codecogs.com/gif.latex?M_1&space;=&space;\log{(1&space;&plus;&space;M)}" title="M_1 = \log{(1 + M)}" />
</div>
转换为OpenCV代码：

```
    magI += Scalar::all(1);                  // 转换为对数刻度
    log(magI, magI);
```
### 裁剪并重新排列

还记得，第一步，我们扩大了图像吗？好了，该放弃新引入的值了。出于可视化目的，我们还可以重新排列结果的象限，以使原点（零，零）与图像中心相对应。

```
    // 如果行或列的数量为奇数,裁剪频谱
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // 重新排列傅立叶图像的象限，以使原点位于图像中心
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    //-在每个象限中创建ROI
    Mat q0(magI, Rect(0, 0, cx, cy));   // 左上
    Mat q1(magI, Rect(cx, 0, cx, cy));  // 右上
    Mat q2(magI, Rect(0, cy, cx, cy));  // 左下方
    Mat q3(magI, Rect(cx, cy, cx, cy)); // 右下
    Mat tmp;                           // 交换象限（左上角-右下角）
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                    // 交换象限（左上-右上）
    q2.copyTo(q1);
    tmp.copyTo(q2);
```

### 归一化

再次进行此操作以实现可视化目的。现在我们有了幅度，但是这仍然超出了我们的图像显示范围（从零到一）。我们使用[cv::normalize()](https://docs.opencv.org/4.3.0/dc/d84/group__core__basic.html#ga1b6a396a456c8b6c6e4afd8591560d80)函数将值标准化到该范围。

```
//这是opencv的官方教程
//将具有浮点值的矩阵转换为可见的图像形式（在0和1之间的浮点数）。
normalize(magI, magI, 0, 1, NORM_MINMAX);
//为了能在Qt中显示，需要进行如下标准化操作
 cv::normalize(magI, magI, 0, 255, cv::NORM_MINMAX, -1);////此处Mat的类型为5，即CV_32F
 magI.convertTo(magI, CV_8U); //再进行一次转换是为了能用QImage显示
```

## 结果

傅里叶变换的应用之一是确定图像中存在的几何方向。例如，让我们找出文本是否水平？查看某些文本，您会发现文本行也以水平线的形式出现，字母则以垂直线的形式出现。在傅立叶变换的情况下，也可以看到文本片段的这两个主要组成部分。让我们使用[水平](./pictures/imageTextN.png)和围绕文本[旋转](./pictures/imageTextR.png)的图像进行观察。
如果是水平文字：
<div align="center">
<img src="./pictures/result_normal.jpg" title="result_normal.jpg" />
</div>

如果文字旋转：
<div align="center">
<img src="./pictures/result_rotated.jpg" title="result_normal.jpg" />
</div>

可以看到，频域中最关键的部分（幅度图像上最亮的点）跟随图像的几何旋转进行旋转。据此，我们可以计算偏移量并执行图像旋转以对未对准的图像进行校正。