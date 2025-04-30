#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include "editbookdialog.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

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
    connect(ui->btnFilterAuthor, &QPushButton::clicked, this, &MainWindow::filterByAuthor);
    connect(ui->btnFilterGenre, &QPushButton::clicked, this, &MainWindow::filterByGenre);
    connect(ui->btnClearFilters, &QPushButton::clicked, this, &MainWindow::clearFilters);
    connect(ui->actionImportJSON, &QAction::triggered, this, &MainWindow::importJSON);
    connect(ui->actionExportJSON, &QAction::triggered, this, &MainWindow::exportJSON);
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

    QString author = model->item(index.row(), 0)->text();
    QString title = model->item(index.row(), 1)->text();
    int year = model->item(index.row(), 2)->text().toInt();
    QString genre = model->item(index.row(), 3)->text();

    EditBookDialog dialog(this);
    dialog.setBookData(author, title, year, genre);

    if (dialog.exec() == QDialog::Accepted) {
        model->setItem(index.row(), 0, new QStandardItem(dialog.getAuthor()));
        model->setItem(index.row(), 1, new QStandardItem(dialog.getTitle()));
        model->setItem(index.row(), 2, new QStandardItem(QString::number(dialog.getYear())));
        model->setItem(index.row(), 3, new QStandardItem(dialog.getGenre()));
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

            for (QString &field : fields) {
                if (field.startsWith('"') && field.endsWith('"')) {
                    field = field.mid(1, field.length() - 2); // quotes
                    field.replace("\"\"", "\""); // quotes
                }
            }

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
void MainWindow::setupSearch()
{
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::searchBooks);
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::sortByColumn);
}

void MainWindow::filterByAuthor()
{
    QString author = QInputDialog::getText(this, "Фильтр по автору", "Введите имя автора:");
    if (!author.isEmpty()) {
        proxyModel->setFilterKeyColumn(0); // Фильтрация по столбцу "Автор"
        proxyModel->setFilterFixedString(author);
    }
}

void MainWindow::filterByGenre()
{
    QString genre = QInputDialog::getText(this, "Фильтр по жанру", "Введите жанр:");
    if (!genre.isEmpty()) {
        proxyModel->setFilterKeyColumn(3); // Фильтрация по столбцу "Жанр"
        proxyModel->setFilterFixedString(genre);
    }
}

void MainWindow::clearFilters()
{
    proxyModel->setFilterKeyColumn(-1); // Сброс фильтрации
    proxyModel->setFilterFixedString("");
}

void MainWindow::sortByColumn(int column)
{
    proxyModel->sort(column, Qt::AscendingOrder);
}

void MainWindow::exportJSON()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт в JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QJsonArray booksArray;
    for (int row = 0; row < model->rowCount(); ++row) {
        QJsonObject bookObject;
        bookObject["author"] = model->item(row, 0)->text();
        bookObject["title"] = model->item(row, 1)->text();
        bookObject["year"] = model->item(row, 2)->text().toInt();
        bookObject["genre"] = model->item(row, 3)->text();
        booksArray.append(bookObject);
    }

    QJsonDocument doc(booksArray);
    file.write(doc.toJson());
    file.close();

    QMessageBox::information(this, "Экспорт", "Файл сохранён успешно!");
}

void MainWindow::importJSON()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Импорт JSON", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат JSON");
        return;
    }

    QJsonArray booksArray = doc.array();
    model->clear();
    setupModel();

    for (const QJsonValue &value : booksArray) {
        if (!value.isObject()) continue;

        QJsonObject bookObject = value.toObject();
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(bookObject["author"].toString())
                 << new QStandardItem(bookObject["title"].toString())
                 << new QStandardItem(QString::number(bookObject["year"].toInt()))
                 << new QStandardItem(bookObject["genre"].toString());

        model->appendRow(rowItems);
    }

    QMessageBox::information(this, "Импорт JSON", "Файл успешно загружен!");
}
