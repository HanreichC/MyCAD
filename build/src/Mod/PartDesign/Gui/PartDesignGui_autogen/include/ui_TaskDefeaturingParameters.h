/********************************************************************************
** Form generated from reading UI file 'TaskDefeaturingParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKDEFEATURINGPARAMETERS_H
#define UI_TASKDEFEATURINGPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskDefeaturingParameters
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *buttonRefSel;
    QListWidget *listWidgetReferences;

    void setupUi(QWidget *PartDesignGui__TaskDefeaturingParameters)
    {
        if (PartDesignGui__TaskDefeaturingParameters->objectName().isEmpty())
            PartDesignGui__TaskDefeaturingParameters->setObjectName("PartDesignGui__TaskDefeaturingParameters");
        PartDesignGui__TaskDefeaturingParameters->resize(232, 120);
        PartDesignGui__TaskDefeaturingParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskDefeaturingParameters);
        verticalLayout->setObjectName("verticalLayout");
        buttonRefSel = new QToolButton(PartDesignGui__TaskDefeaturingParameters);
        buttonRefSel->setObjectName("buttonRefSel");
        buttonRefSel->setCheckable(true);

        verticalLayout->addWidget(buttonRefSel);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskDefeaturingParameters);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetReferences);

        QWidget::setTabOrder(buttonRefSel, listWidgetReferences);

        retranslateUi(PartDesignGui__TaskDefeaturingParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskDefeaturingParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskDefeaturingParameters)
    {
#if QT_CONFIG(tooltip)
        buttonRefSel->setToolTip(QCoreApplication::translate("PartDesignGui::TaskDefeaturingParameters", "Toggles selection mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonRefSel->setText(QCoreApplication::translate("PartDesignGui::TaskDefeaturingParameters", "Select", nullptr));
#if QT_CONFIG(tooltip)
        listWidgetReferences->setToolTip(QCoreApplication::translate("PartDesignGui::TaskDefeaturingParameters", "Select an item in the 3D view to highlight it", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)PartDesignGui__TaskDefeaturingParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskDefeaturingParameters: public Ui_TaskDefeaturingParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKDEFEATURINGPARAMETERS_H
