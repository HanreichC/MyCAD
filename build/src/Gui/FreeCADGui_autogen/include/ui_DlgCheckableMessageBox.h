/********************************************************************************
** Form generated from reading UI file 'DlgCheckableMessageBox.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCHECKABLEMESSAGEBOX_H
#define UI_DLGCHECKABLEMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace Gui {
namespace Dialog {

class Ui_DlgCheckableMessageBox
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *pixmapLabel;
    QSpacerItem *pixmapSpacer;
    QLabel *messageLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *checkBoxLeftSpacer;
    QCheckBox *checkBox;
    QSpacerItem *checkBoxRightSpacer;
    QSpacerItem *buttonSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgCheckableMessageBox)
    {
        if (Gui__Dialog__DlgCheckableMessageBox->objectName().isEmpty())
            Gui__Dialog__DlgCheckableMessageBox->setObjectName("Gui__Dialog__DlgCheckableMessageBox");
        Gui__Dialog__DlgCheckableMessageBox->resize(195, 122);
        verticalLayout_2 = new QVBoxLayout(Gui__Dialog__DlgCheckableMessageBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pixmapLabel = new QLabel(Gui__Dialog__DlgCheckableMessageBox);
        pixmapLabel->setObjectName("pixmapLabel");

        verticalLayout->addWidget(pixmapLabel);

        pixmapSpacer = new QSpacerItem(0, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout->addItem(pixmapSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        messageLabel = new QLabel(Gui__Dialog__DlgCheckableMessageBox);
        messageLabel->setObjectName("messageLabel");

        horizontalLayout_2->addWidget(messageLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        checkBoxLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(checkBoxLeftSpacer);

        checkBox = new QCheckBox(Gui__Dialog__DlgCheckableMessageBox);
        checkBox->setObjectName("checkBox");

        horizontalLayout->addWidget(checkBox);

        checkBoxRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(checkBoxRightSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonSpacer = new QSpacerItem(0, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_2->addItem(buttonSpacer);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgCheckableMessageBox);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Gui__Dialog__DlgCheckableMessageBox);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgCheckableMessageBox, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgCheckableMessageBox, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgCheckableMessageBox);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgCheckableMessageBox)
    {
        Gui__Dialog__DlgCheckableMessageBox->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgCheckableMessageBox", "Dialog", nullptr));
        messageLabel->setText(QCoreApplication::translate("Gui::Dialog::DlgCheckableMessageBox", "TextLabel", nullptr));
        checkBox->setText(QCoreApplication::translate("Gui::Dialog::DlgCheckableMessageBox", "CheckBox", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgCheckableMessageBox: public Ui_DlgCheckableMessageBox {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGCHECKABLEMESSAGEBOX_H
