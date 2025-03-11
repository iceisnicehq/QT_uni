#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::on_addTaskButton_clicked);
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &MainWindow::on_deleteTaskButton_clicked);
    connect(ui->detailsTaskButton, &QPushButton::clicked, this, &MainWindow::on_detailsTaskButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addTaskButton_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Добавить задачу");
    QVBoxLayout layout(&dialog);

    QLineEdit titleEdit;
    titleEdit.setPlaceholderText("Название задачи");
    layout.addWidget(&titleEdit);

    QTextEdit descriptionEdit;
    descriptionEdit.setPlaceholderText("Описание задачи");
    layout.addWidget(&descriptionEdit);

    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    layout.addWidget(&dateEdit);

    QPushButton addButton("Добавить");
    layout.addWidget(&addButton);

    connect(&addButton, &QPushButton::clicked, [&]() {
       QString title = titleEdit.text().trimmed();
       QString description = descriptionEdit.toPlainText().trimmed();
       QDate date = dateEdit.date();
       QListWidgetItem *newItem = new QListWidgetItem(title);
       newItem->setData(Qt::UserRole, description);
       newItem->setData(Qt::UserRole + 1, date);
       ui->tasksListWidget->addItem(newItem);
       dialog.accept();
    });

    dialog.exec();
}


void MainWindow::on_deleteTaskButton_clicked()
{
    QListWidgetItem *item = ui->tasksListWidget->currentItem();
    if (item) {
       QMessageBox msgBox(this);
       msgBox.setWindowTitle("Удаление задачи");
       msgBox.setText("Вы уверены, что хотите удалить задачу?");
       QPushButton* yesButton = msgBox.addButton(QMessageBox::Yes);
       QPushButton* noButton = msgBox.addButton(QMessageBox::No);
       yesButton->setText("Да");
       noButton->setText("Нет");
       msgBox.exec();
       if (msgBox.clickedButton() == yesButton) {
        delete item;
       }
    } else {
       QMessageBox::warning(this, "Удаление задачи", "Выберите задачу для удаления.");
    }
}


void MainWindow::on_detailsTaskButton_clicked()
{
    QListWidgetItem *item = ui->tasksListWidget->currentItem();
    if (item) {
       QString taskDetails = item->text();
       QString description = item->data(Qt::UserRole).toString();
       QDate taskDate = item->data(Qt::UserRole + 1).toDate();
       QString details = QString("<b>Задача:</b> %1\n<b>Описание:</b> %2\n<b>Дата выполнения:</b> %3")
        .arg(taskDetails)
        .arg(description)
        .arg(taskDate.toString("dd.MM.yyyy"));
       QMessageBox::information(this, "Детали задачи", details);
    } else {
       QMessageBox::warning(this, "Просмотр задачи", "Выберите задачу для просмотра.");
    }
}

