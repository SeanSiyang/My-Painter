#include "mainwindow.h"
#include "newdialog.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    // NewDialog dialog;  // �����´��ڶ���
    // dialog.show();      // ��ʾ����

    return a.exec();
}