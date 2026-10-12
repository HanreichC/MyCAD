/********************************************************************************
** Form generated from reading UI file 'DlgSettingsNavigation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSNAVIGATION_H
#define UI_DLGSETTINGSNAVIGATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsNavigation
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxNaviCube;
    QGridLayout *gridLayout_2;
    QLabel *stepLabel;
    Gui::PrefSpinBox *prefStepByTurn;
    QSpacerItem *horizontalSpacer;
    QLabel *cornerLabel;
    Gui::PrefComboBox *naviCubeCorner;
    Gui::PrefCheckBox *naviCubeToNearest;
    QLabel *FontNameLabel;
    Gui::PrefComboBox *naviCubeFontName;
    QLabel *CubeSizeLabel;
    Gui::PrefSpinBox *prefCubeSize;
    QLabel *inactiveOpacityLabel;
    Gui::PrefSpinBox *naviCubeInactiveOpacity;
    QLabel *BaseColorLabel;
    Gui::PrefColorButton *naviCubeBaseColor;
    QGroupBox *groupBoxRotationCenter;
    QGridLayout *gridLayout_3;
    QLabel *sizeLabelRotationCenter;
    QLabel *colorLabelRotationCenter;
    Gui::PrefDoubleSpinBox *rotationCenterSize;
    Gui::PrefColorButton *rotationCenterColor;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *GroupBox12;
    QGridLayout *gridLayout;
    QLabel *navigationLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *mouseButton;
    QComboBox *comboNavigationStyle;
    QLabel *orbitLabel;
    QComboBox *comboOrbitStyle;
    QLabel *labelRotationMode;
    QComboBox *comboRotationMode;
    QLabel *newDocViewLabel;
    QComboBox *comboNewDocView;
    QLabel *label_2;
    Gui::PrefUnitSpinBox *qspinNewDocScale;
    Gui::PrefCheckBox *checkBoxZoomAtCursor;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    Gui::PrefDoubleSpinBox *spinBoxZoomStep;
    QSpacerItem *horizontalSpacer_2;
    Gui::PrefCheckBox *checkBoxInvertZoom;
    Gui::PrefCheckBox *checkBoxDisableTilt;
    Gui::PrefCheckBox *checkBoxTouchpadScrollPans;
    QGroupBox *spaceMouseDevice;
    QGridLayout *gridLayout_5;
    Gui::PrefCheckBox *legacySpaceMouseDevices;
    QGroupBox *groupBoxAnimations;
    QGridLayout *gridLayout_4;
    QLabel *animationDurationLabel;
    Gui::PrefCheckBox *checkBoxSpinningAnimations;
    Gui::PrefSpinBox *spinBoxAnimationDuration;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBoxClarifySelection;
    QGridLayout *gridLayout_6;
    Gui::PrefCheckBox *checkBoxEnableLongPressClarifySelection;
    QLabel *labelLongPressTimeout;
    Gui::PrefDoubleSpinBox *spinBoxLongPressTimeout;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsNavigation)
    {
        if (Gui__Dialog__DlgSettingsNavigation->objectName().isEmpty())
            Gui__Dialog__DlgSettingsNavigation->setObjectName("Gui__Dialog__DlgSettingsNavigation");
        Gui__Dialog__DlgSettingsNavigation->resize(548, 795);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsNavigation);
        verticalLayout->setObjectName("verticalLayout");
        groupBoxNaviCube = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        groupBoxNaviCube->setObjectName("groupBoxNaviCube");
        groupBoxNaviCube->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupBoxNaviCube);
        gridLayout_2->setObjectName("gridLayout_2");
        stepLabel = new QLabel(groupBoxNaviCube);
        stepLabel->setObjectName("stepLabel");

        gridLayout_2->addWidget(stepLabel, 0, 0, 1, 1);

        prefStepByTurn = new Gui::PrefSpinBox(groupBoxNaviCube);
        prefStepByTurn->setObjectName("prefStepByTurn");
        prefStepByTurn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        prefStepByTurn->setMinimum(4);
        prefStepByTurn->setMaximum(36);
        prefStepByTurn->setValue(8);
        prefStepByTurn->setProperty("prefEntry", QVariant(QByteArray("NaviStepByTurn")));
        prefStepByTurn->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(prefStepByTurn, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        cornerLabel = new QLabel(groupBoxNaviCube);
        cornerLabel->setObjectName("cornerLabel");

        gridLayout_2->addWidget(cornerLabel, 0, 3, 1, 1);

        naviCubeCorner = new Gui::PrefComboBox(groupBoxNaviCube);
        naviCubeCorner->addItem(QString());
        naviCubeCorner->addItem(QString());
        naviCubeCorner->addItem(QString());
        naviCubeCorner->addItem(QString());
        naviCubeCorner->setObjectName("naviCubeCorner");
        naviCubeCorner->setProperty("prefEntry", QVariant(QByteArray("CornerNaviCube")));
        naviCubeCorner->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(naviCubeCorner, 0, 4, 1, 1);

        naviCubeToNearest = new Gui::PrefCheckBox(groupBoxNaviCube);
        naviCubeToNearest->setObjectName("naviCubeToNearest");
        naviCubeToNearest->setChecked(true);
        naviCubeToNearest->setProperty("prefEntry", QVariant(QByteArray("NaviRotateToNearest")));
        naviCubeToNearest->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(naviCubeToNearest, 1, 0, 1, 2);

        FontNameLabel = new QLabel(groupBoxNaviCube);
        FontNameLabel->setObjectName("FontNameLabel");

        gridLayout_2->addWidget(FontNameLabel, 1, 3, 1, 1);

        naviCubeFontName = new Gui::PrefComboBox(groupBoxNaviCube);
        naviCubeFontName->addItem(QString());
        naviCubeFontName->setObjectName("naviCubeFontName");
        naviCubeFontName->setMaximumSize(QSize(240, 16777215));
        naviCubeFontName->setProperty("prefEntry", QVariant(QByteArray("FontString")));
        naviCubeFontName->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(naviCubeFontName, 1, 4, 1, 1);

        CubeSizeLabel = new QLabel(groupBoxNaviCube);
        CubeSizeLabel->setObjectName("CubeSizeLabel");

        gridLayout_2->addWidget(CubeSizeLabel, 2, 0, 1, 1);

        prefCubeSize = new Gui::PrefSpinBox(groupBoxNaviCube);
        prefCubeSize->setObjectName("prefCubeSize");
        prefCubeSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        prefCubeSize->setSuffix(QString::fromUtf8(" px"));
        prefCubeSize->setMinimum(10);
        prefCubeSize->setMaximum(1024);
        prefCubeSize->setSingleStep(10);
        prefCubeSize->setValue(132);
        prefCubeSize->setProperty("prefEntry", QVariant(QByteArray("CubeSize")));
        prefCubeSize->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(prefCubeSize, 2, 1, 1, 1);

        inactiveOpacityLabel = new QLabel(groupBoxNaviCube);
        inactiveOpacityLabel->setObjectName("inactiveOpacityLabel");
        inactiveOpacityLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(inactiveOpacityLabel, 2, 3, 1, 1);

        naviCubeInactiveOpacity = new Gui::PrefSpinBox(groupBoxNaviCube);
        naviCubeInactiveOpacity->setObjectName("naviCubeInactiveOpacity");
        naviCubeInactiveOpacity->setMaximumSize(QSize(60, 16777215));
        naviCubeInactiveOpacity->setSuffix(QString::fromUtf8("%"));
        naviCubeInactiveOpacity->setMinimum(1);
        naviCubeInactiveOpacity->setMaximum(100);
        naviCubeInactiveOpacity->setValue(50);
        naviCubeInactiveOpacity->setProperty("prefEntry", QVariant(QByteArray("InactiveOpacity")));
        naviCubeInactiveOpacity->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(naviCubeInactiveOpacity, 2, 4, 1, 1);

        BaseColorLabel = new QLabel(groupBoxNaviCube);
        BaseColorLabel->setObjectName("BaseColorLabel");

        gridLayout_2->addWidget(BaseColorLabel, 3, 0, 1, 1);

        naviCubeBaseColor = new Gui::PrefColorButton(groupBoxNaviCube);
        naviCubeBaseColor->setObjectName("naviCubeBaseColor");
        naviCubeBaseColor->setColor(QColor(226, 232, 239, 128));
        naviCubeBaseColor->setProperty("prefEntry", QVariant(QByteArray("BaseColor")));
        naviCubeBaseColor->setProperty("prefPath", QVariant(QByteArray("NaviCube")));

        gridLayout_2->addWidget(naviCubeBaseColor, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBoxNaviCube);

        groupBoxRotationCenter = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        groupBoxRotationCenter->setObjectName("groupBoxRotationCenter");
        groupBoxRotationCenter->setCheckable(true);
        gridLayout_3 = new QGridLayout(groupBoxRotationCenter);
        gridLayout_3->setObjectName("gridLayout_3");
        sizeLabelRotationCenter = new QLabel(groupBoxRotationCenter);
        sizeLabelRotationCenter->setObjectName("sizeLabelRotationCenter");

        gridLayout_3->addWidget(sizeLabelRotationCenter, 0, 0, 1, 1);

        colorLabelRotationCenter = new QLabel(groupBoxRotationCenter);
        colorLabelRotationCenter->setObjectName("colorLabelRotationCenter");

        gridLayout_3->addWidget(colorLabelRotationCenter, 1, 0, 1, 1);

        rotationCenterSize = new Gui::PrefDoubleSpinBox(groupBoxRotationCenter);
        rotationCenterSize->setObjectName("rotationCenterSize");
        rotationCenterSize->setMaximumSize(QSize(60, 16777215));
        rotationCenterSize->setDecimals(1);
        rotationCenterSize->setMinimum(1.000000000000000);
        rotationCenterSize->setMaximum(100.000000000000000);
        rotationCenterSize->setSingleStep(0.500000000000000);
        rotationCenterSize->setValue(5.000000000000000);
        rotationCenterSize->setProperty("prefEntry", QVariant(QByteArray("RotationCenterSize")));
        rotationCenterSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_3->addWidget(rotationCenterSize, 0, 1, 1, 1);

        rotationCenterColor = new Gui::PrefColorButton(groupBoxRotationCenter);
        rotationCenterColor->setObjectName("rotationCenterColor");
        rotationCenterColor->setColor(QColor(255, 0, 0, 51));
        rotationCenterColor->setProperty("prefEntry", QVariant(QByteArray("RotationCenterColor")));
        rotationCenterColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_3->addWidget(rotationCenterColor, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBoxRotationCenter);

        GroupBox12 = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        GroupBox12->setObjectName("GroupBox12");
        GroupBox12->setEnabled(true);
        gridLayout = new QGridLayout(GroupBox12);
        gridLayout->setObjectName("gridLayout");
        navigationLabel = new QLabel(GroupBox12);
        navigationLabel->setObjectName("navigationLabel");

        gridLayout->addWidget(navigationLabel, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        mouseButton = new QPushButton(GroupBox12);
        mouseButton->setObjectName("mouseButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mouseButton->sizePolicy().hasHeightForWidth());
        mouseButton->setSizePolicy(sizePolicy);
        mouseButton->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(mouseButton);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        comboNavigationStyle = new QComboBox(GroupBox12);
        comboNavigationStyle->setObjectName("comboNavigationStyle");
        comboNavigationStyle->setMinimumSize(QSize(120, 0));
        comboNavigationStyle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboNavigationStyle, 0, 2, 1, 1);

        orbitLabel = new QLabel(GroupBox12);
        orbitLabel->setObjectName("orbitLabel");

        gridLayout->addWidget(orbitLabel, 1, 0, 1, 1);

        comboOrbitStyle = new QComboBox(GroupBox12);
        comboOrbitStyle->addItem(QString());
        comboOrbitStyle->addItem(QString());
        comboOrbitStyle->addItem(QString());
        comboOrbitStyle->addItem(QString());
        comboOrbitStyle->addItem(QString());
        comboOrbitStyle->setObjectName("comboOrbitStyle");
        comboOrbitStyle->setMinimumSize(QSize(120, 0));
        comboOrbitStyle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboOrbitStyle, 1, 2, 1, 1);

        labelRotationMode = new QLabel(GroupBox12);
        labelRotationMode->setObjectName("labelRotationMode");

        gridLayout->addWidget(labelRotationMode, 2, 0, 1, 1);

        comboRotationMode = new QComboBox(GroupBox12);
        comboRotationMode->addItem(QString());
        comboRotationMode->addItem(QString());
        comboRotationMode->addItem(QString());
        comboRotationMode->setObjectName("comboRotationMode");
        comboRotationMode->setMinimumSize(QSize(120, 0));
        comboRotationMode->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboRotationMode, 2, 2, 1, 1);

        newDocViewLabel = new QLabel(GroupBox12);
        newDocViewLabel->setObjectName("newDocViewLabel");

        gridLayout->addWidget(newDocViewLabel, 3, 0, 1, 1);

        comboNewDocView = new QComboBox(GroupBox12);
        comboNewDocView->setObjectName("comboNewDocView");
        comboNewDocView->setMinimumSize(QSize(120, 0));
        comboNewDocView->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(comboNewDocView, 3, 2, 1, 1);

        label_2 = new QLabel(GroupBox12);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        qspinNewDocScale = new Gui::PrefUnitSpinBox(GroupBox12);
        qspinNewDocScale->setObjectName("qspinNewDocScale");
        qspinNewDocScale->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        qspinNewDocScale->setMinimum(0.000010000000000);
        qspinNewDocScale->setMaximum(10000000.000000000000000);
        qspinNewDocScale->setProperty("rawValue", QVariant(100.000000000000000));
        qspinNewDocScale->setProperty("prefEntry", QVariant(QByteArray("NewDocumentCameraScale")));
        qspinNewDocScale->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(qspinNewDocScale, 4, 2, 1, 1);

        checkBoxZoomAtCursor = new Gui::PrefCheckBox(GroupBox12);
        checkBoxZoomAtCursor->setObjectName("checkBoxZoomAtCursor");
        checkBoxZoomAtCursor->setChecked(true);
        checkBoxZoomAtCursor->setProperty("prefEntry", QVariant(QByteArray("ZoomAtCursor")));
        checkBoxZoomAtCursor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxZoomAtCursor, 6, 0, 1, 1);

        label = new QLabel(GroupBox12);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 6, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        spinBoxZoomStep = new Gui::PrefDoubleSpinBox(GroupBox12);
        spinBoxZoomStep->setObjectName("spinBoxZoomStep");
        spinBoxZoomStep->setMaximumSize(QSize(60, 16777215));
        spinBoxZoomStep->setMinimum(0.010000000000000);
        spinBoxZoomStep->setMaximum(1.000000000000000);
        spinBoxZoomStep->setSingleStep(0.050000000000000);
        spinBoxZoomStep->setValue(0.200000000000000);
        spinBoxZoomStep->setProperty("prefEntry", QVariant(QByteArray("ZoomStep")));
        spinBoxZoomStep->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout->addWidget(spinBoxZoomStep);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 6, 2, 1, 1);

        checkBoxInvertZoom = new Gui::PrefCheckBox(GroupBox12);
        checkBoxInvertZoom->setObjectName("checkBoxInvertZoom");
        checkBoxInvertZoom->setChecked(true);
        checkBoxInvertZoom->setProperty("prefEntry", QVariant(QByteArray("InvertZoom")));
        checkBoxInvertZoom->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxInvertZoom, 7, 0, 1, 1);

        checkBoxDisableTilt = new Gui::PrefCheckBox(GroupBox12);
        checkBoxDisableTilt->setObjectName("checkBoxDisableTilt");
        checkBoxDisableTilt->setChecked(true);
        checkBoxDisableTilt->setProperty("prefEntry", QVariant(QByteArray("DisableTouchTilt")));
        checkBoxDisableTilt->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxDisableTilt, 8, 0, 1, 1);

        checkBoxTouchpadScrollPans = new Gui::PrefCheckBox(GroupBox12);
        checkBoxTouchpadScrollPans->setObjectName("checkBoxTouchpadScrollPans");
        checkBoxTouchpadScrollPans->setChecked(false);
        checkBoxTouchpadScrollPans->setProperty("prefEntry", QVariant(QByteArray("TouchpadScrollPans")));
        checkBoxTouchpadScrollPans->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxTouchpadScrollPans, 9, 0, 1, 1);


        verticalLayout->addWidget(GroupBox12);

        spaceMouseDevice = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        spaceMouseDevice->setObjectName("spaceMouseDevice");
        gridLayout_5 = new QGridLayout(spaceMouseDevice);
        gridLayout_5->setObjectName("gridLayout_5");
        legacySpaceMouseDevices = new Gui::PrefCheckBox(spaceMouseDevice);
        legacySpaceMouseDevices->setObjectName("legacySpaceMouseDevices");
        legacySpaceMouseDevices->setProperty("prefEntry", QVariant(QByteArray("LegacySpaceMouseDevices")));
        legacySpaceMouseDevices->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_5->addWidget(legacySpaceMouseDevices, 0, 0, 1, 1);


        verticalLayout->addWidget(spaceMouseDevice);

        groupBoxAnimations = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        groupBoxAnimations->setObjectName("groupBoxAnimations");
        groupBoxAnimations->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupBoxAnimations);
        gridLayout_4->setObjectName("gridLayout_4");
        animationDurationLabel = new QLabel(groupBoxAnimations);
        animationDurationLabel->setObjectName("animationDurationLabel");
        animationDurationLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(animationDurationLabel, 1, 0, 1, 1);

        checkBoxSpinningAnimations = new Gui::PrefCheckBox(groupBoxAnimations);
        checkBoxSpinningAnimations->setObjectName("checkBoxSpinningAnimations");
        checkBoxSpinningAnimations->setChecked(false);
        checkBoxSpinningAnimations->setProperty("prefEntry", QVariant(QByteArray("UseSpinningAnimations")));
        checkBoxSpinningAnimations->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_4->addWidget(checkBoxSpinningAnimations, 2, 0, 1, 1);

        spinBoxAnimationDuration = new Gui::PrefSpinBox(groupBoxAnimations);
        spinBoxAnimationDuration->setObjectName("spinBoxAnimationDuration");
        spinBoxAnimationDuration->setMaximumSize(QSize(60, 16777215));
        spinBoxAnimationDuration->setSuffix(QString::fromUtf8(" ms"));
        spinBoxAnimationDuration->setMinimum(100);
        spinBoxAnimationDuration->setMaximum(10000);
        spinBoxAnimationDuration->setSingleStep(50);
        spinBoxAnimationDuration->setValue(500);
        spinBoxAnimationDuration->setProperty("prefEntry", QVariant(QByteArray("AnimationDuration")));
        spinBoxAnimationDuration->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_4->addWidget(spinBoxAnimationDuration, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_6, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBoxAnimations);

        groupBoxClarifySelection = new QGroupBox(Gui__Dialog__DlgSettingsNavigation);
        groupBoxClarifySelection->setObjectName("groupBoxClarifySelection");
        gridLayout_6 = new QGridLayout(groupBoxClarifySelection);
        gridLayout_6->setObjectName("gridLayout_6");
        checkBoxEnableLongPressClarifySelection = new Gui::PrefCheckBox(groupBoxClarifySelection);
        checkBoxEnableLongPressClarifySelection->setObjectName("checkBoxEnableLongPressClarifySelection");
        checkBoxEnableLongPressClarifySelection->setChecked(true);
        checkBoxEnableLongPressClarifySelection->setProperty("prefEntry", QVariant(QByteArray("EnableLongPressClarifySelection")));
        checkBoxEnableLongPressClarifySelection->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(checkBoxEnableLongPressClarifySelection, 0, 0, 1, 1);

        labelLongPressTimeout = new QLabel(groupBoxClarifySelection);
        labelLongPressTimeout->setObjectName("labelLongPressTimeout");
        labelLongPressTimeout->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(labelLongPressTimeout, 1, 0, 1, 1);

        spinBoxLongPressTimeout = new Gui::PrefDoubleSpinBox(groupBoxClarifySelection);
        spinBoxLongPressTimeout->setObjectName("spinBoxLongPressTimeout");
        spinBoxLongPressTimeout->setMaximumSize(QSize(80, 16777215));
        spinBoxLongPressTimeout->setSuffix(QString::fromUtf8(" s"));
        spinBoxLongPressTimeout->setDecimals(1);
        spinBoxLongPressTimeout->setMinimum(0.300000000000000);
        spinBoxLongPressTimeout->setMaximum(3.000000000000000);
        spinBoxLongPressTimeout->setSingleStep(0.100000000000000);
        spinBoxLongPressTimeout->setValue(1.000000000000000);
        spinBoxLongPressTimeout->setProperty("prefEntry", QVariant(QByteArray("LongPressTimeout")));
        spinBoxLongPressTimeout->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_6->addWidget(spinBoxLongPressTimeout, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_7, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBoxClarifySelection);

        verticalSpacer = new QSpacerItem(20, 96, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(Gui__Dialog__DlgSettingsNavigation);
        QObject::connect(checkBoxEnableLongPressClarifySelection, SIGNAL(toggled(bool)), spinBoxLongPressTimeout, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxEnableLongPressClarifySelection, SIGNAL(toggled(bool)), labelLongPressTimeout, SLOT(setEnabled(bool)));

        naviCubeCorner->setCurrentIndex(1);
        naviCubeFontName->setCurrentIndex(-1);
        comboNavigationStyle->setCurrentIndex(-1);
        comboOrbitStyle->setCurrentIndex(0);
        comboRotationMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsNavigation);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsNavigation)
    {
        Gui__Dialog__DlgSettingsNavigation->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Navigation", nullptr));
        groupBoxNaviCube->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Navigation Cube", nullptr));
        stepLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Steps by turn", nullptr));
#if QT_CONFIG(tooltip)
        prefStepByTurn->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Number of steps by turn when using arrows (default = 8 : step angle = 360/8 = 45 deg)", nullptr));
#endif // QT_CONFIG(tooltip)
        cornerLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Corner", nullptr));
        naviCubeCorner->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Top left", nullptr));
        naviCubeCorner->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Top right", nullptr));
        naviCubeCorner->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Bottom left", nullptr));
        naviCubeCorner->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Bottom right", nullptr));

#if QT_CONFIG(tooltip)
        naviCubeCorner->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Corner where the navigation cube is displayed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        naviCubeToNearest->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotates to nearest possible state when clicking a face of the cube", nullptr));
#endif // QT_CONFIG(tooltip)
        naviCubeToNearest->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotate to nearest", nullptr));
        FontNameLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Font name", nullptr));
        naviCubeFontName->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Default", nullptr));

#if QT_CONFIG(tooltip)
        naviCubeFontName->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Font name of the navigation cube", nullptr));
#endif // QT_CONFIG(tooltip)
        CubeSizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Cube size", nullptr));
#if QT_CONFIG(tooltip)
        prefCubeSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Size of the navigation cube", nullptr));
#endif // QT_CONFIG(tooltip)
        inactiveOpacityLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Opacity when inactive", nullptr));
#if QT_CONFIG(tooltip)
        naviCubeInactiveOpacity->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Opacity of the navigation cube when not focused", nullptr));
#endif // QT_CONFIG(tooltip)
        BaseColorLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Color", nullptr));
#if QT_CONFIG(tooltip)
        naviCubeBaseColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Base color for all elements", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxRotationCenter->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotation Center Indicator", nullptr));
        sizeLabelRotationCenter->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Sphere size", nullptr));
        colorLabelRotationCenter->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Color and transparency", nullptr));
#if QT_CONFIG(tooltip)
        rotationCenterSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "The size of the rotation center indicator", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        rotationCenterColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "The color of the rotation center indicator", nullptr));
#endif // QT_CONFIG(tooltip)
        GroupBox12->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Navigation", nullptr));
        navigationLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "3D navigation", nullptr));
#if QT_CONFIG(tooltip)
        mouseButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Lists the mouse button configs for each chosen navigation setting.\n"
"Select a set and then press the button to view said configurations.", nullptr));
#endif // QT_CONFIG(tooltip)
        mouseButton->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Mouse Configuration", nullptr));
#if QT_CONFIG(tooltip)
        comboNavigationStyle->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Navigation settings set", nullptr));
#endif // QT_CONFIG(tooltip)
        orbitLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Orbit style", nullptr));
        comboOrbitStyle->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rounded Arcball", nullptr));
        comboOrbitStyle->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Trackball", nullptr));
        comboOrbitStyle->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Trackball Classic", nullptr));
        comboOrbitStyle->setItemText(3, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Free Turntable", nullptr));
        comboOrbitStyle->setItemText(4, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Turntable", nullptr));

#if QT_CONFIG(tooltip)
        comboOrbitStyle->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotation orbit style.\n"
"Rounded Arcball: moving the mouse in the corners of the screen will only roll the part.\n"
"Trackball: moving the mouse horizontally will rotate the part around the Y-axis.\n"
"Trackball Classic: moving the mouse will rotate the part allowing precession.\n"
"Free Turntable: the part will be rotated around the Z-axis.\n"
"Turntable: the part will be rotated around the Z-axis (with constrained axes).\n"
"         ", nullptr));
#endif // QT_CONFIG(tooltip)
        labelRotationMode->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotation mode", nullptr));
        comboRotationMode->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Window center", nullptr));
        comboRotationMode->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Drag at cursor", nullptr));
        comboRotationMode->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Object center", nullptr));

#if QT_CONFIG(tooltip)
        comboRotationMode->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Rotations in 3D will use current cursor position as center for rotation", nullptr));
#endif // QT_CONFIG(tooltip)
        newDocViewLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Default camera orientation", nullptr));
#if QT_CONFIG(tooltip)
        comboNewDocView->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Default camera orientation when creating a new document or selecting the home view", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Camera zoom", nullptr));
#if QT_CONFIG(tooltip)
        qspinNewDocScale->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Sets camera zoom for new documents.\n"
"The value is the diameter of the sphere to fit on the screen.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBoxZoomAtCursor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Zoom operations will be performed at position of mouse pointer", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxZoomAtCursor->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Zoom at cursor", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Zoom step", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxZoomStep->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "How much will be zoomed.\n"
"Zoom step of '1' means a factor of 7.5 for every zoom step.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBoxInvertZoom->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Direction of zoom operations will be inverted", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxInvertZoom->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Invert zoom", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxDisableTilt->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Prevents view tilting when pinch-zooming.\n"
"Mouse tilting is not disabled by this setting.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxDisableTilt->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Disable touchscreen tilt gesture", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTouchpadScrollPans->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Two-finger scroll on a touchpad pans the view.\n"
"Shift + scroll orbits, Ctrl + scroll (Cmd on macOS) zooms.\n"
"Applies to touchpads and other devices that report\n"
"pixel-precise scrolling. Ordinary wheel mice keep zooming.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTouchpadScrollPans->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Touchpad scroll pans instead of zooming", nullptr));
        spaceMouseDevice->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Space Mouse", nullptr));
        legacySpaceMouseDevices->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Enable support of legacy SpaceMouse devices", nullptr));
        groupBoxAnimations->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Animations", nullptr));
#if QT_CONFIG(tooltip)
        animationDurationLabel->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Duration of navigation animations that have a fixed duration", nullptr));
#endif // QT_CONFIG(tooltip)
        animationDurationLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Animation duration", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxSpinningAnimations->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Enable spinning animations that are used in some navigation styles after dragging", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxSpinningAnimations->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Enable spinning animations", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxAnimationDuration->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "The duration of navigation animations in milliseconds", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxClarifySelection->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Clarify Selection", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxEnableLongPressClarifySelection->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Enable Clarify Selection on long press of left mouse button.\n"
"When enabled, holding left mouse button shows a menu to select overlapping objects.\n"
"Some navigation styles (OpenInventor, Gesture, OpenSCAD) require Ctrl+LMB instead of just LMB.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxEnableLongPressClarifySelection->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Enable long press clarify selection", nullptr));
#if QT_CONFIG(tooltip)
        labelLongPressTimeout->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Time in seconds to hold left mouse button before showing clarify selection menu", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLongPressTimeout->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Long press timeout", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxLongPressTimeout->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNavigation", "Duration in seconds to hold left mouse button before clarify selection is triggered", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsNavigation: public Ui_DlgSettingsNavigation {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSNAVIGATION_H
