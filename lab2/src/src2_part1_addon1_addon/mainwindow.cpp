#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode("Верхний регистр")
    , isProcessingEnabled(false)
{
    ui->setupUi(this);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::processText);
    connect(ui->modeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::updateMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processText() {
    isProcessingEnabled = true;

    QString inputText = ui->inputLineEdit->text();
    QString processedText;

    if (currentMode == "Верхний регистр") {
        processedText = inputText.toUpper();
    } else if (currentMode == "Нижний регистр") {
        processedText = inputText.toLower();
    } else if (currentMode == "Инвертирование") {
        std::reverse(inputText.begin(), inputText.end());
        processedText = inputText;
    } else if (currentMode == "Удаление пробелов") {
        processedText = inputText.remove(' ');
    }

    ui->resultLineEdit->setText(processedText);
}

void MainWindow::updateMode() {
    currentMode = ui->modeComboBox->currentText();
    if (isProcessingEnabled) {
        processText();
    }
}
