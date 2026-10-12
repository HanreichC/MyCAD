/********************************************************************************
** Form generated from reading UI file 'DlgBooleanOperation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGBOOLEANOPERATION_H
#define UI_DLGBOOLEANOPERATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

namespace PartGui {

class Ui_DlgBooleanOperation
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QRadioButton *unionButton;
    QRadioButton *diffButton;
    QRadioButton *interButton;
    QRadioButton *sectionButton;
    QTreeWidget *firstShape;
    QTreeWidget *secondShape;
    QSpacerItem *horizontalSpacer;
    QPushButton *swapButton;

    void setupUi(QWidget *PartGui__DlgBooleanOperation)
    {
        if (PartGui__DlgBooleanOperation->objectName().isEmpty())
            PartGui__DlgBooleanOperation->setObjectName("PartGui__DlgBooleanOperation");
        PartGui__DlgBooleanOperation->resize(264, 408);
        gridLayout = new QGridLayout(PartGui__DlgBooleanOperation);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(PartGui__DlgBooleanOperation);
        groupBox->setObjectName("groupBox");
        gridLayout1 = new QGridLayout(groupBox);
#ifndef Q_OS_MACOS
        gridLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        gridLayout1->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout1->setObjectName("gridLayout1");
        unionButton = new QRadioButton(groupBox);
        unionButton->setObjectName("unionButton");
        unionButton->setChecked(true);

        gridLayout1->addWidget(unionButton, 0, 0, 1, 1);

        diffButton = new QRadioButton(groupBox);
        diffButton->setObjectName("diffButton");

        gridLayout1->addWidget(diffButton, 0, 1, 1, 1);

        interButton = new QRadioButton(groupBox);
        interButton->setObjectName("interButton");

        gridLayout1->addWidget(interButton, 1, 0, 1, 1);

        sectionButton = new QRadioButton(groupBox);
        sectionButton->setObjectName("sectionButton");

        gridLayout1->addWidget(sectionButton, 1, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 2);

        firstShape = new QTreeWidget(PartGui__DlgBooleanOperation);
        new QTreeWidgetItem(firstShape);
        new QTreeWidgetItem(firstShape);
        new QTreeWidgetItem(firstShape);
        new QTreeWidgetItem(firstShape);
        firstShape->setObjectName("firstShape");
        firstShape->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::EditKeyPressed);
        firstShape->setRootIsDecorated(false);
        firstShape->setExpandsOnDoubleClick(false);

        gridLayout->addWidget(firstShape, 1, 0, 1, 1);

        secondShape = new QTreeWidget(PartGui__DlgBooleanOperation);
        new QTreeWidgetItem(secondShape);
        new QTreeWidgetItem(secondShape);
        new QTreeWidgetItem(secondShape);
        new QTreeWidgetItem(secondShape);
        secondShape->setObjectName("secondShape");
        secondShape->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::EditKeyPressed);
        secondShape->setRootIsDecorated(false);
        secondShape->setExpandsOnDoubleClick(false);

        gridLayout->addWidget(secondShape, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(117, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        swapButton = new QPushButton(PartGui__DlgBooleanOperation);
        swapButton->setObjectName("swapButton");

        gridLayout->addWidget(swapButton, 2, 1, 1, 1);


        retranslateUi(PartGui__DlgBooleanOperation);

        QMetaObject::connectSlotsByName(PartGui__DlgBooleanOperation);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgBooleanOperation)
    {
        PartGui__DlgBooleanOperation->setWindowTitle(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Boolean Operation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Boolean Operation", nullptr));
        unionButton->setText(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Union", nullptr));
        diffButton->setText(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Difference", nullptr));
        interButton->setText(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Intersection", nullptr));
        sectionButton->setText(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Section", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = firstShape->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "First shape", nullptr));

        const bool __sortingEnabled = firstShape->isSortingEnabled();
        firstShape->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = firstShape->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Solids", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = firstShape->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Shells", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = firstShape->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Compounds", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = firstShape->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Faces", nullptr));
        firstShape->setSortingEnabled(__sortingEnabled);

        QTreeWidgetItem *___qtreewidgetitem5 = secondShape->headerItem();
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Second shape", nullptr));

        const bool __sortingEnabled1 = secondShape->isSortingEnabled();
        secondShape->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem6 = secondShape->topLevelItem(0);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Solids", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = secondShape->topLevelItem(1);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Shells", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = secondShape->topLevelItem(2);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Compounds", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = secondShape->topLevelItem(3);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("PartGui::DlgBooleanOperation", "Faces", nullptr));
        secondShape->setSortingEnabled(__sortingEnabled1);

        swapButton->setText(QCoreApplication::translate("PartGui::DlgBooleanOperation", "Swap Selection", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgBooleanOperation: public Ui_DlgBooleanOperation {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGBOOLEANOPERATION_H
