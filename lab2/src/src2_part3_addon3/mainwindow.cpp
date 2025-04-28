#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);
    outputLabel = new QLabel("Результат: ", this);
    intermediateLabel1 = new QLabel("Промежуточный результат 1", this);
    intermediateLabel2 = new QLabel("Промежуточный результат 2", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(processButton);
    layout->addWidget(intermediateLabel1);
    layout->addWidget(intermediateLabel2);
    layout->addWidget(outputLabel);

    processor = new DataProcessor(this);
    advancedProcessor = new AdvancedDataProcessor(this);

    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
    connect(advancedProcessor, &AdvancedDataProcessor::upperCaseDone, this, &MainWindow::handleUpperCase);
    connect(advancedProcessor, &AdvancedDataProcessor::formatDone, this, &MainWindow::handleFormattedText);
    connect(advancedProcessor, &AdvancedDataProcessor::logDone, this, &MainWindow::handleFinalResult);
}

void MainWindow::handleUpperCase(const QString &data) {
    intermediateLabel1->setText("Промежуточный результат 1: " + data);
    advancedProcessor->formatText(data);
}

void MainWindow::handleFormattedText(const QString &data) {
    intermediateLabel2->setText("Промежуточный результат 2: " + data);
    advancedProcessor->logResult(data);
}

void MainWindow::handleFinalResult(const QString &data) {
    outputLabel->setText("Результат: " + data);
}

void MainWindow::onProcessButtonClicked() {
    QString inputData = inputField->text();
    advancedProcessor->toUpperCase(inputData);
}
