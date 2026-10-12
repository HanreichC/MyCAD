/********************************************************************************
** Form generated from reading UI file 'SegmentationBestFit.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGMENTATIONBESTFIT_H
#define UI_SEGMENTATIONBESTFIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

namespace MeshGui {

class Ui_SegmentationBestFit
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBoxPln;
    QGridLayout *gridLayout;
    QPushButton *planeParameters;
    QLabel *label;
    QDoubleSpinBox *tolPln;
    QLabel *label_2;
    QSpinBox *numPln;
    QGroupBox *groupBoxCyl;
    QGridLayout *gridLayout_2;
    QPushButton *cylinderParameters;
    QLabel *label_4;
    QDoubleSpinBox *tolCyl;
    QLabel *label_5;
    QSpinBox *numCyl;
    QGroupBox *groupBoxSph;
    QGridLayout *gridLayout_3;
    QPushButton *sphereParameters;
    QLabel *label_7;
    QDoubleSpinBox *tolSph;
    QLabel *label_8;
    QSpinBox *numSph;

    void setupUi(QWidget *MeshGui__SegmentationBestFit)
    {
        if (MeshGui__SegmentationBestFit->objectName().isEmpty())
            MeshGui__SegmentationBestFit->setObjectName("MeshGui__SegmentationBestFit");
        MeshGui__SegmentationBestFit->resize(289, 354);
        gridLayout_4 = new QGridLayout(MeshGui__SegmentationBestFit);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBoxPln = new QGroupBox(MeshGui__SegmentationBestFit);
        groupBoxPln->setObjectName("groupBoxPln");
        groupBoxPln->setCheckable(true);
        gridLayout = new QGridLayout(groupBoxPln);
        gridLayout->setObjectName("gridLayout");
        planeParameters = new QPushButton(groupBoxPln);
        planeParameters->setObjectName("planeParameters");

        gridLayout->addWidget(planeParameters, 0, 1, 1, 1);

        label = new QLabel(groupBoxPln);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        tolPln = new QDoubleSpinBox(groupBoxPln);
        tolPln->setObjectName("tolPln");
        tolPln->setSingleStep(0.010000000000000);
        tolPln->setValue(0.010000000000000);

        gridLayout->addWidget(tolPln, 1, 1, 1, 1);

        label_2 = new QLabel(groupBoxPln);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        numPln = new QSpinBox(groupBoxPln);
        numPln->setObjectName("numPln");
        numPln->setMaximum(100000);
        numPln->setValue(100);

        gridLayout->addWidget(numPln, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxPln, 0, 0, 1, 2);

        groupBoxCyl = new QGroupBox(MeshGui__SegmentationBestFit);
        groupBoxCyl->setObjectName("groupBoxCyl");
        groupBoxCyl->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupBoxCyl);
        gridLayout_2->setObjectName("gridLayout_2");
        cylinderParameters = new QPushButton(groupBoxCyl);
        cylinderParameters->setObjectName("cylinderParameters");

        gridLayout_2->addWidget(cylinderParameters, 0, 1, 1, 1);

        label_4 = new QLabel(groupBoxCyl);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        tolCyl = new QDoubleSpinBox(groupBoxCyl);
        tolCyl->setObjectName("tolCyl");
        tolCyl->setSingleStep(0.010000000000000);
        tolCyl->setValue(0.010000000000000);

        gridLayout_2->addWidget(tolCyl, 1, 1, 1, 1);

        label_5 = new QLabel(groupBoxCyl);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        numCyl = new QSpinBox(groupBoxCyl);
        numCyl->setObjectName("numCyl");
        numCyl->setMaximum(100000);
        numCyl->setValue(100);

        gridLayout_2->addWidget(numCyl, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxCyl, 1, 0, 1, 2);

        groupBoxSph = new QGroupBox(MeshGui__SegmentationBestFit);
        groupBoxSph->setObjectName("groupBoxSph");
        groupBoxSph->setCheckable(true);
        gridLayout_3 = new QGridLayout(groupBoxSph);
        gridLayout_3->setObjectName("gridLayout_3");
        sphereParameters = new QPushButton(groupBoxSph);
        sphereParameters->setObjectName("sphereParameters");

        gridLayout_3->addWidget(sphereParameters, 0, 1, 1, 1);

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


        gridLayout_4->addWidget(groupBoxSph, 2, 0, 1, 2);


        retranslateUi(MeshGui__SegmentationBestFit);

        QMetaObject::connectSlotsByName(MeshGui__SegmentationBestFit);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__SegmentationBestFit)
    {
        MeshGui__SegmentationBestFit->setWindowTitle(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Mesh Segmentation", nullptr));
        groupBoxPln->setTitle(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Plane", nullptr));
        planeParameters->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Parameters", nullptr));
        label->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Tolerance", nullptr));
        label_2->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Minimum number of faces", nullptr));
        groupBoxCyl->setTitle(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Cylinder", nullptr));
        cylinderParameters->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Parameters", nullptr));
        label_4->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Tolerance", nullptr));
        label_5->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Minimum number of faces", nullptr));
        groupBoxSph->setTitle(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Sphere", nullptr));
        sphereParameters->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Parameters", nullptr));
        label_7->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Tolerance", nullptr));
        label_8->setText(QCoreApplication::translate("MeshGui::SegmentationBestFit", "Minimum number of faces", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class SegmentationBestFit: public Ui_SegmentationBestFit {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_SEGMENTATIONBESTFIT_H
