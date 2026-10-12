/********************************************************************************
** Form generated from reading UI file 'TaskFaceAppearances.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKFACEAPPEARANCES_H
#define UI_TASKFACEAPPEARANCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Mod/Material/Gui/MaterialTreeWidget.h"

namespace PartGui {

class Ui_TaskFaceAppearances
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *faceLabel;
    QLabel *labelElement;
    QHBoxLayout *horizontalLayout_2;
    MatGui::MaterialTreeWidget *widgetMaterial;
    QGridLayout *gridLayout;
    QPushButton *buttonCustomAppearance;
    QLabel *labelCustomAppearance;
    QGridLayout *gridLayout_2;
    QPushButton *defaultButton;
    QPushButton *boxSelection;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PartGui__TaskFaceAppearances)
    {
        if (PartGui__TaskFaceAppearances->objectName().isEmpty())
            PartGui__TaskFaceAppearances->setObjectName("PartGui__TaskFaceAppearances");
        PartGui__TaskFaceAppearances->resize(247, 219);
        verticalLayout = new QVBoxLayout(PartGui__TaskFaceAppearances);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(PartGui__TaskFaceAppearances);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        groupBox = new QGroupBox(PartGui__TaskFaceAppearances);
        groupBox->setObjectName("groupBox");
        groupBox->setTitle(QString::fromUtf8("Group box"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        faceLabel = new QLabel(groupBox);
        faceLabel->setObjectName("faceLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(faceLabel->sizePolicy().hasHeightForWidth());
        faceLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(faceLabel);

        labelElement = new QLabel(groupBox);
        labelElement->setObjectName("labelElement");
        labelElement->setText(QString::fromUtf8("[]"));

        horizontalLayout->addWidget(labelElement);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        widgetMaterial = new MatGui::MaterialTreeWidget(groupBox);
        widgetMaterial->setObjectName("widgetMaterial");

        horizontalLayout_2->addWidget(widgetMaterial);


        verticalLayout_2->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        buttonCustomAppearance = new QPushButton(groupBox);
        buttonCustomAppearance->setObjectName("buttonCustomAppearance");

        gridLayout->addWidget(buttonCustomAppearance, 0, 1, 1, 1);

        labelCustomAppearance = new QLabel(groupBox);
        labelCustomAppearance->setObjectName("labelCustomAppearance");

        gridLayout->addWidget(labelCustomAppearance, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addWidget(groupBox);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        defaultButton = new QPushButton(PartGui__TaskFaceAppearances);
        defaultButton->setObjectName("defaultButton");

        gridLayout_2->addWidget(defaultButton, 0, 0, 1, 1);

        boxSelection = new QPushButton(PartGui__TaskFaceAppearances);
        boxSelection->setObjectName("boxSelection");
        boxSelection->setCheckable(true);
        boxSelection->setChecked(false);
        boxSelection->setAutoDefault(false);
        boxSelection->setFlat(false);

        gridLayout_2->addWidget(boxSelection, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);


        retranslateUi(PartGui__TaskFaceAppearances);

        boxSelection->setDefault(false);


        QMetaObject::connectSlotsByName(PartGui__TaskFaceAppearances);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskFaceAppearances)
    {
        PartGui__TaskFaceAppearances->setWindowTitle(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Appearance per Face", nullptr));
        label->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Select the faces in the 3D view", nullptr));
        faceLabel->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Faces", nullptr));
        buttonCustomAppearance->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Appearance", nullptr));
        labelCustomAppearance->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Custom appearance", nullptr));
#if QT_CONFIG(tooltip)
        defaultButton->setToolTip(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Resets color for all faces of the part", nullptr));
#endif // QT_CONFIG(tooltip)
        defaultButton->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Set to Default", nullptr));
#if QT_CONFIG(tooltip)
        boxSelection->setToolTip(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Allows the selection of multiple faces by dragging a rectangle in the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        boxSelection->setText(QCoreApplication::translate("PartGui::TaskFaceAppearances", "Box Selection", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskFaceAppearances: public Ui_TaskFaceAppearances {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKFACEAPPEARANCES_H
