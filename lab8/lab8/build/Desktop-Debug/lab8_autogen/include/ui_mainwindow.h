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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *urlEdit;
    QPushButton *addUrlButton;
    QListWidget *urlList;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *downloadButton;
    QPushButton *clearButton;
    QProgressBar *progressBar;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        urlEdit = new QLineEdit(centralwidget);
        urlEdit->setObjectName("urlEdit");

        horizontalLayout->addWidget(urlEdit);

        addUrlButton = new QPushButton(centralwidget);
        addUrlButton->setObjectName("addUrlButton");

        horizontalLayout->addWidget(addUrlButton);


        verticalLayout->addLayout(horizontalLayout);

        urlList = new QListWidget(centralwidget);
        urlList->setObjectName("urlList");

        verticalLayout->addWidget(urlList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        downloadButton = new QPushButton(centralwidget);
        downloadButton->setObjectName("downloadButton");

        horizontalLayout_2->addWidget(downloadButton);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");

        horizontalLayout_2->addWidget(clearButton);


        verticalLayout->addLayout(horizontalLayout_2);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\321\207\320\270\320\272 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\271", nullptr));
        urlEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 URL \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217", nullptr));
        addUrlButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 URL", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\321\203", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
