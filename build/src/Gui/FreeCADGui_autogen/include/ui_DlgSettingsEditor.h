/********************************************************************************
** Form generated from reading UI file 'DlgSettingsEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSEDITOR_H
#define UI_DLGSETTINGSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsEditor
{
public:
    QGridLayout *gridLayout;
    QGroupBox *GroupBox2;
    QVBoxLayout *vboxLayout;
    Gui::PrefCheckBox *EnableLineNumber;
    Gui::PrefCheckBox *EnableBlockCursor;
    Gui::PrefCheckBox *EnableFolding;
    QSpacerItem *spacerItem;
    QGroupBox *groupBoxIndent;
    QGridLayout *gridLayout1;
    QLabel *textLabel1;
    Gui::PrefSpinBox *tabSize;
    QLabel *textLabel2;
    Gui::PrefSpinBox *indentSize;
    Gui::PrefRadioButton *radioTabs;
    Gui::PrefRadioButton *radioSpaces;
    QGroupBox *GroupBox5;
    QGridLayout *gridLayout2;
    QTreeWidget *displayItems;
    QLabel *TextLabel3;
    QComboBox *fontFamily;
    QLabel *TextLabel4;
    Gui::PrefSpinBox *fontSize;
    QLabel *label_2;
    Gui::ColorButton *colorButton;
    QLabel *label;
    QTextEdit *textEdit1;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsEditor)
    {
        if (Gui__Dialog__DlgSettingsEditor->objectName().isEmpty())
            Gui__Dialog__DlgSettingsEditor->setObjectName("Gui__Dialog__DlgSettingsEditor");
        Gui__Dialog__DlgSettingsEditor->resize(494, 553);
        gridLayout = new QGridLayout(Gui__Dialog__DlgSettingsEditor);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(9, 9, 9, 9);
        GroupBox2 = new QGroupBox(Gui__Dialog__DlgSettingsEditor);
        GroupBox2->setObjectName("GroupBox2");
        vboxLayout = new QVBoxLayout(GroupBox2);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        EnableLineNumber = new Gui::PrefCheckBox(GroupBox2);
        EnableLineNumber->setObjectName("EnableLineNumber");
        EnableLineNumber->setFocusPolicy(Qt::TabFocus);
        EnableLineNumber->setChecked(true);
        EnableLineNumber->setProperty("prefEntry", QVariant(QByteArray("EnableLineNumber")));
        EnableLineNumber->setProperty("prefPath", QVariant(QByteArray("Editor")));

        vboxLayout->addWidget(EnableLineNumber);

        EnableBlockCursor = new Gui::PrefCheckBox(GroupBox2);
        EnableBlockCursor->setObjectName("EnableBlockCursor");
        EnableBlockCursor->setFocusPolicy(Qt::TabFocus);
        EnableBlockCursor->setChecked(false);
        EnableBlockCursor->setProperty("prefEntry", QVariant(QByteArray("EnableBlockCursor")));
        EnableBlockCursor->setProperty("prefPath", QVariant(QByteArray("Editor")));

        vboxLayout->addWidget(EnableBlockCursor);

        EnableFolding = new Gui::PrefCheckBox(GroupBox2);
        EnableFolding->setObjectName("EnableFolding");
        EnableFolding->setChecked(true);
        EnableFolding->setProperty("prefEntry", QVariant(QByteArray("EnableFolding")));
        EnableFolding->setProperty("prefPath", QVariant(QByteArray("Editor")));

        vboxLayout->addWidget(EnableFolding);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Ignored);

        vboxLayout->addItem(spacerItem);


        gridLayout->addWidget(GroupBox2, 0, 0, 1, 1);

        groupBoxIndent = new QGroupBox(Gui__Dialog__DlgSettingsEditor);
        groupBoxIndent->setObjectName("groupBoxIndent");
        gridLayout1 = new QGridLayout(groupBoxIndent);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        textLabel1 = new QLabel(groupBoxIndent);
        textLabel1->setObjectName("textLabel1");

        gridLayout1->addWidget(textLabel1, 0, 0, 1, 1);

        tabSize = new Gui::PrefSpinBox(groupBoxIndent);
        tabSize->setObjectName("tabSize");
        tabSize->setValue(4);
        tabSize->setProperty("prefEntry", QVariant(QByteArray("TabSize")));
        tabSize->setProperty("prefPath", QVariant(QByteArray("Editor")));

        gridLayout1->addWidget(tabSize, 0, 1, 1, 1);

        textLabel2 = new QLabel(groupBoxIndent);
        textLabel2->setObjectName("textLabel2");

        gridLayout1->addWidget(textLabel2, 1, 0, 1, 1);

        indentSize = new Gui::PrefSpinBox(groupBoxIndent);
        indentSize->setObjectName("indentSize");
        indentSize->setValue(4);
        indentSize->setProperty("prefEntry", QVariant(QByteArray("IndentSize")));
        indentSize->setProperty("prefPath", QVariant(QByteArray("Editor")));

        gridLayout1->addWidget(indentSize, 1, 1, 1, 1);

        radioTabs = new Gui::PrefRadioButton(groupBoxIndent);
        radioTabs->setObjectName("radioTabs");
        radioTabs->setChecked(false);
        radioTabs->setProperty("prefEntry", QVariant(QByteArray("Tabs")));
        radioTabs->setProperty("prefPath", QVariant(QByteArray("Editor")));

        gridLayout1->addWidget(radioTabs, 2, 0, 1, 2);

        radioSpaces = new Gui::PrefRadioButton(groupBoxIndent);
        radioSpaces->setObjectName("radioSpaces");
        radioSpaces->setProperty("prefEntry", QVariant(QByteArray("Spaces")));
        radioSpaces->setChecked(true);
        radioSpaces->setProperty("prefPath", QVariant(QByteArray("Editor")));

        gridLayout1->addWidget(radioSpaces, 3, 0, 1, 2);


        gridLayout->addWidget(groupBoxIndent, 0, 1, 1, 1);

        GroupBox5 = new QGroupBox(Gui__Dialog__DlgSettingsEditor);
        GroupBox5->setObjectName("GroupBox5");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GroupBox5->sizePolicy().hasHeightForWidth());
        GroupBox5->setSizePolicy(sizePolicy);
        gridLayout2 = new QGridLayout(GroupBox5);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        displayItems = new QTreeWidget(GroupBox5);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        displayItems->setHeaderItem(__qtreewidgetitem);
        displayItems->setObjectName("displayItems");
        displayItems->setRootIsDecorated(false);

        gridLayout2->addWidget(displayItems, 0, 0, 7, 1);

        TextLabel3 = new QLabel(GroupBox5);
        TextLabel3->setObjectName("TextLabel3");

        gridLayout2->addWidget(TextLabel3, 0, 1, 1, 1);

        fontFamily = new QComboBox(GroupBox5);
        fontFamily->setObjectName("fontFamily");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fontFamily->sizePolicy().hasHeightForWidth());
        fontFamily->setSizePolicy(sizePolicy1);

        gridLayout2->addWidget(fontFamily, 0, 2, 1, 1);

        TextLabel4 = new QLabel(GroupBox5);
        TextLabel4->setObjectName("TextLabel4");

        gridLayout2->addWidget(TextLabel4, 1, 1, 1, 1);

        fontSize = new Gui::PrefSpinBox(GroupBox5);
        fontSize->setObjectName("fontSize");
        sizePolicy1.setHeightForWidth(fontSize->sizePolicy().hasHeightForWidth());
        fontSize->setSizePolicy(sizePolicy1);
        fontSize->setSuffix(QString::fromUtf8(" pt"));
        fontSize->setMinimum(1);
        fontSize->setValue(10);
        fontSize->setProperty("prefEntry", QVariant(QByteArray("FontSize")));
        fontSize->setProperty("prefPath", QVariant(QByteArray("Editor")));

        gridLayout2->addWidget(fontSize, 1, 2, 1, 1);

        label_2 = new QLabel(GroupBox5);
        label_2->setObjectName("label_2");

        gridLayout2->addWidget(label_2, 2, 1, 1, 1);

        colorButton = new Gui::ColorButton(GroupBox5);
        colorButton->setObjectName("colorButton");
        colorButton->setMinimumSize(QSize(140, 0));
        colorButton->setFocusPolicy(Qt::TabFocus);

        gridLayout2->addWidget(colorButton, 2, 2, 1, 1);

        label = new QLabel(GroupBox5);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        gridLayout2->addWidget(label, 3, 1, 1, 1);

        textEdit1 = new QTextEdit(GroupBox5);
        textEdit1->setObjectName("textEdit1");

        gridLayout2->addWidget(textEdit1, 4, 1, 3, 2);


        gridLayout->addWidget(GroupBox5, 1, 0, 1, 2);

        QWidget::setTabOrder(fontFamily, EnableLineNumber);
        QWidget::setTabOrder(EnableLineNumber, EnableBlockCursor);
        QWidget::setTabOrder(EnableBlockCursor, EnableFolding);
        QWidget::setTabOrder(EnableFolding, tabSize);
        QWidget::setTabOrder(tabSize, indentSize);

        retranslateUi(Gui__Dialog__DlgSettingsEditor);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsEditor);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsEditor)
    {
        Gui__Dialog__DlgSettingsEditor->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Editor", nullptr));
        GroupBox2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Options", nullptr));
#if QT_CONFIG(tooltip)
        EnableLineNumber->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Code lines will be numbered", nullptr));
#endif // QT_CONFIG(tooltip)
        EnableLineNumber->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Enable line numbers", nullptr));
#if QT_CONFIG(tooltip)
        EnableBlockCursor->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "The cursor shape will be a block", nullptr));
#endif // QT_CONFIG(tooltip)
        EnableBlockCursor->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Enable block cursor", nullptr));
        EnableFolding->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Enable folding", nullptr));
        groupBoxIndent->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Indentation", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Tab size", nullptr));
#if QT_CONFIG(tooltip)
        tabSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Tabulator raster (how many spaces)", nullptr));
#endif // QT_CONFIG(tooltip)
        tabSize->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", " spaces", "Do not remove leading space"));
        textLabel2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Indent size", nullptr));
#if QT_CONFIG(tooltip)
        indentSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "How many spaces will be inserted when pressing <Tab>", nullptr));
#endif // QT_CONFIG(tooltip)
        indentSize->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", " spaces", "Do not remove leading space"));
#if QT_CONFIG(tooltip)
        radioTabs->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Pressing <Tab> will insert a tabulator with defined tab size", nullptr));
#endif // QT_CONFIG(tooltip)
        radioTabs->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Keep tabs", nullptr));
#if QT_CONFIG(tooltip)
        radioSpaces->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Pressing <Tab> will insert amount of defined indent size", nullptr));
#endif // QT_CONFIG(tooltip)
        radioSpaces->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Insert spaces", nullptr));
        GroupBox5->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Display Items", nullptr));
#if QT_CONFIG(tooltip)
        displayItems->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Color and font settings will be applied to selected type", nullptr));
#endif // QT_CONFIG(tooltip)
        TextLabel3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Family", nullptr));
#if QT_CONFIG(tooltip)
        fontFamily->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Font family to be used for selected code type", nullptr));
#endif // QT_CONFIG(tooltip)
        TextLabel4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Size", nullptr));
#if QT_CONFIG(tooltip)
        fontSize->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Font size to be used for selected code type", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Color", nullptr));
        colorButton->setText(QString());
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsEditor", "Preview", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsEditor: public Ui_DlgSettingsEditor {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSEDITOR_H
