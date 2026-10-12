/********************************************************************************
** Form generated from reading UI file 'TaskSweep.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSWEEP_H
#define UI_TASKSWEEP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/Widgets.h"

namespace PartGui {

class Ui_TaskSweep
{
public:
    QGridLayout *gridLayout;
    Gui::ActionSelector *selector;
    QPushButton *buttonPath;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelPath;
    QCheckBox *checkSolid;
    QCheckBox *checkFrenet;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PartGui__TaskSweep)
    {
        if (PartGui__TaskSweep->objectName().isEmpty())
            PartGui__TaskSweep->setObjectName("PartGui__TaskSweep");
        PartGui__TaskSweep->resize(333, 434);
        gridLayout = new QGridLayout(PartGui__TaskSweep);
        gridLayout->setObjectName("gridLayout");
        selector = new Gui::ActionSelector(PartGui__TaskSweep);
        selector->setObjectName("selector");

        gridLayout->addWidget(selector, 0, 0, 1, 3);

        buttonPath = new QPushButton(PartGui__TaskSweep);
        buttonPath->setObjectName("buttonPath");
        buttonPath->setCheckable(true);

        gridLayout->addWidget(buttonPath, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(224, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 2);

        labelPath = new QLabel(PartGui__TaskSweep);
        labelPath->setObjectName("labelPath");
        labelPath->setText(QString::fromUtf8("TextLabel"));

        gridLayout->addWidget(labelPath, 2, 0, 1, 3);

        checkSolid = new QCheckBox(PartGui__TaskSweep);
        checkSolid->setObjectName("checkSolid");
        checkSolid->setChecked(true);

        gridLayout->addWidget(checkSolid, 3, 0, 1, 1);

        checkFrenet = new QCheckBox(PartGui__TaskSweep);
        checkFrenet->setObjectName("checkFrenet");
        checkFrenet->setChecked(true);

        gridLayout->addWidget(checkFrenet, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(130, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 2, 1, 1);


        retranslateUi(PartGui__TaskSweep);

        QMetaObject::connectSlotsByName(PartGui__TaskSweep);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskSweep)
    {
        PartGui__TaskSweep->setWindowTitle(QCoreApplication::translate("PartGui::TaskSweep", "Sweep", nullptr));
        buttonPath->setText(QCoreApplication::translate("PartGui::TaskSweep", "Sweep Path", nullptr));
        checkSolid->setText(QCoreApplication::translate("PartGui::TaskSweep", "Create solid", nullptr));
        checkFrenet->setText(QCoreApplication::translate("PartGui::TaskSweep", "Frenet", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskSweep: public Ui_TaskSweep {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKSWEEP_H
