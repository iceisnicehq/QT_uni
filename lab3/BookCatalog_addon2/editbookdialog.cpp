#include "editbookdialog.h"
#include "ui_editbookdialog.h"
#include <QMessageBox>

EditBookDialog::EditBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBookDialog)
{
    ui->setupUi(this);

    // Connect validation to the OK button
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditBookDialog::validateInput);
}

EditBookDialog::~EditBookDialog()
{
    delete ui;
}

void EditBookDialog::setBookData(const QString &author, const QString &title, int year, const QString &genre)
{
    ui->lineEditAuthor->setText(author);
    ui->lineEditTitle->setText(title);
    ui->spinBoxYear->setValue(year);
    ui->lineEditGenre->setText(genre);
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

void EditBookDialog::validateInput()
{
    if (ui->lineEditAuthor->text().isEmpty() || ui->lineEditTitle->text().isEmpty() || ui->lineEditGenre->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    accept();
}
