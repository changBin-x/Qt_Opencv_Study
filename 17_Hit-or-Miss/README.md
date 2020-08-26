# Hit or Miss 击中击不中变换

## 目标

在本教程中，您将学习如何使用Hit-or-Miss变换（也称为Hit-and-Miss变换）在二进制映像中查找给定的配置或模式。此转换也是更高级的形态学操作（例如插入或修剪）的基础。

我们将使用OpenCV函数[morphologyEx()](https://docs.opencv.org/4.3.0/d4/d86/group__imgproc__filter.html#ga67493776e3ad1a3df63883829375201f)。

## 击中击不中理论

形态运算符根据其形状处理图像。这些运算符将一个或多个结构元素应用于输入图像以获得输出图像。两种基本的形态学运算是侵蚀和扩张。这两个操作的组合会生成高级形态转换，例如打开，关闭或礼帽式转换。要了解有关这些以及其他基本形态学操作的更多信息，请参阅以前的教程（[腐蚀和膨胀](./../15_erodingDilating)）和（[更多形态学转换](./../16_MoreMorphologyTransformations/)）。

按位或按位转换对查找二进制图像中的图案很有用。特别地，它找到其邻域与第一结构元件<a href="https://www.codecogs.com/eqnedit.php?latex=B_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_1" title="B_1" /></a>的形状匹配而同时不与第二结构元件<a href="https://www.codecogs.com/eqnedit.php?latex=B_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_2" title="B_2" /></a>的形状匹配的那些像素。从数学上讲，应用于图像<a href="https://www.codecogs.com/eqnedit.php?latex=A" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A" title="A" /></a>的运算可以表示为：

<div align="center">
<a href="https://www.codecogs.com/eqnedit.php?latex=A\circledast&space;B&space;=&space;(A\ominus&space;B_1)&space;\cap&space;(A^c\ominus&space;B_2)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A\circledast&space;B&space;=&space;(A\ominus&space;B_1)&space;\cap&space;(A^c\ominus&space;B_2)" title="A\circledast B = (A\ominus B_1) \cap (A^c\ominus B_2)" /></a>
</div>

因此，击中击不中操作包括三个步骤：

1. 使用结构元素<a href="https://www.codecogs.com/eqnedit.php?latex=B_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_1" title="B_1" /></a>腐蚀图像<a href="https://www.codecogs.com/eqnedit.php?latex=A" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A" title="A" />。
2. 用结构元素<a href="https://www.codecogs.com/eqnedit.php?latex=B_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_2" title="B_2" /></a>腐蚀图像<a href="https://www.codecogs.com/eqnedit.php?latex=A" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A" title="A" />（<a href="https://www.codecogs.com/eqnedit.php?latex=A^c" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A^c" title="A^c" /></a>）的补。
3. 步骤1和步骤2的结果取与。

结构元素<a href="https://www.codecogs.com/eqnedit.php?latex=B_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_1" title="B_1" /></a>和<a href="https://www.codecogs.com/eqnedit.php?latex=B_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?B_2" title="B_2" /></a>可以组合为单个元素BB。让我们来看一个例子：

<div align="center">
<img src="./pictures/hitmiss_kernels.png">
结构元素（内核）。左：内核“命中”。中：内核为“未命中”。右：最终组合内核
</div>

在这种情况下，我们正在寻找一种模式，其中中心像素属于背景，而北，南，东和西像素属于前景。邻域中的其余像素可以是任何一种，我们不关心这些。现在，让我们将此内核应用于输入图像：

<div align="center">
<img src="./pictures/hitmiss_input.png">
输入的二进制图
</div>

<div align="center">
<img src="./pictures/hitmiss_output.png">
输出的二进制图
</div>

您可以看到仅在图像中的一个位置找到了图案。