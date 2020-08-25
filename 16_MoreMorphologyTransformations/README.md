
# 更多图像形态转换操作

## 目标

使用OpenCV函数[cv::morphologyEx](https://docs.opencv.org/4.3.0/d4/d86/group__imgproc__filter.html#ga67493776e3ad1a3df63883829375201f)进行形态转换，例如：
* 图像开操作
* 图像闭操作
* 形态梯度
* 高顶礼帽(叫礼帽更好一点)
* 黑帽

## 理论

--------------------------------------------------

Note

下面的理论来自Bradski和Kaehler的《 Learning OpenCV》一书。

---------------------------------------------------

在上一教程中，我们介绍了两个基本的形态学操作：

* 膨胀
* 腐蚀

基于这两个，我们可以对图像进行更复杂的转换。在这里，我们简要讨论OpenCV提供的5种操作：

### 图像开操作

* 它是通过腐蚀图像然后进行扩张而获得的。

<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=dst&space;=&space;open(&space;src,&space;element)&space;=&space;dilate(&space;erode(&space;src,&space;element&space;)&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?dst&space;=&space;open(&space;src,&space;element)&space;=&space;dilate(&space;erode(&space;src,&space;element&space;)&space;)" title="dst = open( src, element) = dilate( erode( src, element ) )" /></a>
</div>

* 对于**删除小物体**很有用（假设物体在黑暗的前景中很亮）
* 例如，查看下面的示例。应用打开变换后，左图为原始图像，右图为结果。我们可以观察到小点消失了。

<div align="center">
<img src="./pictures/Morphology_2_Tutorial_Theory_Opening.png">
</div>

### 图像闭操作

* 它是通过对图像进行扩张然后进行腐蚀而获得的。

<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=dst&space;=&space;close(&space;src,&space;element&space;)&space;=&space;erode(&space;dilate(&space;src,&space;element&space;)&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?dst&space;=&space;close(&space;src,&space;element&space;)&space;=&space;erode(&space;dilate(&space;src,&space;element&space;)&space;)" title="dst = close( src, element ) = erode( dilate( src, element ) )" /></a>
</div>

* 用于去除小孔（深色区域）。

<div align="center">
<img src="./pictures/Morphology_2_Tutorial_Theory_Closing.png">
</div>

### 形态梯度

* 这是图像的扩张与侵蚀之间的差异。
<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=dst&space;=&space;morph_{grad}(&space;src,&space;element&space;)&space;=&space;dilate(&space;src,&space;element&space;)&space;-&space;erode(&space;src,&space;element&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?dst&space;=&space;morph_{grad}(&space;src,&space;element&space;)&space;=&space;dilate(&space;src,&space;element&space;)&space;-&space;erode(&space;src,&space;element&space;)" title="dst = morph_{grad}( src, element ) = dilate( src, element ) - erode( src, element )" /></a>
</div>

* 如以下所示，这对于查找对象的**轮廓**很有用：
  
<div align="center">
<img src="./pictures/Morphology_2_Tutorial_Theory_Gradient.png">
</div>

### 高顶礼帽

* 它是输入图像与其打开操作之间的差。

<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=dst&space;=&space;tophat(&space;src,&space;element&space;)&space;=&space;src&space;-&space;open(&space;src,&space;element&space;)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?dst&space;=&space;tophat(&space;src,&space;element&space;)&space;=&space;src&space;-&space;open(&space;src,&space;element&space;)" title="dst = tophat( src, element ) = src - open( src, element )" /></a>
</div>

<div align="center">
<img src="./pictures/Morphology_2_Tutorial_Theory_TopHat.png">
</div>

### 黑帽

* 它是图像闭操作和输入图像之间的差

<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=dst&space;=&space;blackhat(&space;src,&space;element&space;)&space;=&space;close(&space;src,&space;element&space;)&space;-&space;src" target="_blank"><img src="https://latex.codecogs.com/gif.latex?dst&space;=&space;blackhat(&space;src,&space;element&space;)&space;=&space;close(&space;src,&space;element&space;)&space;-&space;src" title="dst = blackhat( src, element ) = close( src, element ) - src" /></a>
</div>

## 代码说明

1. 让我们看一下C ++程序的一般结构：

* 载入图片

```
 src = cv::imread("../../opencv430ForQtBuild_win64/data/baboon.jpg",
                   cv::IMREAD_COLOR);
```
* 创建一个窗口和函数以显示形态运算的结果

```
void MainWindow::showImage(cv::Mat img) {
  QImage Image = QImage((const uchar *)img.data, img.cols, img.rows, img.step,
                        QImage::Format_RGB888)
                     .rgbSwapped();
  ui->label_image->setPixmap(QPixmap::fromImage(Image));
}
```

* 每次我们移动任何滑块时，都会调用用户函数Morphology_Operations来执行新的形态学操作，并且它将基于当前轨迹栏值更新输出图像。

```
void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  //因为MORPH_X:2,3,4,5,6
  cv::Mat dst;
  int operation = ui->comboBox_operator->currentIndex() + 2;
  cv::Mat element = cv::getStructuringElement(
      cv::MORPH_ELLIPSE, cv::Size(2 * position + 1, 2 * position + 1),
      cv::Point(position, position));
  cv::morphologyEx(src, dst, operation, element);
  showImage(dst);
}
```

我们可以观察到执行形态转换的关键功能是cv :: morphologyEx。在此示例中，我们使用四个参数（将其余参数保留为默认值）：
  * src：源（输入）图像
  * dst：输出图像
  * operation：要执行的形态转换。请注意，我们有5种选择：
    * Opening: MORPH_OPEN : 2
    * Closing: MORPH_CLOSE: 3
    * Gradient: MORPH_GRADIENT: 4
    * Top Hat: MORPH_TOPHAT: 5
    * Black Hat: MORPH_BLACKHAT: 
    * element：要使用的内核。我们使用函数[cv::getStructuringElement](https://docs.opencv.org/4.3.0/d4/d86/group__imgproc__filter.html#gac342a1bb6eabf6f55c803b09268e36dc)定义我们自己的结构。

## 结果

<div align="center">
<img src="./pictures/result.gif">
</div>