/********************************************************************************
** Form generated from reading UI file 'DlgDocumentObject.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDOCUMENTOBJECT_H
#define UI_DLGDOCUMENTOBJECT_H

#include <Gui/ExpressionCompleter.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgDocumentObject
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkObjectType;
    QCheckBox *checkSubObject;
    QTreeWidget *typeTree;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::ExpressionLineEdit *searchBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__DlgDocumentObject)
    {
        if (Gui__Dialog__DlgDocumentObject->objectName().isEmpty())
            Gui__Dialog__DlgDocumentObject->setObjectName("Gui__Dialog__DlgDocumentObject");
        Gui__Dialog__DlgDocumentObject->resize(436, 438);
        gridLayout = new QGridLayout(Gui__Dialog__DlgDocumentObject);
        gridLayout->setObjectName("gridLayout");
        treeWidget = new QTreeWidget(Gui__Dialog__DlgDocumentObject);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        treeWidget->setProperty("showDropIndicator", QVariant(false));
        treeWidget->setHeaderHidden(true);
        treeWidget->setExpandsOnDoubleClick(false);
        treeWidget->header()->setVisible(false);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        checkObjectType = new QCheckBox(Gui__Dialog__DlgDocumentObject);
        checkObjectType->setObjectName("checkObjectType");

        horizontalLayout_2->addWidget(checkObjectType);

        checkSubObject = new QCheckBox(Gui__Dialog__DlgDocumentObject);
        checkSubObject->setObjectName("checkSubObject");

        horizontalLayout_2->addWidget(checkSubObject);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        typeTree = new QTreeWidget(Gui__Dialog__DlgDocumentObject);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        typeTree->setHeaderItem(__qtreewidgetitem1);
        typeTree->setObjectName("typeTree");
        typeTree->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        typeTree->setRootIsDecorated(false);
        typeTree->setSortingEnabled(true);
        typeTree->header()->setVisible(false);

        gridLayout->addWidget(typeTree, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Gui__Dialog__DlgDocumentObject);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        searchBox = new Gui::ExpressionLineEdit(Gui__Dialog__DlgDocumentObject);
        searchBox->setObjectName("searchBox");

        horizontalLayout->addWidget(searchBox);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__DlgDocumentObject);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 10, 0, 1, 1);

        QWidget::setTabOrder(treeWidget, typeTree);
        QWidget::setTabOrder(typeTree, searchBox);
        QWidget::setTabOrder(searchBox, buttonBox);

        retranslateUi(Gui__Dialog__DlgDocumentObject);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__DlgDocumentObject, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__DlgDocumentObject, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgDocumentObject);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__DlgDocumentObject)
    {
        Gui__Dialog__DlgDocumentObject->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "Object", nullptr));
        checkObjectType->setText(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "Filter by type", nullptr));
#if QT_CONFIG(tooltip)
        checkSubObject->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "Synchronizes the 3D view selection with the full object hierarchy", nullptr));
#endif // QT_CONFIG(tooltip)
        checkSubObject->setText(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "Sync sub-object selection", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "Search", nullptr));
#if QT_CONFIG(tooltip)
        searchBox->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgDocumentObject", "A search pattern to filter the results above", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgDocumentObject: public Ui_DlgDocumentObject {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGDOCUMENTOBJECT_H
