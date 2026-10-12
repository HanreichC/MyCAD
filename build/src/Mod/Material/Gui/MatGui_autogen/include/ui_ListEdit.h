/********************************************************************************
** Form generated from reading UI file 'ListEdit.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTEDIT_H
#define UI_LISTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

namespace MatGui {

class Ui_ListEdit
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonDeleteRow;
    QDialogButtonBox *standardButtons;

    void setupUi(QDialog *MatGui__ListEdit)
    {
        if (MatGui__ListEdit->objectName().isEmpty())
            MatGui__ListEdit->setObjectName("MatGui__ListEdit");
        MatGui__ListEdit->resize(400, 300);
        verticalLayout = new QVBoxLayout(MatGui__ListEdit);
        verticalLayout->setObjectName("verticalLayout");
        listView = new QListView(MatGui__ListEdit);
        listView->setObjectName("listView");

        verticalLayout->addWidget(listView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonDeleteRow = new QPushButton(MatGui__ListEdit);
        buttonDeleteRow->setObjectName("buttonDeleteRow");
        buttonDeleteRow->setEnabled(false);

        horizontalLayout->addWidget(buttonDeleteRow);


        verticalLayout->addLayout(horizontalLayout);

        standardButtons = new QDialogButtonBox(MatGui__ListEdit);
        standardButtons->setObjectName("standardButtons");
        standardButtons->setOrientation(Qt::Horizontal);
        standardButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(standardButtons);


        retranslateUi(MatGui__ListEdit);
        QObject::connect(standardButtons, &QDialogButtonBox::accepted, MatGui__ListEdit, qOverload<>(&QDialog::accept));
        QObject::connect(standardButtons, &QDialogButtonBox::rejected, MatGui__ListEdit, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(MatGui__ListEdit);
    } // setupUi

    void retranslateUi(QDialog *MatGui__ListEdit)
    {
        MatGui__ListEdit->setWindowTitle(QCoreApplication::translate("MatGui::ListEdit", "List Edit", nullptr));
        buttonDeleteRow->setText(QCoreApplication::translate("MatGui::ListEdit", "Delete Row", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class ListEdit: public Ui_ListEdit {};
} // namespace Ui
} // namespace MatGui

#endif // UI_LISTEDIT_H
