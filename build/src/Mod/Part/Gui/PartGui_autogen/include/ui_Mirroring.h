/********************************************************************************
** Form generated from reading UI file 'Mirroring.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIRRORING_H
#define UI_MIRRORING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_Mirroring
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    Gui::QuantitySpinBox *baseX;
    QLabel *label_4;
    Gui::QuantitySpinBox *baseY;
    QLabel *label_5;
    Gui::QuantitySpinBox *baseZ;
    QLabel *label;
    QComboBox *comboBox;
    QTreeWidget *shapes;
    QPushButton *selectButton;
    QLineEdit *referenceLineEdit;

    void setupUi(QWidget *PartGui__Mirroring)
    {
        if (PartGui__Mirroring->objectName().isEmpty())
            PartGui__Mirroring->setObjectName("PartGui__Mirroring");
        PartGui__Mirroring->resize(279, 543);
        gridLayout_2 = new QGridLayout(PartGui__Mirroring);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(PartGui__Mirroring);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        baseX = new Gui::QuantitySpinBox(groupBox);
        baseX->setObjectName("baseX");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(baseX->sizePolicy().hasHeightForWidth());
        baseX->setSizePolicy(sizePolicy);
        baseX->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(baseX, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        baseY = new Gui::QuantitySpinBox(groupBox);
        baseY->setObjectName("baseY");
        sizePolicy.setHeightForWidth(baseY->sizePolicy().hasHeightForWidth());
        baseY->setSizePolicy(sizePolicy);
        baseY->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(baseY, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        baseZ = new Gui::QuantitySpinBox(groupBox);
        baseZ->setObjectName("baseZ");
        sizePolicy.setHeightForWidth(baseZ->sizePolicy().hasHeightForWidth());
        baseZ->setSizePolicy(sizePolicy);
        baseZ->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(baseZ, 2, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 3, 0, 1, 2);

        label = new QLabel(PartGui__Mirroring);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        comboBox = new QComboBox(PartGui__Mirroring);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout_2->addWidget(comboBox, 1, 1, 1, 1);

        shapes = new QTreeWidget(PartGui__Mirroring);
        shapes->setObjectName("shapes");
        shapes->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::EditKeyPressed);
        shapes->setSelectionMode(QAbstractItemView::ExtendedSelection);
        shapes->setRootIsDecorated(false);
        shapes->setExpandsOnDoubleClick(false);

        gridLayout_2->addWidget(shapes, 0, 0, 1, 2);

        selectButton = new QPushButton(PartGui__Mirroring);
        selectButton->setObjectName("selectButton");
        selectButton->setCheckable(true);
        selectButton->setChecked(true);

        gridLayout_2->addWidget(selectButton, 2, 0, 1, 1);

        referenceLineEdit = new QLineEdit(PartGui__Mirroring);
        referenceLineEdit->setObjectName("referenceLineEdit");
        referenceLineEdit->setReadOnly(true);

        gridLayout_2->addWidget(referenceLineEdit, 2, 1, 1, 1);


        retranslateUi(PartGui__Mirroring);

        QMetaObject::connectSlotsByName(PartGui__Mirroring);
    } // setupUi

    void retranslateUi(QWidget *PartGui__Mirroring)
    {
        PartGui__Mirroring->setWindowTitle(QCoreApplication::translate("PartGui::Mirroring", "Mirror", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::Mirroring", "Base Point", nullptr));
        label_3->setText(QCoreApplication::translate("PartGui::Mirroring", "X", nullptr));
        label_4->setText(QCoreApplication::translate("PartGui::Mirroring", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("PartGui::Mirroring", "Z", nullptr));
        label->setText(QCoreApplication::translate("PartGui::Mirroring", "Mirror plane", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("PartGui::Mirroring", "XY-plane", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PartGui::Mirroring", "XZ-plane", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PartGui::Mirroring", "YZ-plane", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("PartGui::Mirroring", "Use selected reference", nullptr));

        QTreeWidgetItem *___qtreewidgetitem = shapes->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PartGui::Mirroring", "Shapes", nullptr));
        selectButton->setText(QCoreApplication::translate("PartGui::Mirroring", "Selecting", nullptr));
        referenceLineEdit->setPlaceholderText(QCoreApplication::translate("PartGui::Mirroring", "Mirror plane reference", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class Mirroring: public Ui_Mirroring {};
} // namespace Ui
} // namespace PartGui

#endif // UI_MIRRORING_H
