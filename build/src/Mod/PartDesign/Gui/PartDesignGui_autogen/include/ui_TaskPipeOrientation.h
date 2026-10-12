/********************************************************************************
** Form generated from reading UI file 'TaskPipeOrientation.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPIPEORIENTATION_H
#define UI_TASKPIPEORIENTATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace PartDesignGui {

class Ui_TaskPipeOrientation
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBoxMode;
    QStackedWidget *stackedWidget;
    QWidget *standard;
    QWidget *fixed;
    QWidget *frenet;
    QWidget *auxiliary;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *curvilinear;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *buttonProfileBase;
    QLineEdit *profileBaseEdit;
    QToolButton *buttonProfileClear;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *buttonRefAdd;
    QToolButton *buttonRefRemove;
    QListWidget *listWidgetReferences;
    QWidget *binormal;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxX;
    QDoubleSpinBox *doubleSpinBoxY;
    QDoubleSpinBox *doubleSpinBoxZ;

    void setupUi(QWidget *PartDesignGui__TaskPipeOrientation)
    {
        if (PartDesignGui__TaskPipeOrientation->objectName().isEmpty())
            PartDesignGui__TaskPipeOrientation->setObjectName("PartDesignGui__TaskPipeOrientation");
        PartDesignGui__TaskPipeOrientation->resize(305, 420);
        PartDesignGui__TaskPipeOrientation->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout_3 = new QVBoxLayout(PartDesignGui__TaskPipeOrientation);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(PartDesignGui__TaskPipeOrientation);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        comboBoxMode = new QComboBox(PartDesignGui__TaskPipeOrientation);
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->addItem(QString());
        comboBoxMode->setObjectName("comboBoxMode");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxMode->sizePolicy().hasHeightForWidth());
        comboBoxMode->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBoxMode);


        verticalLayout_3->addLayout(horizontalLayout);

        stackedWidget = new QStackedWidget(PartDesignGui__TaskPipeOrientation);
        stackedWidget->setObjectName("stackedWidget");
        standard = new QWidget();
        standard->setObjectName("standard");
        stackedWidget->addWidget(standard);
        fixed = new QWidget();
        fixed->setObjectName("fixed");
        stackedWidget->addWidget(fixed);
        frenet = new QWidget();
        frenet->setObjectName("frenet");
        stackedWidget->addWidget(frenet);
        auxiliary = new QWidget();
        auxiliary->setObjectName("auxiliary");
        verticalLayout_2 = new QVBoxLayout(auxiliary);
        verticalLayout_2->setObjectName("verticalLayout_2");
        curvilinear = new QCheckBox(auxiliary);
        curvilinear->setObjectName("curvilinear");

        verticalLayout_2->addWidget(curvilinear);

        groupBox = new QGroupBox(auxiliary);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonProfileBase = new QToolButton(groupBox);
        buttonProfileBase->setObjectName("buttonProfileBase");
        buttonProfileBase->setCheckable(true);

        horizontalLayout_2->addWidget(buttonProfileBase);

        profileBaseEdit = new QLineEdit(groupBox);
        profileBaseEdit->setObjectName("profileBaseEdit");

        horizontalLayout_2->addWidget(profileBaseEdit);

        buttonProfileClear = new QToolButton(groupBox);
        buttonProfileClear->setObjectName("buttonProfileClear");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/edit-cleartext.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        buttonProfileClear->setIcon(icon);

        horizontalLayout_2->addWidget(buttonProfileClear);


        verticalLayout->addLayout(horizontalLayout_2);

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

        stackedWidget->addWidget(auxiliary);
        binormal = new QWidget();
        binormal->setObjectName("binormal");
        verticalLayout_4 = new QVBoxLayout(binormal);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_5 = new QLabel(binormal);
        label_5->setObjectName("label_5");
        label_5->setWordWrap(true);

        verticalLayout_4->addWidget(label_5);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        formLayout->setHorizontalSpacing(20);
        label = new QLabel(binormal);
        label->setObjectName("label");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label);

        label_3 = new QLabel(binormal);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        label_4 = new QLabel(binormal);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        doubleSpinBoxX = new QDoubleSpinBox(binormal);
        doubleSpinBoxX->setObjectName("doubleSpinBoxX");
        sizePolicy.setHeightForWidth(doubleSpinBoxX->sizePolicy().hasHeightForWidth());
        doubleSpinBoxX->setSizePolicy(sizePolicy);
        doubleSpinBoxX->setMinimum(-99.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, doubleSpinBoxX);

        doubleSpinBoxY = new QDoubleSpinBox(binormal);
        doubleSpinBoxY->setObjectName("doubleSpinBoxY");
        sizePolicy.setHeightForWidth(doubleSpinBoxY->sizePolicy().hasHeightForWidth());
        doubleSpinBoxY->setSizePolicy(sizePolicy);
        doubleSpinBoxY->setMinimum(-99.000000000000000);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, doubleSpinBoxY);

        doubleSpinBoxZ = new QDoubleSpinBox(binormal);
        doubleSpinBoxZ->setObjectName("doubleSpinBoxZ");
        sizePolicy.setHeightForWidth(doubleSpinBoxZ->sizePolicy().hasHeightForWidth());
        doubleSpinBoxZ->setSizePolicy(sizePolicy);
        doubleSpinBoxZ->setMinimum(-99.000000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, doubleSpinBoxZ);


        verticalLayout_4->addLayout(formLayout);

        stackedWidget->addWidget(binormal);

        verticalLayout_3->addWidget(stackedWidget);


        retranslateUi(PartDesignGui__TaskPipeOrientation);
        QObject::connect(comboBoxMode, &QComboBox::currentIndexChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PartDesignGui__TaskPipeOrientation);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskPipeOrientation)
    {
        label_2->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Orientation mode", nullptr));
        comboBoxMode->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Standard", nullptr));
        comboBoxMode->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Fixed", nullptr));
        comboBoxMode->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Frenet", nullptr));
        comboBoxMode->setItemText(3, QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Auxiliary", nullptr));
        comboBoxMode->setItemText(4, QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Binormal", nullptr));

        curvilinear->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Curvilinear equivalence", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Profile", nullptr));
        buttonProfileBase->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Object", nullptr));
        buttonRefAdd->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Add Edge", nullptr));
        buttonRefRemove->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Remove Edge", nullptr));
        label_5->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Set the constant binormal vector used to calculate the profiles orientation", nullptr));
        label->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "X", nullptr));
        label_3->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("PartDesignGui::TaskPipeOrientation", "Z", nullptr));
        (void)PartDesignGui__TaskPipeOrientation;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskPipeOrientation: public Ui_TaskPipeOrientation {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPIPEORIENTATION_H
