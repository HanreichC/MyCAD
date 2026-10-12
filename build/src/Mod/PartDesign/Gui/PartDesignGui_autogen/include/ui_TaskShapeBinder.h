/********************************************************************************
** Form generated from reading UI file 'TaskShapeBinder.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSHAPEBINDER_H
#define UI_TASKSHAPEBINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskShapeBinder
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonBase;
    QLineEdit *baseEdit;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *buttonRefAdd;
    QToolButton *buttonRefRemove;
    QListWidget *listWidgetReferences;

    void setupUi(QWidget *PartDesignGui__TaskShapeBinder)
    {
        if (PartDesignGui__TaskShapeBinder->objectName().isEmpty())
            PartDesignGui__TaskShapeBinder->setObjectName("PartDesignGui__TaskShapeBinder");
        PartDesignGui__TaskShapeBinder->resize(309, 331);
        PartDesignGui__TaskShapeBinder->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskShapeBinder);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonBase = new QToolButton(PartDesignGui__TaskShapeBinder);
        buttonBase->setObjectName("buttonBase");
        buttonBase->setCheckable(true);

        horizontalLayout->addWidget(buttonBase);

        baseEdit = new QLineEdit(PartDesignGui__TaskShapeBinder);
        baseEdit->setObjectName("baseEdit");

        horizontalLayout->addWidget(baseEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        buttonRefAdd = new QToolButton(PartDesignGui__TaskShapeBinder);
        buttonRefAdd->setObjectName("buttonRefAdd");
        buttonRefAdd->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonRefAdd->sizePolicy().hasHeightForWidth());
        buttonRefAdd->setSizePolicy(sizePolicy);
        buttonRefAdd->setCheckable(true);
        buttonRefAdd->setChecked(false);

        horizontalLayout_4->addWidget(buttonRefAdd);

        buttonRefRemove = new QToolButton(PartDesignGui__TaskShapeBinder);
        buttonRefRemove->setObjectName("buttonRefRemove");
        sizePolicy.setHeightForWidth(buttonRefRemove->sizePolicy().hasHeightForWidth());
        buttonRefRemove->setSizePolicy(sizePolicy);
        buttonRefRemove->setCheckable(true);

        horizontalLayout_4->addWidget(buttonRefRemove);


        verticalLayout->addLayout(horizontalLayout_4);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskShapeBinder);
        listWidgetReferences->setObjectName("listWidgetReferences");

        verticalLayout->addWidget(listWidgetReferences);

        QWidget::setTabOrder(buttonBase, baseEdit);
        QWidget::setTabOrder(baseEdit, buttonRefAdd);
        QWidget::setTabOrder(buttonRefAdd, buttonRefRemove);
        QWidget::setTabOrder(buttonRefRemove, listWidgetReferences);

        retranslateUi(PartDesignGui__TaskShapeBinder);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskShapeBinder);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskShapeBinder)
    {
        buttonBase->setText(QCoreApplication::translate("PartDesignGui::TaskShapeBinder", "Object", nullptr));
        buttonRefAdd->setText(QCoreApplication::translate("PartDesignGui::TaskShapeBinder", "Add Geometry", nullptr));
        buttonRefRemove->setText(QCoreApplication::translate("PartDesignGui::TaskShapeBinder", "Remove Geometry", nullptr));
        (void)PartDesignGui__TaskShapeBinder;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskShapeBinder: public Ui_TaskShapeBinder {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKSHAPEBINDER_H
