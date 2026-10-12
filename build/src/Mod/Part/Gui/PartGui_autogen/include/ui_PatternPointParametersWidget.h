/********************************************************************************
** Form generated from reading UI file 'PatternPointParametersWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATTERNPOINTPARAMETERSWIDGET_H
#define UI_PATTERNPOINTPARAMETERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

namespace PartGui {

class Ui_PatternPointParametersWidget
{
public:
    QFormLayout *formLayout;
    QLabel *pointObjectLabel;
    QPushButton *pointObjectButton;

    void setupUi(QWidget *PartGui__PatternPointParametersWidget)
    {
        if (PartGui__PatternPointParametersWidget->objectName().isEmpty())
            PartGui__PatternPointParametersWidget->setObjectName("PartGui__PatternPointParametersWidget");
        formLayout = new QFormLayout(PartGui__PatternPointParametersWidget);
        formLayout->setObjectName("formLayout");
        pointObjectLabel = new QLabel(PartGui__PatternPointParametersWidget);
        pointObjectLabel->setObjectName("pointObjectLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, pointObjectLabel);

        pointObjectButton = new QPushButton(PartGui__PatternPointParametersWidget);
        pointObjectButton->setObjectName("pointObjectButton");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, pointObjectButton);

#if QT_CONFIG(shortcut)
        pointObjectLabel->setBuddy(pointObjectButton);
#endif // QT_CONFIG(shortcut)

        retranslateUi(PartGui__PatternPointParametersWidget);

        QMetaObject::connectSlotsByName(PartGui__PatternPointParametersWidget);
    } // setupUi

    void retranslateUi(QWidget *PartGui__PatternPointParametersWidget)
    {
        pointObjectLabel->setText(QCoreApplication::translate("PartGui::PatternPointParametersWidget", "Point object", nullptr));
        pointObjectButton->setText(QCoreApplication::translate("PartGui::PatternPointParametersWidget", "Select Point Object", nullptr));
        (void)PartGui__PatternPointParametersWidget;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class PatternPointParametersWidget: public Ui_PatternPointParametersWidget {};
} // namespace Ui
} // namespace PartGui

#endif // UI_PATTERNPOINTPARAMETERSWIDGET_H
