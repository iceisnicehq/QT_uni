#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings> // dop

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
    void on_addTaskButton_clicked();
    void on_deleteTaskButton_clicked();
    void on_detailsTaskButton_clicked();

private:
    Ui::MainWindow *ui;
    void saveTasks();    // dop2
    void loadTasks();    // dop2
};
#endif // MAINWINDOW_H
