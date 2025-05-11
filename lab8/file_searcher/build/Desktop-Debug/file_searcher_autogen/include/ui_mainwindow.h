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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLineEdit *directoryEdit;
    QPushButton *browseButton;
    QGridLayout *gridLayout;
    QLabel *labelExtension;
    QLineEdit *extensionEdit;
    QLabel *labelContent;
    QLineEdit *contentEdit;
    QLabel *labelSize;
    QHBoxLayout *hboxLayout1;
    QSpinBox *minSizeSpin;
    QLabel *labelTo;
    QSpinBox *maxSizeSpin;
    QListWidget *resultList;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QHBoxLayout *hboxLayout2;
    QPushButton *searchButton;
    QPushButton *cancelButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(347, 428);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        directoryEdit = new QLineEdit(centralwidget);
        directoryEdit->setObjectName("directoryEdit");

        hboxLayout->addWidget(directoryEdit);

        browseButton = new QPushButton(centralwidget);
        browseButton->setObjectName("browseButton");

        hboxLayout->addWidget(browseButton);


        vboxLayout->addLayout(hboxLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelExtension = new QLabel(centralwidget);
        labelExtension->setObjectName("labelExtension");

        gridLayout->addWidget(labelExtension, 0, 0, 1, 1);

        extensionEdit = new QLineEdit(centralwidget);
        extensionEdit->setObjectName("extensionEdit");

        gridLayout->addWidget(extensionEdit, 0, 1, 1, 1);

        labelContent = new QLabel(centralwidget);
        labelContent->setObjectName("labelContent");

        gridLayout->addWidget(labelContent, 1, 0, 1, 1);

        contentEdit = new QLineEdit(centralwidget);
        contentEdit->setObjectName("contentEdit");

        gridLayout->addWidget(contentEdit, 1, 1, 1, 1);

        labelSize = new QLabel(centralwidget);
        labelSize->setObjectName("labelSize");

        gridLayout->addWidget(labelSize, 2, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        minSizeSpin = new QSpinBox(centralwidget);
        minSizeSpin->setObjectName("minSizeSpin");

        hboxLayout1->addWidget(minSizeSpin);

        labelTo = new QLabel(centralwidget);
        labelTo->setObjectName("labelTo");

        hboxLayout1->addWidget(labelTo);

        maxSizeSpin = new QSpinBox(centralwidget);
        maxSizeSpin->setObjectName("maxSizeSpin");
        maxSizeSpin->setMaximum(1024);

        hboxLayout1->addWidget(maxSizeSpin);


        gridLayout->addLayout(hboxLayout1, 2, 1, 1, 1);


        vboxLayout->addLayout(gridLayout);

        resultList = new QListWidget(centralwidget);
        resultList->setObjectName("resultList");

        vboxLayout->addWidget(resultList);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");

        vboxLayout->addWidget(progressBar);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        vboxLayout->addWidget(statusLabel);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");

        hboxLayout2->addWidget(searchButton);

        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName("cancelButton");

        hboxLayout2->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\267\320\276\321\200...", nullptr));
        labelExtension->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\200\320\265\320\275\320\270\320\265:", nullptr));
        labelContent->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\264\320\265\321\200\320\266\320\270\320\274\320\276\320\265:", nullptr));
        labelSize->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 (KB):", nullptr));
        labelTo->setText(QCoreApplication::translate("MainWindow", "\320\264\320\276", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\277\320\276\320\270\321\201\320\272", nullptr));
        cancelButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
