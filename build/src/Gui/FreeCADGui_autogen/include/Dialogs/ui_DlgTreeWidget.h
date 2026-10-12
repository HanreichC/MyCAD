/********************************************************************************
** Form generated from reading UI file 'DlgTreeWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTREEWIDGET_H
#define UI_DLGTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

namespace Gui {

class Ui_DlgTreeWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__DlgTreeWidget)
    {
        if (Gui__DlgTreeWidget->objectName().isEmpty())
            Gui__DlgTreeWidget->setObjectName("Gui__DlgTreeWidget");
        Gui__DlgTreeWidget->resize(396, 281);
        gridLayout = new QGridLayout(Gui__DlgTreeWidget);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(Gui__DlgTreeWidget);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        treeWidget = new QTreeWidget(groupBox);
        treeWidget->setObjectName("treeWidget");

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__DlgTreeWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Gui__DlgTreeWidget);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__DlgTreeWidget, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__DlgTreeWidget, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__DlgTreeWidget);
    } // setupUi

    void retranslateUi(QDialog *Gui__DlgTreeWidget)
    {
        Gui__DlgTreeWidget->setWindowTitle(QCoreApplication::translate("Gui::DlgTreeWidget", "Dialog", nullptr));
        groupBox->setTitle(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Gui::DlgTreeWidget", "Items", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class DlgTreeWidget: public Ui_DlgTreeWidget {};
} // namespace Ui
} // namespace Gui

#endif // UI_DLGTREEWIDGET_H
