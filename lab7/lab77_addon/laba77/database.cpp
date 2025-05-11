#include "database.h"
#include <QDebug>
#include <QStandardPaths>
#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxformat.h"

Database::Database(QObject *parent) : QObject(parent)
{
}

Database::~Database()
{
    closeDatabase();
}

bool Database::connectToDatabase(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void Database::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool Database::addBook(const QString &title, const QString &author, int year, const QString &genre, bool available)
{
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO books (title, author, year, genre, available) "
                  "VALUES (:title, :author, :year, :genre, :available)");
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":year", year);
    query.bindValue(":genre", genre);
    query.bindValue(":available", available);

    if (!query.exec()) {
        qDebug() << "Add book error:" << query.lastError();
        return false;
    }
    return true;
}

bool Database::updateBook(int id, const QString &title, const QString &author, int year, const QString &genre, bool available)
{
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("UPDATE books SET title = :title, author = :author, year = :year, "
                  "genre = :genre, available = :available WHERE id = :id");
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":year", year);
    query.bindValue(":genre", genre);
    query.bindValue(":available", available);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Update book error:" << query.lastError();
        return false;
    }
    return true;
}

bool Database::deleteBook(int id)
{
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM books WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete book error:" << query.lastError();
        return false;
    }
    return true;
}

QVariantList Database::getAllBooks()
{
    QVariantList books;
    if (!m_db.isOpen()) return books;

    QSqlQuery query("SELECT * FROM books ORDER BY title");
    while (query.next()) {
        QVariantMap book;
        book["id"] = query.value("id");
        book["title"] = query.value("title");
        book["author"] = query.value("author");
        book["year"] = query.value("year");
        book["genre"] = query.value("genre");
        book["available"] = query.value("available");
        books.append(book);
    }
    return books;
}

QVariantList Database::searchBooksCombined(
    const QString &author,
    const QString &genre,
    int yearFrom,
    int yearTo,
    int availabilityFilter)
{
    QVariantList books;
    if (!m_db.isOpen()) return books;

    QString queryStr = "SELECT * FROM books WHERE 1=1";
    QVariantList params;

    if (!author.isEmpty()) {
        queryStr += " AND author LIKE ?";
        params.append("%" + author + "%");
    }

    if (!genre.isEmpty()) {
        queryStr += " AND genre LIKE ?";
        params.append("%" + genre + "%");
    }

    if (yearFrom > 0) {
        queryStr += " AND year >= ?";
        params.append(yearFrom);
    }
    if (yearTo > 0) {
        queryStr += " AND year <= ?";
        params.append(yearTo);
    }

    switch (availabilityFilter) {
    case 1:
        queryStr += " AND available = 1";
        break;
    case 2:
        queryStr += " AND available = 0";
        break;
    }

    queryStr += " ORDER BY title";

    QSqlQuery query;
    query.prepare(queryStr);

    for (const auto &param : params) {
        query.addBindValue(param);
    }

    if (!query.exec()) {
        qDebug() << "Combined search error:" << query.lastError();
        return books;
    }

    while (query.next()) {
        QVariantMap book;
        book["id"] = query.value("id");
        book["title"] = query.value("title");
        book["author"] = query.value("author");
        book["year"] = query.value("year");
        book["genre"] = query.value("genre");
        book["available"] = query.value("available");
        books.append(book);
    }
    return books;
}

QVariantList Database::getAvailableBooks(const QString &searchTerm)
{
    QVariantList books;
    if (!m_db.isOpen()) return books;

    QSqlQuery query;

    if (searchTerm.isEmpty()) {
        query.prepare("SELECT * FROM books WHERE available = 1 ORDER BY title");
    } else {
        query.prepare("SELECT * FROM books WHERE available = 1 AND "
                     "(title LIKE :search OR author LIKE :search OR genre LIKE :search) "
                     "ORDER BY title");
        query.bindValue(":search", "%" + searchTerm + "%");
    }

    if (!query.exec()) {
        qDebug() << "Get available books error:" << query.lastError();
        return books;
    }

    while (query.next()) {
        QVariantMap book;
        book["id"] = query.value("id");
        book["title"] = query.value("title");
        book["author"] = query.value("author");
        book["year"] = query.value("year");
        book["genre"] = query.value("genre");
        book["available"] = query.value("available");
        books.append(book);
    }
    return books;
}

bool Database::exportToExcel(const QString &filePath)
{
    if (!m_db.isOpen()) return false;

    QXlsx::Document xlsx;
    xlsx.write("A1", "ID");
    xlsx.write("B1", "Название");
    xlsx.write("C1", "Автор");
    xlsx.write("D1", "Год");
    xlsx.write("E1", "Жанр");
    xlsx.write("F1", "Доступна");

    QSqlQuery query("SELECT * FROM books ORDER BY title");
    int row = 2;
    while (query.next()) {
        xlsx.write(row, 1, query.value("id"));
        xlsx.write(row, 2, query.value("title"));
        xlsx.write(row, 3, query.value("author"));
        xlsx.write(row, 4, query.value("year"));
        xlsx.write(row, 5, query.value("genre"));
        xlsx.write(row, 6, query.value("available").toBool() ? "Да" : "Нет");
        ++row;
    }

    return xlsx.saveAs(filePath);
}

QVariantList Database::getAllReaders() {
    QVariantList readers;
    if (!m_db.isOpen()) return readers;

    QSqlQuery query("SELECT * FROM readers ORDER BY name");
    while (query.next()) {
        readers.append(QVariantMap{
            {"id", query.value("id")},
            {"name", query.value("name")},
            {"contact", query.value("contact")}
        });
    }
    return readers;
}

bool Database::addReader(const QString &name, const QString &contact) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO readers (name, contact) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(contact);
    if (!query.exec()) {
        qDebug() << "Add reader error:" << query.lastError();
        return false;
    }
    return true;
}

bool Database::deleteReader(int id) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM readers WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Delete book error:" << query.lastError();
        return false;
    }
    return true;
}

bool Database::updateReader(int id, const QString &name, const QString &contact)
{
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("UPDATE readers SET name = ?, contact = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(contact);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Update reader error:" << query.lastError();
        return false;
    }

    return true;
}

bool Database::issueBook(int bookId, int readerId) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO loans (book_id, reader_id, issue_date) VALUES (?, ?, datetime('now'))");
    query.addBindValue(bookId);
    query.addBindValue(readerId);
    if (!query.exec()) {
        qDebug() << "Issue book error:" << query.lastError();
        return false;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE books SET available = 0 WHERE id = ?");
    updateQuery.addBindValue(bookId);

    return true;
}

bool Database::returnBook(int loanId) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("UPDATE loans SET return_date = datetime('now') WHERE id = ?");
    query.addBindValue(loanId);
    if (!query.exec()) {
        qDebug() << "Return book error:" << query.lastError();
        return false;
    }

    QSqlQuery bookQuery("SELECT book_id FROM loans WHERE id = " + QString::number(loanId));
    if (bookQuery.next()) {
        int bookId = bookQuery.value(0).toInt();
        QSqlQuery updateBook;
        updateBook.prepare("UPDATE books SET available = 1 WHERE id = ?");
        updateBook.addBindValue(bookId);
        updateBook.exec();
    }

    return true;
}

QVariantList Database::getAllLoans() {
    QVariantList loans;
    if (!m_db.isOpen()) return loans;

    QSqlQuery query("SELECT loans.id, books.title, readers.name, loans.issue_date, loans.return_date "
                    "FROM loans "
                    "JOIN books ON loans.book_id = books.id "
                    "JOIN readers ON loans.reader_id = readers.id "
                    "ORDER BY loans.issue_date DESC");

    while (query.next()) {
        QVariantMap record;
        record["id"] = query.value("id");
        record["bookTitle"] = query.value("title");
        record["readerName"] = query.value("name");
        record["issueDate"] = query.value("issue_date");
        record["returnDate"] = query.value("return_date");
        loans.append(record);
    }

    return loans;
}
