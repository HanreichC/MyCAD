/********************************************************************************
** Form generated from reading UI file 'DlgActivateWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGACTIVATEWINDOW_H
#define UI_DLGACTIVATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgActivateWindow
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgActivateWindow)
    {
        if (Gui__Dialog__DlgActivateWindow->objectName().isEmpty())
            Gui__Dialog__DlgActivateWindow->setObjectName("Gui__Dialog__DlgActivateWindow");
        Gui__Dialog__DlgActivateWindow->resize(341, 267);
        Gui__Dialog__DlgActivateWindow->setSizeGripEnabled(true);
        Gui__Dialog__DlgActivateWindow->setModal(true);
        gridLayout = new QGridLayout(Gui__Dialog__DlgActivateWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        treeWidget = new QTreeWidget(Gui__Dialog__DlgActivateWindow);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setRootIsDecorated(false);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgActivateWindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgActivateWindow);
        QObject::connect(treeWidget, &QTreeWidget::activated, Gui__Dialog__DlgActivateWindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgActivateWindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgActivateWindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgActivateWindow);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgActivateWindow)
    {
        Gui__Dialog__DlgActivateWindow->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgActivateWindow", "Choose Window", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgActivateWindow: public Ui_DlgActivateWindow {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGACTIVATEWINDOW_H
