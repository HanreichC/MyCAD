/********************************************************************************
** Form generated from reading UI file 'Selection.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_H
#define UI_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

namespace MeshGui {

class Ui_Selection
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addSelection;
    QPushButton *clearSelection;
    QCheckBox *visibleTriangles;
    QCheckBox *screenTriangles;
    QLabel *label;

    void setupUi(QWidget *MeshGui__Selection)
    {
        if (MeshGui__Selection->objectName().isEmpty())
            MeshGui__Selection->setObjectName("MeshGui__Selection");
        MeshGui__Selection->resize(304, 143);
        gridLayout_2 = new QGridLayout(MeshGui__Selection);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(MeshGui__Selection);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer = new QSpacerItem(101, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        addSelection = new QPushButton(groupBox);
        addSelection->setObjectName("addSelection");

        gridLayout->addWidget(addSelection, 0, 1, 1, 1);

        clearSelection = new QPushButton(groupBox);
        clearSelection->setObjectName("clearSelection");

        gridLayout->addWidget(clearSelection, 0, 2, 1, 1);

        visibleTriangles = new QCheckBox(groupBox);
        visibleTriangles->setObjectName("visibleTriangles");
        visibleTriangles->setChecked(false);

        gridLayout->addWidget(visibleTriangles, 1, 0, 1, 2);

        screenTriangles = new QCheckBox(groupBox);
        screenTriangles->setObjectName("screenTriangles");
        screenTriangles->setChecked(true);

        gridLayout->addWidget(screenTriangles, 2, 0, 1, 3);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 3, 0, 1, 3);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(MeshGui__Selection);

        QMetaObject::connectSlotsByName(MeshGui__Selection);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__Selection)
    {
        MeshGui__Selection->setWindowTitle(QCoreApplication::translate("MeshGui::Selection", "Selection", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MeshGui::Selection", "Selection", nullptr));
        addSelection->setText(QCoreApplication::translate("MeshGui::Selection", "Add", nullptr));
        clearSelection->setText(QCoreApplication::translate("MeshGui::Selection", "Clear", nullptr));
        visibleTriangles->setText(QCoreApplication::translate("MeshGui::Selection", "Accept only visible triangles", nullptr));
        screenTriangles->setText(QCoreApplication::translate("MeshGui::Selection", "Accept only triangles with screen-facing normals", nullptr));
        label->setText(QString());
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class Selection: public Ui_Selection {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_SELECTION_H
