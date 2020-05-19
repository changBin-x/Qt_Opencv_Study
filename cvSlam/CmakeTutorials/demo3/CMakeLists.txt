cmake_minimum_required(VERSION 3.10)
project(Demo3)
aux_source_directory(. srcFiles)
#添加math子目录
#使用命令 add_subdirectory 指明本项目包含一个子目录 math，
#这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 
add_subdirectory(math)
#指定生成目标
add_executable(Demo3 main.cpp)
#添加链接库
#使用命令 target_link_libraries 
#指明可执行文件 main 需要连接一个名为 MathFunctions 的链接库 
target_link_libraries(Demo3 mathFunctions)