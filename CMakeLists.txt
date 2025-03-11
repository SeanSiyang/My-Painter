# 指定CMake最低版本要求（Qt5推荐3.15+）
cmake_minimum_required(VERSION 3.15)

# 定义项目名称、版本和编程语言
project(MyPainter VERSION 1.0 LANGUAGES CXX)

# 设置生成器为MSVC2022（可选）
# set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE INTERNAL "")

#--------------------------------------------------------------------
# 构建类型配置（Debug/Release/RelWithDebInfo）
#--------------------------------------------------------------------

# 支持的构建类型列表
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "支持的构建类型" FORCE)

# 设置默认构建类型为 Release（如果用户未通过命令行指定）
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "默认构建类型" FORCE)
    message(STATUS "构建类型未指定，默认使用: ${CMAKE_BUILD_TYPE}")
endif()

#----------------------------------------------------------
# Qt自动化配置
#----------------------------------------------------------
# 启用Qt自动编译特性
set(CMAKE_AUTOMOC ON)   # 启用Q_OBJECT元对象系统的自动处理（生成moc_xxx.cpp）
set(CMAKE_AUTOUIC ON)   # 启用.ui文件的自动编译（生成ui_xxx.h）
set(CMAKE_AUTORCC ON)   # 启用.qrc资源文件的自动编译（生成qrc_xxx.cpp）
set(CMAKE_AUTORCC ON)   # 启用资源自动编译

#----------------------------------------------------------
# 依赖配置
#----------------------------------------------------------

# 设置 OpenCV 路径
set(OpenCV_DIR "E:/Environment/OpenCV480/opencv/build/x64/vc16/lib")

# 查找Qt5核心模块（必须组件：Core和Widgets）
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
# 查找OpenCV
find_package(OpenCV REQUIRED)

# 指定.ui文件的搜索路径（解决AutoUic错误的关键配置）
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

#----------------------------------------------------------
# 目录配置
#----------------------------------------------------------
# 添加头文件搜索路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 自定义头文件目录
    ${CMAKE_CURRENT_BINARY_DIR}          # 生成的ui_xxx.h存放位置
    ${OpenCV_INCLUDE_DIRS}               # 添加 OpenCV 头文件路径S
)

#----------------------------------------------------------
# 源代码管理
#----------------------------------------------------------
# 递归收集源代码文件（注意：GLOB_RECURSE在新增文件时需重新生成）
file(GLOB_RECURSE SOURCES
    "src/*.cpp"     # 所有C++源文件
    "include/*.h"   # 所有头文件（触发AUTOMOC需要）
    "ui/*.ui"       # 所有界面文件（触发AUTOUIC需要）
)

#----------------------------------------------------------
# 构建目标
#----------------------------------------------------------
# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接Qt库（PRIVATE表示仅当前目标依赖）
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core       # Qt核心库（QObject等）
    Qt5::Widgets    # Qt Widgets模块（QApplication/QMainWindow等）
    ${OpenCV_LIBS}  # 链接 OpenCV 库
)

#--------------------------------------------------------------------
# 编译器选项（根据构建类型优化）
#--------------------------------------------------------------------
# Debug 模式：禁用优化，启用调试符号
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:-O0 -g3>
)

# Release 模式：最大优化，禁用调试符号
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

# RelWithDebInfo：优化但保留调试符号
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
)


# # 指定CMake最低版本要求（Qt5推荐3.15+）
# cmake_minimum_required(VERSION 3.15)

# # 定义项目名称、版本和编程语言
# project(MyPainter VERSION 1.0 LANGUAGES CXX)

# # 设置生成器为MSVC2022（可选）
# # set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE INTERNAL "")

# #----------------------------------------------------------
# # Qt自动化配置
# #----------------------------------------------------------
# # 启用Qt自动编译特性
# set(CMAKE_AUTOMOC ON)   # 启用Q_OBJECT元对象系统的自动处理（生成moc_xxx.cpp）
# set(CMAKE_AUTOUIC ON)   # 启用.ui文件的自动编译（生成ui_xxx.h）
# set(CMAKE_AUTORCC ON)   # 启用.qrc资源文件的自动编译（生成qrc_xxx.cpp）
# set(CMAKE_AUTORCC ON)   # 启用资源自动编译

# #----------------------------------------------------------
# # 依赖配置
# #----------------------------------------------------------
# # 查找Qt5核心模块（必须组件：Core和Widgets）
# find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# # 指定.ui文件的搜索路径（解决AutoUic错误的关键配置）
# set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

# #----------------------------------------------------------
# # 目录配置
# #----------------------------------------------------------
# # 添加头文件搜索路径
# include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}/include  # 自定义头文件目录
#     ${CMAKE_CURRENT_BINARY_DIR}          # 生成的ui_xxx.h存放位置
# )

# #----------------------------------------------------------
# # 源代码管理
# #----------------------------------------------------------
# # 递归收集源代码文件（注意：GLOB_RECURSE在新增文件时需重新生成）
# file(GLOB_RECURSE SOURCES
#     "src/*.cpp"     # 所有C++源文件
#     "include/*.h"   # 所有头文件（触发AUTOMOC需要）
#     "ui/*.ui"       # 所有界面文件（触发AUTOUIC需要）
# )

# #----------------------------------------------------------
# # 构建目标
# #----------------------------------------------------------
# # 创建可执行文件
# add_executable(${PROJECT_NAME} ${SOURCES})

# # 链接Qt库（PRIVATE表示仅当前目标依赖）
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     Qt5::Core       # Qt核心库（QObject等）
#     Qt5::Widgets    # Qt Widgets模块（QApplication/QMainWindow等）
# )

# # MSVC调试配置
# if(MSVC)
#     # 生成PDB调试符号
#     target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
#     target_link_options(${PROJECT_NAME} PRIVATE /DEBUG /OPT:REF /OPT:ICF)
    
#     # 设置运行时库（MT/MD根据需求选择）
#     set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# endif()

# 设置.ui文件搜索路径
# set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

# # cmake -S . -B build 生成项目配置文件
# # cmake --build build 编译
# # CMake install : https://cmake.org/download/
# # 自动复制依赖的动态库 windeployqt.exe
# # cd build/Debug
# # E:/ProgrammingEditor/Qt/Qt5.14.2/5.14.2/msvc2017_64/bin/windeployqt my_painter.exe

# cmake_minimum_required(VERSION 3.20)    # CMake最低版本要求

# # 定义项目名称和编程语言
# project(MyPainter LANGUAGES CXX)


# set(CMAKE_PREFIX_PATH "E:/ProgrammingEditor/Qt/Qt5.14.2/5.14.2/msvc2017_64") # 指定 Qt 的安装路径

# set(CMAKE_AUTOUIC ON)   # 自动处理 .ui 文件（Qt 用户界面文件）
# set(CMAKE_AUTOMOC ON)   # 自动生成 moc 文件（Qt 元对象系统）
# set(CMAKE_AUTORCC ON)   # 自动编译 .qrc 资源文件
# set(CMAKE_INCLUDE_CURRENT_DIR ON)   # 自动包含当前目录到头文件搜索路径

# set(CMAKE_AUTOUIC_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")  # 生成到 build/
# set(CMAKE_AUTOMOC_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")  # 可选：moc 文件也生成到 build/

# set(CMAKE_CXX_STANDARD 11)   # 强制使用 C++11 标准
# set(CMAKE_CXX_STANDARD_REQUIRED ON) # 必须支持指定标准，否则报错

# find_package(Qt5 COMPONENTS Widgets REQUIRED) # 查找 Qt5 Widgets 模块
# aux_source_directory(./src srcs)    # 收集 src 目录下的所有源文件到变量 srcs

# # 收集 UI 文件（ui 目录）
# file(GLOB UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")  # 关键：添加 UI 目录下的所有 .ui 文件

# message(STATUS "UI_FILES = ${UI_FILES}")
# message(STATUS "CMAKE_AUTOUIC_SEARCH_PATHS = ${CMAKE_AUTOUIC_SEARCH_PATHS}")


# # 强制 MSVC 使用 UTF-8 编码
# add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# add_executable(${PROJECT_NAME}  # 可执行文件名
#     WIN32                       # If you need a terminal for debug, please comment this statement 
#     ${srcs}                     # 包含所有源文件
#     ${UI_FILES}                 # 包含 ui 目录下的 .ui 文件 
# ) 


# # 添加 include 目录到编译器搜索路径
# target_include_directories(${PROJECT_NAME} PRIVATE 
#     "${CMAKE_CURRENT_SOURCE_DIR}/include"
#     "${CMAKE_CURRENT_BINARY_DIR}"  # 关键：包含构建目录（生成的 ui_*.h 在此）
# )

# qt5_wrap_ui(UI_HEADERS ${UI_FILES})
# target_sources(${PROJECT_NAME} PRIVATE ${UI_HEADERS})

# # # 指定 UI 文件搜索路径（AUTOUIC 需要）
# # list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

# # 功能：告诉编译器在编译 ${PROJECT_NAME}（即你的可执行文件）时，需要搜索 include 目录下的头文件。
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets) # 链接 Qt5 Widgets 库

# # 部署时自动复制 Qt 依赖库（可选）
# if(WIN32)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe
#                 --compiler-runtime
#                 $<TARGET_FILE:${PROJECT_NAME}>
#         COMMENT "Deploying Qt dependencies..."
#     )
# endif()