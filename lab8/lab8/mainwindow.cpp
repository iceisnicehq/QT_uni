#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QThread>
#include <QDir>
#include <QMimeData>

DownloadTask::DownloadTask(const QString &url, QObject *parent)
    : QObject(parent), m_url(url), m_manager(nullptr)
{
    setProperty("url", url);
}

DownloadTask::~DownloadTask()
{
    delete m_manager;
}

void DownloadTask::startDownload()
{
    m_manager = new QNetworkAccessManager(this);

    QNetworkRequest request(m_url);
    request.setRawHeader("Accept", "image/jpeg,image/png,image/*;q=0.8");
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                       QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkReply *reply = m_manager->get(request);

    connect(reply, &QNetworkReply::downloadProgress, [this](qint64 bytesReceived, qint64 bytesTotal) {
        int percent = bytesTotal > 0 ? static_cast<int>((bytesReceived * 100) / bytesTotal) : 0;
        emit downloadProgress(percent);
    });

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if(reply->error() != QNetworkReply::NoError) {
            emit error(m_url, reply->errorString());
            reply->deleteLater();
            return;
        }

        QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
        if(!contentType.contains("image/")) {
            emit error(m_url, "Invalid content type: " + contentType);
            reply->deleteLater();
            return;
        }

        emit finished(m_url, reply->readAll());
        reply->deleteLater();
    });
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_activeDownloads(0), m_totalDownloads(0)
{
    ui->setupUi(this);
    m_threadPool.setMaxThreadCount(4);
    ui->progressBar->setValue(0);
    ui->statusLabel->setText("Ready");

    setAcceptDrops(true);
    ui->urlList->setDragEnabled(true);
    ui->urlList->setDropIndicatorShown(true);
    ui->urlList->setDragDropMode(QAbstractItemView::InternalMove);
    ui->urlList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->urlList, &QListWidget::customContextMenuRequested,
            this, &MainWindow::showUrlListContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isValidUrl(const QString &url)
{
    QUrl qurl(url);
    return qurl.isValid() && !qurl.scheme().isEmpty() && !qurl.host().isEmpty();
}

void MainWindow::on_addUrlButton_clicked()
{
    QString url = ui->urlEdit->text().trimmed();
    if(url.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter image URL");
        return;
    }

    if(!url.startsWith("http://") && !url.startsWith("https://")) {
        url.prepend("http://");
    }

    if(!isValidUrl(url)) {
        QMessageBox::warning(this, "Error", "Invalid URL format");
        return;
    }

    if(ui->urlList->count() >= 100) {
        QMessageBox::warning(this, "Error", "Maximum 100 URLs allowed");
        return;
    }

    if(!m_urlItems.contains(url)) {
        QListWidgetItem *item = new QListWidgetItem(url);
        item->setData(Qt::UserRole, url);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        ui->urlList->addItem(item);
        m_urlItems.insert(url, item);
        ui->urlEdit->clear();
    }
}

void MainWindow::on_downloadButton_clicked()
{
    if(ui->urlList->count() == 0) {
        QMessageBox::warning(this, "Error", "Please add at least one URL");
        return;
    }

    m_activeDownloads = 0;
    m_totalDownloads = 0;
    m_activeReplies.clear();

    for(int i = 0; i < ui->urlList->count(); ++i) {
        if(ui->urlList->item(i)->checkState() == Qt::Checked) {
            m_totalDownloads++;
        }
    }

    if(m_totalDownloads == 0) {
        QMessageBox::warning(this, "Error", "No URLs selected for download");
        return;
    }

    ui->progressBar->setMaximum(m_totalDownloads * 100);
    ui->progressBar->setValue(0);
    ui->statusLabel->setText(QString("Downloading: 0/%1").arg(m_totalDownloads));

    for(int i = 0; i < ui->urlList->count(); ++i) {
        QListWidgetItem *item = ui->urlList->item(i);
        if(item->checkState() == Qt::Checked) {
            QString url = item->data(Qt::UserRole).toString();
            DownloadTask *task = new DownloadTask(url);

            QThread *thread = new QThread;
            task->moveToThread(thread);

            connect(thread, &QThread::started, task, &DownloadTask::startDownload);
            connect(task, &DownloadTask::finished, this, &MainWindow::handleDownloadFinished);
            connect(task, &DownloadTask::error, this, &MainWindow::handleDownloadError);
            connect(task, &DownloadTask::downloadProgress, this, &MainWindow::handleDownloadProgress);

            connect(task, &DownloadTask::finished, thread, &QThread::quit);
            connect(task, &DownloadTask::error, thread, &QThread::quit);
            connect(thread, &QThread::finished, thread, &QThread::deleteLater);
            connect(thread, &QThread::finished, task, &DownloadTask::deleteLater);

            m_activeDownloads++;
            thread->start();
        }
    }
}

void MainWindow::handleDownloadProgress(int percent)
{
    Q_UNUSED(percent);
    if (ui->progressBar->value() < ui->progressBar->maximum()) {
        ui->progressBar->setValue(ui->progressBar->value() + 1);
    }
}

void MainWindow::handleDownloadFinished(const QString &url, const QByteArray &data)
{
    QImage image;
    if(!image.loadFromData(data)) {
        if(data.startsWith("<html") || data.startsWith("<?xml")) {
            handleDownloadError(url, "Server returned HTML instead of image");
            return;
        }
        handleDownloadError(url, "Invalid image data");
        return;
    }

    QString defaultDir = QDir::homePath() + "/Downloads/Images/";
    QDir().mkpath(defaultDir);

    QString fileName = generateFileName(url);
    QString savePath = QFileDialog::getSaveFileName(this, "Save Image",
                                                  defaultDir + fileName,
                                                  "Images (*.jpg *.png *.bmp)");

    if(!savePath.isEmpty()) {
        QFile file(savePath);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(data);
            file.close();
            updateUI(url, true);
        } else {
            handleDownloadError(url, "Failed to save file: " + file.errorString());
        }
    }
    m_activeDownloads--;
    updateStatus();
}

void MainWindow::handleDownloadError(const QString &url, const QString &error)
{
    QListWidgetItem *item = m_urlItems.value(url);
    if(item) {
        item->setCheckState(Qt::Unchecked);
        item->setBackground(QBrush(QColor(255, 200, 200)));
        item->setToolTip(error);
    }
    m_activeDownloads--;
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completed = m_totalDownloads - m_activeDownloads;
    ui->statusLabel->setText(QString("Downloading: %1/%2").arg(completed).arg(m_totalDownloads));
    ui->progressBar->setValue(completed * 100);

    if(m_activeDownloads == 0) {
        ui->statusLabel->setText("All downloads completed");
        m_activeReplies.clear();
    }
}

QString MainWindow::generateFileName(const QString &url) const
{
    QString fileName = QFileInfo(url).fileName();
    if(fileName.isEmpty()) {
        fileName = QString("image_%1.jpg").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    }
    return fileName;
}

void MainWindow::updateUI(const QString &url, bool success)
{
    QListWidgetItem *item = m_urlItems.value(url);
    if(item) {
        item->setCheckState(Qt::Unchecked);
        item->setBackground(QBrush(success ? QColor(200, 255, 200) : QColor(255, 200, 200)));
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->urlList->clear();
    m_urlItems.clear();
    ui->progressBar->setValue(0);
    ui->statusLabel->setText("Ready");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach(const QUrl &url, event->mimeData()->urls()) {
        QString urlString = url.toString();
        if(!m_urlItems.contains(urlString)) {
            QListWidgetItem *item = new QListWidgetItem(urlString);
            item->setData(Qt::UserRole, urlString);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Checked);
            ui->urlList->addItem(item);
            m_urlItems.insert(urlString, item);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_activeDownloads > 0) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Downloads in progress",
            "There are active downloads. Do you want to cancel them and exit?",
            QMessageBox::Yes|QMessageBox::No);

        if(reply == QMessageBox::No) {
            event->ignore();
            return;
        }
    }
    event->accept();
}

void MainWindow::showUrlListContextMenu(const QPoint &pos)
{
    QMenu menu;
    QAction *removeAction = menu.addAction("Remove selected");
    QAction *selectAllAction = menu.addAction("Select all");
    QAction *deselectAllAction = menu.addAction("Deselect all");

    QAction *selectedAction = menu.exec(ui->urlList->viewport()->mapToGlobal(pos));

    if(selectedAction == removeAction) {
        qDeleteAll(ui->urlList->selectedItems());
    } else if(selectedAction == selectAllAction) {
        for(int i = 0; i < ui->urlList->count(); ++i)
            ui->urlList->item(i)->setCheckState(Qt::Checked);
    } else if(selectedAction == deselectAllAction) {
        for(int i = 0; i < ui->urlList->count(); ++i)
            ui->urlList->item(i)->setCheckState(Qt::Unchecked);
    }
}
