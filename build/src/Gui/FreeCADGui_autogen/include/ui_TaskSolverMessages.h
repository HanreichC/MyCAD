/********************************************************************************
** Form generated from reading UI file 'TaskSolverMessages.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSOLVERMESSAGES_H
#define UI_TASKSOLVERMESSAGES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "Gui/Widgets.h"

QT_BEGIN_NAMESPACE

class Ui_TaskSolverMessages
{
public:
    QHBoxLayout *horizontalLayout;
    Gui::StatefulLabel *labelStatus;
    Gui::UrlLabel *labelStatusLink;
    QToolButton *manualUpdate;
    QToolButton *settingsButton;

    void setupUi(QWidget *TaskSolverMessages)
    {
        if (TaskSolverMessages->objectName().isEmpty())
            TaskSolverMessages->setObjectName("TaskSolverMessages");
        TaskSolverMessages->resize(350, 48);
        TaskSolverMessages->setMinimumSize(QSize(320, 0));
        TaskSolverMessages->setWindowTitle(QString::fromUtf8("Form"));
        horizontalLayout = new QHBoxLayout(TaskSolverMessages);
        horizontalLayout->setObjectName("horizontalLayout");
        labelStatus = new Gui::StatefulLabel(TaskSolverMessages);
        labelStatus->setObjectName("labelStatus");

        horizontalLayout->addWidget(labelStatus);

        labelStatusLink = new Gui::UrlLabel(TaskSolverMessages);
        labelStatusLink->setObjectName("labelStatusLink");

        horizontalLayout->addWidget(labelStatusLink);

        manualUpdate = new QToolButton(TaskSolverMessages);
        manualUpdate->setObjectName("manualUpdate");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(manualUpdate->sizePolicy().hasHeightForWidth());
        manualUpdate->setSizePolicy(sizePolicy);
        manualUpdate->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/view-refresh.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        manualUpdate->setIcon(icon);

        horizontalLayout->addWidget(manualUpdate);

        settingsButton = new QToolButton(TaskSolverMessages);
        settingsButton->setObjectName("settingsButton");
        sizePolicy.setHeightForWidth(settingsButton->sizePolicy().hasHeightForWidth());
        settingsButton->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/preferences-general.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon1);
        settingsButton->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout->addWidget(settingsButton);


        retranslateUi(TaskSolverMessages);

        QMetaObject::connectSlotsByName(TaskSolverMessages);
    } // setupUi

    void retranslateUi(QWidget *TaskSolverMessages)
    {
        labelStatus->setText(QCoreApplication::translate("TaskSolverMessages", "DOF", nullptr));
        labelStatusLink->setText(QCoreApplication::translate("TaskSolverMessages", "Link", nullptr));
#if QT_CONFIG(tooltip)
        manualUpdate->setToolTip(QCoreApplication::translate("TaskSolverMessages", "Forces the recomputation of the active document", nullptr));
#endif // QT_CONFIG(tooltip)
        manualUpdate->setText(QString());
#if QT_CONFIG(tooltip)
        settingsButton->setToolTip(QCoreApplication::translate("TaskSolverMessages", "Settings", nullptr));
#endif // QT_CONFIG(tooltip)
        settingsButton->setText(QString());
        (void)TaskSolverMessages;
    } // retranslateUi

};

namespace Ui {
    class TaskSolverMessages: public Ui_TaskSolverMessages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKSOLVERMESSAGES_H
