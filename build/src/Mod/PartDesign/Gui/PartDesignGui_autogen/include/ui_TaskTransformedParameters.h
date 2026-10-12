/********************************************************************************
** Form generated from reading UI file 'TaskTransformedParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKTRANSFORMEDPARAMETERS_H
#define UI_TASKTRANSFORMEDPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskTransformedParameters
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioTransformBody;
    QRadioButton *radioTransformToolShapes;
    QWidget *groupFeatureList;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonAddFeature;
    QPushButton *buttonRemoveFeature;
    QListWidget *listWidgetFeatures;
    QWidget *featureUI;
    QCheckBox *checkBoxUpdateView;
    QButtonGroup *buttonGroupMode;

    void setupUi(QWidget *PartDesignGui__TaskTransformedParameters)
    {
        if (PartDesignGui__TaskTransformedParameters->objectName().isEmpty())
            PartDesignGui__TaskTransformedParameters->setObjectName("PartDesignGui__TaskTransformedParameters");
        PartDesignGui__TaskTransformedParameters->resize(297, 248);
        PartDesignGui__TaskTransformedParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskTransformedParameters);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(PartDesignGui__TaskTransformedParameters);
        widget->setObjectName("widget");
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioTransformBody = new QRadioButton(widget);
        buttonGroupMode = new QButtonGroup(PartDesignGui__TaskTransformedParameters);
        buttonGroupMode->setObjectName("buttonGroupMode");
        buttonGroupMode->addButton(radioTransformBody);
        radioTransformBody->setObjectName("radioTransformBody");
        radioTransformBody->setChecked(true);

        verticalLayout_3->addWidget(radioTransformBody);

        radioTransformToolShapes = new QRadioButton(widget);
        buttonGroupMode->addButton(radioTransformToolShapes);
        radioTransformToolShapes->setObjectName("radioTransformToolShapes");

        verticalLayout_3->addWidget(radioTransformToolShapes);


        verticalLayout->addWidget(widget);

        groupFeatureList = new QWidget(PartDesignGui__TaskTransformedParameters);
        groupFeatureList->setObjectName("groupFeatureList");
        verticalLayout_2 = new QVBoxLayout(groupFeatureList);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buttonAddFeature = new QPushButton(groupFeatureList);
        buttonAddFeature->setObjectName("buttonAddFeature");
        buttonAddFeature->setCheckable(true);

        horizontalLayout->addWidget(buttonAddFeature);

        buttonRemoveFeature = new QPushButton(groupFeatureList);
        buttonRemoveFeature->setObjectName("buttonRemoveFeature");
        buttonRemoveFeature->setCheckable(true);

        horizontalLayout->addWidget(buttonRemoveFeature);


        verticalLayout_2->addLayout(horizontalLayout);

        listWidgetFeatures = new QListWidget(groupFeatureList);
        listWidgetFeatures->setObjectName("listWidgetFeatures");
        listWidgetFeatures->setMaximumSize(QSize(16777215, 120));

        verticalLayout_2->addWidget(listWidgetFeatures);


        verticalLayout->addWidget(groupFeatureList);

        featureUI = new QWidget(PartDesignGui__TaskTransformedParameters);
        featureUI->setObjectName("featureUI");

        verticalLayout->addWidget(featureUI);

        checkBoxUpdateView = new QCheckBox(PartDesignGui__TaskTransformedParameters);
        checkBoxUpdateView->setObjectName("checkBoxUpdateView");
        checkBoxUpdateView->setChecked(true);

        verticalLayout->addWidget(checkBoxUpdateView);

        QWidget::setTabOrder(radioTransformBody, radioTransformToolShapes);
        QWidget::setTabOrder(radioTransformToolShapes, buttonAddFeature);
        QWidget::setTabOrder(buttonAddFeature, buttonRemoveFeature);
        QWidget::setTabOrder(buttonRemoveFeature, listWidgetFeatures);
        QWidget::setTabOrder(listWidgetFeatures, checkBoxUpdateView);

        retranslateUi(PartDesignGui__TaskTransformedParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskTransformedParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskTransformedParameters)
    {
        radioTransformBody->setText(QCoreApplication::translate("PartDesignGui::TaskTransformedParameters", "Transform body", nullptr));
        radioTransformToolShapes->setText(QCoreApplication::translate("PartDesignGui::TaskTransformedParameters", "Transform tool shapes", nullptr));
        buttonAddFeature->setText(QCoreApplication::translate("PartDesignGui::TaskTransformedParameters", "Add Feature", nullptr));
        buttonRemoveFeature->setText(QCoreApplication::translate("PartDesignGui::TaskTransformedParameters", "Remove Feature", nullptr));
        checkBoxUpdateView->setText(QCoreApplication::translate("PartDesignGui::TaskTransformedParameters", "Recompute on change", nullptr));
        (void)PartDesignGui__TaskTransformedParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskTransformedParameters: public Ui_TaskTransformedParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKTRANSFORMEDPARAMETERS_H
