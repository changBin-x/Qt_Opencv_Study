cmake_minimum_required(VERSION 3.10)
project(Demo4)

#加入一个配置头文件，用于Cmake对源码的设置
# configure_file 命令用于加入一个配置头文件 config.h ，
# 这个文件由 CMake 从 config.h.in 生成，
# 通过这样的机制，将可以通过预定义一些参数和变量来控制代码的生成。
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "config.h"
)
#是否使用自己的mathFunctions库
# option 命令添加了一个 USE_MYMATH 选项，并且默认值为 ON
option(USE_MYMATH
"Use provided math implementation" 
ON)

#是否加入mathFunctions库
# 根据 USE_MYMATH 变量的值来决定
# 是否使用我们自己编写的 MathFunctions 库
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTRA_LIBS ${EXTRA_LIBS} mathFunctions)
endif(USE_MYMATH)

aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo4 ${DIR_SRCS}/Bin/)

target_link_libraries(Demo4 ${EXTRA_LIBS})