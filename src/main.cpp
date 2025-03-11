#include "mainwindow.h"
#include "newdialog.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    // NewDialog dialog;  // 创建新窗口对象
    // dialog.show();      // 显示窗口

    return a.exec();
}