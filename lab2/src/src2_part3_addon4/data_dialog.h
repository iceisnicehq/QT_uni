#ifndef DATA_DIALOG_H
#define DATA_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class DataDialog : public QDialog {
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = nullptr);

signals:
    void dataSubmitted(const QString &data, const QString &processingType);

private slots:
    void onSubmitButtonClicked();

private:
    QLineEdit *inputField;
    QComboBox *processingTypeComboBox;
    QPushButton *submitButton;
};

#endif // DATA_DIALOG_H
