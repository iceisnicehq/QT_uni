#include "database.h"
#include <QDebug>
#include <QStandardPaths>

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

QVariantList Database::searchBooks(const QString &searchTerm)
{
    QVariantList books;
    if (!m_db.isOpen()) return books;

    QSqlQuery query;
    query.prepare("SELECT * FROM books WHERE title LIKE :search OR author LIKE :search OR genre LIKE :search ORDER BY title");
    query.bindValue(":search", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Search error:" << query.lastError();
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
