/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *inputLineEdit;
    QPushButton *processButton;
    QComboBox *modeComboBox;
    QLineEdit *resultLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(392, 266);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputLineEdit = new QLineEdit(centralwidget);
        inputLineEdit->setObjectName("inputLineEdit");
        inputLineEdit->setGeometry(QRect(70, 100, 191, 25));
        processButton = new QPushButton(centralwidget);
        processButton->setObjectName("processButton");
        processButton->setGeometry(QRect(70, 20, 191, 31));
        modeComboBox = new QComboBox(centralwidget);
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->setObjectName("modeComboBox");
        modeComboBox->setGeometry(QRect(70, 60, 191, 21));
        resultLineEdit = new QLineEdit(centralwidget);
        resultLineEdit->setObjectName("resultLineEdit");
        resultLineEdit->setEnabled(true);
        resultLineEdit->setGeometry(QRect(70, 150, 191, 25));
        resultLineEdit->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 392, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        processButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214", nullptr));
        modeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\205\320\275\320\270\320\271 \321\200\320\265\320\263\320\270\321\201\321\202\321\200", nullptr));
        modeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\235\320\270\320\266\320\275\320\270\320\271 \321\200\320\265\320\263\320\270\321\201\321\202\321\200", nullptr));
        modeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "\320\230\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        modeComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\265\320\275\320\270\320\265 \320\277\321\200\320\276\320\261\320\265\320\273\320\276\320\262", nullptr));

        resultLineEdit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
