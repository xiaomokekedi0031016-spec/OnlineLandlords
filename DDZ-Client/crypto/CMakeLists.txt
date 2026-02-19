cmake_minimum_required(VERSION 3.16)
project(crypto)

# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
file(GLOB HEAD ./*.h)

# 包含OpenSSL头文件
include_directories("D:/OpenSSL/OpenSSL-Win64/include")

# 将当前目录下的源文件制作成静态库
add_library(crypto ${SRC} ${HEAD})
target_link_libraries(crypto PRIVATE Qt${QT_VERSION_MAJOR}::Core
    "D:/OpenSSL/OpenSSL-Win64/lib/libcrypto.lib")
