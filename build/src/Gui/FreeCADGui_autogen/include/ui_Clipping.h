/********************************************************************************
** Form generated from reading UI file 'Clipping.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIPPING_H
#define UI_CLIPPING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

namespace Gui {
namespace Dialog {

class Ui_Clipping
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBoxX;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *clipX;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *flipClipX;
    QGroupBox *groupBoxY;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *clipY;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *flipClipY;
    QGroupBox *groupBoxZ;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *clipZ;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *flipClipZ;
    QGroupBox *groupBoxView;
    QGridLayout *gridLayout_6;
    QLabel *label_4;
    QDoubleSpinBox *clipView;
    QSpacerItem *horizontalSpacer;
    QPushButton *fromView;
    QCheckBox *adjustViewdirection;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QDoubleSpinBox *dirX;
    QDoubleSpinBox *dirY;
    QDoubleSpinBox *dirZ;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Gui__Dialog__Clipping)
    {
        if (Gui__Dialog__Clipping->objectName().isEmpty())
            Gui__Dialog__Clipping->setObjectName("Gui__Dialog__Clipping");
        Gui__Dialog__Clipping->resize(304, 430);
        gridLayout_5 = new QGridLayout(Gui__Dialog__Clipping);
        gridLayout_5->setObjectName("gridLayout_5");
        groupBoxX = new QGroupBox(Gui__Dialog__Clipping);
        groupBoxX->setObjectName("groupBoxX");
        groupBoxX->setCheckable(true);
        groupBoxX->setChecked(false);
        gridLayout = new QGridLayout(groupBoxX);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(groupBoxX);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        clipX = new QDoubleSpinBox(groupBoxX);
        clipX->setObjectName("clipX");

        gridLayout->addWidget(clipX, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        flipClipX = new QPushButton(groupBoxX);
        flipClipX->setObjectName("flipClipX");

        gridLayout->addWidget(flipClipX, 0, 3, 1, 1);


        gridLayout_5->addWidget(groupBoxX, 0, 0, 1, 1);

        groupBoxY = new QGroupBox(Gui__Dialog__Clipping);
        groupBoxY->setObjectName("groupBoxY");
        groupBoxY->setCheckable(true);
        groupBoxY->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxY);
        gridLayout_2->setObjectName("gridLayout_2");
        label_2 = new QLabel(groupBoxY);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        clipY = new QDoubleSpinBox(groupBoxY);
        clipY->setObjectName("clipY");

        gridLayout_2->addWidget(clipY, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        flipClipY = new QPushButton(groupBoxY);
        flipClipY->setObjectName("flipClipY");

        gridLayout_2->addWidget(flipClipY, 0, 3, 1, 1);


        gridLayout_5->addWidget(groupBoxY, 1, 0, 1, 1);

        groupBoxZ = new QGroupBox(Gui__Dialog__Clipping);
        groupBoxZ->setObjectName("groupBoxZ");
        groupBoxZ->setCheckable(true);
        groupBoxZ->setChecked(false);
        gridLayout_3 = new QGridLayout(groupBoxZ);
        gridLayout_3->setObjectName("gridLayout_3");
        label_3 = new QLabel(groupBoxZ);
        label_3->setObjectName("label_3");

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        clipZ = new QDoubleSpinBox(groupBoxZ);
        clipZ->setObjectName("clipZ");

        gridLayout_3->addWidget(clipZ, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        flipClipZ = new QPushButton(groupBoxZ);
        flipClipZ->setObjectName("flipClipZ");

        gridLayout_3->addWidget(flipClipZ, 0, 3, 1, 1);


        gridLayout_5->addWidget(groupBoxZ, 2, 0, 1, 1);

        groupBoxView = new QGroupBox(Gui__Dialog__Clipping);
        groupBoxView->setObjectName("groupBoxView");
        groupBoxView->setCheckable(true);
        groupBoxView->setChecked(false);
        gridLayout_6 = new QGridLayout(groupBoxView);
        gridLayout_6->setObjectName("gridLayout_6");
        label_4 = new QLabel(groupBoxView);
        label_4->setObjectName("label_4");

        gridLayout_6->addWidget(label_4, 0, 1, 1, 1);

        clipView = new QDoubleSpinBox(groupBoxView);
        clipView->setObjectName("clipView");

        gridLayout_6->addWidget(clipView, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(84, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 0, 3, 1, 1);

        fromView = new QPushButton(groupBoxView);
        fromView->setObjectName("fromView");

        gridLayout_6->addWidget(fromView, 0, 4, 1, 1);

        adjustViewdirection = new QCheckBox(groupBoxView);
        adjustViewdirection->setObjectName("adjustViewdirection");

        gridLayout_6->addWidget(adjustViewdirection, 1, 0, 1, 5);

        groupBox = new QGroupBox(groupBoxView);
        groupBox->setObjectName("groupBox");
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        dirX = new QDoubleSpinBox(groupBox);
        dirX->setObjectName("dirX");

        gridLayout_4->addWidget(dirX, 0, 0, 1, 1);

        dirY = new QDoubleSpinBox(groupBox);
        dirY->setObjectName("dirY");

        gridLayout_4->addWidget(dirY, 0, 1, 1, 1);

        dirZ = new QDoubleSpinBox(groupBox);
        dirZ->setObjectName("dirZ");

        gridLayout_4->addWidget(dirZ, 0, 2, 1, 1);


        gridLayout_6->addWidget(groupBox, 2, 0, 1, 5);


        gridLayout_5->addWidget(groupBoxView, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Gui__Dialog__Clipping);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_5->addWidget(buttonBox, 4, 0, 1, 1);

        QWidget::setTabOrder(groupBoxX, clipX);
        QWidget::setTabOrder(clipX, flipClipX);
        QWidget::setTabOrder(flipClipX, groupBoxY);
        QWidget::setTabOrder(groupBoxY, clipY);
        QWidget::setTabOrder(clipY, flipClipY);
        QWidget::setTabOrder(flipClipY, groupBoxZ);
        QWidget::setTabOrder(groupBoxZ, clipZ);
        QWidget::setTabOrder(clipZ, flipClipZ);
        QWidget::setTabOrder(flipClipZ, groupBoxView);
        QWidget::setTabOrder(groupBoxView, clipView);
        QWidget::setTabOrder(clipView, fromView);
        QWidget::setTabOrder(fromView, adjustViewdirection);
        QWidget::setTabOrder(adjustViewdirection, dirX);
        QWidget::setTabOrder(dirX, dirY);
        QWidget::setTabOrder(dirY, dirZ);

        retranslateUi(Gui__Dialog__Clipping);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Gui__Dialog__Clipping, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Gui__Dialog__Clipping);
    } // setupUi

    void retranslateUi(QDialog *Gui__Dialog__Clipping)
    {
        Gui__Dialog__Clipping->setWindowTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Clipping", nullptr));
        groupBoxX->setTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Clipping X", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Offset", nullptr));
        flipClipX->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Flip", nullptr));
        groupBoxY->setTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Clipping Y", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Offset", nullptr));
        flipClipY->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Flip", nullptr));
        groupBoxZ->setTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Clipping Z", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Offset", nullptr));
        flipClipZ->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Flip", nullptr));
        groupBoxView->setTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Custom Clipping Direction", nullptr));
        label_4->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Offset", nullptr));
        fromView->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "View", nullptr));
        adjustViewdirection->setText(QCoreApplication::translate("Gui::Dialog::Clipping", "Adjust to view direction", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::Dialog::Clipping", "Direction", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class Clipping: public Ui_Clipping {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_CLIPPING_H
