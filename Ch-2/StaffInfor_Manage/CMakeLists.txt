cmake_minimum_required(VERSION 2.8)

project(StaffInfor)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加Clocking-in Machine 目录
add_subdirectory(ClockingIn_Machine)

add_executable(StaffInfor, StaffInfor_Manage.cc)
target_link_directories(StaffInfor ClockIn_Mach)

