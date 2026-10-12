/********************************************************************************
** Form generated from reading UI file 'DlgEvaluateMesh.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGEVALUATEMESH_H
#define UI_DLGEVALUATEMESH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

namespace MeshGui {

class Ui_DlgEvaluateMesh
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *hboxLayout1;
    QCheckBox *checkOrientationButton;
    QSpacerItem *spacerItem;
    QPushButton *analyzeOrientationButton;
    QPushButton *repairOrientationButton;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QFrame *line_2;
    QHBoxLayout *hboxLayout3;
    QCheckBox *checkDuplicatedFacesButton;
    QSpacerItem *spacerItem1;
    QPushButton *analyzeDuplicatedFacesButton;
    QPushButton *repairDuplicatedFacesButton;
    QHBoxLayout *hboxLayout4;
    QLabel *label_3;
    QFrame *line_3;
    QHBoxLayout *hboxLayout5;
    QCheckBox *checkDuplicatedPointsButton;
    QSpacerItem *spacerItem2;
    QPushButton *analyzeDuplicatedPointsButton;
    QPushButton *repairDuplicatedPointsButton;
    QHBoxLayout *hboxLayout6;
    QLabel *label_4;
    QFrame *line_4;
    QHBoxLayout *hboxLayout7;
    QCheckBox *checkNonmanifoldsButton;
    QSpacerItem *spacerItem3;
    QPushButton *analyzeNonmanifoldsButton;
    QPushButton *repairNonmanifoldsButton;
    QHBoxLayout *hboxLayout8;
    QLabel *label_5;
    QFrame *line_5;
    QHBoxLayout *hboxLayout9;
    QCheckBox *checkDegenerationButton;
    QSpacerItem *spacerItem4;
    QPushButton *analyzeDegeneratedButton;
    QPushButton *repairDegeneratedButton;
    QHBoxLayout *hboxLayout10;
    QLabel *label_6;
    QFrame *line_6;
    QHBoxLayout *hboxLayout11;
    QCheckBox *checkIndicesButton;
    QSpacerItem *spacerItem5;
    QPushButton *analyzeIndicesButton;
    QPushButton *repairIndicesButton;
    QHBoxLayout *hboxLayout12;
    QLabel *label_7;
    QFrame *line_7;
    QHBoxLayout *hboxLayout13;
    QCheckBox *checkSelfIntersectionButton;
    QSpacerItem *spacerItem6;
    QPushButton *analyzeSelfIntersectionButton;
    QPushButton *repairSelfIntersectionButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QFrame *line_9;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkFoldsButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *analyzeFoldsButton;
    QPushButton *repairFoldsButton;
    QHBoxLayout *hboxLayout14;
    QLabel *label_8;
    QFrame *line_8;
    QHBoxLayout *hboxLayout15;
    QCheckBox *checkRepeatButton;
    QSpacerItem *spacerItem7;
    QPushButton *analyzeAllTogether;
    QPushButton *repairAllTogether;
    QSpacerItem *spacerItem8;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBoxInfo;
    QGridLayout *gridLayout1;
    QPushButton *refreshButton;
    QComboBox *meshNameButton;
    QGridLayout *gridLayout2;
    QLabel *textLabel1;
    QSpacerItem *spacerItem9;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QSpacerItem *spacerItem10;
    QLabel *textLabel5;
    QLabel *textLabel3;
    QSpacerItem *spacerItem11;
    QLabel *textLabel6;

    void setupUi(QDialog *MeshGui__DlgEvaluateMesh)
    {
        if (MeshGui__DlgEvaluateMesh->objectName().isEmpty())
            MeshGui__DlgEvaluateMesh->setObjectName("MeshGui__DlgEvaluateMesh");
        MeshGui__DlgEvaluateMesh->resize(371, 715);
        MeshGui__DlgEvaluateMesh->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(MeshGui__DlgEvaluateMesh);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(MeshGui__DlgEvaluateMesh);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(label);

        line = new QFrame(MeshGui__DlgEvaluateMesh);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout->addWidget(line);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName("hboxLayout1");
        checkOrientationButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkOrientationButton->setObjectName("checkOrientationButton");

        hboxLayout1->addWidget(checkOrientationButton);

        spacerItem = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem);

        analyzeOrientationButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeOrientationButton->setObjectName("analyzeOrientationButton");

        hboxLayout1->addWidget(analyzeOrientationButton);

        repairOrientationButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairOrientationButton->setObjectName("repairOrientationButton");
        repairOrientationButton->setEnabled(false);

        hboxLayout1->addWidget(repairOrientationButton);


        gridLayout->addLayout(hboxLayout1, 2, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName("hboxLayout2");
        label_2 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        hboxLayout2->addWidget(label_2);

        line_2 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout2->addWidget(line_2);


        gridLayout->addLayout(hboxLayout2, 3, 0, 1, 1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName("hboxLayout3");
        checkDuplicatedFacesButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkDuplicatedFacesButton->setObjectName("checkDuplicatedFacesButton");

        hboxLayout3->addWidget(checkDuplicatedFacesButton);

        spacerItem1 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem1);

        analyzeDuplicatedFacesButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeDuplicatedFacesButton->setObjectName("analyzeDuplicatedFacesButton");

        hboxLayout3->addWidget(analyzeDuplicatedFacesButton);

        repairDuplicatedFacesButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairDuplicatedFacesButton->setObjectName("repairDuplicatedFacesButton");
        repairDuplicatedFacesButton->setEnabled(false);

        hboxLayout3->addWidget(repairDuplicatedFacesButton);


        gridLayout->addLayout(hboxLayout3, 4, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName("hboxLayout4");
        label_3 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        hboxLayout4->addWidget(label_3);

        line_3 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout4->addWidget(line_3);


        gridLayout->addLayout(hboxLayout4, 5, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        hboxLayout5->setObjectName("hboxLayout5");
        checkDuplicatedPointsButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkDuplicatedPointsButton->setObjectName("checkDuplicatedPointsButton");

        hboxLayout5->addWidget(checkDuplicatedPointsButton);

        spacerItem2 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout5->addItem(spacerItem2);

        analyzeDuplicatedPointsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeDuplicatedPointsButton->setObjectName("analyzeDuplicatedPointsButton");

        hboxLayout5->addWidget(analyzeDuplicatedPointsButton);

        repairDuplicatedPointsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairDuplicatedPointsButton->setObjectName("repairDuplicatedPointsButton");
        repairDuplicatedPointsButton->setEnabled(false);

        hboxLayout5->addWidget(repairDuplicatedPointsButton);


        gridLayout->addLayout(hboxLayout5, 6, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setContentsMargins(0, 0, 0, 0);
        hboxLayout6->setObjectName("hboxLayout6");
        label_4 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        hboxLayout6->addWidget(label_4);

        line_4 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout6->addWidget(line_4);


        gridLayout->addLayout(hboxLayout6, 7, 0, 1, 1);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setContentsMargins(0, 0, 0, 0);
        hboxLayout7->setObjectName("hboxLayout7");
        checkNonmanifoldsButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkNonmanifoldsButton->setObjectName("checkNonmanifoldsButton");

        hboxLayout7->addWidget(checkNonmanifoldsButton);

        spacerItem3 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout7->addItem(spacerItem3);

        analyzeNonmanifoldsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeNonmanifoldsButton->setObjectName("analyzeNonmanifoldsButton");

        hboxLayout7->addWidget(analyzeNonmanifoldsButton);

        repairNonmanifoldsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairNonmanifoldsButton->setObjectName("repairNonmanifoldsButton");
        repairNonmanifoldsButton->setEnabled(false);

        hboxLayout7->addWidget(repairNonmanifoldsButton);


        gridLayout->addLayout(hboxLayout7, 8, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setContentsMargins(0, 0, 0, 0);
        hboxLayout8->setObjectName("hboxLayout8");
        label_5 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        hboxLayout8->addWidget(label_5);

        line_5 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout8->addWidget(line_5);


        gridLayout->addLayout(hboxLayout8, 9, 0, 1, 1);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setContentsMargins(0, 0, 0, 0);
        hboxLayout9->setObjectName("hboxLayout9");
        checkDegenerationButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkDegenerationButton->setObjectName("checkDegenerationButton");

        hboxLayout9->addWidget(checkDegenerationButton);

        spacerItem4 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout9->addItem(spacerItem4);

        analyzeDegeneratedButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeDegeneratedButton->setObjectName("analyzeDegeneratedButton");

        hboxLayout9->addWidget(analyzeDegeneratedButton);

        repairDegeneratedButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairDegeneratedButton->setObjectName("repairDegeneratedButton");
        repairDegeneratedButton->setEnabled(false);

        hboxLayout9->addWidget(repairDegeneratedButton);


        gridLayout->addLayout(hboxLayout9, 10, 0, 1, 1);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setContentsMargins(0, 0, 0, 0);
        hboxLayout10->setObjectName("hboxLayout10");
        label_6 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_6->setObjectName("label_6");
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        hboxLayout10->addWidget(label_6);

        line_6 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout10->addWidget(line_6);


        gridLayout->addLayout(hboxLayout10, 11, 0, 1, 1);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setContentsMargins(0, 0, 0, 0);
        hboxLayout11->setObjectName("hboxLayout11");
        checkIndicesButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkIndicesButton->setObjectName("checkIndicesButton");

        hboxLayout11->addWidget(checkIndicesButton);

        spacerItem5 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout11->addItem(spacerItem5);

        analyzeIndicesButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeIndicesButton->setObjectName("analyzeIndicesButton");

        hboxLayout11->addWidget(analyzeIndicesButton);

        repairIndicesButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairIndicesButton->setObjectName("repairIndicesButton");
        repairIndicesButton->setEnabled(false);

        hboxLayout11->addWidget(repairIndicesButton);


        gridLayout->addLayout(hboxLayout11, 12, 0, 1, 1);

        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setContentsMargins(0, 0, 0, 0);
        hboxLayout12->setObjectName("hboxLayout12");
        label_7 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_7->setObjectName("label_7");
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        hboxLayout12->addWidget(label_7);

        line_7 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout12->addWidget(line_7);


        gridLayout->addLayout(hboxLayout12, 13, 0, 1, 1);

        hboxLayout13 = new QHBoxLayout();
        hboxLayout13->setSpacing(6);
        hboxLayout13->setContentsMargins(0, 0, 0, 0);
        hboxLayout13->setObjectName("hboxLayout13");
        checkSelfIntersectionButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkSelfIntersectionButton->setObjectName("checkSelfIntersectionButton");

        hboxLayout13->addWidget(checkSelfIntersectionButton);

        spacerItem6 = new QSpacerItem(51, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout13->addItem(spacerItem6);

        analyzeSelfIntersectionButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeSelfIntersectionButton->setObjectName("analyzeSelfIntersectionButton");

        hboxLayout13->addWidget(analyzeSelfIntersectionButton);

        repairSelfIntersectionButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairSelfIntersectionButton->setObjectName("repairSelfIntersectionButton");
        repairSelfIntersectionButton->setEnabled(false);

        hboxLayout13->addWidget(repairSelfIntersectionButton);


        gridLayout->addLayout(hboxLayout13, 14, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_9 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_9->setObjectName("label_9");

        horizontalLayout_2->addWidget(label_9);

        line_9 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::HLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_9);


        gridLayout->addLayout(horizontalLayout_2, 15, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        checkFoldsButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkFoldsButton->setObjectName("checkFoldsButton");

        horizontalLayout->addWidget(checkFoldsButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        analyzeFoldsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeFoldsButton->setObjectName("analyzeFoldsButton");

        horizontalLayout->addWidget(analyzeFoldsButton);

        repairFoldsButton = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairFoldsButton->setObjectName("repairFoldsButton");
        repairFoldsButton->setEnabled(false);

        horizontalLayout->addWidget(repairFoldsButton);


        gridLayout->addLayout(horizontalLayout, 16, 0, 1, 1);

        hboxLayout14 = new QHBoxLayout();
        hboxLayout14->setSpacing(6);
        hboxLayout14->setContentsMargins(0, 0, 0, 0);
        hboxLayout14->setObjectName("hboxLayout14");
        label_8 = new QLabel(MeshGui__DlgEvaluateMesh);
        label_8->setObjectName("label_8");
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        hboxLayout14->addWidget(label_8);

        line_8 = new QFrame(MeshGui__DlgEvaluateMesh);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::HLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        hboxLayout14->addWidget(line_8);


        gridLayout->addLayout(hboxLayout14, 17, 0, 1, 1);

        hboxLayout15 = new QHBoxLayout();
        hboxLayout15->setSpacing(6);
        hboxLayout15->setContentsMargins(0, 0, 0, 0);
        hboxLayout15->setObjectName("hboxLayout15");
        checkRepeatButton = new QCheckBox(MeshGui__DlgEvaluateMesh);
        checkRepeatButton->setObjectName("checkRepeatButton");

        hboxLayout15->addWidget(checkRepeatButton);

        spacerItem7 = new QSpacerItem(72, 26, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout15->addItem(spacerItem7);

        analyzeAllTogether = new QPushButton(MeshGui__DlgEvaluateMesh);
        analyzeAllTogether->setObjectName("analyzeAllTogether");

        hboxLayout15->addWidget(analyzeAllTogether);

        repairAllTogether = new QPushButton(MeshGui__DlgEvaluateMesh);
        repairAllTogether->setObjectName("repairAllTogether");
        repairAllTogether->setEnabled(false);

        hboxLayout15->addWidget(repairAllTogether);


        gridLayout->addLayout(hboxLayout15, 18, 0, 1, 1);

        spacerItem8 = new QSpacerItem(353, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(spacerItem8, 19, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MeshGui__DlgEvaluateMesh);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Close|QDialogButtonBox::StandardButton::Open|QDialogButtonBox::StandardButton::Reset);

        gridLayout->addWidget(buttonBox, 20, 0, 1, 1);

        groupBoxInfo = new QGroupBox(MeshGui__DlgEvaluateMesh);
        groupBoxInfo->setObjectName("groupBoxInfo");
        gridLayout1 = new QGridLayout(groupBoxInfo);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName("gridLayout1");
        refreshButton = new QPushButton(groupBoxInfo);
        refreshButton->setObjectName("refreshButton");

        gridLayout1->addWidget(refreshButton, 0, 2, 1, 1);

        meshNameButton = new QComboBox(groupBoxInfo);
        meshNameButton->setObjectName("meshNameButton");

        gridLayout1->addWidget(meshNameButton, 0, 0, 1, 2);

        gridLayout2 = new QGridLayout();
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(0, 0, 0, 0);
        gridLayout2->setObjectName("gridLayout2");
        textLabel1 = new QLabel(groupBoxInfo);
        textLabel1->setObjectName("textLabel1");

        gridLayout2->addWidget(textLabel1, 0, 0, 1, 1);

        spacerItem9 = new QSpacerItem(16, 21, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem9, 0, 1, 1, 1);

        textLabel4 = new QLabel(groupBoxInfo);
        textLabel4->setObjectName("textLabel4");
        textLabel4->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout2->addWidget(textLabel4, 0, 2, 1, 1);

        textLabel2 = new QLabel(groupBoxInfo);
        textLabel2->setObjectName("textLabel2");

        gridLayout2->addWidget(textLabel2, 1, 0, 1, 1);

        spacerItem10 = new QSpacerItem(26, 21, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem10, 1, 1, 1, 1);

        textLabel5 = new QLabel(groupBoxInfo);
        textLabel5->setObjectName("textLabel5");
        textLabel5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout2->addWidget(textLabel5, 1, 2, 1, 1);

        textLabel3 = new QLabel(groupBoxInfo);
        textLabel3->setObjectName("textLabel3");

        gridLayout2->addWidget(textLabel3, 2, 0, 1, 1);

        spacerItem11 = new QSpacerItem(16, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout2->addItem(spacerItem11, 2, 1, 1, 1);

        textLabel6 = new QLabel(groupBoxInfo);
        textLabel6->setObjectName("textLabel6");
        textLabel6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout2->addWidget(textLabel6, 2, 2, 1, 1);


        gridLayout1->addLayout(gridLayout2, 1, 0, 1, 2);


        gridLayout->addWidget(groupBoxInfo, 0, 0, 1, 1);

        QWidget::setTabOrder(checkOrientationButton, analyzeOrientationButton);
        QWidget::setTabOrder(analyzeOrientationButton, repairOrientationButton);
        QWidget::setTabOrder(repairOrientationButton, checkDuplicatedFacesButton);
        QWidget::setTabOrder(checkDuplicatedFacesButton, analyzeDuplicatedFacesButton);
        QWidget::setTabOrder(analyzeDuplicatedFacesButton, repairDuplicatedFacesButton);
        QWidget::setTabOrder(repairDuplicatedFacesButton, checkDuplicatedPointsButton);
        QWidget::setTabOrder(checkDuplicatedPointsButton, analyzeDuplicatedPointsButton);
        QWidget::setTabOrder(analyzeDuplicatedPointsButton, repairDuplicatedPointsButton);
        QWidget::setTabOrder(repairDuplicatedPointsButton, checkNonmanifoldsButton);
        QWidget::setTabOrder(checkNonmanifoldsButton, analyzeNonmanifoldsButton);
        QWidget::setTabOrder(analyzeNonmanifoldsButton, repairNonmanifoldsButton);
        QWidget::setTabOrder(repairNonmanifoldsButton, checkDegenerationButton);
        QWidget::setTabOrder(checkDegenerationButton, analyzeDegeneratedButton);
        QWidget::setTabOrder(analyzeDegeneratedButton, repairDegeneratedButton);
        QWidget::setTabOrder(repairDegeneratedButton, checkIndicesButton);
        QWidget::setTabOrder(checkIndicesButton, analyzeIndicesButton);
        QWidget::setTabOrder(analyzeIndicesButton, repairIndicesButton);

        retranslateUi(MeshGui__DlgEvaluateMesh);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, MeshGui__DlgEvaluateMesh, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(MeshGui__DlgEvaluateMesh);
    } // setupUi

    void retranslateUi(QDialog *MeshGui__DlgEvaluateMesh)
    {
        MeshGui__DlgEvaluateMesh->setWindowTitle(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Evaluate and Repair Mesh", nullptr));
        label->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Orientation", nullptr));
        checkOrientationButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeOrientationButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairOrientationButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_2->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Duplicated faces", nullptr));
        checkDuplicatedFacesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeDuplicatedFacesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairDuplicatedFacesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_3->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Duplicated points", nullptr));
        checkDuplicatedPointsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeDuplicatedPointsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairDuplicatedPointsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_4->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Non-manifolds", nullptr));
        checkNonmanifoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeNonmanifoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairNonmanifoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_5->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Degenerated faces", nullptr));
        checkDegenerationButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeDegeneratedButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairDegeneratedButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_6->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Face indices", nullptr));
        checkIndicesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeIndicesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairIndicesButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_7->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Self-intersections", nullptr));
        checkSelfIntersectionButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeSelfIntersectionButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairSelfIntersectionButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_9->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Folds on surface", nullptr));
        checkFoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        analyzeFoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairFoldsButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        label_8->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "All above tests together", nullptr));
        checkRepeatButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repetitive repair", nullptr));
        analyzeAllTogether->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Analyze", nullptr));
        repairAllTogether->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Repair", nullptr));
        groupBoxInfo->setTitle(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Mesh Information", nullptr));
        refreshButton->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Refresh", nullptr));
        textLabel1->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Number of faces", nullptr));
        textLabel4->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        textLabel2->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Number of edges", nullptr));
        textLabel5->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
        textLabel3->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "Number of points", nullptr));
        textLabel6->setText(QCoreApplication::translate("MeshGui::DlgEvaluateMesh", "No information", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class DlgEvaluateMesh: public Ui_DlgEvaluateMesh {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_DLGEVALUATEMESH_H
