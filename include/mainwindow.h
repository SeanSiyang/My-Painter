#pragma once

#include <QMainWindow>

namespace Ui {
    class mainwindow; // 并不是下面的mainwindow类
}

class mainwindow : public QMainWindow {
    Q_OBJECT
    
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
};