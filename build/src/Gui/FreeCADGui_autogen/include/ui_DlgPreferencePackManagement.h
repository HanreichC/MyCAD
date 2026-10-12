/********************************************************************************
** Form generated from reading UI file 'DlgPreferencePackManagement.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGPREFERENCEPACKMANAGEMENT_H
#define UI_DLGPREFERENCEPACKMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgPreferencePackManagement
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOpenAddonManager;
    QTreeWidget *treeWidget;

    void setupUi(QDialog *Gui__Dialog__DlgPreferencePackManagement)
    {
        if (Gui__Dialog__DlgPreferencePackManagement->objectName().isEmpty())
            Gui__Dialog__DlgPreferencePackManagement->setObjectName("Gui__Dialog__DlgPreferencePackManagement");
        Gui__Dialog__DlgPreferencePackManagement->resize(392, 255);
        Gui__Dialog__DlgPreferencePackManagement->setSizeGripEnabled(true);
        Gui__Dialog__DlgPreferencePackManagement->setModal(false);
        gridLayout = new QGridLayout(Gui__Dialog__DlgPreferencePackManagement);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonOpenAddonManager = new QPushButton(Gui__Dialog__DlgPreferencePackManagement);
        pushButtonOpenAddonManager->setObjectName("pushButtonOpenAddonManager");

        horizontalLayout->addWidget(pushButtonOpenAddonManager);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        treeWidget = new QTreeWidget(Gui__Dialog__DlgPreferencePackManagement);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidget->setProperty("showDropIndicator", QVariant(false));
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget->setUniformRowHeights(true);
        treeWidget->setHeaderHidden(true);
        treeWidget->setColumnCount(2);
        treeWidget->header()->setStretchLastSection(false);

        gridLayout->addWidget(treeWidget, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgPreferencePackManagement);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgPreferencePackManagement);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgPreferencePackManagement)
    {
        Gui__Dialog__DlgPreferencePackManagement->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgPreferencePackManagement", "Manage Preference Packs", nullptr));
        pushButtonOpenAddonManager->setText(QCoreApplication::translate("Gui::Dialog::DlgPreferencePackManagement", "Open Addon Manager", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgPreferencePackManagement: public Ui_DlgPreferencePackManagement {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGPREFERENCEPACKMANAGEMENT_H
