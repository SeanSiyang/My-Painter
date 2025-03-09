# 导入头文件

`include_directories()`是 全局性 的，调用后会影响当前作用域下 所有后续目标（包括子目录中的目标）

所有在该命令之后添加的可执行文件或库都会自动继承这些头文件路径

```cmake
include_directories(include)  # 全局添加头文件路径
add_executable(MyApp ...)     # MyApp 会自动包含 include 目录
add_library(MyLib ...)        # MyLib 也会自动包含 include 目录
```

`target_include_directories()` 是 目标级别 的，仅对指定的目标生效。通过作用域关键字（PRIVATE/PUBLIC/INTERFACE）可以控制头文件路径的可见性

```cmake
add_executable(MyApp ...)
target_include_directories(MyApp PRIVATE include)  # 仅 MyApp 使用 include 目录
```

`include_directories()`： 不会自动传递依赖。如果目标 A 依赖目标 B，目标 B 的全局头文件路径需要手动添加到目标 A 中

> 无法传递依赖：如果另一个目标（如 OtherApp）通过 target_link_libraries(OtherApp PRIVATE MyLib) 链接 MyLib，include 目录不会自动传递给 OtherApp。即使 MyLib 使用了 include_directories()，OtherApp 仍需手动添加 include 路径，否则会报头文件找不到的错误

`target_include_directories()`： 通过 PUBLIC 或 INTERFACE 关键字，头文件路径可以 自动传递 给依赖当前目标的其他目标。例如，库的公共头文件路径可以通过 PUBLIC 暴露给链接它的可执行文件

`include_directories()`： 适用于 小型项目 或 所有目标共享同一组头文件路径 的场景（如集中管理第三方库路径）

`target_include_directories()`： 适用于 大型项目 或 模块化开发，需为不同目标（如库、可执行文件）单独管理头文件路径，避免全局污染

# CMakeLists.txt

`include_directories()`的使用方法

位置：通常在 add_executable 或 add_library 之前调用

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)

include_directories(include)  # 全局添加 include 目录

add_executable(MyApp src/main.cpp)
add_library(MyLib src/mylib.cpp)
```

`target_include_directories`的使用方法

位置：必须在目标（add_executable 或 add_library）生成之后调用

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject)

add_executable(MyApp src/main.cpp)
add_library(MyLib src/mylib.cpp)

# 为 MyApp 添加私有头文件路径
target_include_directories(MyApp PRIVATE include)

# 为 MyLib 添加公共头文件路径（暴露给依赖它的目标）
target_include_directories(MyLib PUBLIC include)
```

关键字：

- `PRIVATE`：仅当前目标使用此头文件路径（如内部实现的私有头文件）
- `PUBLIC`：当前目标和依赖它的其他目标均可使用（如库的 API 头文件）
- `INTERFACE`：当前目标不使用此路径，但依赖它的目标可以使用（如仅暴露接口的库）
