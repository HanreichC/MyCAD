/********************************************************************************
** Form generated from reading UI file 'DlgSettingsSelection.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSSELECTION_H
#define UI_DLGSETTINGSSELECTION_H

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
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsSelection
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    Gui::PrefColorButton *SelectionColor;
    Gui::PrefCheckBox *checkBoxSelection;
    QHBoxLayout *horizontalLayout_1;
    QLabel *spinPickRadiusLabel;
    QSpacerItem *horizSpacer_1;
    Gui::PrefDoubleSpinBox *spinPickRadius;
    Gui::PrefColorButton *HighlightColor;
    Gui::PrefCheckBox *checkBoxPreselection;
    Gui::PrefCheckBox *checkBoxPreselect;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    Gui::PrefCheckBox *checkBoxAutoSwitch;
    Gui::PrefCheckBox *checkBoxAutoExpand;
    Gui::PrefCheckBox *checkBoxRecord;
    Gui::PrefCheckBox *checkBoxSelectionCheckBoxes;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsSelection)
    {
        if (Gui__Dialog__DlgSettingsSelection->objectName().isEmpty())
            Gui__Dialog__DlgSettingsSelection->setObjectName("Gui__Dialog__DlgSettingsSelection");
        Gui__Dialog__DlgSettingsSelection->resize(670, 641);
        verticalLayout_4 = new QVBoxLayout(Gui__Dialog__DlgSettingsSelection);
        verticalLayout_4->setObjectName("verticalLayout_4");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsSelection);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        SelectionColor = new Gui::PrefColorButton(groupBox);
        SelectionColor->setObjectName("SelectionColor");
        SelectionColor->setColor(QColor(0, 171, 255));
        SelectionColor->setProperty("prefEntry", QVariant(QByteArray("SelectionColor")));
        SelectionColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(SelectionColor, 4, 1, 1, 1);

        checkBoxSelection = new Gui::PrefCheckBox(groupBox);
        checkBoxSelection->setObjectName("checkBoxSelection");
        checkBoxSelection->setChecked(true);
        checkBoxSelection->setProperty("prefEntry", QVariant(QByteArray("EnableSelection")));
        checkBoxSelection->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxSelection, 4, 0, 1, 1);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName("horizontalLayout_1");
        spinPickRadiusLabel = new QLabel(groupBox);
        spinPickRadiusLabel->setObjectName("spinPickRadiusLabel");

        horizontalLayout_1->addWidget(spinPickRadiusLabel);

        horizSpacer_1 = new QSpacerItem(250, 10, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_1->addItem(horizSpacer_1);

        spinPickRadius = new Gui::PrefDoubleSpinBox(groupBox);
        spinPickRadius->setObjectName("spinPickRadius");
        spinPickRadius->setMinimumSize(QSize(120, 0));
        spinPickRadius->setInputMethodHints(Qt::InputMethodHint::ImhPreferNumbers);
        spinPickRadius->setSuffix(QString::fromUtf8(" px"));
        spinPickRadius->setDecimals(1);
        spinPickRadius->setMinimum(0.500000000000000);
        spinPickRadius->setMaximum(200.000000000000000);
        spinPickRadius->setValue(5.000000000000000);
        spinPickRadius->setProperty("prefEntry", QVariant(QByteArray("PickRadius")));
        spinPickRadius->setProperty("prefPath", QVariant(QByteArray("View")));

        horizontalLayout_1->addWidget(spinPickRadius);


        gridLayout->addLayout(horizontalLayout_1, 7, 0, 1, 2);

        HighlightColor = new Gui::PrefColorButton(groupBox);
        HighlightColor->setObjectName("HighlightColor");
        HighlightColor->setColor(QColor(10, 200, 255));
        HighlightColor->setProperty("prefEntry", QVariant(QByteArray("HighlightColor")));
        HighlightColor->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(HighlightColor, 3, 1, 1, 1);

        checkBoxPreselection = new Gui::PrefCheckBox(groupBox);
        checkBoxPreselection->setObjectName("checkBoxPreselection");
        checkBoxPreselection->setMinimumSize(QSize(240, 0));
        checkBoxPreselection->setChecked(true);
        checkBoxPreselection->setProperty("prefEntry", QVariant(QByteArray("EnablePreselection")));
        checkBoxPreselection->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout->addWidget(checkBoxPreselection, 3, 0, 1, 1);

        checkBoxPreselect = new Gui::PrefCheckBox(groupBox);
        checkBoxPreselect->setObjectName("checkBoxPreselect");
        checkBoxPreselect->setChecked(true);
        checkBoxPreselect->setProperty("prefEntry", QVariant(QByteArray("PreSelection")));
        checkBoxPreselect->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout->addWidget(checkBoxPreselect, 8, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox);

        groupBox_3 = new QGroupBox(Gui__Dialog__DlgSettingsSelection);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        checkBoxAutoSwitch = new Gui::PrefCheckBox(groupBox_3);
        checkBoxAutoSwitch->setObjectName("checkBoxAutoSwitch");
        checkBoxAutoSwitch->setProperty("prefEntry", QVariant(QByteArray("SyncView")));
        checkBoxAutoSwitch->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        verticalLayout_2->addWidget(checkBoxAutoSwitch);

        checkBoxAutoExpand = new Gui::PrefCheckBox(groupBox_3);
        checkBoxAutoExpand->setObjectName("checkBoxAutoExpand");
        checkBoxAutoExpand->setProperty("prefEntry", QVariant(QByteArray("SyncSelection")));
        checkBoxAutoExpand->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        verticalLayout_2->addWidget(checkBoxAutoExpand);

        checkBoxRecord = new Gui::PrefCheckBox(groupBox_3);
        checkBoxRecord->setObjectName("checkBoxRecord");
        checkBoxRecord->setProperty("prefEntry", QVariant(QByteArray("RecordSelection")));
        checkBoxRecord->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        verticalLayout_2->addWidget(checkBoxRecord);

        checkBoxSelectionCheckBoxes = new Gui::PrefCheckBox(groupBox_3);
        checkBoxSelectionCheckBoxes->setObjectName("checkBoxSelectionCheckBoxes");
        checkBoxSelectionCheckBoxes->setProperty("prefEntry", QVariant(QByteArray("CheckBoxesSelection")));
        checkBoxSelectionCheckBoxes->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        verticalLayout_2->addWidget(checkBoxSelectionCheckBoxes);


        verticalLayout_4->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 245, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        retranslateUi(Gui__Dialog__DlgSettingsSelection);
        QObject::connect(checkBoxPreselection, SIGNAL(toggled(bool)), HighlightColor, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxSelection, SIGNAL(toggled(bool)), SelectionColor, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsSelection);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsSelection)
    {
        Gui__Dialog__DlgSettingsSelection->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Selection", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Viewport Selection Behavior", nullptr));
#if QT_CONFIG(tooltip)
        SelectionColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "The color used for highlighting selected objects in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        SelectionColor->setText(QString());
#if QT_CONFIG(tooltip)
        checkBoxSelection->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Enable selection, highlighted with specified color", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxSelection->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Enable selection", nullptr));
        spinPickRadiusLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Radius", nullptr));
#if QT_CONFIG(tooltip)
        spinPickRadius->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Area for selecting elements in the 3D view.\n"
"A larger value makes it easier to select elements, but may prevent selection of small features.\n"
"      ", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        HighlightColor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "The color used for highlighting preselected objects in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        HighlightColor->setText(QString());
#if QT_CONFIG(tooltip)
        checkBoxPreselection->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Enable preselection, highlighted with specified color", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxPreselection->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Enable preselection", nullptr));
        checkBoxPreselect->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Preselect the object in the 3D view when hovering the cursor over the tree item", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Tree Selection Behavior", nullptr));
        checkBoxAutoSwitch->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Auto switch to the 3D view containing the selected item", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAutoSwitch->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Selecting an item in the Tree View automatically activates its document and switches to its 3D view.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAutoExpand->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Auto expand tree item when the corresponding object is selected in the 3D view", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAutoExpand->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Locates and reveals the selected object within the tree hierarchy. Prevents manual scrolling in deep, complex document structures.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxRecord->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Record selection in tree view in order to go back/forward using navigation button", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxRecord->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Enables selection history. Use 'Back' and 'Forward' navigation to toggle between previously selected objects without re-searching the tree.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxSelectionCheckBoxes->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Add checkboxes for selection in document tree", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxSelectionCheckBoxes->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsSelection", "Provides persistent selection toggles for each item. Simplifies batch operations and complex multi-selection without holding modifier keys (Ctrl/Shift).", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsSelection: public Ui_DlgSettingsSelection {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSSELECTION_H
