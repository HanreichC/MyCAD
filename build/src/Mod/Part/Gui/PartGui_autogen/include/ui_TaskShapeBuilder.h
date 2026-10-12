/********************************************************************************
** Form generated from reading UI file 'TaskShapeBuilder.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSHAPEBUILDER_H
#define UI_TASKSHAPEBUILDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

namespace PartGui {

class Ui_TaskShapeBuilder
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonEdgeFromVertex;
    QRadioButton *radioButtonWireFromEdge;
    QRadioButton *radioButtonFaceFromVertex;
    QRadioButton *radioButtonFaceFromEdge;
    QRadioButton *radioButtonShellFromFace;
    QRadioButton *radioButtonSolidFromShell;
    QFrame *line;
    QCheckBox *checkPlanar;
    QCheckBox *checkRefine;
    QCheckBox *checkFaces;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *createButton;
    QSpacerItem *verticalSpacer;
    QLabel *label;

    void setupUi(QWidget *PartGui__TaskShapeBuilder)
    {
        if (PartGui__TaskShapeBuilder->objectName().isEmpty())
            PartGui__TaskShapeBuilder->setObjectName("PartGui__TaskShapeBuilder");
        PartGui__TaskShapeBuilder->resize(200, 336);
        gridLayout_2 = new QGridLayout(PartGui__TaskShapeBuilder);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(PartGui__TaskShapeBuilder);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        radioButtonEdgeFromVertex = new QRadioButton(groupBox);
        radioButtonEdgeFromVertex->setObjectName("radioButtonEdgeFromVertex");

        gridLayout->addWidget(radioButtonEdgeFromVertex, 0, 0, 1, 1);

        radioButtonWireFromEdge = new QRadioButton(groupBox);
        radioButtonWireFromEdge->setObjectName("radioButtonWireFromEdge");

        gridLayout->addWidget(radioButtonWireFromEdge, 1, 0, 1, 1);

        radioButtonFaceFromVertex = new QRadioButton(groupBox);
        radioButtonFaceFromVertex->setObjectName("radioButtonFaceFromVertex");

        gridLayout->addWidget(radioButtonFaceFromVertex, 2, 0, 1, 1);

        radioButtonFaceFromEdge = new QRadioButton(groupBox);
        radioButtonFaceFromEdge->setObjectName("radioButtonFaceFromEdge");

        gridLayout->addWidget(radioButtonFaceFromEdge, 3, 0, 1, 1);

        radioButtonShellFromFace = new QRadioButton(groupBox);
        radioButtonShellFromFace->setObjectName("radioButtonShellFromFace");

        gridLayout->addWidget(radioButtonShellFromFace, 4, 0, 1, 1);

        radioButtonSolidFromShell = new QRadioButton(groupBox);
        radioButtonSolidFromShell->setObjectName("radioButtonSolidFromShell");

        gridLayout->addWidget(radioButtonSolidFromShell, 5, 0, 1, 1);

        line = new QFrame(groupBox);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line, 6, 0, 1, 1);

        checkPlanar = new QCheckBox(groupBox);
        checkPlanar->setObjectName("checkPlanar");

        gridLayout->addWidget(checkPlanar, 7, 0, 1, 1);

        checkRefine = new QCheckBox(groupBox);
        checkRefine->setObjectName("checkRefine");
        checkRefine->setChecked(true);

        gridLayout->addWidget(checkRefine, 8, 0, 1, 1);

        checkFaces = new QCheckBox(groupBox);
        checkFaces->setObjectName("checkFaces");

        gridLayout->addWidget(checkFaces, 9, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        selectButton = new QPushButton(groupBox);
        selectButton->setObjectName("selectButton");

        horizontalLayout->addWidget(selectButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        createButton = new QPushButton(groupBox);
        createButton->setObjectName("createButton");

        horizontalLayout->addWidget(createButton);


        gridLayout->addLayout(horizontalLayout, 10, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);

        label = new QLabel(PartGui__TaskShapeBuilder);
        label->setObjectName("label");
        label->setText(QString::fromUtf8("TextLabel"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        QWidget::setTabOrder(radioButtonEdgeFromVertex, radioButtonFaceFromVertex);
        QWidget::setTabOrder(radioButtonFaceFromVertex, radioButtonFaceFromEdge);
        QWidget::setTabOrder(radioButtonFaceFromEdge, radioButtonShellFromFace);
        QWidget::setTabOrder(radioButtonShellFromFace, radioButtonSolidFromShell);
        QWidget::setTabOrder(radioButtonSolidFromShell, checkPlanar);
        QWidget::setTabOrder(checkPlanar, checkRefine);
        QWidget::setTabOrder(checkRefine, checkFaces);
        QWidget::setTabOrder(checkFaces, createButton);

        retranslateUi(PartGui__TaskShapeBuilder);

        QMetaObject::connectSlotsByName(PartGui__TaskShapeBuilder);
    } // setupUi

    void retranslateUi(QWidget *PartGui__TaskShapeBuilder)
    {
        PartGui__TaskShapeBuilder->setWindowTitle(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Create Shape", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Create Shape", nullptr));
        radioButtonEdgeFromVertex->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Edge from vertices", nullptr));
        radioButtonWireFromEdge->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Wire from edges", nullptr));
        radioButtonFaceFromVertex->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Face from vertices", nullptr));
        radioButtonFaceFromEdge->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Face from edges", nullptr));
        radioButtonShellFromFace->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Shell from faces", nullptr));
        radioButtonSolidFromShell->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Solid from shell", nullptr));
        checkPlanar->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Planar", nullptr));
        checkRefine->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Refine shape", nullptr));
        checkFaces->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "All faces", nullptr));
        selectButton->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Box Selection", nullptr));
        createButton->setText(QCoreApplication::translate("PartGui::TaskShapeBuilder", "Create", nullptr));
    } // retranslateUi

};

} // namespace PartGui

namespace PartGui {
namespace Ui {
    class TaskShapeBuilder: public Ui_TaskShapeBuilder {};
} // namespace Ui
} // namespace PartGui

#endif // UI_TASKSHAPEBUILDER_H
