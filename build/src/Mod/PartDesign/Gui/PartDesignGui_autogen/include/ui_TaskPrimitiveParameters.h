/********************************************************************************
** Form generated from reading UI file 'TaskPrimitiveParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPRIMITIVEPARAMETERS_H
#define UI_TASKPRIMITIVEPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_DlgPrimitives
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *widgetStack;
    QWidget *page0_plane;
    QGridLayout *gridLayout;
    QGridLayout *_2;
    QLabel *textLabel2_2;
    Gui::QuantitySpinBox *planeLength;
    QLabel *textLabel3_2;
    Gui::QuantitySpinBox *planeWidth;
    QSpacerItem *spacerItem;
    QWidget *Page1_box;
    QGridLayout *_3;
    QGridLayout *boxParametersLayout;
    QLabel *textLabel2;
    Gui::QuantitySpinBox *boxLength;
    QLabel *textLabel3;
    Gui::QuantitySpinBox *boxWidth;
    QLabel *textLabel4;
    Gui::QuantitySpinBox *boxHeight;
    QSpacerItem *spacerItem1;
    QWidget *Page2_cylinder;
    QGridLayout *_5;
    QGridLayout *_7;
    QLabel *textLabel5;
    Gui::QuantitySpinBox *cylinderRadius;
    QLabel *textLabel6;
    Gui::QuantitySpinBox *cylinderHeight;
    QLabel *labelCylinderXSkew;
    Gui::QuantitySpinBox *cylinderXSkew;
    QLabel *labelCylinderYSkew;
    Gui::QuantitySpinBox *cylinderYSkew;
    QFrame *line_2;
    QGridLayout *cylinderAngleLayout;
    QLabel *label;
    Gui::QuantitySpinBox *cylinderAngle;
    QSpacerItem *spacerItem2;
    QWidget *Page3_cone;
    QGridLayout *_8;
    QGridLayout *_10;
    QLabel *textLabel9;
    Gui::QuantitySpinBox *coneRadius1;
    QLabel *textLabel10;
    Gui::QuantitySpinBox *coneRadius2;
    QLabel *textLabel11;
    Gui::QuantitySpinBox *coneHeight;
    QFrame *line_3;
    QGridLayout *coneAngleLayout;
    QLabel *label_4;
    Gui::QuantitySpinBox *coneAngle;
    QSpacerItem *spacerItem3;
    QWidget *Page4_sphere;
    QGridLayout *_11;
    QHBoxLayout *_13;
    QLabel *textLabel14;
    Gui::QuantitySpinBox *sphereRadius;
    QFrame *line;
    QGridLayout *sphereAnglesLayout;
    QLabel *label_3;
    Gui::QuantitySpinBox *sphereAngle3;
    QLabel *label_2;
    Gui::QuantitySpinBox *sphereAngle1;
    QSpacerItem *spacerItem4;
    Gui::QuantitySpinBox *sphereAngle2;
    QSpacerItem *spacerItem5;
    QWidget *Page5_ellipsoid;
    QGridLayout *_14;
    QGridLayout *_15;
    QLabel *textLabel21;
    Gui::QuantitySpinBox *ellipsoidRadius1;
    QLabel *textLabel22;
    Gui::QuantitySpinBox *ellipsoidRadius2;
    QLabel *textLabel23;
    Gui::QuantitySpinBox *ellipsoidRadius3;
    QFrame *line_5;
    QGridLayout *ellipsoidAnglesLayout;
    QLabel *label23;
    Gui::QuantitySpinBox *ellipsoidAngle3;
    QLabel *label24;
    Gui::QuantitySpinBox *ellipsoidAngle1;
    QSpacerItem *spacerItem6;
    Gui::QuantitySpinBox *ellipsoidAngle2;
    QSpacerItem *spacerItem7;
    QWidget *Page6_torus;
    QGridLayout *_17;
    QGridLayout *_19;
    QLabel *textLabel19;
    Gui::QuantitySpinBox *torusRadius1;
    QLabel *textLabel20;
    Gui::QuantitySpinBox *torusRadius2;
    QFrame *line_4;
    QGridLayout *torusAnglesLayout;
    QLabel *label_5;
    Gui::QuantitySpinBox *torusAngle3;
    QLabel *label_6;
    Gui::QuantitySpinBox *torusAngle1;
    QSpacerItem *spacerItem8;
    Gui::QuantitySpinBox *torusAngle2;
    QSpacerItem *spacerItem9;
    QWidget *page_prism;
    QGridLayout *_20;
    QGridLayout *prismParametersLayout;
    QLabel *labelPrismPolygon;
    QSpinBox *prismPolygon;
    QLabel *labelPrismCircumradius;
    Gui::QuantitySpinBox *prismCircumradius;
    QLabel *labelPrismHeight;
    Gui::QuantitySpinBox *prismHeight;
    QLabel *labelPrismXSkew;
    Gui::QuantitySpinBox *prismXSkew;
    QLabel *labelPrismYSkew;
    Gui::QuantitySpinBox *prismYSkew;
    QSpacerItem *spacerItem10;
    QWidget *page7_wedge;
    QGridLayout *gridLayout_8;
    QGridLayout *wedgeParametersLayout;
    QLabel *label_10;
    Gui::QuantitySpinBox *wedgeXmin;
    Gui::QuantitySpinBox *wedgeXmax;
    QLabel *label_11;
    Gui::QuantitySpinBox *wedgeYmin;
    Gui::QuantitySpinBox *wedgeYmax;
    QLabel *label_12;
    Gui::QuantitySpinBox *wedgeZmin;
    Gui::QuantitySpinBox *wedgeZmax;
    QLabel *label_13;
    Gui::QuantitySpinBox *wedgeX2min;
    Gui::QuantitySpinBox *wedgeX2max;
    QLabel *label_14;
    Gui::QuantitySpinBox *wedgeZ2min;
    Gui::QuantitySpinBox *wedgeZ2max;
    QSpacerItem *verticalSpacer_2;
    QWidget *page8_helix;
    QGridLayout *_22;
    QGridLayout *_23;
    QLabel *label_7;
    Gui::QuantitySpinBox *helixPitch;
    QLabel *label_8;
    Gui::QuantitySpinBox *helixHeight;
    QLabel *label_9;
    Gui::QuantitySpinBox *helixRadius;
    QLabel *label_20;
    Gui::QuantitySpinBox *helixAngle;
    QLabel *label_15;
    QComboBox *helixLocalCS;
    QSpacerItem *spacerItem11;
    QWidget *page9_spiral;
    QGridLayout *_24;
    QGridLayout *_25;
    QLabel *label_spiral_growth;
    Gui::QuantitySpinBox *spiralGrowth;
    QLabel *label_spiral_rotation;
    QDoubleSpinBox *spiralRotation;
    QLabel *label_spiral_radius;
    Gui::QuantitySpinBox *spiralRadius;
    QSpacerItem *spacerItem12;
    QWidget *page10_circle;
    QGridLayout *gridLayout_3;
    QGridLayout *circleParameters;
    QLabel *Radius;
    Gui::QuantitySpinBox *circleRadius;
    QLabel *Angle1;
    Gui::QuantitySpinBox *circleAngle1;
    QLabel *Angle2;
    Gui::QuantitySpinBox *circleAngle2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonCircleFromThreePoints;
    QSpacerItem *verticalSpacer;
    QWidget *page;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_10;
    QLabel *labelEllMajorRadius;
    Gui::QuantitySpinBox *ellipseMajorRadius;
    QLabel *labelEllMinorRadius;
    Gui::QuantitySpinBox *ellipseMinorRadius;
    QLabel *labelEllAngle1;
    Gui::QuantitySpinBox *ellipseAngle1;
    QLabel *labelEllAngle2;
    Gui::QuantitySpinBox *ellipseAngle2;
    QSpacerItem *verticalSpacer_5;
    QWidget *page11_vertex;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_4;
    QLabel *label_X_Axis;
    Gui::QuantitySpinBox *vertexX;
    QLabel *label_Y_Axis;
    Gui::QuantitySpinBox *vertexY;
    QLabel *label_Z_Axis;
    Gui::QuantitySpinBox *vertexZ;
    QSpacerItem *verticalSpacer_3;
    QWidget *page12_edge;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *Start_Vertex;
    QLabel *X1;
    Gui::QuantitySpinBox *edgeX1;
    QLabel *Y1;
    Gui::QuantitySpinBox *edgeY1;
    QLabel *Z1;
    Gui::QuantitySpinBox *edgeZ1;
    QFrame *line_6;
    QLabel *Finish_Vertex;
    QLabel *X2;
    Gui::QuantitySpinBox *edgeX2;
    QLabel *Y2;
    Gui::QuantitySpinBox *edgeY2;
    QLabel *Z2;
    Gui::QuantitySpinBox *edgeZ2;
    QSpacerItem *verticalSpacer_4;
    QWidget *page_regularPolygon;
    QGridLayout *_26;
    QGridLayout *_27;
    QLabel *labelRegularPolygonPolygon;
    QSpinBox *regularPolygonPolygon;
    QLabel *labelRegularPolygonCircumradius;
    Gui::QuantitySpinBox *regularPolygonCircumradius;
    QSpacerItem *spacerItem13;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;

    void setupUi(QWidget *PartDesignGui__DlgPrimitives)
    {
        if (PartDesignGui__DlgPrimitives->objectName().isEmpty())
            PartDesignGui__DlgPrimitives->setObjectName("PartDesignGui__DlgPrimitives");
        PartDesignGui__DlgPrimitives->resize(326, 241);
        PartDesignGui__DlgPrimitives->setProperty("sizeGripEnabled", QVariant(true));
        verticalLayout = new QVBoxLayout(PartDesignGui__DlgPrimitives);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        widgetStack = new QStackedWidget(PartDesignGui__DlgPrimitives);
        widgetStack->setObjectName("widgetStack");
        page0_plane = new QWidget();
        page0_plane->setObjectName("page0_plane");
        gridLayout = new QGridLayout(page0_plane);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        _2 = new QGridLayout();
        _2->setSpacing(6);
        _2->setObjectName("_2");
        _2->setContentsMargins(0, 0, 0, 0);
        textLabel2_2 = new QLabel(page0_plane);
        textLabel2_2->setObjectName("textLabel2_2");

        _2->addWidget(textLabel2_2, 0, 0, 1, 1);

        planeLength = new Gui::QuantitySpinBox(page0_plane);
        planeLength->setObjectName("planeLength");
        planeLength->setKeyboardTracking(false);
        planeLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        planeLength->setValue(10.000000000000000);

        _2->addWidget(planeLength, 0, 2, 1, 1);

        textLabel3_2 = new QLabel(page0_plane);
        textLabel3_2->setObjectName("textLabel3_2");

        _2->addWidget(textLabel3_2, 1, 0, 1, 1);

        planeWidth = new Gui::QuantitySpinBox(page0_plane);
        planeWidth->setObjectName("planeWidth");
        planeWidth->setKeyboardTracking(false);
        planeWidth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        planeWidth->setValue(10.000000000000000);

        _2->addWidget(planeWidth, 1, 2, 1, 1);


        gridLayout->addLayout(_2, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem, 1, 0, 1, 1);

        widgetStack->addWidget(page0_plane);
        Page1_box = new QWidget();
        Page1_box->setObjectName("Page1_box");
        _3 = new QGridLayout(Page1_box);
        _3->setSpacing(6);
        _3->setContentsMargins(11, 11, 11, 11);
        _3->setObjectName("_3");
        _3->setContentsMargins(0, 0, 0, 0);
        boxParametersLayout = new QGridLayout();
        boxParametersLayout->setSpacing(6);
        boxParametersLayout->setObjectName("boxParametersLayout");
        boxParametersLayout->setContentsMargins(0, 0, 0, 0);
        textLabel2 = new QLabel(Page1_box);
        textLabel2->setObjectName("textLabel2");

        boxParametersLayout->addWidget(textLabel2, 0, 0, 1, 1);

        boxLength = new Gui::QuantitySpinBox(Page1_box);
        boxLength->setObjectName("boxLength");
        boxLength->setKeyboardTracking(false);
        boxLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxLength->setValue(10.000000000000000);

        boxParametersLayout->addWidget(boxLength, 0, 2, 1, 1);

        textLabel3 = new QLabel(Page1_box);
        textLabel3->setObjectName("textLabel3");

        boxParametersLayout->addWidget(textLabel3, 1, 0, 1, 1);

        boxWidth = new Gui::QuantitySpinBox(Page1_box);
        boxWidth->setObjectName("boxWidth");
        boxWidth->setKeyboardTracking(false);
        boxWidth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxWidth->setValue(10.000000000000000);

        boxParametersLayout->addWidget(boxWidth, 1, 2, 1, 1);

        textLabel4 = new QLabel(Page1_box);
        textLabel4->setObjectName("textLabel4");

        boxParametersLayout->addWidget(textLabel4, 2, 0, 1, 1);

        boxHeight = new Gui::QuantitySpinBox(Page1_box);
        boxHeight->setObjectName("boxHeight");
        boxHeight->setKeyboardTracking(false);
        boxHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxHeight->setValue(10.000000000000000);

        boxParametersLayout->addWidget(boxHeight, 2, 2, 1, 1);


        _3->addLayout(boxParametersLayout, 0, 0, 1, 1);

        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _3->addItem(spacerItem1, 1, 0, 1, 1);

        widgetStack->addWidget(Page1_box);
        Page2_cylinder = new QWidget();
        Page2_cylinder->setObjectName("Page2_cylinder");
        _5 = new QGridLayout(Page2_cylinder);
        _5->setSpacing(6);
        _5->setContentsMargins(11, 11, 11, 11);
        _5->setObjectName("_5");
        _5->setContentsMargins(0, 0, 0, 0);
        _7 = new QGridLayout();
        _7->setSpacing(6);
        _7->setObjectName("_7");
        _7->setContentsMargins(0, 0, 0, 0);
        textLabel5 = new QLabel(Page2_cylinder);
        textLabel5->setObjectName("textLabel5");

        _7->addWidget(textLabel5, 0, 0, 1, 1);

        cylinderRadius = new Gui::QuantitySpinBox(Page2_cylinder);
        cylinderRadius->setObjectName("cylinderRadius");
        cylinderRadius->setKeyboardTracking(false);
        cylinderRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        cylinderRadius->setValue(2.000000000000000);

        _7->addWidget(cylinderRadius, 0, 1, 1, 1);

        textLabel6 = new QLabel(Page2_cylinder);
        textLabel6->setObjectName("textLabel6");

        _7->addWidget(textLabel6, 1, 0, 1, 1);

        cylinderHeight = new Gui::QuantitySpinBox(Page2_cylinder);
        cylinderHeight->setObjectName("cylinderHeight");
        cylinderHeight->setKeyboardTracking(false);
        cylinderHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        cylinderHeight->setValue(10.000000000000000);

        _7->addWidget(cylinderHeight, 1, 1, 1, 1);

        labelCylinderXSkew = new QLabel(Page2_cylinder);
        labelCylinderXSkew->setObjectName("labelCylinderXSkew");

        _7->addWidget(labelCylinderXSkew, 2, 0, 1, 1);

        cylinderXSkew = new Gui::QuantitySpinBox(Page2_cylinder);
        cylinderXSkew->setObjectName("cylinderXSkew");
        cylinderXSkew->setKeyboardTracking(false);
        cylinderXSkew->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        cylinderXSkew->setMinimum(-90.000000000000000);
        cylinderXSkew->setMaximum(90.000000000000000);

        _7->addWidget(cylinderXSkew, 2, 1, 1, 1);

        labelCylinderYSkew = new QLabel(Page2_cylinder);
        labelCylinderYSkew->setObjectName("labelCylinderYSkew");

        _7->addWidget(labelCylinderYSkew, 3, 0, 1, 1);

        cylinderYSkew = new Gui::QuantitySpinBox(Page2_cylinder);
        cylinderYSkew->setObjectName("cylinderYSkew");
        cylinderYSkew->setKeyboardTracking(false);
        cylinderYSkew->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        cylinderYSkew->setMinimum(-90.000000000000000);
        cylinderYSkew->setMaximum(90.000000000000000);

        _7->addWidget(cylinderYSkew, 3, 1, 1, 1);


        _5->addLayout(_7, 0, 0, 1, 1);

        line_2 = new QFrame(Page2_cylinder);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        _5->addWidget(line_2, 1, 0, 1, 1);

        cylinderAngleLayout = new QGridLayout();
        cylinderAngleLayout->setSpacing(6);
        cylinderAngleLayout->setObjectName("cylinderAngleLayout");
        cylinderAngleLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(Page2_cylinder);
        label->setObjectName("label");
        label->setMinimumSize(QSize(123, 0));

        cylinderAngleLayout->addWidget(label, 0, 0, 1, 1);

        cylinderAngle = new Gui::QuantitySpinBox(Page2_cylinder);
        cylinderAngle->setObjectName("cylinderAngle");
        cylinderAngle->setKeyboardTracking(false);
        cylinderAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        cylinderAngle->setValue(360.000000000000000);

        cylinderAngleLayout->addWidget(cylinderAngle, 0, 1, 1, 1);


        _5->addLayout(cylinderAngleLayout, 2, 0, 1, 1);

        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _5->addItem(spacerItem2, 3, 0, 1, 1);

        widgetStack->addWidget(Page2_cylinder);
        Page3_cone = new QWidget();
        Page3_cone->setObjectName("Page3_cone");
        _8 = new QGridLayout(Page3_cone);
        _8->setSpacing(6);
        _8->setContentsMargins(11, 11, 11, 11);
        _8->setObjectName("_8");
        _8->setContentsMargins(0, 0, 0, 0);
        _10 = new QGridLayout();
        _10->setSpacing(6);
        _10->setObjectName("_10");
        _10->setContentsMargins(0, 0, 0, 0);
        textLabel9 = new QLabel(Page3_cone);
        textLabel9->setObjectName("textLabel9");

        _10->addWidget(textLabel9, 0, 0, 1, 1);

        coneRadius1 = new Gui::QuantitySpinBox(Page3_cone);
        coneRadius1->setObjectName("coneRadius1");
        coneRadius1->setKeyboardTracking(false);
        coneRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneRadius1->setValue(2.000000000000000);

        _10->addWidget(coneRadius1, 0, 2, 1, 1);

        textLabel10 = new QLabel(Page3_cone);
        textLabel10->setObjectName("textLabel10");

        _10->addWidget(textLabel10, 1, 0, 1, 1);

        coneRadius2 = new Gui::QuantitySpinBox(Page3_cone);
        coneRadius2->setObjectName("coneRadius2");
        coneRadius2->setKeyboardTracking(false);
        coneRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneRadius2->setValue(4.000000000000000);

        _10->addWidget(coneRadius2, 1, 2, 1, 1);

        textLabel11 = new QLabel(Page3_cone);
        textLabel11->setObjectName("textLabel11");

        _10->addWidget(textLabel11, 2, 0, 2, 1);

        coneHeight = new Gui::QuantitySpinBox(Page3_cone);
        coneHeight->setObjectName("coneHeight");
        coneHeight->setKeyboardTracking(false);
        coneHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneHeight->setValue(10.000000000000000);

        _10->addWidget(coneHeight, 3, 2, 1, 1);


        _8->addLayout(_10, 0, 0, 1, 1);

        line_3 = new QFrame(Page3_cone);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        _8->addWidget(line_3, 1, 0, 1, 1);

        coneAngleLayout = new QGridLayout();
        coneAngleLayout->setSpacing(6);
        coneAngleLayout->setObjectName("coneAngleLayout");
        coneAngleLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(Page3_cone);
        label_4->setObjectName("label_4");

        coneAngleLayout->addWidget(label_4, 0, 0, 1, 1);

        coneAngle = new Gui::QuantitySpinBox(Page3_cone);
        coneAngle->setObjectName("coneAngle");
        coneAngle->setKeyboardTracking(false);
        coneAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        coneAngle->setValue(360.000000000000000);

        coneAngleLayout->addWidget(coneAngle, 0, 1, 1, 1);


        _8->addLayout(coneAngleLayout, 2, 0, 1, 1);

        spacerItem3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _8->addItem(spacerItem3, 3, 0, 1, 1);

        widgetStack->addWidget(Page3_cone);
        Page4_sphere = new QWidget();
        Page4_sphere->setObjectName("Page4_sphere");
        _11 = new QGridLayout(Page4_sphere);
        _11->setSpacing(6);
        _11->setContentsMargins(11, 11, 11, 11);
        _11->setObjectName("_11");
        _11->setContentsMargins(0, 0, 0, 0);
        _13 = new QHBoxLayout();
        _13->setSpacing(6);
        _13->setObjectName("_13");
        _13->setContentsMargins(0, 0, 0, 0);
        textLabel14 = new QLabel(Page4_sphere);
        textLabel14->setObjectName("textLabel14");

        _13->addWidget(textLabel14);

        sphereRadius = new Gui::QuantitySpinBox(Page4_sphere);
        sphereRadius->setObjectName("sphereRadius");
        sphereRadius->setKeyboardTracking(false);
        sphereRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        sphereRadius->setValue(5.000000000000000);

        _13->addWidget(sphereRadius);


        _11->addLayout(_13, 0, 0, 1, 1);

        line = new QFrame(Page4_sphere);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        _11->addWidget(line, 1, 0, 1, 1);

        sphereAnglesLayout = new QGridLayout();
        sphereAnglesLayout->setSpacing(6);
        sphereAnglesLayout->setObjectName("sphereAnglesLayout");
        sphereAnglesLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(Page4_sphere);
        label_3->setObjectName("label_3");

        sphereAnglesLayout->addWidget(label_3, 0, 0, 1, 1);

        sphereAngle3 = new Gui::QuantitySpinBox(Page4_sphere);
        sphereAngle3->setObjectName("sphereAngle3");
        sphereAngle3->setKeyboardTracking(false);
        sphereAngle3->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        sphereAngle3->setValue(360.000000000000000);

        sphereAnglesLayout->addWidget(sphereAngle3, 0, 2, 1, 1);

        label_2 = new QLabel(Page4_sphere);
        label_2->setObjectName("label_2");

        sphereAnglesLayout->addWidget(label_2, 1, 0, 1, 1);

        sphereAngle1 = new Gui::QuantitySpinBox(Page4_sphere);
        sphereAngle1->setObjectName("sphereAngle1");
        sphereAngle1->setKeyboardTracking(false);
        sphereAngle1->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        sphereAngle1->setValue(-90.000000000000000);

        sphereAnglesLayout->addWidget(sphereAngle1, 1, 2, 1, 1);

        spacerItem4 = new QSpacerItem(81, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        sphereAnglesLayout->addItem(spacerItem4, 2, 0, 1, 1);

        sphereAngle2 = new Gui::QuantitySpinBox(Page4_sphere);
        sphereAngle2->setObjectName("sphereAngle2");
        sphereAngle2->setKeyboardTracking(false);
        sphereAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        sphereAngle2->setValue(90.000000000000000);

        sphereAnglesLayout->addWidget(sphereAngle2, 2, 2, 1, 1);


        _11->addLayout(sphereAnglesLayout, 2, 0, 1, 1);

        spacerItem5 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _11->addItem(spacerItem5, 3, 0, 1, 1);

        widgetStack->addWidget(Page4_sphere);
        Page5_ellipsoid = new QWidget();
        Page5_ellipsoid->setObjectName("Page5_ellipsoid");
        _14 = new QGridLayout(Page5_ellipsoid);
        _14->setSpacing(6);
        _14->setContentsMargins(11, 11, 11, 11);
        _14->setObjectName("_14");
        _14->setContentsMargins(9, 9, 9, 9);
        _15 = new QGridLayout();
        _15->setSpacing(6);
        _15->setObjectName("_15");
        _15->setContentsMargins(0, 0, 0, 0);
        textLabel21 = new QLabel(Page5_ellipsoid);
        textLabel21->setObjectName("textLabel21");

        _15->addWidget(textLabel21, 0, 0, 1, 1);

        ellipsoidRadius1 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidRadius1->setObjectName("ellipsoidRadius1");
        ellipsoidRadius1->setKeyboardTracking(false);
        ellipsoidRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipsoidRadius1->setValue(2.000000000000000);

        _15->addWidget(ellipsoidRadius1, 0, 1, 1, 1);

        textLabel22 = new QLabel(Page5_ellipsoid);
        textLabel22->setObjectName("textLabel22");

        _15->addWidget(textLabel22, 1, 0, 1, 1);

        ellipsoidRadius2 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidRadius2->setObjectName("ellipsoidRadius2");
        ellipsoidRadius2->setKeyboardTracking(false);
        ellipsoidRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipsoidRadius2->setValue(4.000000000000000);

        _15->addWidget(ellipsoidRadius2, 1, 1, 1, 1);

        textLabel23 = new QLabel(Page5_ellipsoid);
        textLabel23->setObjectName("textLabel23");

        _15->addWidget(textLabel23, 2, 0, 1, 1);

        ellipsoidRadius3 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidRadius3->setObjectName("ellipsoidRadius3");
        ellipsoidRadius3->setKeyboardTracking(false);
        ellipsoidRadius3->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipsoidRadius3->setValue(4.000000000000000);

        _15->addWidget(ellipsoidRadius3, 2, 1, 1, 1);


        _14->addLayout(_15, 0, 0, 1, 1);

        line_5 = new QFrame(Page5_ellipsoid);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        _14->addWidget(line_5, 1, 0, 1, 1);

        ellipsoidAnglesLayout = new QGridLayout();
        ellipsoidAnglesLayout->setSpacing(6);
        ellipsoidAnglesLayout->setObjectName("ellipsoidAnglesLayout");
        ellipsoidAnglesLayout->setContentsMargins(0, 0, 0, 0);
        label23 = new QLabel(Page5_ellipsoid);
        label23->setObjectName("label23");

        ellipsoidAnglesLayout->addWidget(label23, 0, 0, 1, 1);

        ellipsoidAngle3 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidAngle3->setObjectName("ellipsoidAngle3");
        ellipsoidAngle3->setKeyboardTracking(false);
        ellipsoidAngle3->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        ellipsoidAngle3->setValue(360.000000000000000);

        ellipsoidAnglesLayout->addWidget(ellipsoidAngle3, 0, 1, 1, 1);

        label24 = new QLabel(Page5_ellipsoid);
        label24->setObjectName("label24");

        ellipsoidAnglesLayout->addWidget(label24, 1, 0, 1, 1);

        ellipsoidAngle1 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidAngle1->setObjectName("ellipsoidAngle1");
        ellipsoidAngle1->setKeyboardTracking(false);
        ellipsoidAngle1->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        ellipsoidAngle1->setValue(-90.000000000000000);

        ellipsoidAnglesLayout->addWidget(ellipsoidAngle1, 1, 1, 1, 1);

        spacerItem6 = new QSpacerItem(81, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        ellipsoidAnglesLayout->addItem(spacerItem6, 2, 0, 1, 1);

        ellipsoidAngle2 = new Gui::QuantitySpinBox(Page5_ellipsoid);
        ellipsoidAngle2->setObjectName("ellipsoidAngle2");
        ellipsoidAngle2->setKeyboardTracking(false);
        ellipsoidAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        ellipsoidAngle2->setValue(90.000000000000000);

        ellipsoidAnglesLayout->addWidget(ellipsoidAngle2, 2, 1, 1, 1);


        _14->addLayout(ellipsoidAnglesLayout, 2, 0, 1, 1);

        spacerItem7 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _14->addItem(spacerItem7, 3, 0, 1, 1);

        widgetStack->addWidget(Page5_ellipsoid);
        Page6_torus = new QWidget();
        Page6_torus->setObjectName("Page6_torus");
        _17 = new QGridLayout(Page6_torus);
        _17->setSpacing(6);
        _17->setContentsMargins(11, 11, 11, 11);
        _17->setObjectName("_17");
        _17->setContentsMargins(9, 9, 9, 9);
        _19 = new QGridLayout();
        _19->setSpacing(6);
        _19->setObjectName("_19");
        _19->setContentsMargins(0, 0, 0, 0);
        textLabel19 = new QLabel(Page6_torus);
        textLabel19->setObjectName("textLabel19");

        _19->addWidget(textLabel19, 0, 0, 1, 1);

        torusRadius1 = new Gui::QuantitySpinBox(Page6_torus);
        torusRadius1->setObjectName("torusRadius1");
        torusRadius1->setKeyboardTracking(false);
        torusRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        torusRadius1->setValue(10.000000000000000);

        _19->addWidget(torusRadius1, 0, 2, 1, 1);

        textLabel20 = new QLabel(Page6_torus);
        textLabel20->setObjectName("textLabel20");

        _19->addWidget(textLabel20, 1, 0, 1, 1);

        torusRadius2 = new Gui::QuantitySpinBox(Page6_torus);
        torusRadius2->setObjectName("torusRadius2");
        torusRadius2->setKeyboardTracking(false);
        torusRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        torusRadius2->setValue(2.000000000000000);

        _19->addWidget(torusRadius2, 1, 2, 1, 1);


        _17->addLayout(_19, 0, 0, 1, 1);

        line_4 = new QFrame(Page6_torus);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        _17->addWidget(line_4, 1, 0, 1, 1);

        torusAnglesLayout = new QGridLayout();
        torusAnglesLayout->setSpacing(6);
        torusAnglesLayout->setObjectName("torusAnglesLayout");
        torusAnglesLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(Page6_torus);
        label_5->setObjectName("label_5");

        torusAnglesLayout->addWidget(label_5, 0, 0, 1, 1);

        torusAngle3 = new Gui::QuantitySpinBox(Page6_torus);
        torusAngle3->setObjectName("torusAngle3");
        torusAngle3->setKeyboardTracking(false);
        torusAngle3->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        torusAngle3->setValue(360.000000000000000);

        torusAnglesLayout->addWidget(torusAngle3, 0, 1, 1, 1);

        label_6 = new QLabel(Page6_torus);
        label_6->setObjectName("label_6");

        torusAnglesLayout->addWidget(label_6, 1, 0, 1, 1);

        torusAngle1 = new Gui::QuantitySpinBox(Page6_torus);
        torusAngle1->setObjectName("torusAngle1");
        torusAngle1->setKeyboardTracking(false);
        torusAngle1->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        torusAngle1->setValue(-180.000000000000000);

        torusAnglesLayout->addWidget(torusAngle1, 1, 1, 1, 1);

        spacerItem8 = new QSpacerItem(81, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        torusAnglesLayout->addItem(spacerItem8, 2, 0, 1, 1);

        torusAngle2 = new Gui::QuantitySpinBox(Page6_torus);
        torusAngle2->setObjectName("torusAngle2");
        torusAngle2->setKeyboardTracking(false);
        torusAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        torusAngle2->setValue(180.000000000000000);

        torusAnglesLayout->addWidget(torusAngle2, 2, 1, 1, 1);


        _17->addLayout(torusAnglesLayout, 2, 0, 1, 1);

        spacerItem9 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _17->addItem(spacerItem9, 3, 0, 1, 1);

        widgetStack->addWidget(Page6_torus);
        page_prism = new QWidget();
        page_prism->setObjectName("page_prism");
        _20 = new QGridLayout(page_prism);
        _20->setSpacing(6);
        _20->setContentsMargins(11, 11, 11, 11);
        _20->setObjectName("_20");
        _20->setContentsMargins(9, 9, 9, 9);
        prismParametersLayout = new QGridLayout();
        prismParametersLayout->setSpacing(6);
        prismParametersLayout->setObjectName("prismParametersLayout");
        prismParametersLayout->setContentsMargins(0, 0, 0, 0);
        labelPrismPolygon = new QLabel(page_prism);
        labelPrismPolygon->setObjectName("labelPrismPolygon");

        prismParametersLayout->addWidget(labelPrismPolygon, 0, 0, 1, 1);

        prismPolygon = new QSpinBox(page_prism);
        prismPolygon->setObjectName("prismPolygon");
        prismPolygon->setMinimum(3);
        prismPolygon->setMaximum(1000);
        prismPolygon->setValue(6);

        prismParametersLayout->addWidget(prismPolygon, 0, 2, 1, 1);

        labelPrismCircumradius = new QLabel(page_prism);
        labelPrismCircumradius->setObjectName("labelPrismCircumradius");

        prismParametersLayout->addWidget(labelPrismCircumradius, 1, 0, 1, 1);

        prismCircumradius = new Gui::QuantitySpinBox(page_prism);
        prismCircumradius->setObjectName("prismCircumradius");
        prismCircumradius->setKeyboardTracking(false);
        prismCircumradius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        prismCircumradius->setValue(2.000000000000000);

        prismParametersLayout->addWidget(prismCircumradius, 1, 2, 1, 1);

        labelPrismHeight = new QLabel(page_prism);
        labelPrismHeight->setObjectName("labelPrismHeight");

        prismParametersLayout->addWidget(labelPrismHeight, 2, 0, 1, 1);

        prismHeight = new Gui::QuantitySpinBox(page_prism);
        prismHeight->setObjectName("prismHeight");
        prismHeight->setKeyboardTracking(false);
        prismHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        prismHeight->setValue(10.000000000000000);

        prismParametersLayout->addWidget(prismHeight, 2, 2, 1, 1);

        labelPrismXSkew = new QLabel(page_prism);
        labelPrismXSkew->setObjectName("labelPrismXSkew");

        prismParametersLayout->addWidget(labelPrismXSkew, 3, 0, 1, 1);

        prismXSkew = new Gui::QuantitySpinBox(page_prism);
        prismXSkew->setObjectName("prismXSkew");
        prismXSkew->setKeyboardTracking(false);
        prismXSkew->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        prismXSkew->setMinimum(-90.000000000000000);
        prismXSkew->setMaximum(90.000000000000000);

        prismParametersLayout->addWidget(prismXSkew, 3, 2, 1, 1);

        labelPrismYSkew = new QLabel(page_prism);
        labelPrismYSkew->setObjectName("labelPrismYSkew");

        prismParametersLayout->addWidget(labelPrismYSkew, 4, 0, 1, 1);

        prismYSkew = new Gui::QuantitySpinBox(page_prism);
        prismYSkew->setObjectName("prismYSkew");
        prismYSkew->setKeyboardTracking(false);
        prismYSkew->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        prismYSkew->setMinimum(-90.000000000000000);
        prismYSkew->setMaximum(90.000000000000000);

        prismParametersLayout->addWidget(prismYSkew, 4, 2, 1, 1);


        _20->addLayout(prismParametersLayout, 0, 0, 1, 1);

        spacerItem10 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _20->addItem(spacerItem10, 1, 0, 1, 1);

        widgetStack->addWidget(page_prism);
        page7_wedge = new QWidget();
        page7_wedge->setObjectName("page7_wedge");
        gridLayout_8 = new QGridLayout(page7_wedge);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName("gridLayout_8");
        wedgeParametersLayout = new QGridLayout();
        wedgeParametersLayout->setSpacing(6);
        wedgeParametersLayout->setObjectName("wedgeParametersLayout");
        wedgeParametersLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        wedgeParametersLayout->setHorizontalSpacing(4);
        label_10 = new QLabel(page7_wedge);
        label_10->setObjectName("label_10");

        wedgeParametersLayout->addWidget(label_10, 0, 0, 1, 1);

        wedgeXmin = new Gui::QuantitySpinBox(page7_wedge);
        wedgeXmin->setObjectName("wedgeXmin");
        wedgeXmin->setKeyboardTracking(false);
        wedgeXmin->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        wedgeParametersLayout->addWidget(wedgeXmin, 0, 1, 1, 1);

        wedgeXmax = new Gui::QuantitySpinBox(page7_wedge);
        wedgeXmax->setObjectName("wedgeXmax");
        wedgeXmax->setKeyboardTracking(false);
        wedgeXmax->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeXmax->setValue(10.000000000000000);

        wedgeParametersLayout->addWidget(wedgeXmax, 0, 2, 1, 1);

        label_11 = new QLabel(page7_wedge);
        label_11->setObjectName("label_11");

        wedgeParametersLayout->addWidget(label_11, 1, 0, 1, 1);

        wedgeYmin = new Gui::QuantitySpinBox(page7_wedge);
        wedgeYmin->setObjectName("wedgeYmin");
        wedgeYmin->setKeyboardTracking(false);
        wedgeYmin->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        wedgeParametersLayout->addWidget(wedgeYmin, 1, 1, 1, 1);

        wedgeYmax = new Gui::QuantitySpinBox(page7_wedge);
        wedgeYmax->setObjectName("wedgeYmax");
        wedgeYmax->setKeyboardTracking(false);
        wedgeYmax->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeYmax->setValue(10.000000000000000);

        wedgeParametersLayout->addWidget(wedgeYmax, 1, 2, 1, 1);

        label_12 = new QLabel(page7_wedge);
        label_12->setObjectName("label_12");

        wedgeParametersLayout->addWidget(label_12, 2, 0, 1, 1);

        wedgeZmin = new Gui::QuantitySpinBox(page7_wedge);
        wedgeZmin->setObjectName("wedgeZmin");
        wedgeZmin->setKeyboardTracking(false);
        wedgeZmin->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        wedgeParametersLayout->addWidget(wedgeZmin, 2, 1, 1, 1);

        wedgeZmax = new Gui::QuantitySpinBox(page7_wedge);
        wedgeZmax->setObjectName("wedgeZmax");
        wedgeZmax->setKeyboardTracking(false);
        wedgeZmax->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeZmax->setValue(10.000000000000000);

        wedgeParametersLayout->addWidget(wedgeZmax, 2, 2, 1, 1);

        label_13 = new QLabel(page7_wedge);
        label_13->setObjectName("label_13");

        wedgeParametersLayout->addWidget(label_13, 3, 0, 1, 1);

        wedgeX2min = new Gui::QuantitySpinBox(page7_wedge);
        wedgeX2min->setObjectName("wedgeX2min");
        wedgeX2min->setKeyboardTracking(false);
        wedgeX2min->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeX2min->setValue(2.000000000000000);

        wedgeParametersLayout->addWidget(wedgeX2min, 3, 1, 1, 1);

        wedgeX2max = new Gui::QuantitySpinBox(page7_wedge);
        wedgeX2max->setObjectName("wedgeX2max");
        wedgeX2max->setKeyboardTracking(false);
        wedgeX2max->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeX2max->setValue(8.000000000000000);

        wedgeParametersLayout->addWidget(wedgeX2max, 3, 2, 1, 1);

        label_14 = new QLabel(page7_wedge);
        label_14->setObjectName("label_14");

        wedgeParametersLayout->addWidget(label_14, 4, 0, 1, 1);

        wedgeZ2min = new Gui::QuantitySpinBox(page7_wedge);
        wedgeZ2min->setObjectName("wedgeZ2min");
        wedgeZ2min->setKeyboardTracking(false);
        wedgeZ2min->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeZ2min->setValue(2.000000000000000);

        wedgeParametersLayout->addWidget(wedgeZ2min, 4, 1, 1, 1);

        wedgeZ2max = new Gui::QuantitySpinBox(page7_wedge);
        wedgeZ2max->setObjectName("wedgeZ2max");
        wedgeZ2max->setKeyboardTracking(false);
        wedgeZ2max->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        wedgeZ2max->setValue(8.000000000000000);

        wedgeParametersLayout->addWidget(wedgeZ2max, 4, 2, 1, 1);


        gridLayout_8->addLayout(wedgeParametersLayout, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_8->addItem(verticalSpacer_2, 1, 0, 1, 1);

        widgetStack->addWidget(page7_wedge);
        page8_helix = new QWidget();
        page8_helix->setObjectName("page8_helix");
        _22 = new QGridLayout(page8_helix);
        _22->setSpacing(6);
        _22->setContentsMargins(11, 11, 11, 11);
        _22->setObjectName("_22");
        _22->setContentsMargins(9, 9, 9, 9);
        _23 = new QGridLayout();
        _23->setSpacing(6);
        _23->setObjectName("_23");
        _23->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(page8_helix);
        label_7->setObjectName("label_7");

        _23->addWidget(label_7, 0, 0, 1, 1);

        helixPitch = new Gui::QuantitySpinBox(page8_helix);
        helixPitch->setObjectName("helixPitch");
        helixPitch->setKeyboardTracking(false);
        helixPitch->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        helixPitch->setValue(1.000000000000000);

        _23->addWidget(helixPitch, 0, 1, 1, 1);

        label_8 = new QLabel(page8_helix);
        label_8->setObjectName("label_8");

        _23->addWidget(label_8, 1, 0, 1, 1);

        helixHeight = new Gui::QuantitySpinBox(page8_helix);
        helixHeight->setObjectName("helixHeight");
        helixHeight->setKeyboardTracking(false);
        helixHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        helixHeight->setValue(2.000000000000000);

        _23->addWidget(helixHeight, 1, 1, 1, 1);

        label_9 = new QLabel(page8_helix);
        label_9->setObjectName("label_9");

        _23->addWidget(label_9, 2, 0, 1, 1);

        helixRadius = new Gui::QuantitySpinBox(page8_helix);
        helixRadius->setObjectName("helixRadius");
        helixRadius->setKeyboardTracking(false);
        helixRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        helixRadius->setValue(1.000000000000000);

        _23->addWidget(helixRadius, 2, 1, 1, 1);

        label_20 = new QLabel(page8_helix);
        label_20->setObjectName("label_20");

        _23->addWidget(label_20, 3, 0, 1, 1);

        helixAngle = new Gui::QuantitySpinBox(page8_helix);
        helixAngle->setObjectName("helixAngle");
        helixAngle->setKeyboardTracking(false);
        helixAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        _23->addWidget(helixAngle, 3, 1, 1, 1);

        label_15 = new QLabel(page8_helix);
        label_15->setObjectName("label_15");

        _23->addWidget(label_15, 4, 0, 1, 1);

        helixLocalCS = new QComboBox(page8_helix);
        helixLocalCS->addItem(QString());
        helixLocalCS->addItem(QString());
        helixLocalCS->setObjectName("helixLocalCS");

        _23->addWidget(helixLocalCS, 4, 1, 1, 1);


        _22->addLayout(_23, 0, 0, 1, 1);

        spacerItem11 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _22->addItem(spacerItem11, 1, 0, 1, 1);

        widgetStack->addWidget(page8_helix);
        page9_spiral = new QWidget();
        page9_spiral->setObjectName("page9_spiral");
        _24 = new QGridLayout(page9_spiral);
        _24->setSpacing(6);
        _24->setContentsMargins(11, 11, 11, 11);
        _24->setObjectName("_24");
        _24->setContentsMargins(9, 9, 9, 9);
        _25 = new QGridLayout();
        _25->setSpacing(6);
        _25->setObjectName("_25");
        _25->setContentsMargins(0, 0, 0, 0);
        label_spiral_growth = new QLabel(page9_spiral);
        label_spiral_growth->setObjectName("label_spiral_growth");

        _25->addWidget(label_spiral_growth, 0, 0, 1, 1);

        spiralGrowth = new Gui::QuantitySpinBox(page9_spiral);
        spiralGrowth->setObjectName("spiralGrowth");
        spiralGrowth->setKeyboardTracking(false);
        spiralGrowth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spiralGrowth->setValue(1.000000000000000);

        _25->addWidget(spiralGrowth, 0, 1, 1, 1);

        label_spiral_rotation = new QLabel(page9_spiral);
        label_spiral_rotation->setObjectName("label_spiral_rotation");

        _25->addWidget(label_spiral_rotation, 1, 0, 1, 1);

        spiralRotation = new QDoubleSpinBox(page9_spiral);
        spiralRotation->setObjectName("spiralRotation");
        spiralRotation->setKeyboardTracking(false);
        spiralRotation->setMaximum(1000.000000000000000);
        spiralRotation->setValue(2.000000000000000);

        _25->addWidget(spiralRotation, 1, 1, 1, 1);

        label_spiral_radius = new QLabel(page9_spiral);
        label_spiral_radius->setObjectName("label_spiral_radius");

        _25->addWidget(label_spiral_radius, 2, 0, 1, 1);

        spiralRadius = new Gui::QuantitySpinBox(page9_spiral);
        spiralRadius->setObjectName("spiralRadius");
        spiralRadius->setKeyboardTracking(false);
        spiralRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        spiralRadius->setValue(1.000000000000000);

        _25->addWidget(spiralRadius, 2, 1, 1, 1);


        _24->addLayout(_25, 0, 0, 1, 1);

        spacerItem12 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _24->addItem(spacerItem12, 1, 0, 1, 1);

        widgetStack->addWidget(page9_spiral);
        page10_circle = new QWidget();
        page10_circle->setObjectName("page10_circle");
        gridLayout_3 = new QGridLayout(page10_circle);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        circleParameters = new QGridLayout();
        circleParameters->setSpacing(6);
        circleParameters->setObjectName("circleParameters");
        circleParameters->setContentsMargins(0, 0, 0, 0);
        Radius = new QLabel(page10_circle);
        Radius->setObjectName("Radius");

        circleParameters->addWidget(Radius, 0, 0, 1, 1);

        circleRadius = new Gui::QuantitySpinBox(page10_circle);
        circleRadius->setObjectName("circleRadius");
        circleRadius->setKeyboardTracking(false);
        circleRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        circleRadius->setValue(2.000000000000000);

        circleParameters->addWidget(circleRadius, 0, 1, 1, 1);

        Angle1 = new QLabel(page10_circle);
        Angle1->setObjectName("Angle1");

        circleParameters->addWidget(Angle1, 1, 0, 1, 1);

        circleAngle1 = new Gui::QuantitySpinBox(page10_circle);
        circleAngle1->setObjectName("circleAngle1");
        circleAngle1->setKeyboardTracking(false);
        circleAngle1->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        circleParameters->addWidget(circleAngle1, 1, 1, 1, 1);

        Angle2 = new QLabel(page10_circle);
        Angle2->setObjectName("Angle2");

        circleParameters->addWidget(Angle2, 2, 0, 1, 1);

        circleAngle2 = new Gui::QuantitySpinBox(page10_circle);
        circleAngle2->setObjectName("circleAngle2");
        circleAngle2->setKeyboardTracking(false);
        circleAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        circleAngle2->setValue(360.000000000000000);

        circleParameters->addWidget(circleAngle2, 2, 1, 1, 1);


        gridLayout_3->addLayout(circleParameters, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonCircleFromThreePoints = new QPushButton(page10_circle);
        buttonCircleFromThreePoints->setObjectName("buttonCircleFromThreePoints");

        horizontalLayout->addWidget(buttonCircleFromThreePoints);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        widgetStack->addWidget(page10_circle);
        page = new QWidget();
        page->setObjectName("page");
        gridLayout_11 = new QGridLayout(page);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName("gridLayout_11");
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName("gridLayout_10");
        labelEllMajorRadius = new QLabel(page);
        labelEllMajorRadius->setObjectName("labelEllMajorRadius");

        gridLayout_10->addWidget(labelEllMajorRadius, 0, 0, 1, 1);

        ellipseMajorRadius = new Gui::QuantitySpinBox(page);
        ellipseMajorRadius->setObjectName("ellipseMajorRadius");
        ellipseMajorRadius->setKeyboardTracking(false);
        ellipseMajorRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipseMajorRadius->setValue(4.000000000000000);

        gridLayout_10->addWidget(ellipseMajorRadius, 0, 1, 1, 1);

        labelEllMinorRadius = new QLabel(page);
        labelEllMinorRadius->setObjectName("labelEllMinorRadius");

        gridLayout_10->addWidget(labelEllMinorRadius, 1, 0, 1, 1);

        ellipseMinorRadius = new Gui::QuantitySpinBox(page);
        ellipseMinorRadius->setObjectName("ellipseMinorRadius");
        ellipseMinorRadius->setKeyboardTracking(false);
        ellipseMinorRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipseMinorRadius->setValue(2.000000000000000);

        gridLayout_10->addWidget(ellipseMinorRadius, 1, 1, 1, 1);

        labelEllAngle1 = new QLabel(page);
        labelEllAngle1->setObjectName("labelEllAngle1");

        gridLayout_10->addWidget(labelEllAngle1, 2, 0, 1, 1);

        ellipseAngle1 = new Gui::QuantitySpinBox(page);
        ellipseAngle1->setObjectName("ellipseAngle1");
        ellipseAngle1->setKeyboardTracking(false);
        ellipseAngle1->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        gridLayout_10->addWidget(ellipseAngle1, 2, 1, 1, 1);

        labelEllAngle2 = new QLabel(page);
        labelEllAngle2->setObjectName("labelEllAngle2");

        gridLayout_10->addWidget(labelEllAngle2, 3, 0, 1, 1);

        ellipseAngle2 = new Gui::QuantitySpinBox(page);
        ellipseAngle2->setObjectName("ellipseAngle2");
        ellipseAngle2->setKeyboardTracking(false);
        ellipseAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        ellipseAngle2->setValue(360.000000000000000);

        gridLayout_10->addWidget(ellipseAngle2, 3, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_10, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_11->addItem(verticalSpacer_5, 1, 0, 1, 1);

        widgetStack->addWidget(page);
        page11_vertex = new QWidget();
        page11_vertex->setObjectName("page11_vertex");
        gridLayout_9 = new QGridLayout(page11_vertex);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName("gridLayout_4");
        label_X_Axis = new QLabel(page11_vertex);
        label_X_Axis->setObjectName("label_X_Axis");
        label_X_Axis->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_X_Axis, 0, 0, 1, 1);

        vertexX = new Gui::QuantitySpinBox(page11_vertex);
        vertexX->setObjectName("vertexX");
        vertexX->setKeyboardTracking(false);
        vertexX->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_4->addWidget(vertexX, 0, 1, 1, 1);

        label_Y_Axis = new QLabel(page11_vertex);
        label_Y_Axis->setObjectName("label_Y_Axis");
        label_Y_Axis->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_Y_Axis, 1, 0, 1, 1);

        vertexY = new Gui::QuantitySpinBox(page11_vertex);
        vertexY->setObjectName("vertexY");
        vertexY->setKeyboardTracking(false);
        vertexY->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_4->addWidget(vertexY, 1, 1, 1, 1);

        label_Z_Axis = new QLabel(page11_vertex);
        label_Z_Axis->setObjectName("label_Z_Axis");
        label_Z_Axis->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_Z_Axis, 2, 0, 1, 1);

        vertexZ = new Gui::QuantitySpinBox(page11_vertex);
        vertexZ->setObjectName("vertexZ");
        vertexZ->setKeyboardTracking(false);
        vertexZ->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_4->addWidget(vertexZ, 2, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer_3, 1, 0, 1, 1);

        widgetStack->addWidget(page11_vertex);
        page12_edge = new QWidget();
        page12_edge->setObjectName("page12_edge");
        gridLayout_6 = new QGridLayout(page12_edge);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName("gridLayout_5");
        Start_Vertex = new QLabel(page12_edge);
        Start_Vertex->setObjectName("Start_Vertex");

        gridLayout_5->addWidget(Start_Vertex, 0, 0, 1, 1);

        X1 = new QLabel(page12_edge);
        X1->setObjectName("X1");
        X1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(X1, 1, 0, 1, 1);

        edgeX1 = new Gui::QuantitySpinBox(page12_edge);
        edgeX1->setObjectName("edgeX1");
        edgeX1->setKeyboardTracking(false);
        edgeX1->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_5->addWidget(edgeX1, 1, 1, 1, 1);

        Y1 = new QLabel(page12_edge);
        Y1->setObjectName("Y1");
        Y1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(Y1, 2, 0, 1, 1);

        edgeY1 = new Gui::QuantitySpinBox(page12_edge);
        edgeY1->setObjectName("edgeY1");
        edgeY1->setKeyboardTracking(false);
        edgeY1->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_5->addWidget(edgeY1, 2, 1, 1, 1);

        Z1 = new QLabel(page12_edge);
        Z1->setObjectName("Z1");
        Z1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(Z1, 3, 0, 1, 1);

        edgeZ1 = new Gui::QuantitySpinBox(page12_edge);
        edgeZ1->setObjectName("edgeZ1");
        edgeZ1->setKeyboardTracking(false);
        edgeZ1->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout_5->addWidget(edgeZ1, 3, 1, 1, 1);

        line_6 = new QFrame(page12_edge);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_5->addWidget(line_6, 4, 0, 1, 1);

        Finish_Vertex = new QLabel(page12_edge);
        Finish_Vertex->setObjectName("Finish_Vertex");
        Finish_Vertex->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(Finish_Vertex, 5, 0, 1, 1);

        X2 = new QLabel(page12_edge);
        X2->setObjectName("X2");
        X2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(X2, 6, 0, 1, 1);

        edgeX2 = new Gui::QuantitySpinBox(page12_edge);
        edgeX2->setObjectName("edgeX2");
        edgeX2->setKeyboardTracking(false);
        edgeX2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        edgeX2->setValue(10.000000000000000);

        gridLayout_5->addWidget(edgeX2, 6, 1, 1, 1);

        Y2 = new QLabel(page12_edge);
        Y2->setObjectName("Y2");
        Y2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(Y2, 7, 0, 1, 1);

        edgeY2 = new Gui::QuantitySpinBox(page12_edge);
        edgeY2->setObjectName("edgeY2");
        edgeY2->setKeyboardTracking(false);
        edgeY2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        edgeY2->setValue(10.000000000000000);

        gridLayout_5->addWidget(edgeY2, 7, 1, 1, 1);

        Z2 = new QLabel(page12_edge);
        Z2->setObjectName("Z2");
        Z2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(Z2, 8, 0, 1, 1);

        edgeZ2 = new Gui::QuantitySpinBox(page12_edge);
        edgeZ2->setObjectName("edgeZ2");
        edgeZ2->setKeyboardTracking(false);
        edgeZ2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        edgeZ2->setValue(10.000000000000000);

        gridLayout_5->addWidget(edgeZ2, 8, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_6->addItem(verticalSpacer_4, 1, 0, 1, 1);

        widgetStack->addWidget(page12_edge);
        page_regularPolygon = new QWidget();
        page_regularPolygon->setObjectName("page_regularPolygon");
        _26 = new QGridLayout(page_regularPolygon);
        _26->setSpacing(6);
        _26->setContentsMargins(11, 11, 11, 11);
        _26->setObjectName("_26");
        _26->setContentsMargins(9, 9, 9, 9);
        _27 = new QGridLayout();
        _27->setSpacing(6);
        _27->setObjectName("_27");
        _27->setContentsMargins(0, 0, 0, 0);
        labelRegularPolygonPolygon = new QLabel(page_regularPolygon);
        labelRegularPolygonPolygon->setObjectName("labelRegularPolygonPolygon");

        _27->addWidget(labelRegularPolygonPolygon, 0, 0, 1, 1);

        regularPolygonPolygon = new QSpinBox(page_regularPolygon);
        regularPolygonPolygon->setObjectName("regularPolygonPolygon");
        regularPolygonPolygon->setKeyboardTracking(false);
        regularPolygonPolygon->setMinimum(3);
        regularPolygonPolygon->setMaximum(1000);
        regularPolygonPolygon->setValue(6);

        _27->addWidget(regularPolygonPolygon, 0, 1, 1, 1);

        labelRegularPolygonCircumradius = new QLabel(page_regularPolygon);
        labelRegularPolygonCircumradius->setObjectName("labelRegularPolygonCircumradius");

        _27->addWidget(labelRegularPolygonCircumradius, 1, 0, 1, 1);

        regularPolygonCircumradius = new Gui::QuantitySpinBox(page_regularPolygon);
        regularPolygonCircumradius->setObjectName("regularPolygonCircumradius");
        regularPolygonCircumradius->setKeyboardTracking(false);
        regularPolygonCircumradius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        regularPolygonCircumradius->setValue(2.000000000000000);

        _27->addWidget(regularPolygonCircumradius, 1, 1, 1, 1);


        _26->addLayout(_27, 0, 0, 1, 1);

        spacerItem13 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _26->addItem(spacerItem13, 1, 0, 1, 1);

        widgetStack->addWidget(page_regularPolygon);

        verticalLayout->addWidget(widgetStack);

        operationLayout = new QHBoxLayout();
        operationLayout->setSpacing(6);
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__DlgPrimitives);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__DlgPrimitives);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);


        verticalLayout->addLayout(operationLayout);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)

        retranslateUi(PartDesignGui__DlgPrimitives);

        widgetStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PartDesignGui__DlgPrimitives);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__DlgPrimitives)
    {
        PartDesignGui__DlgPrimitives->setWindowTitle(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Geometric Primitives", nullptr));
        textLabel2_2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Length", nullptr));
        textLabel3_2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Width", nullptr));
        textLabel2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Length", nullptr));
        textLabel3->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Width", nullptr));
        textLabel4->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Height", nullptr));
        textLabel5->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius", nullptr));
        textLabel6->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Height", nullptr));
        labelCylinderXSkew->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in first direction", nullptr));
#if QT_CONFIG(tooltip)
        cylinderXSkew->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in first direction", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCylinderYSkew->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in second direction", nullptr));
#if QT_CONFIG(tooltip)
        cylinderYSkew->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in second direction", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Rotation angle", nullptr));
        textLabel9->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 1", nullptr));
        textLabel10->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 2", nullptr));
        textLabel11->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Height", nullptr));
        label_4->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle", nullptr));
        textLabel14->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius", nullptr));
        label_3->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "U parameter", nullptr));
        label_2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "V parameters", nullptr));
        textLabel21->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 1", nullptr));
#if QT_CONFIG(tooltip)
        ellipsoidRadius1->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius in local z-direction", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabel22->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 2", nullptr));
#if QT_CONFIG(tooltip)
        ellipsoidRadius2->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius in local X-direction", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabel23->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 3", nullptr));
#if QT_CONFIG(tooltip)
        ellipsoidRadius3->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius in local Y-direction\n"
"If zero, it is equal to Radius2", nullptr));
#endif // QT_CONFIG(tooltip)
        label23->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "U parameter", nullptr));
        label24->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "V parameter", nullptr));
        textLabel19->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 1", nullptr));
#if QT_CONFIG(tooltip)
        torusRadius1->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius in local XY-plane", nullptr));
#endif // QT_CONFIG(tooltip)
        textLabel20->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius 2", nullptr));
#if QT_CONFIG(tooltip)
        torusRadius2->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius in local XZ-plane", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "U parameter", nullptr));
        label_6->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "V parameter", nullptr));
        labelPrismPolygon->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Polygon", nullptr));
        labelPrismCircumradius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Circumradius", nullptr));
        labelPrismHeight->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Height", nullptr));
        labelPrismXSkew->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in first direction", nullptr));
#if QT_CONFIG(tooltip)
        prismXSkew->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in first direction", nullptr));
#endif // QT_CONFIG(tooltip)
        labelPrismYSkew->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in second direction", nullptr));
#if QT_CONFIG(tooltip)
        prismYSkew->setToolTip(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle in second direction", nullptr));
#endif // QT_CONFIG(tooltip)
        label_10->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "X min/max", nullptr));
        label_11->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Y min/max", nullptr));
        label_12->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Z min/max", nullptr));
        label_13->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "X2 min/max", nullptr));
        label_14->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Z2 min/max", nullptr));
        label_7->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Pitch", nullptr));
        label_8->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Height", nullptr));
        label_9->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius", nullptr));
        label_20->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle", nullptr));
        label_15->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Coordinate system", nullptr));
        helixLocalCS->setItemText(0, QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Right-handed", nullptr));
        helixLocalCS->setItemText(1, QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Left-handed", nullptr));

        label_spiral_growth->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Growth", nullptr));
        label_spiral_rotation->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Number of rotations", nullptr));
        label_spiral_radius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius", nullptr));
        Radius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Radius", nullptr));
        Angle1->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle 1", nullptr));
        Angle2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle 2", nullptr));
        buttonCircleFromThreePoints->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "From 3 Points", nullptr));
        labelEllMajorRadius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Major radius", nullptr));
        labelEllMinorRadius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Minor radius", nullptr));
        labelEllAngle1->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle 1", nullptr));
        labelEllAngle2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Angle 2", nullptr));
        label_X_Axis->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "X", nullptr));
        label_Y_Axis->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Y", nullptr));
        label_Z_Axis->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Z", nullptr));
        Start_Vertex->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Start point", nullptr));
        X1->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "X", nullptr));
        Y1->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Y", nullptr));
        Z1->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Z", nullptr));
        Finish_Vertex->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "End point", nullptr));
        X2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "X", nullptr));
        Y2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Y", nullptr));
        Z2->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Z", nullptr));
        labelRegularPolygonPolygon->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Polygon", nullptr));
        labelRegularPolygonCircumradius->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Circumradius", nullptr));
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::DlgPrimitives", "Common", nullptr));

    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class DlgPrimitives: public Ui_DlgPrimitives {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPRIMITIVEPARAMETERS_H
