/********************************************************************************
** Form generated from reading UI file 'TextEdit.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDIT_H
#define UI_TEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

namespace MatGui {

class Ui_TextEdit
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__TextEdit)
    {
        if (MatGui__TextEdit->objectName().isEmpty())
            MatGui__TextEdit->setObjectName("MatGui__TextEdit");
        MatGui__TextEdit->resize(400, 300);
        verticalLayout = new QVBoxLayout(MatGui__TextEdit);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(MatGui__TextEdit);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        standardButtons = new QDialogButtonBox(MatGui__TextEdit);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__TextEdit);
        QObject::connect(standardButtons, &QDialogButtonBox::accepted, MatGui__TextEdit, qOverload<>(&QDialog::accept));
        QObject::connect(standardButtons, &QDialogButtonBox::rejected, MatGui__TextEdit, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(MatGui__TextEdit);
    } // setupUi

    void retranslateUi(QDialog *MatGui__TextEdit)
    {
        MatGui__TextEdit->setWindowTitle(QCoreApplication::translate("MatGui::TextEdit", "Text Edit", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class TextEdit: public Ui_TextEdit {};
} // namespace Ui
} // namespace MatGui

#endif // UI_TEXTEDIT_H
