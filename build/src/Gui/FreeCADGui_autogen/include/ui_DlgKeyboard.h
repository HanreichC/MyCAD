/********************************************************************************
** Form generated from reading UI file 'DlgKeyboard.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGKEYBOARD_H
#define UI_DLGKEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsKeyboard
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    Gui::PrefSpinBox *shortcutTimeout;
    QLabel *label;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *editCommand;
    QSpacerItem *horizontalSpacer;
    QLabel *TextLabelCategory;
    QComboBox *categoryBox;
    QTreeWidget *commandTreeWidget;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QLabel *textLabelNewShortcut;
    Gui::AccelLineEdit *currentShortcut;
    Gui::AccelLineEdit *editShortcut;
    QPushButton *buttonClear;
    QPushButton *buttonAssign;
    QPushButton *buttonReset;
    QLabel *textLabelShortcut;
    QPushButton *buttonResetAll;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *assignedTreeWidget;
    QVBoxLayout *_2;
    QPushButton *buttonUp;
    QPushButton *buttonDown;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsKeyboard)
    {
        if (Gui__Dialog__DlgSettingsKeyboard->objectName().isEmpty())
            Gui__Dialog__DlgSettingsKeyboard->setObjectName("Gui__Dialog__DlgSettingsKeyboard");
        Gui__Dialog__DlgSettingsKeyboard->resize(746, 850);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgSettingsKeyboard);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Gui__Dialog__DlgSettingsKeyboard);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        shortcutTimeout = new Gui::PrefSpinBox(groupBox);
        shortcutTimeout->setObjectName("shortcutTimeout");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(shortcutTimeout->sizePolicy().hasHeightForWidth());
        shortcutTimeout->setSizePolicy(sizePolicy);
        shortcutTimeout->setMinimumSize(QSize(50, 0));
        shortcutTimeout->setMaximum(10000);
        shortcutTimeout->setSingleStep(100);
        shortcutTimeout->setValue(300);
        shortcutTimeout->setProperty("prefEntry", QVariant(QByteArray("ShortcutTimeout")));
        shortcutTimeout->setProperty("prefPath", QVariant(QByteArray("Shortcut/Settings")));

        gridLayout_2->addWidget(shortcutTimeout, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Gui__Dialog__DlgSettingsKeyboard);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        editCommand = new QLineEdit(groupBox_2);
        editCommand->setObjectName("editCommand");

        horizontalLayout_2->addWidget(editCommand);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        TextLabelCategory = new QLabel(groupBox_2);
        TextLabelCategory->setObjectName("TextLabelCategory");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TextLabelCategory->sizePolicy().hasHeightForWidth());
        TextLabelCategory->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(TextLabelCategory);

        categoryBox = new QComboBox(groupBox_2);
        categoryBox->setObjectName("categoryBox");

        horizontalLayout_2->addWidget(categoryBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        commandTreeWidget = new QTreeWidget(groupBox_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        commandTreeWidget->setHeaderItem(__qtreewidgetitem);
        commandTreeWidget->setObjectName("commandTreeWidget");
        commandTreeWidget->setMinimumSize(QSize(400, 0));
        commandTreeWidget->setRootIsDecorated(false);
        commandTreeWidget->setSortingEnabled(true);

        verticalLayout_2->addWidget(commandTreeWidget);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName("gridLayout_3");
        textLabelNewShortcut = new QLabel(groupBox_2);
        textLabelNewShortcut->setObjectName("textLabelNewShortcut");

        gridLayout_3->addWidget(textLabelNewShortcut, 1, 0, 1, 1);

        currentShortcut = new Gui::AccelLineEdit(groupBox_2);
        currentShortcut->setObjectName("currentShortcut");
        currentShortcut->setReadOnly(true);

        gridLayout_3->addWidget(currentShortcut, 0, 1, 1, 1);

        editShortcut = new Gui::AccelLineEdit(groupBox_2);
        editShortcut->setObjectName("editShortcut");

        gridLayout_3->addWidget(editShortcut, 1, 1, 1, 1);

        buttonClear = new QPushButton(groupBox_2);
        buttonClear->setObjectName("buttonClear");

        gridLayout_3->addWidget(buttonClear, 1, 2, 1, 1);

        buttonAssign = new QPushButton(groupBox_2);
        buttonAssign->setObjectName("buttonAssign");

        gridLayout_3->addWidget(buttonAssign, 0, 2, 1, 1);

        buttonReset = new QPushButton(groupBox_2);
        buttonReset->setObjectName("buttonReset");

        gridLayout_3->addWidget(buttonReset, 2, 2, 1, 1);

        textLabelShortcut = new QLabel(groupBox_2);
        textLabelShortcut->setObjectName("textLabelShortcut");

        gridLayout_3->addWidget(textLabelShortcut, 0, 0, 1, 1);

        buttonResetAll = new QPushButton(groupBox_2);
        buttonResetAll->setObjectName("buttonResetAll");

        gridLayout_3->addWidget(buttonResetAll, 3, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        assignedTreeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        assignedTreeWidget->setHeaderItem(__qtreewidgetitem1);
        assignedTreeWidget->setObjectName("assignedTreeWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(assignedTreeWidget->sizePolicy().hasHeightForWidth());
        assignedTreeWidget->setSizePolicy(sizePolicy2);
        assignedTreeWidget->setMinimumSize(QSize(220, 0));
        assignedTreeWidget->setMaximumSize(QSize(16777215, 400));
        assignedTreeWidget->setAlternatingRowColors(true);
        assignedTreeWidget->setRootIsDecorated(false);

        horizontalLayout->addWidget(assignedTreeWidget);

        _2 = new QVBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName("_2");
        _2->setContentsMargins(0, 0, 0, 0);
        buttonUp = new QPushButton(groupBox_3);
        buttonUp->setObjectName("buttonUp");
        buttonUp->setEnabled(false);

        _2->addWidget(buttonUp);

        buttonDown = new QPushButton(groupBox_3);
        buttonDown->setObjectName("buttonDown");
        buttonDown->setEnabled(false);

        _2->addWidget(buttonDown);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        _2->addItem(spacerItem);


        horizontalLayout->addLayout(_2);


        verticalLayout_2->addWidget(groupBox_3);


        verticalLayout->addWidget(groupBox_2);

#if QT_CONFIG(shortcut)
        TextLabelCategory->setBuddy(categoryBox);
        textLabelNewShortcut->setBuddy(editShortcut);
        textLabelShortcut->setBuddy(currentShortcut);
#endif // QT_CONFIG(shortcut)

        retranslateUi(Gui__Dialog__DlgSettingsKeyboard);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsKeyboard);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsKeyboard)
    {
        Gui__Dialog__DlgSettingsKeyboard->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Keyboard", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "General", nullptr));
#if QT_CONFIG(tooltip)
        shortcutTimeout->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Time in milliseconds to wait for the next keystroke of the current key sequence.\n"
"For example, pressing 'F' twice in less than the time delay setting here will be\n"
"treated as shortcut key sequence 'F, F'.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Multi-key sequence delay", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Shortcuts", nullptr));
        TextLabelCategory->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "&Category", nullptr));
        textLabelNewShortcut->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "&New shortcut", nullptr));
#if QT_CONFIG(tooltip)
        currentShortcut->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "To change a current shortcut enter the new shortcut in the field below and press 'Assign'.", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonClear->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Clear", nullptr));
        buttonAssign->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "&Assign", nullptr));
#if QT_CONFIG(shortcut)
        buttonAssign->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Alt+A", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonReset->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "&Reset", nullptr));
#if QT_CONFIG(shortcut)
        buttonReset->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Alt+R", nullptr));
#endif // QT_CONFIG(shortcut)
        textLabelShortcut->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Current shortcut", nullptr));
        buttonResetAll->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Re&set All", nullptr));
#if QT_CONFIG(shortcut)
        buttonResetAll->setShortcut(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_3->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Priority List", nullptr));
        buttonUp->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Move Up", nullptr));
        buttonDown->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsKeyboard", "Move Down", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsKeyboard: public Ui_DlgSettingsKeyboard {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGKEYBOARD_H
