/********************************************************************************
** Form generated from reading UI file 'TaskDraftParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKDRAFTPARAMETERS_H
#define UI_TASKDRAFTPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_TaskDraftParameters
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *buttonRefSel;
    QListWidget *listWidgetReferences;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    Gui::QuantitySpinBox *draftAngle;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *buttonPlane;
    QLineEdit *linePlane;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *buttonLine;
    QLineEdit *lineLine;
    QCheckBox *checkReverse;

    void setupUi(QWidget *PartDesignGui__TaskDraftParameters)
    {
        if (PartDesignGui__TaskDraftParameters->objectName().isEmpty())
            PartDesignGui__TaskDraftParameters->setObjectName("PartDesignGui__TaskDraftParameters");
        PartDesignGui__TaskDraftParameters->resize(257, 285);
        PartDesignGui__TaskDraftParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskDraftParameters);
        verticalLayout->setObjectName("verticalLayout");
        buttonRefSel = new QToolButton(PartDesignGui__TaskDraftParameters);
        buttonRefSel->setObjectName("buttonRefSel");
        buttonRefSel->setCheckable(true);

        verticalLayout->addWidget(buttonRefSel);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskDraftParameters);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetReferences);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(PartDesignGui__TaskDraftParameters);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        draftAngle = new Gui::QuantitySpinBox(PartDesignGui__TaskDraftParameters);
        draftAngle->setObjectName("draftAngle");
        draftAngle->setKeyboardTracking(false);
        draftAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        draftAngle->setMinimum(0.000000000000000);
        draftAngle->setMaximum(89.999999999999986);
        draftAngle->setSingleStep(1.000000000000000);
        draftAngle->setValue(10.000000000000000);

        horizontalLayout_2->addWidget(draftAngle);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        buttonPlane = new QToolButton(PartDesignGui__TaskDraftParameters);
        buttonPlane->setObjectName("buttonPlane");
        buttonPlane->setCheckable(true);

        horizontalLayout_3->addWidget(buttonPlane);

        linePlane = new QLineEdit(PartDesignGui__TaskDraftParameters);
        linePlane->setObjectName("linePlane");

        horizontalLayout_3->addWidget(linePlane);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        buttonLine = new QToolButton(PartDesignGui__TaskDraftParameters);
        buttonLine->setObjectName("buttonLine");
        buttonLine->setCheckable(true);

        horizontalLayout_4->addWidget(buttonLine);

        lineLine = new QLineEdit(PartDesignGui__TaskDraftParameters);
        lineLine->setObjectName("lineLine");

        horizontalLayout_4->addWidget(lineLine);


        verticalLayout->addLayout(horizontalLayout_4);

        checkReverse = new QCheckBox(PartDesignGui__TaskDraftParameters);
        checkReverse->setObjectName("checkReverse");

        verticalLayout->addWidget(checkReverse);

        buttonRefSel->raise();
        checkReverse->raise();
        listWidgetReferences->raise();
        QWidget::setTabOrder(buttonRefSel, listWidgetReferences);
        QWidget::setTabOrder(listWidgetReferences, draftAngle);
        QWidget::setTabOrder(draftAngle, buttonPlane);
        QWidget::setTabOrder(buttonPlane, linePlane);
        QWidget::setTabOrder(linePlane, buttonLine);
        QWidget::setTabOrder(buttonLine, lineLine);
        QWidget::setTabOrder(lineLine, checkReverse);

        retranslateUi(PartDesignGui__TaskDraftParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskDraftParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskDraftParameters)
    {
#if QT_CONFIG(tooltip)
        buttonRefSel->setToolTip(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Toggles between selection and preview mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonRefSel->setText(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Select", nullptr));
#if QT_CONFIG(tooltip)
        listWidgetReferences->setToolTip(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "- select an item to highlight it\n"
"- double-click on an item to see the drafts", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Draft angle", nullptr));
        buttonPlane->setText(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Neutral Plane", nullptr));
        buttonLine->setText(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Pull Direction", nullptr));
        checkReverse->setText(QCoreApplication::translate("PartDesignGui::TaskDraftParameters", "Reverse pull direction", nullptr));
        (void)PartDesignGui__TaskDraftParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskDraftParameters: public Ui_TaskDraftParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKDRAFTPARAMETERS_H
