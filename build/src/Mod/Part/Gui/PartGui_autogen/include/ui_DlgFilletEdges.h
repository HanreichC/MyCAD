/********************************************************************************
** Form generated from reading UI file 'DlgFilletEdges.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGFILLETEDGES_H
#define UI_DLGFILLETEDGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_DlgFilletEdges
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QComboBox *shapeObject;
    QGroupBox *parameterName;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QRadioButton *selectEdges;
    QRadioButton *selectFaces;
    QPushButton *selectAllButton;
    QPushButton *selectNoneButton;
    QSpacerItem *horizontalSpacer;
    QLabel *labelfillet;
    QComboBox *filletType;
    QTreeView *treeView;
    QHBoxLayout *hboxLayout1;
    QLabel *labelRadius;
    Gui::QuantitySpinBox *filletStartRadius;
    Gui::QuantitySpinBox *filletEndRadius;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *PartGui__DlgFilletEdges)
    {
        if (PartGui__DlgFilletEdges->objectName().isEmpty())
            PartGui__DlgFilletEdges->setObjectName("PartGui__DlgFilletEdges");
        PartGui__DlgFilletEdges->resize(290, 441);
        gridLayout_3 = new QGridLayout(PartGui__DlgFilletEdges);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(PartGui__DlgFilletEdges);
        groupBox->setObjectName("groupBox");
        hboxLayout = new QHBoxLayout(groupBox);
#ifndef Q_OS_MACOS
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        hboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        shapeObject = new QComboBox(groupBox);
        shapeObject->addItem(QString());
        shapeObject->setObjectName("shapeObject");

        hboxLayout->addWidget(shapeObject);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        parameterName = new QGroupBox(PartGui__DlgFilletEdges);
        parameterName->setObjectName("parameterName");
        gridLayout_2 = new QGridLayout(parameterName);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox_3 = new QGroupBox(parameterName);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName("gridLayout");
        selectEdges = new QRadioButton(groupBox_3);
        selectEdges->setObjectName("selectEdges");
        selectEdges->setChecked(true);

        gridLayout->addWidget(selectEdges, 0, 0, 1, 2);

        selectFaces = new QRadioButton(groupBox_3);
        selectFaces->setObjectName("selectFaces");

        gridLayout->addWidget(selectFaces, 0, 2, 1, 2);

        selectAllButton = new QPushButton(groupBox_3);
        selectAllButton->setObjectName("selectAllButton");

        gridLayout->addWidget(selectAllButton, 1, 0, 1, 1);

        selectNoneButton = new QPushButton(groupBox_3);
        selectNoneButton->setObjectName("selectNoneButton");

        gridLayout->addWidget(selectNoneButton, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(221, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 2);

        labelfillet = new QLabel(parameterName);
        labelfillet->setObjectName("labelfillet");

        gridLayout_2->addWidget(labelfillet, 1, 0, 1, 1);

        filletType = new QComboBox(parameterName);
        filletType->addItem(QString());
        filletType->addItem(QString());
        filletType->setObjectName("filletType");

        gridLayout_2->addWidget(filletType, 1, 1, 1, 1);

        treeView = new QTreeView(parameterName);
        treeView->setObjectName("treeView");

        gridLayout_2->addWidget(treeView, 2, 0, 1, 2);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName("hboxLayout1");
        labelRadius = new QLabel(parameterName);
        labelRadius->setObjectName("labelRadius");

        hboxLayout1->addWidget(labelRadius);

        filletStartRadius = new Gui::QuantitySpinBox(parameterName);
        filletStartRadius->setObjectName("filletStartRadius");
        filletStartRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        filletStartRadius->setSingleStep(0.100000000000000);
        filletStartRadius->setValue(1.000000000000000);

        hboxLayout1->addWidget(filletStartRadius);

        filletEndRadius = new Gui::QuantitySpinBox(parameterName);
        filletEndRadius->setObjectName("filletEndRadius");
        filletEndRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        filletEndRadius->setSingleStep(0.100000000000000);
        filletEndRadius->setValue(1.000000000000000);

        hboxLayout1->addWidget(filletEndRadius);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem);


        gridLayout_2->addLayout(hboxLayout1, 3, 0, 1, 2);


        gridLayout_3->addWidget(parameterName, 1, 0, 1, 1);

        QWidget::setTabOrder(shapeObject, filletType);
        QWidget::setTabOrder(filletType, treeView);
        QWidget::setTabOrder(treeView, filletStartRadius);
        QWidget::setTabOrder(filletStartRadius, filletEndRadius);

        retranslateUi(PartGui__DlgFilletEdges);

        QMetaObject::connectSlotsByName(PartGui__DlgFilletEdges);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgFilletEdges)
    {
        PartGui__DlgFilletEdges->setWindowTitle(QCoreApplication::translate("PartGui::DlgFilletEdges", "Fillet Edges", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgFilletEdges", "Shape", nullptr));
        label->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "Selected shape", nullptr));
        shapeObject->setItemText(0, QCoreApplication::translate("PartGui::DlgFilletEdges", "No selection", nullptr));

        parameterName->setTitle(QCoreApplication::translate("PartGui::DlgFilletEdges", "Parameters", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PartGui::DlgFilletEdges", "Selection", nullptr));
        selectEdges->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "Select edges", nullptr));
        selectFaces->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "Select faces", nullptr));
        selectAllButton->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "All", nullptr));
        selectNoneButton->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "None", nullptr));
        labelfillet->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "Type", nullptr));
        filletType->setItemText(0, QCoreApplication::translate("PartGui::DlgFilletEdges", "Constant radius", nullptr));
        filletType->setItemText(1, QCoreApplication::translate("PartGui::DlgFilletEdges", "Variable radius", nullptr));

        labelRadius->setText(QCoreApplication::translate("PartGui::DlgFilletEdges", "Radius", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgFilletEdges: public Ui_DlgFilletEdges {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGFILLETEDGES_H
