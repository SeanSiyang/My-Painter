#pragma once

#include <QDialog>

namespace Ui{
    class NewDialog;
}

class NewDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = nullptr);
    ~NewDialog();

private:
    Ui::NewDialog *ui;

    
};