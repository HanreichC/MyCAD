/********************************************************************************
** Form generated from reading UI file 'TaskPipeParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPIPEPARAMETERS_H
#define UI_TASKPIPEPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskPipeParameters
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupprofile;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QToolButton *buttonProfileBase;
    QLineEdit *profileBaseEdit;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *comboBoxTransition;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonSpineBase;
    QLineEdit *spineBaseEdit;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *buttonRefAdd;
    QToolButton *buttonRefRemove;
    QListWidget *listWidgetReferences;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;

    void setupUi(QWidget *PartDesignGui__TaskPipeParameters)
    {
        if (PartDesignGui__TaskPipeParameters->objectName().isEmpty())
            PartDesignGui__TaskPipeParameters->setObjectName("PartDesignGui__TaskPipeParameters");
        PartDesignGui__TaskPipeParameters->resize(306, 421);
        PartDesignGui__TaskPipeParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_2 = new QVBoxLayout(PartDesignGui__TaskPipeParameters);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupprofile = new QGroupBox(PartDesignGui__TaskPipeParameters);
        groupprofile->setObjectName("groupprofile");
        vboxLayout = new QVBoxLayout(groupprofile);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        buttonProfileBase = new QToolButton(groupprofile);
        buttonProfileBase->setObjectName("buttonProfileBase");
        buttonProfileBase->setCheckable(true);

        hboxLayout->addWidget(buttonProfileBase);

        profileBaseEdit = new QLineEdit(groupprofile);
        profileBaseEdit->setObjectName("profileBaseEdit");

        hboxLayout->addWidget(profileBaseEdit);


        vboxLayout->addLayout(hboxLayout);


        verticalLayout_2->addWidget(groupprofile);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_2 = new QLabel(PartDesignGui__TaskPipeParameters);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_2);

        comboBoxTransition = new QComboBox(PartDesignGui__TaskPipeParameters);
        comboBoxTransition->addItem(QString());
        comboBoxTransition->addItem(QString());
        comboBoxTransition->addItem(QString());
        comboBoxTransition->setObjectName("comboBoxTransition");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxTransition->sizePolicy().hasHeightForWidth());
        comboBoxTransition->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, comboBoxTransition);


        verticalLayout_2->addLayout(formLayout);

        groupBox = new QGroupBox(PartDesignGui__TaskPipeParameters);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonSpineBase = new QToolButton(groupBox);
        buttonSpineBase->setObjectName("buttonSpineBase");
        buttonSpineBase->setCheckable(true);

        horizontalLayout->addWidget(buttonSpineBase);

        spineBaseEdit = new QLineEdit(groupBox);
        spineBaseEdit->setObjectName("spineBaseEdit");

        horizontalLayout->addWidget(spineBaseEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        buttonRefAdd = new QToolButton(groupBox);
        buttonRefAdd->setObjectName("buttonRefAdd");
        buttonRefAdd->setEnabled(true);
        sizePolicy.setHeightForWidth(buttonRefAdd->sizePolicy().hasHeightForWidth());
        buttonRefAdd->setSizePolicy(sizePolicy);
        buttonRefAdd->setCheckable(true);
        buttonRefAdd->setChecked(false);

        horizontalLayout_4->addWidget(buttonRefAdd);

        buttonRefRemove = new QToolButton(groupBox);
        buttonRefRemove->setObjectName("buttonRefRemove");
        sizePolicy.setHeightForWidth(buttonRefRemove->sizePolicy().hasHeightForWidth());
        buttonRefRemove->setSizePolicy(sizePolicy);
        buttonRefRemove->setCheckable(true);

        horizontalLayout_4->addWidget(buttonRefRemove);


        verticalLayout->addLayout(horizontalLayout_4);

        listWidgetReferences = new QListWidget(groupBox);
        listWidgetReferences->setObjectName("listWidgetReferences");

        verticalLayout->addWidget(listWidgetReferences);


        verticalLayout_2->addWidget(groupBox);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__TaskPipeParameters);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__TaskPipeParameters);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);

        operationLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(operationLayout);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(buttonProfileBase, profileBaseEdit);
        QWidget::setTabOrder(profileBaseEdit, comboBoxTransition);
        QWidget::setTabOrder(comboBoxTransition, buttonSpineBase);
        QWidget::setTabOrder(buttonSpineBase, spineBaseEdit);
        QWidget::setTabOrder(spineBaseEdit, buttonRefAdd);
        QWidget::setTabOrder(buttonRefAdd, buttonRefRemove);
        QWidget::setTabOrder(buttonRefRemove, listWidgetReferences);
        QWidget::setTabOrder(listWidgetReferences, comboOperation);

        retranslateUi(PartDesignGui__TaskPipeParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskPipeParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskPipeParameters)
    {
        groupprofile->setTitle(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Profile", nullptr));
        buttonProfileBase->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Object", nullptr));
        label_2->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Corner transition", nullptr));
        comboBoxTransition->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Transformed", nullptr));
        comboBoxTransition->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Right corner", nullptr));
        comboBoxTransition->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Round corner", nullptr));

        groupBox->setTitle(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Path to Sweep Along", nullptr));
        buttonSpineBase->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Object", nullptr));
        buttonRefAdd->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Add edge", nullptr));
        buttonRefRemove->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Remove edge", nullptr));
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPipeParameters", "Common", nullptr));

        (void)PartDesignGui__TaskPipeParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskPipeParameters: public Ui_TaskPipeParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPIPEPARAMETERS_H
