# Code

main.cpp
```c++
#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
    return 0;
}
```

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.20)        
project(my_painter)   
add_executable(${PROJECT_NAME} main.cpp)
```

# 解释

```cmake
cmake_minimum_required(VERSION 3.20)  
```
这是CMake的版本要求声明，表示当前项目需要至少CMake 3.20版本才能正常运行。如果系统安装的CMake版本低于3.20，会报错提醒。这个命令必须放在CMakeLists.txt文件的最前面。

```cmake
project(my_painter)
```

这行代码定义了项目的基本信息，项目名称是my_painter，且会自动生成变量```${PROJECT_NAME}```，值为```my_painter```，还隐式生成项目版本变量```${PROJECT_VERSION}```

```cmake
add_executable(${PROJECT_NAME} main.cpp)
```
这行代码是创建可执行文件的指令，`${PROJECT_NAME}`会被替换为前面定义的`my_painter`，最终生成的可执行文件名为my_painter（Windows是my_painter.exe）

第二个参数main.cpp指定了构建这个可执行文件所需的源文件

## project()的作用

### 设置项目名称

该命令将当前项目的名称设为my_painter，并自动生成以下关键变量
- ${PROJECT_NAME}：存储项目名称（值为my_painter）
- PROJECT_SOURCE_DIR：项目源码目录路径
- PROJECT_BINARY_DIR：构建输出目录路径
- CMAKE_PROJECT_NAME：若当前是顶层项目，此变量与PROJECT_NAME一致

### 隐式配置构建环境

检查C/C++编译器可用性（默认语言为C和C++）
若未显式指定版本，会隐式生成PROJECT_VERSION等版本变量（默认值为空）

### 影响生成的项目文件

在生成Visual Studio解决方案（.sln）时，解决方案文件名默认与PROJECT_NAME一致，即my_painter.sln

但需注意：

若通过CMake GUI或命令行指定生成器（如-G "Visual Studio 17 2022"），生成的文件名仍基于PROJECT_NAME

若存在多级子项目（如通过add_subdirectory），顶层项目的CMAKE_PROJECT_NAME将决定主解决方案名

### 常见场景

单项目多可执行文件：可在同一CMakeLists.txt中多次调用add_executable，生成多个独立程序

```cmake
project(my_painter)
add_executable(app1 src1.cpp)
add_executable(app2 src2.cpp)
```

动态调整名称：可通过变量或条件语句灵活设置目标名

```cmake
set(EXE_NAME "painter_tool")
if (WIN32)
    set(EXE_NAME "${EXE_NAME}_win")
endif()

add_executable(${EXE_NAME} main.cpp)
```

# 使用说明

## 生成项目配置文件（构建项目）

```bash
cmake -S . -B build
```

输出：
```bash
-- The C compiler identification is MSVC 19.41.34123.0
-- The CXX compiler identification is MSVC 19.41.34123.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: E:/ProgrammingEditor/Microsoft Visual Studio/2022/VC/Tools/MSVC/14.41.34120/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: E:/ProgrammingEditor/Microsoft Visual Studio/2022/VC/Tools/MSVC/14.41.34120/bin/Hostx64/x64/cl.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (9.2s)
-- Generating done (0.0s)
-- Build files have been written to: E:/Codes/Github/My-Painter/build
```

项目构建好以后，就可以进入build目录查看生成的内容：

```bash
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----          2025/3/7     17:01                CMakeFiles
-a----          2025/3/7     17:01          44607 ALL_BUILD.vcxproj
-a----          2025/3/7     17:01            281 ALL_BUILD.vcxproj.filters
-a----          2025/3/7     17:01          13963 CMakeCache.txt
-a----          2025/3/7     17:01           1439 cmake_install.cmake
-a----          2025/3/7     17:01           3120 my_painter.sln
-a----          2025/3/7     17:01          53559 my_painter.vcxproj
-a----          2025/3/7     17:01            565 my_painter.vcxproj.filters
-a----          2025/3/7     17:01          44713 ZERO_CHECK.vcxproj
-a----          2025/3/7     17:01            524 ZERO_CHECK.vcxproj.filters
```

## 编译

在这个阶段，CMake 会触发完整的编译和链接过程

cmake --build . 本身不直接执行编译或链接，而是调用 CMake 生成的底层构建系统（如 make、ninja 或 Visual Studio 的 MSBuild）。这是 CMake 的抽象层设计，使得用户无需关心不同平台构建工具的具体命令

该命令会执行以下操作：

- 编译：将源代码（.cpp、.c 等）编译为对象文件（.o、.obj）。
- 链接：将对象文件和库文件（静态库 .a/.lib 或动态库 .so/.dll）链接为最终的可执行文件或库

```bash
cmake --build build
```

输出：
```bash
CMake is re-running because E:/Codes/Github/My-Painter/build/CMakeFiles/generate.stamp is out-of-date.
  the file 'E:/Codes/Github/My-Painter/CMakeLists.txt'
  is newer than 'E:/Codes/Github/My-Painter/build/CMakeFiles/generate.stamp.depend'
  result='-1'
-- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.19045.
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: E:/Codes/Github/My-Painter/build
适用于 .NET Framework MSBuild 版本 17.11.9+a69bbaaf5

  1>Checking Build System
  Building Custom Rule E:/Codes/Github/My-Painter/CMakeLists.txt
  main.cpp
  my_painter.vcxproj -> E:\Codes\Github\My-Painter\build\Debug\my_painter.exe
  Building Custom Rule E:/Codes/Github/My-Painter/CMakeLists.txt
```

生成的可执行程序就是：E:\Codes\Github\My-Painter\build\Debug\my_painter.exe

## Linux

```bash
# 创建并进入构建目录（推荐外部构建）
mkdir build
cd build

# 生成Makefile，默认生成Unix Makefiles，支持Debug/Release模式
cmake ..

# 编译（默认Debug模式）
make

# 或指定Release模式
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Windows

```bash
# 创建并进入构建目录（推荐外部构建）
mkdir build
cd build

# 生成VS解决方案（.sln文件）
cmake .. -G "Visual Studio 17 2022" -A x64

# -G 指定生成器版本（如VS2022用"Visual Studio 17 2022"）
# -A x64 表示生成64位项目

# 使用MSBuild编译（Release模式）
cmake --build . --config Release

# 或直接使用MSBuild命令
msbuild my_painter.sln /p:Configuration=Release;Platform=x64

# 编译后的可执行文件默认在build/Release目录下

# 运行程序
.\Release\my_painter.exe
```

曹老师课程中的方式，与linux中的习惯不太一样：

```bash
cmake -S . -B build
# -S 指定源码根目录为当前目录（即CMakeLists.txt所在位置）
# -B build：指定构建目录为build（自动创建该目录）

cmake --build build
# --build 触发实际编译阶段
# build 指定构建目录路径
# 等价于进入build目录以后 cmake --build .
```

# 快速入手

```bash
# windows
mkdir build                                     # 创建构建目录
cd build                   @                     # 进入构建目录
# mkdir build 和 cd build 是冗余的，CMake 可通过 -B 参数自动创建目录。

cmake .. -G "Visual Studio 17 2022" -A x64      # 生成构建系统
# .. 是-S的参数
# 等价于
# cmake -S .. -B . -G "Visual Studio 17 2022" -A x64
# -S .. 指定源码目录为父目录，-B . 指定构建目录为当前目录（即 build）

cmake --build . --config Release                # 编译Release版本
# cmake --build <构建目录路径> [其他选项]
# --build 是 CMake 的子命令，用于触发构建阶段，不可省略。
# . 表示构建目录的路径（即包含 CMakeCache.txt 和生成构建系统文件的目录），非--build的参数
# <构建目录路径> 是必填参数

# 推荐命令(official)
# 官方推荐的方式并不是站在build目录角度出发，而是项目目录角度出发

cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release

# 也就是不需要创建build了，全部都自动创建了，这与linux不一样

# -S . 明确指定源码目录为当前目录（无需进入 build）
# -B build 自动创建并管理构建目录
# 优势：无需手动切换目录，命令更简洁且符合 CMake 官方推荐实践

# 详细的推荐命令
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX="C:/my_install"
# -S .：指定源码目录为当前目录（含 CMakeLists.txt 的根目录）
# -B build：创建并指定构建目录为 build，实现外部构建（源码与构建文件分离）
# -G：选择生成器（Visual Studio 2022），-A x64 指定 64 位架构
# -DCMAKE_INSTALL_PREFIX：设置安装路径（默认为 C:/Program Files），建议自定义路径避免权限问题

cmake --build build --config Release --parallel 8
# --config Release：指定构建配置类型为 Release（默认 Debug）
# --parallel 8：启用 8 线程加速编译，适配 MSBuild 或 Ninja

cmake --install build --config Release --prefix "C:/my_install"
# cmake --install <构建目录路径> [选项]
# --install：将编译产物（可执行文件、库、头文件等）复制到安装目录
# --prefix：覆盖 CMAKE_INSTALL_PREFIX 的安装路径（可选）

# linux
mkdir build
cd build 
cmake ..
make -j8

# 官方推荐（不用手动创建目录）
# 生成 Release 版本的构建系统
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 编译并启用 8 线程
cmake --build build --parallel 8

# 运行程序
./build/my_executable

# 安装到 /usr/local/bin
sudo cmake --build build --target install
```

可以注意到，与习惯的linux的使用方式，在编译链接的时候使用的是 `cmake --build .` 来触发


在`install`的时候也有点不一样

Windows 和 Linux 在使用 CMake 的 install 命令时存在一些关键差异，主要涉及构建类型指定、路径处理和生成器选择等方面。

在Windows的cmake中，必须显式指定 `--config`

由于 Windows 常用的生成器（如 Visual Studio）支持多配置（Debug/Release/RelWithDebInfo 等），在 install 阶段必须通过 --config 参数明确类型，否则默认安装 Debug 版本
```bash
cmake --install build --config Release  # 指定安装 Release 版本
```

Linux 无需指定 `--config`

单配置生成器（如 Makefile）在配置阶段已通过 -DCMAKE_BUILD_TYPE=Release 确定构建类型，install 时直接安装该类型。
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release  # 配置阶段指定构建类型
cmake --install build  # 自动安装 Release 版本
```

安装路径的默认值与覆盖方式

Windows默认安装路径：

若未设置 `CMAKE_INSTALL_PREFIX`，默认路径为 `C:/Program Files/ProjectName`，可能需要管理员权限。
覆盖路径的方法：

```bash
# 配置阶段设置
cmake -B build -DCMAKE_INSTALL_PREFIX="D:/my_install"
# 安装阶段临时覆盖
cmake --install build --prefix "D:/my_install"
```

Linux
默认安装路径：通常为 `/usr/local/`（二进制在 `bin/`，库在 `lib/`，头文件在 `include/`）。
覆盖路径的方法：
```bash
cmake -B build -DCMAKE_INSTALL_PREFIX="/opt/myapp"  # 配置阶段设置
```

# 简化

```bash
# 无需进入build目录

# Windows
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX="C:/my_install"

cmake --build build --config Release --parallel 8

cmake --install build --config Release --prefix "C:/my_install"

# linux
cmake -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --parallel 8

sudo cmake --build build --target install
```

# 查看支持的生成器列表

```bash
cmake --help
```

输出：

```bash
Generators

The following generators are available on this platform (* marks default):
* Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Deprecated.  Generates Visual Studio 2013
                                 project files.  Optional [arch] can be
                                 "Win64" or "ARM".
  Visual Studio 9 2008 [arch]  = Deprecated.  Generates Visual Studio 2008
                                 project files.  Optional [arch] can be
                                 "Win64" or "IA64".
  Borland Makefiles            = Generates Borland makefiles.
  NMake Makefiles              = Generates NMake makefiles.
  NMake Makefiles JOM          = Generates JOM makefiles.
  MSYS Makefiles               = Generates MSYS makefiles.
  MinGW Makefiles              = Generates a make file for use with
                                 mingw32-make.
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
  Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - MinGW Makefiles = Generates CodeBlocks project files
                                 (deprecated).
  CodeBlocks - NMake Makefiles = Generates CodeBlocks project files
                                 (deprecated).
  CodeBlocks - NMake Makefiles JOM
                               = Generates CodeBlocks project files
                                 (deprecated).
  CodeBlocks - Ninja           = Generates CodeBlocks project files
                                 (deprecated).
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files
                                 (deprecated).
  CodeLite - MinGW Makefiles   = Generates CodeLite project files
                                 (deprecated).
  CodeLite - NMake Makefiles   = Generates CodeLite project files
                                 (deprecated).
  CodeLite - Ninja             = Generates CodeLite project files
                                 (deprecated).
  CodeLite - Unix Makefiles    = Generates CodeLite project files
                                 (deprecated).
  Eclipse CDT4 - NMake Makefiles
                               = Generates Eclipse CDT 4.0 project files
                                 (deprecated).
  Eclipse CDT4 - MinGW Makefiles
                               = Generates Eclipse CDT 4.0 project files
                                 (deprecated).
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files
                                 (deprecated).
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files
                                 (deprecated).
  Kate - MinGW Makefiles       = Generates Kate project files (deprecated).
  Kate - NMake Makefiles       = Generates Kate project files (deprecated).
  Kate - Ninja                 = Generates Kate project files (deprecated).
  Kate - Ninja Multi-Config    = Generates Kate project files (deprecated).
  Kate - Unix Makefiles        = Generates Kate project files (deprecated).
  Sublime Text 2 - MinGW Makefiles
                               = Generates Sublime Text 2 project files
                                 (deprecated).
  Sublime Text 2 - NMake Makefiles
                               = Generates Sublime Text 2 project files
                                 (deprecated).
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files
                                 (deprecated).
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files
                                 (deprecated).
```