#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupModel();
    setupSearch();

    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::addBook);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::editBook);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::removeBook);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchBooks);
    connect(ui->actionImportCSV, &QAction::triggered, this, &MainWindow::importCSV);
    connect(ui->actionExportCSV, &QAction::triggered, this, &MainWindow::exportCSV);
    connect(ui->actionExit, &QAction::triggered, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "Автор");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Год");
    model->setHeaderData(3, Qt::Horizontal, "Жанр");

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);

    ui->tableView->setModel(proxyModel);
}

void MainWindow::addBook()
{
    QString author = QInputDialog::getText(this, "Добавить книгу", "Автор:");
    if (author.isEmpty()) return;

    QString title = QInputDialog::getText(this, "Добавить книгу", "Название:");
    if (title.isEmpty()) return;

    int year = QInputDialog::getInt(this, "Добавить книгу", "Год издания:", 2000, 0, 2100);

    QString genre = QInputDialog::getText(this, "Добавить книгу", "Жанр:");
    if (genre.isEmpty()) return;

    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(author)
             << new QStandardItem(title)
             << new QStandardItem(QString::number(year))
             << new QStandardItem(genre);

    model->appendRow(rowItems);
}

void MainWindow::editBook()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для редактирования");
        return;
    }

    QString newText = QInputDialog::getText(this, "Редактировать книгу", "Новое значение:", QLineEdit::Normal, model->item(index.row(), index.column())->text());
    if (!newText.isEmpty()) {
        model->setItem(index.row(), index.column(), new QStandardItem(newText));
    }
}

void MainWindow::removeBook()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Выберите книгу для удаления");
        return;
    }

    model->removeRow(index.row());
}

void MainWindow::setupSearch()
{
}

void MainWindow::searchBooks()
{
    QString searchText = ui->searchLineEdit->text();
    proxyModel->setFilterFixedString(searchText);
}

void MainWindow::exportCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт в CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) {

        return;
    }

    if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        fileName += ".csv";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream out(&file);

    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList fields;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->item(row, col)->text();
            text.replace("\"", "\"\"");
            fields.append('"' + text + '"');
        }
        out << fields.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Экспорт", "Файл сохранён успешно!");
}

void MainWindow::importCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Импорт CSV", "", "CSV Files (*.csv)");
        if (fileName.isEmpty()) {

            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
            return;
        }

        QTextStream in(&file);
        model->clear();
        setupModel();

        int rowCount = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");

            if (fields.size() != 4) {
                continue;
            }

            QList<QStandardItem *> rowItems;
            for (const QString &field : fields)
                rowItems.append(new QStandardItem(field.trimmed()));

            model->appendRow(rowItems);
            rowCount++;
        }

        file.close();

        if (rowCount == 0) {
            QMessageBox::information(this, "Импорт CSV", "Файл загружен, но он пуст.");
        } else {
            QMessageBox::information(this, "Импорт CSV", "Файл успешно загружен: " + fileName);
        }
}
