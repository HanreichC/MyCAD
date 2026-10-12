/********************************************************************************
** Form generated from reading UI file 'DlgUnitsCalculator.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGUNITSCALCULATOR_H
#define UI_DLGUNITSCALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "Gui/InputField.h"
#include "Gui/QuantitySpinBox.h"

namespace Gui {
namespace Dialog {

class Ui_DlgUnitCalculator
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    Gui::InputField *ValueInput;
    QLabel *label;
    QLineEdit *UnitInput;
    QLabel *label_2;
    QLineEdit *ValueOutput;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    Gui::QuantitySpinBox *quantitySpinBox;
    QLabel *label_6;
    QComboBox *comboBoxScheme;
    QLabel *label_5;
    QSpinBox *spinBoxDecimals;
    QLabel *label_4;
    QComboBox *unitsBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Copy;
    QPushButton *pushButton_Close;

    void setupUi(QWidget *Gui__Dialog__DlgUnitCalculator)
    {
        if (Gui__Dialog__DlgUnitCalculator->objectName().isEmpty())
            Gui__Dialog__DlgUnitCalculator->setObjectName("Gui__Dialog__DlgUnitCalculator");
        Gui__Dialog__DlgUnitCalculator->resize(537, 262);
        gridLayout_2 = new QGridLayout(Gui__Dialog__DlgUnitCalculator);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ValueInput = new Gui::InputField(Gui__Dialog__DlgUnitCalculator);
        ValueInput->setObjectName("ValueInput");
        ValueInput->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(ValueInput);

        label = new QLabel(Gui__Dialog__DlgUnitCalculator);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        UnitInput = new QLineEdit(Gui__Dialog__DlgUnitCalculator);
        UnitInput->setObjectName("UnitInput");
        UnitInput->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(UnitInput);

        label_2 = new QLabel(Gui__Dialog__DlgUnitCalculator);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        ValueOutput = new QLineEdit(Gui__Dialog__DlgUnitCalculator);
        ValueOutput->setObjectName("ValueOutput");
        ValueOutput->setMinimumSize(QSize(150, 0));
        ValueOutput->setReadOnly(true);

        horizontalLayout_2->addWidget(ValueOutput);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        textEdit = new QTextEdit(Gui__Dialog__DlgUnitCalculator);
        textEdit->setObjectName("textEdit");
        textEdit->setReadOnly(true);

        gridLayout_2->addWidget(textEdit, 1, 0, 1, 1);

        groupBox = new QGroupBox(Gui__Dialog__DlgUnitCalculator);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        quantitySpinBox = new Gui::QuantitySpinBox(groupBox);
        quantitySpinBox->setObjectName("quantitySpinBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(quantitySpinBox->sizePolicy().hasHeightForWidth());
        quantitySpinBox->setSizePolicy(sizePolicy);

        gridLayout->addWidget(quantitySpinBox, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 2, 1, 1);

        comboBoxScheme = new QComboBox(groupBox);
        comboBoxScheme->setObjectName("comboBoxScheme");

        gridLayout->addWidget(comboBoxScheme, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        spinBoxDecimals = new QSpinBox(groupBox);
        spinBoxDecimals->setObjectName("spinBoxDecimals");
        spinBoxDecimals->setMinimum(2);
        spinBoxDecimals->setMaximum(12);
        spinBoxDecimals->setValue(5);

        gridLayout->addWidget(spinBoxDecimals, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        unitsBox = new QComboBox(groupBox);
        unitsBox->setObjectName("unitsBox");
        sizePolicy.setHeightForWidth(unitsBox->sizePolicy().hasHeightForWidth());
        unitsBox->setSizePolicy(sizePolicy);

        gridLayout->addWidget(unitsBox, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Copy = new QPushButton(Gui__Dialog__DlgUnitCalculator);
        pushButton_Copy->setObjectName("pushButton_Copy");

        horizontalLayout->addWidget(pushButton_Copy);

        pushButton_Close = new QPushButton(Gui__Dialog__DlgUnitCalculator);
        pushButton_Close->setObjectName("pushButton_Close");

        horizontalLayout->addWidget(pushButton_Close);


        gridLayout_2->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgUnitCalculator);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgUnitCalculator);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgUnitCalculator)
    {
        Gui__Dialog__DlgUnitCalculator->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Units Converter", nullptr));
#if QT_CONFIG(tooltip)
        ValueInput->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Input the source value and unit", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "as", nullptr));
#if QT_CONFIG(tooltip)
        UnitInput->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Input the unit for the result", nullptr));
#endif // QT_CONFIG(tooltip)
        UnitInput->setText(QString());
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "=>", nullptr));
#if QT_CONFIG(tooltip)
        ValueOutput->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Result", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        textEdit->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "List of last used calculations.\n"
"To add a calculation press Return in the value input field", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Quantity", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Quantity", nullptr));
        label_6->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Unit system", nullptr));
#if QT_CONFIG(tooltip)
        comboBoxScheme->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Unit system to be used for the Quantity.\n"
"The preference system is the one set in the general preferences.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Decimals", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxDecimals->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Decimals for the quantity", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Unit category", nullptr));
#if QT_CONFIG(tooltip)
        unitsBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Unit category for the quantity", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_Copy->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Copies the result to the clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_Copy->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Copy", nullptr));
        pushButton_Close->setText(QCoreApplication::translate("Gui::Dialog::DlgUnitCalculator", "Close", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgUnitCalculator: public Ui_DlgUnitCalculator {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGUNITSCALCULATOR_H
