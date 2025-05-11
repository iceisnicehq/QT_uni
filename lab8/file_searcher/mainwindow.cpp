#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesearcher.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnections();
    resetUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupConnections()
{
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
}

void MainWindow::onBrowseClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Выбрать директорию"), QDir::homePath());
    if (!dir.isEmpty()) ui->directoryEdit->setText(dir);
}

void MainWindow::onSearchClicked()
{
    ui->resultList->clear();
    if (m_searcher)
        return;

    QString rootDir = ui->directoryEdit->text();
    if (rootDir.isEmpty() || !QDir(rootDir).exists()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Укажите корректную директорию"));
        return;
    }

    m_searcher = new FileSearcher(this);

    // Считаем общее количество файлов
    int totalFiles = m_searcher->countFiles(QDir(rootDir));
    ui->progressBar->setMaximum(totalFiles > 0 ? totalFiles : 1);

    connect(m_searcher, &FileSearcher::resultFound, this, &MainWindow::onResultFound);
    connect(m_searcher, &FileSearcher::progressUpdated, this, &MainWindow::updateProgress);
    connect(m_searcher, &FileSearcher::finished, this, &MainWindow::onSearchFinished);

    QtConcurrent::run(&m_threadPool, [this, rootDir]() {
        m_searcher->search(
            rootDir,
            ui->extensionEdit->text(),
            ui->contentEdit->text(),
            ui->minSizeSpin->value() * 1024,   // KB to bytes
            ui->maxSizeSpin->value() * 1024
        );
    });
}

void MainWindow::onResultFound(const QString &filePath)
{
    ui->resultList->addItem(filePath);
}

void MainWindow::onSearchFinished()
{
    m_searcher->deleteLater();
    m_searcher = nullptr;
    ui->statusLabel->setText(
        tr("Поиск завершен. Найдено: %1 файлов").arg(ui->resultList->count())
    );
}

void MainWindow::updateProgress(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::resetUI()
{
    ui->progressBar->setValue(0);
    ui->resultList->clear();
    ui->statusLabel->setText(tr("Готово"));
}

void MainWindow::onClearClicked()
{
    ui->extensionEdit->clear();
    ui->contentEdit->clear();
    ui->minSizeSpin->setValue(0);
    ui->maxSizeSpin->setValue(0);

    resetUI();
}
