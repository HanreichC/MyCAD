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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsGeneral
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *GroupBox7;
    QGridLayout *gridLayout;
    QLabel *TextLabel1_4;
    QComboBox *Languages;
    QLabel *unitSystemLabel;
    QComboBox *comboBox_UnitSystem;
    QHBoxLayout *horizontalLayout_3;
    QLabel *decimalsLabel;
    QSpinBox *spinBoxDecimals;
    QCheckBox *checkBox_projectUnitSystemIgnore;
    QLabel *fractionalInchLabel;
    QComboBox *comboBox_FracInch;
    QLabel *TextLabel1_5;
    Gui::PrefComboBox *UseLocaleFormatting;
    Gui::PrefCheckBox *SubstituteDecimal;
    QGroupBox *GroupBox3;
    QGridLayout *gridLayout1;
    QLabel *themesLabel;
    QComboBox *themesCombobox;
    QLabel *moreThemesLabel;
    QLabel *iconSizeLabel;
    QComboBox *toolbarIconSize;
    QLabel *treeModeLabel;
    QComboBox *treeMode;
    QLabel *recentFileListLabel;
    Gui::PrefSpinBox *RecentFiles;
    QCheckBox *tiledBackground;
    Gui::PrefCheckBox *EnableCursorBlinking;
    Gui::PrefCheckBox *SplashScreen;
    Gui::PrefCheckBox *ActivateOverlay;
    Gui::PrefCheckBox *ComboBoxWheelEventFilter;
    Gui::PrefCheckBox *FineGrainedRecompute;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *PreferencePacks;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *ImportConfig;
    QPushButton *SaveNewPreferencePack;
    QPushButton *ManagePreferencePacks;
    QPushButton *RevertToSavedConfig;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsGeneral)
    {
        if (Gui__Dialog__DlgSettingsGeneral->objectName().isEmpty())
            Gui__Dialog__DlgSettingsGeneral->setObjectName("Gui__Dialog__DlgSettingsGeneral");
        Gui__Dialog__DlgSettingsGeneral->resize(660, 930);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsGeneral);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        GroupBox7 = new QGroupBox(Gui__Dialog__DlgSettingsGeneral);
        GroupBox7->setObjectName("GroupBox7");
        gridLayout = new QGridLayout(GroupBox7);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(11, 11, 11, 11);
        TextLabel1_4 = new QLabel(GroupBox7);
        TextLabel1_4->setObjectName("TextLabel1_4");

        gridLayout->addWidget(TextLabel1_4, 0, 0, 1, 1);

        Languages = new QComboBox(GroupBox7);
        Languages->setObjectName("Languages");

        gridLayout->addWidget(Languages, 0, 1, 1, 1);

        unitSystemLabel = new QLabel(GroupBox7);
        unitSystemLabel->setObjectName("unitSystemLabel");

        gridLayout->addWidget(unitSystemLabel, 1, 0, 1, 1);

        comboBox_UnitSystem = new QComboBox(GroupBox7);
        comboBox_UnitSystem->setObjectName("comboBox_UnitSystem");

        gridLayout->addWidget(comboBox_UnitSystem, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        decimalsLabel = new QLabel(GroupBox7);
        decimalsLabel->setObjectName("decimalsLabel");

        horizontalLayout_3->addWidget(decimalsLabel);

        spinBoxDecimals = new QSpinBox(GroupBox7);
        spinBoxDecimals->setObjectName("spinBoxDecimals");
        spinBoxDecimals->setMinimum(1);
        spinBoxDecimals->setMaximum(12);

        horizontalLayout_3->addWidget(spinBoxDecimals);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 1);

        checkBox_projectUnitSystemIgnore = new QCheckBox(GroupBox7);
        checkBox_projectUnitSystemIgnore->setObjectName("checkBox_projectUnitSystemIgnore");

        gridLayout->addWidget(checkBox_projectUnitSystemIgnore, 2, 0, 1, 3);

        fractionalInchLabel = new QLabel(GroupBox7);
        fractionalInchLabel->setObjectName("fractionalInchLabel");

        gridLayout->addWidget(fractionalInchLabel, 3, 0, 1, 1);

        comboBox_FracInch = new QComboBox(GroupBox7);
        comboBox_FracInch->addItem(QString::fromUtf8("1/2\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/4\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/8\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/16\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/32\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/64\""));
        comboBox_FracInch->addItem(QString::fromUtf8("1/128\""));
        comboBox_FracInch->setObjectName("comboBox_FracInch");

        gridLayout->addWidget(comboBox_FracInch, 3, 1, 1, 1);

        TextLabel1_5 = new QLabel(GroupBox7);
        TextLabel1_5->setObjectName("TextLabel1_5");

        gridLayout->addWidget(TextLabel1_5, 4, 0, 1, 1);

        UseLocaleFormatting = new Gui::PrefComboBox(GroupBox7);
        UseLocaleFormatting->setObjectName("UseLocaleFormatting");
        UseLocaleFormatting->setProperty("prefEntry", QVariant(QByteArray("UseLocaleFormatting")));
        UseLocaleFormatting->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout->addWidget(UseLocaleFormatting, 4, 1, 1, 1);

        SubstituteDecimal = new Gui::PrefCheckBox(GroupBox7);
        SubstituteDecimal->setObjectName("SubstituteDecimal");
        SubstituteDecimal->setProperty("prefEntry", QVariant(QByteArray("SubstituteDecimalSeparator")));
        SubstituteDecimal->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout->addWidget(SubstituteDecimal, 4, 2, 1, 1);


        verticalLayout->addWidget(GroupBox7);

        GroupBox3 = new QGroupBox(Gui__Dialog__DlgSettingsGeneral);
        GroupBox3->setObjectName("GroupBox3");
        gridLayout1 = new QGridLayout(GroupBox3);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        themesLabel = new QLabel(GroupBox3);
        themesLabel->setObjectName("themesLabel");

        gridLayout1->addWidget(themesLabel, 0, 0, 1, 1);

        themesCombobox = new QComboBox(GroupBox3);
        themesCombobox->setObjectName("themesCombobox");

        gridLayout1->addWidget(themesCombobox, 0, 1, 1, 1);

        moreThemesLabel = new QLabel(GroupBox3);
        moreThemesLabel->setObjectName("moreThemesLabel");
        QFont font;
        font.setPointSize(8);
        moreThemesLabel->setFont(font);
        moreThemesLabel->setTextFormat(Qt::RichText);

        gridLayout1->addWidget(moreThemesLabel, 1, 0, 1, 2);

        iconSizeLabel = new QLabel(GroupBox3);
        iconSizeLabel->setObjectName("iconSizeLabel");

        gridLayout1->addWidget(iconSizeLabel, 2, 0, 1, 1);

        toolbarIconSize = new QComboBox(GroupBox3);
        toolbarIconSize->setObjectName("toolbarIconSize");

        gridLayout1->addWidget(toolbarIconSize, 2, 1, 1, 1);

        treeModeLabel = new QLabel(GroupBox3);
        treeModeLabel->setObjectName("treeModeLabel");

        gridLayout1->addWidget(treeModeLabel, 3, 0, 1, 1);

        treeMode = new QComboBox(GroupBox3);
        treeMode->setObjectName("treeMode");

        gridLayout1->addWidget(treeMode, 3, 1, 1, 1);

        recentFileListLabel = new QLabel(GroupBox3);
        recentFileListLabel->setObjectName("recentFileListLabel");

        gridLayout1->addWidget(recentFileListLabel, 4, 0, 1, 1);

        RecentFiles = new Gui::PrefSpinBox(GroupBox3);
        RecentFiles->setObjectName("RecentFiles");
        RecentFiles->setValue(4);
        RecentFiles->setProperty("prefEntry", QVariant(QByteArray("RecentFiles")));
        RecentFiles->setProperty("prefPath", QVariant(QByteArray("RecentFiles")));

        gridLayout1->addWidget(RecentFiles, 4, 1, 1, 1);

        tiledBackground = new QCheckBox(GroupBox3);
        tiledBackground->setObjectName("tiledBackground");

        gridLayout1->addWidget(tiledBackground, 5, 0, 1, 1);

        EnableCursorBlinking = new Gui::PrefCheckBox(GroupBox3);
        EnableCursorBlinking->setObjectName("EnableCursorBlinking");
        EnableCursorBlinking->setChecked(true);
        EnableCursorBlinking->setProperty("prefEntry", QVariant(QByteArray("EnableCursorBlinking")));
        EnableCursorBlinking->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout1->addWidget(EnableCursorBlinking, 5, 1, 1, 1);

        SplashScreen = new Gui::PrefCheckBox(GroupBox3);
        SplashScreen->setObjectName("SplashScreen");
        SplashScreen->setChecked(true);
        SplashScreen->setProperty("prefEntry", QVariant(QByteArray("ShowSplasher")));
        SplashScreen->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout1->addWidget(SplashScreen, 6, 0, 1, 1);

        ActivateOverlay = new Gui::PrefCheckBox(GroupBox3);
        ActivateOverlay->setObjectName("ActivateOverlay");
        ActivateOverlay->setChecked(true);
        ActivateOverlay->setProperty("prefEntry", QVariant(QByteArray("ActivateOverlay")));
        ActivateOverlay->setProperty("prefPath", QVariant(QByteArray("DockWindows")));

        gridLayout1->addWidget(ActivateOverlay, 6, 1, 1, 1);

        ComboBoxWheelEventFilter = new Gui::PrefCheckBox(GroupBox3);
        ComboBoxWheelEventFilter->setObjectName("ComboBoxWheelEventFilter");
        ComboBoxWheelEventFilter->setChecked(true);
        ComboBoxWheelEventFilter->setProperty("prefEntry", QVariant(QByteArray("ComboBoxWheelEventFilter")));
        ComboBoxWheelEventFilter->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout1->addWidget(ComboBoxWheelEventFilter, 7, 1, 1, 1);

        FineGrainedRecompute = new Gui::PrefCheckBox(GroupBox3);
        FineGrainedRecompute->setObjectName("FineGrainedRecompute");
        FineGrainedRecompute->setChecked(true);
        FineGrainedRecompute->setProperty("prefEntry", QVariant(QByteArray("FineGrainedRecompute")));
        FineGrainedRecompute->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout1->addWidget(FineGrainedRecompute, 7, 0, 1, 1);


        verticalLayout->addWidget(GroupBox3);

        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsGeneral);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        PreferencePacks = new QTableWidget(groupBox);
        if (PreferencePacks->columnCount() < 3)
            PreferencePacks->setColumnCount(3);
        QFont font1;
        font1.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        PreferencePacks->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        PreferencePacks->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        PreferencePacks->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        PreferencePacks->setObjectName("PreferencePacks");
        PreferencePacks->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        PreferencePacks->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        PreferencePacks->setEditTriggers(QAbstractItemView::NoEditTriggers);
        PreferencePacks->setProperty("showDropIndicator", QVariant(false));
        PreferencePacks->setDragDropOverwriteMode(false);
        PreferencePacks->setSelectionMode(QAbstractItemView::NoSelection);
        PreferencePacks->setSelectionBehavior(QAbstractItemView::SelectRows);
        PreferencePacks->setShowGrid(false);
        PreferencePacks->setSortingEnabled(true);
        PreferencePacks->setWordWrap(false);
        PreferencePacks->setCornerButtonEnabled(false);
        PreferencePacks->horizontalHeader()->setVisible(true);
        PreferencePacks->horizontalHeader()->setCascadingSectionResizes(true);
        PreferencePacks->horizontalHeader()->setMinimumSectionSize(30);
        PreferencePacks->horizontalHeader()->setDefaultSectionSize(100);
        PreferencePacks->horizontalHeader()->setStretchLastSection(true);
        PreferencePacks->verticalHeader()->setVisible(false);
        PreferencePacks->verticalHeader()->setMinimumSectionSize(16);
        PreferencePacks->verticalHeader()->setDefaultSectionSize(24);

        verticalLayout_3->addWidget(PreferencePacks);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ImportConfig = new QPushButton(groupBox);
        ImportConfig->setObjectName("ImportConfig");

        horizontalLayout_2->addWidget(ImportConfig);

        SaveNewPreferencePack = new QPushButton(groupBox);
        SaveNewPreferencePack->setObjectName("SaveNewPreferencePack");

        horizontalLayout_2->addWidget(SaveNewPreferencePack);

        ManagePreferencePacks = new QPushButton(groupBox);
        ManagePreferencePacks->setObjectName("ManagePreferencePacks");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ManagePreferencePacks->sizePolicy().hasHeightForWidth());
        ManagePreferencePacks->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(ManagePreferencePacks);

        RevertToSavedConfig = new QPushButton(groupBox);
        RevertToSavedConfig->setObjectName("RevertToSavedConfig");

        horizontalLayout_2->addWidget(RevertToSavedConfig);


        verticalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addWidget(groupBox);

        QWidget::setTabOrder(Languages, RecentFiles);
        QWidget::setTabOrder(RecentFiles, EnableCursorBlinking);
        QWidget::setTabOrder(EnableCursorBlinking, SplashScreen);

        retranslateUi(Gui__Dialog__DlgSettingsGeneral);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsGeneral);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsGeneral)
    {
        Gui__Dialog__DlgSettingsGeneral->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "General", nullptr));
        GroupBox7->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Language and Number Format", nullptr));
        TextLabel1_4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Language", nullptr));
#if QT_CONFIG(tooltip)
        Languages->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Language of the application's user interface", nullptr));
#endif // QT_CONFIG(tooltip)
        unitSystemLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Default unit system", nullptr));
#if QT_CONFIG(tooltip)
        comboBox_UnitSystem->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Unit system for all parts of the application. Can be overridden by specifying a document unit system.", nullptr));
#endif // QT_CONFIG(tooltip)
        decimalsLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Number of decimals", nullptr));
#if QT_CONFIG(tooltip)
        spinBoxDecimals->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Number of decimals that should be shown for numbers and dimensions", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_projectUnitSystemIgnore->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Ignores document unit systems", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_projectUnitSystemIgnore->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Ignore project unit system and use default", nullptr));
        fractionalInchLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Minimum fractional inch", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_FracInch->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Minimum fractional inch to be displayed", nullptr));
#endif // QT_CONFIG(tooltip)
        TextLabel1_5->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Number format", nullptr));
#if QT_CONFIG(tooltip)
        SubstituteDecimal->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Substitutes numerical keypad decimal separator with locale separator, except\n"
"in the Python console and the macro editor where a\n"
"dot/period will always be printed", nullptr));
#endif // QT_CONFIG(tooltip)
        SubstituteDecimal->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Substitute decimal separator", nullptr));
        GroupBox3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Application", nullptr));
        themesLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Theme", nullptr));
#if QT_CONFIG(tooltip)
        themesCombobox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Customize the appearance of the user interface", nullptr));
#endif // QT_CONFIG(tooltip)
        moreThemesLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Looking for more themes? You can obtain them using the <a href=\"freecad:Std_AddonMgr\">Addon Manager</a>.", nullptr));
        iconSizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Size of toolbar icons", nullptr));
#if QT_CONFIG(tooltip)
        toolbarIconSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Icon size in the toolbar", nullptr));
#endif // QT_CONFIG(tooltip)
        treeModeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Tree View and Property View mode", nullptr));
#if QT_CONFIG(tooltip)
        treeMode->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Customize how the tree view is shown in the panel (restart required).\n"
"\n"
"'Combined': combine tree and property view into one panel.\n"
"'Independent': split tree and property view into separate panels.", nullptr));
#endif // QT_CONFIG(tooltip)
        recentFileListLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Size of recent file list", nullptr));
#if QT_CONFIG(tooltip)
        RecentFiles->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "How many files should be listed in recent files list", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        tiledBackground->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Background of the main window (when no document is opened) will consist of tiles of an image.", nullptr));
#endif // QT_CONFIG(tooltip)
        tiledBackground->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Enable tiled background", nullptr));
#if QT_CONFIG(tooltip)
        EnableCursorBlinking->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "The text cursor will be blinking", nullptr));
#endif // QT_CONFIG(tooltip)
        EnableCursorBlinking->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Enable cursor blinking", nullptr));
#if QT_CONFIG(tooltip)
        SplashScreen->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "A splash screen is a small loading window that is shown\n"
"when FreeCAD is launching. If this option is checked, FreeCAD will\n"
"display the splash screen.", nullptr));
#endif // QT_CONFIG(tooltip)
        SplashScreen->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Enable splash screen at start-up", nullptr));
#if QT_CONFIG(tooltip)
        ActivateOverlay->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Activate overlay handling of docked panels", nullptr));
#endif // QT_CONFIG(tooltip)
        ActivateOverlay->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Activate overlay panels", nullptr));
#if QT_CONFIG(tooltip)
        ComboBoxWheelEventFilter->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Prevent the mouse wheel from changing the value of combo boxes,\n"
"and spin boxes with hover focus", nullptr));
#endif // QT_CONFIG(tooltip)
        ComboBoxWheelEventFilter->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Ignore mouse wheel on hover focused input fields", nullptr));
#if QT_CONFIG(tooltip)
        FineGrainedRecompute->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Activate fine-grained recomputation of documents", nullptr));
#endif // QT_CONFIG(tooltip)
        FineGrainedRecompute->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Fine-grained recompute (experimental)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Preference Packs", nullptr));
        QTableWidgetItem *___qtablewidgetitem = PreferencePacks->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = PreferencePacks->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = PreferencePacks->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Load", nullptr));
        ImportConfig->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Import Configuration", nullptr));
        SaveNewPreferencePack->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Save as New", nullptr));
        ManagePreferencePacks->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Manage", nullptr));
        RevertToSavedConfig->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsGeneral", "Revert", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsGeneral: public Ui_DlgSettingsGeneral {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSGENERAL_H
