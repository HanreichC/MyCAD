/********************************************************************************
** Form generated from reading UI file 'Segmentation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGMENTATION_H
#define UI_SEGMENTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

namespace MeshGui {

class Ui_Segmentation
{
public:
    QGridLayout *gridLayout_4;
    QCheckBox *checkBoxSmooth;
    QSpinBox *smoothSteps;
    QGroupBox *groupBoxPln;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *tolPln;
    QLabel *label_2;
    QSpinBox *numPln;
    QGroupBox *groupBoxCyl;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *crvCyl;
    QLabel *label_4;
    QDoubleSpinBox *tol1Cyl;
    QLabel *label_9;
    QDoubleSpinBox *tol2Cyl;
    QLabel *label_5;
    QSpinBox *numCyl;
    QGroupBox *groupBoxSph;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QDoubleSpinBox *crvSph;
    QLabel *label_7;
    QDoubleSpinBox *tolSph;
    QLabel *label_8;
    QSpinBox *numSph;
    QGroupBox *groupBoxFree;
    QGridLayout *gridLayout_5;
    QLabel *label_10;
    QDoubleSpinBox *crv1Free;
    QLabel *label_11;
    QDoubleSpinBox *tol1Free;
    QLabel *label_12;
    QDoubleSpinBox *crv2Free;
    QLabel *label_13;
    QDoubleSpinBox *tol2Free;
    QLabel *label_14;
    QSpinBox *numFree;

    void setupUi(QWidget *MeshGui__Segmentation)
    {
        if (MeshGui__Segmentation->objectName().isEmpty())
            MeshGui__Segmentation->setObjectName("MeshGui__Segmentation");
        MeshGui__Segmentation->resize(289, 379);
        gridLayout_4 = new QGridLayout(MeshGui__Segmentation);
        gridLayout_4->setObjectName("gridLayout_4");
        checkBoxSmooth = new QCheckBox(MeshGui__Segmentation);
        checkBoxSmooth->setObjectName("checkBoxSmooth");
        checkBoxSmooth->setChecked(true);

        gridLayout_4->addWidget(checkBoxSmooth, 0, 0, 1, 1);

        smoothSteps = new QSpinBox(MeshGui__Segmentation);
        smoothSteps->setObjectName("smoothSteps");
        smoothSteps->setValue(3);

        gridLayout_4->addWidget(smoothSteps, 0, 1, 1, 1);

        groupBoxPln = new QGroupBox(MeshGui__Segmentation);
        groupBoxPln->setObjectName("groupBoxPln");
        groupBoxPln->setCheckable(true);
        gridLayout = new QGridLayout(groupBoxPln);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBoxPln);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tolPln = new QDoubleSpinBox(groupBoxPln);
        tolPln->setObjectName("tolPln");
        tolPln->setSingleStep(0.010000000000000);
        tolPln->setValue(0.010000000000000);

        gridLayout->addWidget(tolPln, 0, 1, 1, 1);

        label_2 = new QLabel(groupBoxPln);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        numPln = new QSpinBox(groupBoxPln);
        numPln->setObjectName("numPln");
        numPln->setMaximum(100000);
        numPln->setValue(100);

        gridLayout->addWidget(numPln, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxPln, 1, 0, 1, 2);

        groupBoxCyl = new QGroupBox(MeshGui__Segmentation);
        groupBoxCyl->setObjectName("groupBoxCyl");
        groupBoxCyl->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupBoxCyl);
        gridLayout_2->setObjectName("gridLayout_2");
        label_3 = new QLabel(groupBoxCyl);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        crvCyl = new QDoubleSpinBox(groupBoxCyl);
        crvCyl->setObjectName("crvCyl");
        crvCyl->setSingleStep(0.010000000000000);
        crvCyl->setValue(0.200000000000000);

        gridLayout_2->addWidget(crvCyl, 0, 1, 1, 1);

        label_4 = new QLabel(groupBoxCyl);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        tol1Cyl = new QDoubleSpinBox(groupBoxCyl);
        tol1Cyl->setObjectName("tol1Cyl");
        tol1Cyl->setSingleStep(0.010000000000000);
        tol1Cyl->setValue(0.010000000000000);

        gridLayout_2->addWidget(tol1Cyl, 1, 1, 1, 1);

        label_9 = new QLabel(groupBoxCyl);
        label_9->setObjectName("label_9");

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        tol2Cyl = new QDoubleSpinBox(groupBoxCyl);
        tol2Cyl->setObjectName("tol2Cyl");
        tol2Cyl->setSingleStep(0.010000000000000);
        tol2Cyl->setValue(0.010000000000000);

        gridLayout_2->addWidget(tol2Cyl, 2, 1, 1, 1);

        label_5 = new QLabel(groupBoxCyl);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        numCyl = new QSpinBox(groupBoxCyl);
        numCyl->setObjectName("numCyl");
        numCyl->setMaximum(100000);
        numCyl->setValue(100);

        gridLayout_2->addWidget(numCyl, 3, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxCyl, 2, 0, 1, 2);

        groupBoxSph = new QGroupBox(MeshGui__Segmentation);
        groupBoxSph->setObjectName("groupBoxSph");
        groupBoxSph->setCheckable(true);
        gridLayout_3 = new QGridLayout(groupBoxSph);
        gridLayout_3->setObjectName("gridLayout_3");
        label_6 = new QLabel(groupBoxSph);
        label_6->setObjectName("label_6");

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        crvSph = new QDoubleSpinBox(groupBoxSph);
        crvSph->setObjectName("crvSph");
        crvSph->setSingleStep(0.010000000000000);
        crvSph->setValue(0.200000000000000);

        gridLayout_3->addWidget(crvSph, 0, 1, 1, 1);

        label_7 = new QLabel(groupBoxSph);
        label_7->setObjectName("label_7");

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        tolSph = new QDoubleSpinBox(groupBoxSph);
        tolSph->setObjectName("tolSph");
        tolSph->setSingleStep(0.010000000000000);
        tolSph->setValue(0.010000000000000);

        gridLayout_3->addWidget(tolSph, 1, 1, 1, 1);

        label_8 = new QLabel(groupBoxSph);
        label_8->setObjectName("label_8");

        gridLayout_3->addWidget(label_8, 2, 0, 1, 1);

        numSph = new QSpinBox(groupBoxSph);
        numSph->setObjectName("numSph");
        numSph->setMaximum(100000);
        numSph->setValue(100);

        gridLayout_3->addWidget(numSph, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxSph, 3, 0, 1, 2);

        groupBoxFree = new QGroupBox(MeshGui__Segmentation);
        groupBoxFree->setObjectName("groupBoxFree");
        groupBoxFree->setCheckable(true);
        gridLayout_5 = new QGridLayout(groupBoxFree);
        gridLayout_5->setObjectName("gridLayout_5");
        label_10 = new QLabel(groupBoxFree);
        label_10->setObjectName("label_10");

        gridLayout_5->addWidget(label_10, 0, 0, 1, 1);

        crv1Free = new QDoubleSpinBox(groupBoxFree);
        crv1Free->setObjectName("crv1Free");
        crv1Free->setSingleStep(0.010000000000000);
        crv1Free->setValue(0.200000000000000);

        gridLayout_5->addWidget(crv1Free, 0, 1, 1, 1);

        label_11 = new QLabel(groupBoxFree);
        label_11->setObjectName("label_11");

        gridLayout_5->addWidget(label_11, 1, 0, 1, 1);

        tol1Free = new QDoubleSpinBox(groupBoxFree);
        tol1Free->setObjectName("tol1Free");
        tol1Free->setSingleStep(0.010000000000000);
        tol1Free->setValue(0.010000000000000);

        gridLayout_5->addWidget(tol1Free, 1, 1, 1, 1);

        label_12 = new QLabel(groupBoxFree);
        label_12->setObjectName("label_12");

        gridLayout_5->addWidget(label_12, 2, 0, 1, 1);

        crv2Free = new QDoubleSpinBox(groupBoxFree);
        crv2Free->setObjectName("crv2Free");
        crv2Free->setSingleStep(0.010000000000000);
        crv2Free->setValue(0.200000000000000);

        gridLayout_5->addWidget(crv2Free, 2, 1, 1, 1);

        label_13 = new QLabel(groupBoxFree);
        label_13->setObjectName("label_13");

        gridLayout_5->addWidget(label_13, 3, 0, 1, 1);

        tol2Free = new QDoubleSpinBox(groupBoxFree);
        tol2Free->setObjectName("tol2Free");
        tol2Free->setSingleStep(0.010000000000000);
        tol2Free->setValue(0.010000000000000);

        gridLayout_5->addWidget(tol2Free, 3, 1, 1, 1);

        label_14 = new QLabel(groupBoxFree);
        label_14->setObjectName("label_14");

        gridLayout_5->addWidget(label_14, 4, 0, 1, 1);

        numFree = new QSpinBox(groupBoxFree);
        numFree->setObjectName("numFree");
        numFree->setMaximum(100000);
        numFree->setValue(100);

        gridLayout_5->addWidget(numFree, 4, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxFree, 4, 0, 1, 2);


        retranslateUi(MeshGui__Segmentation);
        QObject::connect(checkBoxSmooth, &QCheckBox::toggled, smoothSteps, &QSpinBox::setEnabled);

        QMetaObject::connectSlotsByName(MeshGui__Segmentation);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__Segmentation)
    {
        MeshGui__Segmentation->setWindowTitle(QCoreApplication::translate("MeshGui::Segmentation", "Mesh Segmentation", nullptr));
        checkBoxSmooth->setText(QCoreApplication::translate("MeshGui::Segmentation", "Smooth mesh", nullptr));
        groupBoxPln->setTitle(QCoreApplication::translate("MeshGui::Segmentation", "Plane", nullptr));
        label->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance", nullptr));
        label_2->setText(QCoreApplication::translate("MeshGui::Segmentation", "Minimum number of faces", nullptr));
        groupBoxCyl->setTitle(QCoreApplication::translate("MeshGui::Segmentation", "Cylinder", nullptr));
        label_3->setText(QCoreApplication::translate("MeshGui::Segmentation", "Curvature", nullptr));
        label_4->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance (flat)", nullptr));
        label_9->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance (curved)", nullptr));
        label_5->setText(QCoreApplication::translate("MeshGui::Segmentation", "Minimum number of faces", nullptr));
        groupBoxSph->setTitle(QCoreApplication::translate("MeshGui::Segmentation", "Sphere", nullptr));
        label_6->setText(QCoreApplication::translate("MeshGui::Segmentation", "Curvature", nullptr));
        label_7->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance", nullptr));
        label_8->setText(QCoreApplication::translate("MeshGui::Segmentation", "Minimum number of faces", nullptr));
        groupBoxFree->setTitle(QCoreApplication::translate("MeshGui::Segmentation", "Freeform", nullptr));
        label_10->setText(QCoreApplication::translate("MeshGui::Segmentation", "Maximum curvature", nullptr));
        label_11->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance", nullptr));
        label_12->setText(QCoreApplication::translate("MeshGui::Segmentation", "Minimum curvature", nullptr));
        label_13->setText(QCoreApplication::translate("MeshGui::Segmentation", "Tolerance", nullptr));
        label_14->setText(QCoreApplication::translate("MeshGui::Segmentation", "Minimum number of faces", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class Segmentation: public Ui_Segmentation {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_SEGMENTATION_H
