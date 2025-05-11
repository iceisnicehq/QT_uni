#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QDateTime>
#include <QUrl>
#include <QCloseEvent>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DownloadTask : public QObject
{
    Q_OBJECT
public:
    explicit DownloadTask(const QString &url, QObject *parent = nullptr);
    ~DownloadTask();

public slots:
    void startDownload();

signals:
    void downloadProgress(int percent);
    void finished(const QString &url, const QByteArray &data);
    void error(const QString &url, const QString &error);

private:
    QString m_url;
    QNetworkAccessManager* m_manager;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addUrlButton_clicked();
    void on_downloadButton_clicked();
    void on_clearButton_clicked();
    void handleDownloadFinished(const QString &url, const QByteArray &data);
    void handleDownloadError(const QString &url, const QString &error);
    void handleDownloadProgress(int percent);
    void showUrlListContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QThreadPool m_threadPool;
    int m_activeDownloads;
    int m_totalDownloads;
    QMap<QString, QListWidgetItem*> m_urlItems;
    QList<QNetworkReply*> m_activeReplies;

    bool isValidUrl(const QString &url);
    void updateStatus();
    QString generateFileName(const QString &url) const;
    void updateUI(const QString &url, bool success);
};

#endif // MAINWINDOW_H
