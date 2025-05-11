#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    bool connectToDatabase(const QString &path);
    void closeDatabase();

    Q_INVOKABLE bool addBook(const QString &title, const QString &author, int year, const QString &genre, bool available);
    Q_INVOKABLE bool updateBook(int id, const QString &title, const QString &author, int year, const QString &genre, bool available);
    Q_INVOKABLE bool deleteBook(int id);
    Q_INVOKABLE QVariantList getAllBooks();
    Q_INVOKABLE QVariantList searchBooks(const QString &searchTerm);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
