/********************************************************************************
** Form generated from reading UI file 'DlgRegularSolid.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGREGULARSOLID_H
#define UI_DLGREGULARSOLID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace MeshGui {

class Ui_DlgRegularSolid
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout1;
    QComboBox *comboBox1;
    QStackedWidget *widgetStack2;
    QWidget *WStackPage1;
    QGridLayout *gridLayout2;
    QGridLayout *gridLayout3;
    QLabel *textLabel2;
    Gui::QuantitySpinBox *boxLength;
    QLabel *textLabel3;
    Gui::QuantitySpinBox *boxWidth;
    QLabel *textLabel4;
    Gui::QuantitySpinBox *boxHeight;
    QSpacerItem *spacerItem;
    QWidget *WStackPage2;
    QGridLayout *gridLayout4;
    QGridLayout *gridLayout5;
    QLabel *textLabel5;
    Gui::QuantitySpinBox *cylinderRadius;
    QLabel *textLabel6;
    Gui::QuantitySpinBox *cylinderLength;
    QFrame *line1;
    QGridLayout *gridLayout6;
    QLabel *textLabel7;
    Gui::QuantitySpinBox *cylinderEdgeLength;
    QLabel *textLabel8;
    QSpinBox *cylinderCount;
    QCheckBox *cylinderClosed;
    QSpacerItem *spacerItem1;
    QWidget *WStackPage3;
    QGridLayout *gridLayout7;
    QGridLayout *gridLayout8;
    QLabel *textLabel9;
    Gui::QuantitySpinBox *coneRadius1;
    QLabel *textLabel10;
    Gui::QuantitySpinBox *coneRadius2;
    QLabel *textLabel11;
    Gui::QuantitySpinBox *coneLength;
    QFrame *line2;
    QGridLayout *gridLayout9;
    QLabel *textLabel12;
    Gui::QuantitySpinBox *coneEdgeLength;
    QLabel *textLabel13;
    QSpinBox *coneCount;
    QCheckBox *coneClosed;
    QSpacerItem *spacerItem2;
    QWidget *WStackPage4;
    QGridLayout *gridLayout10;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel14;
    Gui::QuantitySpinBox *sphereRadius;
    QFrame *line3;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel15;
    QSpinBox *sphereCount;
    QSpacerItem *spacerItem3;
    QWidget *WStackPage5;
    QGridLayout *gridLayout11;
    QGridLayout *gridLayout12;
    QLabel *textLabel16;
    Gui::QuantitySpinBox *ellipsoidRadius1;
    QLabel *textLabel17;
    Gui::QuantitySpinBox *ellipsoidRadius2;
    QFrame *line4;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel18;
    QSpinBox *ellipsoidCount;
    QSpacerItem *spacerItem4;
    QWidget *WStackPage6;
    QGridLayout *gridLayout13;
    QGridLayout *gridLayout14;
    QLabel *textLabel19;
    Gui::QuantitySpinBox *toroidRadius1;
    QLabel *textLabel20;
    Gui::QuantitySpinBox *toroidRadius2;
    QFrame *line5;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel21;
    QSpinBox *toroidCount;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout4;
    QSpacerItem *spacerItem6;
    QPushButton *createSolidButton;
    QPushButton *buttonClose;

    void setupUi(QDialog *MeshGui__DlgRegularSolid)
    {
        if (MeshGui__DlgRegularSolid->objectName().isEmpty())
            MeshGui__DlgRegularSolid->setObjectName("MeshGui__DlgRegularSolid");
        MeshGui__DlgRegularSolid->resize(265, 319);
        MeshGui__DlgRegularSolid->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(MeshGui__DlgRegularSolid);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(10, 10, 10, 10);
        gridLayout->setObjectName("gridLayout");
        groupBox1 = new QGroupBox(MeshGui__DlgRegularSolid);
        groupBox1->setObjectName("groupBox1");
        gridLayout1 = new QGridLayout(groupBox1);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(10, 10, 10, 10);
        gridLayout1->setObjectName("gridLayout1");
        comboBox1 = new QComboBox(groupBox1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Cube.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Cylinder.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Cone.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Sphere.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Ellipsoid.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/RegularSolids/Mesh_Torus.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        comboBox1->addItem(icon5, QString());
        comboBox1->setObjectName("comboBox1");

        gridLayout1->addWidget(comboBox1, 0, 0, 1, 1);

        widgetStack2 = new QStackedWidget(groupBox1);
        widgetStack2->setObjectName("widgetStack2");
        WStackPage1 = new QWidget();
        WStackPage1->setObjectName("WStackPage1");
        gridLayout2 = new QGridLayout(WStackPage1);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout3 = new QGridLayout();
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(0, 0, 0, 0);
        gridLayout3->setObjectName("gridLayout3");
        textLabel2 = new QLabel(WStackPage1);
        textLabel2->setObjectName("textLabel2");

        gridLayout3->addWidget(textLabel2, 0, 0, 1, 1);

        boxLength = new Gui::QuantitySpinBox(WStackPage1);
        boxLength->setObjectName("boxLength");
        boxLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxLength->setMinimum(0.000000000000000);
        boxLength->setMaximum(1000.000000000000000);
        boxLength->setValue(10.000000000000000);

        gridLayout3->addWidget(boxLength, 0, 1, 1, 1);

        textLabel3 = new QLabel(WStackPage1);
        textLabel3->setObjectName("textLabel3");

        gridLayout3->addWidget(textLabel3, 1, 0, 1, 1);

        boxWidth = new Gui::QuantitySpinBox(WStackPage1);
        boxWidth->setObjectName("boxWidth");
        boxWidth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxWidth->setMaximum(1000.000000000000000);
        boxWidth->setValue(10.000000000000000);

        gridLayout3->addWidget(boxWidth, 1, 1, 1, 1);

        textLabel4 = new QLabel(WStackPage1);
        textLabel4->setObjectName("textLabel4");

        gridLayout3->addWidget(textLabel4, 2, 0, 1, 1);

        boxHeight = new Gui::QuantitySpinBox(WStackPage1);
        boxHeight->setObjectName("boxHeight");
        boxHeight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        boxHeight->setMaximum(1000.000000000000000);
        boxHeight->setValue(10.000000000000000);

        gridLayout3->addWidget(boxHeight, 2, 1, 1, 1);


        gridLayout2->addLayout(gridLayout3, 0, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 51, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout2->addItem(spacerItem, 1, 0, 1, 1);

        widgetStack2->addWidget(WStackPage1);
        WStackPage2 = new QWidget();
        WStackPage2->setObjectName("WStackPage2");
        gridLayout4 = new QGridLayout(WStackPage2);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(0, 0, 0, 0);
        gridLayout4->setObjectName("gridLayout4");
        gridLayout5 = new QGridLayout();
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(0, 0, 0, 0);
        gridLayout5->setObjectName("gridLayout5");
        textLabel5 = new QLabel(WStackPage2);
        textLabel5->setObjectName("textLabel5");

        gridLayout5->addWidget(textLabel5, 0, 0, 1, 1);

        cylinderRadius = new Gui::QuantitySpinBox(WStackPage2);
        cylinderRadius->setObjectName("cylinderRadius");
        cylinderRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        cylinderRadius->setValue(2.000000000000000);

        gridLayout5->addWidget(cylinderRadius, 0, 1, 1, 1);

        textLabel6 = new QLabel(WStackPage2);
        textLabel6->setObjectName("textLabel6");

        gridLayout5->addWidget(textLabel6, 1, 0, 1, 1);

        cylinderLength = new Gui::QuantitySpinBox(WStackPage2);
        cylinderLength->setObjectName("cylinderLength");
        cylinderLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        cylinderLength->setValue(10.000000000000000);

        gridLayout5->addWidget(cylinderLength, 1, 1, 1, 1);


        gridLayout4->addLayout(gridLayout5, 0, 0, 1, 1);

        line1 = new QFrame(WStackPage2);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        gridLayout4->addWidget(line1, 1, 0, 1, 1);

        gridLayout6 = new QGridLayout();
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(0, 0, 0, 0);
        gridLayout6->setObjectName("gridLayout6");
        textLabel7 = new QLabel(WStackPage2);
        textLabel7->setObjectName("textLabel7");

        gridLayout6->addWidget(textLabel7, 0, 0, 1, 1);

        cylinderEdgeLength = new Gui::QuantitySpinBox(WStackPage2);
        cylinderEdgeLength->setObjectName("cylinderEdgeLength");
        cylinderEdgeLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        cylinderEdgeLength->setMaximum(10.000000000000000);
        cylinderEdgeLength->setValue(1.000000000000000);

        gridLayout6->addWidget(cylinderEdgeLength, 0, 1, 1, 1);

        textLabel8 = new QLabel(WStackPage2);
        textLabel8->setObjectName("textLabel8");

        gridLayout6->addWidget(textLabel8, 1, 0, 1, 1);

        cylinderCount = new QSpinBox(WStackPage2);
        cylinderCount->setObjectName("cylinderCount");
        cylinderCount->setValue(50);

        gridLayout6->addWidget(cylinderCount, 1, 1, 1, 1);

        cylinderClosed = new QCheckBox(WStackPage2);
        cylinderClosed->setObjectName("cylinderClosed");
        cylinderClosed->setChecked(true);

        gridLayout6->addWidget(cylinderClosed, 2, 0, 1, 2);


        gridLayout4->addLayout(gridLayout6, 2, 0, 1, 1);

        spacerItem1 = new QSpacerItem(31, 81, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout4->addItem(spacerItem1, 3, 0, 1, 1);

        widgetStack2->addWidget(WStackPage2);
        WStackPage3 = new QWidget();
        WStackPage3->setObjectName("WStackPage3");
        gridLayout7 = new QGridLayout(WStackPage3);
        gridLayout7->setSpacing(6);
        gridLayout7->setContentsMargins(0, 0, 0, 0);
        gridLayout7->setObjectName("gridLayout7");
        gridLayout8 = new QGridLayout();
        gridLayout8->setSpacing(6);
        gridLayout8->setContentsMargins(0, 0, 0, 0);
        gridLayout8->setObjectName("gridLayout8");
        textLabel9 = new QLabel(WStackPage3);
        textLabel9->setObjectName("textLabel9");

        gridLayout8->addWidget(textLabel9, 0, 0, 1, 1);

        coneRadius1 = new Gui::QuantitySpinBox(WStackPage3);
        coneRadius1->setObjectName("coneRadius1");
        coneRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneRadius1->setValue(2.000000000000000);

        gridLayout8->addWidget(coneRadius1, 0, 1, 1, 1);

        textLabel10 = new QLabel(WStackPage3);
        textLabel10->setObjectName("textLabel10");

        gridLayout8->addWidget(textLabel10, 1, 0, 1, 1);

        coneRadius2 = new Gui::QuantitySpinBox(WStackPage3);
        coneRadius2->setObjectName("coneRadius2");
        coneRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneRadius2->setValue(4.000000000000000);

        gridLayout8->addWidget(coneRadius2, 1, 1, 2, 1);

        textLabel11 = new QLabel(WStackPage3);
        textLabel11->setObjectName("textLabel11");

        gridLayout8->addWidget(textLabel11, 2, 0, 2, 1);

        coneLength = new Gui::QuantitySpinBox(WStackPage3);
        coneLength->setObjectName("coneLength");
        coneLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneLength->setValue(10.000000000000000);

        gridLayout8->addWidget(coneLength, 3, 1, 1, 1);


        gridLayout7->addLayout(gridLayout8, 0, 0, 1, 1);

        line2 = new QFrame(WStackPage3);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        gridLayout7->addWidget(line2, 1, 0, 1, 1);

        gridLayout9 = new QGridLayout();
        gridLayout9->setSpacing(6);
        gridLayout9->setContentsMargins(0, 0, 0, 0);
        gridLayout9->setObjectName("gridLayout9");
        textLabel12 = new QLabel(WStackPage3);
        textLabel12->setObjectName("textLabel12");

        gridLayout9->addWidget(textLabel12, 0, 0, 1, 1);

        coneEdgeLength = new Gui::QuantitySpinBox(WStackPage3);
        coneEdgeLength->setObjectName("coneEdgeLength");
        coneEdgeLength->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        coneEdgeLength->setValue(1.000000000000000);

        gridLayout9->addWidget(coneEdgeLength, 0, 1, 1, 1);

        textLabel13 = new QLabel(WStackPage3);
        textLabel13->setObjectName("textLabel13");

        gridLayout9->addWidget(textLabel13, 1, 0, 1, 1);

        coneCount = new QSpinBox(WStackPage3);
        coneCount->setObjectName("coneCount");
        coneCount->setValue(50);

        gridLayout9->addWidget(coneCount, 1, 1, 1, 1);

        coneClosed = new QCheckBox(WStackPage3);
        coneClosed->setObjectName("coneClosed");
        coneClosed->setChecked(true);

        gridLayout9->addWidget(coneClosed, 2, 0, 1, 1);


        gridLayout7->addLayout(gridLayout9, 2, 0, 1, 1);

        spacerItem2 = new QSpacerItem(31, 91, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout7->addItem(spacerItem2, 3, 0, 1, 1);

        widgetStack2->addWidget(WStackPage3);
        WStackPage4 = new QWidget();
        WStackPage4->setObjectName("WStackPage4");
        gridLayout10 = new QGridLayout(WStackPage4);
        gridLayout10->setSpacing(6);
        gridLayout10->setContentsMargins(0, 0, 0, 0);
        gridLayout10->setObjectName("gridLayout10");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        textLabel14 = new QLabel(WStackPage4);
        textLabel14->setObjectName("textLabel14");

        hboxLayout->addWidget(textLabel14);

        sphereRadius = new Gui::QuantitySpinBox(WStackPage4);
        sphereRadius->setObjectName("sphereRadius");
        sphereRadius->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        sphereRadius->setValue(5.000000000000000);

        hboxLayout->addWidget(sphereRadius);


        gridLayout10->addLayout(hboxLayout, 0, 0, 1, 1);

        line3 = new QFrame(WStackPage4);
        line3->setObjectName("line3");
        line3->setFrameShape(QFrame::HLine);
        line3->setFrameShadow(QFrame::Sunken);

        gridLayout10->addWidget(line3, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName("hboxLayout1");
        textLabel15 = new QLabel(WStackPage4);
        textLabel15->setObjectName("textLabel15");

        hboxLayout1->addWidget(textLabel15);

        sphereCount = new QSpinBox(WStackPage4);
        sphereCount->setObjectName("sphereCount");
        sphereCount->setValue(50);

        hboxLayout1->addWidget(sphereCount);


        gridLayout10->addLayout(hboxLayout1, 2, 0, 1, 1);

        spacerItem3 = new QSpacerItem(21, 151, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout10->addItem(spacerItem3, 3, 0, 1, 1);

        widgetStack2->addWidget(WStackPage4);
        WStackPage5 = new QWidget();
        WStackPage5->setObjectName("WStackPage5");
        gridLayout11 = new QGridLayout(WStackPage5);
        gridLayout11->setSpacing(6);
        gridLayout11->setContentsMargins(0, 0, 0, 0);
        gridLayout11->setObjectName("gridLayout11");
        gridLayout12 = new QGridLayout();
        gridLayout12->setSpacing(6);
        gridLayout12->setContentsMargins(0, 0, 0, 0);
        gridLayout12->setObjectName("gridLayout12");
        textLabel16 = new QLabel(WStackPage5);
        textLabel16->setObjectName("textLabel16");

        gridLayout12->addWidget(textLabel16, 0, 0, 1, 1);

        ellipsoidRadius1 = new Gui::QuantitySpinBox(WStackPage5);
        ellipsoidRadius1->setObjectName("ellipsoidRadius1");
        ellipsoidRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipsoidRadius1->setValue(2.000000000000000);

        gridLayout12->addWidget(ellipsoidRadius1, 0, 1, 1, 1);

        textLabel17 = new QLabel(WStackPage5);
        textLabel17->setObjectName("textLabel17");

        gridLayout12->addWidget(textLabel17, 1, 0, 1, 1);

        ellipsoidRadius2 = new Gui::QuantitySpinBox(WStackPage5);
        ellipsoidRadius2->setObjectName("ellipsoidRadius2");
        ellipsoidRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        ellipsoidRadius2->setValue(4.000000000000000);

        gridLayout12->addWidget(ellipsoidRadius2, 1, 1, 1, 1);


        gridLayout11->addLayout(gridLayout12, 0, 0, 1, 1);

        line4 = new QFrame(WStackPage5);
        line4->setObjectName("line4");
        line4->setFrameShape(QFrame::HLine);
        line4->setFrameShadow(QFrame::Sunken);

        gridLayout11->addWidget(line4, 1, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName("hboxLayout2");
        textLabel18 = new QLabel(WStackPage5);
        textLabel18->setObjectName("textLabel18");

        hboxLayout2->addWidget(textLabel18);

        ellipsoidCount = new QSpinBox(WStackPage5);
        ellipsoidCount->setObjectName("ellipsoidCount");
        ellipsoidCount->setValue(50);

        hboxLayout2->addWidget(ellipsoidCount);


        gridLayout11->addLayout(hboxLayout2, 2, 0, 1, 1);

        spacerItem4 = new QSpacerItem(31, 81, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout11->addItem(spacerItem4, 3, 0, 1, 1);

        widgetStack2->addWidget(WStackPage5);
        WStackPage6 = new QWidget();
        WStackPage6->setObjectName("WStackPage6");
        gridLayout13 = new QGridLayout(WStackPage6);
        gridLayout13->setSpacing(6);
        gridLayout13->setContentsMargins(0, 0, 0, 0);
        gridLayout13->setObjectName("gridLayout13");
        gridLayout14 = new QGridLayout();
        gridLayout14->setSpacing(6);
        gridLayout14->setContentsMargins(0, 0, 0, 0);
        gridLayout14->setObjectName("gridLayout14");
        textLabel19 = new QLabel(WStackPage6);
        textLabel19->setObjectName("textLabel19");

        gridLayout14->addWidget(textLabel19, 0, 0, 1, 1);

        toroidRadius1 = new Gui::QuantitySpinBox(WStackPage6);
        toroidRadius1->setObjectName("toroidRadius1");
        toroidRadius1->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        toroidRadius1->setValue(10.000000000000000);

        gridLayout14->addWidget(toroidRadius1, 0, 1, 1, 1);

        textLabel20 = new QLabel(WStackPage6);
        textLabel20->setObjectName("textLabel20");

        gridLayout14->addWidget(textLabel20, 1, 0, 1, 1);

        toroidRadius2 = new Gui::QuantitySpinBox(WStackPage6);
        toroidRadius2->setObjectName("toroidRadius2");
        toroidRadius2->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        toroidRadius2->setValue(2.000000000000000);

        gridLayout14->addWidget(toroidRadius2, 1, 1, 1, 1);


        gridLayout13->addLayout(gridLayout14, 0, 0, 1, 1);

        line5 = new QFrame(WStackPage6);
        line5->setObjectName("line5");
        line5->setFrameShape(QFrame::HLine);
        line5->setFrameShadow(QFrame::Sunken);

        gridLayout13->addWidget(line5, 1, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName("hboxLayout3");
        textLabel21 = new QLabel(WStackPage6);
        textLabel21->setObjectName("textLabel21");

        hboxLayout3->addWidget(textLabel21);

        toroidCount = new QSpinBox(WStackPage6);
        toroidCount->setObjectName("toroidCount");
        toroidCount->setValue(50);

        hboxLayout3->addWidget(toroidCount);


        gridLayout13->addLayout(hboxLayout3, 2, 0, 1, 1);

        spacerItem5 = new QSpacerItem(20, 91, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout13->addItem(spacerItem5, 3, 0, 1, 1);

        widgetStack2->addWidget(WStackPage6);

        gridLayout1->addWidget(widgetStack2, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox1, 0, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName("hboxLayout4");
        spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout4->addItem(spacerItem6);

        createSolidButton = new QPushButton(MeshGui__DlgRegularSolid);
        createSolidButton->setObjectName("createSolidButton");
        createSolidButton->setAutoDefault(true);

        hboxLayout4->addWidget(createSolidButton);

        buttonClose = new QPushButton(MeshGui__DlgRegularSolid);
        buttonClose->setObjectName("buttonClose");
        buttonClose->setAutoDefault(true);

        hboxLayout4->addWidget(buttonClose);


        gridLayout->addLayout(hboxLayout4, 1, 0, 1, 1);

        QWidget::setTabOrder(comboBox1, boxLength);
        QWidget::setTabOrder(boxLength, boxWidth);
        QWidget::setTabOrder(boxWidth, boxHeight);
        QWidget::setTabOrder(boxHeight, cylinderRadius);
        QWidget::setTabOrder(cylinderRadius, cylinderLength);
        QWidget::setTabOrder(cylinderLength, cylinderEdgeLength);
        QWidget::setTabOrder(cylinderEdgeLength, cylinderCount);
        QWidget::setTabOrder(cylinderCount, cylinderClosed);
        QWidget::setTabOrder(cylinderClosed, coneRadius1);
        QWidget::setTabOrder(coneRadius1, coneRadius2);
        QWidget::setTabOrder(coneRadius2, coneLength);
        QWidget::setTabOrder(coneLength, coneEdgeLength);
        QWidget::setTabOrder(coneEdgeLength, coneCount);
        QWidget::setTabOrder(coneCount, coneClosed);
        QWidget::setTabOrder(coneClosed, sphereRadius);
        QWidget::setTabOrder(sphereRadius, sphereCount);
        QWidget::setTabOrder(sphereCount, ellipsoidRadius1);
        QWidget::setTabOrder(ellipsoidRadius1, ellipsoidRadius2);
        QWidget::setTabOrder(ellipsoidRadius2, ellipsoidCount);
        QWidget::setTabOrder(ellipsoidCount, toroidRadius1);
        QWidget::setTabOrder(toroidRadius1, toroidRadius2);
        QWidget::setTabOrder(toroidRadius2, toroidCount);
        QWidget::setTabOrder(toroidCount, createSolidButton);
        QWidget::setTabOrder(createSolidButton, buttonClose);

        retranslateUi(MeshGui__DlgRegularSolid);
        QObject::connect(comboBox1, &QComboBox::activated, widgetStack2, &QStackedWidget::setCurrentIndex);
        QObject::connect(buttonClose, &QPushButton::clicked, MeshGui__DlgRegularSolid, qOverload<>(&QDialog::reject));

        widgetStack2->setCurrentIndex(0);
        createSolidButton->setDefault(true);


        QMetaObject::connectSlotsByName(MeshGui__DlgRegularSolid);
    } // setupUi

    void retranslateUi(QDialog *MeshGui__DlgRegularSolid)
    {
        MeshGui__DlgRegularSolid->setWindowTitle(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Regular Solid", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Solid", nullptr));
        comboBox1->setItemText(0, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Cube", nullptr));
        comboBox1->setItemText(1, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Cylinder", nullptr));
        comboBox1->setItemText(2, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Cone", nullptr));
        comboBox1->setItemText(3, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sphere", nullptr));
        comboBox1->setItemText(4, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Ellipsoid", nullptr));
        comboBox1->setItemText(5, QCoreApplication::translate("MeshGui::DlgRegularSolid", "Torus", nullptr));

        textLabel2->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Length", nullptr));
        textLabel3->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Width", nullptr));
        textLabel4->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Height", nullptr));
        textLabel5->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius", nullptr));
        textLabel6->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Length", nullptr));
        textLabel7->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Edge length", nullptr));
        textLabel8->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sampling", nullptr));
        cylinderClosed->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Closed", nullptr));
        textLabel9->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 1", nullptr));
        textLabel10->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 2", nullptr));
        textLabel11->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Length", nullptr));
        textLabel12->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Edge length", nullptr));
        textLabel13->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sampling", nullptr));
        coneClosed->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Closed", nullptr));
        textLabel14->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius", nullptr));
        textLabel15->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sampling", nullptr));
        textLabel16->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 1", nullptr));
        textLabel17->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 2", nullptr));
        textLabel18->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sampling", nullptr));
        textLabel19->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 1", nullptr));
        textLabel20->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Radius 2", nullptr));
        textLabel21->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Sampling", nullptr));
        createSolidButton->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "&Create", nullptr));
#if QT_CONFIG(shortcut)
        createSolidButton->setShortcut(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Alt+C", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonClose->setText(QCoreApplication::translate("MeshGui::DlgRegularSolid", "Close", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class DlgRegularSolid: public Ui_DlgRegularSolid {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_DLGREGULARSOLID_H
