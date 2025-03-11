# QLabel

`QLabel` 是 Qt 框架中用于显示文本、图像和动态内容的核心组件，继承自 `QFrame`，支持丰富的布局和交互功能

## 使用方式

引入头文件

```c++
#include <QLabel>
```

## 核心功能

文本显示：支持纯文本、富文本（HTML 格式），默认左对齐且垂直居中

```c++
QLabel *label = new QLabel("Hello Qt", this);   // 纯文本
label->setText("<b>Hello <i>Qt</i></b>");       // 富文本（HTML）
```

图像显示：支持 QPixmap、QImage、GIF 动画（通过 QMovie）

```c++
QPixmap pix("image.png");
label->setPixmap(pix);
label->setScaledContents(true);  // 自动缩放图像
```

对齐与缩进：通过 `setAlignment()` 设置对齐方式，`setIndent()` 调整缩进

```c++
label->setAlignment(Qt::AlignCenter);  // 居中对齐
label->setIndent(20);                  // 文本缩进20像素
```

边距控制：使用 `setMargin()` 调整内容与边框的距离

自动换行：`setWordWrap(true)` 启用按单词换行（需文本含空格）

超链接：支持 HTML 超链接，需启用 setOpenExternalLinks(true) 自动打开

```c++
label->setText("<a href='https://www.qt.io'>Visit Qt</a>");
label->setOpenExternalLinks(true);
```

文本选择：通过 `setTextInteractionFlags()` 设置可选中或可编辑文本

```c++
label->setTextInteractionFlags(Qt::TextSelectableByMouse);
```

## 实战

### 1.显示文本

利用QLabel和QVBoxLayout布局管理器创建一个垂直居中的文本标签

```c++
QLabel *label = new QLabel();
label->setAlignment(Qt::AlignCenter);                           // 文本居中对齐 
label->setText("Hello World, OpenCV4 + Qt5 Application");       // 设置显示文本

QVBoxLayout *box = new QVBoxLayout();                           // 创建垂直布局管理器
box->addWidget(label);                                          // 将 label 添加到布局中

ui->centralwidget->setLayout(box);                              // 将布局设置到 centralwidget 上
```

第一步：创建`QLabel`并设置属性

- `QLabel`：用于显示文本或图像的控件
- `setAlignment(Qt::AlignCenter)`：设置文本在 `QLabel` 内部水平和垂直居中
- `setText()`：定义要显示的文本内容

第二步：创建垂直布局管理器`QVBoxLayout`

- `QVBoxLayout`：垂直布局管理器，按从上到下的顺序排列控件
- `addWidget()`：将控件（如 `QLabel`）添加到布局中

第三步：将布局应用到父控件

- `centralwidget`：Qt 主窗口（`QMainWindow`）的默认中心区域控件
- `setLayout()`：将布局管理器应用到父控件（此处是 `centralwidget`），父控件会自动管理子控件的布局

知识点：

布局管理器的作用

- 自动调整控件位置和大小：当窗口缩放时，布局内的控件会根据布局规则自动调整
- 支持嵌套布局：可以将多个布局组合（如 `QVBoxLayout` + `QHBoxLayout`）实现复杂界面
- 内存管理：布局对象（`QVBoxLayout`）的父控件（`centralwidget`）会自动释放其内存

`centralwidget` 的角色
- 在 `QMainWindow` 中，`centralwidget` 是主窗口的核心区域，所有主界面控件都应放置在此处。
- 通过 `setLayout()` 设置布局后，`centralwidget` 会自动管理子控件的显示和布局

居中对齐的实现

- `Qt::AlignCenter`：同时启用水平居中（`Qt::AlignHCenter`）和垂直居中（`Qt::AlignVCenter`）。
- 若需更精细控制，可组合其他对齐标志：`label->setAlignment(Qt::AlignLeft | Qt::AlignTop);  // 左上对齐`

### 2.设置Label的字体和显示图像

在Qt中使用QFont设置字体样式，以及通过QPixmap在QLabel中显示图片的操作


设置字体
```c++
QLabel *label = new QLabel();

QFont font;
font.setBold(true);
font.setPixelSize(36);
label->setFont(font)
```

`QFont` 定义字体的样式属性，包括加粗、大小、斜体等

`setBold(true)`：启用加粗效果

`setPixelSize(36)`：以像素为单位设置字体大小

若需与设备无关的尺寸，可用`setPointSize()`（以磅为单位）

其他常见属性：`setFamily("微软雅黑")`（字体族）、`setItalic(true)`（斜体）、`setUnderline(true)`（下划线）

`QFontInfo` 类用于获取字体实际渲染时的属性信息

将 `QFont` 对象传递给 `QFontInfo` 构造函数，即可获取实际生效的字体属性：

```c++
QFont font("Microsoft YaHei", 12, QFont::Bold); // 设置的字体
QFontInfo fontInfo(font);                       // 创建QFontInfo对象

// 检查实际生效的字体属性
qDebug() << "实际字体族：" << fontInfo.family();            // 如 "SimSun" 可能替代 "Microsoft YaHei"
qDebug() << "实际字号（像素）：" << fontInfo.pixelSize();   // 可能因DPI调整变化
qDebug() << "是否加粗：" << fontInfo.bold();                // 可能与设置不同
qDebug() << "是否斜体：" << fontInfo.italic(); 
```

显示图像
```c++
QPixmap pixmap("E:/Codes/Github/My-Painter/resources/images/lena.jpg");

label->setPixmap(pixmap);
```
`QPixmap`是 Qt 中用于处理图像的类，专为屏幕显示优化，适合加载小图或需要频繁绘制的图像

如果图片路径错误或格式不支持，pixmap会为空，后续显示时可能无内容

可以使用`pixmap.isNull()`检查加载是否成功

支持常见图片格式（如PNG、JPEG），通过文件扩展名自动推断格式

内存管理：`QPixmap` 内部使用隐式共享（Copy-on-Write）机制，复制时不会重复占用内存

## 扩展

添加多个控件：

```c++
QVBoxLayout *box = new QVBoxLayout();
box->addWidget(label1);
box->addWidget(label2);
box->addWidget(button);
ui->centralwidget->setLayout(box);
```

设置边距和间距：

```c++
box->setContentsMargins(20, 20, 20, 20);    // 设置布局的外边距（左、上、右、下）
box->setSpacing(10);                        // 控件之间的间距
```

嵌套布局：

```c++
QHBoxLayout *h_box = new QHBoxLayout();     // 水平布局
h_box->addWidget(button1);
h_box->addWidget(button2);

QVBoxLayout *v_box = new QVBoxLayout();     // 垂直布局
v_box->addWidget(label);
v_box->addLayout(h_box);                    // 将水平布局嵌套到垂直布局中

ui->centralwidget->setLayout(vbox);
```