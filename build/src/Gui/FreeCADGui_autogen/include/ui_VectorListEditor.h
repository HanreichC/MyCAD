/********************************************************************************
** Form generated from reading UI file 'VectorListEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VECTORLISTEDITOR_H
#define UI_VECTORLISTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {

class Ui_VectorListEditor
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QDoubleSpinBox *coordX;
    QLabel *label_3;
    QDoubleSpinBox *coordY;
    QLabel *label_4;
    QDoubleSpinBox *coordZ;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonMouse;
    QToolButton *toolButtonAdd;
    QToolButton *toolButtonRemove;
    QToolButton *toolButtonAccept;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableView *tableWidget;

    void setupUi(QDialog *Gui__VectorListEditor)
    {
        if (Gui__VectorListEditor->objectName().isEmpty())
            Gui__VectorListEditor->setObjectName("Gui__VectorListEditor");
        Gui__VectorListEditor->resize(288, 476);
        gridLayout_3 = new QGridLayout(Gui__VectorListEditor);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(Gui__VectorListEditor);
        label->setObjectName("label");
        label->setText(QString::fromUtf8("Id"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(Gui__VectorListEditor);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(1);

        gridLayout_2->addWidget(spinBox, 0, 1, 1, 1);

        label_2 = new QLabel(Gui__VectorListEditor);
        label_2->setObjectName("label_2");
        label_2->setText(QString::fromUtf8("X"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        coordX = new QDoubleSpinBox(Gui__VectorListEditor);
        coordX->setObjectName("coordX");

        gridLayout_2->addWidget(coordX, 1, 1, 1, 1);

        label_3 = new QLabel(Gui__VectorListEditor);
        label_3->setObjectName("label_3");
        label_3->setText(QString::fromUtf8("Y"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        coordY = new QDoubleSpinBox(Gui__VectorListEditor);
        coordY->setObjectName("coordY");

        gridLayout_2->addWidget(coordY, 2, 1, 1, 1);

        label_4 = new QLabel(Gui__VectorListEditor);
        label_4->setObjectName("label_4");
        label_4->setText(QString::fromUtf8("Z"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        coordZ = new QDoubleSpinBox(Gui__VectorListEditor);
        coordZ->setObjectName("coordZ");

        gridLayout_2->addWidget(coordZ, 3, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(47, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        buttonBox = new QDialogButtonBox(Gui__VectorListEditor);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        horizontalSpacer = new QSpacerItem(20, 17, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Gui__VectorListEditor);
        pushButton->setObjectName("pushButton");
        pushButton->setCheckable(true);

        verticalLayout->addWidget(pushButton);


        gridLayout_3->addLayout(verticalLayout, 0, 2, 2, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        toolButtonMouse = new QToolButton(Gui__VectorListEditor);
        toolButtonMouse->setObjectName("toolButtonMouse");
        toolButtonMouse->setText(QString::fromUtf8("\342\200\246"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/mouse_pointer.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonMouse->setIcon(icon);

        horizontalLayout->addWidget(toolButtonMouse);

        toolButtonAdd = new QToolButton(Gui__VectorListEditor);
        toolButtonAdd->setObjectName("toolButtonAdd");
        toolButtonAdd->setText(QString::fromUtf8("\342\200\246"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/list-add.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonAdd->setIcon(icon1);

        horizontalLayout->addWidget(toolButtonAdd);

        toolButtonRemove = new QToolButton(Gui__VectorListEditor);
        toolButtonRemove->setObjectName("toolButtonRemove");
        toolButtonRemove->setText(QString::fromUtf8("\342\200\246"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/list-remove.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonRemove->setIcon(icon2);

        horizontalLayout->addWidget(toolButtonRemove);

        toolButtonAccept = new QToolButton(Gui__VectorListEditor);
        toolButtonAccept->setObjectName("toolButtonAccept");
        toolButtonAccept->setText(QString::fromUtf8("\342\200\246"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/edit_OK.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonAccept->setIcon(icon3);

        horizontalLayout->addWidget(toolButtonAccept);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        widget = new QWidget(Gui__VectorListEditor);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 300));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableView(widget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->horizontalHeader()->setDefaultSectionSize(80);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget, 2, 0, 1, 3);

        QWidget::setTabOrder(spinBox, coordX);
        QWidget::setTabOrder(coordX, coordY);
        QWidget::setTabOrder(coordY, coordZ);
        QWidget::setTabOrder(coordZ, toolButtonMouse);
        QWidget::setTabOrder(toolButtonMouse, toolButtonAdd);
        QWidget::setTabOrder(toolButtonAdd, toolButtonRemove);
        QWidget::setTabOrder(toolButtonRemove, toolButtonAccept);
        QWidget::setTabOrder(toolButtonAccept, tableWidget);
        QWidget::setTabOrder(tableWidget, pushButton);

        retranslateUi(Gui__VectorListEditor);
        QObject::connect(pushButton, &QPushButton::toggled, widget, &QWidget::setVisible);

        QMetaObject::connectSlotsByName(Gui__VectorListEditor);
    } // setupUi

    void retranslateUi(QDialog *Gui__VectorListEditor)
    {
        Gui__VectorListEditor->setWindowTitle(QCoreApplication::translate("Gui::VectorListEditor", "Vectors", nullptr));
        pushButton->setText(QCoreApplication::translate("Gui::VectorListEditor", "Table", nullptr));
    } // retranslateUi

};

} // namespace Gui

namespace Gui {
namespace Ui {
    class VectorListEditor: public Ui_VectorListEditor {};
} // namespace Ui
} // namespace Gui

#endif // UI_VECTORLISTEDITOR_H
