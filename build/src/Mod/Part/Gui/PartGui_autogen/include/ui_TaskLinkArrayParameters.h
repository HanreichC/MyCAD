/********************************************************************************
** Form generated from reading UI file 'TaskLinkArrayParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKLINKARRAYPARAMETERS_H
#define UI_TASKLINKARRAYPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskLinkArrayParameters
{
public:
    QGridLayout *gridLayout;
    QLabel *linkedObjectLabel;
    QPushButton *linkedObjectButton;
    QWidget *parametersWidgetPlaceholder;
    QWidget *parametersWidgetPlaceholder2;

    void setupUi(QWidget *TaskLinkArrayParameters)
    {
        if (TaskLinkArrayParameters->objectName().isEmpty())
            TaskLinkArrayParameters->setObjectName("TaskLinkArrayParameters");
        TaskLinkArrayParameters->resize(300, 180);
        gridLayout = new QGridLayout(TaskLinkArrayParameters);
        gridLayout->setObjectName("gridLayout");
        linkedObjectLabel = new QLabel(TaskLinkArrayParameters);
        linkedObjectLabel->setObjectName("linkedObjectLabel");

        gridLayout->addWidget(linkedObjectLabel, 0, 0, 1, 1);

        linkedObjectButton = new QPushButton(TaskLinkArrayParameters);
        linkedObjectButton->setObjectName("linkedObjectButton");
        linkedObjectButton->setCheckable(true);

        gridLayout->addWidget(linkedObjectButton, 0, 1, 1, 1);

        parametersWidgetPlaceholder = new QWidget(TaskLinkArrayParameters);
        parametersWidgetPlaceholder->setObjectName("parametersWidgetPlaceholder");

        gridLayout->addWidget(parametersWidgetPlaceholder, 1, 0, 1, 2);

        parametersWidgetPlaceholder2 = new QWidget(TaskLinkArrayParameters);
        parametersWidgetPlaceholder2->setObjectName("parametersWidgetPlaceholder2");

        gridLayout->addWidget(parametersWidgetPlaceholder2, 2, 0, 1, 2);

#if QT_CONFIG(shortcut)
        linkedObjectLabel->setBuddy(linkedObjectButton);
#endif // QT_CONFIG(shortcut)

        retranslateUi(TaskLinkArrayParameters);

        QMetaObject::connectSlotsByName(TaskLinkArrayParameters);
    } // setupUi

    void retranslateUi(QWidget *TaskLinkArrayParameters)
    {
        linkedObjectLabel->setText(QCoreApplication::translate("TaskLinkArrayParameters", "Linked object", nullptr));
        linkedObjectButton->setText(QCoreApplication::translate("TaskLinkArrayParameters", "Select Object", nullptr));
        (void)TaskLinkArrayParameters;
    } // retranslateUi

};

namespace Ui {
    class TaskLinkArrayParameters: public Ui_TaskLinkArrayParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKLINKARRAYPARAMETERS_H
