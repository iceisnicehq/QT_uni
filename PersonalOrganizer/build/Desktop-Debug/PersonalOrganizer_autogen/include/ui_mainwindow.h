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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *tasksListWidget;
    QPushButton *addTaskButton;
    QPushButton *deleteTaskButton;
    QPushButton *detailsTaskButton;
    QMenuBar *menubar;
    QMenu *menuPersonal_Organizer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(319, 339);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: white;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tasksListWidget = new QListWidget(centralwidget);
        tasksListWidget->setObjectName("tasksListWidget");
        tasksListWidget->setGeometry(QRect(10, 0, 301, 192));
        tasksListWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        addTaskButton = new QPushButton(centralwidget);
        addTaskButton->setObjectName("addTaskButton");
        addTaskButton->setGeometry(QRect(10, 200, 301, 26));
        deleteTaskButton = new QPushButton(centralwidget);
        deleteTaskButton->setObjectName("deleteTaskButton");
        deleteTaskButton->setGeometry(QRect(10, 230, 301, 26));
        detailsTaskButton = new QPushButton(centralwidget);
        detailsTaskButton->setObjectName("detailsTaskButton");
        detailsTaskButton->setGeometry(QRect(10, 260, 301, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 319, 23));
        menuPersonal_Organizer = new QMenu(menubar);
        menuPersonal_Organizer->setObjectName("menuPersonal_Organizer");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPersonal_Organizer->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addTaskButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\264\320\260\321\207\321\203", nullptr));
        deleteTaskButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\264\320\260\321\207\321\203", nullptr));
        detailsTaskButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\200\320\276\320\261\320\275\320\276\321\201\321\202\320\270 \320\267\320\260\320\264\320\260\321\207\320\270", nullptr));
        menuPersonal_Organizer->setTitle(QCoreApplication::translate("MainWindow", "Personal Organizer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
