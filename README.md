<!--
 * @Date: 2020-08-08 12:03:40
 * @LastEditTime: 2020-08-26 20:07:13
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
-->
# 本项目的目的
用于学习opencv在Qt界面中的操作。

我发现网上关于opencv4.0(C++)以上版本的中文文档非常少，关于如何在Qt中使用opencv4.0+的文档几乎没有，所以我就把自己学习的过程放在了这里。

很多人在一开始编译适用于Qt的opencv源码的时候就被难倒，并且选择了放弃，这里我有一份自己编译好的[OpenCV4.3.0源码](./opencv430ForQtBuild_win64/)，直接下载即可使用;

本项目使用Qt5.14.2版本。

以下的学习记录是以官方的opencv4.3.0(C++)[英文文档](https://docs.opencv.org/4.3.0/de/d7a/tutorial_table_of_content_core.html)为主，我在整理成中文的过程采用机翻+人工校准的方式，由于本人水平有限，所以难免会有错误，欢迎大家一起交流学习。

在本项目中可以了解到：
* Qt5的入门使用方法；
* opencv4.0+的入门使用方法；
* Qt5和opencv的联合开发方法；


# 内容

## [00_检测OpenCV是否在Qt中配置正确](./00_QtCvEnvironmentTest/)

## [OpenCV概述](https://docs.opencv.org/4.3.0/df/d65/tutorial_table_of_content_introduction.html)
### [01_加载并显示图像](./01_LoadAndDisplayAnImage/)
### [02_加载/修改/保存图像](./02_LoadModifySaveAnImage/)
01,02文件夹里面没有详细的README，因为比较简单，所以我把注解都放在代码之中

## [核心功能](https://docs.opencv.org/4.3.0/de/d7a/tutorial_table_of_content_core.html)
### [03_基础的图像容器Mat](./03_BasicImageContainerMat/)
### [04_扫描图像的方法](./04_scanImages/)
### [05_矩阵掩码操作](./05_MaskOperationsOnMatrices/)
### [06_图像操作](./06_operationsWithImages/)
从这一部分开始，我们将会使用更加纯粹的Qt语句来对图像进行操作
### [07_两图片线性合成](./07_addTwoImages/)
### [08_更改图像的对比度和亮度](./08_ChangeContrastAndBrightnessOfAnImage/)
### [09_傅里叶变换](./09_DiscreteFourierTransform/)
### [10_使用XML和YAML文件的文件输入和输出](./10_FileInputOutputUsingXMLAndYAML/)
### [11_如何使用OpenCV parallel_for_to并行化代码](./11_how_to_use_OpenCV_parallel_for_/)

## [图像处理（imgproc模块）](https://docs.opencv.org/4.3.0/d7/da8/tutorial_table_of_content_imgproc.html)
### [12_基础绘图](12_BasicDrawing/)
### [13_opencv中的随机数生成器和文本生成器](./13_RandomGeneratorAndText/)
### [14_图像平滑(模糊)操作](./14_smoothImages)
### [15_图像的腐蚀和膨胀操作](./15_erodingDilating/)
### [16_更多图形变换操作]
### [17_击中击不中变换](./17_Hit-or-Miss/)

# Last
如果觉得本项目对您有所帮助，点一下star吧。

如果您愿意，打赏一杯咖啡可好？:pray:

<div align="center">
<img style="align: center" src="beg.jpg" width="40%" height="40%" alt="" />
<div align=center>跪着要饭:joy: </div>
</div>
