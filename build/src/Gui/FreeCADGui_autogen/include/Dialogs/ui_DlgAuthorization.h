/********************************************************************************
** Form generated from reading UI file 'DlgAuthorization.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGAUTHORIZATION_H
#define UI_DLGAUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

namespace Gui {
namespace Dialog {

class Ui_DlgAuthorization
{
public:
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *siteDescription;
    QLabel *textLabel1;
    QLineEdit *username;
    QLabel *textLabel2;
    QLineEdit *password;
    QSpacerItem *spacerItem;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgAuthorization)
    {
        if (Gui__Dialog__DlgAuthorization->objectName().isEmpty())
            Gui__Dialog__DlgAuthorization->setObjectName("Gui__Dialog__DlgAuthorization");
        Gui__Dialog__DlgAuthorization->resize(284, 128);
        Gui__Dialog__DlgAuthorization->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(Gui__Dialog__DlgAuthorization);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        label_4 = new QLabel(Gui__Dialog__DlgAuthorization);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        siteDescription = new QLabel(Gui__Dialog__DlgAuthorization);
        siteDescription->setObjectName("siteDescription");
        QFont font;
        font.setBold(true);
        siteDescription->setFont(font);
        siteDescription->setWordWrap(true);

        gridLayout->addWidget(siteDescription, 0, 1, 1, 1);

        textLabel1 = new QLabel(Gui__Dialog__DlgAuthorization);
        textLabel1->setObjectName("textLabel1");

        gridLayout->addWidget(textLabel1, 1, 0, 1, 1);

        username = new QLineEdit(Gui__Dialog__DlgAuthorization);
        username->setObjectName("username");

        gridLayout->addWidget(username, 1, 1, 1, 1);

        textLabel2 = new QLabel(Gui__Dialog__DlgAuthorization);
        textLabel2->setObjectName("textLabel2");

        gridLayout->addWidget(textLabel2, 2, 0, 1, 1);

        password = new QLineEdit(Gui__Dialog__DlgAuthorization);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password, 2, 1, 1, 1);

        spacerItem = new QSpacerItem(21, 41, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem, 3, 0, 1, 2);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgAuthorization);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 2);

        QWidget::setTabOrder(username, password);

        retranslateUi(Gui__Dialog__DlgAuthorization);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgAuthorization);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgAuthorization)
    {
        Gui__Dialog__DlgAuthorization->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgAuthorization", "Authorization", nullptr));
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgAuthorization", "Site", nullptr));
        siteDescription->setText(QCoreApplication::translate("Gui::Dialog::DlgAuthorization", "%1 at %2", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgAuthorization", "Username", nullptr));
        textLabel2->setText(QCoreApplication::translate("Gui::Dialog::DlgAuthorization", "Password", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgAuthorization: public Ui_DlgAuthorization {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGAUTHORIZATION_H
