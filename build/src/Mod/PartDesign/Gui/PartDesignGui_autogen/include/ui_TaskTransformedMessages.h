/********************************************************************************
** Form generated from reading UI file 'TaskTransformedMessages.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKTRANSFORMEDMESSAGES_H
#define UI_TASKTRANSFORMEDMESSAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskTransformedMessages
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTransformationStatus;

    void setupUi(QWidget *TaskTransformedMessages)
    {
        if (TaskTransformedMessages->objectName().isEmpty())
            TaskTransformedMessages->setObjectName("TaskTransformedMessages");
        TaskTransformedMessages->resize(228, 89);
        TaskTransformedMessages->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(TaskTransformedMessages);
        verticalLayout->setObjectName("verticalLayout");
        labelTransformationStatus = new QLabel(TaskTransformedMessages);
        labelTransformationStatus->setObjectName("labelTransformationStatus");
        QFont font;
        font.setPointSize(9);
        labelTransformationStatus->setFont(font);
        labelTransformationStatus->setWordWrap(true);

        verticalLayout->addWidget(labelTransformationStatus);


        retranslateUi(TaskTransformedMessages);

        QMetaObject::connectSlotsByName(TaskTransformedMessages);
    } // setupUi

    void retranslateUi(QWidget *TaskTransformedMessages)
    {
        labelTransformationStatus->setText(QCoreApplication::translate("TaskTransformedMessages", "No message", nullptr));
        (void)TaskTransformedMessages;
    } // retranslateUi

};

namespace Ui {
    class TaskTransformedMessages: public Ui_TaskTransformedMessages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKTRANSFORMEDMESSAGES_H
