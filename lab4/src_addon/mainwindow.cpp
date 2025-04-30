#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *spiralIndicator = new SpiralProgressIndicator(this);

    slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 100);
    slider->setValue(0);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(spiralIndicator);
    layout->addWidget(slider);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(slider, &QSlider::valueChanged, spiralIndicator, &SpiralProgressIndicator::setProgressValue);
}

MainWindow::~MainWindow()
{
}
