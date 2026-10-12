/********************************************************************************
** Form generated from reading UI file 'TaskFilletParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKFILLETPARAMETERS_H
#define UI_TASKFILLETPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_TaskFilletParameters
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *buttonRefSel;
    QListWidget *listWidgetReferences;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    Gui::QuantitySpinBox *filletRadius;
    QCheckBox *checkBoxUseAllEdges;

    void setupUi(QWidget *PartDesignGui__TaskFilletParameters)
    {
        if (PartDesignGui__TaskFilletParameters->objectName().isEmpty())
            PartDesignGui__TaskFilletParameters->setObjectName("PartDesignGui__TaskFilletParameters");
        PartDesignGui__TaskFilletParameters->resize(232, 181);
        PartDesignGui__TaskFilletParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskFilletParameters);
        verticalLayout->setObjectName("verticalLayout");
        buttonRefSel = new QToolButton(PartDesignGui__TaskFilletParameters);
        buttonRefSel->setObjectName("buttonRefSel");
        buttonRefSel->setCheckable(true);

        verticalLayout->addWidget(buttonRefSel);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskFilletParameters);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetReferences);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(PartDesignGui__TaskFilletParameters);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        filletRadius = new Gui::QuantitySpinBox(PartDesignGui__TaskFilletParameters);
        filletRadius->setObjectName("filletRadius");
        filletRadius->setKeyboardTracking(false);

        horizontalLayout_2->addWidget(filletRadius);


        verticalLayout->addLayout(horizontalLayout_2);

        checkBoxUseAllEdges = new QCheckBox(PartDesignGui__TaskFilletParameters);
        checkBoxUseAllEdges->setObjectName("checkBoxUseAllEdges");

        verticalLayout->addWidget(checkBoxUseAllEdges);

        QWidget::setTabOrder(buttonRefSel, listWidgetReferences);
        QWidget::setTabOrder(listWidgetReferences, filletRadius);
        QWidget::setTabOrder(filletRadius, checkBoxUseAllEdges);

        retranslateUi(PartDesignGui__TaskFilletParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskFilletParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskFilletParameters)
    {
#if QT_CONFIG(tooltip)
        buttonRefSel->setToolTip(QCoreApplication::translate("PartDesignGui::TaskFilletParameters", "Toggles between selection and preview mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonRefSel->setText(QCoreApplication::translate("PartDesignGui::TaskFilletParameters", "Select", nullptr));
#if QT_CONFIG(tooltip)
        listWidgetReferences->setToolTip(QCoreApplication::translate("PartDesignGui::TaskFilletParameters", "- select an item to highlight it\n"
"- double-click on an item to see the fillets", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("PartDesignGui::TaskFilletParameters", "Radius", nullptr));
        checkBoxUseAllEdges->setText(QCoreApplication::translate("PartDesignGui::TaskFilletParameters", "Use all edges", nullptr));
        (void)PartDesignGui__TaskFilletParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskFilletParameters: public Ui_TaskFilletParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKFILLETPARAMETERS_H
