# cmake -S . -B build 生成项目配置文件
# cmake --build build 编译

cmake_minimum_required(VERSION 3.20)        # 最低版本
project(my_painter)   # 对名称的影响？可执行程序？生成的VS项目的名字？

add_executable(${PROJECT_NAME} main.cpp)    # PROJECT_NAME对应project里面的名称


