#pragma once

#include <QMainWindow>

namespace Ui {
    class mainwindow; // �����������mainwindow��
}

class mainwindow : public QMainWindow {
    Q_OBJECT
    
public:
    mainwindow(QWidget* parent = nullptr);
    ~mainwindow();

private:
    Ui::mainwindow *ui;
};