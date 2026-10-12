/********************************************************************************
** Form generated from reading UI file 'PatternParametersWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATTERNPARAMETERSWIDGET_H
#define UI_PATTERNPARAMETERSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartGui {

class Ui_PatternParametersWidget
{
public:
    QVBoxLayout *generalLayout;
    QCheckBox *enableCheckbox;
    QGroupBox *groupBox;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *PushButtonReverse;
    QComboBox *comboDirection;
    QFormLayout *formLayout;
    QLabel *labelMode;
    QComboBox *comboMode;
    QLabel *labelLength;
    Gui::QuantitySpinBox *spinExtent;
    QLabel *labelOffset;
    QWidget *spacingControlsWidget;
    QHBoxLayout *spacingControlsLayout;
    Gui::QuantitySpinBox *spinSpacing;
    QToolButton *addSpacingButton;
    QLabel *labelOccurrences;
    Gui::UIntSpinBox *spinOccurrences;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PartGui__PatternParametersWidget)
    {
        if (PartGui__PatternParametersWidget->objectName().isEmpty())
            PartGui__PatternParametersWidget->setObjectName("PartGui__PatternParametersWidget");
        PartGui__PatternParametersWidget->resize(270, 200);
        generalLayout = new QVBoxLayout(PartGui__PatternParametersWidget);
        generalLayout->setObjectName("generalLayout");
        generalLayout->setContentsMargins(0, 0, 0, 0);
        enableCheckbox = new QCheckBox(PartGui__PatternParametersWidget);
        enableCheckbox->setObjectName("enableCheckbox");

        generalLayout->addWidget(enableCheckbox);

        groupBox = new QGroupBox(PartGui__PatternParametersWidget);
        groupBox->setObjectName("groupBox");
        mainLayout = new QVBoxLayout(groupBox);
        mainLayout->setObjectName("mainLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        PushButtonReverse = new QToolButton(groupBox);
        PushButtonReverse->setObjectName("PushButtonReverse");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PushButtonReverse->sizePolicy().hasHeightForWidth());
        PushButtonReverse->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/button_sort.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PushButtonReverse->setIcon(icon);

        horizontalLayout_3->addWidget(PushButtonReverse);

        comboDirection = new QComboBox(groupBox);
        comboDirection->setObjectName("comboDirection");

        horizontalLayout_3->addWidget(comboDirection);


        mainLayout->addLayout(horizontalLayout_3);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelMode = new QLabel(groupBox);
        labelMode->setObjectName("labelMode");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelMode);

        comboMode = new QComboBox(groupBox);
        comboMode->addItem(QString());
        comboMode->addItem(QString());
        comboMode->setObjectName("comboMode");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, comboMode);

        labelLength = new QLabel(groupBox);
        labelLength->setObjectName("labelLength");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelLength);

        spinExtent = new Gui::QuantitySpinBox(groupBox);
        spinExtent->setObjectName("spinExtent");
        spinExtent->setProperty("keyboardTracking", QVariant(false));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, spinExtent);

        labelOffset = new QLabel(groupBox);
        labelOffset->setObjectName("labelOffset");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelOffset);

        spacingControlsWidget = new QWidget(groupBox);
        spacingControlsWidget->setObjectName("spacingControlsWidget");
        spacingControlsLayout = new QHBoxLayout(spacingControlsWidget);
        spacingControlsLayout->setSpacing(3);
        spacingControlsLayout->setObjectName("spacingControlsLayout");
        spacingControlsLayout->setContentsMargins(0, 0, 0, 0);
        spinSpacing = new Gui::QuantitySpinBox(spacingControlsWidget);
        spinSpacing->setObjectName("spinSpacing");
        spinSpacing->setProperty("keyboardTracking", QVariant(false));

        spacingControlsLayout->addWidget(spinSpacing);

        addSpacingButton = new QToolButton(spacingControlsWidget);
        addSpacingButton->setObjectName("addSpacingButton");
        sizePolicy.setHeightForWidth(addSpacingButton->sizePolicy().hasHeightForWidth());
        addSpacingButton->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/list-add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        addSpacingButton->setIcon(icon1);

        spacingControlsLayout->addWidget(addSpacingButton);


        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spacingControlsWidget);

        labelOccurrences = new QLabel(groupBox);
        labelOccurrences->setObjectName("labelOccurrences");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelOccurrences);

        spinOccurrences = new Gui::UIntSpinBox(groupBox);
        spinOccurrences->setObjectName("spinOccurrences");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spinOccurrences);


        mainLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(verticalSpacer);


        generalLayout->addWidget(groupBox);


        retranslateUi(PartGui__PatternParametersWidget);

        QMetaObject::connectSlotsByName(PartGui__PatternParametersWidget);
    } // setupUi

    void retranslateUi(QWidget *PartGui__PatternParametersWidget)
    {
        enableCheckbox->setText(QCoreApplication::translate("PartGui::PatternParametersWidget", "Direction 2", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::PatternParametersWidget", "Direction", nullptr));
#if QT_CONFIG(tooltip)
        PushButtonReverse->setToolTip(QCoreApplication::translate("PartGui::PatternParametersWidget", "Reverse the direction of the pattern.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelMode->setText(QCoreApplication::translate("PartGui::PatternParametersWidget", "Mode", nullptr));
        comboMode->setItemText(0, QCoreApplication::translate("PartGui::PatternParametersWidget", "Extent", nullptr));
        comboMode->setItemText(1, QCoreApplication::translate("PartGui::PatternParametersWidget", "Spacing", nullptr));

        labelLength->setText(QCoreApplication::translate("PartGui::PatternParametersWidget", "Length", nullptr));
        labelOffset->setText(QCoreApplication::translate("PartGui::PatternParametersWidget", "Spacing", nullptr));
#if QT_CONFIG(tooltip)
        addSpacingButton->setToolTip(QCoreApplication::translate("PartGui::PatternParametersWidget", "Add spacing to create spacing patterns.", nullptr));
#endif // QT_CONFIG(tooltip)
        addSpacingButton->setText(QString());
        labelOccurrences->setText(QCoreApplication::translate("PartGui::PatternParametersWidget", "Occurrences", nullptr));
        (void)PartGui__PatternParametersWidget;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class PatternParametersWidget: public Ui_PatternParametersWidget {};
} // namespace Ui
} // namespace PartGui

#endif // UI_PATTERNPARAMETERSWIDGET_H
