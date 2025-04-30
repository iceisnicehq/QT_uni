#ifndef EDITBOOKDIALOG_H
#define EDITBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class EditBookDialog;
}

class EditBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBookDialog(QWidget *parent = nullptr);
    ~EditBookDialog();

    void setBookData(const QString &author, const QString &title, int year, const QString &genre, const QString &publisher, const QString &isbn, int pages);
    QString getAuthor() const;
    QString getTitle() const;
    int getYear() const;
    QString getGenre() const;
    QString getPublisher() const;
    QString getISBN() const;
    int getPages() const;

private slots:
    void validateInput();

private:
    Ui::EditBookDialog *ui;
};

#endif // EDITBOOKDIALOG_H
