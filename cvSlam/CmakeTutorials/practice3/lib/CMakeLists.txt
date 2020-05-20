cmake_minimum_required(VERSION 3.10)
set(libHelloSrc hello.cc)

#指定一个编译输出的共享库的新的位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# ADD_LIBRARY(libname 
#   [SHARED|STATIC|MODULE]  #[动态库|静态库|在使用 dyld 的系统有效，如果不支持 dyld，则被当作 SHARED 对待]
#   [EXCLUDE_FROM_ALL]  #EXCLUDE_FROM_ALL 参数的意思是这个库不会被默认构建，
                        #除非有其他的组件依赖或者手工构建
#   source1 source2 ... sourceN)
add_library(hello SHARED ${libHelloSrc})#添加动态库
#我们需要的是名字相同的静态库和动态库，因为 target 名称是唯一的
#所以下面的指令不合适
#需要SET_TARGET_PROPERTIES
add_library(hello_static STATIC ${libHelloSrc})#添加静态库

#SET_TARGET_PROPERTIES可以用来设置输出的名称，对于动态库，还可以用来指定动态库版本和 API 版本
#SET_TARGET_PROPERTIES(target1 target2 ...
#                        PROPERTIES prop1 value1
#                        prop2 value2 ...)
#可以同时得到 libhello.so/libhello.a 两个库了
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
#与上一个指令相对应得指令是GET_TARGET_PROPERTY(VAR target property)
get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)
message(STATUS "This is the hello_static OUTPUT_NAME:" 
${OUTPUT_VALUE})

#cmake 在构建一个新的 target 时，会尝试清理掉其他使用这个名字的库
# 为了回避这个问题，再次使用 SET_TARGET_PROPERTIES 定义CLEAN_DIRECT_OUTPUT属性
set_target_properties(hello PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(hello_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

#实现动态库版本号
#VERSION 指代动态库版本，SOVERSION 指代 API 版本。
set_target_properties(hello PROPERTIES VERSION 1.0 SOVERSION 1)

#安装共享库和头文件
install(TARGETS hello hello_static
LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib#静态库
)
install(FILES hello.h DESTINATION ${PROJECT_SOURCE_DIR}/include/hello)