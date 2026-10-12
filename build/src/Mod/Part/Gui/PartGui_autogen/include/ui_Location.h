/********************************************************************************
** Form generated from reading UI file 'Location.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCATION_H
#define UI_LOCATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartGui {

class Ui_Location
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *PositionGB;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *labelLength2_2;
    Gui::QuantitySpinBox *XPositionQSB;
    QLabel *labelLength2_3;
    Gui::QuantitySpinBox *YPositionQSB;
    QLabel *labelLength2_4;
    Gui::QuantitySpinBox *ZPositionQSB;
    QPushButton *viewPositionButton;
    QGroupBox *RotationGB;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *labelXSkew;
    Gui::DoubleSpinBox *XDirectionEdit;
    QLabel *labelYSkew;
    Gui::DoubleSpinBox *YDirectionEdit;
    QLabel *labelZSkew;
    Gui::DoubleSpinBox *ZDirectionEdit;
    QLabel *labelLength2;
    Gui::QuantitySpinBox *AngleQSB;

    void setupUi(QWidget *PartGui__Location)
    {
        if (PartGui__Location->objectName().isEmpty())
            PartGui__Location->setObjectName("PartGui__Location");
        PartGui__Location->resize(280, 400);
        PartGui__Location->setProperty("sizeGripEnabled", QVariant(true));
        verticalLayout = new QVBoxLayout(PartGui__Location);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        PositionGB = new QGroupBox(PartGui__Location);
        PositionGB->setObjectName("PositionGB");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PositionGB->sizePolicy().hasHeightForWidth());
        PositionGB->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(PositionGB);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        labelLength2_2 = new QLabel(PositionGB);
        labelLength2_2->setObjectName("labelLength2_2");

        gridLayout->addWidget(labelLength2_2, 0, 0, 1, 1);

        XPositionQSB = new Gui::QuantitySpinBox(PositionGB);
        XPositionQSB->setObjectName("XPositionQSB");
        XPositionQSB->setKeyboardTracking(false);
        XPositionQSB->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout->addWidget(XPositionQSB, 0, 1, 1, 1);

        labelLength2_3 = new QLabel(PositionGB);
        labelLength2_3->setObjectName("labelLength2_3");

        gridLayout->addWidget(labelLength2_3, 1, 0, 1, 1);

        YPositionQSB = new Gui::QuantitySpinBox(PositionGB);
        YPositionQSB->setObjectName("YPositionQSB");
        YPositionQSB->setKeyboardTracking(false);
        YPositionQSB->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout->addWidget(YPositionQSB, 1, 1, 1, 1);

        labelLength2_4 = new QLabel(PositionGB);
        labelLength2_4->setObjectName("labelLength2_4");

        gridLayout->addWidget(labelLength2_4, 2, 0, 1, 1);

        ZPositionQSB = new Gui::QuantitySpinBox(PositionGB);
        ZPositionQSB->setObjectName("ZPositionQSB");
        ZPositionQSB->setKeyboardTracking(false);
        ZPositionQSB->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout->addWidget(ZPositionQSB, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        viewPositionButton = new QPushButton(PositionGB);
        viewPositionButton->setObjectName("viewPositionButton");
        viewPositionButton->setCheckable(true);

        verticalLayout_2->addWidget(viewPositionButton);


        verticalLayout->addWidget(PositionGB);

        RotationGB = new QGroupBox(PartGui__Location);
        RotationGB->setObjectName("RotationGB");
        sizePolicy.setHeightForWidth(RotationGB->sizePolicy().hasHeightForWidth());
        RotationGB->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(RotationGB);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName("gridLayout_2");
        labelXSkew = new QLabel(RotationGB);
        labelXSkew->setObjectName("labelXSkew");

        gridLayout_2->addWidget(labelXSkew, 0, 0, 1, 1);

        XDirectionEdit = new Gui::DoubleSpinBox(RotationGB);
        XDirectionEdit->setObjectName("XDirectionEdit");
        XDirectionEdit->setKeyboardTracking(false);
        XDirectionEdit->setMinimum(-100.000000000000000);
        XDirectionEdit->setMaximum(100.000000000000000);
        XDirectionEdit->setSingleStep(0.100000000000000);
        XDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(XDirectionEdit, 0, 1, 1, 1);

        labelYSkew = new QLabel(RotationGB);
        labelYSkew->setObjectName("labelYSkew");

        gridLayout_2->addWidget(labelYSkew, 1, 0, 1, 1);

        YDirectionEdit = new Gui::DoubleSpinBox(RotationGB);
        YDirectionEdit->setObjectName("YDirectionEdit");
        YDirectionEdit->setKeyboardTracking(false);
        YDirectionEdit->setMinimum(-100.000000000000000);
        YDirectionEdit->setMaximum(100.000000000000000);
        YDirectionEdit->setSingleStep(0.100000000000000);
        YDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(YDirectionEdit, 1, 1, 1, 1);

        labelZSkew = new QLabel(RotationGB);
        labelZSkew->setObjectName("labelZSkew");

        gridLayout_2->addWidget(labelZSkew, 2, 0, 1, 1);

        ZDirectionEdit = new Gui::DoubleSpinBox(RotationGB);
        ZDirectionEdit->setObjectName("ZDirectionEdit");
        ZDirectionEdit->setKeyboardTracking(false);
        ZDirectionEdit->setMinimum(-100.000000000000000);
        ZDirectionEdit->setMaximum(100.000000000000000);
        ZDirectionEdit->setSingleStep(0.100000000000000);
        ZDirectionEdit->setValue(1.000000000000000);
        ZDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(ZDirectionEdit, 2, 1, 1, 1);

        labelLength2 = new QLabel(RotationGB);
        labelLength2->setObjectName("labelLength2");

        gridLayout_2->addWidget(labelLength2, 3, 0, 1, 1);

        AngleQSB = new Gui::QuantitySpinBox(RotationGB);
        AngleQSB->setObjectName("AngleQSB");
        AngleQSB->setProperty("unit", QVariant(QString::fromUtf8("")));
        AngleQSB->setSingleStep(5.000000000000000);

        gridLayout_2->addWidget(AngleQSB, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout->addWidget(RotationGB);


        retranslateUi(PartGui__Location);

        QMetaObject::connectSlotsByName(PartGui__Location);
    } // setupUi

    void retranslateUi(QWidget *PartGui__Location)
    {
        PartGui__Location->setWindowTitle(QCoreApplication::translate("PartGui::Location", "Location", nullptr));
        PositionGB->setTitle(QCoreApplication::translate("PartGui::Location", "Position", nullptr));
#if QT_CONFIG(tooltip)
        PositionGB->setToolTip(QCoreApplication::translate("PartGui::Location", "Set the placement location coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelLength2_2->setToolTip(QCoreApplication::translate("PartGui::Location", "X coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLength2_2->setText(QCoreApplication::translate("PartGui::Location", "X", nullptr));
#if QT_CONFIG(tooltip)
        XPositionQSB->setToolTip(QCoreApplication::translate("PartGui::Location", "X coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelLength2_3->setToolTip(QCoreApplication::translate("PartGui::Location", "Y coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLength2_3->setText(QCoreApplication::translate("PartGui::Location", "Y", nullptr));
#if QT_CONFIG(tooltip)
        YPositionQSB->setToolTip(QCoreApplication::translate("PartGui::Location", "Y coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelLength2_4->setToolTip(QCoreApplication::translate("PartGui::Location", "Z coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLength2_4->setText(QCoreApplication::translate("PartGui::Location", "Z", nullptr));
#if QT_CONFIG(tooltip)
        ZPositionQSB->setToolTip(QCoreApplication::translate("PartGui::Location", "Z coordinate of the placement location", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        viewPositionButton->setToolTip(QCoreApplication::translate("PartGui::Location", "Select a point in the 3D view to set the location automatically", nullptr));
#endif // QT_CONFIG(tooltip)
        viewPositionButton->setText(QCoreApplication::translate("PartGui::Location", "Pick Position", nullptr));
#if QT_CONFIG(tooltip)
        RotationGB->setToolTip(QCoreApplication::translate("PartGui::Location", "Use custom vector for pad direction otherwise\n"
"the sketch plane's normal vector will be used", nullptr));
#endif // QT_CONFIG(tooltip)
        RotationGB->setTitle(QCoreApplication::translate("PartGui::Location", "Rotation Axis", nullptr));
#if QT_CONFIG(tooltip)
        labelXSkew->setToolTip(QCoreApplication::translate("PartGui::Location", "X-component of the rotation axis direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelXSkew->setText(QCoreApplication::translate("PartGui::Location", "X", nullptr));
#if QT_CONFIG(tooltip)
        XDirectionEdit->setToolTip(QCoreApplication::translate("PartGui::Location", "X-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelYSkew->setToolTip(QCoreApplication::translate("PartGui::Location", "Y-component of the rotation axis direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelYSkew->setText(QCoreApplication::translate("PartGui::Location", "Y", nullptr));
#if QT_CONFIG(tooltip)
        YDirectionEdit->setToolTip(QCoreApplication::translate("PartGui::Location", "Y-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelZSkew->setToolTip(QCoreApplication::translate("PartGui::Location", "Z-component of the rotation axis direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelZSkew->setText(QCoreApplication::translate("PartGui::Location", "Z", nullptr));
#if QT_CONFIG(tooltip)
        ZDirectionEdit->setToolTip(QCoreApplication::translate("PartGui::Location", "Z-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        labelLength2->setToolTip(QCoreApplication::translate("PartGui::Location", "Rotation angle around the specified axis", nullptr));
#endif // QT_CONFIG(tooltip)
        labelLength2->setText(QCoreApplication::translate("PartGui::Location", "Angle", nullptr));
#if QT_CONFIG(tooltip)
        AngleQSB->setToolTip(QCoreApplication::translate("PartGui::Location", "Rotation angle around the specified axis", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class Location: public Ui_Location {};
} // namespace Ui
} // namespace PartGui

#endif // UI_LOCATION_H
