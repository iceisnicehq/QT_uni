#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::processText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processText() {
    QString inputText = ui->inputLineEdit->text();
    QString proccessedText = inputText.toUpper();
    ui->resultLabel->setText(proccessedText);
}

