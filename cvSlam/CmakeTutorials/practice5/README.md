<!--
 * @Date: 2020-05-20 11:28:41
 * @LastEditTime: 2020-05-20 14:11:53
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
--> 
# 复杂的例子：模块的使用和自定义模块
本章我们将着重介绍系统预定义的 Find 模块的使用以及自己编写**Find**模块，


系统中提供了其他各种模块，一般情况需要使用 INCLUDE 指令显式的调用，FIND_PACKAGE 指令是一个特例，可以直接调用预定义的模块。


其实使用纯粹依靠 cmake 本身提供的基本指令来管理工程是一件非常复杂的事情，所以，cmake 设计成了可扩展的架构，可以通过编写一些通用的模块来扩展 cmake.


在本章，我们准备首先介绍一下 cmake 提供的 FindCURL 模块的使用。然后，基于我们前面的 libhello 共享库，编写一个 FindHello.cmake 模块