/********************************************************************************
** Form generated from reading UI file 'TaskLoftParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKLOFTPARAMETERS_H
#define UI_TASKLOFTPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskLoftParameters
{
public:
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxRuled;
    QCheckBox *checkBoxClosed;
    QGroupBox *groupprofile;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QToolButton *buttonProfileBase;
    QLineEdit *profileBaseEdit;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *buttonRefAdd;
    QToolButton *buttonRefRemove;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidgetReferences;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;
    QFrame *line;
    QCheckBox *checkBoxUpdateView;

    void setupUi(QWidget *PartDesignGui__TaskLoftParameters)
    {
        if (PartDesignGui__TaskLoftParameters->objectName().isEmpty())
            PartDesignGui__TaskLoftParameters->setObjectName("PartDesignGui__TaskLoftParameters");
        PartDesignGui__TaskLoftParameters->resize(262, 293);
        PartDesignGui__TaskLoftParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_3 = new QVBoxLayout(PartDesignGui__TaskLoftParameters);
        verticalLayout_3->setObjectName("verticalLayout_3");
        checkBoxRuled = new QCheckBox(PartDesignGui__TaskLoftParameters);
        checkBoxRuled->setObjectName("checkBoxRuled");

        verticalLayout_3->addWidget(checkBoxRuled);

        checkBoxClosed = new QCheckBox(PartDesignGui__TaskLoftParameters);
        checkBoxClosed->setObjectName("checkBoxClosed");

        verticalLayout_3->addWidget(checkBoxClosed);

        groupprofile = new QGroupBox(PartDesignGui__TaskLoftParameters);
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


        verticalLayout_3->addWidget(groupprofile);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        buttonRefAdd = new QToolButton(PartDesignGui__TaskLoftParameters);
        buttonRefAdd->setObjectName("buttonRefAdd");
        buttonRefAdd->setEnabled(true);
        buttonRefAdd->setCheckable(true);
        buttonRefAdd->setChecked(false);

        horizontalLayout_4->addWidget(buttonRefAdd);

        buttonRefRemove = new QToolButton(PartDesignGui__TaskLoftParameters);
        buttonRefRemove->setObjectName("buttonRefRemove");
        buttonRefRemove->setCheckable(true);

        horizontalLayout_4->addWidget(buttonRefRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_4);

        listWidgetReferences = new QListWidget(PartDesignGui__TaskLoftParameters);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setDragDropMode(QAbstractItemView::InternalMove);

        verticalLayout_3->addWidget(listWidgetReferences);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__TaskLoftParameters);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__TaskLoftParameters);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);

        operationLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(operationLayout);

        line = new QFrame(PartDesignGui__TaskLoftParameters);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line);

        checkBoxUpdateView = new QCheckBox(PartDesignGui__TaskLoftParameters);
        checkBoxUpdateView->setObjectName("checkBoxUpdateView");
        checkBoxUpdateView->setChecked(true);

        verticalLayout_3->addWidget(checkBoxUpdateView);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(checkBoxRuled, checkBoxClosed);
        QWidget::setTabOrder(checkBoxClosed, buttonProfileBase);
        QWidget::setTabOrder(buttonProfileBase, profileBaseEdit);
        QWidget::setTabOrder(profileBaseEdit, buttonRefAdd);
        QWidget::setTabOrder(buttonRefAdd, buttonRefRemove);
        QWidget::setTabOrder(buttonRefRemove, listWidgetReferences);
        QWidget::setTabOrder(listWidgetReferences, comboOperation);
        QWidget::setTabOrder(comboOperation, checkBoxUpdateView);

        retranslateUi(PartDesignGui__TaskLoftParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskLoftParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskLoftParameters)
    {
        checkBoxRuled->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Ruled surface", nullptr));
        checkBoxClosed->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Closed", nullptr));
        groupprofile->setTitle(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Profile", nullptr));
        buttonProfileBase->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Object", nullptr));
        buttonRefAdd->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Add Section", nullptr));
        buttonRefRemove->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Remove Section", nullptr));
#if QT_CONFIG(tooltip)
        listWidgetReferences->setToolTip(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "List can be reordered by dragging", nullptr));
#endif // QT_CONFIG(tooltip)
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Common", nullptr));

        checkBoxUpdateView->setText(QCoreApplication::translate("PartDesignGui::TaskLoftParameters", "Recompute on change", nullptr));
        (void)PartDesignGui__TaskLoftParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskLoftParameters: public Ui_TaskLoftParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKLOFTPARAMETERS_H
