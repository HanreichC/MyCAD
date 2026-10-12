/********************************************************************************
** Form generated from reading UI file 'SketcherSettingsDisplay.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERSETTINGSDISPLAY_H
#define UI_SKETCHERSETTINGSDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace SketcherGui {

class Ui_SketcherSettingsDisplay
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_1;
    QGridLayout *gridLayout_1;
    QLabel *label_5;
    Gui::PrefFontBox *fontBoxSketcherFontName;
    QLabel *label_0;
    Gui::PrefSpinBox *EditSketcherFontSize;
    QLabel *label_6;
    QLabel *LabelFontPreview;
    QLabel *LabelFontMessage;
    QLabel *label_ConstraintSymbolSize;
    Gui::PrefSpinBox *ConstraintSymbolSize;
    QLabel *label_1;
    Gui::PrefDoubleSpinBox *viewScalingFactor;
    QLabel *label_axisTransparency;
    Gui::PrefSpinBox *axisTransparency;
    QLabel *label_occludedAxisTransparency;
    Gui::PrefSpinBox *occludedAxisTransparency;
    QLabel *label_3;
    Gui::PrefSpinBox *SegmentsPerGeometry;
    Gui::PrefCheckBox *dialogOnDistanceConstraint;
    Gui::PrefCheckBox *continueMode;
    Gui::PrefCheckBox *constraintMode;
    Gui::PrefCheckBox *checkBoxHideUnits;
    Gui::PrefCheckBox *checkBoxShowCursorCoords;
    Gui::PrefCheckBox *checkBoxUseSystemDecimals;
    Gui::PrefCheckBox *checkBoxShowDimensionalName;
    Gui::PrefLineEdit *prefDimensionalStringFormat;
    Gui::PrefCheckBox *checkBoxShowDirectionalAutoConstraintHints;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    Gui::PrefCheckBox *checkBoxTVHideDependent;
    Gui::PrefCheckBox *checkBoxTVShowLinks;
    Gui::PrefCheckBox *checkBoxTVShowSupport;
    Gui::PrefCheckBox *checkBoxTVRestoreCamera;
    Gui::PrefCheckBox *checkBoxTVForceOrtho;
    Gui::PrefCheckBox *checkBoxTVSectionView;
    QLabel *label_4;
    QPushButton *btnTVApply;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SketcherGui__SketcherSettingsDisplay)
    {
        if (SketcherGui__SketcherSettingsDisplay->objectName().isEmpty())
            SketcherGui__SketcherSettingsDisplay->setObjectName("SketcherGui__SketcherSettingsDisplay");
        SketcherGui__SketcherSettingsDisplay->resize(500, 538);
        verticalLayout = new QVBoxLayout(SketcherGui__SketcherSettingsDisplay);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_1 = new QGroupBox(SketcherGui__SketcherSettingsDisplay);
        groupBox_1->setObjectName("groupBox_1");
        gridLayout_1 = new QGridLayout(groupBox_1);
        gridLayout_1->setObjectName("gridLayout_1");
        label_5 = new QLabel(groupBox_1);
        label_5->setObjectName("label_5");

        gridLayout_1->addWidget(label_5, 0, 0, 1, 1);

        fontBoxSketcherFontName = new Gui::PrefFontBox(groupBox_1);
        fontBoxSketcherFontName->setObjectName("fontBoxSketcherFontName");
        fontBoxSketcherFontName->setMinimumSize(QSize(250, 0));
        fontBoxSketcherFontName->setProperty("prefEntry", QVariant(QByteArray("EditSketcherFontName")));
        fontBoxSketcherFontName->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_1->addWidget(fontBoxSketcherFontName, 0, 1, 1, 1);

        label_0 = new QLabel(groupBox_1);
        label_0->setObjectName("label_0");
        label_0->setMinimumSize(QSize(182, 0));

        gridLayout_1->addWidget(label_0, 1, 0, 1, 1);

        EditSketcherFontSize = new Gui::PrefSpinBox(groupBox_1);
        EditSketcherFontSize->setObjectName("EditSketcherFontSize");
        EditSketcherFontSize->setMinimum(1);
        EditSketcherFontSize->setMaximum(100);
        EditSketcherFontSize->setValue(17);
        EditSketcherFontSize->setProperty("prefEntry", QVariant(QByteArray("EditSketcherFontSize")));
        EditSketcherFontSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_1->addWidget(EditSketcherFontSize, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_1);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignTop|Qt::AlignLeft|Qt::AlignLeading);

        gridLayout_1->addWidget(label_6, 2, 0, 1, 1);

        LabelFontPreview = new QLabel(groupBox_1);
        LabelFontPreview->setObjectName("LabelFontPreview");
        LabelFontPreview->setMinimumSize(QSize(0, 64));
        LabelFontPreview->setAlignment(Qt::AlignCenter);
        LabelFontPreview->setFrameShape(QFrame::Panel);
        LabelFontPreview->setFrameShadow(QFrame::Sunken);
        LabelFontPreview->setLineWidth(1);
        LabelFontPreview->setAutoFillBackground(true);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        LabelFontPreview->setPalette(palette);

        gridLayout_1->addWidget(LabelFontPreview, 2, 1, 2, 1);

        LabelFontMessage = new QLabel(groupBox_1);
        LabelFontMessage->setObjectName("LabelFontMessage");
        LabelFontMessage->setTextInteractionFlags(Qt::TextSelectableByMouse);
        LabelFontMessage->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);
        QFont font;
        font.setBold(true);
        LabelFontMessage->setFont(font);

        gridLayout_1->addWidget(LabelFontMessage, 3, 0, 1, 1);

        label_ConstraintSymbolSize = new QLabel(groupBox_1);
        label_ConstraintSymbolSize->setObjectName("label_ConstraintSymbolSize");

        gridLayout_1->addWidget(label_ConstraintSymbolSize, 4, 0, 1, 1);

        ConstraintSymbolSize = new Gui::PrefSpinBox(groupBox_1);
        ConstraintSymbolSize->setObjectName("ConstraintSymbolSize");
        ConstraintSymbolSize->setMinimum(6);
        ConstraintSymbolSize->setMaximum(96);
        ConstraintSymbolSize->setValue(15);
        ConstraintSymbolSize->setProperty("prefEntry", QVariant(QByteArray("ConstraintSymbolSize")));
        ConstraintSymbolSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_1->addWidget(ConstraintSymbolSize, 4, 1, 1, 1);

        label_1 = new QLabel(groupBox_1);
        label_1->setObjectName("label_1");
        label_1->setMinimumSize(QSize(182, 0));

        gridLayout_1->addWidget(label_1, 5, 0, 1, 1);

        viewScalingFactor = new Gui::PrefDoubleSpinBox(groupBox_1);
        viewScalingFactor->setObjectName("viewScalingFactor");
        viewScalingFactor->setInputMethodHints(Qt::ImhPreferNumbers);
        viewScalingFactor->setDecimals(2);
        viewScalingFactor->setMinimum(0.500000000000000);
        viewScalingFactor->setMaximum(5.000000000000000);
        viewScalingFactor->setSingleStep(0.050000000000000);
        viewScalingFactor->setValue(1.000000000000000);
        viewScalingFactor->setProperty("prefEntry", QVariant(QByteArray("ViewScalingFactor")));
        viewScalingFactor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_1->addWidget(viewScalingFactor, 5, 1, 1, 1);

        label_axisTransparency = new QLabel(groupBox_1);
        label_axisTransparency->setObjectName("label_axisTransparency");

        gridLayout_1->addWidget(label_axisTransparency, 6, 0, 1, 1);

        axisTransparency = new Gui::PrefSpinBox(groupBox_1);
        axisTransparency->setObjectName("axisTransparency");
        axisTransparency->setSuffix(QString::fromUtf8("%"));
        axisTransparency->setMinimum(0);
        axisTransparency->setMaximum(100);
        axisTransparency->setValue(30);
        axisTransparency->setSingleStep(10);
        axisTransparency->setProperty("prefEntry", QVariant(QByteArray("AxisTransparency")));
        axisTransparency->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayout_1->addWidget(axisTransparency, 6, 1, 1, 1);

        label_occludedAxisTransparency = new QLabel(groupBox_1);
        label_occludedAxisTransparency->setObjectName("label_occludedAxisTransparency");

        gridLayout_1->addWidget(label_occludedAxisTransparency, 7, 0, 1, 1);

        occludedAxisTransparency = new Gui::PrefSpinBox(groupBox_1);
        occludedAxisTransparency->setObjectName("occludedAxisTransparency");
        occludedAxisTransparency->setSuffix(QString::fromUtf8("%"));
        occludedAxisTransparency->setMinimum(0);
        occludedAxisTransparency->setMaximum(100);
        occludedAxisTransparency->setValue(90);
        occludedAxisTransparency->setSingleStep(10);
        occludedAxisTransparency->setProperty("prefEntry", QVariant(QByteArray("OccludedAxisTransparency")));
        occludedAxisTransparency->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayout_1->addWidget(occludedAxisTransparency, 7, 1, 1, 1);

        label_3 = new QLabel(groupBox_1);
        label_3->setObjectName("label_3");

        gridLayout_1->addWidget(label_3, 8, 0, 1, 1);

        SegmentsPerGeometry = new Gui::PrefSpinBox(groupBox_1);
        SegmentsPerGeometry->setObjectName("SegmentsPerGeometry");
        SegmentsPerGeometry->setMinimum(50);
        SegmentsPerGeometry->setMaximum(1000);
        SegmentsPerGeometry->setProperty("prefEntry", QVariant(QByteArray("SegmentsPerGeometry")));
        SegmentsPerGeometry->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_1->addWidget(SegmentsPerGeometry, 8, 1, 1, 1);

        dialogOnDistanceConstraint = new Gui::PrefCheckBox(groupBox_1);
        dialogOnDistanceConstraint->setObjectName("dialogOnDistanceConstraint");
        dialogOnDistanceConstraint->setChecked(true);
        dialogOnDistanceConstraint->setProperty("prefEntry", QVariant(QByteArray("ShowDialogOnDistanceConstraint")));
        dialogOnDistanceConstraint->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(dialogOnDistanceConstraint, 9, 0, 1, 2);

        continueMode = new Gui::PrefCheckBox(groupBox_1);
        continueMode->setObjectName("continueMode");
        continueMode->setChecked(true);
        continueMode->setProperty("prefEntry", QVariant(QByteArray("ContinuousCreationMode")));
        continueMode->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(continueMode, 10, 0, 1, 2);

        constraintMode = new Gui::PrefCheckBox(groupBox_1);
        constraintMode->setObjectName("constraintMode");
        constraintMode->setChecked(true);
        constraintMode->setProperty("prefEntry", QVariant(QByteArray("ContinuousConstraintMode")));
        constraintMode->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(constraintMode, 11, 0, 1, 2);

        checkBoxHideUnits = new Gui::PrefCheckBox(groupBox_1);
        checkBoxHideUnits->setObjectName("checkBoxHideUnits");
        checkBoxHideUnits->setProperty("prefEntry", QVariant(QByteArray("HideUnits")));
        checkBoxHideUnits->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(checkBoxHideUnits, 12, 0, 1, 2);

        checkBoxShowCursorCoords = new Gui::PrefCheckBox(groupBox_1);
        checkBoxShowCursorCoords->setObjectName("checkBoxShowCursorCoords");
        checkBoxShowCursorCoords->setChecked(true);
        checkBoxShowCursorCoords->setProperty("prefEntry", QVariant(QByteArray("ShowCursorCoords")));
        checkBoxShowCursorCoords->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(checkBoxShowCursorCoords, 13, 0, 1, 1);

        checkBoxUseSystemDecimals = new Gui::PrefCheckBox(groupBox_1);
        checkBoxUseSystemDecimals->setObjectName("checkBoxUseSystemDecimals");
        checkBoxUseSystemDecimals->setProperty("prefEntry", QVariant(QByteArray("UseSystemDecimals")));
        checkBoxUseSystemDecimals->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(checkBoxUseSystemDecimals, 14, 0, 1, 1);

        checkBoxShowDimensionalName = new Gui::PrefCheckBox(groupBox_1);
        checkBoxShowDimensionalName->setObjectName("checkBoxShowDimensionalName");
        checkBoxShowDimensionalName->setProperty("prefEntry", QVariant(QByteArray("ShowDimensionalName")));
        checkBoxShowDimensionalName->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));
        checkBoxShowDimensionalName->setChecked(true);

        gridLayout_1->addWidget(checkBoxShowDimensionalName, 15, 0, 1, 1);

        prefDimensionalStringFormat = new Gui::PrefLineEdit(groupBox_1);
        prefDimensionalStringFormat->setObjectName("prefDimensionalStringFormat");
        prefDimensionalStringFormat->setText(QString::fromUtf8("%N = %V"));
        prefDimensionalStringFormat->setProperty("prefEntry", QVariant(QByteArray("DimensionalStringFormat")));
        prefDimensionalStringFormat->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_1->addWidget(prefDimensionalStringFormat, 15, 1, 1, 1);

        checkBoxShowDirectionalAutoConstraintHints = new Gui::PrefCheckBox(groupBox_1);
        checkBoxShowDirectionalAutoConstraintHints->setObjectName("checkBoxShowDirectionalAutoConstraintHints");
        checkBoxShowDirectionalAutoConstraintHints->setChecked(true);
        checkBoxShowDirectionalAutoConstraintHints->setProperty("prefEntry", QVariant(QByteArray("ShowDirectionalAutoConstraintHints")));
        checkBoxShowDirectionalAutoConstraintHints->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayout_1->addWidget(checkBoxShowDirectionalAutoConstraintHints, 16, 0, 1, 2);


        verticalLayout->addWidget(groupBox_1);

        groupBox_2 = new QGroupBox(SketcherGui__SketcherSettingsDisplay);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        groupBox_2->setBaseSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        checkBoxTVHideDependent = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVHideDependent->setObjectName("checkBoxTVHideDependent");
        checkBoxTVHideDependent->setChecked(true);
        checkBoxTVHideDependent->setProperty("prefEntry", QVariant(QByteArray("HideDependent")));
        checkBoxTVHideDependent->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVHideDependent);

        checkBoxTVShowLinks = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVShowLinks->setObjectName("checkBoxTVShowLinks");
        checkBoxTVShowLinks->setChecked(true);
        checkBoxTVShowLinks->setProperty("prefEntry", QVariant(QByteArray("ShowLinks")));
        checkBoxTVShowLinks->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVShowLinks);

        checkBoxTVShowSupport = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVShowSupport->setObjectName("checkBoxTVShowSupport");
        checkBoxTVShowSupport->setChecked(true);
        checkBoxTVShowSupport->setProperty("prefEntry", QVariant(QByteArray("ShowSupport")));
        checkBoxTVShowSupport->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVShowSupport);

        checkBoxTVRestoreCamera = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVRestoreCamera->setObjectName("checkBoxTVRestoreCamera");
        checkBoxTVRestoreCamera->setChecked(true);
        checkBoxTVRestoreCamera->setProperty("prefEntry", QVariant(QByteArray("RestoreCamera")));
        checkBoxTVRestoreCamera->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVRestoreCamera);

        checkBoxTVForceOrtho = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVForceOrtho->setObjectName("checkBoxTVForceOrtho");
        checkBoxTVForceOrtho->setChecked(false);
        checkBoxTVForceOrtho->setProperty("prefEntry", QVariant(QByteArray("ForceOrtho")));
        checkBoxTVForceOrtho->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVForceOrtho);

        checkBoxTVSectionView = new Gui::PrefCheckBox(groupBox_2);
        checkBoxTVSectionView->setObjectName("checkBoxTVSectionView");
        checkBoxTVSectionView->setChecked(false);
        checkBoxTVSectionView->setProperty("prefEntry", QVariant(QByteArray("SectionView")));
        checkBoxTVSectionView->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_2->addWidget(checkBoxTVSectionView);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_4->setWordWrap(true);

        verticalLayout_2->addWidget(label_4);

        btnTVApply = new QPushButton(groupBox_2);
        btnTVApply->setObjectName("btnTVApply");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnTVApply->sizePolicy().hasHeightForWidth());
        btnTVApply->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(btnTVApply);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

#if QT_CONFIG(shortcut)
        label_0->setBuddy(EditSketcherFontSize);
        label_ConstraintSymbolSize->setBuddy(ConstraintSymbolSize);
        label_1->setBuddy(viewScalingFactor);
        label_axisTransparency->setBuddy(axisTransparency);
        label_occludedAxisTransparency->setBuddy(occludedAxisTransparency);
        label_3->setBuddy(SegmentsPerGeometry);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(fontBoxSketcherFontName, EditSketcherFontSize);
        QWidget::setTabOrder(EditSketcherFontSize, ConstraintSymbolSize);
        QWidget::setTabOrder(ConstraintSymbolSize, viewScalingFactor);
        QWidget::setTabOrder(viewScalingFactor, axisTransparency);
        QWidget::setTabOrder(axisTransparency, occludedAxisTransparency);
        QWidget::setTabOrder(occludedAxisTransparency, SegmentsPerGeometry);
        QWidget::setTabOrder(SegmentsPerGeometry, dialogOnDistanceConstraint);
        QWidget::setTabOrder(dialogOnDistanceConstraint, continueMode);
        QWidget::setTabOrder(continueMode, constraintMode);
        QWidget::setTabOrder(constraintMode, checkBoxHideUnits);
        QWidget::setTabOrder(checkBoxHideUnits, checkBoxShowCursorCoords);
        QWidget::setTabOrder(checkBoxShowCursorCoords, checkBoxUseSystemDecimals);
        QWidget::setTabOrder(checkBoxUseSystemDecimals, checkBoxShowDimensionalName);
        QWidget::setTabOrder(checkBoxShowDimensionalName, prefDimensionalStringFormat);
        QWidget::setTabOrder(prefDimensionalStringFormat, checkBoxShowDirectionalAutoConstraintHints);
        QWidget::setTabOrder(checkBoxShowDirectionalAutoConstraintHints, checkBoxTVHideDependent);
        QWidget::setTabOrder(checkBoxTVHideDependent, checkBoxTVShowLinks);
        QWidget::setTabOrder(checkBoxTVShowLinks, checkBoxTVShowSupport);
        QWidget::setTabOrder(checkBoxTVShowSupport, checkBoxTVRestoreCamera);
        QWidget::setTabOrder(checkBoxTVRestoreCamera, checkBoxTVForceOrtho);
        QWidget::setTabOrder(checkBoxTVForceOrtho, checkBoxTVSectionView);
        QWidget::setTabOrder(checkBoxTVSectionView, btnTVApply);

        retranslateUi(SketcherGui__SketcherSettingsDisplay);
        QObject::connect(checkBoxTVRestoreCamera, SIGNAL(toggled(bool)), checkBoxTVForceOrtho, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(SketcherGui__SketcherSettingsDisplay);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__SketcherSettingsDisplay)
    {
        SketcherGui__SketcherSettingsDisplay->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Display", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Sketch Editing", nullptr));
        label_5->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Font name", nullptr));
#if QT_CONFIG(tooltip)
        fontBoxSketcherFontName->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Font used for labels and constraints", nullptr));
#endif // QT_CONFIG(tooltip)
        label_0->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Font size", nullptr));
#if QT_CONFIG(tooltip)
        EditSketcherFontSize->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Font size used for labels and constraints", nullptr));
#endif // QT_CONFIG(tooltip)
        EditSketcherFontSize->setSuffix(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "px", nullptr));
        label_6->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Font preview", nullptr));
#if QT_CONFIG(tooltip)
        LabelFontPreview->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Preview of a constraint text when selected font family and size is used", nullptr));
#endif // QT_CONFIG(tooltip)
        LabelFontPreview->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "\342\214\200123.45 \302\265m (\306\222\360\235\221\245)", nullptr));
#if QT_CONFIG(tooltip)
        LabelFontMessage->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Because the selected font does not contain all characters Sketcher uses,\n"
"the characters listed here will be drawn using a substitute font.", nullptr));
#endif // QT_CONFIG(tooltip)
        LabelFontMessage->setText(QString());
        label_ConstraintSymbolSize->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Constraint symbol size", nullptr));
#if QT_CONFIG(tooltip)
        ConstraintSymbolSize->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Pixel size used to render constraint symbols", nullptr));
#endif // QT_CONFIG(tooltip)
        ConstraintSymbolSize->setSuffix(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "px", nullptr));
        label_1->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "View scale ratio", nullptr));
#if QT_CONFIG(tooltip)
        viewScalingFactor->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Scales the 3D view based on this factor", nullptr));
#endif // QT_CONFIG(tooltip)
        label_axisTransparency->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Axis transparency", nullptr));
#if QT_CONFIG(tooltip)
        axisTransparency->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Transparency of visible axes.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_occludedAxisTransparency->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Occluded axis transparency", nullptr));
#if QT_CONFIG(tooltip)
        occludedAxisTransparency->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Transparency of occluded axes.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Segments per geometry", nullptr));
#if QT_CONFIG(tooltip)
        SegmentsPerGeometry->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "The number of polygons used for geometry approximation", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        dialogOnDistanceConstraint->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Opens a dialog to input a value for new dimensional constraints after creation", nullptr));
#endif // QT_CONFIG(tooltip)
        dialogOnDistanceConstraint->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Ask for value after creating a dimensional constraint", nullptr));
#if QT_CONFIG(tooltip)
        continueMode->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Keeps the current Sketcher tool active after creating geometry", nullptr));
#endif // QT_CONFIG(tooltip)
        continueMode->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Geometry creation \"Continue Mode\"", nullptr));
#if QT_CONFIG(tooltip)
        constraintMode->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Keeps the current Sketcher constraint tool active after creating geometry", nullptr));
#endif // QT_CONFIG(tooltip)
        constraintMode->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Constraint creation \"Continue Mode\"", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxHideUnits->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Base length units will not be displayed in constraints or cursor coordinates.\n"
"Supports all unit systems except 'US customary' and 'Building US/Euro'.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxHideUnits->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Hide base length units for supported unit systems", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxShowCursorCoords->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Shows cursor position coordinates next to the cursor while editing a sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxShowCursorCoords->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Show coordinates next to the cursor while editing", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxUseSystemDecimals->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Cursor coordinates will use the system decimals setting instead of the short form", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxUseSystemDecimals->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Use system decimals setting for cursor coordinates", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxShowDimensionalName->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Shows names of dimensional constraints, if they exist", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxShowDimensionalName->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Show dimensional constraint name with format", nullptr));
#if QT_CONFIG(tooltip)
        prefDimensionalStringFormat->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "The format of the dimensional constraint string presentation.\n"
"Defaults to: %N = %V\n"
"\n"
"%N - name parameter\n"
"%V - dimension value", nullptr));
#endif // QT_CONFIG(tooltip)
        prefDimensionalStringFormat->setPlaceholderText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "%N = %V", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxShowDirectionalAutoConstraintHints->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Shows helper lines for directional autoconstraints such as parallel, perpendicular, and tangent", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxShowDirectionalAutoConstraintHints->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Show directional autoconstraint helpers", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Visibility Automation", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVHideDependent->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Hides all object features that depend on the opened sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVHideDependent->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Hide all objects that depend on the sketch", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVShowLinks->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Shows source objects which are used for external geometry in the opened sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVShowLinks->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Show objects used for external geometry", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVShowSupport->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Shows objects the opened sketch is attached to", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVShowSupport->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Show objects that the sketch is attached to", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVRestoreCamera->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Restores the camera position after closing the sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVRestoreCamera->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Restore camera position after editing", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVForceOrtho->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Forces the camera to an orthographic view when editing a sketch.\n"
"Works only when \"Restore camera position after editing\" is enabled.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVForceOrtho->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Force orthographic camera when entering edit", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTVSectionView->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Opens a sketch in section view mode, showing only objects behind the sketch plane", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTVSectionView->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Open sketch in section view mode", nullptr));
        label_4->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Note: these settings are defaults applied to new sketches. The behavior is remembered for each sketch individually as properties on the View tab.", nullptr));
#if QT_CONFIG(tooltip)
        btnTVApply->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Applies current visibility automation settings to all sketches in the open documents", nullptr));
#endif // QT_CONFIG(tooltip)
        btnTVApply->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsDisplay", "Apply to Existing Sketches", nullptr));
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherSettingsDisplay: public Ui_SketcherSettingsDisplay {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERSETTINGSDISPLAY_H
