/********************************************************************************
** Form generated from reading UI file 'TaskCurveOnMesh.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKCURVEONMESH_H
#define UI_TASKCURVEONMESH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace MeshPartGui {

class Ui_TaskCurveOnMesh
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLabel *lb_instructions;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label_5;
    Gui::QuantitySpinBox *splitAngle;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *meshTolerance;
    QLabel *label_2;
    QComboBox *continuity;
    QLabel *label_3;
    QComboBox *maxDegree;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MeshPartGui__TaskCurveOnMesh)
    {
        if (MeshPartGui__TaskCurveOnMesh->objectName().isEmpty())
            MeshPartGui__TaskCurveOnMesh->setObjectName("MeshPartGui__TaskCurveOnMesh");
        MeshPartGui__TaskCurveOnMesh->resize(507, 637);
        gridLayout_3 = new QGridLayout(MeshPartGui__TaskCurveOnMesh);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox_3 = new QGroupBox(MeshPartGui__TaskCurveOnMesh);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName("verticalLayout");
        lb_instructions = new QLabel(groupBox_3);
        lb_instructions->setObjectName("lb_instructions");
        lb_instructions->setWordWrap(true);

        verticalLayout->addWidget(lb_instructions);


        gridLayout_3->addWidget(groupBox_3, 0, 0, 1, 2);

        groupBox = new QGroupBox(MeshPartGui__TaskCurveOnMesh);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setValue(10);

        gridLayout_2->addWidget(spinBox, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        splitAngle = new Gui::QuantitySpinBox(groupBox);
        splitAngle->setObjectName("splitAngle");
        splitAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        splitAngle->setMinimum(5.000000000000000);
        splitAngle->setMaximum(180.000000000000000);
        splitAngle->setValue(45.000000000000000);

        gridLayout_2->addWidget(splitAngle, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 2);

        groupBox_2 = new QGroupBox(MeshPartGui__TaskCurveOnMesh);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setCheckable(true);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        meshTolerance = new QDoubleSpinBox(groupBox_2);
        meshTolerance->setObjectName("meshTolerance");
        meshTolerance->setDecimals(3);
        meshTolerance->setMinimum(0.001000000000000);
        meshTolerance->setMaximum(10.000000000000000);
        meshTolerance->setSingleStep(0.010000000000000);
        meshTolerance->setValue(0.010000000000000);

        gridLayout->addWidget(meshTolerance, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        continuity = new QComboBox(groupBox_2);
        continuity->setObjectName("continuity");

        gridLayout->addWidget(continuity, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        maxDegree = new QComboBox(groupBox_2);
        maxDegree->setObjectName("maxDegree");

        gridLayout->addWidget(maxDegree, 2, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 0, 1, 2);

        startButton = new QPushButton(MeshPartGui__TaskCurveOnMesh);
        startButton->setObjectName("startButton");

        gridLayout_3->addWidget(startButton, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(211, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 3, 1, 1, 1);

        QWidget::setTabOrder(spinBox, splitAngle);
        QWidget::setTabOrder(splitAngle, meshTolerance);
        QWidget::setTabOrder(meshTolerance, continuity);
        QWidget::setTabOrder(continuity, maxDegree);
        QWidget::setTabOrder(maxDegree, startButton);

        retranslateUi(MeshPartGui__TaskCurveOnMesh);

        continuity->setCurrentIndex(-1);
        maxDegree->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MeshPartGui__TaskCurveOnMesh);
    } // setupUi

    void retranslateUi(QWidget *MeshPartGui__TaskCurveOnMesh)
    {
        MeshPartGui__TaskCurveOnMesh->setWindowTitle(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Curve on Mesh", nullptr));
        lb_instructions->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Press 'Start', then pick points on the mesh; when enough points have been set, right-click and choose 'Create'. Repeat this process to create more splines. Close this task panel to complete the operation.\n"
"\n"
"This command only works with a Mesh object, not a regular face or surface. To convert an object to a mesh use the tools of the Mesh workbench.", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Wire", nullptr));
        label_4->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Snap tolerance to vertices", nullptr));
        spinBox->setSuffix(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", " px", nullptr));
        label_5->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Split threshold", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Spline Approximation", nullptr));
        label->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Tolerance to mesh", nullptr));
        label_2->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Continuity", nullptr));
        label_3->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Maximum curve degree", nullptr));
        startButton->setText(QCoreApplication::translate("MeshPartGui::TaskCurveOnMesh", "Start", nullptr));
    } // retranslateUi

};

} // namespace MeshPartGui

namespace MeshPartGui {
namespace Ui {
    class TaskCurveOnMesh: public Ui_TaskCurveOnMesh {};
} // namespace Ui
} // namespace MeshPartGui

#endif // UI_TASKCURVEONMESH_H
