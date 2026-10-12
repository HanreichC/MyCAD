/********************************************************************************
** Form generated from reading UI file 'DlgCreateNewPreferencePack.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGCREATENEWPREFERENCEPACK_H
#define UI_DLGCREATENEWPREFERENCEPACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

namespace Gui {
namespace Dialog {

class Ui_DlgCreateNewPreferencePack
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgCreateNewPreferencePack)
    {
        if (Gui__Dialog__DlgCreateNewPreferencePack->objectName().isEmpty())
            Gui__Dialog__DlgCreateNewPreferencePack->setObjectName("Gui__Dialog__DlgCreateNewPreferencePack");
        Gui__Dialog__DlgCreateNewPreferencePack->setWindowModality(Qt::ApplicationModal);
        Gui__Dialog__DlgCreateNewPreferencePack->resize(580, 520);
        Gui__Dialog__DlgCreateNewPreferencePack->setModal(true);
        verticalLayout = new QVBoxLayout(Gui__Dialog__DlgCreateNewPreferencePack);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui__Dialog__DlgCreateNewPreferencePack);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(Gui__Dialog__DlgCreateNewPreferencePack);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(Gui__Dialog__DlgCreateNewPreferencePack);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(Gui__Dialog__DlgCreateNewPreferencePack);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setColumnCount(1);
        treeWidget->header()->setMinimumSectionSize(50);
        treeWidget->header()->setDefaultSectionSize(250);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(treeWidget);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgCreateNewPreferencePack);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Gui__Dialog__DlgCreateNewPreferencePack);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgCreateNewPreferencePack, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgCreateNewPreferencePack, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgCreateNewPreferencePack);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgCreateNewPreferencePack)
    {
        Gui__Dialog__DlgCreateNewPreferencePack->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgCreateNewPreferencePack", "Create New Preference Pack", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgCreateNewPreferencePack", "Name", nullptr));
        pushButton->setText(QCoreApplication::translate("Gui::Dialog::DlgCreateNewPreferencePack", "Browse", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Gui::Dialog::DlgCreateNewPreferencePack", "Property group templates", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgCreateNewPreferencePack: public Ui_DlgCreateNewPreferencePack {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGCREATENEWPREFERENCEPACK_H
