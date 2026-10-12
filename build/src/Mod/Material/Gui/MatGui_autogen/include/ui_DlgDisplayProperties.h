/********************************************************************************
** Form generated from reading UI file 'DlgDisplayProperties.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDISPLAYPROPERTIES_H
#define UI_DLGDISPLAYPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include "Gui/Widgets.h"
#include "Mod/Material/Gui/MaterialTreeWidget.h"

namespace MatGui {

class Ui_DlgDisplayProperties
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout_3;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QComboBox *changeMode;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1_3;
    QComboBox *changePlot;
    QGroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel2;
    QSpacerItem *spacerItem;
    QSpinBox *spinPointSize;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel3;
    QSpacerItem *spacerItem1;
    QSpinBox *spinLineWidth;
    QLabel *textLabel1_2;
    QHBoxLayout *hboxLayout4;
    QSlider *horizontalSlider;
    QSpinBox *spinTransparency;
    QLabel *label;
    QHBoxLayout *hboxLayout5;
    QSlider *sliderLineTransparency;
    QSpinBox *spinLineTransparency;
    QGroupBox *groupBox3;
    QGridLayout *gridLayout_2;
    QHBoxLayout *hboxLayout6;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_6;
    Gui::ColorButton *buttonPointColor;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *buttonColorPlot;
    Gui::ColorButton *buttonLineColor;
    QPushButton *buttonCustomAppearance;
    MatGui::MaterialTreeWidget *widgetMaterial;

    void setupUi(QDialog *MatGui__DlgDisplayProperties)
    {
        if (MatGui__DlgDisplayProperties->objectName().isEmpty())
            MatGui__DlgDisplayProperties->setObjectName("MatGui__DlgDisplayProperties");
        MatGui__DlgDisplayProperties->resize(290, 503);
        gridLayout_4 = new QGridLayout(MatGui__DlgDisplayProperties);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox1 = new QGroupBox(MatGui__DlgDisplayProperties);
        groupBox1->setObjectName("groupBox1");
        gridLayout_3 = new QGridLayout(groupBox1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(groupBox1);
        textLabel1->setObjectName("textLabel1");

        hboxLayout->addWidget(textLabel1);

        changeMode = new QComboBox(groupBox1);
        changeMode->setObjectName("changeMode");

        hboxLayout->addWidget(changeMode);


        gridLayout_3->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        textLabel1_3 = new QLabel(groupBox1);
        textLabel1_3->setObjectName("textLabel1_3");
        textLabel1_3->setEnabled(false);

        hboxLayout1->addWidget(textLabel1_3);

        changePlot = new QComboBox(groupBox1);
        changePlot->setObjectName("changePlot");
        changePlot->setEnabled(false);

        hboxLayout1->addWidget(changePlot);


        gridLayout_3->addLayout(hboxLayout1, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox1, 0, 0, 1, 1);

        groupBox2 = new QGroupBox(MatGui__DlgDisplayProperties);
        groupBox2->setObjectName("groupBox2");
        gridLayout1 = new QGridLayout(groupBox2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        textLabel2 = new QLabel(groupBox2);
        textLabel2->setObjectName("textLabel2");

        hboxLayout2->addWidget(textLabel2);

        spacerItem = new QSpacerItem(71, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem);

        spinPointSize = new QSpinBox(groupBox2);
        spinPointSize->setObjectName("spinPointSize");
        spinPointSize->setMinimum(1);
        spinPointSize->setMaximum(64);
        spinPointSize->setValue(2);

        hboxLayout2->addWidget(spinPointSize);


        gridLayout1->addLayout(hboxLayout2, 0, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName("hboxLayout3");
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        textLabel3 = new QLabel(groupBox2);
        textLabel3->setObjectName("textLabel3");

        hboxLayout3->addWidget(textLabel3);

        spacerItem1 = new QSpacerItem(71, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem1);

        spinLineWidth = new QSpinBox(groupBox2);
        spinLineWidth->setObjectName("spinLineWidth");
        spinLineWidth->setMinimum(1);
        spinLineWidth->setMaximum(64);
        spinLineWidth->setValue(2);

        hboxLayout3->addWidget(spinLineWidth);


        gridLayout1->addLayout(hboxLayout3, 1, 0, 1, 1);

        textLabel1_2 = new QLabel(groupBox2);
        textLabel1_2->setObjectName("textLabel1_2");

        gridLayout1->addWidget(textLabel1_2, 2, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName("hboxLayout4");
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(groupBox2);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        hboxLayout4->addWidget(horizontalSlider);

        spinTransparency = new QSpinBox(groupBox2);
        spinTransparency->setObjectName("spinTransparency");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinTransparency->sizePolicy().hasHeightForWidth());
        spinTransparency->setSizePolicy(sizePolicy);
        spinTransparency->setMaximum(100);
        spinTransparency->setSingleStep(5);

        hboxLayout4->addWidget(spinTransparency);


        gridLayout1->addLayout(hboxLayout4, 3, 0, 1, 1);

        label = new QLabel(groupBox2);
        label->setObjectName("label");

        gridLayout1->addWidget(label, 4, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName("hboxLayout5");
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        sliderLineTransparency = new QSlider(groupBox2);
        sliderLineTransparency->setObjectName("sliderLineTransparency");
        sliderLineTransparency->setMaximum(100);
        sliderLineTransparency->setOrientation(Qt::Horizontal);

        hboxLayout5->addWidget(sliderLineTransparency);

        spinLineTransparency = new QSpinBox(groupBox2);
        spinLineTransparency->setObjectName("spinLineTransparency");
        spinLineTransparency->setMaximum(100);
        spinLineTransparency->setSingleStep(5);

        hboxLayout5->addWidget(spinLineTransparency);


        gridLayout1->addLayout(hboxLayout5, 5, 0, 1, 1);


        gridLayout_4->addWidget(groupBox2, 2, 0, 1, 1);

        groupBox3 = new QGroupBox(MatGui__DlgDisplayProperties);
        groupBox3->setObjectName("groupBox3");
        gridLayout_2 = new QGridLayout(groupBox3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName("hboxLayout6");
        hboxLayout6->setContentsMargins(0, 0, 0, 0);

        gridLayout_2->addLayout(hboxLayout6, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        label_4 = new QLabel(groupBox3);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox3);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        buttonPointColor = new Gui::ColorButton(groupBox3);
        buttonPointColor->setObjectName("buttonPointColor");

        gridLayout->addWidget(buttonPointColor, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox3);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox3);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        buttonColorPlot = new QPushButton(groupBox3);
        buttonColorPlot->setObjectName("buttonColorPlot");
        buttonColorPlot->setText(QString::fromUtf8("Color Plot"));

        gridLayout->addWidget(buttonColorPlot, 1, 1, 1, 1);

        buttonLineColor = new Gui::ColorButton(groupBox3);
        buttonLineColor->setObjectName("buttonLineColor");

        gridLayout->addWidget(buttonLineColor, 2, 1, 1, 1);

        buttonCustomAppearance = new QPushButton(groupBox3);
        buttonCustomAppearance->setObjectName("buttonCustomAppearance");
        buttonCustomAppearance->setText(QString::fromUtf8("Appearance"));

        gridLayout->addWidget(buttonCustomAppearance, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        widgetMaterial = new MatGui::MaterialTreeWidget(groupBox3);
        widgetMaterial->setObjectName("widgetMaterial");

        gridLayout_2->addWidget(widgetMaterial, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox3, 1, 0, 1, 1);

        QWidget::setTabOrder(changeMode, changePlot);
        QWidget::setTabOrder(changePlot, buttonLineColor);
        QWidget::setTabOrder(buttonLineColor, spinPointSize);
        QWidget::setTabOrder(spinPointSize, spinLineWidth);
        QWidget::setTabOrder(spinLineWidth, horizontalSlider);
        QWidget::setTabOrder(horizontalSlider, spinTransparency);
        QWidget::setTabOrder(spinTransparency, sliderLineTransparency);
        QWidget::setTabOrder(sliderLineTransparency, spinLineTransparency);

        retranslateUi(MatGui__DlgDisplayProperties);
        QObject::connect(spinTransparency, &QSpinBox::valueChanged, horizontalSlider, &QSlider::setValue);
        QObject::connect(horizontalSlider, &QSlider::valueChanged, spinTransparency, &QSpinBox::setValue);
        QObject::connect(sliderLineTransparency, &QSlider::valueChanged, spinLineTransparency, &QSpinBox::setValue);
        QObject::connect(spinLineTransparency, &QSpinBox::valueChanged, sliderLineTransparency, &QSlider::setValue);

        QMetaObject::connectSlotsByName(MatGui__DlgDisplayProperties);
    } // setupUi

    void retranslateUi(QDialog *MatGui__DlgDisplayProperties)
    {
        MatGui__DlgDisplayProperties->setWindowTitle(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Display Properties", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Viewing Mode", nullptr));
        textLabel1->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Document window", nullptr));
        textLabel1_3->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Plot mode", nullptr));
        groupBox2->setTitle(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Display", nullptr));
        textLabel2->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Point size", nullptr));
        textLabel3->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Line width", nullptr));
        textLabel1_2->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Transparency", nullptr));
        label->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Line transparency", nullptr));
        groupBox3->setTitle(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Material", nullptr));
        label_4->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Color plot", nullptr));
        label_6->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Custom appearance", nullptr));
        label_5->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Point color", nullptr));
        label_3->setText(QCoreApplication::translate("MatGui::DlgDisplayProperties", "Line color", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgDisplayProperties: public Ui_DlgDisplayProperties {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGDISPLAYPROPERTIES_H
