/********************************************************************************
** Form generated from reading UI file 'TaskPadPocketParameters.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKPADPOCKETPARAMETERS_H
#define UI_TASKPADPOCKETPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"
#include "Gui/SpinBox.h"

namespace PartDesignGui {

class Ui_TaskPadPocketParameters
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
    QHBoxLayout *side1Layout;
    QLabel *side1Label;
    QFrame *line1;
    QLabel *textLabel1;
    QComboBox *changeMode;
    QLabel *labelLength;
    Gui::PrefQuantitySpinBox *lengthEdit;
    QLabel *labelOffset;
    Gui::PrefQuantitySpinBox *offsetEdit;
    QLabel *labelTaperAngle;
    Gui::PrefQuantitySpinBox *taperEdit;
    QFrame *upToShapeList;
    QVBoxLayout *vboxLayout;
    QGridLayout *_2;
    QLineEdit *lineShapeName;
    QToolButton *buttonShape;
    QCheckBox *checkBoxAllFaces;
    QWidget *upToShapeFaces;
    QVBoxLayout *verticalLayout_2;
    QToolButton *buttonShapeFace;
    QListWidget *listWidgetReferences;
    QGridLayout *gridLayout_5;
    QLineEdit *lineFaceName;
    QToolButton *buttonFace;
    QHBoxLayout *verticalLayout_221;
    QLabel *side2Label;
    QFrame *line2;
    QLabel *typeLabel2;
    QComboBox *changeMode2;
    QLabel *labelLength2;
    Gui::PrefQuantitySpinBox *lengthEdit2;
    QLabel *labelOffset2;
    Gui::PrefQuantitySpinBox *offsetEdit2;
    QLabel *labelTaperAngle2;
    Gui::PrefQuantitySpinBox *taperEdit2;
    QFrame *upToShapeList2;
    QVBoxLayout *vboxLayout1;
    QGridLayout *_22;
    QLineEdit *lineShapeName2;
    QToolButton *buttonShape2;
    QCheckBox *checkBoxAllFaces2;
    QWidget *upToShapeFaces2;
    QVBoxLayout *verticalLayout_222;
    QToolButton *buttonShapeFace2;
    QListWidget *listWidgetReferences2;
    QGridLayout *gridLayout_52;
    QLineEdit *lineFaceName2;
    QToolButton *buttonFace2;
    QFrame *line;
    QCheckBox *checkBoxReversed;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QCheckBox *checkBoxAlongDirection;
    QGridLayout *gridLayout_3;
    QLabel *labelEdge;
    QComboBox *directionCB;
    QGroupBox *groupBoxDirection;
    QGridLayout *gridLayout_2;
    QLabel *labelXSkew;
    Gui::DoubleSpinBox *XDirectionEdit;
    QLabel *labelYSkew;
    Gui::DoubleSpinBox *YDirectionEdit;
    QLabel *labelZSkew;
    Gui::DoubleSpinBox *ZDirectionEdit;
    QHBoxLayout *operationLayout;
    QLabel *labelOperation;
    QComboBox *comboOperation;
    QCheckBox *checkBoxUpdateView;

    void setupUi(QWidget *PartDesignGui__TaskPadPocketParameters)
    {
        if (PartDesignGui__TaskPadPocketParameters->objectName().isEmpty())
            PartDesignGui__TaskPadPocketParameters->setObjectName("PartDesignGui__TaskPadPocketParameters");
        PartDesignGui__TaskPadPocketParameters->resize(300, 772);
        PartDesignGui__TaskPadPocketParameters->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(PartDesignGui__TaskPadPocketParameters);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelStart = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelStart->setObjectName("labelStart");

        gridLayout->addWidget(labelStart, 0, 0, 1, 1);

        startMode = new QComboBox(PartDesignGui__TaskPadPocketParameters);
        startMode->addItem(QString());
        startMode->addItem(QString());
        startMode->addItem(QString());
        startMode->setObjectName("startMode");

        gridLayout->addWidget(startMode, 0, 1, 1, 1);

        labelStartReference = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelStartReference->setObjectName("labelStartReference");
        labelStartReference->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(labelStartReference, 1, 0, 2, 1);

        lineStartReference = new QLineEdit(PartDesignGui__TaskPadPocketParameters);
        lineStartReference->setObjectName("lineStartReference");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineStartReference->sizePolicy().hasHeightForWidth());
        lineStartReference->setSizePolicy(sizePolicy);
        lineStartReference->setReadOnly(true);

        gridLayout->addWidget(lineStartReference, 1, 1, 1, 1);

        buttonStartReference = new QPushButton(PartDesignGui__TaskPadPocketParameters);
        buttonStartReference->setObjectName("buttonStartReference");
        sizePolicy.setHeightForWidth(buttonStartReference->sizePolicy().hasHeightForWidth());
        buttonStartReference->setSizePolicy(sizePolicy);
        buttonStartReference->setCheckable(true);

        gridLayout->addWidget(buttonStartReference, 2, 1, 1, 1);

        labelStartOffset = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelStartOffset->setObjectName("labelStartOffset");

        gridLayout->addWidget(labelStartOffset, 3, 0, 1, 1);

        startOffsetEdit = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        startOffsetEdit->setObjectName("startOffsetEdit");
        startOffsetEdit->setProperty("keyboardTracking", QVariant(false));
        startOffsetEdit->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(startOffsetEdit, 3, 1, 1, 1);

        sidesLabel = new QLabel(PartDesignGui__TaskPadPocketParameters);
        sidesLabel->setObjectName("sidesLabel");

        gridLayout->addWidget(sidesLabel, 4, 0, 1, 1);

        sidesMode = new QComboBox(PartDesignGui__TaskPadPocketParameters);
        sidesMode->setObjectName("sidesMode");

        gridLayout->addWidget(sidesMode, 4, 1, 1, 1);

        side1Layout = new QHBoxLayout();
        side1Layout->setObjectName("side1Layout");
        side1Layout->setContentsMargins(0, 0, 0, 0);
        side1Label = new QLabel(PartDesignGui__TaskPadPocketParameters);
        side1Label->setObjectName("side1Label");

        side1Layout->addWidget(side1Label);

        line1 = new QFrame(PartDesignGui__TaskPadPocketParameters);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::Shape::HLine);
        line1->setFrameShadow(QFrame::Shadow::Sunken);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line1->sizePolicy().hasHeightForWidth());
        line1->setSizePolicy(sizePolicy1);

        side1Layout->addWidget(line1);


        gridLayout->addLayout(side1Layout, 5, 0, 1, 2);

        textLabel1 = new QLabel(PartDesignGui__TaskPadPocketParameters);
        textLabel1->setObjectName("textLabel1");

        gridLayout->addWidget(textLabel1, 6, 0, 1, 1);

        changeMode = new QComboBox(PartDesignGui__TaskPadPocketParameters);
        changeMode->addItem(QString());
        changeMode->setObjectName("changeMode");

        gridLayout->addWidget(changeMode, 6, 1, 1, 1);

        labelLength = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelLength->setObjectName("labelLength");

        gridLayout->addWidget(labelLength, 7, 0, 1, 1);

        lengthEdit = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        lengthEdit->setObjectName("lengthEdit");
        lengthEdit->setProperty("keyboardTracking", QVariant(false));
        lengthEdit->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(lengthEdit, 7, 1, 1, 1);

        labelOffset = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelOffset->setObjectName("labelOffset");

        gridLayout->addWidget(labelOffset, 8, 0, 1, 1);

        offsetEdit = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        offsetEdit->setObjectName("offsetEdit");
        offsetEdit->setProperty("keyboardTracking", QVariant(false));
        offsetEdit->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(offsetEdit, 8, 1, 1, 1);

        labelTaperAngle = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelTaperAngle->setObjectName("labelTaperAngle");

        gridLayout->addWidget(labelTaperAngle, 9, 0, 1, 1);

        taperEdit = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        taperEdit->setObjectName("taperEdit");
        taperEdit->setProperty("keyboardTracking", QVariant(false));
        taperEdit->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        gridLayout->addWidget(taperEdit, 9, 1, 1, 1);

        upToShapeList = new QFrame(PartDesignGui__TaskPadPocketParameters);
        upToShapeList->setObjectName("upToShapeList");
        upToShapeList->setFrameShadow(QFrame::Plain);
        upToShapeList->setLineWidth(0);
        vboxLayout = new QVBoxLayout(upToShapeList);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        _2 = new QGridLayout();
        _2->setObjectName("_2");
        lineShapeName = new QLineEdit(upToShapeList);
        lineShapeName->setObjectName("lineShapeName");
        lineShapeName->setReadOnly(true);

        _2->addWidget(lineShapeName, 0, 1, 1, 1);

        buttonShape = new QToolButton(upToShapeList);
        buttonShape->setObjectName("buttonShape");
        buttonShape->setMinimumSize(QSize(0, 22));
        buttonShape->setCheckable(true);

        _2->addWidget(buttonShape, 0, 0, 1, 1);


        vboxLayout->addLayout(_2);

        checkBoxAllFaces = new QCheckBox(upToShapeList);
        checkBoxAllFaces->setObjectName("checkBoxAllFaces");
        checkBoxAllFaces->setEnabled(true);

        vboxLayout->addWidget(checkBoxAllFaces);

        upToShapeFaces = new QWidget(upToShapeList);
        upToShapeFaces->setObjectName("upToShapeFaces");
        verticalLayout_2 = new QVBoxLayout(upToShapeFaces);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonShapeFace = new QToolButton(upToShapeFaces);
        buttonShapeFace->setObjectName("buttonShapeFace");
        buttonShapeFace->setCheckable(true);

        verticalLayout_2->addWidget(buttonShapeFace);

        listWidgetReferences = new QListWidget(upToShapeFaces);
        listWidgetReferences->setObjectName("listWidgetReferences");
        listWidgetReferences->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_2->addWidget(listWidgetReferences);


        vboxLayout->addWidget(upToShapeFaces);


        gridLayout->addWidget(upToShapeList, 10, 0, 1, 2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        lineFaceName = new QLineEdit(PartDesignGui__TaskPadPocketParameters);
        lineFaceName->setObjectName("lineFaceName");
        lineFaceName->setReadOnly(true);

        gridLayout_5->addWidget(lineFaceName, 0, 1, 1, 1);

        buttonFace = new QToolButton(PartDesignGui__TaskPadPocketParameters);
        buttonFace->setObjectName("buttonFace");
        buttonFace->setMinimumSize(QSize(0, 22));
        buttonFace->setCheckable(true);

        gridLayout_5->addWidget(buttonFace, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_5, 11, 0, 1, 2);

        verticalLayout_221 = new QHBoxLayout();
        verticalLayout_221->setObjectName("verticalLayout_221");
        verticalLayout_221->setContentsMargins(0, 0, 0, 0);
        side2Label = new QLabel(PartDesignGui__TaskPadPocketParameters);
        side2Label->setObjectName("side2Label");

        verticalLayout_221->addWidget(side2Label);

        line2 = new QFrame(PartDesignGui__TaskPadPocketParameters);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::Shape::HLine);
        line2->setFrameShadow(QFrame::Shadow::Sunken);
        sizePolicy1.setHeightForWidth(line2->sizePolicy().hasHeightForWidth());
        line2->setSizePolicy(sizePolicy1);

        verticalLayout_221->addWidget(line2);


        gridLayout->addLayout(verticalLayout_221, 12, 0, 1, 2);

        typeLabel2 = new QLabel(PartDesignGui__TaskPadPocketParameters);
        typeLabel2->setObjectName("typeLabel2");

        gridLayout->addWidget(typeLabel2, 13, 0, 1, 1);

        changeMode2 = new QComboBox(PartDesignGui__TaskPadPocketParameters);
        changeMode2->setObjectName("changeMode2");

        gridLayout->addWidget(changeMode2, 13, 1, 1, 1);

        labelLength2 = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelLength2->setObjectName("labelLength2");

        gridLayout->addWidget(labelLength2, 14, 0, 1, 1);

        lengthEdit2 = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        lengthEdit2->setObjectName("lengthEdit2");
        lengthEdit2->setProperty("keyboardTracking", QVariant(false));
        lengthEdit2->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(lengthEdit2, 14, 1, 1, 1);

        labelOffset2 = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelOffset2->setObjectName("labelOffset2");

        gridLayout->addWidget(labelOffset2, 15, 0, 1, 1);

        offsetEdit2 = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        offsetEdit2->setObjectName("offsetEdit2");
        offsetEdit2->setProperty("keyboardTracking", QVariant(false));
        offsetEdit2->setProperty("unit", QVariant(QString::fromUtf8("mm")));

        gridLayout->addWidget(offsetEdit2, 15, 1, 1, 1);

        labelTaperAngle2 = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelTaperAngle2->setObjectName("labelTaperAngle2");

        gridLayout->addWidget(labelTaperAngle2, 16, 0, 1, 1);

        taperEdit2 = new Gui::PrefQuantitySpinBox(PartDesignGui__TaskPadPocketParameters);
        taperEdit2->setObjectName("taperEdit2");
        taperEdit2->setProperty("keyboardTracking", QVariant(false));
        taperEdit2->setProperty("unit", QVariant(QString::fromUtf8("deg")));

        gridLayout->addWidget(taperEdit2, 16, 1, 1, 1);

        upToShapeList2 = new QFrame(PartDesignGui__TaskPadPocketParameters);
        upToShapeList2->setObjectName("upToShapeList2");
        upToShapeList2->setFrameShadow(QFrame::Plain);
        upToShapeList2->setLineWidth(0);
        vboxLayout1 = new QVBoxLayout(upToShapeList2);
        vboxLayout1->setObjectName("vboxLayout1");
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        _22 = new QGridLayout();
        _22->setObjectName("_22");
        lineShapeName2 = new QLineEdit(upToShapeList2);
        lineShapeName2->setObjectName("lineShapeName2");
        lineShapeName2->setReadOnly(true);

        _22->addWidget(lineShapeName2, 0, 1, 1, 1);

        buttonShape2 = new QToolButton(upToShapeList2);
        buttonShape2->setObjectName("buttonShape2");
        buttonShape2->setMinimumSize(QSize(0, 22));
        buttonShape2->setCheckable(true);

        _22->addWidget(buttonShape2, 0, 0, 1, 1);


        vboxLayout1->addLayout(_22);

        checkBoxAllFaces2 = new QCheckBox(upToShapeList2);
        checkBoxAllFaces2->setObjectName("checkBoxAllFaces2");
        checkBoxAllFaces2->setEnabled(true);

        vboxLayout1->addWidget(checkBoxAllFaces2);

        upToShapeFaces2 = new QWidget(upToShapeList2);
        upToShapeFaces2->setObjectName("upToShapeFaces2");
        verticalLayout_222 = new QVBoxLayout(upToShapeFaces2);
        verticalLayout_222->setObjectName("verticalLayout_222");
        verticalLayout_222->setContentsMargins(0, 0, 0, 0);
        buttonShapeFace2 = new QToolButton(upToShapeFaces2);
        buttonShapeFace2->setObjectName("buttonShapeFace2");
        buttonShapeFace2->setCheckable(true);

        verticalLayout_222->addWidget(buttonShapeFace2);

        listWidgetReferences2 = new QListWidget(upToShapeFaces2);
        listWidgetReferences2->setObjectName("listWidgetReferences2");
        listWidgetReferences2->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_222->addWidget(listWidgetReferences2);


        vboxLayout1->addWidget(upToShapeFaces2);


        gridLayout->addWidget(upToShapeList2, 17, 0, 1, 2);

        gridLayout_52 = new QGridLayout();
        gridLayout_52->setObjectName("gridLayout_52");
        lineFaceName2 = new QLineEdit(PartDesignGui__TaskPadPocketParameters);
        lineFaceName2->setObjectName("lineFaceName2");
        lineFaceName2->setReadOnly(true);

        gridLayout_52->addWidget(lineFaceName2, 0, 1, 1, 1);

        buttonFace2 = new QToolButton(PartDesignGui__TaskPadPocketParameters);
        buttonFace2->setObjectName("buttonFace2");
        buttonFace2->setMinimumSize(QSize(0, 22));
        buttonFace2->setCheckable(true);

        gridLayout_52->addWidget(buttonFace2, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_52, 24, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        line = new QFrame(PartDesignGui__TaskPadPocketParameters);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        checkBoxReversed = new QCheckBox(PartDesignGui__TaskPadPocketParameters);
        checkBoxReversed->setObjectName("checkBoxReversed");

        verticalLayout->addWidget(checkBoxReversed);

        groupBox = new QGroupBox(PartDesignGui__TaskPadPocketParameters);
        groupBox->setObjectName("groupBox");
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        checkBoxAlongDirection = new QCheckBox(groupBox);
        checkBoxAlongDirection->setObjectName("checkBoxAlongDirection");
        checkBoxAlongDirection->setEnabled(true);

        gridLayout_4->addWidget(checkBoxAlongDirection, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        labelEdge = new QLabel(groupBox);
        labelEdge->setObjectName("labelEdge");

        gridLayout_3->addWidget(labelEdge, 0, 0, 1, 1);

        directionCB = new QComboBox(groupBox);
        directionCB->addItem(QString());
        directionCB->addItem(QString());
        directionCB->addItem(QString());
        directionCB->setObjectName("directionCB");

        gridLayout_3->addWidget(directionCB, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        groupBoxDirection = new QGroupBox(groupBox);
        groupBoxDirection->setObjectName("groupBoxDirection");
        groupBoxDirection->setEnabled(true);
        groupBoxDirection->setCheckable(false);
        groupBoxDirection->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxDirection);
        gridLayout_2->setObjectName("gridLayout_2");
        labelXSkew = new QLabel(groupBoxDirection);
        labelXSkew->setObjectName("labelXSkew");

        gridLayout_2->addWidget(labelXSkew, 0, 0, 1, 1);

        XDirectionEdit = new Gui::DoubleSpinBox(groupBoxDirection);
        XDirectionEdit->setObjectName("XDirectionEdit");
        XDirectionEdit->setKeyboardTracking(false);
        XDirectionEdit->setMinimum(-100.000000000000000);
        XDirectionEdit->setMaximum(100.000000000000000);
        XDirectionEdit->setSingleStep(0.100000000000000);
        XDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(XDirectionEdit, 0, 1, 1, 1);

        labelYSkew = new QLabel(groupBoxDirection);
        labelYSkew->setObjectName("labelYSkew");

        gridLayout_2->addWidget(labelYSkew, 1, 0, 1, 1);

        YDirectionEdit = new Gui::DoubleSpinBox(groupBoxDirection);
        YDirectionEdit->setObjectName("YDirectionEdit");
        YDirectionEdit->setKeyboardTracking(false);
        YDirectionEdit->setMinimum(-100.000000000000000);
        YDirectionEdit->setMaximum(100.000000000000000);
        YDirectionEdit->setSingleStep(0.100000000000000);
        YDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(YDirectionEdit, 1, 1, 1, 1);

        labelZSkew = new QLabel(groupBoxDirection);
        labelZSkew->setObjectName("labelZSkew");

        gridLayout_2->addWidget(labelZSkew, 2, 0, 1, 1);

        ZDirectionEdit = new Gui::DoubleSpinBox(groupBoxDirection);
        ZDirectionEdit->setObjectName("ZDirectionEdit");
        ZDirectionEdit->setKeyboardTracking(false);
        ZDirectionEdit->setMinimum(-100.000000000000000);
        ZDirectionEdit->setMaximum(100.000000000000000);
        ZDirectionEdit->setSingleStep(0.100000000000000);
        ZDirectionEdit->setValue(1.000000000000000);
        ZDirectionEdit->setProperty("unit", QVariant(QString::fromUtf8("")));

        gridLayout_2->addWidget(ZDirectionEdit, 2, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxDirection, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        operationLayout = new QHBoxLayout();
        operationLayout->setObjectName("operationLayout");
        labelOperation = new QLabel(PartDesignGui__TaskPadPocketParameters);
        labelOperation->setObjectName("labelOperation");

        operationLayout->addWidget(labelOperation);

        comboOperation = new QComboBox(PartDesignGui__TaskPadPocketParameters);
        comboOperation->addItem(QString());
        comboOperation->addItem(QString());
        comboOperation->setObjectName("comboOperation");

        operationLayout->addWidget(comboOperation);


        verticalLayout->addLayout(operationLayout);

        checkBoxUpdateView = new QCheckBox(PartDesignGui__TaskPadPocketParameters);
        checkBoxUpdateView->setObjectName("checkBoxUpdateView");
        checkBoxUpdateView->setChecked(true);

        verticalLayout->addWidget(checkBoxUpdateView);

#if QT_CONFIG(shortcut)
        labelOperation->setBuddy(comboOperation);
#endif // QT_CONFIG(shortcut)

        retranslateUi(PartDesignGui__TaskPadPocketParameters);

        QMetaObject::connectSlotsByName(PartDesignGui__TaskPadPocketParameters);
    } // setupUi

    void retranslateUi(QWidget *PartDesignGui__TaskPadPocketParameters)
    {
        labelStart->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Start", nullptr));
        startMode->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Profile plane", nullptr));
        startMode->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Offset", nullptr));
        startMode->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Reference", nullptr));

        labelStartReference->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Reference", nullptr));
        buttonStartReference->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Pick Reference", nullptr));
        labelStartOffset->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Offset", nullptr));
        sidesLabel->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Direction", nullptr));
        side1Label->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Side 1", nullptr));
        textLabel1->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Type", nullptr));
        changeMode->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Dimension", nullptr));

        labelLength->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Length", nullptr));
        labelOffset->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Offset to face", nullptr));
#if QT_CONFIG(tooltip)
        labelTaperAngle->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Angle to taper the extrusion", nullptr));
#endif // QT_CONFIG(tooltip)
        labelTaperAngle->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Taper angle", nullptr));
        buttonShape->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select Shape", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAllFaces->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Selects all faces of the shape", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAllFaces->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select all faces", nullptr));
#if QT_CONFIG(tooltip)
        buttonShapeFace->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Toggles between selection and preview mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonShapeFace->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select", nullptr));
        buttonFace->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select Face", nullptr));
        side2Label->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Side 2", nullptr));
        typeLabel2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Type", nullptr));
        labelLength2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Length", nullptr));
        labelOffset2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Offset to face", nullptr));
#if QT_CONFIG(tooltip)
        labelTaperAngle2->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Angle to taper the extrusion", nullptr));
#endif // QT_CONFIG(tooltip)
        labelTaperAngle2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Taper angle", nullptr));
        buttonShape2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select Shape", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAllFaces2->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Selects all faces of the shape", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAllFaces2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select all faces", nullptr));
#if QT_CONFIG(tooltip)
        buttonShapeFace2->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Toggles between selection and preview mode", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonShapeFace2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select", nullptr));
        buttonFace2->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select Face", nullptr));
        checkBoxReversed->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Reversed", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Direction", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxAlongDirection->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "If unchecked, the length will be\n"
"measured along the specified direction", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxAlongDirection->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Length along sketch normal", nullptr));
        labelEdge->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Direction/edge", nullptr));
        directionCB->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Sketch normal", nullptr));
        directionCB->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Select reference\342\200\246", nullptr));
        directionCB->setItemText(2, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Custom direction", nullptr));

#if QT_CONFIG(tooltip)
        directionCB->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Set a direction or select an edge\n"
"from the model as reference", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBoxDirection->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Use custom vector for pad direction, otherwise\n"
"the sketch plane's normal vector will be used", nullptr));
#endif // QT_CONFIG(tooltip)
        labelXSkew->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "X", nullptr));
#if QT_CONFIG(tooltip)
        XDirectionEdit->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "X-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelYSkew->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Y", nullptr));
#if QT_CONFIG(tooltip)
        YDirectionEdit->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Y-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelZSkew->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Z", nullptr));
#if QT_CONFIG(tooltip)
        ZDirectionEdit->setToolTip(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Z-component of direction vector", nullptr));
#endif // QT_CONFIG(tooltip)
        labelOperation->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Operation", nullptr));
        comboOperation->setItemText(0, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Subtraction", nullptr));
        comboOperation->setItemText(1, QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Common", nullptr));

        checkBoxUpdateView->setText(QCoreApplication::translate("PartDesignGui::TaskPadPocketParameters", "Recompute on change", nullptr));
        (void)PartDesignGui__TaskPadPocketParameters;
    } // retranslateUi

};

} // namespace PartDesignGui

namespace PartDesignGui {
namespace Ui {
    class TaskPadPocketParameters: public Ui_TaskPadPocketParameters {};
} // namespace Ui
} // namespace PartDesignGui

#endif // UI_TASKPADPOCKETPARAMETERS_H
