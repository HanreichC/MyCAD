/********************************************************************************
** Form generated from reading UI file 'DlgSettingsWorkbenches.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSWORKBENCHES_H
#define UI_DLGSETTINGSWORKBENCHES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "ListWidgetDragBugFix.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsWorkbenches
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *noteLabel;
    ListWidgetDragBugFix *wbList;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QLabel *WorkbenchSelectorItemLabel;
    QComboBox *WorkbenchSelectorItem;
    QHBoxLayout *hboxLayout1;
    QLabel *WorkbenchSelectorTypeLabel;
    QComboBox *WorkbenchSelectorType;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hboxLayout2;
    QLabel *autoModuleLabel;
    QComboBox *AutoloadModuleCombo;
    Gui::PrefCheckBox *CheckBox_WbByTab;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsWorkbenches)
    {
        if (Gui__Dialog__DlgSettingsWorkbenches->objectName().isEmpty())
            Gui__Dialog__DlgSettingsWorkbenches->setObjectName("Gui__Dialog__DlgSettingsWorkbenches");
        Gui__Dialog__DlgSettingsWorkbenches->resize(980, 859);
        verticalLayout_3 = new QVBoxLayout(Gui__Dialog__DlgSettingsWorkbenches);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsWorkbenches);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        noteLabel = new QLabel(groupBox);
        noteLabel->setObjectName("noteLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(noteLabel->sizePolicy().hasHeightForWidth());
        noteLabel->setSizePolicy(sizePolicy);
        noteLabel->setMinimumSize(QSize(0, 50));
        noteLabel->setWordWrap(true);

        verticalLayout_4->addWidget(noteLabel);

        wbList = new ListWidgetDragBugFix(groupBox);
        wbList->setObjectName("wbList");

        verticalLayout_4->addWidget(wbList);


        verticalLayout_3->addWidget(groupBox);

        groupBox_3 = new QGroupBox(Gui__Dialog__DlgSettingsWorkbenches);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        WorkbenchSelectorItemLabel = new QLabel(groupBox_3);
        WorkbenchSelectorItemLabel->setObjectName("WorkbenchSelectorItemLabel");

        hboxLayout->addWidget(WorkbenchSelectorItemLabel);

        WorkbenchSelectorItem = new QComboBox(groupBox_3);
        WorkbenchSelectorItem->setObjectName("WorkbenchSelectorItem");

        hboxLayout->addWidget(WorkbenchSelectorItem);


        verticalLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        WorkbenchSelectorTypeLabel = new QLabel(groupBox_3);
        WorkbenchSelectorTypeLabel->setObjectName("WorkbenchSelectorTypeLabel");

        hboxLayout1->addWidget(WorkbenchSelectorTypeLabel);

        WorkbenchSelectorType = new QComboBox(groupBox_3);
        WorkbenchSelectorType->setObjectName("WorkbenchSelectorType");

        hboxLayout1->addWidget(WorkbenchSelectorType);


        verticalLayout->addLayout(hboxLayout1);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(Gui__Dialog__DlgSettingsWorkbenches);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        autoModuleLabel = new QLabel(groupBox_2);
        autoModuleLabel->setObjectName("autoModuleLabel");

        hboxLayout2->addWidget(autoModuleLabel);

        AutoloadModuleCombo = new QComboBox(groupBox_2);
        AutoloadModuleCombo->setObjectName("AutoloadModuleCombo");

        hboxLayout2->addWidget(AutoloadModuleCombo);


        verticalLayout_2->addLayout(hboxLayout2);

        CheckBox_WbByTab = new Gui::PrefCheckBox(groupBox_2);
        CheckBox_WbByTab->setObjectName("CheckBox_WbByTab");
        CheckBox_WbByTab->setChecked(false);
        CheckBox_WbByTab->setProperty("prefEntry", QVariant(QByteArray("SaveWBbyTab")));
        CheckBox_WbByTab->setProperty("prefPath", QVariant(QByteArray("View")));

        verticalLayout_2->addWidget(CheckBox_WbByTab);


        verticalLayout_3->addWidget(groupBox_2);


        retranslateUi(Gui__Dialog__DlgSettingsWorkbenches);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsWorkbenches);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsWorkbenches)
    {
        Gui__Dialog__DlgSettingsWorkbenches->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Available Workbenches", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Workbenches", nullptr));
        noteLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "<html><head/><body><p>You can reorder workbenches by drag and drop or sort them by right-clicking on any workbench and select <span style=\"  font-weight:600; font-style:italic;\">Sort alphabetically</span>. Additional workbenches can be installed through the addon manager.</p><p>\n"
"Currently installed workbenches:</p></body></html>", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Selectors", nullptr));
        WorkbenchSelectorItemLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Workbench selector items style", nullptr));
#if QT_CONFIG(tooltip)
        WorkbenchSelectorItem->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Customizes how the items are displayed", nullptr));
#endif // QT_CONFIG(tooltip)
        WorkbenchSelectorTypeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Workbench selector type", nullptr));
#if QT_CONFIG(tooltip)
        WorkbenchSelectorType->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Choose the workbench selector widget type (restart required)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Startup", nullptr));
        autoModuleLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Default workbench", nullptr));
#if QT_CONFIG(tooltip)
        AutoloadModuleCombo->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Changes which workbench will be activated and shown\n"
"after FreeCAD launches", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        CheckBox_WbByTab->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Remembers which workbench is active for each tab of the viewport", nullptr));
#endif // QT_CONFIG(tooltip)
        CheckBox_WbByTab->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsWorkbenches", "Remember active workbench by tab", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsWorkbenches: public Ui_DlgSettingsWorkbenches {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSWORKBENCHES_H
