#pragma once

#include "ui_test.h"    // 直接引入Ui_test.h，而不是通过 namespace
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