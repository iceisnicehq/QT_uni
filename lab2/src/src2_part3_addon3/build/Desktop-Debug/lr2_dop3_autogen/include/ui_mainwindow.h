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
#include <QtWidgets/QLabel>
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
    QLabel *resultLabel;
    QLabel *intermediateLabel1;
    QLabel *intermediateLabel2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(384, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputLineEdit = new QLineEdit(centralwidget);
        inputLineEdit->setObjectName("inputLineEdit");
        inputLineEdit->setGeometry(QRect(50, 100, 281, 25));
        processButton = new QPushButton(centralwidget);
        processButton->setObjectName("processButton");
        processButton->setGeometry(QRect(100, 40, 171, 51));
        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(50, 140, 281, 17));
        intermediateLabel1 = new QLabel(centralwidget);
        intermediateLabel1->setObjectName("intermediateLabel1");
        intermediateLabel1->setGeometry(QRect(50, 170, 281, 17));
        intermediateLabel2 = new QLabel(centralwidget);
        intermediateLabel2->setObjectName("intermediateLabel2");
        intermediateLabel2->setGeometry(QRect(50, 200, 281, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 384, 22));
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
        processButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\205\320\275\320\270\320\271 \321\200\320\265\320\263\320\270\321\201\321\202\321\200", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        intermediateLabel1->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\274\320\265\320\266\321\203\321\202\320\276\321\207\320\275\321\213\320\271 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 1", nullptr));
        intermediateLabel2->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\274\320\265\320\266\321\203\321\202\320\276\321\207\320\275\321\213\320\271 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
