/********************************************************************************
** Form generated from reading UI file 'TaskImage.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKIMAGE_H
#define UI_TASKIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace Gui {

class Ui_TaskImage
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *XY_radioButton;
    QRadioButton *XZ_radioButton;
    QRadioButton *YZ_radioButton;
    QLabel *previewLabel;
    QCheckBox *Reverse_checkBox;
    QLabel *labelZ;
    Gui::QuantitySpinBox *spinBoxZ;
    QLabel *labelX;
    Gui::QuantitySpinBox *spinBoxX;
    QLabel *labelY;
    Gui::QuantitySpinBox *spinBoxY;
    QLabel *labelRotation;
    Gui::QuantitySpinBox *spinBoxRotation;
    QHBoxLayout *hboxLayout;
    QLabel *labelTransparency;
    QSlider *sliderTransparency;
    QSpinBox *spinBoxTransparency;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout_2;
    QLabel *label;
    Gui::QuantitySpinBox *spinBoxWidth;
    QLabel *label_2;
    Gui::QuantitySpinBox *spinBoxHeight;
    QCheckBox *checkBoxRatio;
    QPushButton *pushButtonScale;
    QGroupBox *groupBoxCalibration;
    QVBoxLayout *calibrationLayout;
    QCheckBox *checkBoxOrient;
    QCheckBox *checkBoxCenterMidpoint;
    QHBoxLayout *buttonLayout;
    QPushButton *pushButtonApply;
    QPushButton *pushButtonCancel;

    void setupUi(QWidget *Gui__TaskImage)
    {
        if (Gui__TaskImage->objectName().isEmpty())
            Gui__TaskImage->setObjectName("Gui__TaskImage");
        Gui__TaskImage->resize(421, 267);
        gridLayout_5 = new QGridLayout(Gui__TaskImage);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        groupBox = new QGroupBox(Gui__TaskImage);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        XY_radioButton = new QRadioButton(groupBox);
        XY_radioButton->setObjectName("XY_radioButton");

        verticalLayout->addWidget(XY_radioButton);

        XZ_radioButton = new QRadioButton(groupBox);
        XZ_radioButton->setObjectName("XZ_radioButton");

        verticalLayout->addWidget(XZ_radioButton);

        YZ_radioButton = new QRadioButton(groupBox);
        YZ_radioButton->setObjectName("YZ_radioButton");

        verticalLayout->addWidget(YZ_radioButton);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 1);

        previewLabel = new QLabel(Gui__TaskImage);
        previewLabel->setObjectName("previewLabel");
        previewLabel->setMinimumSize(QSize(48, 48));
        previewLabel->setMaximumSize(QSize(48, 48));
        previewLabel->setText(QString::fromUtf8("Preview"));

        gridLayout_8->addWidget(previewLabel, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_8, 0, 0, 1, 2);

        Reverse_checkBox = new QCheckBox(Gui__TaskImage);
        Reverse_checkBox->setObjectName("Reverse_checkBox");

        gridLayout_5->addWidget(Reverse_checkBox, 1, 0, 1, 2);

        labelZ = new QLabel(Gui__TaskImage);
        labelZ->setObjectName("labelZ");

        gridLayout_5->addWidget(labelZ, 2, 0, 1, 1);

        spinBoxZ = new Gui::QuantitySpinBox(Gui__TaskImage);
        spinBoxZ->setObjectName("spinBoxZ");
        spinBoxZ->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinBoxZ->setProperty("minimum", QVariant(-999999999.000000000000000));
        spinBoxZ->setProperty("maximum", QVariant(999999999.000000000000000));

        gridLayout_5->addWidget(spinBoxZ, 2, 1, 1, 1);

        labelX = new QLabel(Gui__TaskImage);
        labelX->setObjectName("labelX");

        gridLayout_5->addWidget(labelX, 3, 0, 1, 1);

        spinBoxX = new Gui::QuantitySpinBox(Gui__TaskImage);
        spinBoxX->setObjectName("spinBoxX");
        spinBoxX->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinBoxX->setProperty("minimum", QVariant(-999999999.000000000000000));
        spinBoxX->setProperty("maximum", QVariant(999999999.000000000000000));

        gridLayout_5->addWidget(spinBoxX, 3, 1, 1, 1);

        labelY = new QLabel(Gui__TaskImage);
        labelY->setObjectName("labelY");

        gridLayout_5->addWidget(labelY, 4, 0, 1, 1);

        spinBoxY = new Gui::QuantitySpinBox(Gui__TaskImage);
        spinBoxY->setObjectName("spinBoxY");
        spinBoxY->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinBoxY->setProperty("minimum", QVariant(-999999999.000000000000000));
        spinBoxY->setProperty("maximum", QVariant(999999999.000000000000000));

        gridLayout_5->addWidget(spinBoxY, 4, 1, 1, 1);

        labelRotation = new QLabel(Gui__TaskImage);
        labelRotation->setObjectName("labelRotation");

        gridLayout_5->addWidget(labelRotation, 5, 0, 1, 1);

        spinBoxRotation = new Gui::QuantitySpinBox(Gui__TaskImage);
        spinBoxRotation->setObjectName("spinBoxRotation");
        spinBoxRotation->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        gridLayout_5->addWidget(spinBoxRotation, 5, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        labelTransparency = new QLabel(Gui__TaskImage);
        labelTransparency->setObjectName("labelTransparency");

        hboxLayout->addWidget(labelTransparency);

        sliderTransparency = new QSlider(Gui__TaskImage);
        sliderTransparency->setObjectName("sliderTransparency");
        sliderTransparency->setMaximum(100);
        sliderTransparency->setOrientation(Qt::Horizontal);

        hboxLayout->addWidget(sliderTransparency);

        spinBoxTransparency = new QSpinBox(Gui__TaskImage);
        spinBoxTransparency->setObjectName("spinBoxTransparency");
        spinBoxTransparency->setValue(0);
        spinBoxTransparency->setMinimum(0);
        spinBoxTransparency->setMaximum(100);

        hboxLayout->addWidget(spinBoxTransparency);


        gridLayout_5->addLayout(hboxLayout, 6, 0, 1, 2);

        groupBox1 = new QGroupBox(Gui__TaskImage);
        groupBox1->setObjectName("groupBox1");
        gridLayout_2 = new QGridLayout(groupBox1);
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(groupBox1);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBoxWidth = new Gui::QuantitySpinBox(groupBox1);
        spinBoxWidth->setObjectName("spinBoxWidth");
        spinBoxWidth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinBoxWidth->setProperty("minimum", QVariant(0.000000010000000));
        spinBoxWidth->setProperty("maximum", QVariant(999999999.000000000000000));

        gridLayout_2->addWidget(spinBoxWidth, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox1);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        spinBoxHeight = new Gui::QuantitySpinBox(groupBox1);
        spinBoxHeight->setObjectName("spinBoxHeight");
        spinBoxHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinBoxHeight->setProperty("minimum", QVariant(0.000000010000000));
        spinBoxHeight->setProperty("maximum", QVariant(999999999.000000000000000));

        gridLayout_2->addWidget(spinBoxHeight, 1, 1, 1, 1);

        checkBoxRatio = new QCheckBox(groupBox1);
        checkBoxRatio->setObjectName("checkBoxRatio");
        checkBoxRatio->setChecked(true);

        gridLayout_2->addWidget(checkBoxRatio, 2, 0, 1, 2);

        pushButtonScale = new QPushButton(groupBox1);
        pushButtonScale->setObjectName("pushButtonScale");

        gridLayout_2->addWidget(pushButtonScale, 3, 0, 1, 2);

        groupBoxCalibration = new QGroupBox(groupBox1);
        groupBoxCalibration->setObjectName("groupBoxCalibration");
        calibrationLayout = new QVBoxLayout(groupBoxCalibration);
        calibrationLayout->setObjectName("calibrationLayout");
        checkBoxOrient = new QCheckBox(groupBoxCalibration);
        checkBoxOrient->setObjectName("checkBoxOrient");
        checkBoxOrient->setChecked(false);

        calibrationLayout->addWidget(checkBoxOrient);

        checkBoxCenterMidpoint = new QCheckBox(groupBoxCalibration);
        checkBoxCenterMidpoint->setObjectName("checkBoxCenterMidpoint");
        checkBoxCenterMidpoint->setChecked(false);

        calibrationLayout->addWidget(checkBoxCenterMidpoint);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        pushButtonApply = new QPushButton(groupBoxCalibration);
        pushButtonApply->setObjectName("pushButtonApply");

        buttonLayout->addWidget(pushButtonApply);

        pushButtonCancel = new QPushButton(groupBoxCalibration);
        pushButtonCancel->setObjectName("pushButtonCancel");

        buttonLayout->addWidget(pushButtonCancel);


        calibrationLayout->addLayout(buttonLayout);


        gridLayout_2->addWidget(groupBoxCalibration, 4, 0, 1, 2);


        gridLayout_5->addWidget(groupBox1, 7, 0, 1, 2);


        retranslateUi(Gui__TaskImage);

        QMetaObject::connectSlotsByName(Gui__TaskImage);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskImage)
    {
        Gui__TaskImage->setWindowTitle(QCoreApplication::translate("Gui::TaskImage", "Image Plane Settings", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::TaskImage", "Planes", nullptr));
        XY_radioButton->setText(QCoreApplication::translate("Gui::TaskImage", "XY-plane", nullptr));
        XZ_radioButton->setText(QCoreApplication::translate("Gui::TaskImage", "XZ-plane", nullptr));
        YZ_radioButton->setText(QCoreApplication::translate("Gui::TaskImage", "YZ-plane", nullptr));
        Reverse_checkBox->setText(QCoreApplication::translate("Gui::TaskImage", "Reverse direction", nullptr));
        labelZ->setText(QCoreApplication::translate("Gui::TaskImage", "Offset", nullptr));
        labelX->setText(QCoreApplication::translate("Gui::TaskImage", "X distance", nullptr));
        labelY->setText(QCoreApplication::translate("Gui::TaskImage", "Y distance", nullptr));
        labelRotation->setText(QCoreApplication::translate("Gui::TaskImage", "Rotation", nullptr));
        labelTransparency->setText(QCoreApplication::translate("Gui::TaskImage", "Transparency", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("Gui::TaskImage", "Image Size", nullptr));
        label->setText(QCoreApplication::translate("Gui::TaskImage", "Width", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::TaskImage", "Height", nullptr));
        checkBoxRatio->setText(QCoreApplication::translate("Gui::TaskImage", "Keep aspect ratio", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonScale->setToolTip(QCoreApplication::translate("Gui::TaskImage", "Scales the image interactively by setting a length between two points of the image", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonScale->setText(QCoreApplication::translate("Gui::TaskImage", "Calibrate", nullptr));
        groupBoxCalibration->setTitle(QCoreApplication::translate("Gui::TaskImage", "Calibration", nullptr));
        checkBoxOrient->setText(QCoreApplication::translate("Gui::TaskImage", "Snap rotation to line", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxOrient->setToolTip(QCoreApplication::translate("Gui::TaskImage", "Rotate the image to align the drawn line to the nearest 45 degree angle", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxCenterMidpoint->setText(QCoreApplication::translate("Gui::TaskImage", "Center on midpoint", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxCenterMidpoint->setToolTip(QCoreApplication::translate("Gui::TaskImage", "Center the image on the midpoint of the drawn line", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonApply->setText(QCoreApplication::translate("Gui::TaskImage", "Apply", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("Gui::TaskImage", "Cancel", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class TaskImage: public Ui_TaskImage {};
} // namespace Ui
} // namespace Gui

#endif // UI_TASKIMAGE_H
