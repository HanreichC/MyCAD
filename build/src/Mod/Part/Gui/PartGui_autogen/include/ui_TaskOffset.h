/********************************************************************************
** Form generated from reading UI file 'TaskOffset.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKOFFSET_H
#define UI_TASKOFFSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace PartGui {

class Ui_TaskOffset
{
public:
    QGridLayout *gridLayout;
    QLabel *labelOffset;
    Gui::QuantitySpinBox *spinOffset;
    QLabel *label_2;
    QComboBox *modeType;
    QLabel *label_3;
    QComboBox *joinType;
    QCheckBox *intersection;
    QCheckBox *selfIntersection;
    QCheckBox *fillOffset;
    QLabel *labelFaces;
    QPushButton *facesButton;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QCheckBox *updateView;

    void setupUi(QWidget *PartGui__TaskOffset)
    {
        if (PartGui__TaskOffset->objectName().isEmpty())
            PartGui__TaskOffset->setObjectName("PartGui__TaskOffset");
        PartGui__TaskOffset->resize(264, 244);
        gridLayout = new QGridLayout(PartGui__TaskOffset);
        gridLayout->setObjectName("gridLayout");
        labelOffset = new QLabel(PartGui__TaskOffset);
        labelOffset->setObjectName("labelOffset");

        gridLayout->addWidget(labelOffset, 0, 0, 1, 1);

        spinOffset = new Gui::QuantitySpinBox(PartGui__TaskOffset);
        spinOffset->setObjectName("spinOffset");
        spinOffset->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(spinOffset, 0, 2, 1, 1);

        label_2 = new QLabel(PartGui__TaskOffset);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        modeType = new QComboBox(PartGui__TaskOffset);
        modeType->addItem(QString());
        modeType->addItem(QString());
        modeType->addItem(QString());
        modeType->setObjectName("modeType");

        gridLayout->addWidget(modeType, 1, 2, 1, 1);

        label_3 = new QLabel(PartGui__TaskOffset);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        joinType = new QComboBox(PartGui__TaskOffset);
        joinType->addItem(QString());
        joinType->addItem(QString());
        joinType->addItem(QString());
        joinType->setObjectName("joinType");

        gridLayout->addWidget(joinType, 2, 2, 1, 1);

        intersection = new QCheckBox(PartGui__TaskOffset);
        intersection->setObjectName("intersection");

        gridLayout->addWidget(intersection, 3, 0, 1, 1);

        selfIntersection = new QCheckBox(PartGui__TaskOffset);
        selfIntersection->setObjectName("selfIntersection");

        gridLayout->addWidget(selfIntersection, 4, 0, 1, 2);

        fillOffset = new QCheckBox(PartGui__TaskOffset);
        fillOffset->setObjectName("fillOffset");

        gridLayout->addWidget(fillOffset, 5, 0, 1, 1);

        labelFaces = new QLabel(PartGui__TaskOffset);
        labelFaces->setObjectName("labelFaces");
        labelFaces->setText(QString::fromUtf8(""));

        gridLayout->addWidget(labelFaces, 6, 0, 1, 3);

        facesButton = new QPushButton(PartGui__TaskOffset);
        facesButton->setObjectName("facesButton");
        facesButton->setCheckable(true);

        gridLayout->addWidget(facesButton, 7, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(152, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 7, 1, 1, 2);

        line = new QFrame(PartGui__TaskOffset);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line, 8, 0, 1, 3);

        updateView = new QCheckBox(PartGui__TaskOffset);
        updateView->setObjectName("updateView");
        updateView->setChecked(true);

        gridLayout->addWidget(updateView, 9, 0, 1, 1);

        QWidget::setTabOrder(spinOffset, modeType);
        QWidget::setTabOrder(modeType, joinType);
        QWidget::setTabOrder(joinType, intersection);
        QWidget::setTabOrder(intersection, selfIntersection);

        retranslateUi(PartGui__TaskOffset);

        QMetaObject::connectSlotsByName(PartGui__TaskOffset);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskOffset)
    {
        PartGui__TaskOffset->setWindowTitle(QCoreApplication::translate("PartGui::TaskOffset", "Offset", nullptr));
        labelOffset->setText(QCoreApplication::translate("PartGui::TaskOffset", "Offset", nullptr));
        label_2->setText(QCoreApplication::translate("PartGui::TaskOffset", "Mode", nullptr));
        modeType->setItemText(0, QCoreApplication::translate("PartGui::TaskOffset", "Skin", nullptr));
        modeType->setItemText(1, QCoreApplication::translate("PartGui::TaskOffset", "Pipe", nullptr));
        modeType->setItemText(2, QCoreApplication::translate("PartGui::TaskOffset", "Recto verso", nullptr));

        label_3->setText(QCoreApplication::translate("PartGui::TaskOffset", "Join type", nullptr));
        joinType->setItemText(0, QCoreApplication::translate("PartGui::TaskOffset", "Arc", nullptr));
        joinType->setItemText(1, QCoreApplication::translate("PartGui::TaskOffset", "Tangent", nullptr));
        joinType->setItemText(2, QCoreApplication::translate("PartGui::TaskOffset", "Intersection", nullptr));

        intersection->setText(QCoreApplication::translate("PartGui::TaskOffset", "Intersection", nullptr));
        selfIntersection->setText(QCoreApplication::translate("PartGui::TaskOffset", "Self-intersection", nullptr));
        fillOffset->setText(QCoreApplication::translate("PartGui::TaskOffset", "Fill offset", nullptr));
        facesButton->setText(QCoreApplication::translate("PartGui::TaskOffset", "Faces", nullptr));
        updateView->setText(QCoreApplication::translate("PartGui::TaskOffset", "Update view", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskOffset: public Ui_TaskOffset {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKOFFSET_H
