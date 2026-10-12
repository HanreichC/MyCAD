/********************************************************************************
** Form generated from reading UI file 'TaskSelectLinkProperty.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSELECTLINKPROPERTY_H
#define UI_TASKSELECTLINKPROPERTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {
namespace TaskView {

class Ui_TaskSelectLinkProperty
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *Remove;
    QToolButton *Add;
    QToolButton *Invert;
    QSpacerItem *horizontalSpacer;
    QToolButton *Help;
    QListWidget *listWidget;

    void setupUi(QWidget *Gui__TaskView__TaskSelectLinkProperty)
    {
        if (Gui__TaskView__TaskSelectLinkProperty->objectName().isEmpty())
            Gui__TaskView__TaskSelectLinkProperty->setObjectName("Gui__TaskView__TaskSelectLinkProperty");
        Gui__TaskView__TaskSelectLinkProperty->resize(257, 313);
        verticalLayout = new QVBoxLayout(Gui__TaskView__TaskSelectLinkProperty);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Remove = new QToolButton(Gui__TaskView__TaskSelectLinkProperty);
        Remove->setObjectName("Remove");
        Remove->setText(QString::fromUtf8("\342\200\246"));

        horizontalLayout->addWidget(Remove);

        Add = new QToolButton(Gui__TaskView__TaskSelectLinkProperty);
        Add->setObjectName("Add");
        Add->setText(QString::fromUtf8("\342\200\246"));

        horizontalLayout->addWidget(Add);

        Invert = new QToolButton(Gui__TaskView__TaskSelectLinkProperty);
        Invert->setObjectName("Invert");
        Invert->setText(QString::fromUtf8("\342\200\246"));

        horizontalLayout->addWidget(Invert);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Help = new QToolButton(Gui__TaskView__TaskSelectLinkProperty);
        Help->setObjectName("Help");
        Help->setText(QString::fromUtf8("\342\200\246"));

        horizontalLayout->addWidget(Help);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(Gui__TaskView__TaskSelectLinkProperty);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);


        retranslateUi(Gui__TaskView__TaskSelectLinkProperty);

        QMetaObject::connectSlotsByName(Gui__TaskView__TaskSelectLinkProperty);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskView__TaskSelectLinkProperty)
    {
        Gui__TaskView__TaskSelectLinkProperty->setWindowTitle(QCoreApplication::translate("Gui::TaskView::TaskSelectLinkProperty", "Appearance", nullptr));
    } // retranslateUi

};

} // namespace TaskView
} // namespace Gui

namespace Gui {
namespace TaskView {
namespace Ui {
    class TaskSelectLinkProperty: public Ui_TaskSelectLinkProperty {};
} // namespace Ui
} // namespace TaskView
} // namespace Gui

#endif // UI_TASKSELECTLINKPROPERTY_H
