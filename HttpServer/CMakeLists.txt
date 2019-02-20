project (HttpServer)

# cmake limited version
cmake_minimum_required(VERSION 2.8)

# 指定头文件目录
include_directories(include)

# 指定源文件目录
aux_source_directory(src DIR_SRCS)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# 添加可执行文件所需要的库
