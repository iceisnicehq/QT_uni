#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "data_processor.h"
#include "data_dialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void handleProcessedData(const QString &data);
    void onProcessButtonClicked();
    void openDataDialog();
    void handleDialogData(const QString &data, const QString &processingType);

private:
    QLineEdit *inputField;
    QLabel *outputLabel;
    QPushButton *processButton;
    QPushButton *openDialogButton;
    DataProcessor *processor;
    DataDialog *dataDialog;
};

#endif // MAINWINDOW_H
