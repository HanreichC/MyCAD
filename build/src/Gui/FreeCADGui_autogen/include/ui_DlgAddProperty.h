/********************************************************************************
** Form generated from reading UI file 'DlgAddProperty.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGADDPROPERTY_H
#define UI_DLGADDPROPERTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

namespace Gui {
namespace Dialog {

class Ui_DlgAddProperty
{
public:
    QFormLayout *formLayout;
    QLabel *labelGroup;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelValue;
    QLabel *labelToolTip;
    QLineEdit *lineEditToolTip;
    QLabel *labelError;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgAddProperty)
    {
        if (Gui__Dialog__DlgAddProperty->objectName().isEmpty())
            Gui__Dialog__DlgAddProperty->setObjectName("Gui__Dialog__DlgAddProperty");
        Gui__Dialog__DlgAddProperty->resize(418, 258);
        formLayout = new QFormLayout(Gui__Dialog__DlgAddProperty);
        formLayout->setObjectName("formLayout");
        labelGroup = new QLabel(Gui__Dialog__DlgAddProperty);
        labelGroup->setObjectName("labelGroup");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelGroup);

        labelType = new QLabel(Gui__Dialog__DlgAddProperty);
        labelType->setObjectName("labelType");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelType);

        comboBoxType = new QComboBox(Gui__Dialog__DlgAddProperty);
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setEditable(true);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, comboBoxType);

        labelName = new QLabel(Gui__Dialog__DlgAddProperty);
        labelName->setObjectName("labelName");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelName);

        lineEditName = new QLineEdit(Gui__Dialog__DlgAddProperty);
        lineEditName->setObjectName("lineEditName");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditName);

        labelValue = new QLabel(Gui__Dialog__DlgAddProperty);
        labelValue->setObjectName("labelValue");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelValue);

        labelToolTip = new QLabel(Gui__Dialog__DlgAddProperty);
        labelToolTip->setObjectName("labelToolTip");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelToolTip);

        lineEditToolTip = new QLineEdit(Gui__Dialog__DlgAddProperty);
        lineEditToolTip->setObjectName("lineEditToolTip");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, lineEditToolTip);

        labelError = new QLabel(Gui__Dialog__DlgAddProperty);
        labelError->setObjectName("labelError");

        formLayout->setWidget(5, QFormLayout::ItemRole::SpanningRole, labelError);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgAddProperty);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Close|QDialogButtonBox::StandardButton::Ok);

        formLayout->setWidget(6, QFormLayout::ItemRole::SpanningRole, buttonBox);


        retranslateUi(Gui__Dialog__DlgAddProperty);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgAddProperty, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgAddProperty, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgAddProperty);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgAddProperty)
    {
        Gui__Dialog__DlgAddProperty->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Add Property", nullptr));
        labelGroup->setText(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Group", nullptr));
        labelType->setText(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Type", nullptr));
        labelName->setText(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Name", nullptr));
        labelValue->setText(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Value", nullptr));
        labelToolTip->setText(QCoreApplication::translate("Gui::Dialog::DlgAddProperty", "Tooltip", nullptr));
        labelError->setText(QString());
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgAddProperty: public Ui_DlgAddProperty {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGADDPROPERTY_H
