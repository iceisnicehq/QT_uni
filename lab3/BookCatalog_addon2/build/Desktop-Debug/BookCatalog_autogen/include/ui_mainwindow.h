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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImportCSV;
    QAction *actionExportCSV;
    QAction *actionExit;
    QWidget *centralwidget;
    QTableView *tableView;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QPushButton *btnEdit;
    QPushButton *searchButton;
    QLineEdit *searchLineEdit;
    QPushButton *btnFilterAuthor;
    QPushButton *btnFilterGenre;
    QPushButton *btnClearFilters;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionImportCSV = new QAction(MainWindow);
        actionImportCSV->setObjectName("actionImportCSV");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/img/import.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionImportCSV->setIcon(icon);
        actionExportCSV = new QAction(MainWindow);
        actionExportCSV->setObjectName("actionExportCSV");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/img/export.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExportCSV->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/img/exit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExit->setIcon(icon2);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(60, 50, 351, 201));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(60, 250, 121, 41));
        btnRemove = new QPushButton(centralwidget);
        btnRemove->setObjectName("btnRemove");
        btnRemove->setGeometry(QRect(180, 250, 101, 41));
        btnEdit = new QPushButton(centralwidget);
        btnEdit->setObjectName("btnEdit");
        btnEdit->setGeometry(QRect(280, 250, 131, 41));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(340, 360, 61, 31));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setGeometry(QRect(60, 360, 271, 31));
        btnFilterAuthor = new QPushButton(centralwidget);
        btnFilterAuthor->setObjectName("btnFilterAuthor");
        btnFilterAuthor->setGeometry(QRect(60, 300, 171, 25));
        btnFilterGenre = new QPushButton(centralwidget);
        btnFilterGenre->setObjectName("btnFilterGenre");
        btnFilterGenre->setGeometry(QRect(230, 300, 181, 25));
        btnClearFilters = new QPushButton(centralwidget);
        btnClearFilters->setObjectName("btnClearFilters");
        btnClearFilters->setGeometry(QRect(170, 330, 121, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionImportCSV);
        menu->addAction(actionExportCSV);
        menu->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionImportCSV->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        actionExportCSV->setText(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnFilterAuthor->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\273\321\202\321\214\321\200 \320\277\320\276 \320\260\320\262\321\202\320\276\321\200\321\203", nullptr));
        btnFilterGenre->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\273\321\214\321\202\321\200 \320\277\320\276 \320\266\320\260\320\275\321\200\321\203", nullptr));
        btnClearFilters->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \321\204\320\270\320\273\321\214\321\202\321\200\321\213", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
