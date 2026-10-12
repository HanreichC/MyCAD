/********************************************************************************
** Form generated from reading UI file 'SketcherSettings.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERSETTINGS_H
#define UI_SKETCHERSETTINGS_H

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

namespace SketcherGui {

class Ui_SketcherSettings
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    Gui::PrefCheckBox *checkBoxAdvancedSolverTaskBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    Gui::PrefCheckBox *checkBoxRecalculateInitialSolutionWhileDragging;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_22;
    Gui::PrefCheckBox *checkBoxAutoRemoveRedundants;
    Gui::PrefCheckBox *checkBoxEnableEscape;
    Gui::PrefCheckBox *checkBoxNotifyConstraintSubstitutions;
    Gui::PrefCheckBox *checkBoxUnifiedCoincident;
    Gui::PrefCheckBox *checkBoxHorVerAuto;
    Gui::PrefCheckBox *checkBoxLineGroup;
    Gui::PrefCheckBox *checkBoxAddExtGeo;
    Gui::PrefCheckBox *checkBoxMakeInternals;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_general;
    QComboBox *radiusDiameterMode;
    QComboBox *dimensioningMode;
    QLabel *radiusDiameterLabel;
    QLabel *dimensioningLabel;
    QLabel *autoScaleModeLabel;
    QComboBox *autoScaleMode;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_vis;
    QLabel *ovpVisibilityLabel;
    QComboBox *ovpVisibility;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SketcherGui__SketcherSettings)
    {
        if (SketcherGui__SketcherSettings->objectName().isEmpty())
            SketcherGui__SketcherSettings->setObjectName("SketcherGui__SketcherSettings");
        SketcherGui__SketcherSettings->resize(500, 661);
        gridLayout = new QGridLayout(SketcherGui__SketcherSettings);
        gridLayout->setObjectName("gridLayout");
        groupBox_2 = new QGroupBox(SketcherGui__SketcherSettings);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName("gridLayout_4");
        checkBoxAdvancedSolverTaskBox = new Gui::PrefCheckBox(groupBox_2);
        checkBoxAdvancedSolverTaskBox->setObjectName("checkBoxAdvancedSolverTaskBox");
        checkBoxAdvancedSolverTaskBox->setProperty("prefEntry", QVariant(QByteArray("ShowSolverAdvancedWidget")));
        checkBoxAdvancedSolverTaskBox->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_4->addWidget(checkBoxAdvancedSolverTaskBox, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(SketcherGui__SketcherSettings);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName("gridLayout_5");
        checkBoxRecalculateInitialSolutionWhileDragging = new Gui::PrefCheckBox(groupBox_4);
        checkBoxRecalculateInitialSolutionWhileDragging->setObjectName("checkBoxRecalculateInitialSolutionWhileDragging");
        checkBoxRecalculateInitialSolutionWhileDragging->setChecked(true);
        checkBoxRecalculateInitialSolutionWhileDragging->setProperty("prefEntry", QVariant(QByteArray("RecalculateInitialSolutionWhileDragging")));
        checkBoxRecalculateInitialSolutionWhileDragging->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        gridLayout_5->addWidget(checkBoxRecalculateInitialSolutionWhileDragging, 1, 0, 1, 2);


        gridLayout->addWidget(groupBox_4, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(SketcherGui__SketcherSettings);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMinimumSize(QSize(0, 0));
        groupBox_5->setMaximumSize(QSize(16777215, 16777215));
        groupBox_5->setBaseSize(QSize(0, 0));
        verticalLayout_22 = new QVBoxLayout(groupBox_5);
        verticalLayout_22->setObjectName("verticalLayout_22");
        checkBoxAutoRemoveRedundants = new Gui::PrefCheckBox(groupBox_5);
        checkBoxAutoRemoveRedundants->setObjectName("checkBoxAutoRemoveRedundants");
        checkBoxAutoRemoveRedundants->setChecked(false);
        checkBoxAutoRemoveRedundants->setProperty("prefEntry", QVariant(QByteArray("AutoRemoveRedundants")));
        checkBoxAutoRemoveRedundants->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        verticalLayout_22->addWidget(checkBoxAutoRemoveRedundants);

        checkBoxEnableEscape = new Gui::PrefCheckBox(groupBox_5);
        checkBoxEnableEscape->setObjectName("checkBoxEnableEscape");
        checkBoxEnableEscape->setChecked(true);
        checkBoxEnableEscape->setProperty("prefEntry", QVariant(QByteArray("LeaveSketchWithEscape")));
        checkBoxEnableEscape->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));

        verticalLayout_22->addWidget(checkBoxEnableEscape);

        checkBoxNotifyConstraintSubstitutions = new Gui::PrefCheckBox(groupBox_5);
        checkBoxNotifyConstraintSubstitutions->setObjectName("checkBoxNotifyConstraintSubstitutions");
        checkBoxNotifyConstraintSubstitutions->setChecked(true);
        checkBoxNotifyConstraintSubstitutions->setProperty("prefEntry", QVariant(QByteArray("NotifyConstraintSubstitutions")));
        checkBoxNotifyConstraintSubstitutions->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_22->addWidget(checkBoxNotifyConstraintSubstitutions);

        checkBoxUnifiedCoincident = new Gui::PrefCheckBox(groupBox_5);
        checkBoxUnifiedCoincident->setObjectName("checkBoxUnifiedCoincident");
        checkBoxUnifiedCoincident->setChecked(true);
        checkBoxUnifiedCoincident->setProperty("prefEntry", QVariant(QByteArray("UnifiedCoincident")));
        checkBoxUnifiedCoincident->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/Constraints")));

        verticalLayout_22->addWidget(checkBoxUnifiedCoincident);

        checkBoxHorVerAuto = new Gui::PrefCheckBox(groupBox_5);
        checkBoxHorVerAuto->setObjectName("checkBoxHorVerAuto");
        checkBoxHorVerAuto->setChecked(true);
        checkBoxHorVerAuto->setProperty("prefEntry", QVariant(QByteArray("AutoHorVer")));
        checkBoxHorVerAuto->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/Constraints")));

        verticalLayout_22->addWidget(checkBoxHorVerAuto);

        checkBoxLineGroup = new Gui::PrefCheckBox(groupBox_5);
        checkBoxLineGroup->setObjectName("checkBoxLineGroup");
        checkBoxLineGroup->setChecked(true);
        checkBoxLineGroup->setProperty("prefEntry", QVariant(QByteArray("UnifiedLineCommands")));
        checkBoxLineGroup->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/Commands")));

        verticalLayout_22->addWidget(checkBoxLineGroup);

        checkBoxAddExtGeo = new Gui::PrefCheckBox(groupBox_5);
        checkBoxAddExtGeo->setObjectName("checkBoxAddExtGeo");
        checkBoxAddExtGeo->setChecked(false);
        checkBoxAddExtGeo->setProperty("prefEntry", QVariant(QByteArray("AlwaysExtGeoReference")));
        checkBoxAddExtGeo->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher/General")));

        verticalLayout_22->addWidget(checkBoxAddExtGeo);

        checkBoxMakeInternals = new Gui::PrefCheckBox(groupBox_5);
        checkBoxMakeInternals->setObjectName("checkBoxMakeInternals");
        checkBoxMakeInternals->setChecked(true);
        checkBoxMakeInternals->setProperty("prefPath", QVariant(QByteArray("Mod/Sketcher")));
        checkBoxMakeInternals->setProperty("prefEntry", QVariant(QByteArray("MakeInternals")));

        verticalLayout_22->addWidget(checkBoxMakeInternals);


        gridLayout->addWidget(groupBox_5, 2, 0, 1, 1);

        groupBox_6 = new QGroupBox(SketcherGui__SketcherSettings);
        groupBox_6->setObjectName("groupBox_6");
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        gridLayout_general = new QGridLayout(groupBox_6);
        gridLayout_general->setObjectName("gridLayout_general");
        radiusDiameterMode = new QComboBox(groupBox_6);
        radiusDiameterMode->setObjectName("radiusDiameterMode");

        gridLayout_general->addWidget(radiusDiameterMode, 1, 1, 1, 1);

        dimensioningMode = new QComboBox(groupBox_6);
        dimensioningMode->setObjectName("dimensioningMode");

        gridLayout_general->addWidget(dimensioningMode, 0, 1, 1, 1);

        radiusDiameterLabel = new QLabel(groupBox_6);
        radiusDiameterLabel->setObjectName("radiusDiameterLabel");

        gridLayout_general->addWidget(radiusDiameterLabel, 1, 0, 1, 1);

        dimensioningLabel = new QLabel(groupBox_6);
        dimensioningLabel->setObjectName("dimensioningLabel");

        gridLayout_general->addWidget(dimensioningLabel, 0, 0, 1, 1);

        autoScaleModeLabel = new QLabel(groupBox_6);
        autoScaleModeLabel->setObjectName("autoScaleModeLabel");

        gridLayout_general->addWidget(autoScaleModeLabel, 2, 0, 1, 1);

        autoScaleMode = new QComboBox(groupBox_6);
        autoScaleMode->setObjectName("autoScaleMode");

        gridLayout_general->addWidget(autoScaleMode, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox_6, 3, 0, 1, 1);

        groupBox_7 = new QGroupBox(SketcherGui__SketcherSettings);
        groupBox_7->setObjectName("groupBox_7");
        sizePolicy.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy);
        gridLayout_vis = new QGridLayout(groupBox_7);
        gridLayout_vis->setObjectName("gridLayout_vis");
        ovpVisibilityLabel = new QLabel(groupBox_7);
        ovpVisibilityLabel->setObjectName("ovpVisibilityLabel");

        gridLayout_vis->addWidget(ovpVisibilityLabel, 0, 0, 1, 1);

        ovpVisibility = new QComboBox(groupBox_7);
        ovpVisibility->setObjectName("ovpVisibility");

        gridLayout_vis->addWidget(ovpVisibility, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_7, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        QWidget::setTabOrder(checkBoxAdvancedSolverTaskBox, checkBoxRecalculateInitialSolutionWhileDragging);
        QWidget::setTabOrder(checkBoxRecalculateInitialSolutionWhileDragging, checkBoxAutoRemoveRedundants);
        QWidget::setTabOrder(checkBoxAutoRemoveRedundants, checkBoxEnableEscape);
        QWidget::setTabOrder(checkBoxEnableEscape, checkBoxNotifyConstraintSubstitutions);

        retranslateUi(SketcherGui__SketcherSettings);

        QMetaObject::connectSlotsByName(SketcherGui__SketcherSettings);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__SketcherSettings)
    {
        SketcherGui__SketcherSettings->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "General", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "Task Panel Widgets", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAdvancedSolverTaskBox->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Displays the additional section 'Advanced Solver Controls' to adjust solver settings in the task view", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAdvancedSolverTaskBox->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Show section 'Advanced solver control'", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "Dragging Performance", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxRecalculateInitialSolutionWhileDragging->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Special solver algorithm will be used while dragging sketch elements.\n"
"Requires to re-enter edit mode to take effect.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxRecalculateInitialSolutionWhileDragging->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Improve solving while dragging", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "General", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAutoRemoveRedundants->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Automatically removes newly added redundant constraints", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAutoRemoveRedundants->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Auto remove redundant constraints", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxEnableEscape->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Allows to leave the sketch edit mode by pressing the Esc key", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxEnableEscape->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Esc key can leave sketch edit mode", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxNotifyConstraintSubstitutions->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Notifies about automatic constraint substitutions", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxNotifyConstraintSubstitutions->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Notify about automatic constraint substitutions", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxUnifiedCoincident->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Unifies the coincident and point-on-object constraints in a single tool", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxUnifiedCoincident->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Unify coincident and point-on-object constraints", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxHorVerAuto->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Unifies the horizontal and vertical constraints to an automatic command", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxHorVerAuto->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Unified tool for automatic horizontal/vertical constraints", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxLineGroup->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Shows a command group button that contains both the polyline and line commands. Otherwise, each command has its own separate button.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxLineGroup->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Group the polyline and line commands", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAddExtGeo->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Always adds external geometry as construction geometry. Otherwise, it is added according to the current construction mode.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAddExtGeo->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Always add external geometry as construction", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxMakeInternals->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Closed loops will automatically generate internal faces which are selectable to be used with other tools", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxMakeInternals->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Generate internal faces", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "Dimension Constraint", nullptr));
#if QT_CONFIG(tooltip)
        radiusDiameterMode->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "While using the Dimension tool you may choose how to handle circles and arcs:\n"
"'Auto': The tool will apply radius to arcs and diameter to circles.\n"
"'Diameter': The tool will apply diameter to both arcs and circles.\n"
"'Radius': The tool will apply radius to both arcs and circles.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        dimensioningMode->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Select the type of dimensioning constraints for your toolbar:\n"
"'Single tool': A single tool for all dimensioning constraints in the toolbar: Distance, Distance X / Y, Angle, Radius. (Others in dropdown)\n"
"'Separated tools': Individual tools for each dimensioning constraint.\n"
"'Both': You will have both the 'Dimension' tool and the separated tools.\n"
"This setting is only for the toolbar. Whichever you choose, all tools are always available in the menu and through shortcuts.", nullptr));
#endif // QT_CONFIG(tooltip)
        radiusDiameterLabel->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Dimension tool diameter/radius mode", nullptr));
        dimensioningLabel->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Dimensioning constraints", nullptr));
        autoScaleModeLabel->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "Scale upon first constraint", nullptr));
#if QT_CONFIG(tooltip)
        autoScaleMode->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Select the mode of automatic geometry scaling upon first dimension:\n"
"'Always': Automatic scaling upon first dimension is always performed.\n"
"'Never': Automatic scaling upon first dimension is never performed.\n"
"'When no scale feature is visible': Automatic scaling upon first dimension is only performed if there are no visible objects in the 3D view.\n"
"", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_7->setTitle(QCoreApplication::translate("SketcherGui::SketcherSettings", "Tool Parameters", nullptr));
        ovpVisibilityLabel->setText(QCoreApplication::translate("SketcherGui::SketcherSettings", "On-view-parameters (OVP)", nullptr));
#if QT_CONFIG(tooltip)
        ovpVisibility->setToolTip(QCoreApplication::translate("SketcherGui::SketcherSettings", "Choose a visibility mode for the On-View-Parameters:\n"
"'Disabled': On-View-Parameters are completely disabled.\n"
"'Dimensional only': Only dimensional On-View-Parameters are visible. They are the most useful. For example, the radius of a circle.\n"
"'All': Both dimensional and positional On-View-Parameters. Positionals are the (x,y) position of the cursor. For example for the center of a circle.", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherSettings: public Ui_SketcherSettings {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERSETTINGS_H
