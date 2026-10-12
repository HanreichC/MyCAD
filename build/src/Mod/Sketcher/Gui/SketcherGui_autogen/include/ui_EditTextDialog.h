/********************************************************************************
** Form generated from reading UI file 'EditTextDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTEXTDIALOG_H
#define UI_EDITTEXTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditTextDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_text;
    QLineEdit *lineEdit_text;
    QLabel *label_font;
    QComboBox *comboBox_font;
    QHBoxLayout *layoutType;
    QRadioButton *radioButton_height;
    QRadioButton *radioButton_width;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditTextDialog)
    {
        if (EditTextDialog->objectName().isEmpty())
            EditTextDialog->setObjectName("EditTextDialog");
        EditTextDialog->resize(320, 100);
        verticalLayout = new QVBoxLayout(EditTextDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_text = new QLabel(EditTextDialog);
        label_text->setObjectName("label_text");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_text);

        lineEdit_text = new QLineEdit(EditTextDialog);
        lineEdit_text->setObjectName("lineEdit_text");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_text);

        label_font = new QLabel(EditTextDialog);
        label_font->setObjectName("label_font");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_font);

        comboBox_font = new QComboBox(EditTextDialog);
        comboBox_font->setObjectName("comboBox_font");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, comboBox_font);

        layoutType = new QHBoxLayout();
        layoutType->setObjectName("layoutType");
        radioButton_height = new QRadioButton(EditTextDialog);
        radioButton_height->setObjectName("radioButton_height");

        layoutType->addWidget(radioButton_height);

        radioButton_width = new QRadioButton(EditTextDialog);
        radioButton_width->setObjectName("radioButton_width");

        layoutType->addWidget(radioButton_width);


        formLayout->setLayout(2, QFormLayout::ItemRole::SpanningRole, layoutType);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(EditTextDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EditTextDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, EditTextDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, EditTextDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(EditTextDialog);
    } // setupUi

    void retranslateUi(QDialog *EditTextDialog)
    {
        EditTextDialog->setWindowTitle(QCoreApplication::translate("EditTextDialog", "Edit Text", nullptr));
        label_text->setText(QCoreApplication::translate("EditTextDialog", "Text", nullptr));
        label_font->setText(QCoreApplication::translate("EditTextDialog", "Font", nullptr));
        radioButton_height->setText(QCoreApplication::translate("EditTextDialog", "Height", nullptr));
        radioButton_width->setText(QCoreApplication::translate("EditTextDialog", "Width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTextDialog: public Ui_EditTextDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTEXTDIALOG_H
