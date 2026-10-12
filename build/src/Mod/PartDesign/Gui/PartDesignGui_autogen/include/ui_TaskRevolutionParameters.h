/********************************************************************************
** Form generated from reading UI file 'TaskRevolutionParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKREVOLUTIONPARAMETERS_H
#define UI_TASKREVOLUTIONPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

namespace PartDesignGui {

class Ui_TaskRevolutionParameters
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *labelStart;
    QComboBox *startMode;
    QLabel *labelStartReference;
    QLineEdit *lineStartReference;
    QPushButton *buttonStartReference;
    QLabel *labelStartOffset;
    Gui::PrefQuantitySpinBox *startOffsetEdit;
    QLabel *sidesLabel;
    QComboBox *sidesMode;
    QLabel *textLabel1;
    QComboBox *axis;
    QHBoxLayout *side1HeaderLayout;
    QLabel *side1Label;
    QFrame *line1;
    QLabel *textLabelMode;
    QComboBox *changeMode;
    QLabel *labelAngle;
    Gui::QuantitySpinBox *revolveAngle;
    QGridLayout *gridLayout_5;
    QToolButton *buttonFace;
    QLineEdit *lineFaceName;
    QHBoxLayout *side2HeaderLayout;
    QLabel *side2Label;
    QFrame *line2;
    QLabel *typeLabel2;
    QComboBox *changeMode2;
    QLabel *labelAngle2;
    Gui::QuantitySpinBox *revolveAngle2;
    QGridLayout *gridLayout_6;
    QToolButton *buttonFace2;
    QLineEdit *lineFaceName2;
    QCheckBox *checkBoxMidplane;
    QCheckBox *checkBoxProjectAxis;
    QCheckBox *checkBoxReversed;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;
    QFrame *line;
    QCheckBox *checkBoxUpdateView;

    void setupUi(QWidget *PartDesignGui__TaskRevolutionParameters)
    {
        if (PartDesignGui__TaskRevolutionParameters->objectName().isEmpty())
            PartDesignGui__TaskRevolutionParameters->setObjectName("PartDesignGui__TaskRevolutionParameters");
        PartDesignGui__TaskRevolutionParameters->resize(278, 450);
        PartDesignGui__TaskRevolutionParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskRevolutionParameters);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelStart = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelStart->setObjectName("labelStart");

        gridLayout->addWidget(labelStart, 0, 0, 1, 1);

        startMode = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        startMode->addItem(QString());
        startMode->addItem(QString());
        startMode->addItem(QString());
        startMode->setObjectName("startMode");

        gridLayout->addWidget(startMode, 0, 1, 1, 1);

        labelStartReference = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelStartReference->setObjectName("labelStartReference");
        labelStartReference->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(labelStartReference, 1, 0, 2, 1);

        lineStartReference = new QLineEdit(PartDesignGui__TaskRevolutionParameters);
        lineStartReference->setObjectName("lineStartReference");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineStartReference->sizePolicy().hasHeightForWidth());
        lineStartReference->setSizePolicy(sizePolicy);
        lineStartReference->setReadOnly(true);

        gridLayout->addWidget(lineStartReference, 1, 1, 1, 1);

        buttonStartReference = new QPushButton(PartDesignGui__TaskRevolutionParameters);
        buttonStartReference->setObjectName("buttonStartReference");
        sizePolicy.setHeightForWidth(buttonStartReference->sizePolicy().hasHeightForWidth());
        buttonStartReference->setSizePolicy(sizePolicy);
        buttonStartReference->setCheckable(true);

        gridLayout->addWidget(buttonStartReference, 2, 1, 1, 1);

        labelStartOffset = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelStartOffset->setObjectName("labelStartOffset");

        gridLayout->addWidget(labelStartOffset, 3, 0, 1, 1);

        startOffsetEdit = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskRevolutionParameters);
        startOffsetEdit->setObjectName("startOffsetEdit");
        startOffsetEdit->setProperty("keyboardTracking", QVariant(false));
        startOffsetEdit->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        startOffsetEdit->setMinimum(-360.000000000000000);
        startOffsetEdit->setMaximum(360.000000000000000);
        startOffsetEdit->setSingleStep(10.000000000000000);

        gridLayout->addWidget(startOffsetEdit, 3, 1, 1, 1);

        sidesLabel = new QLabel(PartDesignGui__TaskRevolutionParameters);
        sidesLabel->setObjectName("sidesLabel");

        gridLayout->addWidget(sidesLabel, 4, 0, 1, 1);

        sidesMode = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        sidesMode->setObjectName("sidesMode");

        gridLayout->addWidget(sidesMode, 4, 1, 1, 1);

        textLabel1 = new QLabel(PartDesignGui__TaskRevolutionParameters);
        textLabel1->setObjectName("textLabel1");

        gridLayout->addWidget(textLabel1, 5, 0, 1, 1);

        axis = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->addItem(QString());
        axis->setObjectName("axis");

        gridLayout->addWidget(axis, 5, 1, 1, 1);

        side1HeaderLayout = new QHBoxLayout();
        side1HeaderLayout->setObjectName("side1HeaderLayout");
        side1HeaderLayout->setContentsMargins(0, 0, 0, 0);
        side1Label = new QLabel(PartDesignGui__TaskRevolutionParameters);
        side1Label->setObjectName("side1Label");

        side1HeaderLayout->addWidget(side1Label);

        line1 = new QFrame(PartDesignGui__TaskRevolutionParameters);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::Shape::HLine);
        line1->setFrameShadow(QFrame::Shadow::Sunken);

        side1HeaderLayout->addWidget(line1);


        gridLayout->addLayout(side1HeaderLayout, 6, 0, 1, 2);

        textLabelMode = new QLabel(PartDesignGui__TaskRevolutionParameters);
        textLabelMode->setObjectName("textLabelMode");

        gridLayout->addWidget(textLabelMode, 7, 0, 1, 1);

        changeMode = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        changeMode->addItem(QString::fromUtf8("Angle"));
        changeMode->setObjectName("changeMode");

        gridLayout->addWidget(changeMode, 7, 1, 1, 1);

        labelAngle = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelAngle->setObjectName("labelAngle");

        gridLayout->addWidget(labelAngle, 8, 0, 1, 1);

        revolveAngle = new Gui::QuantitySpinBox(PartDesignGui__TaskRevolutionParameters);
        revolveAngle->setObjectName("revolveAngle");
        revolveAngle->setKeyboardTracking(false);
        revolveAngle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        revolveAngle->setMinimum(-360.000000000000000);
        revolveAngle->setMaximum(360.000000000000000);
        revolveAngle->setSingleStep(10.000000000000000);
        revolveAngle->setValue(360.000000000000000);

        gridLayout->addWidget(revolveAngle, 8, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        buttonFace = new QToolButton(PartDesignGui__TaskRevolutionParameters);
        buttonFace->setObjectName("buttonFace");
        buttonFace->setMinimumSize(QSize(0, 22));
        buttonFace->setCheckable(true);

        gridLayout_5->addWidget(buttonFace, 0, 0, 1, 1);

        lineFaceName = new QLineEdit(PartDesignGui__TaskRevolutionParameters);
        lineFaceName->setObjectName("lineFaceName");
        lineFaceName->setReadOnly(true);

        gridLayout_5->addWidget(lineFaceName, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_5, 9, 0, 1, 2);

        side2HeaderLayout = new QHBoxLayout();
        side2HeaderLayout->setObjectName("side2HeaderLayout");
        side2HeaderLayout->setContentsMargins(0, 0, 0, 0);
        side2Label = new QLabel(PartDesignGui__TaskRevolutionParameters);
        side2Label->setObjectName("side2Label");

        side2HeaderLayout->addWidget(side2Label);

        line2 = new QFrame(PartDesignGui__TaskRevolutionParameters);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::Shape::HLine);
        line2->setFrameShadow(QFrame::Shadow::Sunken);

        side2HeaderLayout->addWidget(line2);


        gridLayout->addLayout(side2HeaderLayout, 10, 0, 1, 2);

        typeLabel2 = new QLabel(PartDesignGui__TaskRevolutionParameters);
        typeLabel2->setObjectName("typeLabel2");

        gridLayout->addWidget(typeLabel2, 11, 0, 1, 1);

        changeMode2 = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        changeMode2->setObjectName("changeMode2");

        gridLayout->addWidget(changeMode2, 11, 1, 1, 1);

        labelAngle2 = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelAngle2->setObjectName("labelAngle2");

        gridLayout->addWidget(labelAngle2, 12, 0, 1, 1);

        revolveAngle2 = new Gui::QuantitySpinBox(PartDesignGui__TaskRevolutionParameters);
        revolveAngle2->setObjectName("revolveAngle2");
        revolveAngle2->setKeyboardTracking(false);
        revolveAngle2->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        revolveAngle2->setMinimum(-360.000000000000000);
        revolveAngle2->setMaximum(360.000000000000000);
        revolveAngle2->setSingleStep(10.000000000000000);
        revolveAngle2->setValue(0.000000000000000);

        gridLayout->addWidget(revolveAngle2, 12, 1, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        buttonFace2 = new QToolButton(PartDesignGui__TaskRevolutionParameters);
        buttonFace2->setObjectName("buttonFace2");
        buttonFace2->setMinimumSize(QSize(0, 22));
        buttonFace2->setCheckable(true);

        gridLayout_6->addWidget(buttonFace2, 0, 0, 1, 1);

        lineFaceName2 = new QLineEdit(PartDesignGui__TaskRevolutionParameters);
        lineFaceName2->setObjectName("lineFaceName2");
        lineFaceName2->setReadOnly(true);

        gridLayout_6->addWidget(lineFaceName2, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_6, 13, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        checkBoxMidplane = new QCheckBox(PartDesignGui__TaskRevolutionParameters);
        checkBoxMidplane->setObjectName("checkBoxMidplane");
        checkBoxMidplane->setEnabled(true);

        verticalLayout->addWidget(checkBoxMidplane);

        checkBoxProjectAxis = new QCheckBox(PartDesignGui__TaskRevolutionParameters);
        checkBoxProjectAxis->setObjectName("checkBoxProjectAxis");

        verticalLayout->addWidget(checkBoxProjectAxis);

        checkBoxReversed = new QCheckBox(PartDesignGui__TaskRevolutionParameters);
        checkBoxReversed->setObjectName("checkBoxReversed");

        verticalLayout->addWidget(checkBoxReversed);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__TaskRevolutionParameters);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__TaskRevolutionParameters);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);


        verticalLayout->addLayout(operationLayout);

        line = new QFrame(PartDesignGui__TaskRevolutionParameters);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        checkBoxUpdateView = new QCheckBox(PartDesignGui__TaskRevolutionParameters);
        checkBoxUpdateView->setObjectName("checkBoxUpdateView");
        checkBoxUpdateView->setChecked(true);

        verticalLayout->addWidget(checkBoxUpdateView);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(startMode, lineStartReference);
        QWidget::setTabOrder(lineStartReference, buttonStartReference);
        QWidget::setTabOrder(buttonStartReference, startOffsetEdit);
        QWidget::setTabOrder(startOffsetEdit, sidesMode);
        QWidget::setTabOrder(sidesMode, axis);
        QWidget::setTabOrder(axis, changeMode);
        QWidget::setTabOrder(changeMode, revolveAngle);
        QWidget::setTabOrder(revolveAngle, lineFaceName);
        QWidget::setTabOrder(lineFaceName, changeMode2);
        QWidget::setTabOrder(changeMode2, revolveAngle2);
        QWidget::setTabOrder(revolveAngle2, lineFaceName2);
        QWidget::setTabOrder(lineFaceName2, checkBoxProjectAxis);
        QWidget::setTabOrder(checkBoxProjectAxis, checkBoxReversed);
        QWidget::setTabOrder(checkBoxReversed, comboOperation);
        QWidget::setTabOrder(comboOperation, checkBoxUpdateView);

        retranslateUi(PartDesignGui__TaskRevolutionParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskRevolutionParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskRevolutionParameters)
    {
        labelStart->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Start", nullptr));
        startMode->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Profile plane", nullptr));
        startMode->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Offset", nullptr));
        startMode->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Reference", nullptr));

        labelStartReference->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Reference", nullptr));
        buttonStartReference->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Pick Reference", nullptr));
        labelStartOffset->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Offset", nullptr));
        sidesLabel->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Direction", nullptr));
        textLabel1->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Axis", nullptr));
        axis->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Base X-axis", nullptr));
        axis->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Base Y-axis", nullptr));
        axis->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Base Z-axis", nullptr));
        axis->setItemText(3, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Horizontal sketch axis", nullptr));
        axis->setItemText(4, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Vertical sketch axis", nullptr));
        axis->setItemText(5, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Select reference\342\200\246", nullptr));

        side1Label->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Side 1", nullptr));
        textLabelMode->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Type", nullptr));

        labelAngle->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Angle", nullptr));
        buttonFace->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Select Face", nullptr));
        side2Label->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Side 2", nullptr));
        typeLabel2->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Type", nullptr));
        labelAngle2->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Angle", nullptr));
        buttonFace2->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Select Face", nullptr));
        checkBoxMidplane->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Symmetric to plane", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxProjectAxis->setToolTip(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Projects the selected axis onto the profile plane if the profile is planar. When unchecked, uses the axis in its original position and direction.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxProjectAxis->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Project selected axis to profile plane", nullptr));
        checkBoxReversed->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Reversed", nullptr));
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Common", nullptr));

        checkBoxUpdateView->setText(QCoreApplication::translate("PartDesignGui::TaskRevolutionParameters", "Recompute on change", nullptr));
        (void)PartDesignGui__TaskRevolutionParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskRevolutionParameters: public Ui_TaskRevolutionParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKREVOLUTIONPARAMETERS_H
