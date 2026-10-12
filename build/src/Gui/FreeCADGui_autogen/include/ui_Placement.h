/********************************************************************************
** Form generated from reading UI file 'Placement.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACEMENT_H
#define UI_PLACEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace Gui {
namespace Dialog {

class Ui_Placement
{
public:
    QGridLayout *gridLayout;
    QGroupBox *GroupBox5;
    QGridLayout *gridLayout1;
    QLabel *TextLabelX;
    Gui::QuantitySpinBox *xPos;
    QLabel *TextLabelY;
    Gui::QuantitySpinBox *yPos;
    QLabel *TextLabelZ;
    Gui::QuantitySpinBox *zPos;
    QLabel *TextLabelAxial;
    Gui::QuantitySpinBox *axialPos;
    QPushButton *applyAxial;
    QGroupBox *GroupBox5_3;
    QGridLayout *gridLayout2;
    QLabel *TextLabelX_2;
    Gui::QuantitySpinBox *xCnt;
    QLabel *TextLabelY_2;
    Gui::QuantitySpinBox *yCnt;
    QLabel *TextLabelZ_5;
    Gui::QuantitySpinBox *zCnt;
    QCheckBox *centerOfMass;
    QPushButton *selectedVertex;
    QGroupBox *GroupBox5_2;
    QGridLayout *gridLayout3;
    QComboBox *rotationInput;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout4;
    QGridLayout *gridLayout5;
    QLabel *TextLabelAxis;
    Gui::QuantitySpinBox *xAxis;
    Gui::QuantitySpinBox *yAxis;
    Gui::QuantitySpinBox *zAxis;
    QLabel *textLabelAngle;
    Gui::QuantitySpinBox *angle;
    QWidget *page_3;
    QGridLayout *gridLayout6;
    QGridLayout *gridLayout7;
    QLabel *TextLabelZ_2;
    Gui::QuantitySpinBox *yawAngle;
    QLabel *TextLabelZ_3;
    Gui::QuantitySpinBox *pitchAngle;
    QLabel *TextLabelZ_4;
    Gui::QuantitySpinBox *rollAngle;
    QWidget *page_2;
    QSpacerItem *vSpacer;
    QHBoxLayout *horizontalLayout;
    QCheckBox *applyIncrementalPlacement;
    QSpacerItem *hSpacer;
    QPushButton *resetButton;
    QHBoxLayout *buttonBoxLayout;
    QSpacerItem *buttonBoxSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__Placement)
    {
        if (Gui__Dialog__Placement->objectName().isEmpty())
            Gui__Dialog__Placement->setObjectName("Gui__Dialog__Placement");
        Gui__Dialog__Placement->resize(456, 492);
        gridLayout = new QGridLayout(Gui__Dialog__Placement);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        GroupBox5 = new QGroupBox(Gui__Dialog__Placement);
        GroupBox5->setObjectName("GroupBox5");
        gridLayout1 = new QGridLayout(GroupBox5);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        TextLabelX = new QLabel(GroupBox5);
        TextLabelX->setObjectName("TextLabelX");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextLabelX->sizePolicy().hasHeightForWidth());
        TextLabelX->setSizePolicy(sizePolicy);
        TextLabelX->setText(QString::fromUtf8("X"));

        gridLayout1->addWidget(TextLabelX, 0, 0, 1, 1);

        xPos = new Gui::QuantitySpinBox(GroupBox5);
        xPos->setObjectName("xPos");

        gridLayout1->addWidget(xPos, 0, 1, 1, 1);

        TextLabelY = new QLabel(GroupBox5);
        TextLabelY->setObjectName("TextLabelY");
        sizePolicy.setHeightForWidth(TextLabelY->sizePolicy().hasHeightForWidth());
        TextLabelY->setSizePolicy(sizePolicy);
        TextLabelY->setText(QString::fromUtf8("Y"));

        gridLayout1->addWidget(TextLabelY, 2, 0, 1, 1);

        yPos = new Gui::QuantitySpinBox(GroupBox5);
        yPos->setObjectName("yPos");

        gridLayout1->addWidget(yPos, 2, 1, 1, 1);

        TextLabelZ = new QLabel(GroupBox5);
        TextLabelZ->setObjectName("TextLabelZ");
        sizePolicy.setHeightForWidth(TextLabelZ->sizePolicy().hasHeightForWidth());
        TextLabelZ->setSizePolicy(sizePolicy);
        TextLabelZ->setText(QString::fromUtf8("Z"));

        gridLayout1->addWidget(TextLabelZ, 3, 0, 1, 1);

        zPos = new Gui::QuantitySpinBox(GroupBox5);
        zPos->setObjectName("zPos");

        gridLayout1->addWidget(zPos, 3, 1, 1, 1);

        TextLabelAxial = new QLabel(GroupBox5);
        TextLabelAxial->setObjectName("TextLabelAxial");
        sizePolicy.setHeightForWidth(TextLabelAxial->sizePolicy().hasHeightForWidth());
        TextLabelAxial->setSizePolicy(sizePolicy);

        gridLayout1->addWidget(TextLabelAxial, 4, 0, 1, 1);

        axialPos = new Gui::QuantitySpinBox(GroupBox5);
        axialPos->setObjectName("axialPos");

        gridLayout1->addWidget(axialPos, 4, 1, 1, 1);

        applyAxial = new QPushButton(GroupBox5);
        applyAxial->setObjectName("applyAxial");

        gridLayout1->addWidget(applyAxial, 5, 1, 1, 1);


        gridLayout->addWidget(GroupBox5, 0, 0, 1, 1);

        GroupBox5_3 = new QGroupBox(Gui__Dialog__Placement);
        GroupBox5_3->setObjectName("GroupBox5_3");
        gridLayout2 = new QGridLayout(GroupBox5_3);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        TextLabelX_2 = new QLabel(GroupBox5_3);
        TextLabelX_2->setObjectName("TextLabelX_2");
        sizePolicy.setHeightForWidth(TextLabelX_2->sizePolicy().hasHeightForWidth());
        TextLabelX_2->setSizePolicy(sizePolicy);
        TextLabelX_2->setText(QString::fromUtf8("X"));

        gridLayout2->addWidget(TextLabelX_2, 0, 0, 1, 1);

        xCnt = new Gui::QuantitySpinBox(GroupBox5_3);
        xCnt->setObjectName("xCnt");

        gridLayout2->addWidget(xCnt, 0, 1, 1, 1);

        TextLabelY_2 = new QLabel(GroupBox5_3);
        TextLabelY_2->setObjectName("TextLabelY_2");
        sizePolicy.setHeightForWidth(TextLabelY_2->sizePolicy().hasHeightForWidth());
        TextLabelY_2->setSizePolicy(sizePolicy);
        TextLabelY_2->setText(QString::fromUtf8("Y"));

        gridLayout2->addWidget(TextLabelY_2, 1, 0, 1, 1);

        yCnt = new Gui::QuantitySpinBox(GroupBox5_3);
        yCnt->setObjectName("yCnt");

        gridLayout2->addWidget(yCnt, 1, 1, 1, 1);

        TextLabelZ_5 = new QLabel(GroupBox5_3);
        TextLabelZ_5->setObjectName("TextLabelZ_5");
        sizePolicy.setHeightForWidth(TextLabelZ_5->sizePolicy().hasHeightForWidth());
        TextLabelZ_5->setSizePolicy(sizePolicy);
        TextLabelZ_5->setText(QString::fromUtf8("Z"));

        gridLayout2->addWidget(TextLabelZ_5, 2, 0, 1, 1);

        zCnt = new Gui::QuantitySpinBox(GroupBox5_3);
        zCnt->setObjectName("zCnt");

        gridLayout2->addWidget(zCnt, 2, 1, 1, 1);

        centerOfMass = new QCheckBox(GroupBox5_3);
        centerOfMass->setObjectName("centerOfMass");

        gridLayout2->addWidget(centerOfMass, 3, 0, 1, 2);

        selectedVertex = new QPushButton(GroupBox5_3);
        selectedVertex->setObjectName("selectedVertex");

        gridLayout2->addWidget(selectedVertex, 4, 0, 1, 2);


        gridLayout->addWidget(GroupBox5_3, 0, 1, 1, 1);

        GroupBox5_2 = new QGroupBox(Gui__Dialog__Placement);
        GroupBox5_2->setObjectName("GroupBox5_2");
        gridLayout3 = new QGridLayout(GroupBox5_2);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName("gridLayout3");
        gridLayout3->setContentsMargins(9, 9, 9, 9);
        rotationInput = new QComboBox(GroupBox5_2);
        rotationInput->addItem(QString());
        rotationInput->addItem(QString());
        rotationInput->setObjectName("rotationInput");

        gridLayout3->addWidget(rotationInput, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(GroupBox5_2);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        gridLayout4 = new QGridLayout(page);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName("gridLayout4");
        gridLayout4->setContentsMargins(9, 0, 9, 0);
        gridLayout5 = new QGridLayout();
        gridLayout5->setSpacing(6);
        gridLayout5->setObjectName("gridLayout5");
        gridLayout5->setContentsMargins(0, 0, 0, 0);
        TextLabelAxis = new QLabel(page);
        TextLabelAxis->setObjectName("TextLabelAxis");
        sizePolicy.setHeightForWidth(TextLabelAxis->sizePolicy().hasHeightForWidth());
        TextLabelAxis->setSizePolicy(sizePolicy);

        gridLayout5->addWidget(TextLabelAxis, 0, 0, 1, 1);

        xAxis = new Gui::QuantitySpinBox(page);
        xAxis->setObjectName("xAxis");

        gridLayout5->addWidget(xAxis, 0, 1, 1, 1);

        yAxis = new Gui::QuantitySpinBox(page);
        yAxis->setObjectName("yAxis");

        gridLayout5->addWidget(yAxis, 1, 1, 1, 1);

        zAxis = new Gui::QuantitySpinBox(page);
        zAxis->setObjectName("zAxis");

        gridLayout5->addWidget(zAxis, 2, 1, 1, 1);

        textLabelAngle = new QLabel(page);
        textLabelAngle->setObjectName("textLabelAngle");
        sizePolicy.setHeightForWidth(textLabelAngle->sizePolicy().hasHeightForWidth());
        textLabelAngle->setSizePolicy(sizePolicy);

        gridLayout5->addWidget(textLabelAngle, 3, 0, 1, 1);

        angle = new Gui::QuantitySpinBox(page);
        angle->setObjectName("angle");

        gridLayout5->addWidget(angle, 3, 1, 1, 1);


        gridLayout4->addLayout(gridLayout5, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        gridLayout6 = new QGridLayout(page_3);
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(11, 11, 11, 11);
        gridLayout6->setObjectName("gridLayout6");
        gridLayout6->setContentsMargins(9, 0, 9, 0);
        gridLayout7 = new QGridLayout();
        gridLayout7->setSpacing(6);
        gridLayout7->setObjectName("gridLayout7");
        gridLayout7->setContentsMargins(0, 0, 0, 0);
        TextLabelZ_2 = new QLabel(page_3);
        TextLabelZ_2->setObjectName("TextLabelZ_2");
        sizePolicy.setHeightForWidth(TextLabelZ_2->sizePolicy().hasHeightForWidth());
        TextLabelZ_2->setSizePolicy(sizePolicy);

        gridLayout7->addWidget(TextLabelZ_2, 0, 0, 1, 1);

        yawAngle = new Gui::QuantitySpinBox(page_3);
        yawAngle->setObjectName("yawAngle");

        gridLayout7->addWidget(yawAngle, 0, 1, 1, 1);

        TextLabelZ_3 = new QLabel(page_3);
        TextLabelZ_3->setObjectName("TextLabelZ_3");
        sizePolicy.setHeightForWidth(TextLabelZ_3->sizePolicy().hasHeightForWidth());
        TextLabelZ_3->setSizePolicy(sizePolicy);

        gridLayout7->addWidget(TextLabelZ_3, 1, 0, 1, 1);

        pitchAngle = new Gui::QuantitySpinBox(page_3);
        pitchAngle->setObjectName("pitchAngle");

        gridLayout7->addWidget(pitchAngle, 1, 1, 1, 1);

        TextLabelZ_4 = new QLabel(page_3);
        TextLabelZ_4->setObjectName("TextLabelZ_4");
        sizePolicy.setHeightForWidth(TextLabelZ_4->sizePolicy().hasHeightForWidth());
        TextLabelZ_4->setSizePolicy(sizePolicy);

        gridLayout7->addWidget(TextLabelZ_4, 2, 0, 1, 1);

        rollAngle = new Gui::QuantitySpinBox(page_3);
        rollAngle->setObjectName("rollAngle");

        gridLayout7->addWidget(rollAngle, 2, 1, 1, 1);


        gridLayout6->addLayout(gridLayout7, 0, 0, 1, 1);

        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        gridLayout3->addWidget(stackedWidget, 1, 0, 1, 1);


        gridLayout->addWidget(GroupBox5_2, 1, 0, 1, 2);

        vSpacer = new QSpacerItem(20, 41, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(vSpacer, 2, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        applyIncrementalPlacement = new QCheckBox(Gui__Dialog__Placement);
        applyIncrementalPlacement->setObjectName("applyIncrementalPlacement");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(applyIncrementalPlacement->sizePolicy().hasHeightForWidth());
        applyIncrementalPlacement->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(applyIncrementalPlacement);

        hSpacer = new QSpacerItem(78, 22, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(hSpacer);

        resetButton = new QPushButton(Gui__Dialog__Placement);
        resetButton->setObjectName("resetButton");

        horizontalLayout->addWidget(resetButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 2);

        buttonBoxLayout = new QHBoxLayout();
        buttonBoxLayout->setSpacing(6);
        buttonBoxLayout->setObjectName("buttonBoxLayout");
        buttonBoxSpacer = new QSpacerItem(88, 24, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonBoxLayout->addItem(buttonBoxSpacer);

        buttonBox = new QDialogButtonBox(Gui__Dialog__Placement);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonBoxLayout->addWidget(buttonBox);


        gridLayout->addLayout(buttonBoxLayout, 4, 0, 1, 2);


        retranslateUi(Gui__Dialog__Placement);
        QObject::connect(rotationInput, &QComboBox::activated, stackedWidget, &QStackedWidget::setCurrentIndex);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Gui__Dialog__Placement, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__Placement, qOverload<>(&QDialog::reject));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Gui__Dialog__Placement);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__Placement)
    {
        Gui__Dialog__Placement->setWindowTitle(QCoreApplication::translate("Gui::Dialog::Placement", "Placement", nullptr));
        GroupBox5->setTitle(QCoreApplication::translate("Gui::Dialog::Placement", "Translation", nullptr));
        TextLabelAxial->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Axial", nullptr));
#if QT_CONFIG(tooltip)
        applyAxial->setToolTip(QCoreApplication::translate("Gui::Dialog::Placement", "Shift-click for opposite direction", nullptr));
#endif // QT_CONFIG(tooltip)
        applyAxial->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Apply Axial", nullptr));
        GroupBox5_3->setTitle(QCoreApplication::translate("Gui::Dialog::Placement", "Center", nullptr));
        centerOfMass->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Use center of mass", nullptr));
        selectedVertex->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Selected Points", nullptr));
        GroupBox5_2->setTitle(QCoreApplication::translate("Gui::Dialog::Placement", "Rotation", nullptr));
        rotationInput->setItemText(0, QCoreApplication::translate("Gui::Dialog::Placement", "Rotation axis and angle", nullptr));
        rotationInput->setItemText(1, QCoreApplication::translate("Gui::Dialog::Placement", "Euler angles (Z\342\200\223Y\342\200\262\342\200\223X\342\200\263)", nullptr));

        TextLabelAxis->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Axis", nullptr));
        textLabelAngle->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Angle", nullptr));
        TextLabelZ_2->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Yaw (around Z-axis)", nullptr));
#if QT_CONFIG(tooltip)
        yawAngle->setToolTip(QCoreApplication::translate("Gui::Dialog::Placement", "Yaw (around Z-axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        TextLabelZ_3->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Pitch (around Y-axis)", nullptr));
#if QT_CONFIG(tooltip)
        pitchAngle->setToolTip(QCoreApplication::translate("Gui::Dialog::Placement", "Pitch (around Y-axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        TextLabelZ_4->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Roll (around X-axis)", nullptr));
#if QT_CONFIG(tooltip)
        rollAngle->setToolTip(QCoreApplication::translate("Gui::Dialog::Placement", "Roll (around the X-axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        applyIncrementalPlacement->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Apply incremental changes", nullptr));
        resetButton->setText(QCoreApplication::translate("Gui::Dialog::Placement", "Reset", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class Placement: public Ui_Placement {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_PLACEMENT_H
