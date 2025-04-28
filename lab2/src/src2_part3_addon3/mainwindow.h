#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "data_processor.h"
#include "advanced_data_processor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void handleUpperCase(const QString &data);
    void handleFormattedText(const QString &data);
    void handleFinalResult(const QString &data);
    void onProcessButtonClicked();

private:
    QLineEdit *inputField;
    QLabel *outputLabel;
    QLabel *intermediateLabel1;
    QLabel *intermediateLabel2;
    QPushButton *processButton;
    DataProcessor *processor;
    AdvancedDataProcessor *advancedProcessor;
};

#endif // MAINWINDOW_H
