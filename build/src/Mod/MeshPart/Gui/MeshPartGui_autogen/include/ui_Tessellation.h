/********************************************************************************
** Form generated from reading UI file 'Tessellation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESSELLATION_H
#define UI_TESSELLATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace MeshPartGui {

class Ui_Tessellation
{
public:
    QGridLayout *gridLayout_7;
    QGroupBox *groupBoxMeshingOptions;
    QGridLayout *gridLayout_6;
    QTabWidget *stackedWidget;
    QWidget *pageStandard;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *labelSurfaceDeviation;
    Gui::QuantitySpinBox *spinSurfaceDeviation;
    QLabel *labelAngularDeviation;
    Gui::QuantitySpinBox *spinAngularDeviation;
    QCheckBox *relativeDeviation;
    QCheckBox *meshShapeColors;
    QCheckBox *groupsFaceColors;
    QSpacerItem *verticalSpacer;
    QWidget *pageMefisto;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkMaximumEdgeLength;
    Gui::QuantitySpinBox *spinMaximumEdgeLength;
    QPushButton *estimateMaximumEdgeLength;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageNetgen;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *labelFineness;
    QComboBox *comboFineness;
    QGridLayout *gridLayout_2;
    QLabel *labelGrading;
    QDoubleSpinBox *doubleGrading;
    QLabel *labelEdgeElements;
    QDoubleSpinBox *spinEdgeElements;
    QLabel *labelCurvatureElements;
    QDoubleSpinBox *spinCurvatureElements;
    QCheckBox *checkOptimizeSurface;
    QCheckBox *checkSecondOrder;
    QCheckBox *checkQuadDominated;
    QSpacerItem *verticalSpacer_3;
    QCheckBox *checkBoxDontQuit;

    void setupUi(QWidget *MeshPartGui__Tessellation)
    {
        if (MeshPartGui__Tessellation->objectName().isEmpty())
            MeshPartGui__Tessellation->setObjectName("MeshPartGui__Tessellation");
        MeshPartGui__Tessellation->resize(363, 508);
        gridLayout_7 = new QGridLayout(MeshPartGui__Tessellation);
        gridLayout_7->setObjectName("gridLayout_7");
        groupBoxMeshingOptions = new QGroupBox(MeshPartGui__Tessellation);
        groupBoxMeshingOptions->setObjectName("groupBoxMeshingOptions");
        gridLayout_6 = new QGridLayout(groupBoxMeshingOptions);
        gridLayout_6->setObjectName("gridLayout_6");
        stackedWidget = new QTabWidget(groupBoxMeshingOptions);
        stackedWidget->setObjectName("stackedWidget");
        pageStandard = new QWidget();
        pageStandard->setObjectName("pageStandard");
        gridLayout_3 = new QGridLayout(pageStandard);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelSurfaceDeviation = new QLabel(pageStandard);
        labelSurfaceDeviation->setObjectName("labelSurfaceDeviation");

        gridLayout->addWidget(labelSurfaceDeviation, 0, 0, 1, 1);

        spinSurfaceDeviation = new Gui::QuantitySpinBox(pageStandard);
        spinSurfaceDeviation->setObjectName("spinSurfaceDeviation");
        spinSurfaceDeviation->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinSurfaceDeviation->setMinimum(0.001000000000000);
        spinSurfaceDeviation->setSingleStep(0.100000000000000);
        spinSurfaceDeviation->setValue(0.100000000000000);

        gridLayout->addWidget(spinSurfaceDeviation, 0, 1, 1, 1);

        labelAngularDeviation = new QLabel(pageStandard);
        labelAngularDeviation->setObjectName("labelAngularDeviation");

        gridLayout->addWidget(labelAngularDeviation, 1, 0, 1, 1);

        spinAngularDeviation = new Gui::QuantitySpinBox(pageStandard);
        spinAngularDeviation->setObjectName("spinAngularDeviation");
        spinAngularDeviation->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        spinAngularDeviation->setMinimum(1.000000000000000);
        spinAngularDeviation->setMaximum(180.000000000000000);
        spinAngularDeviation->setSingleStep(5.000000000000000);
        spinAngularDeviation->setValue(30.000000000000000);

        gridLayout->addWidget(spinAngularDeviation, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        relativeDeviation = new QCheckBox(pageStandard);
        relativeDeviation->setObjectName("relativeDeviation");

        gridLayout_3->addWidget(relativeDeviation, 1, 0, 1, 1);

        meshShapeColors = new QCheckBox(pageStandard);
        meshShapeColors->setObjectName("meshShapeColors");

        gridLayout_3->addWidget(meshShapeColors, 2, 0, 1, 1);

        groupsFaceColors = new QCheckBox(pageStandard);
        groupsFaceColors->setObjectName("groupsFaceColors");

        gridLayout_3->addWidget(groupsFaceColors, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 189, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 4, 0, 1, 1);

        stackedWidget->addTab(pageStandard, QString());
        pageMefisto = new QWidget();
        pageMefisto->setObjectName("pageMefisto");
        gridLayout_9 = new QGridLayout(pageMefisto);
        gridLayout_9->setObjectName("gridLayout_9");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        checkMaximumEdgeLength = new QCheckBox(pageMefisto);
        checkMaximumEdgeLength->setObjectName("checkMaximumEdgeLength");
        checkMaximumEdgeLength->setChecked(true);

        horizontalLayout_2->addWidget(checkMaximumEdgeLength);

        spinMaximumEdgeLength = new Gui::QuantitySpinBox(pageMefisto);
        spinMaximumEdgeLength->setObjectName("spinMaximumEdgeLength");
        spinMaximumEdgeLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spinMaximumEdgeLength->setSingleStep(0.100000000000000);
        spinMaximumEdgeLength->setValue(1.000000000000000);

        horizontalLayout_2->addWidget(spinMaximumEdgeLength);

        estimateMaximumEdgeLength = new QPushButton(pageMefisto);
        estimateMaximumEdgeLength->setObjectName("estimateMaximumEdgeLength");

        horizontalLayout_2->addWidget(estimateMaximumEdgeLength);


        gridLayout_9->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 189, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer_2, 1, 0, 1, 1);

        stackedWidget->addTab(pageMefisto, QString());
        pageNetgen = new QWidget();
        pageNetgen->setObjectName("pageNetgen");
        gridLayout_5 = new QGridLayout(pageNetgen);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        labelFineness = new QLabel(pageNetgen);
        labelFineness->setObjectName("labelFineness");

        gridLayout_4->addWidget(labelFineness, 0, 0, 1, 1);

        comboFineness = new QComboBox(pageNetgen);
        comboFineness->addItem(QString());
        comboFineness->addItem(QString());
        comboFineness->addItem(QString());
        comboFineness->addItem(QString());
        comboFineness->addItem(QString());
        comboFineness->addItem(QString());
        comboFineness->setObjectName("comboFineness");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboFineness->sizePolicy().hasHeightForWidth());
        comboFineness->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(comboFineness, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        labelGrading = new QLabel(pageNetgen);
        labelGrading->setObjectName("labelGrading");

        gridLayout_2->addWidget(labelGrading, 0, 0, 1, 1);

        doubleGrading = new QDoubleSpinBox(pageNetgen);
        doubleGrading->setObjectName("doubleGrading");
        doubleGrading->setEnabled(false);
        doubleGrading->setDecimals(1);
        doubleGrading->setMinimum(0.100000000000000);
        doubleGrading->setMaximum(1.000000000000000);
        doubleGrading->setSingleStep(0.100000000000000);
        doubleGrading->setValue(0.300000000000000);

        gridLayout_2->addWidget(doubleGrading, 0, 1, 1, 1);

        labelEdgeElements = new QLabel(pageNetgen);
        labelEdgeElements->setObjectName("labelEdgeElements");

        gridLayout_2->addWidget(labelEdgeElements, 1, 0, 1, 1);

        spinEdgeElements = new QDoubleSpinBox(pageNetgen);
        spinEdgeElements->setObjectName("spinEdgeElements");
        spinEdgeElements->setEnabled(false);
        spinEdgeElements->setDecimals(1);
        spinEdgeElements->setMinimum(0.200000000000000);
        spinEdgeElements->setMaximum(10.000000000000000);
        spinEdgeElements->setSingleStep(0.100000000000000);
        spinEdgeElements->setValue(1.000000000000000);

        gridLayout_2->addWidget(spinEdgeElements, 1, 1, 1, 1);

        labelCurvatureElements = new QLabel(pageNetgen);
        labelCurvatureElements->setObjectName("labelCurvatureElements");

        gridLayout_2->addWidget(labelCurvatureElements, 2, 0, 1, 1);

        spinCurvatureElements = new QDoubleSpinBox(pageNetgen);
        spinCurvatureElements->setObjectName("spinCurvatureElements");
        spinCurvatureElements->setEnabled(false);
        spinCurvatureElements->setDecimals(1);
        spinCurvatureElements->setMinimum(0.200000000000000);
        spinCurvatureElements->setMaximum(10.000000000000000);
        spinCurvatureElements->setSingleStep(0.100000000000000);
        spinCurvatureElements->setValue(2.000000000000000);

        gridLayout_2->addWidget(spinCurvatureElements, 2, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 1, 1, 1, 1);

        checkOptimizeSurface = new QCheckBox(pageNetgen);
        checkOptimizeSurface->setObjectName("checkOptimizeSurface");
        checkOptimizeSurface->setChecked(true);

        gridLayout_4->addWidget(checkOptimizeSurface, 2, 0, 1, 2);

        checkSecondOrder = new QCheckBox(pageNetgen);
        checkSecondOrder->setObjectName("checkSecondOrder");

        gridLayout_4->addWidget(checkSecondOrder, 3, 0, 1, 2);

        checkQuadDominated = new QCheckBox(pageNetgen);
        checkQuadDominated->setObjectName("checkQuadDominated");

        gridLayout_4->addWidget(checkQuadDominated, 4, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 37, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 1, 0, 1, 1);

        stackedWidget->addTab(pageNetgen, QString());

        gridLayout_6->addWidget(stackedWidget, 0, 0, 1, 3);

        checkBoxDontQuit = new QCheckBox(groupBoxMeshingOptions);
        checkBoxDontQuit->setObjectName("checkBoxDontQuit");

        gridLayout_6->addWidget(checkBoxDontQuit, 1, 0, 1, 1);


        gridLayout_7->addWidget(groupBoxMeshingOptions, 0, 0, 1, 1);


        retranslateUi(MeshPartGui__Tessellation);
        QObject::connect(checkMaximumEdgeLength, SIGNAL(toggled(bool)), spinMaximumEdgeLength, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);
        comboFineness->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MeshPartGui__Tessellation);
    } // setupUi

    void retranslateUi(QWidget *MeshPartGui__Tessellation)
    {
        MeshPartGui__Tessellation->setWindowTitle(QCoreApplication::translate("MeshPartGui::Tessellation", "Tessellation", nullptr));
        groupBoxMeshingOptions->setTitle(QCoreApplication::translate("MeshPartGui::Tessellation", "Meshing Options", nullptr));
        labelSurfaceDeviation->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Surface deviation", nullptr));
#if QT_CONFIG(tooltip)
        spinSurfaceDeviation->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Maximal linear deflection of a mesh section from the surface of the object", nullptr));
#endif // QT_CONFIG(tooltip)
        labelAngularDeviation->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Angular deviation", nullptr));
#if QT_CONFIG(tooltip)
        spinAngularDeviation->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Maximal angular deflection of a mesh section to the next section", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        relativeDeviation->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "The maximal linear deviation of a mesh segment will be the specified\n"
"surface deviation multiplied by the length of the current mesh segment (edge)", nullptr));
#endif // QT_CONFIG(tooltip)
        relativeDeviation->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Relative surface deviation", nullptr));
#if QT_CONFIG(tooltip)
        meshShapeColors->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Mesh will get face colors of the object", nullptr));
#endif // QT_CONFIG(tooltip)
        meshShapeColors->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Apply face colors to mesh", nullptr));
#if QT_CONFIG(tooltip)
        groupsFaceColors->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Mesh segments will be grouped according to the color of the object faces.\n"
"These groups will be exported for mesh output formats supporting\n"
"this feature (e.g. the format OBJ).", nullptr));
#endif // QT_CONFIG(tooltip)
        groupsFaceColors->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Define segments by face colors", nullptr));
        stackedWidget->setTabText(stackedWidget->indexOf(pageStandard), QCoreApplication::translate("MeshPartGui::Tessellation", "Standard", nullptr));
#if QT_CONFIG(tooltip)
        stackedWidget->setTabToolTip(stackedWidget->indexOf(pageStandard), QCoreApplication::translate("MeshPartGui::Tessellation", "Use the standard mesher", nullptr));
#endif // QT_CONFIG(tooltip)
        checkMaximumEdgeLength->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Maximum edge length", nullptr));
#if QT_CONFIG(tooltip)
        checkMaximumEdgeLength->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "If this number is smaller the mesh becomes finer.\n"
"The smallest value is 0.", nullptr));
#endif // QT_CONFIG(tooltip)
        estimateMaximumEdgeLength->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Estimate", nullptr));
        stackedWidget->setTabText(stackedWidget->indexOf(pageMefisto), QCoreApplication::translate("MeshPartGui::Tessellation", "Mefisto", nullptr));
#if QT_CONFIG(tooltip)
        stackedWidget->setTabToolTip(stackedWidget->indexOf(pageMefisto), QCoreApplication::translate("MeshPartGui::Tessellation", "Use the Mefisto mesher", nullptr));
#endif // QT_CONFIG(tooltip)
        labelFineness->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Fineness", nullptr));
        comboFineness->setItemText(0, QCoreApplication::translate("MeshPartGui::Tessellation", "Very coarse", nullptr));
        comboFineness->setItemText(1, QCoreApplication::translate("MeshPartGui::Tessellation", "Coarse", nullptr));
        comboFineness->setItemText(2, QCoreApplication::translate("MeshPartGui::Tessellation", "Moderate", nullptr));
        comboFineness->setItemText(3, QCoreApplication::translate("MeshPartGui::Tessellation", "Fine", nullptr));
        comboFineness->setItemText(4, QCoreApplication::translate("MeshPartGui::Tessellation", "Very fine", nullptr));
        comboFineness->setItemText(5, QCoreApplication::translate("MeshPartGui::Tessellation", "User defined", nullptr));

        labelGrading->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Mesh size grading", nullptr));
#if QT_CONFIG(tooltip)
        doubleGrading->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "If this parameter is smaller, the mesh becomes finer.\n"
"A value in the range of 0.1-1.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelEdgeElements->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Elements per edge", nullptr));
#if QT_CONFIG(tooltip)
        spinEdgeElements->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "If this parameter is larger, the mesh becomes finer.\n"
"A value in the range of 0.2-10.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCurvatureElements->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Elements per curvature radius", nullptr));
#if QT_CONFIG(tooltip)
        spinCurvatureElements->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "If this parameter is larger, the mesh becomes finer.\n"
"A value in the range of 0.2-10.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkOptimizeSurface->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Whether optimization of surface shape will be done", nullptr));
#endif // QT_CONFIG(tooltip)
        checkOptimizeSurface->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Optimize surface", nullptr));
#if QT_CONFIG(tooltip)
        checkSecondOrder->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Whether second order elements will be generated", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSecondOrder->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Second order elements", nullptr));
#if QT_CONFIG(tooltip)
        checkQuadDominated->setToolTip(QCoreApplication::translate("MeshPartGui::Tessellation", "Whether meshes will be arranged preferably using quadrilateral faces", nullptr));
#endif // QT_CONFIG(tooltip)
        checkQuadDominated->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Quad dominated", nullptr));
        stackedWidget->setTabText(stackedWidget->indexOf(pageNetgen), QCoreApplication::translate("MeshPartGui::Tessellation", "Netgen", nullptr));
#if QT_CONFIG(tooltip)
        stackedWidget->setTabToolTip(stackedWidget->indexOf(pageNetgen), QCoreApplication::translate("MeshPartGui::Tessellation", "Use the Netgen mesher", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxDontQuit->setText(QCoreApplication::translate("MeshPartGui::Tessellation", "Leave panel open", nullptr));
    } // retranslateUi

};

} // namespace MeshPartGui

namespace MeshPartGui {
namespace Ui {
    class Tessellation: public Ui_Tessellation {};
} // namespace Ui
} // namespace MeshPartGui

#endif // UI_TESSELLATION_H
