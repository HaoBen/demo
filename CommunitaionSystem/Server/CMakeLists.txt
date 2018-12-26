#cmake最低版本要求
cmake_minimum_required(VERSION 3.4.0)

#项目名称
project(Server)

#源文件目录，并将该目录下的源文件名放到变量SRC_LIST中
aux_source_directory(./src SRC_LIST)

#指定头文件路径
include_directories(./include)

#指定需要链接的库，该项以参数形式提供给编译器
LINK_LIBRARIES(-lpthread)

#指定可执行文件的输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#编译主函数，生成可执行文件
add_executable(Server ${SRC_LIST})
