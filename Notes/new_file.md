说明：在vscode环境下如何创建新的窗口文件

需要三个文件：

- mainwindow.h
- mainwindow.cpp
- mainwindow.ui

# 头文件

```c++
#pragma once

#include <QMainWindow>

namespace Ui {
    class mainwindow;
}

class mainwindow : public QMainWindow {
    Q_OBJECT
    
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
};
```

> 为什么要使用命名空间Ui？

来源：当你使用 Qt Designer 创建 .ui 文件时，Qt 会通过 uic 工具自动生成 ui_*.h 文件（例如 ui_mainwindow.h），其中包含一个名为 Ui 的命名空间，内部定义了界面类（如 Ui::mainwindow）

目的：将自动生成的 UI 代码与你的业务逻辑代码隔离，避免命名冲突

> `Ui::mainwindow *ui;` 的作用是什么？

功能：ui 是指向自动生成的界面类 Ui::mainwindow 的指针，用于访问 UI 文件中定义的控件（如按钮、文本框等）

生命周期：在构造函数中通过 ui->setupUi(this) 初始化，析构函数中释放内存

访问控件：例如，如果 UI 文件中有一个名为 pushButton 的按钮，可以通过 ui->pushButton 访问它

> `ui`的其他声明方式

使用智能指针自动管理内存，避免手动delete

```c++
#pragma once
#include <QMainWindow>
#include <QScopedPointer>  // 新增头文件

// 前置声明
namespace Ui {
    class mainwindow;
}

class mainwindow : public QMainWindow {
    Q_OBJECT
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();  // 不再需要手动 delete ui

private:
    QScopedPointer<Ui::mainwindow> ui;  // 使用智能指针
};
```

直接包含`ui_*.h`头文件，需要在`.cpp`中调用`setupUi`

```c++
#pragma once
#include <QMainWindow>
#include "ui_mainwindow.h"  // 直接包含 UI 头文件

class mainwindow : public QMainWindow {
    Q_OBJECT
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindow *ui;  // 声明方式不变
};
```

对应的`mainwindow.cpp`：

```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"  // 必须包含生成的 UI 头文件

mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::mainwindow)  // 初始化智能指针
{
    ui->setupUi(this);  // 加载 UI 布局
}

mainwindow::~mainwindow()
{
    delete ui; 
}
```

> `namesapce Ui` 的作用与实现机制

**声明与定义分离**：

在 `mainwindow.h` 中，`namespace Ui { class mainwindow; }` 是 前置声明（forward declaration），仅告诉编译器存在一个名为 `Ui::mainwindow` 的类，但不提供具体定义。

真正的类定义在 `ui_mainwindow.h`（由 Qt 自动生成），其中包含完整的成员变量和 `setupUi()` 方法

**ui_mainwindow.h 的内容**：

当你通过 Qt Designer 设计界面并保存为 `mainwindow.ui` 后，Qt 的 uic 工具会生成 `ui_mainwindow.h`，内容大致如下:

```c++
// ui_mainwindow.h（自动生成，不可手动编辑）
namespace Ui {
    class mainwindow {
    public:
        QPushButton *pushButton;  // 假设 UI 中有一个按钮
        void setupUi(QMainWindow *parent) {
            // 创建按钮、布局等控件
            pushButton = new QPushButton(parent);
            // ...
        }
    };
}
```

**主窗口类的职责**：

`mainwindow` 类（继承自 `QMainWindow`）负责业务逻辑，而 `Ui::mainwindow` 类（在 `ui_mainwindow.h` 中定义）负责管理界面控件。

通过组合的方式（`Ui::mainwindow *ui` 成员变量）将界面逻辑与业务逻辑分离

总结：

`mainwindow.h`里定义的`mainwindow`类并不是 `Ui::mainwindow`类

只是在`mainwindow`类里声明了这个`Ui::mainwindow`类的变量，就可以访问`Ui::mainwindow`类里的元素了

> 另一种实现方式的原理及与传统方式的区别

Test.h：
```c++
#pragma once
#include "ui_Test.h"
#include <QMainWindow>

class Test : public QMainWindow {
    Q_OBJECT
    
public:
    Test(QWidget* parent = nullptr);
    ~Test();

private:
    Ui_Test* ui;
};
```

Test.cpp：
```c++
#include "Test.h"

Test::Test(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_Test)
{
    ui->setupUi(this);
}

Test::~Test()
{
    delete ui; 
}
```

区别在于 UI 类的生成方式（是否使用 namespace Ui）

传统方式：

通过 `.ui` 文件生成的 UI 类通常位于 `namespace Ui` 中，例如 `Ui::Test`，对应的头文件为 `ui_Test.h`，代码结构如下：
```c++
// ui_Test.h（自动生成）
namespace Ui {
    class Test {  // UI 类在命名空间内
    public:
        void setupUi(QMainWindow *parent) { ... }
        // 其他控件声明...
    };
}
```

现在这种方式：

在代码中直接使用 `Ui_Test 类`（无命名空间），说明生成的 `ui_Test.h` 可能未将 UI 类放在 namespace Ui 中，而是直接定义为全局类：
```c++
// Test.h
// 传统方法将声明namespace Ui 然后引入自动生成的 Ui::mainwindow类
// 这种方式是直接声明一个全局类 Ui_Test
#include "ui_Test.h" // 引入全局类

private:
    Ui_Test* ui; // 声明一个全局类变量，传统方法中是声明一个命名空间类的变量

// Test.cpp
// 不用在cpp里引入 ui_Test.h，这一步已经在头文件中实现，在传统方法里需要引入

Test::Test(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_Test)  // 这里直接创建的是Ui_Test类对象（全局类），而传统方式声明的是命名空间里面的Ui::Test类
```


两种不同方式对比如下：

`.cpp`：
```c++
// traditional 
#include "mainwindow.h"
#include "ui_test.h"        // 因为使用了命名空间，所以mainwindow.h不用包含这个文件，但是在cpp中需要使用

mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow) // 区别：使用命名空间的类来创建ui
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui; 
}

// other
#include "test.h"   
// 不使用命名空间，所以无需在cpp中引入ui_xxx.h

test::test(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_test)   // 区别：new一个ui对象时，方法不太一样，没用到命名空间
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui;
}
```

可以看到，区别在于是否使用了namespace来new一个ui对象，如果在头文件里使用命名空间了，就不需要在头文件里引入 `ui_xxx.h`，但是要在cpp中引入`ui_xxx.h`

如果不使用命名空间，则需要把`ui_xxx.h`放到头文件中

`.h`：
```c++
// traditional
#pragma once
// 使用了命名空间，所以不需要引入 ui_xxx.h
#include <QMainWindow> 

namespace Ui {
    class mainwindow; 
}

class mainwindow : public QMainWindow {
    Q_OBJECT
    
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindow *ui; // 使用了命名空间的方式创建 ui
};

// other
#pragma once

#include "ui_test.h"    // 因为没有使用命名空间，所以需要引入 ui_xxx.h
#include <QMainWindow>

class test : public QMainWindow 
{
    Q_OBJECT

public:
    test(QWidget* parent = nullptr);
    ~test();

private:
    Ui_test *ui;    // 没有使用命名空间的方式声明ui 
    // Ui_test在ui_xxx.h中定义了
};
```