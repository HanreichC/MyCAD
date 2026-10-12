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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

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

    void setupUi(QDialog *PartGui__CrossSections)
    {
        if (PartGui__CrossSections->objectName().isEmpty())
            PartGui__CrossSections->setObjectName("PartGui__CrossSections");
        PartGui__CrossSections->resize(235, 240);
        gridLayout_4 = new QGridLayout(PartGui__CrossSections);
        gridLayout_4->setObjectName("gridLayout_4");
        planeBox = new QGroupBox(PartGui__CrossSections);
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

        sectionsBox = new QGroupBox(PartGui__CrossSections);
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

        QWidget::setTabOrder(xyPlane, xzPlane);
        QWidget::setTabOrder(xzPlane, yzPlane);
        QWidget::setTabOrder(yzPlane, position);
        QWidget::setTabOrder(position, sectionsBox);
        QWidget::setTabOrder(sectionsBox, checkBothSides);
        QWidget::setTabOrder(checkBothSides, countSections);
        QWidget::setTabOrder(countSections, distance);

        retranslateUi(PartGui__CrossSections);

        QMetaObject::connectSlotsByName(PartGui__CrossSections);
    } // setupUi

    void retranslateUi(QDialog *PartGui__CrossSections)
    {
        PartGui__CrossSections->setWindowTitle(QCoreApplication::translate("PartGui::CrossSections", "Cross Sections", nullptr));
        planeBox->setTitle(QCoreApplication::translate("PartGui::CrossSections", "Guiding Plane", nullptr));
        xyPlane->setText(QCoreApplication::translate("PartGui::CrossSections", "XY", nullptr));
        xzPlane->setText(QCoreApplication::translate("PartGui::CrossSections", "XZ", nullptr));
        yzPlane->setText(QCoreApplication::translate("PartGui::CrossSections", "YZ", nullptr));
        label->setText(QCoreApplication::translate("PartGui::CrossSections", "Position", nullptr));
        sectionsBox->setTitle(QCoreApplication::translate("PartGui::CrossSections", "Sections", nullptr));
        checkBothSides->setText(QCoreApplication::translate("PartGui::CrossSections", "On both sides", nullptr));
        label_3->setText(QCoreApplication::translate("PartGui::CrossSections", "Count", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::CrossSections", "Distance", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class CrossSections: public Ui_CrossSections {};
} // namespace Ui
} // namespace PartGui

#endif // UI_CROSSSECTIONS_H
