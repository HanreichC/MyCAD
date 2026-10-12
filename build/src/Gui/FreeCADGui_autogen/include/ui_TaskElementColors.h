/********************************************************************************
** Form generated from reading UI file 'TaskElementColors.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKELEMENTCOLORS_H
#define UI_TASKELEMENTCOLORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {

class Ui_TaskElementColors
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *objectLabel;
    QListWidget *elementList;
    QGridLayout *gridLayout_6;
    QPushButton *addSelection;
    QPushButton *hideSelection;
    QPushButton *removeSelection;
    QPushButton *removeAll;
    QPushButton *boxSelect;
    QCheckBox *recompute;
    QCheckBox *onTop;

    void setupUi(QWidget *Gui__TaskElementColors)
    {
        if (Gui__TaskElementColors->objectName().isEmpty())
            Gui__TaskElementColors->setObjectName("Gui__TaskElementColors");
        Gui__TaskElementColors->resize(483, 406);
        gridLayout_2 = new QGridLayout(Gui__TaskElementColors);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        objectLabel = new QLabel(Gui__TaskElementColors);
        objectLabel->setObjectName("objectLabel");

        verticalLayout->addWidget(objectLabel);

        elementList = new QListWidget(Gui__TaskElementColors);
        elementList->setObjectName("elementList");
        elementList->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(elementList);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        addSelection = new QPushButton(Gui__TaskElementColors);
        addSelection->setObjectName("addSelection");

        gridLayout_6->addWidget(addSelection, 0, 0, 1, 1);

        hideSelection = new QPushButton(Gui__TaskElementColors);
        hideSelection->setObjectName("hideSelection");

        gridLayout_6->addWidget(hideSelection, 0, 1, 1, 1);

        removeSelection = new QPushButton(Gui__TaskElementColors);
        removeSelection->setObjectName("removeSelection");

        gridLayout_6->addWidget(removeSelection, 0, 2, 1, 1);

        removeAll = new QPushButton(Gui__TaskElementColors);
        removeAll->setObjectName("removeAll");

        gridLayout_6->addWidget(removeAll, 0, 3, 1, 1);

        boxSelect = new QPushButton(Gui__TaskElementColors);
        boxSelect->setObjectName("boxSelect");

        gridLayout_6->addWidget(boxSelect, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_6, 3, 0, 1, 1);

        recompute = new QCheckBox(Gui__TaskElementColors);
        recompute->setObjectName("recompute");

        gridLayout_2->addWidget(recompute, 4, 0, 1, 1);

        onTop = new QCheckBox(Gui__TaskElementColors);
        onTop->setObjectName("onTop");

        gridLayout_2->addWidget(onTop, 5, 0, 1, 1);


        retranslateUi(Gui__TaskElementColors);

        QMetaObject::connectSlotsByName(Gui__TaskElementColors);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskElementColors)
    {
        Gui__TaskElementColors->setWindowTitle(QCoreApplication::translate("Gui::TaskElementColors", "Set Element Color", nullptr));
        objectLabel->setText(QCoreApplication::translate("Gui::TaskElementColors", "TextLabel", nullptr));
        addSelection->setText(QCoreApplication::translate("Gui::TaskElementColors", "Edit", nullptr));
        hideSelection->setText(QCoreApplication::translate("Gui::TaskElementColors", "Hide", nullptr));
        removeSelection->setText(QCoreApplication::translate("Gui::TaskElementColors", "Remove", nullptr));
        removeAll->setText(QCoreApplication::translate("Gui::TaskElementColors", "Remove All", nullptr));
        boxSelect->setText(QCoreApplication::translate("Gui::TaskElementColors", "Box Select", nullptr));
        recompute->setText(QCoreApplication::translate("Gui::TaskElementColors", "Recompute after commit", nullptr));
        onTop->setText(QCoreApplication::translate("Gui::TaskElementColors", "On top when selected", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class TaskElementColors: public Ui_TaskElementColors {};
} // namespace Ui
} // namespace Gui

#endif // UI_TASKELEMENTCOLORS_H
