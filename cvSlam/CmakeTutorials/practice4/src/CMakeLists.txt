cmake_minimum_required(VERSION 3.10)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(main main.cc)

#INCLUDE_DIRECTORIES([AFTER|BEFORE] [SYSTEM] dir1 dir2 ...)
# 这条指令可以用来向工程添加多个特定的头文件搜索路径，路径之间用空格分割，
# 如果路径中包含了空格，可以使用双引号将它括起来，
# 默认的行为是追加到当前的头文件搜索路径的后面，
# 可以通过两种方式来进行控制搜索路径添加的方式：
# １，CMAKE_INCLUDE_DIRECTORIES_BEFORE，通过 SET 这个 cmake 变量为 on，
# 可以将添加的头文件搜索路径放在已有路径的前面。
# ２，通过 AFTER 或者 BEFORE 参数，也可以控制是追加还是置前。
include_directories(${PROJECT_SOURCE_DIR}/include)

# 将目标文件链接到 libhello
# LINK_DIRECTORIES(directory1 directory2 ...)#添加非标准的共享库搜索路径

# TARGET_LINK_LIBRARIES(target library1
# <debug | optimized> library2
# ...)
# 这个指令可以用来为 target 添加需要链接的共享库
# target_link_libraries(main ${PROJECT_SOURCE_DIR}/lib/libhello.a)#链接到静态库
target_link_libraries(main ${PROJECT_SOURCE_DIR}/lib/libhello.dll)#链接到动态库