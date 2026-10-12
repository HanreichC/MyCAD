/********************************************************************************
** Form generated from reading UI file 'DlgExpressionInput.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEXPRESSIONINPUT_H
#define UI_DLGEXPRESSIONINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "ExpressionCompleter.h"

QT_BEGIN_NAMESPACE

class Ui_DlgExpressionInput
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    Gui::ExpressionTextEdit *expression;
    QFrame *ctrlArea;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *msg;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxVarSets;
    QGroupBox *groupBoxVarSets;
    QVBoxLayout *verticalLayout_3;
    QFrame *errorFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *errorIconLabel;
    QLabel *errorTextLabel;
    QFormLayout *formLayout;
    QLabel *labelVarSet;
    QComboBox *comboBoxVarSet;
    QLabel *labelGroup;
    QLabel *LabelPropNew;
    QLineEdit *lineEditPropNew;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgExpressionInput)
    {
        if (DlgExpressionInput->objectName().isEmpty())
            DlgExpressionInput->setObjectName("DlgExpressionInput");
        DlgExpressionInput->resize(414, 298);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DlgExpressionInput->sizePolicy().hasHeightForWidth());
        DlgExpressionInput->setSizePolicy(sizePolicy);
        DlgExpressionInput->setMinimumSize(QSize(350, 0));
        verticalLayout = new QVBoxLayout(DlgExpressionInput);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
#ifndef Q_OS_MACOS
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
#endif
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        expression = new Gui::ExpressionTextEdit(DlgExpressionInput);
        expression->setObjectName("expression");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(expression->sizePolicy().hasHeightForWidth());
        expression->setSizePolicy(sizePolicy1);
        expression->setMinimumSize(QSize(10, 10));

        horizontalLayout_5->addWidget(expression);


        verticalLayout_2->addLayout(horizontalLayout_5);

        ctrlArea = new QFrame(DlgExpressionInput);
        ctrlArea->setObjectName("ctrlArea");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ctrlArea->sizePolicy().hasHeightForWidth());
        ctrlArea->setSizePolicy(sizePolicy2);
        ctrlArea->setAutoFillBackground(true);
        ctrlArea->setFrameShape(QFrame::Shape::StyledPanel);
        ctrlArea->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_4 = new QHBoxLayout(ctrlArea);
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(ctrlArea);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(label);

        msg = new QLabel(ctrlArea);
        msg->setObjectName("msg");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(msg->sizePolicy().hasHeightForWidth());
        msg->setSizePolicy(sizePolicy4);
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        QBrush brush1(QColor(190, 190, 190, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush1);
        msg->setPalette(palette);

        horizontalLayout_4->addWidget(msg);


        verticalLayout_2->addWidget(ctrlArea);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(0, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        checkBoxVarSets = new QCheckBox(DlgExpressionInput);
        checkBoxVarSets->setObjectName("checkBoxVarSets");

        horizontalLayout_3->addWidget(checkBoxVarSets);


        verticalLayout->addLayout(horizontalLayout_3);

        groupBoxVarSets = new QGroupBox(DlgExpressionInput);
        groupBoxVarSets->setObjectName("groupBoxVarSets");
        verticalLayout_3 = new QVBoxLayout(groupBoxVarSets);
        verticalLayout_3->setObjectName("verticalLayout_3");
        errorFrame = new QFrame(groupBoxVarSets);
        errorFrame->setObjectName("errorFrame");
        errorFrame->setEnabled(true);
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(errorFrame->sizePolicy().hasHeightForWidth());
        errorFrame->setSizePolicy(sizePolicy5);
        errorFrame->setMinimumSize(QSize(0, 0));
        errorFrame->setStyleSheet(QString::fromUtf8("#errorFrame { border: 1px solid red; border-radius: 5px; background-color: #f8d7da; color: #721c24; } #errorTextLabel { color: #721c24; }"));
        errorFrame->setFrameShape(QFrame::Shape::StyledPanel);
        errorFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(errorFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        errorIconLabel = new QLabel(errorFrame);
        errorIconLabel->setObjectName("errorIconLabel");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(errorIconLabel->sizePolicy().hasHeightForWidth());
        errorIconLabel->setSizePolicy(sizePolicy6);

        horizontalLayout->addWidget(errorIconLabel);

        errorTextLabel = new QLabel(errorFrame);
        errorTextLabel->setObjectName("errorTextLabel");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(errorTextLabel->sizePolicy().hasHeightForWidth());
        errorTextLabel->setSizePolicy(sizePolicy7);
        errorTextLabel->setTextFormat(Qt::TextFormat::PlainText);
        errorTextLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        errorTextLabel->setWordWrap(true);
        errorTextLabel->setMargin(0);

        horizontalLayout->addWidget(errorTextLabel);


        verticalLayout_3->addWidget(errorFrame);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelVarSet = new QLabel(groupBoxVarSets);
        labelVarSet->setObjectName("labelVarSet");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelVarSet);

        comboBoxVarSet = new QComboBox(groupBoxVarSets);
        comboBoxVarSet->setObjectName("comboBoxVarSet");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, comboBoxVarSet);

        labelGroup = new QLabel(groupBoxVarSets);
        labelGroup->setObjectName("labelGroup");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelGroup);

        LabelPropNew = new QLabel(groupBoxVarSets);
        LabelPropNew->setObjectName("LabelPropNew");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, LabelPropNew);

        lineEditPropNew = new QLineEdit(groupBoxVarSets);
        lineEditPropNew->setObjectName("lineEditPropNew");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(lineEditPropNew->sizePolicy().hasHeightForWidth());
        lineEditPropNew->setSizePolicy(sizePolicy8);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEditPropNew);


        verticalLayout_3->addLayout(formLayout);


        verticalLayout->addWidget(groupBoxVarSets);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(DlgExpressionInput);
        buttonBox->setObjectName("buttonBox");
        QSizePolicy sizePolicy9(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy9);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Ok|QDialogButtonBox::StandardButton::Reset);

        horizontalLayout_6->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(DlgExpressionInput);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DlgExpressionInput, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(DlgExpressionInput);
    } // setupUi

    void retranslateUi(QDialog *DlgExpressionInput)
    {
        DlgExpressionInput->setWindowTitle(QCoreApplication::translate("DlgExpressionInput", "Expression Editor", nullptr));
        label->setText(QCoreApplication::translate("DlgExpressionInput", "Result", nullptr));
        msg->setText(QString());
#if QT_CONFIG(tooltip)
        checkBoxVarSets->setToolTip(QCoreApplication::translate("DlgExpressionInput", "Store the expression in a newly created property in the selected Variable Set.\n"
"The property of this object will refer to the property of the Variable Set.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxVarSets->setText(QCoreApplication::translate("DlgExpressionInput", "Store in Variable Set\342\200\246", nullptr));
        groupBoxVarSets->setTitle(QString());
        errorIconLabel->setText(QString());
        errorTextLabel->setText(QCoreApplication::translate("DlgExpressionInput", "Error", nullptr));
        labelVarSet->setText(QCoreApplication::translate("DlgExpressionInput", "Variable Set", nullptr));
        labelGroup->setText(QCoreApplication::translate("DlgExpressionInput", "Group", nullptr));
        LabelPropNew->setText(QCoreApplication::translate("DlgExpressionInput", "Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgExpressionInput: public Ui_DlgExpressionInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGEXPRESSIONINPUT_H
