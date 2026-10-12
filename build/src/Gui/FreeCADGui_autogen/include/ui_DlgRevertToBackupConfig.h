/********************************************************************************
** Form generated from reading UI file 'DlgRevertToBackupConfig.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGREVERTTOBACKUPCONFIG_H
#define UI_DLGREVERTTOBACKUPCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace Gui {
namespace Dialog {

class Ui_DlgRevertToBackupConfig
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgRevertToBackupConfig)
    {
        if (Gui__Dialog__DlgRevertToBackupConfig->objectName().isEmpty())
            Gui__Dialog__DlgRevertToBackupConfig->setObjectName("Gui__Dialog__DlgRevertToBackupConfig");
        Gui__Dialog__DlgRevertToBackupConfig->resize(610, 471);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgRevertToBackupConfig);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Gui__Dialog__DlgRevertToBackupConfig);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(Gui__Dialog__DlgRevertToBackupConfig);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        listWidget = new QListWidget(Gui__Dialog__DlgRevertToBackupConfig);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgRevertToBackupConfig);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Gui__Dialog__DlgRevertToBackupConfig);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgRevertToBackupConfig, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgRevertToBackupConfig, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgRevertToBackupConfig);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgRevertToBackupConfig)
    {
        Gui__Dialog__DlgRevertToBackupConfig->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgRevertToBackupConfig", "Revert to Backup Config", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgRevertToBackupConfig", "WARNING: this process will undo any preference changes made since the specified date, and will also reset your recent files and Macros to their state on that date.", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgRevertToBackupConfig", "Available backup files", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgRevertToBackupConfig: public Ui_DlgRevertToBackupConfig {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGREVERTTOBACKUPCONFIG_H
