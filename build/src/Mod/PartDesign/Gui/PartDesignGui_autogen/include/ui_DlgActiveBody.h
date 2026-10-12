/********************************************************************************
** Form generated from reading UI file 'DlgActiveBody.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGACTIVEBODY_H
#define UI_DLGACTIVEBODY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

namespace PartDesignGui {

class Ui_DlgActiveBody
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListWidget *bodySelect;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PartDesignGui__DlgActiveBody)
    {
        if (PartDesignGui__DlgActiveBody->objectName().isEmpty())
            PartDesignGui__DlgActiveBody->setObjectName("PartDesignGui__DlgActiveBody");
        PartDesignGui__DlgActiveBody->resize(480, 270);
        verticalLayout_2 = new QVBoxLayout(PartDesignGui__DlgActiveBody);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(PartDesignGui__DlgActiveBody);
        label->setObjectName("label");
        label->setScaledContents(true);
        label->setWordWrap(true);

        verticalLayout_2->addWidget(label);

        bodySelect = new QListWidget(PartDesignGui__DlgActiveBody);
        new QListWidgetItem(bodySelect);
        bodySelect->setObjectName("bodySelect");

        verticalLayout_2->addWidget(bodySelect);

        buttonBox = new QDialogButtonBox(PartDesignGui__DlgActiveBody);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PartDesignGui__DlgActiveBody);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, PartDesignGui__DlgActiveBody, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, PartDesignGui__DlgActiveBody, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(PartDesignGui__DlgActiveBody);
    } // setupUi

    void retranslateUi(QDialog *PartDesignGui__DlgActiveBody)
    {
        PartDesignGui__DlgActiveBody->setWindowTitle(QCoreApplication::translate("PartDesignGui::DlgActiveBody", "Active Body Required", nullptr));
        label->setText(QCoreApplication::translate("PartDesignGui::DlgActiveBody", "To create a new Part Design object, there must be an active body in the document.\n"
"Select a body from below, or create a new body.", nullptr));

        const bool __sortingEnabled = bodySelect->isSortingEnabled();
        bodySelect->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = bodySelect->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("PartDesignGui::DlgActiveBody", "Create New Body", nullptr));
        bodySelect->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class DlgActiveBody: public Ui_DlgActiveBody {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_DLGACTIVEBODY_H
