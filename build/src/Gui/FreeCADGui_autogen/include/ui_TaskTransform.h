/********************************************************************************
** Form generated from reading UI file 'TaskTransform.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKTRANSFORM_H
#define UI_TASKTRANSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/QuantitySpinBox.h"

namespace Gui {

class Ui_TaskTransformDialog
{
public:
    QGridLayout *gridLayout;
    QWidget *coordinateSystemWidget;
    QGridLayout *coordinateSystemLayout;
    QLabel *label_2;
    QComboBox *positionModeComboBox;
    QLabel *customCSReferenceLabel;
    QWidget *customCSPickerWidget;
    QVBoxLayout *customCSPickerLayout;
    QLineEdit *customCSLineEdit;
    QPushButton *pickCoordinateSystemReferenceButton;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *alignRotationCheckBox;
    QSpacerItem *vSpacer;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *positionGroupBox;
    QGridLayout *gridLayout1;
    QWidget *positionStackWidget;
    QGridLayout *absolutePositionLayout;
    Gui::QuantitySpinBox *zPositionSpinBox;
    Gui::QuantitySpinBox *xPositionSpinBox;
    QLabel *xPositionLabel;
    QLabel *yPositionLabel;
    QLabel *zPositionLabel;
    Gui::QuantitySpinBox *yPositionSpinBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *alignToOtherObjectButton;
    QPushButton *moveOptionsButton;
    QFrame *frameMoveOptions;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *translateCheckbox;
    QCheckBox *rotateCheckbox;
    QGridLayout *gridLayout_2;
    QCheckBox *matchXcheckbox;
    QCheckBox *matchYcheckbox;
    QCheckBox *matchZcheckbox;
    QCheckBox *alignXcheckbox;
    QCheckBox *alignYcheckbox;
    QCheckBox *alignZcheckbox;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame;
    QPushButton *flipPartButton;
    QGroupBox *transformOriginGroupBox;
    QGridLayout *transformOriginLayout;
    QComboBox *placementComboBox;
    QLabel *snappingLabel;
    QLabel *translationIncrementLabel;
    Gui::QuantitySpinBox *rotationIncrementSpinBox;
    QSpacerItem *verticalSpacer_4;
    QLabel *referenceLabel;
    QWidget *referencePickerWidget;
    QVBoxLayout *referencePickerLayout;
    QLineEdit *referenceLineEdit;
    QPushButton *pickTransformOriginButton;
    Gui::QuantitySpinBox *translationIncrementSpinBox;
    QLabel *label;
    QLabel *rotationIncrementLabel;
    QGroupBox *rotationGroupBox;
    QGridLayout *gridLayout2;
    QWidget *rotationStackWidget;
    QGridLayout *absoluteRotationLayout;
    Gui::QuantitySpinBox *zRotationSpinBox;
    QLabel *yRotationLabel;
    QLabel *zRotationLabel;
    Gui::QuantitySpinBox *yRotationSpinBox;
    Gui::QuantitySpinBox *xRotationSpinBox;
    QLabel *xRotationLabel;

    void setupUi(QWidget *Gui__TaskTransformDialog)
    {
        if (Gui__TaskTransformDialog->objectName().isEmpty())
            Gui__TaskTransformDialog->setObjectName("Gui__TaskTransformDialog");
        Gui__TaskTransformDialog->resize(450, 1012);
        gridLayout = new QGridLayout(Gui__TaskTransformDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        coordinateSystemWidget = new QWidget(Gui__TaskTransformDialog);
        coordinateSystemWidget->setObjectName("coordinateSystemWidget");
        coordinateSystemLayout = new QGridLayout(coordinateSystemWidget);
        coordinateSystemLayout->setSpacing(6);
        coordinateSystemLayout->setContentsMargins(11, 11, 11, 11);
        coordinateSystemLayout->setObjectName("coordinateSystemLayout");
        coordinateSystemLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(coordinateSystemWidget);
        label_2->setObjectName("label_2");

        coordinateSystemLayout->addWidget(label_2, 0, 0, 1, 1);

        positionModeComboBox = new QComboBox(coordinateSystemWidget);
        positionModeComboBox->addItem(QString());
        positionModeComboBox->addItem(QString());
        positionModeComboBox->setObjectName("positionModeComboBox");

        coordinateSystemLayout->addWidget(positionModeComboBox, 0, 1, 1, 1);

        customCSReferenceLabel = new QLabel(coordinateSystemWidget);
        customCSReferenceLabel->setObjectName("customCSReferenceLabel");
        customCSReferenceLabel->setVisible(false);
        customCSReferenceLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        coordinateSystemLayout->addWidget(customCSReferenceLabel, 1, 0, 1, 1);

        customCSPickerWidget = new QWidget(coordinateSystemWidget);
        customCSPickerWidget->setObjectName("customCSPickerWidget");
        customCSPickerWidget->setVisible(false);
        customCSPickerLayout = new QVBoxLayout(customCSPickerWidget);
        customCSPickerLayout->setSpacing(6);
        customCSPickerLayout->setContentsMargins(11, 11, 11, 11);
        customCSPickerLayout->setObjectName("customCSPickerLayout");
        customCSPickerLayout->setContentsMargins(0, 0, 0, 0);
        customCSLineEdit = new QLineEdit(customCSPickerWidget);
        customCSLineEdit->setObjectName("customCSLineEdit");
        customCSLineEdit->setReadOnly(true);

        customCSPickerLayout->addWidget(customCSLineEdit);

        pickCoordinateSystemReferenceButton = new QPushButton(customCSPickerWidget);
        pickCoordinateSystemReferenceButton->setObjectName("pickCoordinateSystemReferenceButton");

        customCSPickerLayout->addWidget(pickCoordinateSystemReferenceButton);


        coordinateSystemLayout->addWidget(customCSPickerWidget, 1, 1, 1, 1);

        coordinateSystemLayout->setColumnStretch(1, 1);

        gridLayout->addWidget(coordinateSystemWidget, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        alignRotationCheckBox = new QCheckBox(Gui__TaskTransformDialog);
        alignRotationCheckBox->setObjectName("alignRotationCheckBox");

        horizontalLayout_4->addWidget(alignRotationCheckBox);


        gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        vSpacer = new QSpacerItem(20, 41, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(vSpacer, 8, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 1, 0, 1, 1);

        positionGroupBox = new QGroupBox(Gui__TaskTransformDialog);
        positionGroupBox->setObjectName("positionGroupBox");
        gridLayout1 = new QGridLayout(positionGroupBox);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        gridLayout1->setContentsMargins(9, 9, 9, 9);
        positionStackWidget = new QWidget(positionGroupBox);
        positionStackWidget->setObjectName("positionStackWidget");
        absolutePositionLayout = new QGridLayout(positionStackWidget);
        absolutePositionLayout->setSpacing(6);
        absolutePositionLayout->setContentsMargins(11, 11, 11, 11);
        absolutePositionLayout->setObjectName("absolutePositionLayout");
        absolutePositionLayout->setContentsMargins(0, 0, 0, 0);
        zPositionSpinBox = new Gui::QuantitySpinBox(positionStackWidget);
        zPositionSpinBox->setObjectName("zPositionSpinBox");

        absolutePositionLayout->addWidget(zPositionSpinBox, 4, 1, 1, 1);

        xPositionSpinBox = new Gui::QuantitySpinBox(positionStackWidget);
        xPositionSpinBox->setObjectName("xPositionSpinBox");

        absolutePositionLayout->addWidget(xPositionSpinBox, 2, 1, 1, 1);

        xPositionLabel = new QLabel(positionStackWidget);
        xPositionLabel->setObjectName("xPositionLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xPositionLabel->sizePolicy().hasHeightForWidth());
        xPositionLabel->setSizePolicy(sizePolicy);

        absolutePositionLayout->addWidget(xPositionLabel, 2, 0, 1, 1);

        yPositionLabel = new QLabel(positionStackWidget);
        yPositionLabel->setObjectName("yPositionLabel");
        sizePolicy.setHeightForWidth(yPositionLabel->sizePolicy().hasHeightForWidth());
        yPositionLabel->setSizePolicy(sizePolicy);

        absolutePositionLayout->addWidget(yPositionLabel, 3, 0, 1, 1);

        zPositionLabel = new QLabel(positionStackWidget);
        zPositionLabel->setObjectName("zPositionLabel");
        sizePolicy.setHeightForWidth(zPositionLabel->sizePolicy().hasHeightForWidth());
        zPositionLabel->setSizePolicy(sizePolicy);

        absolutePositionLayout->addWidget(zPositionLabel, 4, 0, 1, 1);

        yPositionSpinBox = new Gui::QuantitySpinBox(positionStackWidget);
        yPositionSpinBox->setObjectName("yPositionSpinBox");

        absolutePositionLayout->addWidget(yPositionSpinBox, 3, 1, 1, 1);

        absolutePositionLayout->setColumnStretch(0, 1);

        gridLayout1->addWidget(positionStackWidget, 0, 0, 1, 1);

        gridLayout1->setColumnMinimumWidth(0, 100);

        gridLayout->addWidget(positionGroupBox, 5, 0, 1, 1);

        groupBox = new QGroupBox(Gui__TaskTransformDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 6, -1, -1);
        alignToOtherObjectButton = new QPushButton(groupBox);
        alignToOtherObjectButton->setObjectName("alignToOtherObjectButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(alignToOtherObjectButton->sizePolicy().hasHeightForWidth());
        alignToOtherObjectButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(alignToOtherObjectButton);

        moveOptionsButton = new QPushButton(groupBox);
        moveOptionsButton->setObjectName("moveOptionsButton");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("preferences-other")));
        moveOptionsButton->setIcon(icon);
        moveOptionsButton->setCheckable(true);
        moveOptionsButton->setChecked(false);

        horizontalLayout_2->addWidget(moveOptionsButton);


        verticalLayout->addLayout(horizontalLayout_2);

        frameMoveOptions = new QFrame(groupBox);
        frameMoveOptions->setObjectName("frameMoveOptions");
        frameMoveOptions->setVisible(false);
        frameMoveOptions->setFrameShape(QFrame::Shape::StyledPanel);
        frameMoveOptions->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frameMoveOptions);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 6, -1, -1);
        translateCheckbox = new QCheckBox(frameMoveOptions);
        translateCheckbox->setObjectName("translateCheckbox");
        translateCheckbox->setChecked(true);

        horizontalLayout->addWidget(translateCheckbox);

        rotateCheckbox = new QCheckBox(frameMoveOptions);
        rotateCheckbox->setObjectName("rotateCheckbox");
        rotateCheckbox->setChecked(true);

        horizontalLayout->addWidget(rotateCheckbox);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(-1, 0, -1, 6);
        matchXcheckbox = new QCheckBox(frameMoveOptions);
        matchXcheckbox->setObjectName("matchXcheckbox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(matchXcheckbox->sizePolicy().hasHeightForWidth());
        matchXcheckbox->setSizePolicy(sizePolicy2);
        matchXcheckbox->setChecked(true);

        gridLayout_2->addWidget(matchXcheckbox, 0, 1, 1, 1);

        matchYcheckbox = new QCheckBox(frameMoveOptions);
        matchYcheckbox->setObjectName("matchYcheckbox");
        sizePolicy2.setHeightForWidth(matchYcheckbox->sizePolicy().hasHeightForWidth());
        matchYcheckbox->setSizePolicy(sizePolicy2);
        matchYcheckbox->setChecked(true);

        gridLayout_2->addWidget(matchYcheckbox, 1, 1, 1, 1);

        matchZcheckbox = new QCheckBox(frameMoveOptions);
        matchZcheckbox->setObjectName("matchZcheckbox");
        sizePolicy2.setHeightForWidth(matchZcheckbox->sizePolicy().hasHeightForWidth());
        matchZcheckbox->setSizePolicy(sizePolicy2);
        matchZcheckbox->setChecked(true);

        gridLayout_2->addWidget(matchZcheckbox, 2, 1, 1, 1);

        alignXcheckbox = new QCheckBox(frameMoveOptions);
        alignXcheckbox->setObjectName("alignXcheckbox");
        sizePolicy2.setHeightForWidth(alignXcheckbox->sizePolicy().hasHeightForWidth());
        alignXcheckbox->setSizePolicy(sizePolicy2);
        alignXcheckbox->setChecked(true);

        gridLayout_2->addWidget(alignXcheckbox, 0, 3, 1, 1);

        alignYcheckbox = new QCheckBox(frameMoveOptions);
        alignYcheckbox->setObjectName("alignYcheckbox");
        sizePolicy2.setHeightForWidth(alignYcheckbox->sizePolicy().hasHeightForWidth());
        alignYcheckbox->setSizePolicy(sizePolicy2);
        alignYcheckbox->setChecked(true);

        gridLayout_2->addWidget(alignYcheckbox, 1, 3, 1, 1);

        alignZcheckbox = new QCheckBox(frameMoveOptions);
        alignZcheckbox->setObjectName("alignZcheckbox");
        sizePolicy2.setHeightForWidth(alignZcheckbox->sizePolicy().hasHeightForWidth());
        alignZcheckbox->setSizePolicy(sizePolicy2);
        alignZcheckbox->setChecked(true);

        gridLayout_2->addWidget(alignZcheckbox, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout->addWidget(frameMoveOptions);

        frame = new QFrame(groupBox);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout->addWidget(frame);

        flipPartButton = new QPushButton(groupBox);
        flipPartButton->setObjectName("flipPartButton");

        verticalLayout->addWidget(flipPartButton);


        gridLayout->addWidget(groupBox, 7, 0, 1, 1);

        transformOriginGroupBox = new QGroupBox(Gui__TaskTransformDialog);
        transformOriginGroupBox->setObjectName("transformOriginGroupBox");
        transformOriginLayout = new QGridLayout(transformOriginGroupBox);
        transformOriginLayout->setSpacing(6);
        transformOriginLayout->setContentsMargins(11, 11, 11, 11);
        transformOriginLayout->setObjectName("transformOriginLayout");
        transformOriginLayout->setContentsMargins(9, 9, 9, 9);
        placementComboBox = new QComboBox(transformOriginGroupBox);
        placementComboBox->setObjectName("placementComboBox");

        transformOriginLayout->addWidget(placementComboBox, 0, 1, 1, 1);

        snappingLabel = new QLabel(transformOriginGroupBox);
        snappingLabel->setObjectName("snappingLabel");
        sizePolicy1.setHeightForWidth(snappingLabel->sizePolicy().hasHeightForWidth());
        snappingLabel->setSizePolicy(sizePolicy1);
        snappingLabel->setFrameShape(QFrame::Shape::NoFrame);
        snappingLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        transformOriginLayout->addWidget(snappingLabel, 5, 0, 1, 2);

        translationIncrementLabel = new QLabel(transformOriginGroupBox);
        translationIncrementLabel->setObjectName("translationIncrementLabel");
        sizePolicy.setHeightForWidth(translationIncrementLabel->sizePolicy().hasHeightForWidth());
        translationIncrementLabel->setSizePolicy(sizePolicy);

        transformOriginLayout->addWidget(translationIncrementLabel, 6, 0, 1, 1);

        rotationIncrementSpinBox = new Gui::QuantitySpinBox(transformOriginGroupBox);
        rotationIncrementSpinBox->setObjectName("rotationIncrementSpinBox");
        rotationIncrementSpinBox->setMinimum(0.000000000000000);
        rotationIncrementSpinBox->setMaximum(360.000000000000000);
        rotationIncrementSpinBox->setValue(5.000000000000000);

        transformOriginLayout->addWidget(rotationIncrementSpinBox, 7, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        transformOriginLayout->addItem(verticalSpacer_4, 4, 0, 1, 2);

        referenceLabel = new QLabel(transformOriginGroupBox);
        referenceLabel->setObjectName("referenceLabel");
        referenceLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        transformOriginLayout->addWidget(referenceLabel, 1, 0, 1, 1);

        referencePickerWidget = new QWidget(transformOriginGroupBox);
        referencePickerWidget->setObjectName("referencePickerWidget");
        referencePickerLayout = new QVBoxLayout(referencePickerWidget);
        referencePickerLayout->setSpacing(6);
        referencePickerLayout->setContentsMargins(11, 11, 11, 11);
        referencePickerLayout->setObjectName("referencePickerLayout");
        referencePickerLayout->setContentsMargins(0, 0, 0, 0);
        referenceLineEdit = new QLineEdit(referencePickerWidget);
        referenceLineEdit->setObjectName("referenceLineEdit");
        referenceLineEdit->setReadOnly(true);

        referencePickerLayout->addWidget(referenceLineEdit);

        pickTransformOriginButton = new QPushButton(referencePickerWidget);
        pickTransformOriginButton->setObjectName("pickTransformOriginButton");

        referencePickerLayout->addWidget(pickTransformOriginButton);


        transformOriginLayout->addWidget(referencePickerWidget, 1, 1, 1, 1);

        translationIncrementSpinBox = new Gui::QuantitySpinBox(transformOriginGroupBox);
        translationIncrementSpinBox->setObjectName("translationIncrementSpinBox");
        translationIncrementSpinBox->setMinimum(0.000000000000000);
        translationIncrementSpinBox->setMaximum(2147483647.000000000000000);
        translationIncrementSpinBox->setValue(1.000000000000000);

        transformOriginLayout->addWidget(translationIncrementSpinBox, 6, 1, 1, 1);

        label = new QLabel(transformOriginGroupBox);
        label->setObjectName("label");

        transformOriginLayout->addWidget(label, 0, 0, 1, 1);

        rotationIncrementLabel = new QLabel(transformOriginGroupBox);
        rotationIncrementLabel->setObjectName("rotationIncrementLabel");
        sizePolicy.setHeightForWidth(rotationIncrementLabel->sizePolicy().hasHeightForWidth());
        rotationIncrementLabel->setSizePolicy(sizePolicy);

        transformOriginLayout->addWidget(rotationIncrementLabel, 7, 0, 1, 1);


        gridLayout->addWidget(transformOriginGroupBox, 0, 0, 1, 1);

        rotationGroupBox = new QGroupBox(Gui__TaskTransformDialog);
        rotationGroupBox->setObjectName("rotationGroupBox");
        gridLayout2 = new QGridLayout(rotationGroupBox);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName("gridLayout2");
        gridLayout2->setContentsMargins(9, 9, 9, 9);
        rotationStackWidget = new QWidget(rotationGroupBox);
        rotationStackWidget->setObjectName("rotationStackWidget");
        absoluteRotationLayout = new QGridLayout(rotationStackWidget);
        absoluteRotationLayout->setSpacing(6);
        absoluteRotationLayout->setContentsMargins(11, 11, 11, 11);
        absoluteRotationLayout->setObjectName("absoluteRotationLayout");
        absoluteRotationLayout->setContentsMargins(0, 0, 0, 0);
        zRotationSpinBox = new Gui::QuantitySpinBox(rotationStackWidget);
        zRotationSpinBox->setObjectName("zRotationSpinBox");

        absoluteRotationLayout->addWidget(zRotationSpinBox, 2, 1, 1, 1);

        yRotationLabel = new QLabel(rotationStackWidget);
        yRotationLabel->setObjectName("yRotationLabel");
        sizePolicy.setHeightForWidth(yRotationLabel->sizePolicy().hasHeightForWidth());
        yRotationLabel->setSizePolicy(sizePolicy);

        absoluteRotationLayout->addWidget(yRotationLabel, 1, 0, 1, 1);

        zRotationLabel = new QLabel(rotationStackWidget);
        zRotationLabel->setObjectName("zRotationLabel");
        sizePolicy.setHeightForWidth(zRotationLabel->sizePolicy().hasHeightForWidth());
        zRotationLabel->setSizePolicy(sizePolicy);

        absoluteRotationLayout->addWidget(zRotationLabel, 2, 0, 1, 1);

        yRotationSpinBox = new Gui::QuantitySpinBox(rotationStackWidget);
        yRotationSpinBox->setObjectName("yRotationSpinBox");

        absoluteRotationLayout->addWidget(yRotationSpinBox, 1, 1, 1, 1);

        xRotationSpinBox = new Gui::QuantitySpinBox(rotationStackWidget);
        xRotationSpinBox->setObjectName("xRotationSpinBox");

        absoluteRotationLayout->addWidget(xRotationSpinBox, 0, 1, 1, 1);

        xRotationLabel = new QLabel(rotationStackWidget);
        xRotationLabel->setObjectName("xRotationLabel");
        sizePolicy.setHeightForWidth(xRotationLabel->sizePolicy().hasHeightForWidth());
        xRotationLabel->setSizePolicy(sizePolicy);

        absoluteRotationLayout->addWidget(xRotationLabel, 0, 0, 1, 1);

        absoluteRotationLayout->setColumnStretch(0, 1);

        gridLayout2->addWidget(rotationStackWidget, 1, 0, 1, 2);


        gridLayout->addWidget(rotationGroupBox, 6, 0, 1, 1);

#if QT_CONFIG(shortcut)
        label_2->setBuddy(positionModeComboBox);
        customCSReferenceLabel->setBuddy(customCSLineEdit);
        xPositionLabel->setBuddy(xPositionSpinBox);
        yPositionLabel->setBuddy(yPositionSpinBox);
        zPositionLabel->setBuddy(zPositionSpinBox);
        translationIncrementLabel->setBuddy(translationIncrementSpinBox);
        referenceLabel->setBuddy(referenceLineEdit);
        label->setBuddy(placementComboBox);
        rotationIncrementLabel->setBuddy(rotationIncrementSpinBox);
        yRotationLabel->setBuddy(yRotationSpinBox);
        zRotationLabel->setBuddy(zRotationSpinBox);
        xRotationLabel->setBuddy(xRotationSpinBox);
#endif // QT_CONFIG(shortcut)
        QWidget::setTabOrder(placementComboBox, referenceLineEdit);
        QWidget::setTabOrder(referenceLineEdit, pickTransformOriginButton);
        QWidget::setTabOrder(pickTransformOriginButton, translationIncrementSpinBox);
        QWidget::setTabOrder(translationIncrementSpinBox, rotationIncrementSpinBox);
        QWidget::setTabOrder(rotationIncrementSpinBox, positionModeComboBox);
        QWidget::setTabOrder(positionModeComboBox, customCSLineEdit);
        QWidget::setTabOrder(customCSLineEdit, pickCoordinateSystemReferenceButton);
        QWidget::setTabOrder(pickCoordinateSystemReferenceButton, alignRotationCheckBox);
        QWidget::setTabOrder(alignRotationCheckBox, xPositionSpinBox);
        QWidget::setTabOrder(xPositionSpinBox, yPositionSpinBox);
        QWidget::setTabOrder(yPositionSpinBox, zPositionSpinBox);
        QWidget::setTabOrder(zPositionSpinBox, xRotationSpinBox);
        QWidget::setTabOrder(xRotationSpinBox, yRotationSpinBox);
        QWidget::setTabOrder(yRotationSpinBox, zRotationSpinBox);
        QWidget::setTabOrder(zRotationSpinBox, alignToOtherObjectButton);
        QWidget::setTabOrder(alignToOtherObjectButton, flipPartButton);

        retranslateUi(Gui__TaskTransformDialog);

        QMetaObject::connectSlotsByName(Gui__TaskTransformDialog);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskTransformDialog)
    {
        Gui__TaskTransformDialog->setWindowTitle(QCoreApplication::translate("Gui::TaskTransformDialog", "Placement", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Coordinate system", nullptr));
        positionModeComboBox->setItemText(0, QCoreApplication::translate("Gui::TaskTransformDialog", "Local coordinate system", nullptr));
        positionModeComboBox->setItemText(1, QCoreApplication::translate("Gui::TaskTransformDialog", "Global coordinate system", nullptr));

        customCSReferenceLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Reference", nullptr));
        pickCoordinateSystemReferenceButton->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Pick Reference", nullptr));
        alignRotationCheckBox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Align dragger rotation with selected coordinate system", nullptr));
        positionGroupBox->setTitle(QCoreApplication::translate("Gui::TaskTransformDialog", "Translation", nullptr));
        xPositionLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "X", nullptr));
        yPositionLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Y", nullptr));
        zPositionLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Z", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Gui::TaskTransformDialog", "Utilities", nullptr));
        alignToOtherObjectButton->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Move to Other Object", nullptr));
        moveOptionsButton->setText(QString());
        translateCheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Translate", nullptr));
        rotateCheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Rotate", nullptr));
        matchXcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Match U/X", nullptr));
        matchYcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Match V/Y", nullptr));
        matchZcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Match W/Z", nullptr));
        alignXcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Align U/X", nullptr));
        alignYcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Align V/Y", nullptr));
        alignZcheckbox->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Align W/Z", nullptr));
        flipPartButton->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Flip", nullptr));
        transformOriginGroupBox->setTitle(QCoreApplication::translate("Gui::TaskTransformDialog", "Dragger", nullptr));
        snappingLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "<b>Snapping</b>", nullptr));
        translationIncrementLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Translation", nullptr));
        referenceLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Reference", nullptr));
        pickTransformOriginButton->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Pick Reference", nullptr));
        label->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Mode", nullptr));
        rotationIncrementLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Rotation", nullptr));
        rotationGroupBox->setTitle(QCoreApplication::translate("Gui::TaskTransformDialog", "Rotation", nullptr));
        yRotationLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Y", nullptr));
        zRotationLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "Z", nullptr));
        xRotationLabel->setText(QCoreApplication::translate("Gui::TaskTransformDialog", "X", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class TaskTransformDialog: public Ui_TaskTransformDialog {};
} // namespace Ui
} // namespace Gui

#endif // UI_TASKTRANSFORM_H
