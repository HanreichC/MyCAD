/********************************************************************************
** Form generated from reading UI file 'DlgObjectSelection.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGOBJECTSELECTION_H
#define UI_DLGOBJECTSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

namespace Gui {

class Ui_DlgObjectSelection
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSplitter *vsplitter;
    QTreeWidget *treeWidget;
    QSplitter *splitter;
    QTreeWidget *depList;
    QTreeWidget *inList;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxAutoDeps;
    QCheckBox *checkBoxShowDeps;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__DlgObjectSelection)
    {
        if (Gui__DlgObjectSelection->objectName().isEmpty())
            Gui__DlgObjectSelection->setObjectName("Gui__DlgObjectSelection");
        Gui__DlgObjectSelection->resize(795, 375);
        Gui__DlgObjectSelection->setSizeGripEnabled(true);
        Gui__DlgObjectSelection->setModal(true);
        verticalLayout = new QVBoxLayout(Gui__DlgObjectSelection);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Gui__DlgObjectSelection);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        vsplitter = new QSplitter(Gui__DlgObjectSelection);
        vsplitter->setObjectName("vsplitter");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(vsplitter->sizePolicy().hasHeightForWidth());
        vsplitter->setSizePolicy(sizePolicy1);
        vsplitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(vsplitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        vsplitter->addWidget(treeWidget);
        treeWidget->header()->setVisible(false);
        splitter = new QSplitter(vsplitter);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        depList = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem1->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        depList->setHeaderItem(__qtreewidgetitem1);
        depList->setObjectName("depList");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(depList->sizePolicy().hasHeightForWidth());
        depList->setSizePolicy(sizePolicy2);
        depList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        depList->setRootIsDecorated(false);
        depList->setSortingEnabled(true);
        depList->setColumnCount(3);
        splitter->addWidget(depList);
        depList->header()->setProperty("showSortIndicator", QVariant(true));
        inList = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem2->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem2->setText(0, QString::fromUtf8("1"));
        inList->setHeaderItem(__qtreewidgetitem2);
        inList->setObjectName("inList");
        sizePolicy2.setHeightForWidth(inList->sizePolicy().hasHeightForWidth());
        inList->setSizePolicy(sizePolicy2);
        inList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        inList->setRootIsDecorated(false);
        inList->setSortingEnabled(true);
        inList->setColumnCount(3);
        splitter->addWidget(inList);
        inList->header()->setProperty("showSortIndicator", QVariant(true));
        vsplitter->addWidget(splitter);

        verticalLayout->addWidget(vsplitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        checkBoxAutoDeps = new QCheckBox(Gui__DlgObjectSelection);
        checkBoxAutoDeps->setObjectName("checkBoxAutoDeps");

        horizontalLayout->addWidget(checkBoxAutoDeps);

        checkBoxShowDeps = new QCheckBox(Gui__DlgObjectSelection);
        checkBoxShowDeps->setObjectName("checkBoxShowDeps");
        checkBoxShowDeps->setChecked(true);

        horizontalLayout->addWidget(checkBoxShowDeps);

        buttonBox = new QDialogButtonBox(Gui__DlgObjectSelection);
        buttonBox->setObjectName("buttonBox");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy3);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Gui__DlgObjectSelection);

        QMetaObject::connectSlotsByName(Gui__DlgObjectSelection);
    } // setupUi

    void retranslateUi(QDialog *Gui__DlgObjectSelection)
    {
        Gui__DlgObjectSelection->setWindowTitle(QCoreApplication::translate("Gui::DlgObjectSelection", "Object Selection", nullptr));
        label->setText(QCoreApplication::translate("Gui::DlgObjectSelection", "The selected objects contain other dependencies. Select which objects to export. All dependencies are auto-selected by default.", nullptr));
        checkBoxAutoDeps->setText(QCoreApplication::translate("Gui::DlgObjectSelection", "Auto select depending objects", nullptr));
        checkBoxShowDeps->setText(QCoreApplication::translate("Gui::DlgObjectSelection", "Show dependencies", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class DlgObjectSelection: public Ui_DlgObjectSelection {};
} // namespace Ui
} // namespace Gui

#endif // UI_DLGOBJECTSELECTION_H
