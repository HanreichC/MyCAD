/********************************************************************************
** Form generated from reading UI file 'TaskMassProperties.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKMASSPROPERTIES_H
#define UI_TASKMASSPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskMassProperties
{
public:
    QVBoxLayout *mainLayout;
    QWidget *parametersPage;
    QVBoxLayout *parametersLayout;
    QLabel *objectsLabel;
    QListWidget *objectList;
    QLabel *referenceLabel;
    QWidget *referenceWidget;
    QVBoxLayout *referenceLayout;
    QRadioButton *centerOfGravityRadioButton;
    QHBoxLayout *customControlsLayout;
    QRadioButton *customRadioButton;
    QLineEdit *customEdit;
    QPushButton *selectCustomButton;
    QComboBox *unitsComboBox;
    QWidget *physicalPropertiesPage;
    QFormLayout *physicalPropertiesLayout;
    QLabel *volumeLabel;
    QLineEdit *volumeEdit;
    QLabel *massLabel;
    QLineEdit *massEdit;
    QLabel *densityLabel;
    QLineEdit *densityEdit;
    QLabel *surfaceAreaLabel;
    QLineEdit *surfaceAreaEdit;
    QWidget *centerOfGravityPage;
    QVBoxLayout *centerOfGravityLayout;
    QHBoxLayout *cogFieldsLayout;
    QLabel *cogXLabel;
    QLineEdit *cogXText;
    QSpacerItem *cogSpacer1;
    QLabel *cogYLabel;
    QLineEdit *cogYText;
    QSpacerItem *cogSpacer2;
    QLabel *cogZLabel;
    QLineEdit *cogZText;
    QHBoxLayout *cogButtonLayout;
    QSpacerItem *cogButtonSpacer1;
    QPushButton *cogDatumButton;
    QSpacerItem *cogButtonSpacer2;
    QWidget *centerOfVolumePage;
    QVBoxLayout *centerOfVolumeLayout;
    QHBoxLayout *covFieldsLayout;
    QLabel *covXLabel;
    QLineEdit *covXText;
    QSpacerItem *covSpacer1;
    QLabel *covYLabel;
    QLineEdit *covYText;
    QSpacerItem *covSpacer2;
    QLabel *covZLabel;
    QLineEdit *covZText;
    QHBoxLayout *covButtonLayout;
    QSpacerItem *covButtonSpacer1;
    QPushButton *covDatumButton;
    QSpacerItem *covButtonSpacer2;
    QWidget *inertiaPage;
    QVBoxLayout *inertiaLayout;
    QLabel *inertiaMatrixLabel;
    QWidget *inertiaMatrixWidget;
    QGridLayout *inertiaMatrixLayout;
    QLabel *inertiaJoxLabel;
    QLineEdit *inertiaJoxText;
    QLabel *inertiaJxyLabel;
    QLineEdit *inertiaJxyText;
    QLabel *inertiaJzxLabel;
    QLineEdit *inertiaJzxText;
    QLabel *inertiaJoyLabel;
    QLineEdit *inertiaJoyText;
    QLabel *inertiaJzyLabel;
    QLineEdit *inertiaJzyText;
    QLabel *inertiaJozLabel;
    QLineEdit *inertiaJozText;
    QFrame *inertiaSeparator;
    QLabel *inertiaPrincipalLabel;
    QWidget *inertiaDiagWidget;
    QHBoxLayout *inertiaDiagLayout;
    QLabel *inertiaJxLabel;
    QLineEdit *inertiaJxText;
    QSpacerItem *inertiaDiagSpacer1;
    QLabel *inertiaJyLabel;
    QLineEdit *inertiaJyText;
    QSpacerItem *inertiaDiagSpacer2;
    QLabel *inertiaJzLabel;
    QLineEdit *inertiaJzText;
    QWidget *inertiaLcsWidget;
    QHBoxLayout *inertiaLcsLayout;
    QSpacerItem *inertiaLcsSpacer1;
    QPushButton *inertiaLcsButton;
    QSpacerItem *inertiaLcsSpacer2;
    QWidget *axisInertiaWidget;
    QHBoxLayout *axisInertiaLayout;
    QLabel *axisLabel;
    QLineEdit *axisInertiaText;

    void setupUi(QWidget *TaskMassProperties)
    {
        if (TaskMassProperties->objectName().isEmpty())
            TaskMassProperties->setObjectName("TaskMassProperties");
        TaskMassProperties->resize(480, 720);
        mainLayout = new QVBoxLayout(TaskMassProperties);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        parametersPage = new QWidget(TaskMassProperties);
        parametersPage->setObjectName("parametersPage");
        parametersLayout = new QVBoxLayout(parametersPage);
        parametersLayout->setSpacing(8);
        parametersLayout->setObjectName("parametersLayout");
        parametersLayout->setContentsMargins(0, 0, 0, 0);
        objectsLabel = new QLabel(parametersPage);
        objectsLabel->setObjectName("objectsLabel");
        objectsLabel->setWordWrap(true);

        parametersLayout->addWidget(objectsLabel);

        objectList = new QListWidget(parametersPage);
        objectList->setObjectName("objectList");
        objectList->setMaximumHeight(75);
        objectList->setSelectionMode(QAbstractItemView::ExtendedSelection);

        parametersLayout->addWidget(objectList);

        referenceLabel = new QLabel(parametersPage);
        referenceLabel->setObjectName("referenceLabel");

        parametersLayout->addWidget(referenceLabel);

        referenceWidget = new QWidget(parametersPage);
        referenceWidget->setObjectName("referenceWidget");
        referenceLayout = new QVBoxLayout(referenceWidget);
        referenceLayout->setSpacing(6);
        referenceLayout->setObjectName("referenceLayout");
        referenceLayout->setContentsMargins(0, 0, 0, 0);
        centerOfGravityRadioButton = new QRadioButton(referenceWidget);
        centerOfGravityRadioButton->setObjectName("centerOfGravityRadioButton");
        centerOfGravityRadioButton->setChecked(true);

        referenceLayout->addWidget(centerOfGravityRadioButton);

        customControlsLayout = new QHBoxLayout();
        customControlsLayout->setSpacing(6);
        customControlsLayout->setObjectName("customControlsLayout");
        customControlsLayout->setContentsMargins(0, 0, 0, 0);
        customRadioButton = new QRadioButton(referenceWidget);
        customRadioButton->setObjectName("customRadioButton");

        customControlsLayout->addWidget(customRadioButton);

        customEdit = new QLineEdit(referenceWidget);
        customEdit->setObjectName("customEdit");
        customEdit->setReadOnly(true);

        customControlsLayout->addWidget(customEdit);

        selectCustomButton = new QPushButton(referenceWidget);
        selectCustomButton->setObjectName("selectCustomButton");

        customControlsLayout->addWidget(selectCustomButton);


        referenceLayout->addLayout(customControlsLayout);


        parametersLayout->addWidget(referenceWidget);

        unitsComboBox = new QComboBox(parametersPage);
        unitsComboBox->addItem(QString());
        unitsComboBox->addItem(QString());
        unitsComboBox->addItem(QString());
        unitsComboBox->addItem(QString());
        unitsComboBox->setObjectName("unitsComboBox");

        parametersLayout->addWidget(unitsComboBox);


        mainLayout->addWidget(parametersPage);

        physicalPropertiesPage = new QWidget(TaskMassProperties);
        physicalPropertiesPage->setObjectName("physicalPropertiesPage");
        physicalPropertiesLayout = new QFormLayout(physicalPropertiesPage);
        physicalPropertiesLayout->setObjectName("physicalPropertiesLayout");
        physicalPropertiesLayout->setHorizontalSpacing(6);
        physicalPropertiesLayout->setVerticalSpacing(6);
        physicalPropertiesLayout->setContentsMargins(0, 0, 0, 0);
        volumeLabel = new QLabel(physicalPropertiesPage);
        volumeLabel->setObjectName("volumeLabel");

        physicalPropertiesLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, volumeLabel);

        volumeEdit = new QLineEdit(physicalPropertiesPage);
        volumeEdit->setObjectName("volumeEdit");
        volumeEdit->setReadOnly(true);

        physicalPropertiesLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, volumeEdit);

        massLabel = new QLabel(physicalPropertiesPage);
        massLabel->setObjectName("massLabel");

        physicalPropertiesLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, massLabel);

        massEdit = new QLineEdit(physicalPropertiesPage);
        massEdit->setObjectName("massEdit");
        massEdit->setReadOnly(true);

        physicalPropertiesLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, massEdit);

        densityLabel = new QLabel(physicalPropertiesPage);
        densityLabel->setObjectName("densityLabel");

        physicalPropertiesLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, densityLabel);

        densityEdit = new QLineEdit(physicalPropertiesPage);
        densityEdit->setObjectName("densityEdit");
        densityEdit->setReadOnly(true);

        physicalPropertiesLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, densityEdit);

        surfaceAreaLabel = new QLabel(physicalPropertiesPage);
        surfaceAreaLabel->setObjectName("surfaceAreaLabel");

        physicalPropertiesLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, surfaceAreaLabel);

        surfaceAreaEdit = new QLineEdit(physicalPropertiesPage);
        surfaceAreaEdit->setObjectName("surfaceAreaEdit");
        surfaceAreaEdit->setReadOnly(true);

        physicalPropertiesLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, surfaceAreaEdit);


        mainLayout->addWidget(physicalPropertiesPage);

        centerOfGravityPage = new QWidget(TaskMassProperties);
        centerOfGravityPage->setObjectName("centerOfGravityPage");
        centerOfGravityLayout = new QVBoxLayout(centerOfGravityPage);
        centerOfGravityLayout->setSpacing(8);
        centerOfGravityLayout->setObjectName("centerOfGravityLayout");
        centerOfGravityLayout->setContentsMargins(0, 0, 0, 0);
        cogFieldsLayout = new QHBoxLayout();
        cogFieldsLayout->setSpacing(6);
        cogFieldsLayout->setObjectName("cogFieldsLayout");
        cogFieldsLayout->setContentsMargins(0, 0, 0, 0);
        cogXLabel = new QLabel(centerOfGravityPage);
        cogXLabel->setObjectName("cogXLabel");

        cogFieldsLayout->addWidget(cogXLabel);

        cogXText = new QLineEdit(centerOfGravityPage);
        cogXText->setObjectName("cogXText");
        cogXText->setReadOnly(true);

        cogFieldsLayout->addWidget(cogXText);

        cogSpacer1 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        cogFieldsLayout->addItem(cogSpacer1);

        cogYLabel = new QLabel(centerOfGravityPage);
        cogYLabel->setObjectName("cogYLabel");

        cogFieldsLayout->addWidget(cogYLabel);

        cogYText = new QLineEdit(centerOfGravityPage);
        cogYText->setObjectName("cogYText");
        cogYText->setReadOnly(true);

        cogFieldsLayout->addWidget(cogYText);

        cogSpacer2 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        cogFieldsLayout->addItem(cogSpacer2);

        cogZLabel = new QLabel(centerOfGravityPage);
        cogZLabel->setObjectName("cogZLabel");

        cogFieldsLayout->addWidget(cogZLabel);

        cogZText = new QLineEdit(centerOfGravityPage);
        cogZText->setObjectName("cogZText");
        cogZText->setReadOnly(true);

        cogFieldsLayout->addWidget(cogZText);


        centerOfGravityLayout->addLayout(cogFieldsLayout);

        cogButtonLayout = new QHBoxLayout();
        cogButtonLayout->setObjectName("cogButtonLayout");
        cogButtonSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        cogButtonLayout->addItem(cogButtonSpacer1);

        cogDatumButton = new QPushButton(centerOfGravityPage);
        cogDatumButton->setObjectName("cogDatumButton");

        cogButtonLayout->addWidget(cogDatumButton);

        cogButtonSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        cogButtonLayout->addItem(cogButtonSpacer2);


        centerOfGravityLayout->addLayout(cogButtonLayout);


        mainLayout->addWidget(centerOfGravityPage);

        centerOfVolumePage = new QWidget(TaskMassProperties);
        centerOfVolumePage->setObjectName("centerOfVolumePage");
        centerOfVolumeLayout = new QVBoxLayout(centerOfVolumePage);
        centerOfVolumeLayout->setSpacing(8);
        centerOfVolumeLayout->setObjectName("centerOfVolumeLayout");
        centerOfVolumeLayout->setContentsMargins(0, 0, 0, 0);
        covFieldsLayout = new QHBoxLayout();
        covFieldsLayout->setSpacing(6);
        covFieldsLayout->setObjectName("covFieldsLayout");
        covFieldsLayout->setContentsMargins(0, 0, 0, 0);
        covXLabel = new QLabel(centerOfVolumePage);
        covXLabel->setObjectName("covXLabel");

        covFieldsLayout->addWidget(covXLabel);

        covXText = new QLineEdit(centerOfVolumePage);
        covXText->setObjectName("covXText");
        covXText->setReadOnly(true);

        covFieldsLayout->addWidget(covXText);

        covSpacer1 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        covFieldsLayout->addItem(covSpacer1);

        covYLabel = new QLabel(centerOfVolumePage);
        covYLabel->setObjectName("covYLabel");

        covFieldsLayout->addWidget(covYLabel);

        covYText = new QLineEdit(centerOfVolumePage);
        covYText->setObjectName("covYText");
        covYText->setReadOnly(true);

        covFieldsLayout->addWidget(covYText);

        covSpacer2 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        covFieldsLayout->addItem(covSpacer2);

        covZLabel = new QLabel(centerOfVolumePage);
        covZLabel->setObjectName("covZLabel");

        covFieldsLayout->addWidget(covZLabel);

        covZText = new QLineEdit(centerOfVolumePage);
        covZText->setObjectName("covZText");
        covZText->setReadOnly(true);

        covFieldsLayout->addWidget(covZText);


        centerOfVolumeLayout->addLayout(covFieldsLayout);

        covButtonLayout = new QHBoxLayout();
        covButtonLayout->setObjectName("covButtonLayout");
        covButtonSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        covButtonLayout->addItem(covButtonSpacer1);

        covDatumButton = new QPushButton(centerOfVolumePage);
        covDatumButton->setObjectName("covDatumButton");

        covButtonLayout->addWidget(covDatumButton);

        covButtonSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        covButtonLayout->addItem(covButtonSpacer2);


        centerOfVolumeLayout->addLayout(covButtonLayout);


        mainLayout->addWidget(centerOfVolumePage);

        inertiaPage = new QWidget(TaskMassProperties);
        inertiaPage->setObjectName("inertiaPage");
        inertiaLayout = new QVBoxLayout(inertiaPage);
        inertiaLayout->setSpacing(8);
        inertiaLayout->setObjectName("inertiaLayout");
        inertiaLayout->setContentsMargins(0, 0, 0, 0);
        inertiaMatrixLabel = new QLabel(inertiaPage);
        inertiaMatrixLabel->setObjectName("inertiaMatrixLabel");

        inertiaLayout->addWidget(inertiaMatrixLabel);

        inertiaMatrixWidget = new QWidget(inertiaPage);
        inertiaMatrixWidget->setObjectName("inertiaMatrixWidget");
        inertiaMatrixLayout = new QGridLayout(inertiaMatrixWidget);
        inertiaMatrixLayout->setObjectName("inertiaMatrixLayout");
        inertiaMatrixLayout->setHorizontalSpacing(6);
        inertiaMatrixLayout->setVerticalSpacing(6);
        inertiaMatrixLayout->setContentsMargins(0, 0, 0, 0);
        inertiaJoxLabel = new QLabel(inertiaMatrixWidget);
        inertiaJoxLabel->setObjectName("inertiaJoxLabel");

        inertiaMatrixLayout->addWidget(inertiaJoxLabel, 0, 0, 1, 1);

        inertiaJoxText = new QLineEdit(inertiaMatrixWidget);
        inertiaJoxText->setObjectName("inertiaJoxText");
        inertiaJoxText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJoxText, 0, 1, 1, 1);

        inertiaJxyLabel = new QLabel(inertiaMatrixWidget);
        inertiaJxyLabel->setObjectName("inertiaJxyLabel");

        inertiaMatrixLayout->addWidget(inertiaJxyLabel, 0, 2, 1, 1);

        inertiaJxyText = new QLineEdit(inertiaMatrixWidget);
        inertiaJxyText->setObjectName("inertiaJxyText");
        inertiaJxyText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJxyText, 0, 3, 1, 1);

        inertiaJzxLabel = new QLabel(inertiaMatrixWidget);
        inertiaJzxLabel->setObjectName("inertiaJzxLabel");

        inertiaMatrixLayout->addWidget(inertiaJzxLabel, 0, 4, 1, 1);

        inertiaJzxText = new QLineEdit(inertiaMatrixWidget);
        inertiaJzxText->setObjectName("inertiaJzxText");
        inertiaJzxText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJzxText, 0, 5, 1, 1);

        inertiaJoyLabel = new QLabel(inertiaMatrixWidget);
        inertiaJoyLabel->setObjectName("inertiaJoyLabel");

        inertiaMatrixLayout->addWidget(inertiaJoyLabel, 1, 2, 1, 1);

        inertiaJoyText = new QLineEdit(inertiaMatrixWidget);
        inertiaJoyText->setObjectName("inertiaJoyText");
        inertiaJoyText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJoyText, 1, 3, 1, 1);

        inertiaJzyLabel = new QLabel(inertiaMatrixWidget);
        inertiaJzyLabel->setObjectName("inertiaJzyLabel");

        inertiaMatrixLayout->addWidget(inertiaJzyLabel, 1, 4, 1, 1);

        inertiaJzyText = new QLineEdit(inertiaMatrixWidget);
        inertiaJzyText->setObjectName("inertiaJzyText");
        inertiaJzyText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJzyText, 1, 5, 1, 1);

        inertiaJozLabel = new QLabel(inertiaMatrixWidget);
        inertiaJozLabel->setObjectName("inertiaJozLabel");

        inertiaMatrixLayout->addWidget(inertiaJozLabel, 2, 4, 1, 1);

        inertiaJozText = new QLineEdit(inertiaMatrixWidget);
        inertiaJozText->setObjectName("inertiaJozText");
        inertiaJozText->setReadOnly(true);

        inertiaMatrixLayout->addWidget(inertiaJozText, 2, 5, 1, 1);


        inertiaLayout->addWidget(inertiaMatrixWidget);

        inertiaSeparator = new QFrame(inertiaPage);
        inertiaSeparator->setObjectName("inertiaSeparator");
        inertiaSeparator->setFrameShape(QFrame::Shape::HLine);
        inertiaSeparator->setFrameShadow(QFrame::Shadow::Sunken);

        inertiaLayout->addWidget(inertiaSeparator);

        inertiaPrincipalLabel = new QLabel(inertiaPage);
        inertiaPrincipalLabel->setObjectName("inertiaPrincipalLabel");

        inertiaLayout->addWidget(inertiaPrincipalLabel);

        inertiaDiagWidget = new QWidget(inertiaPage);
        inertiaDiagWidget->setObjectName("inertiaDiagWidget");
        inertiaDiagLayout = new QHBoxLayout(inertiaDiagWidget);
        inertiaDiagLayout->setSpacing(6);
        inertiaDiagLayout->setObjectName("inertiaDiagLayout");
        inertiaDiagLayout->setContentsMargins(0, 0, 0, 0);
        inertiaJxLabel = new QLabel(inertiaDiagWidget);
        inertiaJxLabel->setObjectName("inertiaJxLabel");

        inertiaDiagLayout->addWidget(inertiaJxLabel);

        inertiaJxText = new QLineEdit(inertiaDiagWidget);
        inertiaJxText->setObjectName("inertiaJxText");
        inertiaJxText->setReadOnly(true);

        inertiaDiagLayout->addWidget(inertiaJxText);

        inertiaDiagSpacer1 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inertiaDiagLayout->addItem(inertiaDiagSpacer1);

        inertiaJyLabel = new QLabel(inertiaDiagWidget);
        inertiaJyLabel->setObjectName("inertiaJyLabel");

        inertiaDiagLayout->addWidget(inertiaJyLabel);

        inertiaJyText = new QLineEdit(inertiaDiagWidget);
        inertiaJyText->setObjectName("inertiaJyText");
        inertiaJyText->setReadOnly(true);

        inertiaDiagLayout->addWidget(inertiaJyText);

        inertiaDiagSpacer2 = new QSpacerItem(8, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inertiaDiagLayout->addItem(inertiaDiagSpacer2);

        inertiaJzLabel = new QLabel(inertiaDiagWidget);
        inertiaJzLabel->setObjectName("inertiaJzLabel");

        inertiaDiagLayout->addWidget(inertiaJzLabel);

        inertiaJzText = new QLineEdit(inertiaDiagWidget);
        inertiaJzText->setObjectName("inertiaJzText");
        inertiaJzText->setReadOnly(true);

        inertiaDiagLayout->addWidget(inertiaJzText);


        inertiaLayout->addWidget(inertiaDiagWidget);

        inertiaLcsWidget = new QWidget(inertiaPage);
        inertiaLcsWidget->setObjectName("inertiaLcsWidget");
        inertiaLcsLayout = new QHBoxLayout(inertiaLcsWidget);
        inertiaLcsLayout->setObjectName("inertiaLcsLayout");
        inertiaLcsLayout->setContentsMargins(0, 0, 0, 0);
        inertiaLcsSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inertiaLcsLayout->addItem(inertiaLcsSpacer1);

        inertiaLcsButton = new QPushButton(inertiaLcsWidget);
        inertiaLcsButton->setObjectName("inertiaLcsButton");

        inertiaLcsLayout->addWidget(inertiaLcsButton);

        inertiaLcsSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        inertiaLcsLayout->addItem(inertiaLcsSpacer2);


        inertiaLayout->addWidget(inertiaLcsWidget);

        axisInertiaWidget = new QWidget(inertiaPage);
        axisInertiaWidget->setObjectName("axisInertiaWidget");
        axisInertiaLayout = new QHBoxLayout(axisInertiaWidget);
        axisInertiaLayout->setSpacing(6);
        axisInertiaLayout->setObjectName("axisInertiaLayout");
        axisInertiaLayout->setContentsMargins(0, 0, 0, 0);
        axisLabel = new QLabel(axisInertiaWidget);
        axisLabel->setObjectName("axisLabel");
        axisLabel->setWordWrap(true);

        axisInertiaLayout->addWidget(axisLabel);

        axisInertiaText = new QLineEdit(axisInertiaWidget);
        axisInertiaText->setObjectName("axisInertiaText");
        axisInertiaText->setReadOnly(true);

        axisInertiaLayout->addWidget(axisInertiaText);


        inertiaLayout->addWidget(axisInertiaWidget);


        mainLayout->addWidget(inertiaPage);


        retranslateUi(TaskMassProperties);

        QMetaObject::connectSlotsByName(TaskMassProperties);
    } // setupUi

    void retranslateUi(QWidget *TaskMassProperties)
    {
        objectsLabel->setText(QCoreApplication::translate("TaskMassProperties", "Objects to measure", nullptr));
        referenceLabel->setText(QCoreApplication::translate("TaskMassProperties", "Reference", nullptr));
        centerOfGravityRadioButton->setText(QCoreApplication::translate("TaskMassProperties", "Center of gravity", nullptr));
        customRadioButton->setText(QCoreApplication::translate("TaskMassProperties", "Custom", nullptr));
        selectCustomButton->setText(QCoreApplication::translate("TaskMassProperties", "Select\342\200\246", nullptr));
        unitsComboBox->setItemText(0, QCoreApplication::translate("TaskMassProperties", "mm, kg, kg*mm^2", nullptr));
        unitsComboBox->setItemText(1, QCoreApplication::translate("TaskMassProperties", "m, kg, kg*m^2", nullptr));
        unitsComboBox->setItemText(2, QCoreApplication::translate("TaskMassProperties", "in, lb, lb*in^2", nullptr));
        unitsComboBox->setItemText(3, QCoreApplication::translate("TaskMassProperties", "ft, lb, lb*ft^2", nullptr));

        volumeLabel->setText(QCoreApplication::translate("TaskMassProperties", "Volume", nullptr));
        massLabel->setText(QCoreApplication::translate("TaskMassProperties", "Mass", nullptr));
        densityLabel->setText(QCoreApplication::translate("TaskMassProperties", "Density", nullptr));
        surfaceAreaLabel->setText(QCoreApplication::translate("TaskMassProperties", "Surface area", nullptr));
        cogXLabel->setText(QCoreApplication::translate("TaskMassProperties", "X", nullptr));
        cogYLabel->setText(QCoreApplication::translate("TaskMassProperties", "Y", nullptr));
        cogZLabel->setText(QCoreApplication::translate("TaskMassProperties", "Z", nullptr));
        cogDatumButton->setText(QCoreApplication::translate("TaskMassProperties", "Create Datum Point", nullptr));
        covXLabel->setText(QCoreApplication::translate("TaskMassProperties", "X", nullptr));
        covYLabel->setText(QCoreApplication::translate("TaskMassProperties", "Y", nullptr));
        covZLabel->setText(QCoreApplication::translate("TaskMassProperties", "Z", nullptr));
        covDatumButton->setText(QCoreApplication::translate("TaskMassProperties", "Create Datum Point", nullptr));
        inertiaMatrixLabel->setText(QCoreApplication::translate("TaskMassProperties", "Inertia Matrix", nullptr));
        inertiaJoxLabel->setText(QCoreApplication::translate("TaskMassProperties", "Jox", nullptr));
        inertiaJxyLabel->setText(QCoreApplication::translate("TaskMassProperties", "Jxy", nullptr));
        inertiaJzxLabel->setText(QCoreApplication::translate("TaskMassProperties", "Jzx", nullptr));
        inertiaJoyLabel->setText(QCoreApplication::translate("TaskMassProperties", "Joy", nullptr));
        inertiaJzyLabel->setText(QCoreApplication::translate("TaskMassProperties", "Jzy", nullptr));
        inertiaJozLabel->setText(QCoreApplication::translate("TaskMassProperties", "Joz", nullptr));
        inertiaPrincipalLabel->setText(QCoreApplication::translate("TaskMassProperties", "Principal Moments of Inertia", nullptr));
        inertiaJxLabel->setText(QCoreApplication::translate("TaskMassProperties", "J1", nullptr));
        inertiaJyLabel->setText(QCoreApplication::translate("TaskMassProperties", "J2", nullptr));
        inertiaJzLabel->setText(QCoreApplication::translate("TaskMassProperties", "J3", nullptr));
        inertiaLcsButton->setText(QCoreApplication::translate("TaskMassProperties", "Create Principal Axes LCS", nullptr));
        axisLabel->setText(QCoreApplication::translate("TaskMassProperties", "Inertia around axis", nullptr));
        (void)TaskMassProperties;
    } // retranslateUi

};

namespace Ui {
    class TaskMassProperties: public Ui_TaskMassProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKMASSPROPERTIES_H
