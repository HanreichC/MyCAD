/********************************************************************************
** Form generated from reading UI file 'DocumentRecovery.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTRECOVERY_H
#define UI_DOCUMENTRECOVERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>

namespace Gui {
namespace Dialog {

class Ui_DocumentRecovery
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QPushButton *buttonCleanup;
    QLabel *label_2;
    QTreeWidget *treeWidget;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *Gui__Dialog__DocumentRecovery)
    {
        if (Gui__Dialog__DocumentRecovery->objectName().isEmpty())
            Gui__Dialog__DocumentRecovery->setObjectName("Gui__Dialog__DocumentRecovery");
        Gui__Dialog__DocumentRecovery->resize(576, 495);
        gridLayout = new QGridLayout(Gui__Dialog__DocumentRecovery);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(Gui__Dialog__DocumentRecovery);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 2);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DocumentRecovery);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 4, 1, 1, 1);

        buttonCleanup = new QPushButton(Gui__Dialog__DocumentRecovery);
        buttonCleanup->setObjectName("buttonCleanup");
        buttonCleanup->setEnabled(true);

        gridLayout->addWidget(buttonCleanup, 4, 0, 1, 1);

        label_2 = new QLabel(Gui__Dialog__DocumentRecovery);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 2);

        treeWidget = new QTreeWidget(Gui__Dialog__DocumentRecovery);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

        gridLayout->addWidget(treeWidget, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(Gui__Dialog__DocumentRecovery);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DocumentRecovery, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DocumentRecovery, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DocumentRecovery);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DocumentRecovery)
    {
        Gui__Dialog__DocumentRecovery->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Document Recovery", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Press 'Start Recovery' to start the recovery process of the document listed below.\n"
"\n"
"The 'Status' column shows whether the document could be recovered.", nullptr));
        buttonCleanup->setText(QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Cleanup", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Status of recovered documents", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Status", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Gui::Dialog::DocumentRecovery", "Document name", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DocumentRecovery: public Ui_DocumentRecovery {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DOCUMENTRECOVERY_H
