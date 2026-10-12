/********************************************************************************
** Form generated from reading UI file 'TaskThicknessParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKTHICKNESSPARAMETERS_H
#define UI_TASKTHICKNESSPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_TaskThicknessParameters
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *buttonRefSel;
    QListWidget *listWidgetReferences;
    QGridLayout *gridLayout_2;
    QLabel *label;
    Gui::QuantitySpinBox *Value;
    QLabel *label_2;
    QComboBox *modeComboBox;
    QLabel *label_3;
    QComboBox *joinComboBox;
    QCheckBox *checkIntersection;
    QCheckBox *checkReverse;

    void setupUi(QWidget *PartDesignGui__TaskThicknessParameters)
    {
        if (PartDesignGui__TaskThicknessParameters->objectName().isEmpty())
            PartDesignGui__TaskThicknessParameters->setObjectName("PartDesignGui__TaskThicknessParameters");
        PartDesignGui__TaskThicknessParameters->resize(321, 509);
        PartDesignGui__TaskThicknessParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskThicknessParameters);
        verticalLayout->setObjectName("verticalLayout");
        buttonRefSel = new QToolButton(PartDesignGui__TaskThicknessParameters);
        buttonRefSel->setObjectName("buttonRefSel");
        buttonRefSel->setCheckable(true);

        verticalLayout->addWidget(buttonRefSel);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskThicknessParameters);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout->addWidget(listWidgetReferences);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(PartDesignGui__TaskThicknessParameters);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        Value = new Gui::QuantitySpinBox(PartDesignGui__TaskThicknessParameters);
        Value->setObjectName("Value");
        Value->setKeyboardTracking(false);
        Value->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        Value->setMinimum(0.000000000000000);
        Value->setMaximum(999999999.000000000000000);
        Value->setSingleStep(0.100000000000000);
        Value->setValue(1.000000000000000);

        gridLayout_2->addWidget(Value, 0, 1, 1, 1);

        label_2 = new QLabel(PartDesignGui__TaskThicknessParameters);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        modeComboBox = new QComboBox(PartDesignGui__TaskThicknessParameters);
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->addItem(QString());
        modeComboBox->setObjectName("modeComboBox");

        gridLayout_2->addWidget(modeComboBox, 1, 1, 1, 1);

        label_3 = new QLabel(PartDesignGui__TaskThicknessParameters);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        joinComboBox = new QComboBox(PartDesignGui__TaskThicknessParameters);
        joinComboBox->addItem(QString());
        joinComboBox->addItem(QString());
        joinComboBox->setObjectName("joinComboBox");

        gridLayout_2->addWidget(joinComboBox, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        checkIntersection = new QCheckBox(PartDesignGui__TaskThicknessParameters);
        checkIntersection->setObjectName("checkIntersection");

        verticalLayout->addWidget(checkIntersection);

        checkReverse = new QCheckBox(PartDesignGui__TaskThicknessParameters);
        checkReverse->setObjectName("checkReverse");

        verticalLayout->addWidget(checkReverse);

        QWidget::setTabOrder(buttonRefSel, listWidgetReferences);
        QWidget::setTabOrder(listWidgetReferences, Value);
        QWidget::setTabOrder(Value, modeComboBox);
        QWidget::setTabOrder(modeComboBox, joinComboBox);
        QWidget::setTabOrder(joinComboBox, checkIntersection);
        QWidget::setTabOrder(checkIntersection, checkReverse);

        retranslateUi(PartDesignGui__TaskThicknessParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskThicknessParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskThicknessParameters)
    {
#if QT_CONFIG(tooltip)
        buttonRefSel->setToolTip(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Toggles between selection and preview mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonRefSel->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Select", nullptr));
#if QT_CONFIG(tooltip)
        listWidgetReferences->setToolTip(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "- select an item to highlight it\n"
"- double-click on an item to see the features", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Thickness", nullptr));
        label_2->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Mode", nullptr));
        modeComboBox->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Skin", nullptr));
        modeComboBox->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Pipe", nullptr));
        modeComboBox->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Recto verso", nullptr));

        label_3->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Join type", nullptr));
        joinComboBox->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Arc", nullptr));
        joinComboBox->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Intersection", nullptr));

        checkIntersection->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Intersection", nullptr));
        checkReverse->setText(QCoreApplication::translate("PartDesignGui::TaskThicknessParameters", "Make thickness inwards", nullptr));
        (void)PartDesignGui__TaskThicknessParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskThicknessParameters: public Ui_TaskThicknessParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKTHICKNESSPARAMETERS_H
