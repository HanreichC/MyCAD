/********************************************************************************
** Form generated from reading UI file 'PatternPathParametersWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATTERNPATHPARAMETERSWIDGET_H
#define UI_PATTERNPATHPARAMETERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartGui {

class Ui_PatternPathParametersWidget
{
public:
    QFormLayout *formLayout;
    QLabel *pathLabel;
    QPushButton *pathButton;
    QLabel *spacingModeLabel;
    QComboBox *spacingMode;
    QLabel *countLabel;
    Gui::UIntSpinBox *count;
    QLabel *spacingLabel;
    Gui::QuantitySpinBox *spacing;
    QLabel *startOffsetLabel;
    Gui::QuantitySpinBox *startOffset;
    QLabel *endOffsetLabel;
    Gui::QuantitySpinBox *endOffset;
    QCheckBox *reversePath;
    QCheckBox *align;

    void setupUi(QWidget *PartGui__PatternPathParametersWidget)
    {
        if (PartGui__PatternPathParametersWidget->objectName().isEmpty())
            PartGui__PatternPathParametersWidget->setObjectName("PartGui__PatternPathParametersWidget");
        formLayout = new QFormLayout(PartGui__PatternPathParametersWidget);
        formLayout->setObjectName("formLayout");
        pathLabel = new QLabel(PartGui__PatternPathParametersWidget);
        pathLabel->setObjectName("pathLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, pathLabel);

        pathButton = new QPushButton(PartGui__PatternPathParametersWidget);
        pathButton->setObjectName("pathButton");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, pathButton);

        spacingModeLabel = new QLabel(PartGui__PatternPathParametersWidget);
        spacingModeLabel->setObjectName("spacingModeLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, spacingModeLabel);

        spacingMode = new QComboBox(PartGui__PatternPathParametersWidget);
        spacingMode->setObjectName("spacingMode");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, spacingMode);

        countLabel = new QLabel(PartGui__PatternPathParametersWidget);
        countLabel->setObjectName("countLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, countLabel);

        count = new Gui::UIntSpinBox(PartGui__PatternPathParametersWidget);
        count->setObjectName("count");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, count);

        spacingLabel = new QLabel(PartGui__PatternPathParametersWidget);
        spacingLabel->setObjectName("spacingLabel");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, spacingLabel);

        spacing = new Gui::QuantitySpinBox(PartGui__PatternPathParametersWidget);
        spacing->setObjectName("spacing");
        spacing->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spacing);

        startOffsetLabel = new QLabel(PartGui__PatternPathParametersWidget);
        startOffsetLabel->setObjectName("startOffsetLabel");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, startOffsetLabel);

        startOffset = new Gui::QuantitySpinBox(PartGui__PatternPathParametersWidget);
        startOffset->setObjectName("startOffset");
        startOffset->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, startOffset);

        endOffsetLabel = new QLabel(PartGui__PatternPathParametersWidget);
        endOffsetLabel->setObjectName("endOffsetLabel");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, endOffsetLabel);

        endOffset = new Gui::QuantitySpinBox(PartGui__PatternPathParametersWidget);
        endOffset->setObjectName("endOffset");
        endOffset->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, endOffset);

        reversePath = new QCheckBox(PartGui__PatternPathParametersWidget);
        reversePath->setObjectName("reversePath");

        formLayout->setWidget(6, QFormLayout::ItemRole::SpanningRole, reversePath);

        align = new QCheckBox(PartGui__PatternPathParametersWidget);
        align->setObjectName("align");

        formLayout->setWidget(7, QFormLayout::ItemRole::SpanningRole, align);


        retranslateUi(PartGui__PatternPathParametersWidget);

        QMetaObject::connectSlotsByName(PartGui__PatternPathParametersWidget);
    } // setupUi

    void retranslateUi(QWidget *PartGui__PatternPathParametersWidget)
    {
        pathLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Path", nullptr));
        pathButton->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Select Path", nullptr));
        spacingModeLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Spacing mode", nullptr));
        countLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Occurrences", nullptr));
        spacingLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Spacing", nullptr));
        startOffsetLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Start offset", nullptr));
        endOffsetLabel->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "End offset", nullptr));
        reversePath->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Reverse path", nullptr));
        align->setText(QCoreApplication::translate("PartGui::PatternPathParametersWidget", "Align to path", nullptr));
        (void)PartGui__PatternPathParametersWidget;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class PatternPathParametersWidget: public Ui_PatternPathParametersWidget {};
} // namespace Ui
} // namespace PartGui

#endif // UI_PATTERNPATHPARAMETERSWIDGET_H
