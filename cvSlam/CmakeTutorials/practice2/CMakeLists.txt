cmake_minimum_required(VERSION 3.10)
project(practice2)
# aux_source_directory(. srcFiles)

#重新定义 EXECUTABLE_OUTPUT_PATH 
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#重新定义最终的共享库
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# message(STATUS "This is BINARY dir" ${PROJECT_BINARY_DIR})
# message(STATUS "This is SOURCE dir" ${PROJECT_SOURCE_DIR})
# add_executable(practice1 ${srcFiles})

#添加资源子目录
#生成的hello位于./bin目录
#ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
#用于向当前工程添加存放源文件的子目录，
#并可以指定中间二进制和目标二进制存放的位置。
#EXCLUDE_FROM_ALL 参数的含义是将这个目录从编译过程中排除，
#比如，工程的 example，可能就需要工程构建完成后，再进入 example 目录单独进行构建
add_subdirectory(src ${PROJECT_SOURCE_DIR}/bin)

#INSTALL 指令用于定义安装规则，安装的内容可以包括
#目标二进制、动态库、静态库以及文件、目录、脚本等
#普通文件的安装：
#INSTALL(FILES files... DESTINATION <dir>   #安装类型FILES 文件名 目标关键字DESTINATION 目标文件夹
#   [PERMISSIONS permissions...]    #权限
#   [CONFIGURATIONS [Debug|Release|...]]    #配置模式
#   [COMPONENT <component>]
#   [RENAME <name>] [OPTIONAL]) #重命名
#可用于安装一般文件，并可以指定访问权限，文件名是此指令所在路径下的相对路径。
#如果默认不定义权限 PERMISSIONS，安装后的权限为：
#OWNER_WRITE, OWNER_READ, GROUP_READ,和 WORLD_READ，即 644 权限。
#安装COPYRIGHT/README
install(FILES COPYRIGHT README.md DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#目标文件的安装
#INSTALL(TARGETS targets...
    # [[ARCHIVE|LIBRARY|RUNTIME]
    # [DESTINATION <dir>]
    # [PERMISSIONS permissions...]
    # [CONFIGURATIONS [Debug|Release|...]]
    # [COMPONENT <component>]
    # [OPTIONAL]] 
    # [...])
# DESTINATION 定义了安装的路径，
# 如果路径以/开头，那么指的是绝对路径，这时候CMAKE_INSTALL_PREFIX 其实就无效了。
# 如果你希望使用 CMAKE_INSTALL_PREFIX 来定义安装路径，
# 就要写成相对路径，即不要以/开头，那么安装后的路径就是
# ${CMAKE_INSTALL_PREFIX}/<DESTINATION 定义的路径>