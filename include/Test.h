#pragma once

#include "ui_test.h"    // ֱ������Ui_test.h��������ͨ�� namespace
#include <QMainWindow>

class test : public QMainWindow 
{
    Q_OBJECT

public:
    test(QWidget* parent = nullptr);
    ~test();

private:
    Ui_test *ui;
};