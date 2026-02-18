cmake_minimum_required(VERSION 3.10.2)
project(Test)
set(CMAKE_CXX_STANDARD 17)

# 取出当前目录中所有的源文件, 存储到一个变量中
aux_source_directory(./ SRC)
# 把源文件制作成静态库
add_library(Test STATIC ${SRC})
# 链接动态库
target_link_libraries(Test protobuf)
