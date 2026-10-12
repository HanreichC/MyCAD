/********************************************************************************
** Form generated from reading UI file 'SketcherSettingsAppearance.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERSETTINGSAPPEARANCE_H
#define UI_SKETCHERSETTINGSAPPEARANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace SketcherGui {

class Ui_SketcherSettingsAppearance
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout;
    QLabel *label_6;
    Gui::PrefColorButton *CreateLineColor;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    Gui::PrefColorButton *CursorTextColor;
    QLabel *label_19;
    Gui::PrefColorButton *CursorCrosshairColor;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_pattern;
    QLabel *label_width;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    Gui::PrefColorButton *FullyConstraintElementColor;
    Gui::PrefColorButton *EditedEdgeColor;
    QComboBox *EdgePattern;
    Gui::PrefSpinBox *EdgeWidth;
    QLabel *label_3;
    Gui::PrefColorButton *FullyConstraintConstructionElementColor;
    Gui::PrefColorButton *ConstructionColor;
    QComboBox *ConstructionPattern;
    Gui::PrefSpinBox *ConstructionWidth;
    QLabel *label_ia;
    Gui::PrefColorButton *FullyConstraintInternalAlignmentColor;
    Gui::PrefColorButton *InternalAlignedGeoColor;
    QComboBox *InternalPattern;
    Gui::PrefSpinBox *InternalWidth;
    QLabel *label_20;
    Gui::PrefColorButton *ExternalColor;
    QComboBox *ExternalPattern;
    Gui::PrefSpinBox *ExternalWidth;
    QLabel *label_21;
    Gui::PrefColorButton *ExternalDefiningColor;
    QComboBox *ExternalDefiningPattern;
    Gui::PrefSpinBox *ExternalDefiningWidth;
    QLabel *label_45;
    Gui::PrefColorButton *FullyConstrainedColor;
    QLabel *label_4;
    Gui::PrefColorButton *InvalidSketchColor;
    QLabel *label_31;
    Gui::PrefColorButton *InformationColor;
    QComboBox *InformationPattern;
    Gui::PrefSpinBox *InformationWidth;
    QLabel *labelGridLineColor;
    Gui::PrefColorButton *GridLineColor;
    QLabel *label_axislines;
    QComboBox *AxisLinePattern;
    Gui::PrefSpinBox *AxisLineWidth;
    QGroupBox *groupBoxSketcherColor;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *labelOtherItem;
    QLabel *labelOtherColor;
    QLabel *labelOtherSpacing;
    QLabel *labelOtherLinetype;
    QLabel *labelOtherWidth;
    QSpacerItem *horizontalSpacer_other;
    QLabel *dimensionalConstraintTitle;
    Gui::PrefColorButton *DatumColor;
    QComboBox *DimensionalConstraintLinePattern;
    Gui::PrefSpinBox *DimensionalConstraintLineWidth;
    QLabel *label_14;
    Gui::PrefColorButton *ConstrainedColor;
    QLabel *label_8;
    Gui::PrefColorButton *NonDrivingConstraintColor;
    QLabel *labelexpr;
    Gui::PrefColorButton *ExprBasedConstrDimColor;
    QLabel *labeldeact;
    Gui::PrefColorButton *DeactivatedConstrDimColor;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QLabel *label_18;
    Gui::PrefColorButton *SketchVertexColor;
    QSpacerItem *horizontalSpacer;
    QLabel *label_17;
    Gui::PrefColorButton *SketchEdgeColor;
    QLabel *label_10;
    Gui::PrefColorButton *InternalFaceColor;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SketcherGui__SketcherSettingsAppearance)
    {
        if (SketcherGui__SketcherSettingsAppearance->objectName().isEmpty())
            SketcherGui__SketcherSettingsAppearance->setObjectName("SketcherGui__SketcherSettingsAppearance");
        SketcherGui__SketcherSettingsAppearance->resize(689, 863);
        verticalLayout_2 = new QVBoxLayout(SketcherGui__SketcherSettingsAppearance);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(SketcherGui__SketcherSettingsAppearance);
        groupBox->setObjectName("groupBox");
        gridLayout_7 = new QGridLayout(groupBox);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        CreateLineColor = new Gui::PrefColorButton(groupBox);
        CreateLineColor->setObjectName("CreateLineColor");
        CreateLineColor->setProperty("color", QVariant(QColor(127, 127, 127)));
        CreateLineColor->setProperty("prefEntry", QVariant(QByteArray("CreateLineColor")));
        CreateLineColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(CreateLineColor, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        CursorTextColor = new Gui::PrefColorButton(groupBox);
        CursorTextColor->setObjectName("CursorTextColor");
        CursorTextColor->setProperty("color", QVariant(QColor(0, 0, 255)));
        CursorTextColor->setProperty("prefEntry", QVariant(QByteArray("CursorTextColor")));
        CursorTextColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(CursorTextColor, 4, 1, 1, 1);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName("label_19");

        gridLayout->addWidget(label_19, 5, 0, 1, 1);

        CursorCrosshairColor = new Gui::PrefColorButton(groupBox);
        CursorCrosshairColor->setObjectName("CursorCrosshairColor");
        CursorCrosshairColor->setProperty("color", QVariant(QColor(255, 255, 255)));
        CursorCrosshairColor->setProperty("prefEntry", QVariant(QByteArray("CursorCrosshairColor")));
        CursorCrosshairColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(CursorCrosshairColor, 5, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SketcherGui__SketcherSettingsAppearance);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName("gridLayout_6");
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(95, 0));

        gridLayout_6->addWidget(label_7, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(95, 0));

        gridLayout_6->addWidget(label_9, 1, 2, 1, 1);

        label_pattern = new QLabel(groupBox_2);
        label_pattern->setObjectName("label_pattern");

        gridLayout_6->addWidget(label_pattern, 1, 3, 1, 1);

        label_width = new QLabel(groupBox_2);
        label_width->setObjectName("label_width");

        gridLayout_6->addWidget(label_width, 1, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_6, 1, 5, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        gridLayout_6->addWidget(label, 5, 0, 1, 1);

        FullyConstraintElementColor = new Gui::PrefColorButton(groupBox_2);
        FullyConstraintElementColor->setObjectName("FullyConstraintElementColor");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FullyConstraintElementColor->sizePolicy().hasHeightForWidth());
        FullyConstraintElementColor->setSizePolicy(sizePolicy);
        FullyConstraintElementColor->setProperty("color", QVariant(QColor(128, 208, 160)));
        FullyConstraintElementColor->setProperty("prefEntry", QVariant(QByteArray("FullyConstraintElementColor")));
        FullyConstraintElementColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(FullyConstraintElementColor, 5, 1, 1, 1);

        EditedEdgeColor = new Gui::PrefColorButton(groupBox_2);
        EditedEdgeColor->setObjectName("EditedEdgeColor");
        sizePolicy.setHeightForWidth(EditedEdgeColor->sizePolicy().hasHeightForWidth());
        EditedEdgeColor->setSizePolicy(sizePolicy);
        EditedEdgeColor->setProperty("color", QVariant(QColor(255, 255, 255)));
        EditedEdgeColor->setProperty("prefEntry", QVariant(QByteArray("EditedEdgeColor")));
        EditedEdgeColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(EditedEdgeColor, 5, 2, 1, 1);

        EdgePattern = new QComboBox(groupBox_2);
        EdgePattern->setObjectName("EdgePattern");

        gridLayout_6->addWidget(EdgePattern, 5, 3, 1, 1);

        EdgeWidth = new Gui::PrefSpinBox(groupBox_2);
        EdgeWidth->setObjectName("EdgeWidth");
        EdgeWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        EdgeWidth->setSuffix(QString::fromUtf8(" px"));
        EdgeWidth->setMinimum(1);
        EdgeWidth->setMaximum(99);
        EdgeWidth->setValue(2);
        EdgeWidth->setProperty("prefEntry", QVariant(QByteArray("EdgeWidth")));
        EdgeWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(EdgeWidth, 5, 4, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout_6->addWidget(label_3, 7, 0, 1, 1);

        FullyConstraintConstructionElementColor = new Gui::PrefColorButton(groupBox_2);
        FullyConstraintConstructionElementColor->setObjectName("FullyConstraintConstructionElementColor");
        sizePolicy.setHeightForWidth(FullyConstraintConstructionElementColor->sizePolicy().hasHeightForWidth());
        FullyConstraintConstructionElementColor->setSizePolicy(sizePolicy);
        FullyConstraintConstructionElementColor->setProperty("color", QVariant(QColor(143, 169, 253)));
        FullyConstraintConstructionElementColor->setProperty("prefEntry", QVariant(QByteArray("FullyConstraintConstructionElementColor")));
        FullyConstraintConstructionElementColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(FullyConstraintConstructionElementColor, 7, 1, 1, 1);

        ConstructionColor = new Gui::PrefColorButton(groupBox_2);
        ConstructionColor->setObjectName("ConstructionColor");
        sizePolicy.setHeightForWidth(ConstructionColor->sizePolicy().hasHeightForWidth());
        ConstructionColor->setSizePolicy(sizePolicy);
        ConstructionColor->setProperty("color", QVariant(QColor(0, 0, 220)));
        ConstructionColor->setProperty("prefEntry", QVariant(QByteArray("ConstructionColor")));
        ConstructionColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(ConstructionColor, 7, 2, 1, 1);

        ConstructionPattern = new QComboBox(groupBox_2);
        ConstructionPattern->setObjectName("ConstructionPattern");

        gridLayout_6->addWidget(ConstructionPattern, 7, 3, 1, 1);

        ConstructionWidth = new Gui::PrefSpinBox(groupBox_2);
        ConstructionWidth->setObjectName("ConstructionWidth");
        ConstructionWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        ConstructionWidth->setSuffix(QString::fromUtf8(" px"));
        ConstructionWidth->setMinimum(1);
        ConstructionWidth->setMaximum(99);
        ConstructionWidth->setValue(2);
        ConstructionWidth->setProperty("prefEntry", QVariant(QByteArray("ConstructionWidth")));
        ConstructionWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(ConstructionWidth, 7, 4, 1, 1);

        label_ia = new QLabel(groupBox_2);
        label_ia->setObjectName("label_ia");

        gridLayout_6->addWidget(label_ia, 8, 0, 1, 1);

        FullyConstraintInternalAlignmentColor = new Gui::PrefColorButton(groupBox_2);
        FullyConstraintInternalAlignmentColor->setObjectName("FullyConstraintInternalAlignmentColor");
        sizePolicy.setHeightForWidth(FullyConstraintInternalAlignmentColor->sizePolicy().hasHeightForWidth());
        FullyConstraintInternalAlignmentColor->setSizePolicy(sizePolicy);
        FullyConstraintInternalAlignmentColor->setProperty("color", QVariant(QColor(222, 222, 200)));
        FullyConstraintInternalAlignmentColor->setProperty("prefEntry", QVariant(QByteArray("FullyConstraintInternalAlignmentColor")));
        FullyConstraintInternalAlignmentColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(FullyConstraintInternalAlignmentColor, 8, 1, 1, 1);

        InternalAlignedGeoColor = new Gui::PrefColorButton(groupBox_2);
        InternalAlignedGeoColor->setObjectName("InternalAlignedGeoColor");
        sizePolicy.setHeightForWidth(InternalAlignedGeoColor->sizePolicy().hasHeightForWidth());
        InternalAlignedGeoColor->setSizePolicy(sizePolicy);
        InternalAlignedGeoColor->setProperty("color", QVariant(QColor(178, 178, 127)));
        InternalAlignedGeoColor->setProperty("prefEntry", QVariant(QByteArray("InternalAlignedGeoColor")));
        InternalAlignedGeoColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(InternalAlignedGeoColor, 8, 2, 1, 1);

        InternalPattern = new QComboBox(groupBox_2);
        InternalPattern->setObjectName("InternalPattern");

        gridLayout_6->addWidget(InternalPattern, 8, 3, 1, 1);

        InternalWidth = new Gui::PrefSpinBox(groupBox_2);
        InternalWidth->setObjectName("InternalWidth");
        InternalWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        InternalWidth->setSuffix(QString::fromUtf8(" px"));
        InternalWidth->setMinimum(1);
        InternalWidth->setMaximum(99);
        InternalWidth->setValue(2);
        InternalWidth->setProperty("prefEntry", QVariant(QByteArray("InternalWidth")));
        InternalWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(InternalWidth, 8, 4, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName("label_20");

        gridLayout_6->addWidget(label_20, 9, 0, 1, 1);

        ExternalColor = new Gui::PrefColorButton(groupBox_2);
        ExternalColor->setObjectName("ExternalColor");
        sizePolicy.setHeightForWidth(ExternalColor->sizePolicy().hasHeightForWidth());
        ExternalColor->setSizePolicy(sizePolicy);
        ExternalColor->setProperty("color", QVariant(QColor(204, 51, 115)));
        ExternalColor->setProperty("prefEntry", QVariant(QByteArray("ExternalColor")));
        ExternalColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(ExternalColor, 9, 1, 1, 1);

        ExternalPattern = new QComboBox(groupBox_2);
        ExternalPattern->setObjectName("ExternalPattern");

        gridLayout_6->addWidget(ExternalPattern, 9, 3, 1, 1);

        ExternalWidth = new Gui::PrefSpinBox(groupBox_2);
        ExternalWidth->setObjectName("ExternalWidth");
        ExternalWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        ExternalWidth->setSuffix(QString::fromUtf8(" px"));
        ExternalWidth->setMinimum(1);
        ExternalWidth->setMaximum(99);
        ExternalWidth->setValue(2);
        ExternalWidth->setProperty("prefEntry", QVariant(QByteArray("ExternalWidth")));
        ExternalWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(ExternalWidth, 9, 4, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName("label_21");

        gridLayout_6->addWidget(label_21, 10, 0, 1, 1);

        ExternalDefiningColor = new Gui::PrefColorButton(groupBox_2);
        ExternalDefiningColor->setObjectName("ExternalDefiningColor");
        sizePolicy.setHeightForWidth(ExternalDefiningColor->sizePolicy().hasHeightForWidth());
        ExternalDefiningColor->setSizePolicy(sizePolicy);
        ExternalDefiningColor->setProperty("color", QVariant(QColor(204, 51, 153)));
        ExternalDefiningColor->setProperty("prefEntry", QVariant(QByteArray("ExternalDefiningColor")));
        ExternalDefiningColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(ExternalDefiningColor, 10, 1, 1, 1);

        ExternalDefiningPattern = new QComboBox(groupBox_2);
        ExternalDefiningPattern->setObjectName("ExternalDefiningPattern");

        gridLayout_6->addWidget(ExternalDefiningPattern, 10, 3, 1, 1);

        ExternalDefiningWidth = new Gui::PrefSpinBox(groupBox_2);
        ExternalDefiningWidth->setObjectName("ExternalDefiningWidth");
        ExternalDefiningWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        ExternalDefiningWidth->setSuffix(QString::fromUtf8(" px"));
        ExternalDefiningWidth->setMinimum(1);
        ExternalDefiningWidth->setMaximum(99);
        ExternalDefiningWidth->setValue(2);
        ExternalDefiningWidth->setProperty("prefEntry", QVariant(QByteArray("ExternalDefiningWidth")));
        ExternalDefiningWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(ExternalDefiningWidth, 10, 4, 1, 1);

        label_45 = new QLabel(groupBox_2);
        label_45->setObjectName("label_45");
        label_45->setMinimumSize(QSize(200, 0));

        gridLayout_6->addWidget(label_45, 11, 0, 1, 1);

        FullyConstrainedColor = new Gui::PrefColorButton(groupBox_2);
        FullyConstrainedColor->setObjectName("FullyConstrainedColor");
        sizePolicy.setHeightForWidth(FullyConstrainedColor->sizePolicy().hasHeightForWidth());
        FullyConstrainedColor->setSizePolicy(sizePolicy);
        FullyConstrainedColor->setProperty("color", QVariant(QColor(0, 255, 0)));
        FullyConstrainedColor->setProperty("prefEntry", QVariant(QByteArray("FullyConstrainedColor")));
        FullyConstrainedColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(FullyConstrainedColor, 11, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 12, 0, 1, 1);

        InvalidSketchColor = new Gui::PrefColorButton(groupBox_2);
        InvalidSketchColor->setObjectName("InvalidSketchColor");
        sizePolicy.setHeightForWidth(InvalidSketchColor->sizePolicy().hasHeightForWidth());
        InvalidSketchColor->setSizePolicy(sizePolicy);
        InvalidSketchColor->setProperty("color", QVariant(QColor(255, 109, 0)));
        InvalidSketchColor->setProperty("prefEntry", QVariant(QByteArray("InvalidSketchColor")));
        InvalidSketchColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(InvalidSketchColor, 12, 1, 1, 1);

        label_31 = new QLabel(groupBox_2);
        label_31->setObjectName("label_31");

        gridLayout_6->addWidget(label_31, 14, 0, 1, 1);

        InformationColor = new Gui::PrefColorButton(groupBox_2);
        InformationColor->setObjectName("InformationColor");
        sizePolicy.setHeightForWidth(InformationColor->sizePolicy().hasHeightForWidth());
        InformationColor->setSizePolicy(sizePolicy);
        InformationColor->setProperty("color", QVariant(QColor(0, 255, 0)));
        InformationColor->setProperty("prefEntry", QVariant(QByteArray("InformationColor")));
        InformationColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(InformationColor, 14, 1, 1, 1);

        InformationPattern = new QComboBox(groupBox_2);
        InformationPattern->setObjectName("InformationPattern");

        gridLayout_6->addWidget(InformationPattern, 14, 3, 1, 1);

        InformationWidth = new Gui::PrefSpinBox(groupBox_2);
        InformationWidth->setObjectName("InformationWidth");
        InformationWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        InformationWidth->setSuffix(QString::fromUtf8(" px"));
        InformationWidth->setMinimum(1);
        InformationWidth->setMaximum(99);
        InformationWidth->setValue(1);
        InformationWidth->setProperty("prefEntry", QVariant(QByteArray("InformationWidth")));
        InformationWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(InformationWidth, 14, 4, 1, 1);

        labelGridLineColor = new QLabel(groupBox_2);
        labelGridLineColor->setObjectName("labelGridLineColor");

        gridLayout_6->addWidget(labelGridLineColor, 15, 0, 1, 1);

        GridLineColor = new Gui::PrefColorButton(groupBox_2);
        GridLineColor->setObjectName("GridLineColor");
        sizePolicy.setHeightForWidth(GridLineColor->sizePolicy().hasHeightForWidth());
        GridLineColor->setSizePolicy(sizePolicy);
        GridLineColor->setProperty("color", QVariant(QColor(178, 178, 178)));
        GridLineColor->setProperty("prefEntry", QVariant(QByteArray("GridLineColor")));
        GridLineColor->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayout_6->addWidget(GridLineColor, 15, 1, 1, 1);

        label_axislines = new QLabel(groupBox_2);
        label_axislines->setObjectName("label_axislines");

        gridLayout_6->addWidget(label_axislines, 16, 0, 1, 1);

        AxisLinePattern = new QComboBox(groupBox_2);
        AxisLinePattern->setObjectName("AxisLinePattern");

        gridLayout_6->addWidget(AxisLinePattern, 16, 3, 1, 1);

        AxisLineWidth = new Gui::PrefSpinBox(groupBox_2);
        AxisLineWidth->setObjectName("AxisLineWidth");
        AxisLineWidth->setSuffix(QString::fromUtf8(" px"));
        AxisLineWidth->setMinimum(1);
        AxisLineWidth->setMaximum(99);
        AxisLineWidth->setValue(2);
        AxisLineWidth->setProperty("prefEntry", QVariant(QByteArray("AxisLineWidth")));
        AxisLineWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_6->addWidget(AxisLineWidth, 16, 4, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBoxSketcherColor = new QGroupBox(SketcherGui__SketcherSettingsAppearance);
        groupBoxSketcherColor->setObjectName("groupBoxSketcherColor");
        horizontalLayout_2 = new QHBoxLayout(groupBoxSketcherColor);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        labelOtherItem = new QLabel(groupBoxSketcherColor);
        labelOtherItem->setObjectName("labelOtherItem");
        labelOtherItem->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(labelOtherItem, 1, 0, 1, 1);

        labelOtherColor = new QLabel(groupBoxSketcherColor);
        labelOtherColor->setObjectName("labelOtherColor");
        labelOtherColor->setMinimumSize(QSize(95, 0));

        gridLayout_2->addWidget(labelOtherColor, 1, 1, 1, 1);

        labelOtherSpacing = new QLabel(groupBoxSketcherColor);
        labelOtherSpacing->setObjectName("labelOtherSpacing");
        labelOtherSpacing->setMinimumSize(QSize(105, 0));

        gridLayout_2->addWidget(labelOtherSpacing, 1, 2, 1, 1);

        labelOtherLinetype = new QLabel(groupBoxSketcherColor);
        labelOtherLinetype->setObjectName("labelOtherLinetype");

        gridLayout_2->addWidget(labelOtherLinetype, 1, 3, 1, 1);

        labelOtherWidth = new QLabel(groupBoxSketcherColor);
        labelOtherWidth->setObjectName("labelOtherWidth");

        gridLayout_2->addWidget(labelOtherWidth, 1, 4, 1, 1);

        horizontalSpacer_other = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_other, 1, 5, 1, 1);

        dimensionalConstraintTitle = new QLabel(groupBoxSketcherColor);
        dimensionalConstraintTitle->setObjectName("dimensionalConstraintTitle");
        dimensionalConstraintTitle->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(dimensionalConstraintTitle, 5, 0, 1, 1);

        DatumColor = new Gui::PrefColorButton(groupBoxSketcherColor);
        DatumColor->setObjectName("DatumColor");
        DatumColor->setProperty("color", QVariant(QColor(255, 38, 0)));
        DatumColor->setProperty("prefEntry", QVariant(QByteArray("ConstrainedDimColor")));
        DatumColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(DatumColor, 5, 1, 1, 1);

        DimensionalConstraintLinePattern = new QComboBox(groupBoxSketcherColor);
        DimensionalConstraintLinePattern->setObjectName("DimensionalConstraintLinePattern");

        gridLayout_2->addWidget(DimensionalConstraintLinePattern, 5, 3, 1, 1);

        DimensionalConstraintLineWidth = new Gui::PrefSpinBox(groupBoxSketcherColor);
        DimensionalConstraintLineWidth->setObjectName("DimensionalConstraintLineWidth");
        DimensionalConstraintLineWidth->setProperty("unit", QVariant(QString::fromUtf8("px")));
        DimensionalConstraintLineWidth->setSuffix(QString::fromUtf8(" px"));
        DimensionalConstraintLineWidth->setMinimum(1);
        DimensionalConstraintLineWidth->setMaximum(4);
        DimensionalConstraintLineWidth->setValue(2);
        DimensionalConstraintLineWidth->setProperty("prefEntry", QVariant(QByteArray("DimensionalConstraintLineWidth")));
        DimensionalConstraintLineWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/View")));

        gridLayout_2->addWidget(DimensionalConstraintLineWidth, 5, 4, 1, 1);

        label_14 = new QLabel(groupBoxSketcherColor);
        label_14->setObjectName("label_14");
        label_14->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(label_14, 10, 0, 1, 1);

        ConstrainedColor = new Gui::PrefColorButton(groupBoxSketcherColor);
        ConstrainedColor->setObjectName("ConstrainedColor");
        ConstrainedColor->setProperty("color", QVariant(QColor(255, 38, 0)));
        ConstrainedColor->setProperty("prefEntry", QVariant(QByteArray("ConstrainedIcoColor")));
        ConstrainedColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(ConstrainedColor, 10, 1, 1, 1);

        label_8 = new QLabel(groupBoxSketcherColor);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 12, 0, 1, 1);

        NonDrivingConstraintColor = new Gui::PrefColorButton(groupBoxSketcherColor);
        NonDrivingConstraintColor->setObjectName("NonDrivingConstraintColor");
        NonDrivingConstraintColor->setProperty("color", QVariant(QColor(0, 38, 255)));
        NonDrivingConstraintColor->setProperty("prefEntry", QVariant(QByteArray("NonDrivingConstrDimColor")));
        NonDrivingConstraintColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(NonDrivingConstraintColor, 12, 1, 1, 1);

        labelexpr = new QLabel(groupBoxSketcherColor);
        labelexpr->setObjectName("labelexpr");

        gridLayout_2->addWidget(labelexpr, 13, 0, 1, 1);

        ExprBasedConstrDimColor = new Gui::PrefColorButton(groupBoxSketcherColor);
        ExprBasedConstrDimColor->setObjectName("ExprBasedConstrDimColor");
        ExprBasedConstrDimColor->setProperty("color", QVariant(QColor(255, 127, 38)));
        ExprBasedConstrDimColor->setProperty("prefEntry", QVariant(QByteArray("ExprBasedConstrDimColor")));
        ExprBasedConstrDimColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(ExprBasedConstrDimColor, 13, 1, 1, 1);

        labeldeact = new QLabel(groupBoxSketcherColor);
        labeldeact->setObjectName("labeldeact");

        gridLayout_2->addWidget(labeldeact, 14, 0, 1, 1);

        DeactivatedConstrDimColor = new Gui::PrefColorButton(groupBoxSketcherColor);
        DeactivatedConstrDimColor->setObjectName("DeactivatedConstrDimColor");
        DeactivatedConstrDimColor->setProperty("color", QVariant(QColor(127, 127, 127)));
        DeactivatedConstrDimColor->setProperty("prefEntry", QVariant(QByteArray("DeactivatedConstrDimColor")));
        DeactivatedConstrDimColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(DeactivatedConstrDimColor, 14, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(groupBoxSketcherColor);

        groupBox_3 = new QGroupBox(SketcherGui__SketcherSettingsAppearance);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName("gridLayout_4");
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName("label_18");

        gridLayout_4->addWidget(label_18, 0, 0, 1, 1);

        SketchVertexColor = new Gui::PrefColorButton(groupBox_3);
        SketchVertexColor->setObjectName("SketchVertexColor");
        SketchVertexColor->setProperty("color", QVariant(QColor(255, 255, 255)));
        SketchVertexColor->setProperty("prefEntry", QVariant(QByteArray("SketchVertexColor")));
        SketchVertexColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_4->addWidget(SketchVertexColor, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName("label_17");
        label_17->setMinimumSize(QSize(200, 0));

        gridLayout_4->addWidget(label_17, 1, 0, 1, 1);

        SketchEdgeColor = new Gui::PrefColorButton(groupBox_3);
        SketchEdgeColor->setObjectName("SketchEdgeColor");
        SketchEdgeColor->setProperty("color", QVariant(QColor(255, 255, 255)));
        SketchEdgeColor->setProperty("prefEntry", QVariant(QByteArray("SketchEdgeColor")));
        SketchEdgeColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_4->addWidget(SketchEdgeColor, 1, 1, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        gridLayout_4->addWidget(label_10, 2, 0, 1, 1);

        InternalFaceColor = new Gui::PrefColorButton(groupBox_3);
        InternalFaceColor->setObjectName("InternalFaceColor");
        sizePolicy.setHeightForWidth(InternalFaceColor->sizePolicy().hasHeightForWidth());
        InternalFaceColor->setSizePolicy(sizePolicy);
        InternalFaceColor->setProperty("color", QVariant(QColor(245, 159, 0, 64)));
        InternalFaceColor->setProperty("prefEntry", QVariant(QByteArray("SketchFaceColor")));
        InternalFaceColor->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayout_4->addWidget(InternalFaceColor, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

#if QT_CONFIG(shortcut)
        labelGridLineColor->setBuddy(GridLineColor);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SketcherGui__SketcherSettingsAppearance);

        EdgePattern->setCurrentIndex(-1);
        ConstructionPattern->setCurrentIndex(-1);
        InternalPattern->setCurrentIndex(-1);
        ExternalPattern->setCurrentIndex(-1);
        ExternalDefiningPattern->setCurrentIndex(-1);
        InformationPattern->setCurrentIndex(-1);
        AxisLinePattern->setCurrentIndex(-1);
        DimensionalConstraintLinePattern->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SketcherGui__SketcherSettingsAppearance);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__SketcherSettingsAppearance)
    {
        SketcherGui__SketcherSettingsAppearance->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Appearance", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Working Colors", nullptr));
        label_6->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Creating line", nullptr));
#if QT_CONFIG(tooltip)
        CreateLineColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color used while new sketch elements are created", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Coordinate text", nullptr));
#if QT_CONFIG(tooltip)
        CursorTextColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Text color of the coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        label_19->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Cursor crosshair", nullptr));
#if QT_CONFIG(tooltip)
        CursorCrosshairColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of the crosshair cursor", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_2->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Geometric Element Colors", nullptr));
        label_7->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Constrained", nullptr));
        label_9->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Unconstrained", nullptr));
        label_pattern->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line Type", nullptr));
        label_width->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width", nullptr));
        label->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Geometry", nullptr));
#if QT_CONFIG(tooltip)
        FullyConstraintElementColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of fully constrained normal geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        EditedEdgeColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of normal geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        EdgePattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of normal edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        EdgeWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of normal edges", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Construction geometry", nullptr));
#if QT_CONFIG(tooltip)
        FullyConstraintConstructionElementColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of fully constrained construction geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ConstructionColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of construction geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ConstructionPattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of construction edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ConstructionWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of construction edges", nullptr));
#endif // QT_CONFIG(tooltip)
        label_ia->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Internal alignment geometry", nullptr));
#if QT_CONFIG(tooltip)
        FullyConstraintInternalAlignmentColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of fully constrained internal alignment geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        InternalAlignedGeoColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of internal alignment geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        InternalPattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of internal aligned edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        InternalWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of internal aligned edges", nullptr));
#endif // QT_CONFIG(tooltip)
        label_20->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "External construction geometry", nullptr));
#if QT_CONFIG(tooltip)
        ExternalColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of external construction geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ExternalPattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of external construction edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ExternalWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of external construction edges", nullptr));
#endif // QT_CONFIG(tooltip)
        label_21->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "External defining geometry", nullptr));
#if QT_CONFIG(tooltip)
        ExternalDefiningColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of external defining geometry in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ExternalDefiningPattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of external defining edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ExternalDefiningWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of external defining edges", nullptr));
#endif // QT_CONFIG(tooltip)
        label_45->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Fully constrained sketch", nullptr));
#if QT_CONFIG(tooltip)
        FullyConstrainedColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of geometry indicating a fully constrained sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Invalid sketch", nullptr));
#if QT_CONFIG(tooltip)
        InvalidSketchColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of geometry indicating an invalid sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        label_31->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Information layer", nullptr));
#if QT_CONFIG(tooltip)
        InformationColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of arc and line helpers and also bspline polygon, comb...", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        InformationPattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of information edges", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        InformationWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of information edges", nullptr));
#endif // QT_CONFIG(tooltip)
        labelGridLineColor->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Grid and inactive helpers", nullptr));
#if QT_CONFIG(tooltip)
        GridLineColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of sketch grid lines and inactive helper lines", nullptr));
#endif // QT_CONFIG(tooltip)
        label_axislines->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Sketcher axes", nullptr));
#if QT_CONFIG(tooltip)
        AxisLinePattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of sketcher axes", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        AxisLineWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of the sketcher axes", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxSketcherColor->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Constraint Colors", nullptr));
        labelOtherItem->setText(QString());
        labelOtherColor->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color", nullptr));
        labelOtherSpacing->setText(QString());
        labelOtherLinetype->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line Type", nullptr));
        labelOtherWidth->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width", nullptr));
        dimensionalConstraintTitle->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Dimensional constraints", nullptr));
#if QT_CONFIG(tooltip)
        DatumColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of dimensional driving constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DimensionalConstraintLinePattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Line pattern of dimensional constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        DimensionalConstraintLineWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Width of dimensional constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        label_14->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Constraint symbols", nullptr));
#if QT_CONFIG(tooltip)
        ConstrainedColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of driving constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Reference constraints", nullptr));
#if QT_CONFIG(tooltip)
        NonDrivingConstraintColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of reference constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        labelexpr->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Expression dependent constraint", nullptr));
#if QT_CONFIG(tooltip)
        ExprBasedConstrDimColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of expression dependent constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        labeldeact->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Deactivated constraints", nullptr));
#if QT_CONFIG(tooltip)
        DeactivatedConstrDimColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of deactivated constraints in edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Colors Outside Sketcher", nullptr));
        label_18->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Vertex", nullptr));
#if QT_CONFIG(tooltip)
        SketchVertexColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of vertices outside edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        label_17->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Edge", nullptr));
#if QT_CONFIG(tooltip)
        SketchEdgeColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of edges outside edit mode", nullptr));
#endif // QT_CONFIG(tooltip)
        label_10->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Face", nullptr));
#if QT_CONFIG(tooltip)
        InternalFaceColor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsAppearance", "Color of internal faces formed by intersecting geometry or closed loops in the sketch", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherSettingsAppearance: public Ui_SketcherSettingsAppearance {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERSETTINGSAPPEARANCE_H
