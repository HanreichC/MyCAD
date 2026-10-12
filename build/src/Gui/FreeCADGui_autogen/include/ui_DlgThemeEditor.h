/********************************************************************************
** Form generated from reading UI file 'DlgThemeEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTHEMEEDITOR_H
#define UI_DLGTHEMEEDITOR_H

#include <Gui/Dialogs/DlgThemeEditor.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "Gui/Widgets.h"

namespace Gui {

class Ui_DlgThemeEditor
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QRadioButton *radioButton;
    QLineEdit *lineEdit;
    Gui::ColorButton *colorButton;
    QSpacerItem *verticalSpacer;
    QComboBox *comboBox;
    QScrollBar *horizontalScrollBar;
    QSpinBox *spinBox;
    QComboBox *comboBox_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QDialogButtonBox *buttonBox;
    Gui::TokenTreeView *tokensTreeView;

    void setupUi(QDialog *Gui__DlgThemeEditor)
    {
        if (Gui__DlgThemeEditor->objectName().isEmpty())
            Gui__DlgThemeEditor->setObjectName("Gui__DlgThemeEditor");
        Gui__DlgThemeEditor->resize(1169, 562);
        gridLayout = new QGridLayout(Gui__DlgThemeEditor);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(Gui__DlgThemeEditor);
        groupBox->setObjectName("groupBox");
        groupBox->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        gridLayout_3->addWidget(pushButton, 0, 1, 1, 1);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName("checkBox");

        gridLayout_3->addWidget(checkBox, 3, 1, 1, 1);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");

        gridLayout_3->addWidget(radioButton, 2, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName("lineEdit");

        gridLayout_3->addWidget(lineEdit, 5, 1, 1, 1);

        colorButton = new Gui::ColorButton(groupBox);
        colorButton->setObjectName("colorButton");

        gridLayout_3->addWidget(colorButton, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 11, 1, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout_3->addWidget(comboBox, 8, 1, 1, 1);

        horizontalScrollBar = new QScrollBar(groupBox);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_3->addWidget(horizontalScrollBar, 7, 1, 1, 1);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");

        gridLayout_3->addWidget(spinBox, 4, 1, 1, 1);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setEditable(true);

        gridLayout_3->addWidget(comboBox_2, 9, 1, 1, 1);

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());

        gridLayout_3->addWidget(tabWidget, 10, 1, 1, 1);

        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName("textEdit");

        gridLayout_3->addWidget(textEdit, 6, 1, 1, 1);


        gridLayout->addWidget(groupBox, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonBox = new QDialogButtonBox(Gui__DlgThemeEditor);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Apply|QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok|QDialogButtonBox::StandardButton::Reset);

        horizontalLayout_2->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        tokensTreeView = new Gui::TokenTreeView(Gui__DlgThemeEditor);
        tokensTreeView->setObjectName("tokensTreeView");
        tokensTreeView->setMouseTracking(true);
        tokensTreeView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tokensTreeView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
        tokensTreeView->setAlternatingRowColors(true);
        tokensTreeView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tokensTreeView->setRootIsDecorated(false);
        tokensTreeView->setUniformRowHeights(true);

        gridLayout->addWidget(tokensTreeView, 1, 0, 1, 1);

        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 1);

        retranslateUi(Gui__DlgThemeEditor);

        QMetaObject::connectSlotsByName(Gui__DlgThemeEditor);
    } // setupUi

    void retranslateUi(QDialog *Gui__DlgThemeEditor)
    {
        Gui__DlgThemeEditor->setWindowTitle(QCoreApplication::translate("Gui::DlgThemeEditor", "Theme Editor", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::DlgThemeEditor", "Preview", nullptr));
        pushButton->setText(QCoreApplication::translate("Gui::DlgThemeEditor", "PushButton", nullptr));
        checkBox->setText(QCoreApplication::translate("Gui::DlgThemeEditor", "CheckBox", nullptr));
        radioButton->setText(QCoreApplication::translate("Gui::DlgThemeEditor", "RadioButton", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Gui::DlgThemeEditor", "Item 1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Gui::DlgThemeEditor", "Item 2", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Gui::DlgThemeEditor", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Gui::DlgThemeEditor", "Tab 2", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class DlgThemeEditor: public Ui_DlgThemeEditor {};
} // namespace Ui
} // namespace Gui

#endif // UI_DLGTHEMEEDITOR_H
