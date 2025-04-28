#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings> // dop

//qfile
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTasks(); // dop
}

MainWindow::~MainWindow()
{
    saveTasks(); // dop
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

        // Проверка на пустое название
        if (title.isEmpty()) {
            QMessageBox::warning(&dialog, "Ошибка", "Название задачи не может быть пустым!");
            return;
        }

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
// dops
// // Сохранение задач ================================================
// void MainWindow::saveTasks()
// {
//     QSettings settings;
//     settings.beginWriteArray("tasks");

//     for (int i = 0; i < ui->tasksListWidget->count(); ++i) {
//         settings.setArrayIndex(i);
//         QListWidgetItem *item = ui->tasksListWidget->item(i);
//         settings.setValue("title", item->text());
//         settings.setValue("description", item->data(Qt::UserRole));
//         settings.setValue("date", item->data(Qt::UserRole + 1));
//     }

//     settings.endArray();
// }
void MainWindow::saveTasks()
{
    QFile file("tasks.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для сохранения задач.");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < ui->tasksListWidget->count(); ++i) {
        QListWidgetItem *item = ui->tasksListWidget->item(i);
        QString title = item->text();
        QString description = item->data(Qt::UserRole).toString();
        QDate date = item->data(Qt::UserRole + 1).toDate();

        // Сохраняем данные в формате: Название|Описание|Дата
        out << title << "|" << description << "|" << date.toString("dd.MM.yyyy") << "\n";
    }

    file.close();
}

// Загрузка задач ==================================================
// void MainWindow::loadTasks()
// {
//     QSettings settings;
//     int size = settings.beginReadArray("tasks");

//     for (int i = 0; i < size; ++i) {
//         settings.setArrayIndex(i);
//         QListWidgetItem *item = new QListWidgetItem(settings.value("title").toString());
//         item->setData(Qt::UserRole, settings.value("description"));
//         item->setData(Qt::UserRole + 1, settings.value("date"));
//         ui->tasksListWidget->addItem(item);
//     }

//     settings.endArray();
// }

void MainWindow::loadTasks()
{
    QFile file("tasks.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для загрузки задач.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");

        if (parts.size() == 3) {
            QString title = parts[0];
            QString description = parts[1];
            QDate date = QDate::fromString(parts[2], "dd.MM.yyyy");

            QListWidgetItem *item = new QListWidgetItem(title);
            item->setData(Qt::UserRole, description);
            item->setData(Qt::UserRole + 1, date);
            ui->tasksListWidget->addItem(item);
        }
    }

    file.close();
}