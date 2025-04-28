#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QDate>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::processVariant);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processVariant() {
    QString inputText = ui->inputLineEdit->text();
    QVariant var;
    bool isInt, isDouble, isBool;

    // Check for integer
    int intValue = inputText.toInt(&isInt);

    // Check for double
    double doubleValue = inputText.toDouble(&isDouble);

    // Check for boolean
    if (inputText.compare("true", Qt::CaseInsensitive) == 0 || inputText.compare("false", Qt::CaseInsensitive) == 0) {
        isBool = true;
    } else {
        isBool = false;
    }

    // Check for date
    QDate dateValue = QDate::fromString(inputText, "dd.MM.yyyy");
    if (!dateValue.isValid()) {
        dateValue = QDate::fromString(inputText, "dd-MM-yyyy");
    }
    if (!dateValue.isValid()) {
        dateValue = QDate::fromString(inputText, "dd/MM/yyyy");
    }

    // Assign QVariant based on input type
    if (isInt) {
        var = intValue;
    } else if (isDouble) {
        var = doubleValue;
    } else if (isBool) {
        var = (inputText.compare("true", Qt::CaseInsensitive) == 0);
    } else if (dateValue.isValid()) {
        var = dateValue;
    } else {
        var = inputText;
    }

    // Process the QVariant and display the result
    QString resultText = processVariantValue(var);
    ui->resultLabel->setText(resultText);
}

QString MainWindow::processVariantValue(const QVariant &var) {
    QString resultText;

    if (var.type() == QVariant::Int) {
        resultText = "Целое число: " + QString::number(var.toInt() * 2);
    } else if (var.type() == QVariant::Double) {
        resultText = "Вещественное число: " + QString::number(var.toDouble(), 'f', 2);
    } else if (var.type() == QVariant::Bool) {
        resultText = "Логическое значение: " + QString(var.toBool() ? "false" : "true");
    } else if (var.type() == QVariant::Date) {
        resultText = "Дата: " + var.toDate().toString("dd.MM.yyyy");
    } else {
        resultText = "Строка: " + var.toString();
    }

    return resultText;
}
