#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileSearcher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBrowseClicked();
    void onSearchClicked();
    void onResultFound(const QString &filePath);
    void onSearchFinished();
    void updateProgress(int value);
    void onClearClicked();

private:
    Ui::MainWindow *ui;
    QThreadPool m_threadPool;
    FileSearcher *m_searcher = nullptr;
    QFutureWatcher<void> m_watcher;

    void setupConnections();
    void resetUI();
};

#endif // MAINWINDOW_H
