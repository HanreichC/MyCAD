/********************************************************************************
** Form generated from reading UI file 'TaskCommandLink.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKCOMMANDLINK_H
#define UI_TASKCOMMANDLINK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

namespace Gui {

class Ui_TaskCommandLinkDialog
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *objectsList;

    void setupUi(QWidget *Gui__TaskCommandLinkDialog)
    {
        if (Gui__TaskCommandLinkDialog->objectName().isEmpty())
            Gui__TaskCommandLinkDialog->setObjectName("Gui__TaskCommandLinkDialog");
        Gui__TaskCommandLinkDialog->resize(340, 212);
        gridLayout = new QGridLayout(Gui__TaskCommandLinkDialog);
        gridLayout->setObjectName("gridLayout");
        objectsList = new QTreeWidget(Gui__TaskCommandLinkDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        objectsList->setHeaderItem(__qtreewidgetitem);
        objectsList->setObjectName("objectsList");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(objectsList->sizePolicy().hasHeightForWidth());
        objectsList->setSizePolicy(sizePolicy);

        gridLayout->addWidget(objectsList, 0, 0, 1, 1);


        retranslateUi(Gui__TaskCommandLinkDialog);

        QMetaObject::connectSlotsByName(Gui__TaskCommandLinkDialog);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskCommandLinkDialog)
    {
        Gui__TaskCommandLinkDialog->setWindowTitle(QCoreApplication::translate("Gui::TaskCommandLinkDialog", "Insert", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class TaskCommandLinkDialog: public Ui_TaskCommandLinkDialog {};
} // namespace Ui
} // namespace Gui

#endif // UI_TASKCOMMANDLINK_H
