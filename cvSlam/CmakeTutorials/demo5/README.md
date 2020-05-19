<!--
 * @Date: 2020-05-19 14:03:51
 * @LastEditTime: 2020-05-19 14:04:52
 * @Author:  Chang_Bin
 * @LastEditors: Chang_Bin
 * @Email: bin_chang@qq.com
 * @Description: In User Settings Edit
--> 
# Demo5

CMake 也可以指定安装规则，以及添加测试。


这两个功能分别可以通过在产生 Makefile 后使用 make install 和 make test 来执行。

在以前的 GNU Makefile 里，你可能需要为此编写 install 和 test 两个伪目标和相应的规则，

但在 CMake 里，这样的工作同样只需要简单的调用几条命令。
