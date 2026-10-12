/********************************************************************************
** Form generated from reading UI file 'DlgSettingsMacro.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSMACRO_H
#define UI_DLGSETTINGSMACRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/FileDialog.h"
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsMacro
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    Gui::PrefCheckBox *PrefCheckBox_LocalEnv;
    QGroupBox *GroupBox6;
    QGridLayout *gridLayout1;
    QGroupBox *GroupBox8;
    QGridLayout *gridLayout2;
    Gui::PrefFileChooser *MacroPath;
    QGroupBox *GroupBox7;
    QGridLayout *gridLayout3;
    Gui::PrefCheckBox *PrefCheckBox_RecordGui;
    Gui::PrefCheckBox *PrefCheckBox_GuiAsComment;
    QGroupBox *groupBox4;
    QVBoxLayout *vboxLayout;
    Gui::PrefCheckBox *PConsoleCheckBox;
    Gui::PrefCheckBox *FileLogCheckBox;
    Gui::PrefFileChooser *MacroPath_2;
    QGroupBox *recentmacrosgroupBox;
    QGridLayout *recentmacrosgridLayout;
    QLabel *recentMacroListLabel;
    QSpacerItem *horizontalSpacer;
    Gui::PrefSpinBox *RecentMacros;
    QLabel *recentMacroListShortcutCountLabel;
    QSpacerItem *horizontalSpacer_2;
    Gui::PrefSpinBox *ShortcutCount;
    QLabel *ShorcutModifiersLabel;
    QSpacerItem *horizontalSpacer_3;
    Gui::ModifierLineEdit *ShortcutModifiers;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsMacro)
    {
        if (Gui__Dialog__DlgSettingsMacro->objectName().isEmpty())
            Gui__Dialog__DlgSettingsMacro->setObjectName("Gui__Dialog__DlgSettingsMacro");
        Gui__Dialog__DlgSettingsMacro->resize(391, 407);
        gridLayout_2 = new QGridLayout(Gui__Dialog__DlgSettingsMacro);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsMacro);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        PrefCheckBox_LocalEnv = new Gui::PrefCheckBox(groupBox);
        PrefCheckBox_LocalEnv->setObjectName("PrefCheckBox_LocalEnv");
        PrefCheckBox_LocalEnv->setChecked(true);
        PrefCheckBox_LocalEnv->setProperty("prefEntry", QVariant(QByteArray("LocalEnvironment")));
        PrefCheckBox_LocalEnv->setProperty("prefPath", QVariant(QByteArray("Macro")));

        gridLayout->addWidget(PrefCheckBox_LocalEnv, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        GroupBox6 = new QGroupBox(Gui__Dialog__DlgSettingsMacro);
        GroupBox6->setObjectName("GroupBox6");
        gridLayout1 = new QGridLayout(GroupBox6);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        GroupBox8 = new QGroupBox(GroupBox6);
        GroupBox8->setObjectName("GroupBox8");
        gridLayout2 = new QGridLayout(GroupBox8);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        MacroPath = new Gui::PrefFileChooser(GroupBox8);
        MacroPath->setObjectName("MacroPath");
        MacroPath->setMode(Gui::FileChooser::Directory);
        MacroPath->setProperty("prefEntry", QVariant(QByteArray("MacroPath")));
        MacroPath->setProperty("prefPath", QVariant(QByteArray("Macro")));

        gridLayout2->addWidget(MacroPath, 0, 0, 1, 1);


        gridLayout1->addWidget(GroupBox8, 0, 0, 1, 1);

        GroupBox7 = new QGroupBox(GroupBox6);
        GroupBox7->setObjectName("GroupBox7");
        gridLayout3 = new QGridLayout(GroupBox7);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        PrefCheckBox_RecordGui = new Gui::PrefCheckBox(GroupBox7);
        PrefCheckBox_RecordGui->setObjectName("PrefCheckBox_RecordGui");
        PrefCheckBox_RecordGui->setChecked(true);
        PrefCheckBox_RecordGui->setProperty("prefEntry", QVariant(QByteArray("RecordGui")));
        PrefCheckBox_RecordGui->setProperty("prefPath", QVariant(QByteArray("Macro")));

        gridLayout3->addWidget(PrefCheckBox_RecordGui, 0, 0, 1, 1);

        PrefCheckBox_GuiAsComment = new Gui::PrefCheckBox(GroupBox7);
        PrefCheckBox_GuiAsComment->setObjectName("PrefCheckBox_GuiAsComment");
        PrefCheckBox_GuiAsComment->setChecked(true);
        PrefCheckBox_GuiAsComment->setProperty("prefEntry", QVariant(QByteArray("GuiAsComment")));
        PrefCheckBox_GuiAsComment->setProperty("prefPath", QVariant(QByteArray("Macro")));

        gridLayout3->addWidget(PrefCheckBox_GuiAsComment, 1, 0, 1, 1);


        gridLayout1->addWidget(GroupBox7, 1, 0, 1, 1);

        groupBox4 = new QGroupBox(GroupBox6);
        groupBox4->setObjectName("groupBox4");
        vboxLayout = new QVBoxLayout(groupBox4);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        PConsoleCheckBox = new Gui::PrefCheckBox(groupBox4);
        PConsoleCheckBox->setObjectName("PConsoleCheckBox");
        PConsoleCheckBox->setChecked(true);
        PConsoleCheckBox->setProperty("prefEntry", QVariant(QByteArray("ScriptToPyConsole")));
        PConsoleCheckBox->setProperty("prefPath", QVariant(QByteArray("Macro")));

        vboxLayout->addWidget(PConsoleCheckBox);

        FileLogCheckBox = new Gui::PrefCheckBox(groupBox4);
        FileLogCheckBox->setObjectName("FileLogCheckBox");
        FileLogCheckBox->setProperty("prefEntry", QVariant(QByteArray("ScriptToFile")));
        FileLogCheckBox->setProperty("prefPath", QVariant(QByteArray("Macro")));

        vboxLayout->addWidget(FileLogCheckBox);

        MacroPath_2 = new Gui::PrefFileChooser(groupBox4);
        MacroPath_2->setObjectName("MacroPath_2");
        MacroPath_2->setProperty("prefEntry", QVariant(QByteArray("ScriptFile")));
        MacroPath_2->setProperty("prefPath", QVariant(QByteArray("Macro")));

        vboxLayout->addWidget(MacroPath_2);


        gridLayout1->addWidget(groupBox4, 2, 0, 1, 1);


        gridLayout_2->addWidget(GroupBox6, 1, 0, 1, 1);

        recentmacrosgroupBox = new QGroupBox(Gui__Dialog__DlgSettingsMacro);
        recentmacrosgroupBox->setObjectName("recentmacrosgroupBox");
        recentmacrosgridLayout = new QGridLayout(recentmacrosgroupBox);
        recentmacrosgridLayout->setSpacing(6);
        recentmacrosgridLayout->setContentsMargins(11, 11, 11, 11);
        recentmacrosgridLayout->setObjectName("recentmacrosgridLayout");
        recentMacroListLabel = new QLabel(recentmacrosgroupBox);
        recentMacroListLabel->setObjectName("recentMacroListLabel");

        recentmacrosgridLayout->addWidget(recentMacroListLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recentmacrosgridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        RecentMacros = new Gui::PrefSpinBox(recentmacrosgroupBox);
        RecentMacros->setObjectName("RecentMacros");
        RecentMacros->setValue(12);
        RecentMacros->setProperty("prefEntry", QVariant(QByteArray("RecentMacros")));
        RecentMacros->setProperty("prefPath", QVariant(QByteArray("RecentMacros")));

        recentmacrosgridLayout->addWidget(RecentMacros, 0, 5, 1, 1);

        recentMacroListShortcutCountLabel = new QLabel(recentmacrosgroupBox);
        recentMacroListShortcutCountLabel->setObjectName("recentMacroListShortcutCountLabel");

        recentmacrosgridLayout->addWidget(recentMacroListShortcutCountLabel, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recentmacrosgridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        ShortcutCount = new Gui::PrefSpinBox(recentmacrosgroupBox);
        ShortcutCount->setObjectName("ShortcutCount");
        ShortcutCount->setValue(3);
        ShortcutCount->setProperty("prefEntry", QVariant(QByteArray("ShortcutCount")));
        ShortcutCount->setProperty("prefPath", QVariant(QByteArray("RecentMacros")));

        recentmacrosgridLayout->addWidget(ShortcutCount, 1, 5, 1, 1);

        ShorcutModifiersLabel = new QLabel(recentmacrosgroupBox);
        ShorcutModifiersLabel->setObjectName("ShorcutModifiersLabel");

        recentmacrosgridLayout->addWidget(ShorcutModifiersLabel, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        recentmacrosgridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        ShortcutModifiers = new Gui::ModifierLineEdit(recentmacrosgroupBox);
        ShortcutModifiers->setObjectName("ShortcutModifiers");

        recentmacrosgridLayout->addWidget(ShortcutModifiers, 2, 5, 1, 3);


        gridLayout_2->addWidget(recentmacrosgroupBox, 2, 0, 1, 1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(spacerItem, 3, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgSettingsMacro);
        QObject::connect(PrefCheckBox_RecordGui, SIGNAL(toggled(bool)), PrefCheckBox_GuiAsComment, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsMacro);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsMacro)
    {
        Gui__Dialog__DlgSettingsMacro->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Macro", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "General Macro Settings", nullptr));
#if QT_CONFIG(tooltip)
        PrefCheckBox_LocalEnv->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Variables defined by macros are created as local variables", nullptr));
#endif // QT_CONFIG(tooltip)
        PrefCheckBox_LocalEnv->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Run macros in local environment", nullptr));
        GroupBox6->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Macro Recording Settings", nullptr));
        GroupBox8->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Macro Path", nullptr));
#if QT_CONFIG(tooltip)
        MacroPath->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "The directory in which the application will search for macros", nullptr));
#endif // QT_CONFIG(tooltip)
        GroupBox7->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Gui Commands", nullptr));
#if QT_CONFIG(tooltip)
        PrefCheckBox_RecordGui->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Recorded macros will also contain user interface commands", nullptr));
#endif // QT_CONFIG(tooltip)
        PrefCheckBox_RecordGui->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Record GUI commands", nullptr));
#if QT_CONFIG(tooltip)
        PrefCheckBox_GuiAsComment->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Recorded macros will also contain user interface commands as comments", nullptr));
#endif // QT_CONFIG(tooltip)
        PrefCheckBox_GuiAsComment->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Record as comment", nullptr));
        groupBox4->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Logging Commands", nullptr));
#if QT_CONFIG(tooltip)
        PConsoleCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Commands executed by macro scripts are shown in Python console", nullptr));
#endif // QT_CONFIG(tooltip)
        PConsoleCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Show script commands in Python console", nullptr));
        FileLogCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Log all commands issued by menus to file", nullptr));
        MacroPath_2->setProperty("fileName", QVariant(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "FullScript.FCScript", nullptr)));
        recentmacrosgroupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Recent Macros Menu", nullptr));
        recentMacroListLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Size of recent macro list", nullptr));
#if QT_CONFIG(tooltip)
        RecentMacros->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "How many macros should be listed in recent macros list", nullptr));
#endif // QT_CONFIG(tooltip)
        recentMacroListShortcutCountLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Keyboard shortcut count", nullptr));
#if QT_CONFIG(tooltip)
        ShortcutCount->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "How many recent macros should have shortcuts", nullptr));
#endif // QT_CONFIG(tooltip)
        ShorcutModifiersLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Keyboard Modifiers", nullptr));
#if QT_CONFIG(tooltip)
        ShortcutModifiers->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsMacro", "Keyboard modifiers, default = Ctrl+Shift+", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsMacro: public Ui_DlgSettingsMacro {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSMACRO_H
