#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);
    openDialogButton = new QPushButton("Открыть диалог", this);
    outputLabel = new QLabel("Результат: ", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(processButton);
    layout->addWidget(openDialogButton);
    layout->addWidget(outputLabel);

    processor = new DataProcessor(this);
    dataDialog = new DataDialog(this);

    connect(processor, &DataProcessor::dataProcessed, this, &MainWindow::handleProcessedData);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
    connect(openDialogButton, &QPushButton::clicked, this, &MainWindow::openDataDialog);
    connect(dataDialog, &DataDialog::dataSubmitted, this, &MainWindow::handleDialogData);
}

void MainWindow::handleProcessedData(const QString &data) {
    outputLabel->setText("Результат: " + data);
}

void MainWindow::onProcessButtonClicked() {
    QString inputData = inputField->text();
    processor->processData(inputData);
}

void MainWindow::openDataDialog() {
    dataDialog->show();
}

void MainWindow::handleDialogData(const QString &data, const QString &processingType) {
    QString result;
    if (processingType == "Верхний регистр") {
        result = data.toUpper();
    } else if (processingType == "Добавить префикс") {
        result = "Префикс: " + data;
    } else if (processingType == "Логирование") {
        result = "Лог: " + data;
    }
    outputLabel->setText("Результат: " + result);
}
