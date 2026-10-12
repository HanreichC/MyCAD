/********************************************************************************
** Form generated from reading UI file 'DlgSettingsUI.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSUI_H
#define UI_DLGSETTINGSUI_H

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
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsUI
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label1;
    Gui::PrefColorButton *ThemeAccentColor1;
    QLabel *label2;
    QLabel *label3;
    QLabel *styleSheetLabel;
    QLabel *label_2;
    Gui::PrefColorButton *ThemeAccentColor2;
    Gui::PrefColorButton *ThemeAccentColor3;
    Gui::PrefComboBox *StyleSheets;
    Gui::PrefComboBox *OverlayStyleSheets;
    QPushButton *themeEditorButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout1;
    Gui::PrefCheckBox *hideInternalNamesCheckBox;
    Gui::PrefSpinBox *fontSizeSpinBox;
    Gui::PrefSpinBox *iconSizeSpinBox;
    Gui::PrefCheckBox *resizableColumnsCheckBox;
    QLabel *iconSizeLabel;
    QLabel *fontSizeLabel;
    Gui::PrefCheckBox *showVisibilityIconCheckBox;
    Gui::PrefCheckBox *hideHeaderCheckBox;
    Gui::PrefCheckBox *hideTreeViewScrollBarCheckBox;
    Gui::PrefCheckBox *hideDescriptionCheckBox;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    Gui::PrefCheckBox *hideTabBarCheckBox;
    Gui::PrefCheckBox *hintShowTabBarCheckBox;
    Gui::PrefCheckBox *hidePropertyViewScrollBarCheckBox;
    Gui::PrefCheckBox *overlayAutoHideCheckBox;
    Gui::PrefCheckBox *mouseClickPassThroughCheckBox;
    Gui::PrefCheckBox *mouseWheelPassThroughCheckBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    Gui::PrefCheckBox *showTaskWatcherCheckBox;
    QSpacerItem *spacer_3;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsUI)
    {
        if (Gui__Dialog__DlgSettingsUI->objectName().isEmpty())
            Gui__Dialog__DlgSettingsUI->setObjectName("Gui__Dialog__DlgSettingsUI");
        Gui__Dialog__DlgSettingsUI->resize(405, 1065);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsUI);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsUI);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label1 = new QLabel(groupBox);
        label1->setObjectName("label1");

        gridLayout->addWidget(label1, 0, 0, 1, 1);

        ThemeAccentColor1 = new Gui::PrefColorButton(groupBox);
        ThemeAccentColor1->setObjectName("ThemeAccentColor1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ThemeAccentColor1->sizePolicy().hasHeightForWidth());
        ThemeAccentColor1->setSizePolicy(sizePolicy);
        ThemeAccentColor1->setProperty("color", QVariant(QColor(0, 171, 255)));
        ThemeAccentColor1->setProperty("prefEntry", QVariant(QByteArray("ThemeAccentColor1")));
        ThemeAccentColor1->setProperty("prefPath", QVariant(QByteArray("Themes")));

        gridLayout->addWidget(ThemeAccentColor1, 0, 1, 1, 1);

        label2 = new QLabel(groupBox);
        label2->setObjectName("label2");

        gridLayout->addWidget(label2, 1, 0, 1, 1);

        label3 = new QLabel(groupBox);
        label3->setObjectName("label3");

        gridLayout->addWidget(label3, 2, 0, 1, 1);

        styleSheetLabel = new QLabel(groupBox);
        styleSheetLabel->setObjectName("styleSheetLabel");

        gridLayout->addWidget(styleSheetLabel, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        ThemeAccentColor2 = new Gui::PrefColorButton(groupBox);
        ThemeAccentColor2->setObjectName("ThemeAccentColor2");
        sizePolicy.setHeightForWidth(ThemeAccentColor2->sizePolicy().hasHeightForWidth());
        ThemeAccentColor2->setSizePolicy(sizePolicy);
        ThemeAccentColor2->setProperty("color", QVariant(QColor(85, 123, 182)));
        ThemeAccentColor2->setProperty("prefEntry", QVariant(QByteArray("ThemeAccentColor2")));
        ThemeAccentColor2->setProperty("prefPath", QVariant(QByteArray("Themes")));

        gridLayout->addWidget(ThemeAccentColor2, 1, 1, 1, 1);

        ThemeAccentColor3 = new Gui::PrefColorButton(groupBox);
        ThemeAccentColor3->setObjectName("ThemeAccentColor3");
        sizePolicy.setHeightForWidth(ThemeAccentColor3->sizePolicy().hasHeightForWidth());
        ThemeAccentColor3->setSizePolicy(sizePolicy);
        ThemeAccentColor3->setProperty("color", QVariant(QColor(85, 123, 182)));
        ThemeAccentColor3->setProperty("prefEntry", QVariant(QByteArray("ThemeAccentColor3")));
        ThemeAccentColor3->setProperty("prefPath", QVariant(QByteArray("Themes")));

        gridLayout->addWidget(ThemeAccentColor3, 2, 1, 1, 1);

        StyleSheets = new Gui::PrefComboBox(groupBox);
        StyleSheets->setObjectName("StyleSheets");
        StyleSheets->setProperty("prefEntry", QVariant(QByteArray("StyleSheet")));
        StyleSheets->setProperty("prefPath", QVariant(QByteArray("MainWindow")));
        StyleSheets->setProperty("prefType", QVariant(QByteArray("")));

        gridLayout->addWidget(StyleSheets, 3, 1, 1, 1);

        OverlayStyleSheets = new Gui::PrefComboBox(groupBox);
        OverlayStyleSheets->setObjectName("OverlayStyleSheets");
        OverlayStyleSheets->setProperty("prefEntry", QVariant(QByteArray("OverlayActiveStyleSheet")));
        OverlayStyleSheets->setProperty("prefPath", QVariant(QByteArray("MainWindow")));
        OverlayStyleSheets->setProperty("prefType", QVariant(QByteArray("")));

        gridLayout->addWidget(OverlayStyleSheets, 4, 1, 1, 1);

        gridLayout->setColumnStretch(0, 2);
        gridLayout->setColumnStretch(1, 1);

        verticalLayout_2->addLayout(gridLayout);

        themeEditorButton = new QPushButton(groupBox);
        themeEditorButton->setObjectName("themeEditorButton");

        verticalLayout_2->addWidget(themeEditorButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Gui__Dialog__DlgSettingsUI);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout1 = new QGridLayout(groupBox_2);
        gridLayout1->setObjectName("gridLayout1");
        hideInternalNamesCheckBox = new Gui::PrefCheckBox(groupBox_2);
        hideInternalNamesCheckBox->setObjectName("hideInternalNamesCheckBox");
        hideInternalNamesCheckBox->setChecked(true);
        hideInternalNamesCheckBox->setProperty("prefEntry", QVariant(QByteArray("HideInternalNames")));
        hideInternalNamesCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(hideInternalNamesCheckBox, 5, 0, 1, 2);

        fontSizeSpinBox = new Gui::PrefSpinBox(groupBox_2);
        fontSizeSpinBox->setObjectName("fontSizeSpinBox");
        fontSizeSpinBox->setMinimum(0);
        fontSizeSpinBox->setMaximum(100);
        fontSizeSpinBox->setSingleStep(1);
        fontSizeSpinBox->setValue(0);
        fontSizeSpinBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));
        fontSizeSpinBox->setProperty("prefEntry", QVariant(QByteArray("FontSize")));

        gridLayout1->addWidget(fontSizeSpinBox, 0, 1, 1, 1);

        iconSizeSpinBox = new Gui::PrefSpinBox(groupBox_2);
        iconSizeSpinBox->setObjectName("iconSizeSpinBox");
        iconSizeSpinBox->setSingleStep(1);
        iconSizeSpinBox->setValue(16);
        iconSizeSpinBox->setProperty("prefEntry", QVariant(QByteArray("IconSize")));
        iconSizeSpinBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(iconSizeSpinBox, 1, 1, 1, 1);

        resizableColumnsCheckBox = new Gui::PrefCheckBox(groupBox_2);
        resizableColumnsCheckBox->setObjectName("resizableColumnsCheckBox");
        resizableColumnsCheckBox->setProperty("prefEntry", QVariant(QByteArray("ResizableColumn")));
        resizableColumnsCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(resizableColumnsCheckBox, 3, 0, 1, 2);

        iconSizeLabel = new QLabel(groupBox_2);
        iconSizeLabel->setObjectName("iconSizeLabel");

        gridLayout1->addWidget(iconSizeLabel, 1, 0, 1, 1);

        fontSizeLabel = new QLabel(groupBox_2);
        fontSizeLabel->setObjectName("fontSizeLabel");

        gridLayout1->addWidget(fontSizeLabel, 0, 0, 1, 1);

        showVisibilityIconCheckBox = new Gui::PrefCheckBox(groupBox_2);
        showVisibilityIconCheckBox->setObjectName("showVisibilityIconCheckBox");
        showVisibilityIconCheckBox->setChecked(true);
        showVisibilityIconCheckBox->setProperty("prefEntry", QVariant(QByteArray("VisibilityIcon")));
        showVisibilityIconCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(showVisibilityIconCheckBox, 2, 0, 1, 2);

        hideHeaderCheckBox = new Gui::PrefCheckBox(groupBox_2);
        hideHeaderCheckBox->setObjectName("hideHeaderCheckBox");
        hideHeaderCheckBox->setChecked(true);
        hideHeaderCheckBox->setProperty("prefEntry", QVariant(QByteArray("HideHeaderView")));
        hideHeaderCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(hideHeaderCheckBox, 7, 0, 1, 2);

        hideTreeViewScrollBarCheckBox = new Gui::PrefCheckBox(groupBox_2);
        hideTreeViewScrollBarCheckBox->setObjectName("hideTreeViewScrollBarCheckBox");
        hideTreeViewScrollBarCheckBox->setChecked(true);
        hideTreeViewScrollBarCheckBox->setProperty("prefEntry", QVariant(QByteArray("HideScrollBar")));
        hideTreeViewScrollBarCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(hideTreeViewScrollBarCheckBox, 6, 0, 1, 2);

        hideDescriptionCheckBox = new Gui::PrefCheckBox(groupBox_2);
        hideDescriptionCheckBox->setObjectName("hideDescriptionCheckBox");
        hideDescriptionCheckBox->setChecked(true);
        hideDescriptionCheckBox->setProperty("prefEntry", QVariant(QByteArray("HideColumn")));
        hideDescriptionCheckBox->setProperty("prefPath", QVariant(QByteArray("TreeView")));

        gridLayout1->addWidget(hideDescriptionCheckBox, 4, 0, 1, 2);

        gridLayout1->setColumnStretch(0, 2);
        gridLayout1->setColumnStretch(1, 1);

        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Gui__Dialog__DlgSettingsUI);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName("gridLayout_2");
        hideTabBarCheckBox = new Gui::PrefCheckBox(groupBox_3);
        hideTabBarCheckBox->setObjectName("hideTabBarCheckBox");
        hideTabBarCheckBox->setChecked(true);
        hideTabBarCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayHideTabBar")));
        hideTabBarCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(hideTabBarCheckBox, 2, 0, 1, 1);

        hintShowTabBarCheckBox = new Gui::PrefCheckBox(groupBox_3);
        hintShowTabBarCheckBox->setObjectName("hintShowTabBarCheckBox");
        hintShowTabBarCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayHintTabBar")));
        hintShowTabBarCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(hintShowTabBarCheckBox, 3, 0, 1, 1);

        hidePropertyViewScrollBarCheckBox = new Gui::PrefCheckBox(groupBox_3);
        hidePropertyViewScrollBarCheckBox->setObjectName("hidePropertyViewScrollBarCheckBox");
        hidePropertyViewScrollBarCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayHidePropertyViewScrollBar")));
        hidePropertyViewScrollBarCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(hidePropertyViewScrollBarCheckBox, 4, 0, 1, 1);

        overlayAutoHideCheckBox = new Gui::PrefCheckBox(groupBox_3);
        overlayAutoHideCheckBox->setObjectName("overlayAutoHideCheckBox");
        overlayAutoHideCheckBox->setChecked(true);
        overlayAutoHideCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayAutoView")));
        overlayAutoHideCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(overlayAutoHideCheckBox, 5, 0, 1, 1);

        mouseClickPassThroughCheckBox = new Gui::PrefCheckBox(groupBox_3);
        mouseClickPassThroughCheckBox->setObjectName("mouseClickPassThroughCheckBox");
        mouseClickPassThroughCheckBox->setChecked(true);
        mouseClickPassThroughCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayAutoMouseThrough")));
        mouseClickPassThroughCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(mouseClickPassThroughCheckBox, 6, 0, 1, 1);

        mouseWheelPassThroughCheckBox = new Gui::PrefCheckBox(groupBox_3);
        mouseWheelPassThroughCheckBox->setObjectName("mouseWheelPassThroughCheckBox");
        mouseWheelPassThroughCheckBox->setChecked(true);
        mouseWheelPassThroughCheckBox->setProperty("prefEntry", QVariant(QByteArray("DockOverlayWheelPassThrough")));
        mouseWheelPassThroughCheckBox->setProperty("prefPath", QVariant(QByteArray("View")));

        gridLayout_2->addWidget(mouseWheelPassThroughCheckBox, 7, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(Gui__Dialog__DlgSettingsUI);
        groupBox_4->setObjectName("groupBox_4");
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName("gridLayout_3");
        showTaskWatcherCheckBox = new Gui::PrefCheckBox(groupBox_4);
        showTaskWatcherCheckBox->setObjectName("showTaskWatcherCheckBox");
        showTaskWatcherCheckBox->setChecked(true);
        showTaskWatcherCheckBox->setProperty("prefEntry", QVariant(QByteArray("ShowTaskWatcher")));
        showTaskWatcherCheckBox->setProperty("prefPath", QVariant(QByteArray("General")));

        gridLayout_3->addWidget(showTaskWatcherCheckBox, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        spacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(spacer_3);

#if QT_CONFIG(shortcut)
        label1->setBuddy(ThemeAccentColor1);
        label2->setBuddy(ThemeAccentColor2);
        label3->setBuddy(ThemeAccentColor3);
        styleSheetLabel->setBuddy(StyleSheets);
        label_2->setBuddy(OverlayStyleSheets);
        iconSizeLabel->setBuddy(iconSizeSpinBox);
        fontSizeLabel->setBuddy(fontSizeSpinBox);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(ThemeAccentColor1, ThemeAccentColor2);
        QWidget::setTabOrder(ThemeAccentColor2, ThemeAccentColor3);
        QWidget::setTabOrder(ThemeAccentColor3, StyleSheets);
        QWidget::setTabOrder(StyleSheets, OverlayStyleSheets);
        QWidget::setTabOrder(OverlayStyleSheets, fontSizeSpinBox);
        QWidget::setTabOrder(fontSizeSpinBox, iconSizeSpinBox);
        QWidget::setTabOrder(iconSizeSpinBox, resizableColumnsCheckBox);
        QWidget::setTabOrder(resizableColumnsCheckBox, showVisibilityIconCheckBox);
        QWidget::setTabOrder(showVisibilityIconCheckBox, hideDescriptionCheckBox);
        QWidget::setTabOrder(hideDescriptionCheckBox, hideInternalNamesCheckBox);
        QWidget::setTabOrder(hideInternalNamesCheckBox, hideTreeViewScrollBarCheckBox);
        QWidget::setTabOrder(hideTreeViewScrollBarCheckBox, hideHeaderCheckBox);
        QWidget::setTabOrder(hideHeaderCheckBox, hideTabBarCheckBox);
        QWidget::setTabOrder(hideTabBarCheckBox, hintShowTabBarCheckBox);
        QWidget::setTabOrder(hintShowTabBarCheckBox, hidePropertyViewScrollBarCheckBox);
        QWidget::setTabOrder(hidePropertyViewScrollBarCheckBox, overlayAutoHideCheckBox);
        QWidget::setTabOrder(overlayAutoHideCheckBox, mouseClickPassThroughCheckBox);
        QWidget::setTabOrder(mouseClickPassThroughCheckBox, mouseWheelPassThroughCheckBox);

        retranslateUi(Gui__Dialog__DlgSettingsUI);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsUI);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsUI)
    {
        Gui__Dialog__DlgSettingsUI->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "UI", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Theme Customization", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Customize the current theme. The offered settings are optional for theme developers so they may or may not have an effect in the current theme.", nullptr));
        label1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Accent color 1", nullptr));
#if QT_CONFIG(tooltip)
        ThemeAccentColor1->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "This color might be used by your theme to let you customize it.", nullptr));
#endif // QT_CONFIG(tooltip)
        label2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Accent color 2", nullptr));
        label3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Accent color 3", nullptr));
        styleSheetLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Style sheet (advanced)", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Overlay style sheet", nullptr));
#if QT_CONFIG(tooltip)
        ThemeAccentColor2->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "This color might be used by your theme to let you customize it.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        ThemeAccentColor3->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "This color might be used by your theme to let you customize it.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        StyleSheets->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Style sheet how user interface will look like", nullptr));
#endif // QT_CONFIG(tooltip)
        themeEditorButton->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Open Theme Editor", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Tree View", nullptr));
#if QT_CONFIG(tooltip)
        hideInternalNamesCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide extra tree view column for internal names", nullptr));
#endif // QT_CONFIG(tooltip)
        hideInternalNamesCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide internal names", nullptr));
#if QT_CONFIG(tooltip)
        fontSizeSpinBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Font size override, set to 0 for the default value.", nullptr));
#endif // QT_CONFIG(tooltip)
        fontSizeSpinBox->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", " pt", nullptr));
#if QT_CONFIG(tooltip)
        iconSizeSpinBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Icon size override, set to 0 for the default value.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        resizableColumnsCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Allow tree view columns to be manually resized.", nullptr));
#endif // QT_CONFIG(tooltip)
        resizableColumnsCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Resizable columns", nullptr));
        iconSizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Icon size", nullptr));
        fontSizeLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Font size", nullptr));
#if QT_CONFIG(tooltip)
        showVisibilityIconCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Displays an eye icon in front of the tree view items, showing their visibility status. When clicked the visibility is toggled.", nullptr));
#endif // QT_CONFIG(tooltip)
        showVisibilityIconCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Show visibility icon", nullptr));
#if QT_CONFIG(tooltip)
        hideHeaderCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide header with column names from the tree view.", nullptr));
#endif // QT_CONFIG(tooltip)
        hideHeaderCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide header", nullptr));
#if QT_CONFIG(tooltip)
        hideTreeViewScrollBarCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide scroll bar from the tree view, scrolling will still be possible using mouse wheel.", nullptr));
#endif // QT_CONFIG(tooltip)
        hideTreeViewScrollBarCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide scroll bar", nullptr));
#if QT_CONFIG(tooltip)
        hideDescriptionCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide column with object description in tree view.", nullptr));
#endif // QT_CONFIG(tooltip)
        hideDescriptionCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide description", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Overlay", nullptr));
#if QT_CONFIG(tooltip)
        hideTabBarCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide tab bar in dock overlay", nullptr));
#endif // QT_CONFIG(tooltip)
        hideTabBarCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide tab bar", nullptr));
#if QT_CONFIG(tooltip)
        hintShowTabBarCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Show tab bar on mouse over when auto hide", nullptr));
#endif // QT_CONFIG(tooltip)
        hintShowTabBarCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hint show tab bar", nullptr));
#if QT_CONFIG(tooltip)
        hidePropertyViewScrollBarCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide property view scroll bar in dock overlay", nullptr));
#endif // QT_CONFIG(tooltip)
        hidePropertyViewScrollBarCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Hide property view scroll bar", nullptr));
#if QT_CONFIG(tooltip)
        overlayAutoHideCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Automatically hide overlaid dock panels when in non 3D view (e.g. TechDraw or Spreadsheet)", nullptr));
#endif // QT_CONFIG(tooltip)
        overlayAutoHideCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Automatically hide in non-3D view", nullptr));
#if QT_CONFIG(tooltip)
        mouseClickPassThroughCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Auto mouse click through transparent part of dock overlay.", nullptr));
#endif // QT_CONFIG(tooltip)
        mouseClickPassThroughCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Automatically pass through of the mouse cursor", nullptr));
#if QT_CONFIG(tooltip)
        mouseWheelPassThroughCheckBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Automatically passes mouse wheel events through the transparent areas of an overlay panel", nullptr));
#endif // QT_CONFIG(tooltip)
        mouseWheelPassThroughCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Automatically pass through of the mouse wheel", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Suggested Actions", nullptr));
        showTaskWatcherCheckBox->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsUI", "Suggest actions in the task view based on the selection", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsUI: public Ui_DlgSettingsUI {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSUI_H
