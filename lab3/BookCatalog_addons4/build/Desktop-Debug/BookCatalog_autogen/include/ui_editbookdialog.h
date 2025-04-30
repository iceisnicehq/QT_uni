/********************************************************************************
** Form generated from reading UI file 'editbookdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITBOOKDIALOG_H
#define UI_EDITBOOKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditBookDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor;
    QLabel *labelTitle;
    QLineEdit *lineEditTitle;
    QLabel *labelYear;
    QSpinBox *spinBoxYear;
    QLabel *labelGenre;
    QLineEdit *lineEditGenre;
    QLabel *labelPublisher;
    QLabel *labelISBN;
    QLabel *labelPages;
    QLineEdit *lineEditPublisher;
    QLineEdit *lineEditISBN;
    QSpinBox *spinBoxPages;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditBookDialog)
    {
        if (EditBookDialog->objectName().isEmpty())
            EditBookDialog->setObjectName("EditBookDialog");
        EditBookDialog->resize(358, 282);
        verticalLayout = new QVBoxLayout(EditBookDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelAuthor = new QLabel(EditBookDialog);
        labelAuthor->setObjectName("labelAuthor");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelAuthor);

        lineEditAuthor = new QLineEdit(EditBookDialog);
        lineEditAuthor->setObjectName("lineEditAuthor");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditAuthor);

        labelTitle = new QLabel(EditBookDialog);
        labelTitle->setObjectName("labelTitle");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelTitle);

        lineEditTitle = new QLineEdit(EditBookDialog);
        lineEditTitle->setObjectName("lineEditTitle");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditTitle);

        labelYear = new QLabel(EditBookDialog);
        labelYear->setObjectName("labelYear");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelYear);

        spinBoxYear = new QSpinBox(EditBookDialog);
        spinBoxYear->setObjectName("spinBoxYear");
        spinBoxYear->setMinimum(0);
        spinBoxYear->setMaximum(2100);
        spinBoxYear->setValue(2000);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxYear);

        labelGenre = new QLabel(EditBookDialog);
        labelGenre->setObjectName("labelGenre");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelGenre);

        lineEditGenre = new QLineEdit(EditBookDialog);
        lineEditGenre->setObjectName("lineEditGenre");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditGenre);

        labelPublisher = new QLabel(EditBookDialog);
        labelPublisher->setObjectName("labelPublisher");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelPublisher);

        labelISBN = new QLabel(EditBookDialog);
        labelISBN->setObjectName("labelISBN");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelISBN);

        labelPages = new QLabel(EditBookDialog);
        labelPages->setObjectName("labelPages");

        formLayout->setWidget(6, QFormLayout::LabelRole, labelPages);

        lineEditPublisher = new QLineEdit(EditBookDialog);
        lineEditPublisher->setObjectName("lineEditPublisher");

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditPublisher);

        lineEditISBN = new QLineEdit(EditBookDialog);
        lineEditISBN->setObjectName("lineEditISBN");

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditISBN);

        spinBoxPages = new QSpinBox(EditBookDialog);
        spinBoxPages->setObjectName("spinBoxPages");
        spinBoxPages->setMinimum(1);
        spinBoxPages->setMaximum(10000);

        formLayout->setWidget(6, QFormLayout::FieldRole, spinBoxPages);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(EditBookDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EditBookDialog);

        QMetaObject::connectSlotsByName(EditBookDialog);
    } // setupUi

    void retranslateUi(QDialog *EditBookDialog)
    {
        EditBookDialog->setWindowTitle(QCoreApplication::translate("EditBookDialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\275\320\270\320\263\321\203", nullptr));
        labelAuthor->setText(QCoreApplication::translate("EditBookDialog", "\320\220\320\262\321\202\320\276\321\200:", nullptr));
        labelTitle->setText(QCoreApplication::translate("EditBookDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", nullptr));
        labelYear->setText(QCoreApplication::translate("EditBookDialog", "\320\223\320\276\320\264:", nullptr));
        labelGenre->setText(QCoreApplication::translate("EditBookDialog", "\320\226\320\260\320\275\321\200:", nullptr));
        labelPublisher->setText(QCoreApplication::translate("EditBookDialog", "\320\230\320\267\320\264\320\260\321\202\320\265\320\273\321\214\321\201\321\202\320\262\320\276:", nullptr));
        labelISBN->setText(QCoreApplication::translate("EditBookDialog", "ISBN:", nullptr));
        labelPages->setText(QCoreApplication::translate("EditBookDialog", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\321\213:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditBookDialog: public Ui_EditBookDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITBOOKDIALOG_H
