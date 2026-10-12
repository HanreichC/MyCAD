/********************************************************************************
** Form generated from reading UI file 'TaskOrientation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKORIENTATION_H
#define UI_TASKORIENTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace Gui {

class Ui_TaskOrientation
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *XY_radioButton;
    QRadioButton *XZ_radioButton;
    QRadioButton *YZ_radioButton;
    QCheckBox *Reverse_checkBox;
    QLabel *previewLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::QuantitySpinBox *Offset_doubleSpinBox;

    void setupUi(QWidget *Gui__TaskOrientation)
    {
        if (Gui__TaskOrientation->objectName().isEmpty())
            Gui__TaskOrientation->setObjectName("Gui__TaskOrientation");
        Gui__TaskOrientation->resize(194, 200);
        gridLayout = new QGridLayout(Gui__TaskOrientation);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(Gui__TaskOrientation);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        XY_radioButton = new QRadioButton(groupBox);
        XY_radioButton->setObjectName("XY_radioButton");
        XY_radioButton->setChecked(true);

        verticalLayout->addWidget(XY_radioButton);

        XZ_radioButton = new QRadioButton(groupBox);
        XZ_radioButton->setObjectName("XZ_radioButton");

        verticalLayout->addWidget(XZ_radioButton);

        YZ_radioButton = new QRadioButton(groupBox);
        YZ_radioButton->setObjectName("YZ_radioButton");

        verticalLayout->addWidget(YZ_radioButton);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        Reverse_checkBox = new QCheckBox(Gui__TaskOrientation);
        Reverse_checkBox->setObjectName("Reverse_checkBox");

        gridLayout->addWidget(Reverse_checkBox, 1, 0, 1, 2);

        previewLabel = new QLabel(Gui__TaskOrientation);
        previewLabel->setObjectName("previewLabel");
        previewLabel->setMinimumSize(QSize(48, 48));
        previewLabel->setMaximumSize(QSize(48, 48));
        previewLabel->setText(QString::fromUtf8("Preview"));

        gridLayout->addWidget(previewLabel, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui__TaskOrientation);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        Offset_doubleSpinBox = new Gui::QuantitySpinBox(Gui__TaskOrientation);
        Offset_doubleSpinBox->setObjectName("Offset_doubleSpinBox");
        Offset_doubleSpinBox->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        Offset_doubleSpinBox->setProperty("minimum", QVariant(-999999999.000000000000000));
        Offset_doubleSpinBox->setProperty("maximum", QVariant(999999999.000000000000000));
        Offset_doubleSpinBox->setProperty("singleStep", QVariant(1.000000000000000));

        horizontalLayout->addWidget(Offset_doubleSpinBox);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);


        retranslateUi(Gui__TaskOrientation);

        QMetaObject::connectSlotsByName(Gui__TaskOrientation);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskOrientation)
    {
        Gui__TaskOrientation->setWindowTitle(QCoreApplication::translate("Gui::TaskOrientation", "Choose Orientation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::TaskOrientation", "Planes", nullptr));
        XY_radioButton->setText(QCoreApplication::translate("Gui::TaskOrientation", "XY-plane", nullptr));
        XZ_radioButton->setText(QCoreApplication::translate("Gui::TaskOrientation", "XZ-plane", nullptr));
        YZ_radioButton->setText(QCoreApplication::translate("Gui::TaskOrientation", "YZ-plane", nullptr));
        Reverse_checkBox->setText(QCoreApplication::translate("Gui::TaskOrientation", "Reverse direction", nullptr));
        label->setText(QCoreApplication::translate("Gui::TaskOrientation", "Offset", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class TaskOrientation: public Ui_TaskOrientation {};
} // namespace Ui
} // namespace Gui

#endif // UI_TASKORIENTATION_H
