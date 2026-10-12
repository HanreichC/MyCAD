/********************************************************************************
** Form generated from reading UI file 'SketcherSettingsGrid.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERSETTINGSGRID_H
#define UI_SKETCHERSETTINGSGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"
#include "Gui/Widgets.h"

namespace SketcherGui {

class Ui_SketcherSettingsGrid
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_1;
    QGridLayout *QGridLayout_1;
    Gui::PrefCheckBox *checkBoxShowGrid;
    Gui::PrefCheckBox *checkBoxGridAuto;
    QLabel *label_gridSize;
    Gui::PrefQuantitySpinBox *gridSize;
    QLabel *label_gridSizePixelThreshold;
    Gui::PrefSpinBox *gridSizePixelThreshold;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayoutDisplay;
    QLabel *label_gridTransparency;
    Gui::PrefSpinBox *gridTransparency;
    QGroupBox *groupBox_3;
    QGridLayout *QGridLayout_2;
    QLabel *label_2;
    QComboBox *gridLinePattern;
    QLabel *label_gridLineWidth;
    Gui::PrefSpinBox *gridLineWidth;
    QLabel *label_gridLineColor;
    Gui::PrefColorButton *gridLineColor;
    QGroupBox *groupBox_4;
    QGridLayout *QGridLayout_3;
    QLabel *label_gridNumberSubdivision;
    Gui::PrefSpinBox *gridNumberSubdivision;
    QLabel *label_22;
    QComboBox *gridDivLinePattern;
    QLabel *label_gridDivLineWidth;
    Gui::PrefSpinBox *gridDivLineWidth;
    QLabel *label_gridDivLineColor;
    Gui::PrefColorButton *gridDivLineColor;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SketcherGui__SketcherSettingsGrid)
    {
        if (SketcherGui__SketcherSettingsGrid->objectName().isEmpty())
            SketcherGui__SketcherSettingsGrid->setObjectName("SketcherGui__SketcherSettingsGrid");
        SketcherGui__SketcherSettingsGrid->resize(500, 664);
        verticalLayout = new QVBoxLayout(SketcherGui__SketcherSettingsGrid);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_1 = new QGroupBox(SketcherGui__SketcherSettingsGrid);
        groupBox_1->setObjectName("groupBox_1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_1->sizePolicy().hasHeightForWidth());
        groupBox_1->setSizePolicy(sizePolicy);
        QGridLayout_1 = new QGridLayout(groupBox_1);
        QGridLayout_1->setObjectName("QGridLayout_1");
        checkBoxShowGrid = new Gui::PrefCheckBox(groupBox_1);
        checkBoxShowGrid->setObjectName("checkBoxShowGrid");
        checkBoxShowGrid->setEnabled(true);
        checkBoxShowGrid->setChecked(true);
        checkBoxShowGrid->setProperty("prefEntry", QVariant(QByteArray("ShowGrid")));
        checkBoxShowGrid->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_1->addWidget(checkBoxShowGrid, 0, 0, 1, 1);

        checkBoxGridAuto = new Gui::PrefCheckBox(groupBox_1);
        checkBoxGridAuto->setObjectName("checkBoxGridAuto");
        checkBoxGridAuto->setChecked(true);
        checkBoxGridAuto->setProperty("prefEntry", QVariant(QByteArray("GridAuto")));
        checkBoxGridAuto->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_1->addWidget(checkBoxGridAuto, 1, 0, 1, 1);

        label_gridSize = new QLabel(groupBox_1);
        label_gridSize->setObjectName("label_gridSize");

        QGridLayout_1->addWidget(label_gridSize, 2, 0, 1, 1);

        gridSize = new Gui::PrefQuantitySpinBox(groupBox_1);
        gridSize->setObjectName("gridSize");
        gridSize->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        gridSize->setMinimum(0.001000000000000);
        gridSize->setMaximum(99999999.000000000000000);
        gridSize->setSingleStep(1.000000000000000);
        gridSize->setValue(10.000000000000000);
        gridSize->setProperty("prefEntry", QVariant(QByteArray("GridSize")));
        gridSize->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General/GridSize")));
        gridSize->setProperty("decimals", QVariant(3));

        QGridLayout_1->addWidget(gridSize, 2, 1, 1, 1);

        label_gridSizePixelThreshold = new QLabel(groupBox_1);
        label_gridSizePixelThreshold->setObjectName("label_gridSizePixelThreshold");

        QGridLayout_1->addWidget(label_gridSizePixelThreshold, 3, 0, 1, 1);

        gridSizePixelThreshold = new Gui::PrefSpinBox(groupBox_1);
        gridSizePixelThreshold->setObjectName("gridSizePixelThreshold");
        gridSizePixelThreshold->setSuffix(QString::fromUtf8(" px"));
        gridSizePixelThreshold->setMinimum(3);
        gridSizePixelThreshold->setMaximum(10000);
        gridSizePixelThreshold->setValue(15);
        gridSizePixelThreshold->setProperty("prefEntry", QVariant(QByteArray("GridSizePixelThreshold")));
        gridSizePixelThreshold->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_1->addWidget(gridSizePixelThreshold, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBox_1);

        groupBox_2 = new QGroupBox(SketcherGui__SketcherSettingsGrid);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayoutDisplay = new QGridLayout(groupBox_2);
        gridLayoutDisplay->setObjectName("gridLayoutDisplay");
        label_gridTransparency = new QLabel(groupBox_2);
        label_gridTransparency->setObjectName("label_gridTransparency");

        gridLayoutDisplay->addWidget(label_gridTransparency, 0, 0, 1, 1);

        gridTransparency = new Gui::PrefSpinBox(groupBox_2);
        gridTransparency->setObjectName("gridTransparency");
        gridTransparency->setSuffix(QString::fromUtf8(" %"));
        gridTransparency->setMinimum(0);
        gridTransparency->setMaximum(100);
        gridTransparency->setValue(60);
        gridTransparency->setProperty("prefEntry", QVariant(QByteArray("GridTransparency")));
        gridTransparency->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        gridLayoutDisplay->addWidget(gridTransparency, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        QGridLayout_2 = new QGridLayout(groupBox_3);
        QGridLayout_2->setObjectName("QGridLayout_2");
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");

        QGridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        gridLinePattern = new QComboBox(groupBox_3);
        gridLinePattern->setObjectName("gridLinePattern");
        gridLinePattern->setProperty("prefEntry", QVariant(QByteArray("GridLinePattern")));
        gridLinePattern->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_2->addWidget(gridLinePattern, 0, 1, 1, 1);

        label_gridLineWidth = new QLabel(groupBox_3);
        label_gridLineWidth->setObjectName("label_gridLineWidth");

        QGridLayout_2->addWidget(label_gridLineWidth, 1, 0, 1, 1);

        gridLineWidth = new Gui::PrefSpinBox(groupBox_3);
        gridLineWidth->setObjectName("gridLineWidth");
        gridLineWidth->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        gridLineWidth->setMinimum(1);
        gridLineWidth->setMaximum(99);
        gridLineWidth->setValue(1);
        gridLineWidth->setProperty("prefEntry", QVariant(QByteArray("GridLineWidth")));
        gridLineWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_2->addWidget(gridLineWidth, 1, 1, 1, 1);

        label_gridLineColor = new QLabel(groupBox_3);
        label_gridLineColor->setObjectName("label_gridLineColor");

        QGridLayout_2->addWidget(label_gridLineColor, 2, 0, 1, 1);

        gridLineColor = new Gui::PrefColorButton(groupBox_3);
        gridLineColor->setObjectName("gridLineColor");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gridLineColor->sizePolicy().hasHeightForWidth());
        gridLineColor->setSizePolicy(sizePolicy1);
        gridLineColor->setColor(QColor(178, 178, 178));
        gridLineColor->setProperty("prefEntry", QVariant(QByteArray("GridLineColor")));
        gridLineColor->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_2->addWidget(gridLineColor, 2, 1, 1, 1);


        gridLayoutDisplay->addWidget(groupBox_3, 1, 0, 1, 2);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName("groupBox_4");
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        QGridLayout_3 = new QGridLayout(groupBox_4);
        QGridLayout_3->setObjectName("QGridLayout_3");
        label_gridNumberSubdivision = new QLabel(groupBox_4);
        label_gridNumberSubdivision->setObjectName("label_gridNumberSubdivision");

        QGridLayout_3->addWidget(label_gridNumberSubdivision, 0, 0, 1, 1);

        gridNumberSubdivision = new Gui::PrefSpinBox(groupBox_4);
        gridNumberSubdivision->setObjectName("gridNumberSubdivision");
        gridNumberSubdivision->setMinimum(1);
        gridNumberSubdivision->setMaximum(10000);
        gridNumberSubdivision->setValue(10);
        gridNumberSubdivision->setProperty("prefEntry", QVariant(QByteArray("GridNumberSubdivision")));
        gridNumberSubdivision->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_3->addWidget(gridNumberSubdivision, 0, 1, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName("label_22");

        QGridLayout_3->addWidget(label_22, 1, 0, 1, 1);

        gridDivLinePattern = new QComboBox(groupBox_4);
        gridDivLinePattern->setObjectName("gridDivLinePattern");

        QGridLayout_3->addWidget(gridDivLinePattern, 1, 1, 1, 1);

        label_gridDivLineWidth = new QLabel(groupBox_4);
        label_gridDivLineWidth->setObjectName("label_gridDivLineWidth");

        QGridLayout_3->addWidget(label_gridDivLineWidth, 2, 0, 1, 1);

        gridDivLineWidth = new Gui::PrefSpinBox(groupBox_4);
        gridDivLineWidth->setObjectName("gridDivLineWidth");
        gridDivLineWidth->setMinimum(1);
        gridDivLineWidth->setMaximum(99);
        gridDivLineWidth->setValue(2);
        gridDivLineWidth->setProperty("prefEntry", QVariant(QByteArray("GridDivLineWidth")));
        gridDivLineWidth->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_3->addWidget(gridDivLineWidth, 2, 1, 1, 1);

        label_gridDivLineColor = new QLabel(groupBox_4);
        label_gridDivLineColor->setObjectName("label_gridDivLineColor");

        QGridLayout_3->addWidget(label_gridDivLineColor, 3, 0, 1, 1);

        gridDivLineColor = new Gui::PrefColorButton(groupBox_4);
        gridDivLineColor->setObjectName("gridDivLineColor");
        sizePolicy1.setHeightForWidth(gridDivLineColor->sizePolicy().hasHeightForWidth());
        gridDivLineColor->setSizePolicy(sizePolicy1);
        gridDivLineColor->setColor(QColor(178, 178, 178));
        gridDivLineColor->setProperty("prefEntry", QVariant(QByteArray("GridDivLineColor")));
        gridDivLineColor->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        QGridLayout_3->addWidget(gridDivLineColor, 3, 1, 1, 1);


        gridLayoutDisplay->addWidget(groupBox_4, 2, 0, 1, 2);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

#if QT_CONFIG(shortcut)
        label_gridSize->setBuddy(gridSize);
        label_gridSizePixelThreshold->setBuddy(gridNumberSubdivision);
        label_2->setBuddy(gridLinePattern);
        label_gridLineWidth->setBuddy(gridLineWidth);
        label_gridLineColor->setBuddy(gridLineColor);
        label_gridNumberSubdivision->setBuddy(gridNumberSubdivision);
        label_22->setBuddy(gridDivLinePattern);
        label_gridDivLineWidth->setBuddy(gridDivLineWidth);
        label_gridDivLineColor->setBuddy(gridDivLineColor);
#endif // QT_CONFIG(shortcut)

        retranslateUi(SketcherGui__SketcherSettingsGrid);

        gridLinePattern->setCurrentIndex(-1);
        gridDivLinePattern->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SketcherGui__SketcherSettingsGrid);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__SketcherSettingsGrid)
    {
        SketcherGui__SketcherSettingsGrid->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid Settings", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxShowGrid->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Displays a grid in the active sketch", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxShowGrid->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxGridAuto->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Automatically adapts grid spacing based on the viewer dimensions", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxGridAuto->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid auto-spacing", nullptr));
        label_gridSize->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid spacing", nullptr));
#if QT_CONFIG(tooltip)
        gridSize->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Distance between two subsequent grid lines.\n"
"If 'Grid auto-apacing' is enabled, it will be used as the base value", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gridSizePixelThreshold->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Pixel size threshold", nullptr));
#if QT_CONFIG(tooltip)
        gridSizePixelThreshold->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "While using 'Grid auto-spacing', this sets a pixel threshold for grid spacing.\n"
"The grid spacing changes if it becomes smaller than the specified pixel size.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_2->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid Display", nullptr));
        label_gridTransparency->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Grid transparency", nullptr));
#if QT_CONFIG(tooltip)
        gridTransparency->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Sets the transparency of the grid lines (0 = opaque, 100 = fully transparent)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Minor Grid Lines", nullptr));
        label_2->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line pattern", nullptr));
#if QT_CONFIG(tooltip)
        gridLinePattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line pattern used for grid lines", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gridLineWidth->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line width", nullptr));
#if QT_CONFIG(tooltip)
        gridLineWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Minor grid line width in pixels", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gridLineColor->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line color", nullptr));
        gridLineColor->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Major Grid Lines", nullptr));
        label_gridNumberSubdivision->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Major grid line interval", nullptr));
#if QT_CONFIG(tooltip)
        gridNumberSubdivision->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Displays a major grid line every 'n' minor lines. Enter 1 to disable major lines", nullptr));
#endif // QT_CONFIG(tooltip)
        label_22->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line pattern", nullptr));
#if QT_CONFIG(tooltip)
        gridDivLinePattern->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line pattern used for grid division", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gridDivLineWidth->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line width", nullptr));
#if QT_CONFIG(tooltip)
        gridDivLineWidth->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Major grid line width in pixels", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gridDivLineColor->setText(QCoreApplication::translate("SketcherGui::SketcherSettingsGrid", "Line color", nullptr));
        gridDivLineColor->setText(QString());
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherSettingsGrid: public Ui_SketcherSettingsGrid {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERSETTINGSGRID_H
