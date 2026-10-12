/********************************************************************************
** Form generated from reading UI file 'SketchOrientationDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHORIENTATIONDIALOG_H
#define UI_SKETCHORIENTATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include "Gui/QuantitySpinBox.h"

namespace SketcherGui {

class Ui_SketchOrientationDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *XY_radioButton;
    QRadioButton *XZ_radioButton;
    QRadioButton *YZ_radioButton;
    QLabel *previewLabel;
    QCheckBox *Reverse_checkBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::QuantitySpinBox *Offset_doubleSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SketcherGui__SketchOrientationDialog)
    {
        if (SketcherGui__SketchOrientationDialog->objectName().isEmpty())
            SketcherGui__SketchOrientationDialog->setObjectName("SketcherGui__SketchOrientationDialog");
        SketcherGui__SketchOrientationDialog->resize(178, 201);
        gridLayout = new QGridLayout(SketcherGui__SketchOrientationDialog);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(SketcherGui__SketchOrientationDialog);
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

        previewLabel = new QLabel(SketcherGui__SketchOrientationDialog);
        previewLabel->setObjectName("previewLabel");
        previewLabel->setMinimumSize(QSize(48, 48));
        previewLabel->setMaximumSize(QSize(48, 48));
        previewLabel->setText(QString::fromUtf8("Preview"));

        gridLayout->addWidget(previewLabel, 0, 1, 1, 1);

        Reverse_checkBox = new QCheckBox(SketcherGui__SketchOrientationDialog);
        Reverse_checkBox->setObjectName("Reverse_checkBox");

        gridLayout->addWidget(Reverse_checkBox, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SketcherGui__SketchOrientationDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        Offset_doubleSpinBox = new Gui::QuantitySpinBox(SketcherGui__SketchOrientationDialog);
        Offset_doubleSpinBox->setObjectName("Offset_doubleSpinBox");
        Offset_doubleSpinBox->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        Offset_doubleSpinBox->setMinimum(-999999999.000000000000000);
        Offset_doubleSpinBox->setMaximum(999999999.000000000000000);
        Offset_doubleSpinBox->setSingleStep(10.000000000000000);

        horizontalLayout->addWidget(Offset_doubleSpinBox);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(SketcherGui__SketchOrientationDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(SketcherGui__SketchOrientationDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SketcherGui__SketchOrientationDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SketcherGui__SketchOrientationDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SketcherGui__SketchOrientationDialog);
    } // setupUi

    void retranslateUi(QDialog *SketcherGui__SketchOrientationDialog)
    {
        SketcherGui__SketchOrientationDialog->setWindowTitle(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "Choose Orientation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "Sketch Orientation", nullptr));
        XY_radioButton->setText(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "XY-plane", nullptr));
        XZ_radioButton->setText(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "XZ-plane", nullptr));
        YZ_radioButton->setText(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "YZ-plane", nullptr));
        Reverse_checkBox->setText(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "Reverse direction", nullptr));
        label->setText(QCoreApplication::translate("SketcherGui::SketchOrientationDialog", "Offset", nullptr));
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketchOrientationDialog: public Ui_SketchOrientationDialog {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHORIENTATIONDIALOG_H
