#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QDate>
#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);
    outputLabel = new QLabel("Результат: ", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(processButton);
    layout->addWidget(outputLabel);

    processor = new DataProcessor(this);

    connect(processor, &DataProcessor::dataProcessed, this, &MainWindow::handleProcessedData);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
}

void MainWindow::handleProcessedData(const QString &data) {
    outputLabel->setText("Результат: " + data);
}

void MainWindow::onProcessButtonClicked() {
    QString inputData = inputField->text();
    processor->processData(inputData);
}
