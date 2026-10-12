/********************************************************************************
** Form generated from reading UI file 'CrossSections.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROSSSECTIONS_H
#define UI_CROSSSECTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include "Gui/QuantitySpinBox.h"

namespace MeshPartGui {

class Ui_CrossSections
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *planeBox;
    QGridLayout *gridLayout;
    QRadioButton *xyPlane;
    QRadioButton *xzPlane;
    QRadioButton *yzPlane;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::QuantitySpinBox *position;
    QGroupBox *sectionsBox;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBothSides;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QSpinBox *countSections;
    QLabel *label_2;
    Gui::QuantitySpinBox *distance;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBoxConnect;
    QDoubleSpinBox *spinEpsilon;

    void setupUi(QDialog *MeshPartGui__CrossSections)
    {
        if (MeshPartGui__CrossSections->objectName().isEmpty())
            MeshPartGui__CrossSections->setObjectName("MeshPartGui__CrossSections");
        MeshPartGui__CrossSections->resize(309, 269);
        gridLayout_4 = new QGridLayout(MeshPartGui__CrossSections);
        gridLayout_4->setObjectName("gridLayout_4");
        planeBox = new QGroupBox(MeshPartGui__CrossSections);
        planeBox->setObjectName("planeBox");
        gridLayout = new QGridLayout(planeBox);
        gridLayout->setObjectName("gridLayout");
        xyPlane = new QRadioButton(planeBox);
        xyPlane->setObjectName("xyPlane");
        xyPlane->setChecked(true);

        gridLayout->addWidget(xyPlane, 0, 0, 1, 1);

        xzPlane = new QRadioButton(planeBox);
        xzPlane->setObjectName("xzPlane");

        gridLayout->addWidget(xzPlane, 0, 1, 1, 1);

        yzPlane = new QRadioButton(planeBox);
        yzPlane->setObjectName("yzPlane");

        gridLayout->addWidget(yzPlane, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(planeBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        position = new Gui::QuantitySpinBox(planeBox);
        position->setObjectName("position");
        position->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        horizontalLayout->addWidget(position);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);


        gridLayout_4->addWidget(planeBox, 0, 0, 1, 1);

        sectionsBox = new QGroupBox(MeshPartGui__CrossSections);
        sectionsBox->setObjectName("sectionsBox");
        sectionsBox->setCheckable(true);
        sectionsBox->setChecked(false);
        gridLayout_3 = new QGridLayout(sectionsBox);
        gridLayout_3->setObjectName("gridLayout_3");
        checkBothSides = new QCheckBox(sectionsBox);
        checkBothSides->setObjectName("checkBothSides");

        gridLayout_3->addWidget(checkBothSides, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_3 = new QLabel(sectionsBox);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        countSections = new QSpinBox(sectionsBox);
        countSections->setObjectName("countSections");
        countSections->setMinimum(1);
        countSections->setMaximum(2000000);

        gridLayout_2->addWidget(countSections, 0, 1, 1, 1);

        label_2 = new QLabel(sectionsBox);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        distance = new Gui::QuantitySpinBox(sectionsBox);
        distance->setObjectName("distance");
        distance->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_2->addWidget(distance, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);


        gridLayout_4->addWidget(sectionsBox, 1, 0, 1, 1);

        groupBox = new QGroupBox(MeshPartGui__CrossSections);
        groupBox->setObjectName("groupBox");
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName("gridLayout_5");
        checkBoxConnect = new QCheckBox(groupBox);
        checkBoxConnect->setObjectName("checkBoxConnect");

        gridLayout_5->addWidget(checkBoxConnect, 0, 0, 1, 1);

        spinEpsilon = new QDoubleSpinBox(groupBox);
        spinEpsilon->setObjectName("spinEpsilon");
        spinEpsilon->setEnabled(false);
        spinEpsilon->setDecimals(4);
        spinEpsilon->setValue(0.020000000000000);

        gridLayout_5->addWidget(spinEpsilon, 0, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 2, 0, 1, 1);

        QWidget::setTabOrder(xyPlane, xzPlane);
        QWidget::setTabOrder(xzPlane, yzPlane);
        QWidget::setTabOrder(yzPlane, position);
        QWidget::setTabOrder(position, sectionsBox);
        QWidget::setTabOrder(sectionsBox, checkBothSides);
        QWidget::setTabOrder(checkBothSides, countSections);
        QWidget::setTabOrder(countSections, distance);

        retranslateUi(MeshPartGui__CrossSections);
        QObject::connect(checkBoxConnect, &QCheckBox::toggled, spinEpsilon, &QDoubleSpinBox::setEnabled);

        QMetaObject::connectSlotsByName(MeshPartGui__CrossSections);
    } // setupUi

    void retranslateUi(QDialog *MeshPartGui__CrossSections)
    {
        MeshPartGui__CrossSections->setWindowTitle(QCoreApplication::translate("MeshPartGui::CrossSections", "Cross Sections", nullptr));
        planeBox->setTitle(QCoreApplication::translate("MeshPartGui::CrossSections", "Guiding Plane", nullptr));
        xyPlane->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "XY", nullptr));
        xzPlane->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "XZ", nullptr));
        yzPlane->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "YZ", nullptr));
        label->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "Position", nullptr));
        sectionsBox->setTitle(QCoreApplication::translate("MeshPartGui::CrossSections", "Sections", nullptr));
        checkBothSides->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "On both sides", nullptr));
        label_3->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "Count", nullptr));
        label_2->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "Distance", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MeshPartGui::CrossSections", "Options", nullptr));
        checkBoxConnect->setText(QCoreApplication::translate("MeshPartGui::CrossSections", "Connect edges if distance less than", nullptr));
    } // retranslateUi

};

} // namespace MeshPartGui

namespace MeshPartGui {
namespace Ui {
    class CrossSections: public Ui_CrossSections {};
} // namespace Ui
} // namespace MeshPartGui

#endif // UI_CROSSSECTIONS_H
