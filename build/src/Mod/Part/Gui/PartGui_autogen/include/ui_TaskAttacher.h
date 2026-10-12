/********************************************************************************
** Form generated from reading UI file 'TaskAttacher.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKATTACHER_H
#define UI_TASKATTACHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_TaskAttacher
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *message;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonRef1;
    QLineEdit *lineRef1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *buttonRef2;
    QLineEdit *lineRef2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *buttonRef3;
    QLineEdit *lineRef3;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *buttonRef4;
    QLineEdit *lineRef4;
    QLabel *label;
    QListWidget *listOfModes;
    QGroupBox *groupBox_AttachmentOffset;
    QGridLayout *gridLayout;
    QLabel *labelOffsetX;
    Gui::PrefQuantitySpinBox *attachmentOffsetX;
    QLabel *labelOffsetY;
    Gui::PrefQuantitySpinBox *attachmentOffsetY;
    QLabel *labelOffsetZ;
    Gui::PrefQuantitySpinBox *attachmentOffsetZ;
    QLabel *labelRoll;
    Gui::QuantitySpinBox *attachmentOffsetRoll;
    QLabel *labelPitch;
    Gui::QuantitySpinBox *attachmentOffsetPitch;
    QLabel *labelYaw;
    Gui::QuantitySpinBox *attachmentOffsetYaw;
    QCheckBox *checkBoxFlip;

    void setupUi(QWidget *PartGui__TaskAttacher)
    {
        if (PartGui__TaskAttacher->objectName().isEmpty())
            PartGui__TaskAttacher->setObjectName("PartGui__TaskAttacher");
        PartGui__TaskAttacher->resize(271, 604);
        PartGui__TaskAttacher->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartGui__TaskAttacher);
        verticalLayout->setObjectName("verticalLayout");
        message = new QLabel(PartGui__TaskAttacher);
        message->setObjectName("message");
        message->setAlignment(Qt::AlignCenter);
        message->setWordWrap(true);

        verticalLayout->addWidget(message);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        buttonRef1 = new QPushButton(PartGui__TaskAttacher);
        buttonRef1->setObjectName("buttonRef1");
        buttonRef1->setCheckable(true);

        horizontalLayout_3->addWidget(buttonRef1);

        lineRef1 = new QLineEdit(PartGui__TaskAttacher);
        lineRef1->setObjectName("lineRef1");

        horizontalLayout_3->addWidget(lineRef1);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        buttonRef2 = new QPushButton(PartGui__TaskAttacher);
        buttonRef2->setObjectName("buttonRef2");
        buttonRef2->setCheckable(true);

        horizontalLayout_5->addWidget(buttonRef2);

        lineRef2 = new QLineEdit(PartGui__TaskAttacher);
        lineRef2->setObjectName("lineRef2");

        horizontalLayout_5->addWidget(lineRef2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        buttonRef3 = new QPushButton(PartGui__TaskAttacher);
        buttonRef3->setObjectName("buttonRef3");
        buttonRef3->setCheckable(true);

        horizontalLayout_6->addWidget(buttonRef3);

        lineRef3 = new QLineEdit(PartGui__TaskAttacher);
        lineRef3->setObjectName("lineRef3");

        horizontalLayout_6->addWidget(lineRef3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        buttonRef4 = new QPushButton(PartGui__TaskAttacher);
        buttonRef4->setObjectName("buttonRef4");
        buttonRef4->setCheckable(true);

        horizontalLayout_7->addWidget(buttonRef4);

        lineRef4 = new QLineEdit(PartGui__TaskAttacher);
        lineRef4->setObjectName("lineRef4");

        horizontalLayout_7->addWidget(lineRef4);


        verticalLayout->addLayout(horizontalLayout_7);

        label = new QLabel(PartGui__TaskAttacher);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        listOfModes = new QListWidget(PartGui__TaskAttacher);
        listOfModes->setObjectName("listOfModes");
        listOfModes->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(listOfModes);

        groupBox_AttachmentOffset = new QGroupBox(PartGui__TaskAttacher);
        groupBox_AttachmentOffset->setObjectName("groupBox_AttachmentOffset");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_AttachmentOffset->sizePolicy().hasHeightForWidth());
        groupBox_AttachmentOffset->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_AttachmentOffset);
        gridLayout->setObjectName("gridLayout");
        labelOffsetX = new QLabel(groupBox_AttachmentOffset);
        labelOffsetX->setObjectName("labelOffsetX");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelOffsetX->sizePolicy().hasHeightForWidth());
        labelOffsetX->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelOffsetX, 1, 0, 1, 1);

        attachmentOffsetX = new Gui::PrefQuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetX->setObjectName("attachmentOffsetX");
        sizePolicy.setHeightForWidth(attachmentOffsetX->sizePolicy().hasHeightForWidth());
        attachmentOffsetX->setSizePolicy(sizePolicy);
        attachmentOffsetX->setMinimumSize(QSize(0, 5));
        attachmentOffsetX->setKeyboardTracking(false);

        gridLayout->addWidget(attachmentOffsetX, 1, 1, 1, 1);

        labelOffsetY = new QLabel(groupBox_AttachmentOffset);
        labelOffsetY->setObjectName("labelOffsetY");
        sizePolicy1.setHeightForWidth(labelOffsetY->sizePolicy().hasHeightForWidth());
        labelOffsetY->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelOffsetY, 2, 0, 1, 1);

        attachmentOffsetY = new Gui::PrefQuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetY->setObjectName("attachmentOffsetY");
        sizePolicy.setHeightForWidth(attachmentOffsetY->sizePolicy().hasHeightForWidth());
        attachmentOffsetY->setSizePolicy(sizePolicy);
        attachmentOffsetY->setMinimumSize(QSize(0, 5));
        attachmentOffsetY->setKeyboardTracking(false);

        gridLayout->addWidget(attachmentOffsetY, 2, 1, 1, 1);

        labelOffsetZ = new QLabel(groupBox_AttachmentOffset);
        labelOffsetZ->setObjectName("labelOffsetZ");
        sizePolicy1.setHeightForWidth(labelOffsetZ->sizePolicy().hasHeightForWidth());
        labelOffsetZ->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelOffsetZ, 3, 0, 1, 1);

        attachmentOffsetZ = new Gui::PrefQuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetZ->setObjectName("attachmentOffsetZ");
        sizePolicy.setHeightForWidth(attachmentOffsetZ->sizePolicy().hasHeightForWidth());
        attachmentOffsetZ->setSizePolicy(sizePolicy);
        attachmentOffsetZ->setMinimumSize(QSize(0, 5));
        attachmentOffsetZ->setKeyboardTracking(false);

        gridLayout->addWidget(attachmentOffsetZ, 3, 1, 1, 1);

        labelRoll = new QLabel(groupBox_AttachmentOffset);
        labelRoll->setObjectName("labelRoll");
        sizePolicy1.setHeightForWidth(labelRoll->sizePolicy().hasHeightForWidth());
        labelRoll->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelRoll, 4, 0, 1, 1);

        attachmentOffsetRoll = new Gui::QuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetRoll->setObjectName("attachmentOffsetRoll");
        sizePolicy.setHeightForWidth(attachmentOffsetRoll->sizePolicy().hasHeightForWidth());
        attachmentOffsetRoll->setSizePolicy(sizePolicy);
        attachmentOffsetRoll->setKeyboardTracking(false);
        attachmentOffsetRoll->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        attachmentOffsetRoll->setMinimum(-360.000000000000000);
        attachmentOffsetRoll->setMaximum(360.000000000000000);

        gridLayout->addWidget(attachmentOffsetRoll, 4, 1, 1, 1);

        labelPitch = new QLabel(groupBox_AttachmentOffset);
        labelPitch->setObjectName("labelPitch");
        sizePolicy1.setHeightForWidth(labelPitch->sizePolicy().hasHeightForWidth());
        labelPitch->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelPitch, 5, 0, 1, 1);

        attachmentOffsetPitch = new Gui::QuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetPitch->setObjectName("attachmentOffsetPitch");
        sizePolicy.setHeightForWidth(attachmentOffsetPitch->sizePolicy().hasHeightForWidth());
        attachmentOffsetPitch->setSizePolicy(sizePolicy);
        attachmentOffsetPitch->setKeyboardTracking(false);
        attachmentOffsetPitch->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        attachmentOffsetPitch->setMinimum(-360.000000000000000);
        attachmentOffsetPitch->setMaximum(360.000000000000000);

        gridLayout->addWidget(attachmentOffsetPitch, 5, 1, 1, 1);

        labelYaw = new QLabel(groupBox_AttachmentOffset);
        labelYaw->setObjectName("labelYaw");
        sizePolicy1.setHeightForWidth(labelYaw->sizePolicy().hasHeightForWidth());
        labelYaw->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelYaw, 6, 0, 1, 1);

        attachmentOffsetYaw = new Gui::QuantitySpinBox(groupBox_AttachmentOffset);
        attachmentOffsetYaw->setObjectName("attachmentOffsetYaw");
        sizePolicy.setHeightForWidth(attachmentOffsetYaw->sizePolicy().hasHeightForWidth());
        attachmentOffsetYaw->setSizePolicy(sizePolicy);
        attachmentOffsetYaw->setKeyboardTracking(false);
        attachmentOffsetYaw->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        attachmentOffsetYaw->setMinimum(-360.000000000000000);
        attachmentOffsetYaw->setMaximum(360.000000000000000);

        gridLayout->addWidget(attachmentOffsetYaw, 6, 1, 1, 1);


        verticalLayout->addWidget(groupBox_AttachmentOffset);

        checkBoxFlip = new QCheckBox(PartGui__TaskAttacher);
        checkBoxFlip->setObjectName("checkBoxFlip");

        verticalLayout->addWidget(checkBoxFlip);

        QWidget::setTabOrder(buttonRef1, lineRef1);
        QWidget::setTabOrder(lineRef1, buttonRef2);
        QWidget::setTabOrder(buttonRef2, lineRef2);
        QWidget::setTabOrder(lineRef2, buttonRef3);
        QWidget::setTabOrder(buttonRef3, lineRef3);
        QWidget::setTabOrder(lineRef3, buttonRef4);
        QWidget::setTabOrder(buttonRef4, lineRef4);
        QWidget::setTabOrder(lineRef4, listOfModes);
        QWidget::setTabOrder(listOfModes, attachmentOffsetX);
        QWidget::setTabOrder(attachmentOffsetX, attachmentOffsetY);
        QWidget::setTabOrder(attachmentOffsetY, attachmentOffsetZ);
        QWidget::setTabOrder(attachmentOffsetZ, attachmentOffsetRoll);
        QWidget::setTabOrder(attachmentOffsetRoll, attachmentOffsetPitch);
        QWidget::setTabOrder(attachmentOffsetPitch, attachmentOffsetYaw);
        QWidget::setTabOrder(attachmentOffsetYaw, checkBoxFlip);

        retranslateUi(PartGui__TaskAttacher);

        QMetaObject::connectSlotsByName(PartGui__TaskAttacher);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskAttacher)
    {
        message->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Selection accepted", nullptr));
        buttonRef1->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Reference 1", nullptr));
        buttonRef2->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Reference 2", nullptr));
        buttonRef3->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Reference 3", nullptr));
        buttonRef4->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Reference 4", nullptr));
        label->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Attachment Mode", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_AttachmentOffset->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        groupBox_AttachmentOffset->setTitle(QCoreApplication::translate("PartGui::TaskAttacher", "Attachment Offset in its Local Coordinate System", nullptr));
        labelOffsetX->setText(QCoreApplication::translate("PartGui::TaskAttacher", "In X-direction", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetX->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "The offset is expressed in the local coordinate system\n"
"of the object being attached", nullptr));
#endif // QT_CONFIG(tooltip)
        labelOffsetY->setText(QCoreApplication::translate("PartGui::TaskAttacher", "In Y-direction", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetY->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "The offset is expressed in the local coordinate system\n"
"of the object being attached", nullptr));
#endif // QT_CONFIG(tooltip)
        labelOffsetZ->setText(QCoreApplication::translate("PartGui::TaskAttacher", "In Z-direction", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetZ->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "The offset is expressed in the local coordinate system\n"
"of the object being attached", nullptr));
#endif // QT_CONFIG(tooltip)
        labelRoll->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Around X-axis", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetRoll->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "Rotation around the local X-axis. The offset is expressed in the local coordinate system\n"
"of the object being attached.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelPitch->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Around Y-axis", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetPitch->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "Rotation around the local Y-axis. The offset is expressed in the local coordinate system\n"
"of the object being attached.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelYaw->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Around Z-axis", nullptr));
#if QT_CONFIG(tooltip)
        attachmentOffsetYaw->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "Rotation around the local Z-axis. The offset is expressed in the local coordinate system\n"
"of the object being attached.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBoxFlip->setToolTip(QCoreApplication::translate("PartGui::TaskAttacher", "Flip side of attachment and offset", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxFlip->setText(QCoreApplication::translate("PartGui::TaskAttacher", "Flip sides", nullptr));
        (void)PartGui__TaskAttacher;
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskAttacher: public Ui_TaskAttacher {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKATTACHER_H
