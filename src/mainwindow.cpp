#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QVBoxLayout>

#include <opencv2/opencv.hpp>

#pragma execution_character_set("utf-8")

mainwindow::mainwindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    std::string image_path = "E:/Codes/Github/My-Painter/resources/images/lena.jpg";
    // cv::Mat image = cv::imread(image_path);
    // if (image.empty()) {
    //     std::cerr << "Error: Could not open or find the image!" << std::endl;
    //     // return -1;   
    // } 
    // cv::imshow("test", image);

    QPixmap pixmap("E:/Codes/Github/My-Painter/resources/images/lena.jpg");

    auto label = new QLabel();

    QFont font;
    font.setBold(true);
    font.setPixelSize(36);
    label->setFont(font);

    label->setAlignment(Qt::AlignCenter);
    // label->setText("Hello World, OpenCV4 + Qt5 Application");
    label->setPixmap(pixmap);

    QVBoxLayout *box = new QVBoxLayout();
    box->addWidget(label);

    ui->centralwidget->setLayout(box);

    this->setWindowTitle("≤‚ ‘");
    cv::waitKey(0);
    cv::destroyAllWindows();
}

mainwindow::~mainwindow()
{
    delete ui; 
}