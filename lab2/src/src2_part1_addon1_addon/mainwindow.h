#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processText();
    void updateMode();

private:
    Ui::MainWindow *ui;
    QString currentMode;
    bool isProcessingEnabled; // Flag
};

#endif // MAINWINDOW_H
