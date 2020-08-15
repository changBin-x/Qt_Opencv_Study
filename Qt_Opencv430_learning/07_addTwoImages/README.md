<!--
 * @Date: 2020-08-15 13:45:33
 * @LastEditTime: 2020-08-15 15:02:40
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
-->
# 使用OpenCV添加（混合,合成）两个图像
## 目标
在本教程中，您将学习：
* 什么是线性混合以及为什么有用？
* 如何使用[addWeighted()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#gafafb2513349db3bcff51f54ee5592a19)添加两个图像？
* 如何在Qt中使用QGraphicsView中显示图像？

## 理论

* Note:
  
    以下说明属于Richard Szeliski撰写的《计算机视觉：算法和应用》一书

从我们之前的教程中，我们已经了解了一些Pixel运算符。线性混合运算符是一个有趣的二元（双输入）运算符：
$$g(x) = (1 - \alpha)f_{0}(x) + \alpha f_{1}(x)$$

通过在0→1内改变α，该运算符可用于在两个图像或视频之间进行时间交叉混合，如幻灯片显示和电影制作（很酷，对吗？）

## 说明

由于我们要执行：

$$g(x) = (1 - \alpha)f_{0}(x) + \alpha f_{1}(x)$$


我们需要两个源图像$f_{0}(x)$和$f_{1}(x)$。因此，我们以常见的方式加载它们：
```
   src1 = imread( samples::findFile("LinuxLogo.jpg") );//这里的路径可能和自己的不一致
   src2 = imread( samples::findFile("WindowsLogo.jpg") );
```
然后，为了显示完整的图像，我们需要把图像大小调整为适合graphicsView_img组件的尺寸;
```
  //重设图像大小为显示框的大小
  cv::Size dsize1 = cv::Size(ui->graphicsView_img1->width() - 8,
                             ui->graphicsView_img1->height() - 6);
  cv::Mat tempImg1;
  cv::resize(img1, tempImg1, dsize1);
```
接着，我们使用新的方法调整加载的opencv的图像的通道:
```
  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换时需要rgbSwapped()将通道更改。
  QImage image1 = QImage((const uchar *)tempImg1.data, tempImg1.cols,
                         tempImg1.rows, QImage::Format_RGB888)
                      .rgbSwapped();
```
接着，新建画布，并且加入图像:
```
  QGraphicsScene *scene = new QGraphicsScene;
  scene->addPixmap(QPixmap::fromImage(image1));
```
然后我们就可以显示图像了：
```
ui->graphicsView_img1->setScene(scene);
```

* Warning

    两个线性混合的图像src1和src2都必须具有相同的大小（宽度和高度）和类型。

现在我们需要生成$g(x)$图像，使用功能[addWeighted()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#gafafb2513349db3bcff51f54ee5592a19)非常方便：
```
   beta = ( 1.0 - alpha );
   addWeighted( src1, alpha, src2, beta, 0.0, dst);
```
因为[addWeighted()](https://docs.opencv.org/4.3.0/d2/de8/group__core__array.html#gafafb2513349db3bcff51f54ee5592a19)的原理为：

$$dst = \alpha \cdot src1 + \beta \cdot src2 + \gamma$$

在这里，$\gamma$在上面的代码中被设为0.0。

创建窗口，显示图像，然后等待用户结束程序。

## 结果

<div align="center">
<img style="align: center" src="结果.gif" width="50%" height="50%" alt="" />
  </div>