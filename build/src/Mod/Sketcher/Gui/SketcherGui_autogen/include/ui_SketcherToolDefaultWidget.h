/********************************************************************************
** Form generated from reading UI file 'SketcherToolDefaultWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKETCHERTOOLDEFAULTWIDGET_H
#define UI_SKETCHERTOOLDEFAULTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace SketcherGui {

class Ui_SketcherToolDefaultWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *comboLayout1;
    QLabel *comboLabel1;
    Gui::PrefComboBox *comboBox1;
    QHBoxLayout *comboLayout2;
    QLabel *comboLabel2;
    Gui::PrefComboBox *comboBox2;
    QHBoxLayout *comboLayout3;
    QLabel *comboLabel3;
    Gui::PrefComboBox *comboBox3;
    QHBoxLayout *lineEditLayout1;
    QLabel *lineEditLabel1;
    QLineEdit *lineEdit1;
    QHBoxLayout *lineEditLayout2;
    QLabel *lineEditLabel2;
    QLineEdit *lineEdit2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::PrefQuantitySpinBox *parameterOne;
    QHBoxLayout *horizontalLayout2;
    QLabel *label2;
    Gui::PrefQuantitySpinBox *parameterTwo;
    QHBoxLayout *horizontalLayout3;
    QLabel *label3;
    Gui::PrefQuantitySpinBox *parameterThree;
    QHBoxLayout *horizontalLayout4;
    QLabel *label4;
    Gui::PrefQuantitySpinBox *parameterFour;
    QHBoxLayout *horizontalLayout5;
    QLabel *label5;
    Gui::PrefQuantitySpinBox *parameterFive;
    QHBoxLayout *horizontalLayout6;
    QLabel *label6;
    Gui::PrefQuantitySpinBox *parameterSix;
    QHBoxLayout *horizontalLayout7;
    QLabel *label7;
    Gui::PrefQuantitySpinBox *parameterSeven;
    QHBoxLayout *horizontalLayout8;
    QLabel *label8;
    Gui::PrefQuantitySpinBox *parameterEight;
    QHBoxLayout *horizontalLayout9;
    QLabel *label9;
    Gui::PrefQuantitySpinBox *parameterNine;
    QHBoxLayout *horizontalLayout10;
    QLabel *label10;
    Gui::PrefQuantitySpinBox *parameterTen;
    Gui::PrefCheckBox *checkBoxTS1;
    Gui::PrefCheckBox *checkBoxTS2;
    Gui::PrefCheckBox *checkBoxTS3;
    Gui::PrefCheckBox *checkBoxTS4;
    QLabel *notice;

    void setupUi(QWidget *SketcherGui__SketcherToolDefaultWidget)
    {
        if (SketcherGui__SketcherToolDefaultWidget->objectName().isEmpty())
            SketcherGui__SketcherToolDefaultWidget->setObjectName("SketcherGui__SketcherToolDefaultWidget");
        SketcherGui__SketcherToolDefaultWidget->resize(312, 254);
        verticalLayout = new QVBoxLayout(SketcherGui__SketcherToolDefaultWidget);
        verticalLayout->setObjectName("verticalLayout");
        comboLayout1 = new QHBoxLayout();
        comboLayout1->setObjectName("comboLayout1");
        comboLabel1 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        comboLabel1->setObjectName("comboLabel1");

        comboLayout1->addWidget(comboLabel1);

        comboBox1 = new Gui::PrefComboBox(SketcherGui__SketcherToolDefaultWidget);
        comboBox1->setObjectName("comboBox1");
        comboBox1->setCurrentIndex(0);
        comboBox1->setPrefEntry("");
        comboBox1->setPrefPath("Mod/Sketcher/General");

        comboLayout1->addWidget(comboBox1);


        verticalLayout->addLayout(comboLayout1);

        comboLayout2 = new QHBoxLayout();
        comboLayout2->setObjectName("comboLayout2");
        comboLabel2 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        comboLabel2->setObjectName("comboLabel2");

        comboLayout2->addWidget(comboLabel2);

        comboBox2 = new Gui::PrefComboBox(SketcherGui__SketcherToolDefaultWidget);
        comboBox2->setObjectName("comboBox2");
        comboBox2->setCurrentIndex(0);
        comboBox2->setPrefEntry("");
        comboBox2->setPrefPath("Mod/Sketcher/General");

        comboLayout2->addWidget(comboBox2);


        verticalLayout->addLayout(comboLayout2);

        comboLayout3 = new QHBoxLayout();
        comboLayout3->setObjectName("comboLayout3");
        comboLabel3 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        comboLabel3->setObjectName("comboLabel3");

        comboLayout3->addWidget(comboLabel3);

        comboBox3 = new Gui::PrefComboBox(SketcherGui__SketcherToolDefaultWidget);
        comboBox3->setObjectName("comboBox3");
        comboBox3->setCurrentIndex(0);
        comboBox3->setPrefEntry("");
        comboBox3->setPrefPath("Mod/Sketcher/General");

        comboLayout3->addWidget(comboBox3);


        verticalLayout->addLayout(comboLayout3);

        lineEditLayout1 = new QHBoxLayout();
        lineEditLayout1->setObjectName("lineEditLayout1");
        lineEditLabel1 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        lineEditLabel1->setObjectName("lineEditLabel1");

        lineEditLayout1->addWidget(lineEditLabel1);

        lineEdit1 = new QLineEdit(SketcherGui__SketcherToolDefaultWidget);
        lineEdit1->setObjectName("lineEdit1");

        lineEditLayout1->addWidget(lineEdit1);


        verticalLayout->addLayout(lineEditLayout1);

        lineEditLayout2 = new QHBoxLayout();
        lineEditLayout2->setObjectName("lineEditLayout2");
        lineEditLabel2 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        lineEditLabel2->setObjectName("lineEditLabel2");

        lineEditLayout2->addWidget(lineEditLabel2);

        lineEdit2 = new QLineEdit(SketcherGui__SketcherToolDefaultWidget);
        lineEdit2->setObjectName("lineEdit2");

        lineEditLayout2->addWidget(lineEdit2);


        verticalLayout->addLayout(lineEditLayout2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        parameterOne = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterOne->setObjectName("parameterOne");
        parameterOne->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterOne->setKeyboardTracking(false);

        horizontalLayout->addWidget(parameterOne);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout2 = new QHBoxLayout();
        horizontalLayout2->setObjectName("horizontalLayout2");
        label2 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label2->setObjectName("label2");

        horizontalLayout2->addWidget(label2);

        parameterTwo = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterTwo->setObjectName("parameterTwo");
        parameterTwo->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterTwo->setKeyboardTracking(false);

        horizontalLayout2->addWidget(parameterTwo);


        verticalLayout->addLayout(horizontalLayout2);

        horizontalLayout3 = new QHBoxLayout();
        horizontalLayout3->setObjectName("horizontalLayout3");
        label3 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label3->setObjectName("label3");

        horizontalLayout3->addWidget(label3);

        parameterThree = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterThree->setObjectName("parameterThree");
        parameterThree->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterThree->setKeyboardTracking(false);

        horizontalLayout3->addWidget(parameterThree);


        verticalLayout->addLayout(horizontalLayout3);

        horizontalLayout4 = new QHBoxLayout();
        horizontalLayout4->setObjectName("horizontalLayout4");
        label4 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label4->setObjectName("label4");

        horizontalLayout4->addWidget(label4);

        parameterFour = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterFour->setObjectName("parameterFour");
        parameterFour->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterFour->setKeyboardTracking(false);

        horizontalLayout4->addWidget(parameterFour);


        verticalLayout->addLayout(horizontalLayout4);

        horizontalLayout5 = new QHBoxLayout();
        horizontalLayout5->setObjectName("horizontalLayout5");
        label5 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label5->setObjectName("label5");

        horizontalLayout5->addWidget(label5);

        parameterFive = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterFive->setObjectName("parameterFive");
        parameterFive->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterFive->setKeyboardTracking(false);

        horizontalLayout5->addWidget(parameterFive);


        verticalLayout->addLayout(horizontalLayout5);

        horizontalLayout6 = new QHBoxLayout();
        horizontalLayout6->setObjectName("horizontalLayout6");
        label6 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label6->setObjectName("label6");

        horizontalLayout6->addWidget(label6);

        parameterSix = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterSix->setObjectName("parameterSix");
        parameterSix->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterSix->setKeyboardTracking(false);

        horizontalLayout6->addWidget(parameterSix);


        verticalLayout->addLayout(horizontalLayout6);

        horizontalLayout7 = new QHBoxLayout();
        horizontalLayout7->setObjectName("horizontalLayout7");
        label7 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label7->setObjectName("label7");

        horizontalLayout7->addWidget(label7);

        parameterSeven = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterSeven->setObjectName("parameterSeven");
        parameterSeven->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterSeven->setKeyboardTracking(false);

        horizontalLayout7->addWidget(parameterSeven);


        verticalLayout->addLayout(horizontalLayout7);

        horizontalLayout8 = new QHBoxLayout();
        horizontalLayout8->setObjectName("horizontalLayout8");
        label8 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label8->setObjectName("label8");

        horizontalLayout8->addWidget(label8);

        parameterEight = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterEight->setObjectName("parameterEight");
        parameterEight->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterEight->setKeyboardTracking(false);

        horizontalLayout8->addWidget(parameterEight);


        verticalLayout->addLayout(horizontalLayout8);

        horizontalLayout9 = new QHBoxLayout();
        horizontalLayout9->setObjectName("horizontalLayout9");
        label9 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label9->setObjectName("label9");

        horizontalLayout9->addWidget(label9);

        parameterNine = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterNine->setObjectName("parameterNine");
        parameterNine->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterNine->setKeyboardTracking(false);

        horizontalLayout9->addWidget(parameterNine);


        verticalLayout->addLayout(horizontalLayout9);

        horizontalLayout10 = new QHBoxLayout();
        horizontalLayout10->setObjectName("horizontalLayout10");
        label10 = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        label10->setObjectName("label10");

        horizontalLayout10->addWidget(label10);

        parameterTen = new Gui::PrefQuantitySpinBox(SketcherGui__SketcherToolDefaultWidget);
        parameterTen->setObjectName("parameterTen");
        parameterTen->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        parameterTen->setKeyboardTracking(false);

        horizontalLayout10->addWidget(parameterTen);


        verticalLayout->addLayout(horizontalLayout10);

        checkBoxTS1 = new Gui::PrefCheckBox(SketcherGui__SketcherToolDefaultWidget);
        checkBoxTS1->setObjectName("checkBoxTS1");
        checkBoxTS1->setEnabled(true);
        checkBoxTS1->setChecked(false);
        checkBoxTS1->setPrefEntry("");
        checkBoxTS1->setPrefPath("Mod/Sketcher/General");

        verticalLayout->addWidget(checkBoxTS1);

        checkBoxTS2 = new Gui::PrefCheckBox(SketcherGui__SketcherToolDefaultWidget);
        checkBoxTS2->setObjectName("checkBoxTS2");
        checkBoxTS2->setEnabled(true);
        checkBoxTS2->setChecked(false);
        checkBoxTS2->setPrefEntry("");
        checkBoxTS2->setPrefPath("Mod/Sketcher/General");

        verticalLayout->addWidget(checkBoxTS2);

        checkBoxTS3 = new Gui::PrefCheckBox(SketcherGui__SketcherToolDefaultWidget);
        checkBoxTS3->setObjectName("checkBoxTS3");
        checkBoxTS3->setEnabled(true);
        checkBoxTS3->setChecked(false);
        checkBoxTS3->setPrefEntry("");
        checkBoxTS3->setPrefPath("Mod/Sketcher/General");

        verticalLayout->addWidget(checkBoxTS3);

        checkBoxTS4 = new Gui::PrefCheckBox(SketcherGui__SketcherToolDefaultWidget);
        checkBoxTS4->setObjectName("checkBoxTS4");
        checkBoxTS4->setEnabled(true);
        checkBoxTS4->setChecked(false);
        checkBoxTS4->setPrefEntry("");
        checkBoxTS4->setPrefPath("Mod/Sketcher/General");

        verticalLayout->addWidget(checkBoxTS4);

        notice = new QLabel(SketcherGui__SketcherToolDefaultWidget);
        notice->setObjectName("notice");
        notice->setMaximumSize(QSize(400, 500));

        verticalLayout->addWidget(notice);


        retranslateUi(SketcherGui__SketcherToolDefaultWidget);

        QMetaObject::connectSlotsByName(SketcherGui__SketcherToolDefaultWidget);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__SketcherToolDefaultWidget)
    {
        SketcherGui__SketcherToolDefaultWidget->setWindowTitle(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Form", nullptr));
        comboLabel1->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Mode (M)", nullptr));
        comboLabel2->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Mode", nullptr));
        comboLabel3->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Mode", nullptr));
        lineEditLabel1->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Line edit 1", nullptr));
        lineEditLabel2->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Line edit 2", nullptr));
        label->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 1", nullptr));
        label2->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 2", nullptr));
        label3->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 3", nullptr));
        label4->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 4", nullptr));
        label5->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 5", nullptr));
        label6->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 6", nullptr));
        label7->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 7", nullptr));
        label8->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 8", nullptr));
        label9->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 9", nullptr));
        label10->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Parameter 10", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTS1->setToolTip(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 1 toolTip", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTS1->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 1", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTS2->setToolTip(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 2 toolTip", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTS2->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 2", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTS3->setToolTip(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 3 toolTip", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTS3->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 3", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxTS4->setToolTip(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 4 toolTip", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxTS4->setText(QCoreApplication::translate("SketcherGui::SketcherToolDefaultWidget", "Checkbox 4", nullptr));
        notice->setText(QString());
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class SketcherToolDefaultWidget: public Ui_SketcherToolDefaultWidget {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_SKETCHERTOOLDEFAULTWIDGET_H
