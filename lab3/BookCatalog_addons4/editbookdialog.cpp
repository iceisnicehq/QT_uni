#include "editbookdialog.h"
#include "ui_editbookdialog.h"
#include <QMessageBox>

EditBookDialog::EditBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditBookDialog::validateInput);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditBookDialog::reject);

}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}

void EditBookDialog::setBookData(const QString &author, const QString &title, int year, const QString &genre, const QString &publisher, const QString &isbn, int pages)
{
    ui->lineEditAuthor->setText(author);
    ui->lineEditTitle->setText(title);
    ui->spinBoxYear->setValue(year);
    ui->lineEditGenre->setText(genre);
    ui->lineEditPublisher->setText(publisher);
    ui->lineEditISBN->setText(isbn);
    ui->spinBoxPages->setValue(pages);
}

QString EditBookDialog::getAuthor() const
{
    return ui->lineEditAuthor->text();
}

QString EditBookDialog::getTitle() const
{
    return ui->lineEditTitle->text();
}

int EditBookDialog::getYear() const
{
    return ui->spinBoxYear->value();
}

QString EditBookDialog::getGenre() const
{
    return ui->lineEditGenre->text();
}

QString EditBookDialog::getPublisher() const
{
    return ui->lineEditPublisher->text();
}

QString EditBookDialog::getISBN() const
{
    return ui->lineEditISBN->text();
}

int EditBookDialog::getPages() const
{
    return ui->spinBoxPages->value();
}

void EditBookDialog::validateInput()
{
    if (ui->lineEditAuthor->text().isEmpty() || ui->lineEditTitle->text().isEmpty() || ui->lineEditGenre->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    accept();
}

