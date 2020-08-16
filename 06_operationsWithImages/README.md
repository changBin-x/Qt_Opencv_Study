<!--
 * @Date: 2020-08-14 16:52:04
 * @LastEditTime: 2020-08-14 21:29:02
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
-->
# 图像操作
## 前言
从这一节开始，我们将会使用更加纯粹的Qt语句来对图像进行操作，本节主要用到[QLabel](https://doc.qt.io/qt-5/qlabel.html)类的公有槽函数[setPixmap(const QPixmap&)](https://doc.qt.io/qt-5/qlabel.html#pixmap-prop)和[QImage类](https://doc.qt.io/qt-5/qimage.html)来显示图像。
在使用过程中，遇到Qt的相关问题时，最好的解决办法是查找[Qt官方文档](https://doc.qt.io/qt-5/classes.html)

## 输入/输出
### 加载图像
首先，我们要能够在编写的QT程序中弹出选择文件的窗口，并且把文件路径保存在标准字符串中：
```
  QString dlgTitle = "打开图片"; //设置选择图片的窗口的标题
  QString filter = "图片(*png *jpg *bmp)";        //文件过滤器
  QFileDialog::Options dlgOptions;                //对话框选项
  dlgOptions |= QFileDialog::DontUseNativeDialog; //不使用原始对话框，
                                                  //即使用QT的子窗口作为对话框
  QString selectedFilter;
  imgFileName =
      QFileDialog::getOpenFileName(this, dlgTitle, "", filter, &selectedFilter,
                                   dlgOptions); //保存选择的图片路径
  ui->lineEdit_imgFileName->clear();
  ui->lineEdit_imgFileName->setText(imgFileName); //显示图片名字
  std::string imgFileNameStr = imgFileName.toLatin1().data(); //转化为标准字符串
```
其次，加载图片:
```
    img = cv::imread(imgFileNameStr);
  if (img.empty()) {
    ui->lbl_showImg->setText("图片加载失败");
    ui->lbl_showImg->setStyleSheet("color:#7c828e");
  }
```
如果读取的是jpg文件，则默认情况下会创建3通道图像。如果需要灰度图像，请使用：
```
  grayImg = cv::imread(imgFileNameStr, cv::IMREAD_GRAYSCALE);
```

* Note:
    
    文件的格式取决于其内容（前几个字节）。

    要将图像保存到文件：
    ```
    QFileInfo fileInfo = QFileInfo(imgFileName); //获取文件信息
    QString savedImgName = fileInfo.absolutePath() + "/" + fileInfo.baseName() +
                         "-copy." +
                         fileInfo.suffix(); //另存为副本,路径中不能有汉字
    std::string savedImgNameStr =
      savedImgName.toLatin1().data(); // QString转化为标准字符串
    cv::imwrite(savedImgNameStr, img);  //图像另存
    ```

* Note:

    文件的格式由其扩展名决定。
    使用[cv::imdecode](https://docs.opencv.org/4.3.0/d4/da8/group__imgcodecs.html#ga26a67788faa58ade337f8d28ba0eb19e)和[cv::imencode](https://docs.opencv.org/4.3.0/d4/da8/group__imgcodecs.html#ga461f9ac09887e47797a54567df3b8b63)从内存而不是从文件读取/写入图像。

## 图像的基本操作

### 访问像素强度值

为了获得像素强度值，必须知道图像的类型和通道数。这是一个单通道灰度图像（类型8UC1）以及像素坐标x和y的示例：

```
Scalar intensity = img.at<uchar>(y, x);
```
仅限于C ++版本：strength.val [0]包含从0到255的值。请注意x和y的顺序。由于在OpenCV中，图像由与矩阵相同的结构表示，因此在两种情况下我们都使用相同的约定-首先从0开始的行索引（或y坐标），然后从0开始的列索引（或x坐标）它。或者，您可以使用以下表示法（仅C ++）：
```
Scalar intensity = img.at<uchar>(Point(x, y));
```
现在，让我们考虑一个具有BGR颜色顺序的3通道图像（imread返回的默认格式）：
```
            Vec3b intensity = img.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
```

可以使用相同的方法来更改像素强度：
```
 img.at<uchar>(y, x) = 128;
```

OpenCV中有一些功能，尤其是来自calib3d模块的功能，例如[cv::projectPoints](https://docs.opencv.org/4.3.0/d9/d0c/group__calib3d.html#ga1019495a2c8d1743ed5cc23fa0daff8c)，它们采用Mat形式的2D或3D点数组。矩阵仅包含一列，每一行对应一个点，矩阵类型应对应为32FC2或32FC3。这样的矩阵可以很容易地从std::vector构造（仅C ++）：
```
            vector<Point2f> points;
            //... 填充数组
            Mat pointsMat = Mat(points);
```
可以使用相同的Mat :: at方法（仅C ++）访问此矩阵中的点：
```
 Point2f point = pointsMat.at<Point2f>(i, 0);
```

### 内存管理和引用计数

Mat是一种保留矩阵/图像特征（行和列数，数据类型等）和数据指针的结构。因此，我们可以得到与对应Mat的相同数据的实例。Mat保留一个引用计数，该参考计数指示在销毁Mat的特定实例时是否必须重新分配数据。这是在不复制数据的情况下创建两个矩阵的示例（仅C ++）：
```
        std::vector<Point3f> points;
        // .. 填充数组
        Mat pointsMat = Mat(points).reshape(1);
```

结果，我们得到一个3列的32FC1矩阵，而不是一个1列的32FC3矩阵。pointsMat使用来自点的数据，销毁后不会取消分配内存。但是，开发人员必须确保点的生存期长于pointsMat。如果我们需要复制数据，可以使用例如[cv::Mat::copyTo](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77)或[cv::Mat::clone](https://docs.opencv.org/4.3.0/d3/d63/classcv_1_1Mat.html#a33fd5d125b4c302b0c9aa86980791a77)来完成：

```
        Mat img = imread("image.jpg");
        Mat img1 = img.clone();
```

可以为每个函数提供一个空的输出Mat。每个实现都为目标矩阵调用Mat::create。如果矩阵为空，则此方法为矩阵分配数据。如果它不是空的并且具有正确的大小和类型，则该方法不执行任何操作。但是，如果大小或类型与输入参数不同，则数据将被释放（并丢失）并分配新数据。例如：
```
        Mat img = imread("image.jpg");//其实可以理解为源矩阵
        Mat sobelx;//其实可以理解为目标矩阵
        Sobel(img, sobelx, CV_32F, 1, 0);
```

### 原始操作
在矩阵上定义了许多方便的运算符。例如，这是我们如何从现有的灰度图像img制作黑色图像的方法：
```
 img = Scalar(0);
```
选择感兴趣的区域：
```
            Rect r(10, 10, 100, 100);
            Mat smallImg = img(r);
```
从彩色到灰度的转换：
```
        Mat img = imread("image.jpg"); // 加载一个8UC3图像
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
```
将映像类型从8UC1更改为32FC1：
```
src.convertTo(dst, CV_32F);
```
### 可视化图像
在开发过程中查看算法的中间结果非常有用。OpenCV提供了一种可视化图像的便捷方法。可以使用以下方式显示8U图像：
```
        Mat img = imread("image.jpg");
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", img);
        waitKey();
```
Qt中在界面显示图像的常用便捷方法如下:
```
 //重设图像大小为显示框的大小
  cv::Size dsize =
      cv::Size(ui->lbl_showImg->width(), ui->lbl_showImg->height());
  cv::Mat img1;
  cv::resize(img, img1, dsize);

  cv::Size dsizeGray =
      cv::Size(ui->lbl_showGrayImg->width(), ui->lbl_showGrayImg->height());
  cv::Mat grayImg1;
  cv::resize(grayImg, grayImg1, dsizeGray);

  // Mat类图像是按照BGR顺序存储的图像，而QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像顺序存储的，
  //在类型转换前需要将通道更改。
  cv::Mat rgbImg;
  cv::cvtColor(img1, rgbImg, cv::COLOR_BGR2RGB);
  QImage image = QImage((const uchar *)rgbImg.data, rgbImg.cols, rgbImg.rows,
                        rgbImg.step, QImage::Format_RGB888);

  cv::Mat gray2rgbImg;
  cv::cvtColor(grayImg1, gray2rgbImg, cv::COLOR_GRAY2RGB);
  QImage grayImage =
      QImage((const uchar *)gray2rgbImg.data, gray2rgbImg.cols,
             gray2rgbImg.rows, rgbImg.step, QImage::Format_RGB888);

  //显示图像
  ui->lbl_showImg->setPixmap(QPixmap::fromImage(image));
  // Bug:此处显示的灰度图像
  ui->lbl_showGrayImg->setPixmap(QPixmap::fromImage(grayImage));
```

调用[waitKey()](https://docs.opencv.org/4.3.0/d7/dfc/group__highgui.html#ga5628525ad33f52eab17feebcfba38bd7)会启动消息传递周期，该消息传递周期等待“图像”窗口中的击键。需要将32F图像转换为8U类型。例如：
```
        Mat img = imread("image.jpg");
        Mat grey;
        cvtColor(img, grey, COLOR_BGR2GRAY);
        Mat sobelx;
        Sobel(grey, sobelx, CV_32F, 1, 0);
        double minVal, maxVal;
        minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
        Mat draw;
        sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", draw);
        waitKey();
```
如果选择在Qt的组件中显示图像，则不需要waitKey()函数。

* 注意
    这里[cv::namedWindow](https://docs.opencv.org/4.3.0/d7/dfc/group__highgui.html#ga5afdf8410934fd099df85c75b2e0888b)是不必要的，因为紧随其后是[cv::imshow](https://docs.opencv.org/4.3.0/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563)。不过，它可以用于更改窗口属性或用于[cv::createTrackbar](https://docs.opencv.org/4.3.0/d7/dfc/group__highgui.html#gaf78d2155d30b728fc413803745b67a9b)