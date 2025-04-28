#include "data_dialog.h"
#include <QVBoxLayout>

DataDialog::DataDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Обработка данных");

    inputField = new QLineEdit(this);
    processingTypeComboBox = new QComboBox(this);
    submitButton = new QPushButton("Отправить", this);

    processingTypeComboBox->addItems({"Верхний регистр", "Добавить префикс", "Логирование"});

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(inputField);
    layout->addWidget(processingTypeComboBox);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &DataDialog::onSubmitButtonClicked);
}

void DataDialog::onSubmitButtonClicked() {
    QString data = inputField->text();
    QString processingType = processingTypeComboBox->currentText();
    emit dataSubmitted(data, processingType);
    close();
}
