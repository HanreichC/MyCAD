/********************************************************************************
** Form generated from reading UI file 'TaskHelixParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKHELIXPARAMETERS_H
#define UI_TASKHELIXPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_TaskHelixParameters
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutStatus;
    QLabel *labelStatus;
    QLabel *labelMessage;
    QHBoxLayout *horizontalLayout;
    QLabel *labelAxis;
    QComboBox *axis;
    QHBoxLayout *horizontalLayoutMode;
    QLabel *labelInputMode;
    QComboBox *inputMode;
    QHBoxLayout *horizontalLayoutPitch;
    QLabel *labelPitch;
    Gui::QuantitySpinBox *pitch;
    QHBoxLayout *horizontalLayoutHeight;
    QLabel *labelHeight;
    Gui::QuantitySpinBox *height;
    QHBoxLayout *horizontalLayoutTurns;
    QLabel *labelTurns;
    Gui::QuantitySpinBox *turns;
    QHBoxLayout *horizontalLayoutConeAngle;
    QLabel *labelConeAngle;
    Gui::QuantitySpinBox *coneAngle;
    QHBoxLayout *horizontalLayoutGrowth;
    QLabel *labelGrowth;
    Gui::QuantitySpinBox *growth;
    QCheckBox *checkBoxLeftHanded;
    QCheckBox *checkBoxReversed;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;
    QFrame *line;
    QCheckBox *checkBoxUpdateView;

    void setupUi(QWidget *PartDesignGui__TaskHelixParameters)
    {
        if (PartDesignGui__TaskHelixParameters->objectName().isEmpty())
            PartDesignGui__TaskHelixParameters->setObjectName("PartDesignGui__TaskHelixParameters");
        PartDesignGui__TaskHelixParameters->resize(278, 398);
        PartDesignGui__TaskHelixParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskHelixParameters);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayoutStatus = new QHBoxLayout();
        horizontalLayoutStatus->setObjectName("horizontalLayoutStatus");
        labelStatus = new QLabel(PartDesignGui__TaskHelixParameters);
        labelStatus->setObjectName("labelStatus");

        horizontalLayoutStatus->addWidget(labelStatus);

        labelMessage = new QLabel(PartDesignGui__TaskHelixParameters);
        labelMessage->setObjectName("labelMessage");

        horizontalLayoutStatus->addWidget(labelMessage);


        verticalLayout->addLayout(horizontalLayoutStatus);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelAxis = new QLabel(PartDesignGui__TaskHelixParameters);
        labelAxis->setObjectName("labelAxis");

        horizontalLayout->addWidget(labelAxis);

        axis = new QComboBox(PartDesignGui__TaskHelixParameters);
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->setObjectName("axis");

        horizontalLayout->addWidget(axis);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayoutMode = new QHBoxLayout();
        horizontalLayoutMode->setObjectName("horizontalLayoutMode");
        labelInputMode = new QLabel(PartDesignGui__TaskHelixParameters);
        labelInputMode->setObjectName("labelInputMode");

        horizontalLayoutMode->addWidget(labelInputMode);

        inputMode = new QComboBox(PartDesignGui__TaskHelixParameters);
        inputMode->addItem(QString());
        inputMode->addItem(QString());
        inputMode->addItem(QString());
        inputMode->addItem(QString());
        inputMode->setObjectName("inputMode");

        horizontalLayoutMode->addWidget(inputMode);


        verticalLayout->addLayout(horizontalLayoutMode);

        horizontalLayoutPitch = new QHBoxLayout();
        horizontalLayoutPitch->setObjectName("horizontalLayoutPitch");
        labelPitch = new QLabel(PartDesignGui__TaskHelixParameters);
        labelPitch->setObjectName("labelPitch");

        horizontalLayoutPitch->addWidget(labelPitch);

        pitch = new Gui::QuantitySpinBox(PartDesignGui__TaskHelixParameters);
        pitch->setObjectName("pitch");
        pitch->setKeyboardTracking(false);
        pitch->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        pitch->setMinimum(0.000000000000000);
        pitch->setValue(10.000000000000000);

        horizontalLayoutPitch->addWidget(pitch);


        verticalLayout->addLayout(horizontalLayoutPitch);

        horizontalLayoutHeight = new QHBoxLayout();
        horizontalLayoutHeight->setObjectName("horizontalLayoutHeight");
        labelHeight = new QLabel(PartDesignGui__TaskHelixParameters);
        labelHeight->setObjectName("labelHeight");

        horizontalLayoutHeight->addWidget(labelHeight);

        height = new Gui::QuantitySpinBox(PartDesignGui__TaskHelixParameters);
        height->setObjectName("height");
        height->setKeyboardTracking(false);
        height->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        height->setMinimum(0.000000000000000);
        height->setValue(30.000000000000000);

        horizontalLayoutHeight->addWidget(height);


        verticalLayout->addLayout(horizontalLayoutHeight);

        horizontalLayoutTurns = new QHBoxLayout();
        horizontalLayoutTurns->setObjectName("horizontalLayoutTurns");
        labelTurns = new QLabel(PartDesignGui__TaskHelixParameters);
        labelTurns->setObjectName("labelTurns");

        horizontalLayoutTurns->addWidget(labelTurns);

        turns = new Gui::QuantitySpinBox(PartDesignGui__TaskHelixParameters);
        turns->setObjectName("turns");
        turns->setKeyboardTracking(false);
        turns->setMinimum(0.000000000000000);
        turns->setValue(3.000000000000000);

        horizontalLayoutTurns->addWidget(turns);


        verticalLayout->addLayout(horizontalLayoutTurns);

        horizontalLayoutConeAngle = new QHBoxLayout();
        horizontalLayoutConeAngle->setObjectName("horizontalLayoutConeAngle");
        labelConeAngle = new QLabel(PartDesignGui__TaskHelixParameters);
        labelConeAngle->setObjectName("labelConeAngle");

        horizontalLayoutConeAngle->addWidget(labelConeAngle);

        coneAngle = new Gui::QuantitySpinBox(PartDesignGui__TaskHelixParameters);
        coneAngle->setObjectName("coneAngle");
        coneAngle->setKeyboardTracking(false);
        coneAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        coneAngle->setMinimum(-89.000000000000000);
        coneAngle->setMaximum(89.000000000000000);
        coneAngle->setSingleStep(1.000000000000000);

        horizontalLayoutConeAngle->addWidget(coneAngle);


        verticalLayout->addLayout(horizontalLayoutConeAngle);

        horizontalLayoutGrowth = new QHBoxLayout();
        horizontalLayoutGrowth->setObjectName("horizontalLayoutGrowth");
        labelGrowth = new QLabel(PartDesignGui__TaskHelixParameters);
        labelGrowth->setObjectName("labelGrowth");

        horizontalLayoutGrowth->addWidget(labelGrowth);

        growth = new Gui::QuantitySpinBox(PartDesignGui__TaskHelixParameters);
        growth->setObjectName("growth");
        growth->setKeyboardTracking(false);
        growth->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        horizontalLayoutGrowth->addWidget(growth);


        verticalLayout->addLayout(horizontalLayoutGrowth);

        checkBoxLeftHanded = new QCheckBox(PartDesignGui__TaskHelixParameters);
        checkBoxLeftHanded->setObjectName("checkBoxLeftHanded");
        checkBoxLeftHanded->setEnabled(true);

        verticalLayout->addWidget(checkBoxLeftHanded);

        checkBoxReversed = new QCheckBox(PartDesignGui__TaskHelixParameters);
        checkBoxReversed->setObjectName("checkBoxReversed");
        checkBoxReversed->setEnabled(true);

        verticalLayout->addWidget(checkBoxReversed);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__TaskHelixParameters);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__TaskHelixParameters);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);


        verticalLayout->addLayout(operationLayout);

        line = new QFrame(PartDesignGui__TaskHelixParameters);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        checkBoxUpdateView = new QCheckBox(PartDesignGui__TaskHelixParameters);
        checkBoxUpdateView->setObjectName("checkBoxUpdateView");
        checkBoxUpdateView->setChecked(true);

        verticalLayout->addWidget(checkBoxUpdateView);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(axis, inputMode);
        QWidget::setTabOrder(inputMode, pitch);
        QWidget::setTabOrder(pitch, height);
        QWidget::setTabOrder(height, turns);
        QWidget::setTabOrder(turns, coneAngle);
        QWidget::setTabOrder(coneAngle, growth);
        QWidget::setTabOrder(growth, checkBoxLeftHanded);
        QWidget::setTabOrder(checkBoxLeftHanded, checkBoxReversed);
        QWidget::setTabOrder(checkBoxReversed, comboOperation);
        QWidget::setTabOrder(comboOperation, checkBoxUpdateView);

        retranslateUi(PartDesignGui__TaskHelixParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskHelixParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskHelixParameters)
    {
        labelStatus->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Status", nullptr));
        labelMessage->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Valid", nullptr));
        labelAxis->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Axis", nullptr));
        axis->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Base X-axis", nullptr));
        axis->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Base Y-axis", nullptr));
        axis->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Base Z-axis", nullptr));
        axis->setItemText(3, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Horizontal sketch axis", nullptr));
        axis->setItemText(4, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Vertical sketch axis", nullptr));
        axis->setItemText(5, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Normal sketch axis", nullptr));
        axis->setItemText(6, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Select reference\342\200\246", nullptr));

        labelInputMode->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Mode", nullptr));
        inputMode->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Pitch-Height-Angle", nullptr));
        inputMode->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Pitch-Turns-Angle", nullptr));
        inputMode->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Height-Turns-Angle", nullptr));
        inputMode->setItemText(3, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Height-Turns-Growth", nullptr));

        labelPitch->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Pitch", nullptr));
        labelHeight->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Height", nullptr));
        labelTurns->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Turns", nullptr));
        labelConeAngle->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Cone angle", nullptr));
        labelGrowth->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Radial growth", nullptr));
        checkBoxLeftHanded->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Left handed", nullptr));
        checkBoxReversed->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Reversed", nullptr));
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Common", nullptr));

        checkBoxUpdateView->setText(QCoreApplication::translate("PartDesignGui::TaskHelixParameters", "Recompute on change", nullptr));
        (void)PartDesignGui__TaskHelixParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskHelixParameters: public Ui_TaskHelixParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKHELIXPARAMETERS_H
