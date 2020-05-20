cmake_minimum_required(VERSION 3.10)
set(libHelloSrc hello.cc)

#指定一个编译输出得共享库的位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/include)

#添加动态库
add_library(hello SHARED ${libHelloSrc})
#添加静态库
add_library(hello_static STATIC ${libHelloSrc})
#设置输出的静态库的名称
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
#与上一个指令相对应得指令是GET_TARGET_PROPERTY(VAR target property)
get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)
message(STATUS
"This is the hello_static OUTPUT_NAME:"
${OUTPUT_VALUE})

#安装头文件
install(FILES hello.h DESTINATION ${PROJECT_SOURCE_DIR}/include)

