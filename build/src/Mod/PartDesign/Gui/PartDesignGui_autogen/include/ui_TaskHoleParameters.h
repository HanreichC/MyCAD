/********************************************************************************
** Form generated from reading UI file 'TaskHoleParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKHOLEPARAMETERS_H
#define UI_TASKHOLEPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/ElideCheckBox.h"
#include "Gui/ElideLabel.h"
#include "Gui/FontScaledSVG.h"
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

QT_BEGIN_NAMESPACE

class Ui_TaskHoleParameters
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *ProfileAndPlacementGroupBox;
    QVBoxLayout *profileAndPlacementLayout;
    QGridLayout *TopLayout;
    Gui::ElideLabel *labelProfileType;
    QComboBox *BaseProfileType;
    Gui::ElideLabel *labelStart;
    QComboBox *StartType;
    Gui::ElideLabel *labelStartReference;
    QLineEdit *lineStartReference;
    QPushButton *buttonStartReference;
    Gui::ElideLabel *labelStartOffset;
    Gui::PrefQuantitySpinBox *StartOffset;
    QGroupBox *HoleGroupBox;
    QVBoxLayout *holeLayout;
    QGridLayout *holeTopLayout;
    Gui::ElideLabel *labelThreadType;
    QComboBox *ThreadType;
    Gui::ElideLabel *labelSize;
    QComboBox *ThreadSize;
    Gui::ElideLabel *labelHeadType;
    QComboBox *HoleCutType;
    Gui::ElideLabel *labelDepthType;
    QComboBox *DepthType;
    Gui::ElideCheckBox *HoleCutCustomValues;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_13;
    Gui::ElideLabel *labelHoleCutDiameter;
    Gui::PrefQuantitySpinBox *HoleCutDiameter;
    QVBoxLayout *verticalLayout_12;
    Gui::ElideLabel *labelHoleCutDepth;
    Gui::PrefQuantitySpinBox *HoleCutDepth;
    QFrame *DrillFrame;
    QVBoxLayout *verticalLayout_5;
    Gui::ElideCheckBox *DrillPointAngled;
    Gui::PrefQuantitySpinBox *DrillPointAngle;
    Gui::ElideCheckBox *DrillForDepth;
    Gui::FontScaledSVG *cutDiagram;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_9;
    Gui::ElideLabel *labelHoleCutCountersinkAngle;
    Gui::PrefQuantitySpinBox *HoleCutCountersinkAngle;
    QVBoxLayout *verticalLayout_10;
    Gui::ElideLabel *labelDepth;
    Gui::PrefQuantitySpinBox *Depth;
    QVBoxLayout *verticalLayout_11;
    Gui::ElideLabel *labelDiameter;
    Gui::PrefQuantitySpinBox *Diameter;
    QHBoxLayout *horizontalLayout_7;
    Gui::ElideCheckBox *Reversed;
    QCheckBox *Tapered;
    Gui::PrefQuantitySpinBox *TaperedAngle;
    QGridLayout *profileLayout;
    QComboBox *HoleType;
    Gui::ElideLabel *labelHoleType;
    Gui::ElideLabel *labelThreadClearance;
    QComboBox *ThreadFit;
    QWidget *ClearanceWidget;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *ThreadGroupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *modelThreadLayout;
    Gui::ElideCheckBox *ModelThread;
    Gui::ElideCheckBox *UpdateView;
    QGridLayout *classLayout;
    QComboBox *ThreadClass;
    Gui::ElideLabel *labelThreadClass;
    QVBoxLayout *verticalLayout;
    QLabel *labelThreadDirection;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *directionRightHand;
    QRadioButton *directionLeftHand;
    QWidget *ThreadDepthWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *depthTypeLayout;
    Gui::ElideLabel *labelThreadDepthType;
    QComboBox *ThreadDepthType;
    QWidget *ThreadDepthDimensionWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelThreadDepth;
    Gui::PrefQuantitySpinBox *ThreadDepth;
    QWidget *CustomClearanceWidget;
    QHBoxLayout *horizontalLayout_13;
    Gui::ElideCheckBox *UseCustomThreadClearance;
    Gui::PrefQuantitySpinBox *CustomThreadClearance;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;
    QButtonGroup *directionButtonGroup;

    void setupUi(QWidget *TaskHoleParameters)
    {
        if (TaskHoleParameters->objectName().isEmpty())
            TaskHoleParameters->setObjectName("TaskHoleParameters");
        TaskHoleParameters->resize(414, 903);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaskHoleParameters->sizePolicy().hasHeightForWidth());
        TaskHoleParameters->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(TaskHoleParameters);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(3, 6, 3, 6);
        ProfileAndPlacementGroupBox = new QGroupBox(TaskHoleParameters);
        ProfileAndPlacementGroupBox->setObjectName("ProfileAndPlacementGroupBox");
        ProfileAndPlacementGroupBox->setFlat(true);
        profileAndPlacementLayout = new QVBoxLayout(ProfileAndPlacementGroupBox);
        profileAndPlacementLayout->setObjectName("profileAndPlacementLayout");
        TopLayout = new QGridLayout();
        TopLayout->setObjectName("TopLayout");
        TopLayout->setContentsMargins(-1, 10, -1, -1);
        labelProfileType = new Gui::ElideLabel(ProfileAndPlacementGroupBox);
        labelProfileType->setObjectName("labelProfileType");

        TopLayout->addWidget(labelProfileType, 0, 0, 1, 1);

        BaseProfileType = new QComboBox(ProfileAndPlacementGroupBox);
        BaseProfileType->addItem(QString());
        BaseProfileType->addItem(QString());
        BaseProfileType->addItem(QString());
        BaseProfileType->setObjectName("BaseProfileType");

        TopLayout->addWidget(BaseProfileType, 0, 1, 1, 1);

        labelStart = new Gui::ElideLabel(ProfileAndPlacementGroupBox);
        labelStart->setObjectName("labelStart");

        TopLayout->addWidget(labelStart, 1, 0, 1, 1);

        StartType = new QComboBox(ProfileAndPlacementGroupBox);
        StartType->addItem(QString());
        StartType->addItem(QString());
        StartType->addItem(QString());
        StartType->setObjectName("StartType");

        TopLayout->addWidget(StartType, 1, 1, 1, 1);

        labelStartReference = new Gui::ElideLabel(ProfileAndPlacementGroupBox);
        labelStartReference->setObjectName("labelStartReference");
        labelStartReference->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        TopLayout->addWidget(labelStartReference, 2, 0, 2, 1);

        lineStartReference = new QLineEdit(ProfileAndPlacementGroupBox);
        lineStartReference->setObjectName("lineStartReference");
        lineStartReference->setReadOnly(true);

        TopLayout->addWidget(lineStartReference, 2, 1, 1, 1);

        buttonStartReference = new QPushButton(ProfileAndPlacementGroupBox);
        buttonStartReference->setObjectName("buttonStartReference");
        buttonStartReference->setCheckable(true);

        TopLayout->addWidget(buttonStartReference, 3, 1, 1, 1);

        labelStartOffset = new Gui::ElideLabel(ProfileAndPlacementGroupBox);
        labelStartOffset->setObjectName("labelStartOffset");

        TopLayout->addWidget(labelStartOffset, 4, 0, 1, 1);

        StartOffset = new Gui::PrefQuantitySpinBox(ProfileAndPlacementGroupBox);
        StartOffset->setObjectName("StartOffset");
        StartOffset->setKeyboardTracking(false);
        StartOffset->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        TopLayout->addWidget(StartOffset, 4, 1, 1, 1);

        TopLayout->setColumnStretch(0, 2);
        TopLayout->setColumnStretch(1, 2);

        profileAndPlacementLayout->addLayout(TopLayout);


        verticalLayout_2->addWidget(ProfileAndPlacementGroupBox);

        HoleGroupBox = new QGroupBox(TaskHoleParameters);
        HoleGroupBox->setObjectName("HoleGroupBox");
        HoleGroupBox->setFlat(true);
        holeLayout = new QVBoxLayout(HoleGroupBox);
        holeLayout->setObjectName("holeLayout");
        holeTopLayout = new QGridLayout();
        holeTopLayout->setObjectName("holeTopLayout");
        labelThreadType = new Gui::ElideLabel(HoleGroupBox);
        labelThreadType->setObjectName("labelThreadType");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelThreadType->sizePolicy().hasHeightForWidth());
        labelThreadType->setSizePolicy(sizePolicy1);

        holeTopLayout->addWidget(labelThreadType, 0, 0, 1, 1);

        ThreadType = new QComboBox(HoleGroupBox);
        ThreadType->setObjectName("ThreadType");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ThreadType->sizePolicy().hasHeightForWidth());
        ThreadType->setSizePolicy(sizePolicy2);

        holeTopLayout->addWidget(ThreadType, 0, 1, 1, 1);

        labelSize = new Gui::ElideLabel(HoleGroupBox);
        labelSize->setObjectName("labelSize");
        sizePolicy1.setHeightForWidth(labelSize->sizePolicy().hasHeightForWidth());
        labelSize->setSizePolicy(sizePolicy1);

        holeTopLayout->addWidget(labelSize, 1, 0, 1, 1);

        ThreadSize = new QComboBox(HoleGroupBox);
        ThreadSize->setObjectName("ThreadSize");
        sizePolicy2.setHeightForWidth(ThreadSize->sizePolicy().hasHeightForWidth());
        ThreadSize->setSizePolicy(sizePolicy2);

        holeTopLayout->addWidget(ThreadSize, 1, 1, 1, 1);

        labelHeadType = new Gui::ElideLabel(HoleGroupBox);
        labelHeadType->setObjectName("labelHeadType");
        sizePolicy1.setHeightForWidth(labelHeadType->sizePolicy().hasHeightForWidth());
        labelHeadType->setSizePolicy(sizePolicy1);
        labelHeadType->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        holeTopLayout->addWidget(labelHeadType, 2, 0, 1, 1);

        HoleCutType = new QComboBox(HoleGroupBox);
        HoleCutType->setObjectName("HoleCutType");
        sizePolicy2.setHeightForWidth(HoleCutType->sizePolicy().hasHeightForWidth());
        HoleCutType->setSizePolicy(sizePolicy2);

        holeTopLayout->addWidget(HoleCutType, 2, 1, 1, 1);

        labelDepthType = new Gui::ElideLabel(HoleGroupBox);
        labelDepthType->setObjectName("labelDepthType");
        sizePolicy1.setHeightForWidth(labelDepthType->sizePolicy().hasHeightForWidth());
        labelDepthType->setSizePolicy(sizePolicy1);
        labelDepthType->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        holeTopLayout->addWidget(labelDepthType, 3, 0, 1, 1);

        DepthType = new QComboBox(HoleGroupBox);
        DepthType->addItem(QString());
        DepthType->addItem(QString());
        DepthType->setObjectName("DepthType");
        sizePolicy2.setHeightForWidth(DepthType->sizePolicy().hasHeightForWidth());
        DepthType->setSizePolicy(sizePolicy2);
        DepthType->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        holeTopLayout->addWidget(DepthType, 3, 1, 1, 1);

        holeTopLayout->setColumnStretch(0, 2);
        holeTopLayout->setColumnStretch(1, 2);

        holeLayout->addLayout(holeTopLayout);

        HoleCutCustomValues = new Gui::ElideCheckBox(HoleGroupBox);
        HoleCutCustomValues->setObjectName("HoleCutCustomValues");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(HoleCutCustomValues->sizePolicy().hasHeightForWidth());
        HoleCutCustomValues->setSizePolicy(sizePolicy3);
        HoleCutCustomValues->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        holeLayout->addWidget(HoleCutCustomValues);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(14);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, 0, -1, 0);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(3);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(-1, -1, -1, 3);
        labelHoleCutDiameter = new Gui::ElideLabel(HoleGroupBox);
        labelHoleCutDiameter->setObjectName("labelHoleCutDiameter");
        sizePolicy2.setHeightForWidth(labelHoleCutDiameter->sizePolicy().hasHeightForWidth());
        labelHoleCutDiameter->setSizePolicy(sizePolicy2);

        verticalLayout_13->addWidget(labelHoleCutDiameter);

        HoleCutDiameter = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        HoleCutDiameter->setObjectName("HoleCutDiameter");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(HoleCutDiameter->sizePolicy().hasHeightForWidth());
        HoleCutDiameter->setSizePolicy(sizePolicy4);
        HoleCutDiameter->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);
        HoleCutDiameter->setKeyboardTracking(false);
        HoleCutDiameter->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        HoleCutDiameter->setProperty("minimum", QVariant(0.000000000000000));
        HoleCutDiameter->setProperty("singleStep", QVariant(0.100000000000000));

        verticalLayout_13->addWidget(HoleCutDiameter);


        verticalLayout_4->addLayout(verticalLayout_13);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(3);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(-1, -1, -1, 3);
        labelHoleCutDepth = new Gui::ElideLabel(HoleGroupBox);
        labelHoleCutDepth->setObjectName("labelHoleCutDepth");
        sizePolicy2.setHeightForWidth(labelHoleCutDepth->sizePolicy().hasHeightForWidth());
        labelHoleCutDepth->setSizePolicy(sizePolicy2);

        verticalLayout_12->addWidget(labelHoleCutDepth);

        HoleCutDepth = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        HoleCutDepth->setObjectName("HoleCutDepth");
        sizePolicy4.setHeightForWidth(HoleCutDepth->sizePolicy().hasHeightForWidth());
        HoleCutDepth->setSizePolicy(sizePolicy4);
        HoleCutDepth->setKeyboardTracking(false);
        HoleCutDepth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        HoleCutDepth->setProperty("minimum", QVariant(0.000000000000000));
        HoleCutDepth->setProperty("singleStep", QVariant(0.100000000000000));

        verticalLayout_12->addWidget(HoleCutDepth);


        verticalLayout_4->addLayout(verticalLayout_12);

        DrillFrame = new QFrame(HoleGroupBox);
        DrillFrame->setObjectName("DrillFrame");
        DrillFrame->setEnabled(true);
        sizePolicy.setHeightForWidth(DrillFrame->sizePolicy().hasHeightForWidth());
        DrillFrame->setSizePolicy(sizePolicy);
        DrillFrame->setStyleSheet(QString::fromUtf8("QFrame {background-color: none; border-width: 0px;}"));
        DrillFrame->setLineWidth(0);
        verticalLayout_5 = new QVBoxLayout(DrillFrame);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 6, 0, 0);
        DrillPointAngled = new Gui::ElideCheckBox(DrillFrame);
        DrillPointAngled->setObjectName("DrillPointAngled");
        sizePolicy2.setHeightForWidth(DrillPointAngled->sizePolicy().hasHeightForWidth());
        DrillPointAngled->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(DrillPointAngled);

        DrillPointAngle = new Gui::PrefQuantitySpinBox(DrillFrame);
        DrillPointAngle->setObjectName("DrillPointAngle");
        sizePolicy4.setHeightForWidth(DrillPointAngle->sizePolicy().hasHeightForWidth());
        DrillPointAngle->setSizePolicy(sizePolicy4);
        DrillPointAngle->setKeyboardTracking(false);
        DrillPointAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        DrillPointAngle->setProperty("minimum", QVariant(0.000000000000000));

        verticalLayout_5->addWidget(DrillPointAngle);

        DrillForDepth = new Gui::ElideCheckBox(DrillFrame);
        DrillForDepth->setObjectName("DrillForDepth");
        sizePolicy2.setHeightForWidth(DrillForDepth->sizePolicy().hasHeightForWidth());
        DrillForDepth->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(DrillForDepth);


        verticalLayout_4->addWidget(DrillFrame);


        horizontalLayout->addLayout(verticalLayout_4);

        cutDiagram = new Gui::FontScaledSVG(HoleGroupBox);
        cutDiagram->setObjectName("cutDiagram");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(cutDiagram->sizePolicy().hasHeightForWidth());
        cutDiagram->setSizePolicy(sizePolicy5);
        cutDiagram->setMinimumSize(QSize(20, 40));
        cutDiagram->setBaseSize(QSize(0, 0));

        horizontalLayout->addWidget(cutDiagram);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(14);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(-1, 0, -1, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(3);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(-1, -1, -1, 3);
        labelHoleCutCountersinkAngle = new Gui::ElideLabel(HoleGroupBox);
        labelHoleCutCountersinkAngle->setObjectName("labelHoleCutCountersinkAngle");
        sizePolicy2.setHeightForWidth(labelHoleCutCountersinkAngle->sizePolicy().hasHeightForWidth());
        labelHoleCutCountersinkAngle->setSizePolicy(sizePolicy2);
        labelHoleCutCountersinkAngle->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_9->addWidget(labelHoleCutCountersinkAngle);

        HoleCutCountersinkAngle = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        HoleCutCountersinkAngle->setObjectName("HoleCutCountersinkAngle");
        sizePolicy4.setHeightForWidth(HoleCutCountersinkAngle->sizePolicy().hasHeightForWidth());
        HoleCutCountersinkAngle->setSizePolicy(sizePolicy4);
        HoleCutCountersinkAngle->setKeyboardTracking(false);
        HoleCutCountersinkAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        HoleCutCountersinkAngle->setProperty("minimum", QVariant(0.000000000000000));

        verticalLayout_9->addWidget(HoleCutCountersinkAngle);


        verticalLayout_6->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(-1, -1, -1, 3);
        labelDepth = new Gui::ElideLabel(HoleGroupBox);
        labelDepth->setObjectName("labelDepth");
        sizePolicy2.setHeightForWidth(labelDepth->sizePolicy().hasHeightForWidth());
        labelDepth->setSizePolicy(sizePolicy2);
        labelDepth->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_10->addWidget(labelDepth);

        Depth = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        Depth->setObjectName("Depth");
        sizePolicy4.setHeightForWidth(Depth->sizePolicy().hasHeightForWidth());
        Depth->setSizePolicy(sizePolicy4);
        Depth->setKeyboardTracking(false);
        Depth->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        verticalLayout_10->addWidget(Depth);


        verticalLayout_6->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(3);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(-1, 3, -1, 0);
        labelDiameter = new Gui::ElideLabel(HoleGroupBox);
        labelDiameter->setObjectName("labelDiameter");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(labelDiameter->sizePolicy().hasHeightForWidth());
        labelDiameter->setSizePolicy(sizePolicy6);
        labelDiameter->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_11->addWidget(labelDiameter);

        Diameter = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        Diameter->setObjectName("Diameter");
        sizePolicy4.setHeightForWidth(Diameter->sizePolicy().hasHeightForWidth());
        Diameter->setSizePolicy(sizePolicy4);
        Diameter->setBaseSize(QSize(0, 0));
        Diameter->setKeyboardTracking(false);
        Diameter->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        Diameter->setProperty("minimum", QVariant(0.000000000000000));

        verticalLayout_11->addWidget(Diameter);


        verticalLayout_6->addLayout(verticalLayout_11);


        horizontalLayout->addLayout(verticalLayout_6);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(-1, 0, -1, -1);
        Reversed = new Gui::ElideCheckBox(HoleGroupBox);
        Reversed->setObjectName("Reversed");
        sizePolicy3.setHeightForWidth(Reversed->sizePolicy().hasHeightForWidth());
        Reversed->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(Reversed);

        Tapered = new QCheckBox(HoleGroupBox);
        Tapered->setObjectName("Tapered");
        sizePolicy4.setHeightForWidth(Tapered->sizePolicy().hasHeightForWidth());
        Tapered->setSizePolicy(sizePolicy4);
        Tapered->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        horizontalLayout_7->addWidget(Tapered);

        TaperedAngle = new Gui::PrefQuantitySpinBox(HoleGroupBox);
        TaperedAngle->setObjectName("TaperedAngle");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(TaperedAngle->sizePolicy().hasHeightForWidth());
        TaperedAngle->setSizePolicy(sizePolicy7);
        TaperedAngle->setKeyboardTracking(false);
        TaperedAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        TaperedAngle->setProperty("minimum", QVariant(0.000000000000000));

        horizontalLayout_7->addWidget(TaperedAngle);


        verticalLayout_8->addLayout(horizontalLayout_7);


        holeLayout->addLayout(verticalLayout_8);

        profileLayout = new QGridLayout();
        profileLayout->setObjectName("profileLayout");
        profileLayout->setContentsMargins(-1, 0, -1, -1);
        HoleType = new QComboBox(HoleGroupBox);
        HoleType->addItem(QString());
        HoleType->addItem(QString());
        HoleType->addItem(QString());
        HoleType->setObjectName("HoleType");

        profileLayout->addWidget(HoleType, 0, 1, 1, 1);

        labelHoleType = new Gui::ElideLabel(HoleGroupBox);
        labelHoleType->setObjectName("labelHoleType");

        profileLayout->addWidget(labelHoleType, 0, 0, 1, 1);

        labelThreadClearance = new Gui::ElideLabel(HoleGroupBox);
        labelThreadClearance->setObjectName("labelThreadClearance");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(labelThreadClearance->sizePolicy().hasHeightForWidth());
        labelThreadClearance->setSizePolicy(sizePolicy8);

        profileLayout->addWidget(labelThreadClearance, 1, 0, 1, 1);

        ThreadFit = new QComboBox(HoleGroupBox);
        ThreadFit->addItem(QString());
        ThreadFit->addItem(QString());
        ThreadFit->addItem(QString());
        ThreadFit->setObjectName("ThreadFit");
        sizePolicy6.setHeightForWidth(ThreadFit->sizePolicy().hasHeightForWidth());
        ThreadFit->setSizePolicy(sizePolicy6);

        profileLayout->addWidget(ThreadFit, 1, 1, 1, 1);

        profileLayout->setColumnStretch(0, 2);
        profileLayout->setColumnStretch(1, 2);

        holeLayout->addLayout(profileLayout);

        ClearanceWidget = new QWidget(HoleGroupBox);
        ClearanceWidget->setObjectName("ClearanceWidget");
        sizePolicy6.setHeightForWidth(ClearanceWidget->sizePolicy().hasHeightForWidth());
        ClearanceWidget->setSizePolicy(sizePolicy6);
        horizontalLayout_6 = new QHBoxLayout(ClearanceWidget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);

        holeLayout->addWidget(ClearanceWidget);

        ThreadGroupBox = new QGroupBox(HoleGroupBox);
        ThreadGroupBox->setObjectName("ThreadGroupBox");
        sizePolicy8.setHeightForWidth(ThreadGroupBox->sizePolicy().hasHeightForWidth());
        ThreadGroupBox->setSizePolicy(sizePolicy8);
        ThreadGroupBox->setAutoFillBackground(false);
        ThreadGroupBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(ThreadGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        modelThreadLayout = new QHBoxLayout();
        modelThreadLayout->setObjectName("modelThreadLayout");
        modelThreadLayout->setContentsMargins(-1, -1, -1, 0);
        ModelThread = new Gui::ElideCheckBox(ThreadGroupBox);
        ModelThread->setObjectName("ModelThread");
        sizePolicy2.setHeightForWidth(ModelThread->sizePolicy().hasHeightForWidth());
        ModelThread->setSizePolicy(sizePolicy2);

        modelThreadLayout->addWidget(ModelThread);

        UpdateView = new Gui::ElideCheckBox(ThreadGroupBox);
        UpdateView->setObjectName("UpdateView");
        UpdateView->setEnabled(true);
        sizePolicy2.setHeightForWidth(UpdateView->sizePolicy().hasHeightForWidth());
        UpdateView->setSizePolicy(sizePolicy2);

        modelThreadLayout->addWidget(UpdateView);


        verticalLayout_3->addLayout(modelThreadLayout);

        classLayout = new QGridLayout();
        classLayout->setObjectName("classLayout");
        classLayout->setContentsMargins(-1, 0, -1, -1);
        ThreadClass = new QComboBox(ThreadGroupBox);
        ThreadClass->setObjectName("ThreadClass");
        sizePolicy2.setHeightForWidth(ThreadClass->sizePolicy().hasHeightForWidth());
        ThreadClass->setSizePolicy(sizePolicy2);

        classLayout->addWidget(ThreadClass, 0, 1, 1, 1);

        labelThreadClass = new Gui::ElideLabel(ThreadGroupBox);
        labelThreadClass->setObjectName("labelThreadClass");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(labelThreadClass->sizePolicy().hasHeightForWidth());
        labelThreadClass->setSizePolicy(sizePolicy9);

        classLayout->addWidget(labelThreadClass, 0, 0, 1, 1);

        classLayout->setColumnStretch(0, 2);
        classLayout->setColumnStretch(1, 5);

        verticalLayout_3->addLayout(classLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        labelThreadDirection = new QLabel(ThreadGroupBox);
        labelThreadDirection->setObjectName("labelThreadDirection");
        sizePolicy9.setHeightForWidth(labelThreadDirection->sizePolicy().hasHeightForWidth());
        labelThreadDirection->setSizePolicy(sizePolicy9);
        labelThreadDirection->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(labelThreadDirection);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        directionRightHand = new QRadioButton(ThreadGroupBox);
        directionButtonGroup = new QButtonGroup(TaskHoleParameters);
        directionButtonGroup->setObjectName("directionButtonGroup");
        directionButtonGroup->addButton(directionRightHand);
        directionRightHand->setObjectName("directionRightHand");
        sizePolicy2.setHeightForWidth(directionRightHand->sizePolicy().hasHeightForWidth());
        directionRightHand->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(directionRightHand);

        directionLeftHand = new QRadioButton(ThreadGroupBox);
        directionButtonGroup->addButton(directionLeftHand);
        directionLeftHand->setObjectName("directionLeftHand");
        sizePolicy2.setHeightForWidth(directionLeftHand->sizePolicy().hasHeightForWidth());
        directionLeftHand->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(directionLeftHand);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout);

        ThreadDepthWidget = new QWidget(ThreadGroupBox);
        ThreadDepthWidget->setObjectName("ThreadDepthWidget");
        sizePolicy8.setHeightForWidth(ThreadDepthWidget->sizePolicy().hasHeightForWidth());
        ThreadDepthWidget->setSizePolicy(sizePolicy8);
        verticalLayout_7 = new QVBoxLayout(ThreadDepthWidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        depthTypeLayout = new QHBoxLayout();
        depthTypeLayout->setSpacing(6);
        depthTypeLayout->setObjectName("depthTypeLayout");
        depthTypeLayout->setContentsMargins(-1, 0, -1, -1);
        labelThreadDepthType = new Gui::ElideLabel(ThreadDepthWidget);
        labelThreadDepthType->setObjectName("labelThreadDepthType");
        QSizePolicy sizePolicy10(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(labelThreadDepthType->sizePolicy().hasHeightForWidth());
        labelThreadDepthType->setSizePolicy(sizePolicy10);

        depthTypeLayout->addWidget(labelThreadDepthType);

        ThreadDepthType = new QComboBox(ThreadDepthWidget);
        ThreadDepthType->addItem(QString());
        ThreadDepthType->addItem(QString());
        ThreadDepthType->addItem(QString());
        ThreadDepthType->setObjectName("ThreadDepthType");
        sizePolicy2.setHeightForWidth(ThreadDepthType->sizePolicy().hasHeightForWidth());
        ThreadDepthType->setSizePolicy(sizePolicy2);

        depthTypeLayout->addWidget(ThreadDepthType);


        verticalLayout_7->addLayout(depthTypeLayout);

        ThreadDepthDimensionWidget = new QWidget(ThreadDepthWidget);
        ThreadDepthDimensionWidget->setObjectName("ThreadDepthDimensionWidget");
        horizontalLayout_3 = new QHBoxLayout(ThreadDepthDimensionWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelThreadDepth = new QLabel(ThreadDepthDimensionWidget);
        labelThreadDepth->setObjectName("labelThreadDepth");

        horizontalLayout_3->addWidget(labelThreadDepth);

        ThreadDepth = new Gui::PrefQuantitySpinBox(ThreadDepthDimensionWidget);
        ThreadDepth->setObjectName("ThreadDepth");
        sizePolicy6.setHeightForWidth(ThreadDepth->sizePolicy().hasHeightForWidth());
        ThreadDepth->setSizePolicy(sizePolicy6);
        ThreadDepth->setKeyboardTracking(false);
        ThreadDepth->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        horizontalLayout_3->addWidget(ThreadDepth);


        verticalLayout_7->addWidget(ThreadDepthDimensionWidget);


        verticalLayout_3->addWidget(ThreadDepthWidget);

        CustomClearanceWidget = new QWidget(ThreadGroupBox);
        CustomClearanceWidget->setObjectName("CustomClearanceWidget");
        horizontalLayout_13 = new QHBoxLayout(CustomClearanceWidget);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        UseCustomThreadClearance = new Gui::ElideCheckBox(CustomClearanceWidget);
        UseCustomThreadClearance->setObjectName("UseCustomThreadClearance");
        sizePolicy2.setHeightForWidth(UseCustomThreadClearance->sizePolicy().hasHeightForWidth());
        UseCustomThreadClearance->setSizePolicy(sizePolicy2);
        UseCustomThreadClearance->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        horizontalLayout_13->addWidget(UseCustomThreadClearance);

        CustomThreadClearance = new Gui::PrefQuantitySpinBox(CustomClearanceWidget);
        CustomThreadClearance->setObjectName("CustomThreadClearance");
        sizePolicy4.setHeightForWidth(CustomThreadClearance->sizePolicy().hasHeightForWidth());
        CustomThreadClearance->setSizePolicy(sizePolicy4);
        CustomThreadClearance->setKeyboardTracking(false);
        CustomThreadClearance->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        CustomThreadClearance->setProperty("singleStep", QVariant(0.100000000000000));

        horizontalLayout_13->addWidget(CustomThreadClearance);


        verticalLayout_3->addWidget(CustomClearanceWidget);


        holeLayout->addWidget(ThreadGroupBox);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(HoleGroupBox);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(HoleGroupBox);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);

        operationLayout->setStretch(0, 1);
        operationLayout->setStretch(1, 1);

        holeLayout->addLayout(operationLayout);


        verticalLayout_2->addWidget(HoleGroupBox);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)

        retranslateUi(TaskHoleParameters);

        QMetaObject::connectSlotsByName(TaskHoleParameters);
    } // setupUi

    void retranslateUi(QWidget *TaskHoleParameters)
    {
        TaskHoleParameters->setWindowTitle(QCoreApplication::translate("TaskHoleParameters", "Hole Parameters", nullptr));
        ProfileAndPlacementGroupBox->setTitle(QCoreApplication::translate("TaskHoleParameters", "Profile and Placement", nullptr));
        labelProfileType->setText(QCoreApplication::translate("TaskHoleParameters", "Base profile types", nullptr));
        BaseProfileType->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Circles and arcs", nullptr));
        BaseProfileType->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Points, circles and arcs", nullptr));
        BaseProfileType->setItemText(2, QCoreApplication::translate("TaskHoleParameters", "Points", nullptr));

        labelStart->setText(QCoreApplication::translate("TaskHoleParameters", "Start", nullptr));
        StartType->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Profile plane", nullptr));
        StartType->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Offset", nullptr));
        StartType->setItemText(2, QCoreApplication::translate("TaskHoleParameters", "Reference", nullptr));

        labelStartReference->setText(QCoreApplication::translate("TaskHoleParameters", "Reference", nullptr));
        buttonStartReference->setText(QCoreApplication::translate("TaskHoleParameters", "Pick Reference", nullptr));
        labelStartOffset->setText(QCoreApplication::translate("TaskHoleParameters", "Offset", nullptr));
        HoleGroupBox->setTitle(QCoreApplication::translate("TaskHoleParameters", "Hole", nullptr));
        labelThreadType->setText(QCoreApplication::translate("TaskHoleParameters", "Standard", nullptr));
        labelSize->setText(QCoreApplication::translate("TaskHoleParameters", "Size", nullptr));
        labelHeadType->setText(QCoreApplication::translate("TaskHoleParameters", "Head type", nullptr));
#if QT_CONFIG(tooltip)
        HoleCutType->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Cut type for screw heads", nullptr));
#endif // QT_CONFIG(tooltip)
        labelDepthType->setText(QCoreApplication::translate("TaskHoleParameters", "Depth type", nullptr));
        DepthType->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Dimension", nullptr));
        DepthType->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Through all", nullptr));

#if QT_CONFIG(tooltip)
        HoleCutCustomValues->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Check to override the values predefined by the 'Type'", nullptr));
#endif // QT_CONFIG(tooltip)
        HoleCutCustomValues->setText(QCoreApplication::translate("TaskHoleParameters", "Custom head values", nullptr));
        labelHoleCutDiameter->setText(QCoreApplication::translate("TaskHoleParameters", "Head diameter", nullptr));
        labelHoleCutDepth->setText(QCoreApplication::translate("TaskHoleParameters", "Head depth", nullptr));
#if QT_CONFIG(tooltip)
        HoleCutDepth->setToolTip(QCoreApplication::translate("TaskHoleParameters", "For countersinks this is the depth of\n"
"the screw's top below the surface", nullptr));
#endif // QT_CONFIG(tooltip)
        DrillPointAngled->setText(QCoreApplication::translate("TaskHoleParameters", "Drill angle", nullptr));
#if QT_CONFIG(tooltip)
        DrillForDepth->setToolTip(QCoreApplication::translate("TaskHoleParameters", "The size of the drill point will be taken into\n"
"account for the depth of blind holes", nullptr));
#endif // QT_CONFIG(tooltip)
        DrillForDepth->setText(QCoreApplication::translate("TaskHoleParameters", "Include in depth", nullptr));
        labelHoleCutCountersinkAngle->setText(QCoreApplication::translate("TaskHoleParameters", "Countersink angle", nullptr));
        labelDepth->setText(QCoreApplication::translate("TaskHoleParameters", "Depth", nullptr));
        labelDiameter->setText(QCoreApplication::translate("TaskHoleParameters", "Diameter", nullptr));
#if QT_CONFIG(tooltip)
        Diameter->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Hole diameter", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        Reversed->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Reverses the hole direction", nullptr));
#endif // QT_CONFIG(tooltip)
        Reversed->setText(QCoreApplication::translate("TaskHoleParameters", "Switch direction", nullptr));
        Tapered->setText(QCoreApplication::translate("TaskHoleParameters", "Tapered", nullptr));
#if QT_CONFIG(tooltip)
        TaperedAngle->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Taper angle for the hole\n"
"90 degree: straight hole\n"
"under 90: smaller hole radius at the bottom\n"
"over 90: larger hole radius at the bottom", nullptr));
#endif // QT_CONFIG(tooltip)
        HoleType->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Clearance / Passthrough", nullptr));
        HoleType->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Tap drill", nullptr));
        HoleType->setItemText(2, QCoreApplication::translate("TaskHoleParameters", "Threaded", nullptr));

        labelHoleType->setText(QCoreApplication::translate("TaskHoleParameters", "Hole type", nullptr));
        labelThreadClearance->setText(QCoreApplication::translate("TaskHoleParameters", "Clearance", nullptr));
        ThreadFit->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Standard", nullptr));
        ThreadFit->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Close", nullptr));
        ThreadFit->setItemText(2, QCoreApplication::translate("TaskHoleParameters", "Wide", nullptr));

#if QT_CONFIG(tooltip)
        ThreadFit->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Hole clearance\n"
"Only available for holes without thread", nullptr));
#endif // QT_CONFIG(tooltip)
        ThreadGroupBox->setTitle(QCoreApplication::translate("TaskHoleParameters", "Thread", nullptr));
#if QT_CONFIG(tooltip)
        ModelThread->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Whether the hole gets a modelled thread", nullptr));
#endif // QT_CONFIG(tooltip)
        ModelThread->setText(QCoreApplication::translate("TaskHoleParameters", "Model Thread", nullptr));
#if QT_CONFIG(tooltip)
        UpdateView->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Live update of changes to the thread\n"
"Note that the calculation can take some time", nullptr));
#endif // QT_CONFIG(tooltip)
        UpdateView->setText(QCoreApplication::translate("TaskHoleParameters", "Update thread view", nullptr));
#if QT_CONFIG(tooltip)
        ThreadClass->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Tolerance class for threaded holes according to hole profile", nullptr));
#endif // QT_CONFIG(tooltip)
        labelThreadClass->setText(QCoreApplication::translate("TaskHoleParameters", "Class", nullptr));
        labelThreadDirection->setText(QCoreApplication::translate("TaskHoleParameters", "Direction", nullptr));
#if QT_CONFIG(tooltip)
        directionRightHand->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        directionRightHand->setText(QCoreApplication::translate("TaskHoleParameters", "&Right hand", nullptr));
        directionLeftHand->setText(QCoreApplication::translate("TaskHoleParameters", "&Left hand", nullptr));
        labelThreadDepthType->setText(QCoreApplication::translate("TaskHoleParameters", "Thread Depth Type", nullptr));
        ThreadDepthType->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Hole depth", nullptr));
        ThreadDepthType->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Dimension", nullptr));
        ThreadDepthType->setItemText(2, QCoreApplication::translate("TaskHoleParameters", "Tapped (DIN76)", nullptr));

        labelThreadDepth->setText(QCoreApplication::translate("TaskHoleParameters", "Thread Depth", nullptr));
#if QT_CONFIG(tooltip)
        UseCustomThreadClearance->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Customize thread clearance", nullptr));
#endif // QT_CONFIG(tooltip)
        UseCustomThreadClearance->setText(QCoreApplication::translate("TaskHoleParameters", "Custom Clearance", nullptr));
#if QT_CONFIG(tooltip)
        CustomThreadClearance->setToolTip(QCoreApplication::translate("TaskHoleParameters", "Custom Thread clearance value", nullptr));
#endif // QT_CONFIG(tooltip)
        labelOperation->setText(QCoreApplication::translate("TaskHoleParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("TaskHoleParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("TaskHoleParameters", "Common", nullptr));

    } // retranslateUi

};

namespace Ui {
    class TaskHoleParameters: public Ui_TaskHoleParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKHOLEPARAMETERS_H
