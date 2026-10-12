/********************************************************************************
** Form generated from reading UI file 'DlgSettings3DView.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGS3DVIEW_H
#define UI_DLGSETTINGS3DVIEW_H

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

namespace Gui {
namespace Dialog {

class Ui_DlgSettings3DView
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *GroupBoxGeneral;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutCoord;
    Gui::PrefCheckBox *CheckBox_CornerCoordSystem;
    QSpacerItem *horizontalSpacerCoord;
    QLabel *labelCoordSize;
    Gui::PrefSpinBox *SpinBox_CornerCoordSystemSize;
    QLabel *axisLetterColorLabel;
    Gui::PrefColorButton *axisLetterColor;
    QHBoxLayout *horizontalLayout_2;
    QLabel *xAxisLabel;
    Gui::PrefColorButton *xAxisColor;
    QSpacerItem *horizontalSpacer_2;
    QLabel *yAxisLabel;
    Gui::PrefColorButton *yAxisColor;
    QSpacerItem *horizontalSpacer_3;
    QLabel *zAxisLabel;
    Gui::PrefColorButton *zAxisColor;
    Gui::PrefCheckBox *CheckBox_ShowAxisCross;
    Gui::PrefCheckBox *CheckBox_ShowFPS;
    QGroupBox *GroupBox12;
    QVBoxLayout *verticalLayout_3;
    Gui::PrefCheckBox *CheckBox_use_SW_OpenGL;
    Gui::PrefCheckBox *CheckBox_useVBO;
    QGridLayout *gridLayout;
    QLabel *renderCacheLabel;
    QLabel *textLabel1;
    QComboBox *renderCache;
    QComboBox *comboAliasing;
    QLabel *aliasingLAbel;
    Gui::PrefDoubleSpinBox *FloatSpinBox_EyeDistance;
    Gui::PrefComboBox *comboTransparentRender;
    QLabel *transparentRenderLabel;
    QLabel *markerSizeLabel;
    QComboBox *boxMarkerSize;
    QLabel *markerSizeLabel_2;
    Gui::PrefDoubleSpinBox *FloatSpinBox_DatumScale;
    QLabel *maxFrameRateLabel;
    Gui::PrefSpinBox *SpinBox_MaxFrameRate;
    QGroupBox *groupBoxCamera;
    QGridLayout *gridLayout1;
    Gui::PrefRadioButton *radioPerspective;
    Gui::PrefRadioButton *radioOrthographic;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *Gui__Dialog__DlgSettings3DView)
    {
        if (Gui__Dialog__DlgSettings3DView->objectName().isEmpty())
            Gui__Dialog__DlgSettings3DView->setObjectName("Gui__Dialog__DlgSettings3DView");
        Gui__Dialog__DlgSettings3DView->resize(499, 708);
        verticalLayout_2 = new QVBoxLayout(Gui__Dialog__DlgSettings3DView);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        GroupBoxGeneral = new QGroupBox(Gui__Dialog__DlgSettings3DView);
        GroupBoxGeneral->setObjectName("GroupBoxGeneral");
        GroupBoxGeneral->setEnabled(true);
        verticalLayout = new QVBoxLayout(GroupBoxGeneral);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        gridLayoutCoord = new QGridLayout();
        gridLayoutCoord->setSpacing(6);
        gridLayoutCoord->setObjectName("gridLayoutCoord");
        CheckBox_CornerCoordSystem = new Gui::PrefCheckBox(GroupBoxGeneral);
        CheckBox_CornerCoordSystem->setObjectName("CheckBox_CornerCoordSystem");
        CheckBox_CornerCoordSystem->setChecked(true);
        CheckBox_CornerCoordSystem->setProperty("prefEntry", QVariant(QByteArray("CornerCoordSystem")));
        CheckBox_CornerCoordSystem->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayoutCoord->addWidget(CheckBox_CornerCoordSystem, 0, 0, 1, 1);

        horizontalSpacerCoord = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayoutCoord->addItem(horizontalSpacerCoord, 0, 1, 1, 1);

        labelCoordSize = new QLabel(GroupBoxGeneral);
        labelCoordSize->setObjectName("labelCoordSize");
        labelCoordSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayoutCoord->addWidget(labelCoordSize, 0, 2, 1, 1);

        SpinBox_CornerCoordSystemSize = new Gui::PrefSpinBox(GroupBoxGeneral);
        SpinBox_CornerCoordSystemSize->setObjectName("SpinBox_CornerCoordSystemSize");
        SpinBox_CornerCoordSystemSize->setSuffix(QString::fromUtf8("%"));
        SpinBox_CornerCoordSystemSize->setMinimum(2);
        SpinBox_CornerCoordSystemSize->setMaximum(100);
        SpinBox_CornerCoordSystemSize->setValue(10);
        SpinBox_CornerCoordSystemSize->setProperty("prefEntry", QVariant(QByteArray("CornerCoordSystemSize")));
        SpinBox_CornerCoordSystemSize->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayoutCoord->addWidget(SpinBox_CornerCoordSystemSize, 0, 3, 1, 1);

        axisLetterColorLabel = new QLabel(GroupBoxGeneral);
        axisLetterColorLabel->setObjectName("axisLetterColorLabel");

        gridLayoutCoord->addWidget(axisLetterColorLabel, 1, 2, 1, 1);

        axisLetterColor = new Gui::PrefColorButton(GroupBoxGeneral);
        axisLetterColor->setObjectName("axisLetterColor");
        axisLetterColor->setColor(QColor(0, 0, 0));
        axisLetterColor->setProperty("prefEntry", QVariant(QByteArray("AxisLetterColor")));
        axisLetterColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayoutCoord->addWidget(axisLetterColor, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayoutCoord);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        xAxisLabel = new QLabel(GroupBoxGeneral);
        xAxisLabel->setObjectName("xAxisLabel");

        horizontalLayout_2->addWidget(xAxisLabel);

        xAxisColor = new Gui::PrefColorButton(GroupBoxGeneral);
        xAxisColor->setObjectName("xAxisColor");
        xAxisColor->setColor(QColor(204, 51, 51));
        xAxisColor->setProperty("prefEntry", QVariant(QByteArray("AxisXColor")));
        xAxisColor->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(xAxisColor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        yAxisLabel = new QLabel(GroupBoxGeneral);
        yAxisLabel->setObjectName("yAxisLabel");

        horizontalLayout_2->addWidget(yAxisLabel);

        yAxisColor = new Gui::PrefColorButton(GroupBoxGeneral);
        yAxisColor->setObjectName("yAxisColor");
        yAxisColor->setColor(QColor(51, 204, 51));
        yAxisColor->setProperty("prefEntry", QVariant(QByteArray("AxisYColor")));
        yAxisColor->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(yAxisColor);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        zAxisLabel = new QLabel(GroupBoxGeneral);
        zAxisLabel->setObjectName("zAxisLabel");

        horizontalLayout_2->addWidget(zAxisLabel);

        zAxisColor = new Gui::PrefColorButton(GroupBoxGeneral);
        zAxisColor->setObjectName("zAxisColor");
        zAxisColor->setColor(QColor(51, 51, 204));
        zAxisColor->setProperty("prefEntry", QVariant(QByteArray("AxisZColor")));
        zAxisColor->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_2->addWidget(zAxisColor);


        verticalLayout->addLayout(horizontalLayout_2);

        CheckBox_ShowAxisCross = new Gui::PrefCheckBox(GroupBoxGeneral);
        CheckBox_ShowAxisCross->setObjectName("CheckBox_ShowAxisCross");
        CheckBox_ShowAxisCross->setProperty("prefEntry", QVariant(QByteArray("ShowAxisCross")));
        CheckBox_ShowAxisCross->setProperty("prefPath", QVariant(QByteArray("View")));

        verticalLayout->addWidget(CheckBox_ShowAxisCross);

        CheckBox_ShowFPS = new Gui::PrefCheckBox(GroupBoxGeneral);
        CheckBox_ShowFPS->setObjectName("CheckBox_ShowFPS");
        CheckBox_ShowFPS->setProperty("prefEntry", QVariant(QByteArray("ShowFPS")));
        CheckBox_ShowFPS->setProperty("prefPath", QVariant(QByteArray("View")));

        verticalLayout->addWidget(CheckBox_ShowFPS);


        verticalLayout_2->addWidget(GroupBoxGeneral);

        GroupBox12 = new QGroupBox(Gui__Dialog__DlgSettings3DView);
        GroupBox12->setObjectName("GroupBox12");
        GroupBox12->setEnabled(true);
        verticalLayout_3 = new QVBoxLayout(GroupBox12);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        CheckBox_use_SW_OpenGL = new Gui::PrefCheckBox(GroupBox12);
        CheckBox_use_SW_OpenGL->setObjectName("CheckBox_use_SW_OpenGL");
        CheckBox_use_SW_OpenGL->setProperty("prefEntry", QVariant(QByteArray("UseSoftwareOpenGL")));
        CheckBox_use_SW_OpenGL->setProperty("prefPath", QVariant(QByteArray("OpenGL")));

        verticalLayout_3->addWidget(CheckBox_use_SW_OpenGL);

        CheckBox_useVBO = new Gui::PrefCheckBox(GroupBox12);
        CheckBox_useVBO->setObjectName("CheckBox_useVBO");
        CheckBox_useVBO->setProperty("prefEntry", QVariant(QByteArray("UseVBO")));
        CheckBox_useVBO->setProperty("prefPath", QVariant(QByteArray("View")));

        verticalLayout_3->addWidget(CheckBox_useVBO);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        renderCacheLabel = new QLabel(GroupBox12);
        renderCacheLabel->setObjectName("renderCacheLabel");

        gridLayout->addWidget(renderCacheLabel, 0, 0, 1, 1);

        textLabel1 = new QLabel(GroupBox12);
        textLabel1->setObjectName("textLabel1");

        gridLayout->addWidget(textLabel1, 5, 0, 1, 1);

        renderCache = new QComboBox(GroupBox12);
        renderCache->addItem(QString());
        renderCache->addItem(QString());
        renderCache->addItem(QString());
        renderCache->setObjectName("renderCache");
        renderCache->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(renderCache, 0, 1, 1, 1);

        comboAliasing = new QComboBox(GroupBox12);
        comboAliasing->setObjectName("comboAliasing");
        comboAliasing->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(comboAliasing, 1, 1, 1, 1);

        aliasingLAbel = new QLabel(GroupBox12);
        aliasingLAbel->setObjectName("aliasingLAbel");

        gridLayout->addWidget(aliasingLAbel, 1, 0, 1, 1);

        FloatSpinBox_EyeDistance = new Gui::PrefDoubleSpinBox(GroupBox12);
        FloatSpinBox_EyeDistance->setObjectName("FloatSpinBox_EyeDistance");
        FloatSpinBox_EyeDistance->setMinimumSize(QSize(120, 0));
        FloatSpinBox_EyeDistance->setDecimals(1);
        FloatSpinBox_EyeDistance->setMinimum(0.100000000000000);
        FloatSpinBox_EyeDistance->setMaximum(1000.000000000000000);
        FloatSpinBox_EyeDistance->setSingleStep(2.000000000000000);
        FloatSpinBox_EyeDistance->setValue(5.000000000000000);
        FloatSpinBox_EyeDistance->setProperty("prefEntry", QVariant(QByteArray("EyeDistance")));
        FloatSpinBox_EyeDistance->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(FloatSpinBox_EyeDistance, 5, 1, 1, 1);

        comboTransparentRender = new Gui::PrefComboBox(GroupBox12);
        comboTransparentRender->addItem(QString());
        comboTransparentRender->addItem(QString());
        comboTransparentRender->setObjectName("comboTransparentRender");
        comboTransparentRender->setMinimumSize(QSize(120, 0));
        comboTransparentRender->setProperty("prefEntry", QVariant(QByteArray("TransparentObjectRenderType")));
        comboTransparentRender->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(comboTransparentRender, 2, 1, 1, 1);

        transparentRenderLabel = new QLabel(GroupBox12);
        transparentRenderLabel->setObjectName("transparentRenderLabel");

        gridLayout->addWidget(transparentRenderLabel, 2, 0, 1, 1);

        markerSizeLabel = new QLabel(GroupBox12);
        markerSizeLabel->setObjectName("markerSizeLabel");

        gridLayout->addWidget(markerSizeLabel, 3, 0, 1, 1);

        boxMarkerSize = new QComboBox(GroupBox12);
        boxMarkerSize->setObjectName("boxMarkerSize");
        boxMarkerSize->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(boxMarkerSize, 3, 1, 1, 1);

        markerSizeLabel_2 = new QLabel(GroupBox12);
        markerSizeLabel_2->setObjectName("markerSizeLabel_2");

        gridLayout->addWidget(markerSizeLabel_2, 4, 0, 1, 1);

        FloatSpinBox_DatumScale = new Gui::PrefDoubleSpinBox(GroupBox12);
        FloatSpinBox_DatumScale->setObjectName("FloatSpinBox_DatumScale");
        FloatSpinBox_DatumScale->setMinimumSize(QSize(120, 0));
        FloatSpinBox_DatumScale->setDecimals(0);
        FloatSpinBox_DatumScale->setMinimum(0.000000000000000);
        FloatSpinBox_DatumScale->setMaximum(400.000000000000000);
        FloatSpinBox_DatumScale->setSingleStep(5.000000000000000);
        FloatSpinBox_DatumScale->setValue(100.000000000000000);
        FloatSpinBox_DatumScale->setProperty("prefEntry", QVariant(QByteArray("DatumScale")));
        FloatSpinBox_DatumScale->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(FloatSpinBox_DatumScale, 4, 1, 1, 1);

        maxFrameRateLabel = new QLabel(GroupBox12);
        maxFrameRateLabel->setObjectName("maxFrameRateLabel");

        gridLayout->addWidget(maxFrameRateLabel, 6, 0, 1, 1);

        SpinBox_MaxFrameRate = new Gui::PrefSpinBox(GroupBox12);
        SpinBox_MaxFrameRate->setObjectName("SpinBox_MaxFrameRate");
        SpinBox_MaxFrameRate->setMinimumSize(QSize(120, 0));
        SpinBox_MaxFrameRate->setMinimum(-1);
        SpinBox_MaxFrameRate->setMaximum(1000);
        SpinBox_MaxFrameRate->setValue(-1);
        SpinBox_MaxFrameRate->setProperty("prefEntry", QVariant(QByteArray("MaxFrameRate")));
        SpinBox_MaxFrameRate->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(SpinBox_MaxFrameRate, 6, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_2->addWidget(GroupBox12);

        groupBoxCamera = new QGroupBox(Gui__Dialog__DlgSettings3DView);
        groupBoxCamera->setObjectName("groupBoxCamera");
        gridLayout1 = new QGridLayout(groupBoxCamera);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        radioPerspective = new Gui::PrefRadioButton(groupBoxCamera);
        radioPerspective->setObjectName("radioPerspective");
        radioPerspective->setProperty("prefEntry", QVariant(QByteArray("Perspective")));
        radioPerspective->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout1->addWidget(radioPerspective, 0, 0, 1, 1);

        radioOrthographic = new Gui::PrefRadioButton(groupBoxCamera);
        radioOrthographic->setObjectName("radioOrthographic");
        radioOrthographic->setChecked(true);
        radioOrthographic->setProperty("prefEntry", QVariant(QByteArray("Orthographic")));
        radioOrthographic->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout1->addWidget(radioOrthographic, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBoxCamera);

        spacerItem = new QSpacerItem(455, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(spacerItem);


        retranslateUi(Gui__Dialog__DlgSettings3DView);
        QObject::connect(CheckBox_CornerCoordSystem, SIGNAL(toggled(bool)), SpinBox_CornerCoordSystemSize, SLOT(setEnabled(bool)));
        QObject::connect(CheckBox_CornerCoordSystem, SIGNAL(toggled(bool)), axisLetterColor, SLOT(setEnabled(bool)));

        renderCache->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettings3DView);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettings3DView)
    {
        Gui__Dialog__DlgSettings3DView->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "3D View", nullptr));
        GroupBoxGeneral->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "General", nullptr));
#if QT_CONFIG(tooltip)
        CheckBox_CornerCoordSystem->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Main coordinate system will always be shown in\n"
"lower right corner within opened files", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_CornerCoordSystem->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Show coordinate system in the corner", nullptr));
        labelCoordSize->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Relative size", nullptr));
#if QT_CONFIG(tooltip)
        SpinBox_CornerCoordSystemSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Size of main coordinate system representation\n"
"in the corner in % of height/width of the viewport", nullptr));
#endif // QT_CONFIG(tooltip)
        axisLetterColorLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Letter color", nullptr));
#if QT_CONFIG(tooltip)
        axisLetterColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Axis letter and FPS counter color", nullptr));
#endif // QT_CONFIG(tooltip)
        xAxisLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "X-axis color", nullptr));
        xAxisColor->setText(QString());
        yAxisLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Y-axis color", nullptr));
        yAxisColor->setText(QString());
        zAxisLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Z-axis color", nullptr));
        zAxisColor->setText(QString());
#if QT_CONFIG(tooltip)
        CheckBox_ShowAxisCross->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Axis cross will be shown by default at file\n"
"opening or creation", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_ShowAxisCross->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Show axis cross by default", nullptr));
#if QT_CONFIG(tooltip)
        CheckBox_ShowFPS->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Time needed for last operation and resulting frame rate\n"
"will be shown at the lower left corner in opened files", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_ShowFPS->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Show counter of frames per second", nullptr));
        GroupBox12->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Rendering", nullptr));
#if QT_CONFIG(tooltip)
        CheckBox_use_SW_OpenGL->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "This option is useful for troubleshooting graphics card and driver problems.\n"
"Changing this option requires a restart of the application.", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_use_SW_OpenGL->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Use software OpenGL", nullptr));
#if QT_CONFIG(tooltip)
        CheckBox_useVBO->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "A VBO is an OpenGL feature that enables uploading geometry data\n"
"to the graphics card, and is how efficient 3D rendering is done\n"
"on modern hardware.\n"
"This feature might not be used by default if you are running old\n"
"hardware or drivers. By selecting this option its usage will be\n"
"forcibly enabled.\n"
"\n"
"Note: Turning this on is typically not required. If you do,\n"
"remember to report this setting as enabled when seeking support.", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_useVBO->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Force use of OpenGL VBO (Vertex Buffer Object)", nullptr));
        renderCacheLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Render cache", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Eye to eye distance for stereo modes", nullptr));
        renderCache->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Auto", nullptr));
        renderCache->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Distributed", nullptr));
        renderCache->setItemText(2, QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Centralized", nullptr));

#if QT_CONFIG(tooltip)
        renderCache->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "'Render caching' is another way to say 'Rendering acceleration'.\n"
"There are 3 options available to achieve this:\n"
"1) 'Auto' (default), let Coin3D decide where to cache.\n"
"2) 'Distributed', manually turn on cache for all view provider root node.\n"
"3) 'Centralized', manually turn off cache in all nodes of all view provider, and\n"
"only cache at the scene graph root node. This offers the fastest rendering speed\n"
"but slower response to any scene changes.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        comboAliasing->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Method of multisample anti-aliasing", nullptr));
#endif // QT_CONFIG(tooltip)
        aliasingLAbel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Anti-aliasing", nullptr));
#if QT_CONFIG(tooltip)
        FloatSpinBox_EyeDistance->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Eye-to-eye distance used for stereo projections.\n"
"The specified value is a factor that will be multiplied with the\n"
"bounding box size of the 3D object that is currently displayed.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboTransparentRender->setItemText(0, QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "One pass", nullptr));
        comboTransparentRender->setItemText(1, QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Backface pass", nullptr));

#if QT_CONFIG(tooltip)
        comboTransparentRender->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Render types of transparent objects", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        transparentRenderLabel->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        transparentRenderLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Transparent objects", nullptr));
#if QT_CONFIG(tooltip)
        markerSizeLabel->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        markerSizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Marker size", nullptr));
#if QT_CONFIG(tooltip)
        boxMarkerSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Size of vertices in the Sketcher, TechDraw and other workbenches", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        markerSizeLabel_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        markerSizeLabel_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Datum size", nullptr));
#if QT_CONFIG(tooltip)
        FloatSpinBox_DatumScale->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Size of core datum objects", nullptr));
#endif // QT_CONFIG(tooltip)
        FloatSpinBox_DatumScale->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "%", nullptr));
        maxFrameRateLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Maximum frame rate", nullptr));
#if QT_CONFIG(tooltip)
        SpinBox_MaxFrameRate->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Upper limit on how often the 3D view is redrawn.\n"
"'Automatic' follows the refresh rate of the display, since drawing\n"
"faster than the display can show only wastes graphics card work.\n"
"Set to 0 to redraw as fast as the graphics driver allows.", nullptr));
#endif // QT_CONFIG(tooltip)
        SpinBox_MaxFrameRate->setSpecialValueText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Automatic", nullptr));
        SpinBox_MaxFrameRate->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", " FPS", nullptr));
        groupBoxCamera->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Camera Type", nullptr));
#if QT_CONFIG(tooltip)
        radioPerspective->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Objects will appear in a perspective projection", nullptr));
#endif // QT_CONFIG(tooltip)
        radioPerspective->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Perspective renderin&g", nullptr));
#if QT_CONFIG(tooltip)
        radioOrthographic->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Objects will be in orthographic projection", nullptr));
#endif // QT_CONFIG(tooltip)
        radioOrthographic->setText(QCoreApplication::translate("Gui::Dialog::DlgSettings3DView", "Or&thographic rendering", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettings3DView: public Ui_DlgSettings3DView {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGS3DVIEW_H
