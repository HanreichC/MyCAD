/********************************************************************************
** Form generated from reading UI file 'DlgSettingsGeneral.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSGENERAL_H
#define UI_DLGSETTINGSGENERAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace PartGui {

class Ui_DlgSettingsGeneral
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    Gui::PrefCheckBox *checkBooleanCheck;
    Gui::PrefCheckBox *checkBooleanRefine;
    Gui::PrefCheckBox *checkSketchBaseRefine;
    Gui::PrefCheckBox *checkAllowCompoundBody;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    Gui::PrefCheckBox *checkObjectNaming;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    Gui::PrefComboBox *comboDefaultProfileTypeForHole;
    Gui::PrefCheckBox *checkSwitchToTask;
    Gui::PrefCheckBox *checkNewSketchAttachmentDialog;
    QGroupBox *groupBoxPreview;
    QVBoxLayout *verticalLayout_31;
    Gui::PrefCheckBox *checkShowFinalPreview;
    Gui::PrefCheckBox *checkShowTransparentPreview;
    Gui::PrefCheckBox *checkShowProfilePreview;
    QGroupBox *groupBoxExperimental;
    QVBoxLayout *verticalLayout_2;
    QLabel *warningLabel;
    Gui::PrefCheckBox *enableGizmos;
    Gui::PrefCheckBox *delayedGizmoUpdate;
    Gui::PrefCheckBox *enableCoarseSnap;
    QHBoxLayout *horizontalLayoutFineSnapModifier;
    QLabel *labelFineSnapModifier;
    Gui::PrefComboBox *fineSnapModifier;
    QHBoxLayout *horizontalLayoutDefaultCoarseDragBehavior;
    QLabel *labelDefaultCoarseDragBehavior;
    Gui::PrefComboBox *defaultCoarseDragBehavior;
    QHBoxLayout *horizontalLayoutCoarseLinearSnapMultiplier;
    QLabel *labelCoarseLinearSnapMultiplier;
    Gui::PrefSpinBox *coarseLinearSnapMultiplier;
    QHBoxLayout *horizontalLayoutCoarseRotationSnapMultiplier;
    QLabel *labelCoarseRotationSnapMultiplier;
    Gui::PrefSpinBox *coarseRotationSnapMultiplier;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *PartGui__DlgSettingsGeneral)
    {
        if (PartGui__DlgSettingsGeneral->objectName().isEmpty())
            PartGui__DlgSettingsGeneral->setObjectName("PartGui__DlgSettingsGeneral");
        PartGui__DlgSettingsGeneral->setMinimumSize(QSize(400, 500));
        verticalLayout = new QVBoxLayout(PartGui__DlgSettingsGeneral);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_2 = new QGroupBox(PartGui__DlgSettingsGeneral);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        checkBooleanCheck = new Gui::PrefCheckBox(groupBox_2);
        checkBooleanCheck->setObjectName("checkBooleanCheck");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBooleanCheck->sizePolicy().hasHeightForWidth());
        checkBooleanCheck->setSizePolicy(sizePolicy);
        checkBooleanCheck->setChecked(true);
        checkBooleanCheck->setProperty("prefEntry", QVariant(QByteArray("CheckModel")));
        checkBooleanCheck->setProperty("prefPath", QVariant(QByteArray("Mod/Part/Boolean")));

        gridLayout->addWidget(checkBooleanCheck, 0, 0, 1, 1);

        checkBooleanRefine = new Gui::PrefCheckBox(groupBox_2);
        checkBooleanRefine->setObjectName("checkBooleanRefine");
        sizePolicy.setHeightForWidth(checkBooleanRefine->sizePolicy().hasHeightForWidth());
        checkBooleanRefine->setSizePolicy(sizePolicy);
        checkBooleanRefine->setChecked(true);
        checkBooleanRefine->setProperty("prefEntry", QVariant(QByteArray("RefineModel")));
        checkBooleanRefine->setProperty("prefPath", QVariant(QByteArray("Mod/Part/Boolean")));

        gridLayout->addWidget(checkBooleanRefine, 1, 0, 1, 1);

        checkSketchBaseRefine = new Gui::PrefCheckBox(groupBox_2);
        checkSketchBaseRefine->setObjectName("checkSketchBaseRefine");
        sizePolicy.setHeightForWidth(checkSketchBaseRefine->sizePolicy().hasHeightForWidth());
        checkSketchBaseRefine->setSizePolicy(sizePolicy);
        checkSketchBaseRefine->setChecked(true);
        checkSketchBaseRefine->setProperty("prefEntry", QVariant(QByteArray("RefineModel")));
        checkSketchBaseRefine->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign")));

        gridLayout->addWidget(checkSketchBaseRefine, 2, 0, 1, 1);

        checkAllowCompoundBody = new Gui::PrefCheckBox(groupBox_2);
        checkAllowCompoundBody->setObjectName("checkAllowCompoundBody");
        sizePolicy.setHeightForWidth(checkAllowCompoundBody->sizePolicy().hasHeightForWidth());
        checkAllowCompoundBody->setSizePolicy(sizePolicy);
        checkAllowCompoundBody->setChecked(true);
        checkAllowCompoundBody->setProperty("prefEntry", QVariant(QByteArray("AllowCompoundDefault")));
        checkAllowCompoundBody->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign")));

        gridLayout->addWidget(checkAllowCompoundBody, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(PartGui__DlgSettingsGeneral);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setEnabled(true);
        groupBox_3->setVisible(false);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName("gridLayout_2");
        checkObjectNaming = new Gui::PrefCheckBox(groupBox_3);
        checkObjectNaming->setObjectName("checkObjectNaming");
        sizePolicy.setHeightForWidth(checkObjectNaming->sizePolicy().hasHeightForWidth());
        checkObjectNaming->setSizePolicy(sizePolicy);
        checkObjectNaming->setProperty("prefEntry", QVariant(QByteArray("AddBaseObjectName")));
        checkObjectNaming->setProperty("prefPath", QVariant(QByteArray("Mod/Part")));

        gridLayout_2->addWidget(checkObjectNaming, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(PartGui__DlgSettingsGeneral);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label);

        comboDefaultProfileTypeForHole = new Gui::PrefComboBox(groupBox);
        comboDefaultProfileTypeForHole->addItem(QString());
        comboDefaultProfileTypeForHole->addItem(QString());
        comboDefaultProfileTypeForHole->addItem(QString());
        comboDefaultProfileTypeForHole->setObjectName("comboDefaultProfileTypeForHole");
        sizePolicy.setHeightForWidth(comboDefaultProfileTypeForHole->sizePolicy().hasHeightForWidth());
        comboDefaultProfileTypeForHole->setSizePolicy(sizePolicy);
        comboDefaultProfileTypeForHole->setProperty("prefEntry", QVariant(QByteArray("defaultBaseTypeHole")));
        comboDefaultProfileTypeForHole->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign")));

        horizontalLayout_2->addWidget(comboDefaultProfileTypeForHole);


        verticalLayout_4->addLayout(horizontalLayout_2);

        checkSwitchToTask = new Gui::PrefCheckBox(groupBox);
        checkSwitchToTask->setObjectName("checkSwitchToTask");
        sizePolicy.setHeightForWidth(checkSwitchToTask->sizePolicy().hasHeightForWidth());
        checkSwitchToTask->setSizePolicy(sizePolicy);
        checkSwitchToTask->setChecked(true);
        checkSwitchToTask->setProperty("prefEntry", QVariant(QByteArray("SwitchToTask")));
        checkSwitchToTask->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign")));

        verticalLayout_4->addWidget(checkSwitchToTask);

        checkNewSketchAttachmentDialog = new Gui::PrefCheckBox(groupBox);
        checkNewSketchAttachmentDialog->setObjectName("checkNewSketchAttachmentDialog");
        sizePolicy.setHeightForWidth(checkNewSketchAttachmentDialog->sizePolicy().hasHeightForWidth());
        checkNewSketchAttachmentDialog->setSizePolicy(sizePolicy);
        checkNewSketchAttachmentDialog->setChecked(false);
        checkNewSketchAttachmentDialog->setProperty("prefEntry", QVariant(QByteArray("NewSketchUseAttachmentDialog")));
        checkNewSketchAttachmentDialog->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign")));

        verticalLayout_4->addWidget(checkNewSketchAttachmentDialog);


        verticalLayout->addWidget(groupBox);

        groupBoxPreview = new QGroupBox(PartGui__DlgSettingsGeneral);
        groupBoxPreview->setObjectName("groupBoxPreview");
        verticalLayout_31 = new QVBoxLayout(groupBoxPreview);
        verticalLayout_31->setObjectName("verticalLayout_31");
        checkShowFinalPreview = new Gui::PrefCheckBox(groupBoxPreview);
        checkShowFinalPreview->setObjectName("checkShowFinalPreview");
        sizePolicy.setHeightForWidth(checkShowFinalPreview->sizePolicy().hasHeightForWidth());
        checkShowFinalPreview->setSizePolicy(sizePolicy);
        checkShowFinalPreview->setProperty("prefEntry", QVariant(QByteArray("ShowFinal")));
        checkShowFinalPreview->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign/Preview")));

        verticalLayout_31->addWidget(checkShowFinalPreview);

        checkShowTransparentPreview = new Gui::PrefCheckBox(groupBoxPreview);
        checkShowTransparentPreview->setObjectName("checkShowTransparentPreview");
        sizePolicy.setHeightForWidth(checkShowTransparentPreview->sizePolicy().hasHeightForWidth());
        checkShowTransparentPreview->setSizePolicy(sizePolicy);
        checkShowTransparentPreview->setChecked(true);
        checkShowTransparentPreview->setProperty("prefEntry", QVariant(QByteArray("ShowTransparentPreview")));
        checkShowTransparentPreview->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign/Preview")));

        verticalLayout_31->addWidget(checkShowTransparentPreview);

        checkShowProfilePreview = new Gui::PrefCheckBox(groupBoxPreview);
        checkShowProfilePreview->setObjectName("checkShowProfilePreview");
        sizePolicy.setHeightForWidth(checkShowProfilePreview->sizePolicy().hasHeightForWidth());
        checkShowProfilePreview->setSizePolicy(sizePolicy);
        checkShowProfilePreview->setChecked(true);
        checkShowProfilePreview->setProperty("prefEntry", QVariant(QByteArray("ShowProfilePreview")));
        checkShowProfilePreview->setProperty("prefPath", QVariant(QByteArray("Mod/PartDesign/Preview")));

        verticalLayout_31->addWidget(checkShowProfilePreview);


        verticalLayout->addWidget(groupBoxPreview);

        groupBoxExperimental = new QGroupBox(PartGui__DlgSettingsGeneral);
        groupBoxExperimental->setObjectName("groupBoxExperimental");
        verticalLayout_2 = new QVBoxLayout(groupBoxExperimental);
        verticalLayout_2->setObjectName("verticalLayout_2");
        warningLabel = new QLabel(groupBoxExperimental);
        warningLabel->setObjectName("warningLabel");
        warningLabel->setWordWrap(true);

        verticalLayout_2->addWidget(warningLabel);

        enableGizmos = new Gui::PrefCheckBox(groupBoxExperimental);
        enableGizmos->setObjectName("enableGizmos");
        sizePolicy.setHeightForWidth(enableGizmos->sizePolicy().hasHeightForWidth());
        enableGizmos->setSizePolicy(sizePolicy);
        enableGizmos->setChecked(true);
        enableGizmos->setProperty("prefEntry", QVariant(QByteArray("EnableGizmos")));
        enableGizmos->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));

        verticalLayout_2->addWidget(enableGizmos);

        delayedGizmoUpdate = new Gui::PrefCheckBox(groupBoxExperimental);
        delayedGizmoUpdate->setObjectName("delayedGizmoUpdate");
        sizePolicy.setHeightForWidth(delayedGizmoUpdate->sizePolicy().hasHeightForWidth());
        delayedGizmoUpdate->setSizePolicy(sizePolicy);
        delayedGizmoUpdate->setProperty("prefEntry", QVariant(QByteArray("DelayedGizmoUpdate")));
        delayedGizmoUpdate->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));

        verticalLayout_2->addWidget(delayedGizmoUpdate);

        enableCoarseSnap = new Gui::PrefCheckBox(groupBoxExperimental);
        enableCoarseSnap->setObjectName("enableCoarseSnap");
        enableCoarseSnap->setChecked(true);
        enableCoarseSnap->setProperty("prefEntry", QVariant(QByteArray("EnableCoarseSnap")));
        enableCoarseSnap->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));

        verticalLayout_2->addWidget(enableCoarseSnap);

        horizontalLayoutFineSnapModifier = new QHBoxLayout();
        horizontalLayoutFineSnapModifier->setObjectName("horizontalLayoutFineSnapModifier");
        labelFineSnapModifier = new QLabel(groupBoxExperimental);
        labelFineSnapModifier->setObjectName("labelFineSnapModifier");

        horizontalLayoutFineSnapModifier->addWidget(labelFineSnapModifier);

        fineSnapModifier = new Gui::PrefComboBox(groupBoxExperimental);
        fineSnapModifier->setObjectName("fineSnapModifier");
        fineSnapModifier->setProperty("prefEntry", QVariant(QByteArray("FineSnapModifier")));
        fineSnapModifier->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));
        fineSnapModifier->setProperty("prefType", QVariant(0));

        horizontalLayoutFineSnapModifier->addWidget(fineSnapModifier);


        verticalLayout_2->addLayout(horizontalLayoutFineSnapModifier);

        horizontalLayoutDefaultCoarseDragBehavior = new QHBoxLayout();
        horizontalLayoutDefaultCoarseDragBehavior->setObjectName("horizontalLayoutDefaultCoarseDragBehavior");
        labelDefaultCoarseDragBehavior = new QLabel(groupBoxExperimental);
        labelDefaultCoarseDragBehavior->setObjectName("labelDefaultCoarseDragBehavior");

        horizontalLayoutDefaultCoarseDragBehavior->addWidget(labelDefaultCoarseDragBehavior);

        defaultCoarseDragBehavior = new Gui::PrefComboBox(groupBoxExperimental);
        defaultCoarseDragBehavior->setObjectName("defaultCoarseDragBehavior");
        defaultCoarseDragBehavior->setProperty("prefEntry", QVariant(QByteArray("DefaultCoarseDragBehavior")));
        defaultCoarseDragBehavior->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));
        defaultCoarseDragBehavior->setProperty("prefType", QVariant(0));

        horizontalLayoutDefaultCoarseDragBehavior->addWidget(defaultCoarseDragBehavior);


        verticalLayout_2->addLayout(horizontalLayoutDefaultCoarseDragBehavior);

        horizontalLayoutCoarseLinearSnapMultiplier = new QHBoxLayout();
        horizontalLayoutCoarseLinearSnapMultiplier->setObjectName("horizontalLayoutCoarseLinearSnapMultiplier");
        labelCoarseLinearSnapMultiplier = new QLabel(groupBoxExperimental);
        labelCoarseLinearSnapMultiplier->setObjectName("labelCoarseLinearSnapMultiplier");

        horizontalLayoutCoarseLinearSnapMultiplier->addWidget(labelCoarseLinearSnapMultiplier);

        coarseLinearSnapMultiplier = new Gui::PrefSpinBox(groupBoxExperimental);
        coarseLinearSnapMultiplier->setObjectName("coarseLinearSnapMultiplier");
        coarseLinearSnapMultiplier->setMinimum(1);
        coarseLinearSnapMultiplier->setMaximum(100);
        coarseLinearSnapMultiplier->setValue(5);
        coarseLinearSnapMultiplier->setProperty("prefEntry", QVariant(QByteArray("CoarseLinearSnapMultiplier")));
        coarseLinearSnapMultiplier->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));

        horizontalLayoutCoarseLinearSnapMultiplier->addWidget(coarseLinearSnapMultiplier);


        verticalLayout_2->addLayout(horizontalLayoutCoarseLinearSnapMultiplier);

        horizontalLayoutCoarseRotationSnapMultiplier = new QHBoxLayout();
        horizontalLayoutCoarseRotationSnapMultiplier->setObjectName("horizontalLayoutCoarseRotationSnapMultiplier");
        labelCoarseRotationSnapMultiplier = new QLabel(groupBoxExperimental);
        labelCoarseRotationSnapMultiplier->setObjectName("labelCoarseRotationSnapMultiplier");

        horizontalLayoutCoarseRotationSnapMultiplier->addWidget(labelCoarseRotationSnapMultiplier);

        coarseRotationSnapMultiplier = new Gui::PrefSpinBox(groupBoxExperimental);
        coarseRotationSnapMultiplier->setObjectName("coarseRotationSnapMultiplier");
        coarseRotationSnapMultiplier->setMinimum(1);
        coarseRotationSnapMultiplier->setMaximum(100);
        coarseRotationSnapMultiplier->setValue(5);
        coarseRotationSnapMultiplier->setProperty("prefEntry", QVariant(QByteArray("CoarseRotationSnapMultiplier")));
        coarseRotationSnapMultiplier->setProperty("prefPath", QVariant(QByteArray("Gui/Gizmos")));

        horizontalLayoutCoarseRotationSnapMultiplier->addWidget(coarseRotationSnapMultiplier);


        verticalLayout_2->addLayout(horizontalLayoutCoarseRotationSnapMultiplier);


        verticalLayout->addWidget(groupBoxExperimental);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerItem);


        retranslateUi(PartGui__DlgSettingsGeneral);

        comboDefaultProfileTypeForHole->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PartGui__DlgSettingsGeneral);
    } // setupUi

    void retranslateUi(QWidget *PartGui__DlgSettingsGeneral)
    {
        PartGui__DlgSettingsGeneral->setWindowTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "General", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Model Settings", nullptr));
        checkBooleanCheck->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Automatically check model after boolean operation", nullptr));
#if QT_CONFIG(tooltip)
        checkBooleanCheck->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Validates the geometry (BRep) after every boolean operation to detect errors. Note: This may slow down performance on complex models.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBooleanRefine->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Automatic refinement of Part Boolean results", nullptr));
#if QT_CONFIG(tooltip)
        checkBooleanRefine->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Refines Part Boolean results by removing redundant edges and merging adjacent faces", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSketchBaseRefine->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Automatic refinement of Part Design features", nullptr));
#if QT_CONFIG(tooltip)
        checkSketchBaseRefine->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Refines Part Design features after creation by removing unnecessary edges", nullptr));
#endif // QT_CONFIG(tooltip)
        checkAllowCompoundBody->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Allow multiple solids in Part Design bodies by default", nullptr));
#if QT_CONFIG(tooltip)
        checkAllowCompoundBody->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Sets new bodies to allow multiple disconnected solids (compounds). If unchecked, a body is strictly limited to a single contiguous solid.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Object Naming", nullptr));
#if QT_CONFIG(tooltip)
        checkObjectNaming->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Currently not implemented: this option does not yet modify automatically generated Part feature names", nullptr));
#endif // QT_CONFIG(tooltip)
        checkObjectNaming->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Add name of base object", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Features Settings", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Specifies which profile geometry types are accepted by the Part Design Hole feature", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Default profile type for holes", nullptr));
        comboDefaultProfileTypeForHole->setItemText(0, QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Circles and arcs", nullptr));
        comboDefaultProfileTypeForHole->setItemText(1, QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Points, circles and arcs", nullptr));
        comboDefaultProfileTypeForHole->setItemText(2, QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Points", nullptr));

#if QT_CONFIG(tooltip)
        comboDefaultProfileTypeForHole->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Specifies which sketch elements (points, circles, or arcs) the Hole tool should automatically detect and use as hole centers", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkSwitchToTask->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Automatically switch to the task panel when the Part Design workbench is activated", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSwitchToTask->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Switch to task panel when entering Part Design workbench", nullptr));
#if QT_CONFIG(tooltip)
        checkNewSketchAttachmentDialog->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Always open the attachment dialog when creating a new sketch in Part Design, regardless of selection or holding the Shift key. Without this, only a single face or datum plane selection skips the dialog.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkNewSketchAttachmentDialog->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Always open attachment dialog for new sketches", nullptr));
        groupBoxPreview->setTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Preview", nullptr));
        checkShowFinalPreview->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Show final result by default when editing features", nullptr));
#if QT_CONFIG(tooltip)
        checkShowFinalPreview->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Displays the fully computed model in the 3D view while editing a feature, showing the final context rather than just the isolated feature", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowTransparentPreview->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Show transparent preview overlay by default when editing features", nullptr));
#if QT_CONFIG(tooltip)
        checkShowTransparentPreview->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Overlays a semi-transparent preview of the result while editing features to visualize changes before they are applied", nullptr));
#endif // QT_CONFIG(tooltip)
        checkShowProfilePreview->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Highlight the profile used to create features", nullptr));
#if QT_CONFIG(tooltip)
        checkShowProfilePreview->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Visually highlights the source sketch or geometry used to generate the feature currently being edited", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBoxExperimental->setTitle(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Experimental", nullptr));
        warningLabel->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "These settings are experimental and may result in decreased stability, problems and undefined behaviors", nullptr));
        enableGizmos->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Show interactive draggers when editing features", nullptr));
#if QT_CONFIG(tooltip)
        enableGizmos->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Enables on-screen handles (draggers) in the 3D view for interactively modifying dimensions and parameters of the feature being edited by dragging", nullptr));
#endif // QT_CONFIG(tooltip)
        delayedGizmoUpdate->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Disable recompute while dragging", nullptr));
#if QT_CONFIG(tooltip)
        delayedGizmoUpdate->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Prevents the model from recalculating while manipulating draggers. The shape updates only after release of the mouse button.", nullptr));
#endif // QT_CONFIG(tooltip)
        enableCoarseSnap->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Enable coarse snapping while dragging", nullptr));
#if QT_CONFIG(tooltip)
        enableCoarseSnap->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Enables larger snapping increments while  manipulating draggers", nullptr));
#endif // QT_CONFIG(tooltip)
        labelFineSnapModifier->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Fine snap modifier", nullptr));
#if QT_CONFIG(tooltip)
        fineSnapModifier->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Defines the modifier key used for fine snapping while dragging", nullptr));
#endif // QT_CONFIG(tooltip)
        labelDefaultCoarseDragBehavior->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Default coarse drag behavior", nullptr));
#if QT_CONFIG(tooltip)
        defaultCoarseDragBehavior->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Determines whether the drag is coarse or fine without holding the modifier key", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCoarseLinearSnapMultiplier->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Coarse movement multiplier", nullptr));
#if QT_CONFIG(tooltip)
        coarseLinearSnapMultiplier->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Multiplies the base movement increment when coarse snapping is active", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCoarseRotationSnapMultiplier->setText(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Coarse rotation step (degrees)", nullptr));
#if QT_CONFIG(tooltip)
        coarseRotationSnapMultiplier->setToolTip(QCoreApplication::translate("PartGui::DlgSettingsGeneral", "Sets the rotation step in degrees applied when coarse snapping is active", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class DlgSettingsGeneral: public Ui_DlgSettingsGeneral {};
} // namespace Ui
} // namespace PartGui

#endif // UI_DLGSETTINGSGENERAL_H
