/********************************************************************************
** Form generated from reading UI file 'DlgInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGINPUTDIALOG_H
#define UI_DLGINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "Gui/SpinBox.h"

namespace Gui {
namespace Dialog {

class Ui_DlgInputDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QStackedWidget *stack;
    QWidget *WStackPage1;
    QGridLayout *gridLayout1;
    QLineEdit *lineEdit;
    QWidget *WStackPage2;
    QGridLayout *gridLayout2;
    QSpinBox *spinBox;
    QWidget *WStackPage3;
    QGridLayout *gridLayout3;
    QDoubleSpinBox *floatSpinBox;
    QWidget *WStackPage4;
    QGridLayout *gridLayout4;
    QComboBox *comboBox;
    QWidget *WStackPage5;
    QHBoxLayout *hboxLayout;
    Gui::UIntSpinBox *uIntSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgInputDialog)
    {
        if (Gui__Dialog__DlgInputDialog->objectName().isEmpty())
            Gui__Dialog__DlgInputDialog->setObjectName("Gui__Dialog__DlgInputDialog");
        Gui__Dialog__DlgInputDialog->resize(399, 99);
        Gui__Dialog__DlgInputDialog->setSizeGripEnabled(false);
        gridLayout = new QGridLayout(Gui__Dialog__DlgInputDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(Gui__Dialog__DlgInputDialog);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        stack = new QStackedWidget(Gui__Dialog__DlgInputDialog);
        stack->setObjectName("stack");
        WStackPage1 = new QWidget();
        WStackPage1->setObjectName("WStackPage1");
        gridLayout1 = new QGridLayout(WStackPage1);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(1, 1, 1, 1);
        gridLayout1->setObjectName("gridLayout1");
        lineEdit = new QLineEdit(WStackPage1);
        lineEdit->setObjectName("lineEdit");

        gridLayout1->addWidget(lineEdit, 0, 0, 1, 1);

        stack->addWidget(WStackPage1);
        WStackPage2 = new QWidget();
        WStackPage2->setObjectName("WStackPage2");
        gridLayout2 = new QGridLayout(WStackPage2);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(1, 1, 1, 1);
        gridLayout2->setObjectName("gridLayout2");
        spinBox = new QSpinBox(WStackPage2);
        spinBox->setObjectName("spinBox");

        gridLayout2->addWidget(spinBox, 0, 0, 1, 1);

        stack->addWidget(WStackPage2);
        WStackPage3 = new QWidget();
        WStackPage3->setObjectName("WStackPage3");
        gridLayout3 = new QGridLayout(WStackPage3);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(1, 1, 1, 1);
        gridLayout3->setObjectName("gridLayout3");
        floatSpinBox = new QDoubleSpinBox(WStackPage3);
        floatSpinBox->setObjectName("floatSpinBox");

        gridLayout3->addWidget(floatSpinBox, 0, 0, 1, 1);

        stack->addWidget(WStackPage3);
        WStackPage4 = new QWidget();
        WStackPage4->setObjectName("WStackPage4");
        gridLayout4 = new QGridLayout(WStackPage4);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(1, 1, 1, 1);
        gridLayout4->setObjectName("gridLayout4");
        comboBox = new QComboBox(WStackPage4);
        comboBox->setObjectName("comboBox");

        gridLayout4->addWidget(comboBox, 0, 0, 1, 1);

        stack->addWidget(WStackPage4);
        WStackPage5 = new QWidget();
        WStackPage5->setObjectName("WStackPage5");
        hboxLayout = new QHBoxLayout(WStackPage5);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(1, 1, 1, 1);
        hboxLayout->setObjectName("hboxLayout");
        uIntSpinBox = new Gui::UIntSpinBox(WStackPage5);
        uIntSpinBox->setObjectName("uIntSpinBox");

        hboxLayout->addWidget(uIntSpinBox);

        stack->addWidget(WStackPage5);

        gridLayout->addWidget(stack, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgInputDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgInputDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgInputDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgInputDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgInputDialog);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgInputDialog)
    {
        Gui__Dialog__DlgInputDialog->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgInputDialog", "Input", nullptr));
        label->setText(QString());
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgInputDialog: public Ui_DlgInputDialog {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGINPUTDIALOG_H
