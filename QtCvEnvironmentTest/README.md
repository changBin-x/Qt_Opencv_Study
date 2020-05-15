<!--
 * @Date: 2020-05-03 18:41:28
 * @LastEditTime: 2020-05-08 10:22:44
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
 -->
This project is to test weather opecv is configed successfully with Qt
<<<<<<< HEAD

=======
>>>>>>> dev
<br>
<img src="./test.jpg" alt="test.jpg" align=center>

## <font color=#008000>以下是Latex公式练习</font>
* 数学公式基本语法
1. 上标与下标
   ```
   $$x_1$$
   $$x_1^2$$
   $$x^2_1$$
   $$x^n_{22}$$
   $$x_{22}^{(2)}$$
    ```
    显示效果
    $$x_1$$
    $$x_1^2$$
    $$x^2_1$$
    $$x^n_{22}$$
    $$x_{22}^{(2)}$$
2. 分式
<br>&emsp;&emsp;输入较短的分式时，最简单的方法是使用斜线，譬如输入 (x+y)/2，可得到(x+y)/2 。要输入带有水平分数线的公式，可用命令：\frac{分子}{分母}。</br>
```
$$\frac{x+y}{2}$$
$$\frac{1}{1+\frac{1}{2}}=\frac{2}{3}$$
```
显示效果
$$\frac{x+y}{2}$$
$$\frac{1}{1+\frac{1}{2}}=\frac{2}{3}$$
3. 根式


&emsp;&emsp;排版根式的命令是：开平方：\sqrt{表达式}；开 n 次方：\sqrt[n]{表达式}
```
$$\sqrt{2}<\sqrt[3]{3}$$
$$\sqrt{1+\sqrt[p]{1+a^2}}$$
$$\sqrt{1+\sqrt[^p\!]{1+a^2}}$$
```
显示效果
$$\sqrt{2}<\sqrt[3]{3}$$
$$\sqrt{1+\sqrt[p]{1+a^2}}$$
$$\sqrt{1+\sqrt[^p\!]{1+a^2}}$$
注意：上面第三个示例与第二个示例的区别，有时候 LaTeX 公式需要经过这样的微调会更美观。


4. 求和与积分

&emsp;&emsp;排版求和符号与积分符号的命令分别为 \sum 和 \int，它们通常都有上下限，在排版上就是上标和下标。
```
$$\sum_{k=1}^{n}\frac{1}{k}$$
$\sum_{k=1}^n\frac{1}{k}$
$$\int_a^b f(x)dx$$
$\int_a^b f(x)dx$
```
显示效果
$$\sum_{k=1}^{n}\frac{1}{k}$$
$\sum_{k=1}^n\frac{1}{k}$
$$\int_a^b f(x)dx$$
$\int_a^b f(x)dx$

# QT5如何打包发布exe程序

Notice：教程基于MinGW


1. 把Qt5的MinGW工具添加到系统环境变量之中
   
   ```
   xx\Qt_5.14.2\5.14.2\mingw73_64\bin
   ```
2. 使用QT以release方式运行程序
3. 在运行后的release文件夹中找到xx.exe，可以单独复制到a文件夹
4. 使用powershell(推荐)或cmd进入xx.exe文件夹，并运行
```
windeployqt xx.exe
```

