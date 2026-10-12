/********************************************************************************
** Form generated from reading UI file 'DlgChooseIcon.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCHOOSEICON_H
#define UI_DLGCHOOSEICON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

namespace Gui {
namespace Dialog {

class Ui_DlgChooseIcon
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgChooseIcon)
    {
        if (Gui__Dialog__DlgChooseIcon->objectName().isEmpty())
            Gui__Dialog__DlgChooseIcon->setObjectName("Gui__Dialog__DlgChooseIcon");
        Gui__Dialog__DlgChooseIcon->resize(430, 370);
        gridLayout = new QGridLayout(Gui__Dialog__DlgChooseIcon);
        gridLayout->setObjectName("gridLayout");
        listWidget = new QListWidget(Gui__Dialog__DlgChooseIcon);
        listWidget->setObjectName("listWidget");
        listWidget->setGridSize(QSize(50, 50));
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(false);

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(Gui__Dialog__DlgChooseIcon);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        spacerItem = new QSpacerItem(38, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(spacerItem);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgChooseIcon);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgChooseIcon);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgChooseIcon, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgChooseIcon, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgChooseIcon);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgChooseIcon)
    {
        Gui__Dialog__DlgChooseIcon->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgChooseIcon", "Choose Icon", nullptr));
        addButton->setText(QCoreApplication::translate("Gui::Dialog::DlgChooseIcon", "Icon Folders", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgChooseIcon: public Ui_DlgChooseIcon {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGCHOOSEICON_H
