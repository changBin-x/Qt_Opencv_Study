#查找当前目录下的所有文件
#并将名称保存到DIR_LIB_SRCS
aux_source_directory(. DIR_LIB_SRCS)

#指定生成mathFunctions链接库
add_library(mathFunctions ${DIR_LIB_SRCS})

#指定mathFunctions库的安装路径
install(TARGETS mathFunctions DESTINATION lib)
install(FILES mathFunctions.h DESTINATION include)
