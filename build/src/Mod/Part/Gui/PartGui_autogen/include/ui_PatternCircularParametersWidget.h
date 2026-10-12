/********************************************************************************
** Form generated from reading UI file 'PatternCircularParametersWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATTERNCIRCULARPARAMETERSWIDGET_H
#define UI_PATTERNCIRCULARPARAMETERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartGui {

class Ui_PatternCircularParametersWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *axisLabel;
    QComboBox *axisCombo;
    QLabel *radialDistanceLabel;
    Gui::QuantitySpinBox *radialDistance;
    QLabel *tangentialDistanceLabel;
    Gui::QuantitySpinBox *tangentialDistance;
    QLabel *numberCirclesLabel;
    Gui::UIntSpinBox *numberCircles;
    QLabel *symmetryLabel;
    Gui::UIntSpinBox *symmetry;

    void setupUi(QWidget *PartGui__PatternCircularParametersWidget)
    {
        if (PartGui__PatternCircularParametersWidget->objectName().isEmpty())
            PartGui__PatternCircularParametersWidget->setObjectName("PartGui__PatternCircularParametersWidget");
        PartGui__PatternCircularParametersWidget->resize(270, 180);
        verticalLayout = new QVBoxLayout(PartGui__PatternCircularParametersWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(PartGui__PatternCircularParametersWidget);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        axisLabel = new QLabel(groupBox);
        axisLabel->setObjectName("axisLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, axisLabel);

        axisCombo = new QComboBox(groupBox);
        axisCombo->setObjectName("axisCombo");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, axisCombo);

        radialDistanceLabel = new QLabel(groupBox);
        radialDistanceLabel->setObjectName("radialDistanceLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, radialDistanceLabel);

        radialDistance = new Gui::QuantitySpinBox(groupBox);
        radialDistance->setObjectName("radialDistance");
        radialDistance->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, radialDistance);

        tangentialDistanceLabel = new QLabel(groupBox);
        tangentialDistanceLabel->setObjectName("tangentialDistanceLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, tangentialDistanceLabel);

        tangentialDistance = new Gui::QuantitySpinBox(groupBox);
        tangentialDistance->setObjectName("tangentialDistance");
        tangentialDistance->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, tangentialDistance);

        numberCirclesLabel = new QLabel(groupBox);
        numberCirclesLabel->setObjectName("numberCirclesLabel");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, numberCirclesLabel);

        numberCircles = new Gui::UIntSpinBox(groupBox);
        numberCircles->setObjectName("numberCircles");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, numberCircles);

        symmetryLabel = new QLabel(groupBox);
        symmetryLabel->setObjectName("symmetryLabel");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, symmetryLabel);

        symmetry = new Gui::UIntSpinBox(groupBox);
        symmetry->setObjectName("symmetry");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, symmetry);


        verticalLayout->addWidget(groupBox);

#if QT_CONFIG(shortcut)
        axisLabel->setBuddy(axisCombo);
        radialDistanceLabel->setBuddy(radialDistance);
        tangentialDistanceLabel->setBuddy(tangentialDistance);
        numberCirclesLabel->setBuddy(numberCircles);
        symmetryLabel->setBuddy(symmetry);
#endif // QT_CONFIG(shortcut)

        retranslateUi(PartGui__PatternCircularParametersWidget);

        QMetaObject::connectSlotsByName(PartGui__PatternCircularParametersWidget);
    } // setupUi

    void retranslateUi(QWidget *PartGui__PatternCircularParametersWidget)
    {
        groupBox->setTitle(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Circular Pattern", nullptr));
        axisLabel->setText(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Axis", nullptr));
        radialDistanceLabel->setText(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Radial distance", nullptr));
        tangentialDistanceLabel->setText(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Tangential distance", nullptr));
        numberCirclesLabel->setText(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Concentric circles", nullptr));
        symmetryLabel->setText(QCoreApplication::translate("PartGui::PatternCircularParametersWidget", "Symmetry", nullptr));
        (void)PartGui__PatternCircularParametersWidget;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class PatternCircularParametersWidget: public Ui_PatternCircularParametersWidget {};
} // namespace Ui
} // namespace PartGui

#endif // UI_PATTERNCIRCULARPARAMETERSWIDGET_H
