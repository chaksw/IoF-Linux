cmake_minimum_required(VERSION 2.8)
project(main)

# 指定目标文件及库文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指名项目包含一个子目录 Project，这样 Project 目录下的 CMakeLists.txt文件和源代码也会被处理
add_subdirectory(source)

add_executable(main main.c)
# 添加链接库
target_link_libraries(main StaffInfor_Manage)

