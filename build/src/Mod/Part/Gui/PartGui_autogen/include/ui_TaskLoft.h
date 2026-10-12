/********************************************************************************
** Form generated from reading UI file 'TaskLoft.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKLOFT_H
#define UI_TASKLOFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/Widgets.h"

namespace PartGui {

class Ui_TaskLoft
{
public:
    QGridLayout *gridLayout;
    Gui::ActionSelector *selector;
    QCheckBox *checkSolid;
    QCheckBox *checkRuledSurface;
    QCheckBox *checkClosed;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PartGui__TaskLoft)
    {
        if (PartGui__TaskLoft->objectName().isEmpty())
            PartGui__TaskLoft->setObjectName("PartGui__TaskLoft");
        PartGui__TaskLoft->resize(336, 326);
        gridLayout = new QGridLayout(PartGui__TaskLoft);
        gridLayout->setObjectName("gridLayout");
        selector = new Gui::ActionSelector(PartGui__TaskLoft);
        selector->setObjectName("selector");

        gridLayout->addWidget(selector, 0, 0, 1, 4);

        checkSolid = new QCheckBox(PartGui__TaskLoft);
        checkSolid->setObjectName("checkSolid");
        checkSolid->setChecked(true);

        gridLayout->addWidget(checkSolid, 1, 0, 1, 1);

        checkRuledSurface = new QCheckBox(PartGui__TaskLoft);
        checkRuledSurface->setObjectName("checkRuledSurface");

        gridLayout->addWidget(checkRuledSurface, 1, 1, 1, 1);

        checkClosed = new QCheckBox(PartGui__TaskLoft);
        checkClosed->setObjectName("checkClosed");

        gridLayout->addWidget(checkClosed, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(130, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);


        retranslateUi(PartGui__TaskLoft);

        QMetaObject::connectSlotsByName(PartGui__TaskLoft);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskLoft)
    {
        PartGui__TaskLoft->setWindowTitle(QCoreApplication::translate("PartGui::TaskLoft", "Loft", nullptr));
        checkSolid->setText(QCoreApplication::translate("PartGui::TaskLoft", "Create solid", nullptr));
        checkRuledSurface->setText(QCoreApplication::translate("PartGui::TaskLoft", "Ruled surface", nullptr));
        checkClosed->setText(QCoreApplication::translate("PartGui::TaskLoft", "Closed", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskLoft: public Ui_TaskLoft {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKLOFT_H
