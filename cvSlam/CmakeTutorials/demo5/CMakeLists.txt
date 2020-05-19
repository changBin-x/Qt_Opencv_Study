# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo5)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
#指定二进制目标文件的位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#指定共享库位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  ${PROJECT_SOURCE_DIR}/config.h
  )
 
# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
	   "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory (math)
  set (EXTRA_LIBS ${EXTRA_LIBS} mathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo5 ${DIR_SRCS})
target_link_libraries (Demo5  ${EXTRA_LIBS})
#指定安装路径
install(TARGETS Demo5 DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(FILES ${PROJECT_BINARY_DIR}/build/config.h DESTINATION ${PROJECT_SOURCE_DIR}/include/)
#启用测试
enable_testing()

#测试程序是否成功运行
add_test(test_run ${PROJECT_SOURCE_DIR}/bin/Demo5 5 2)

#支持gdb
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")