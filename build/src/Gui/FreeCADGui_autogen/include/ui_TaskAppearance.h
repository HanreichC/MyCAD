/********************************************************************************
** Form generated from reading UI file 'TaskAppearance.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKAPPEARANCE_H
#define UI_TASKAPPEARANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {
namespace TaskView {

class Ui_TaskAppearance
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QComboBox *changeMode;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabel1_3;
    QComboBox *changePlot;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel2;
    QSpacerItem *spacerItem;
    QSpinBox *spinPointSize;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel3;
    QSpacerItem *spacerItem1;
    QSpinBox *spinLineWidth;
    QLabel *textLabel1_2;
    QHBoxLayout *hboxLayout4;
    QSlider *horizontalSlider;
    QSpinBox *spinTransparency;

    void setupUi(QWidget *Gui__TaskView__TaskAppearance)
    {
        if (Gui__TaskView__TaskAppearance->objectName().isEmpty())
            Gui__TaskView__TaskAppearance->setObjectName("Gui__TaskView__TaskAppearance");
        Gui__TaskView__TaskAppearance->resize(193, 174);
        vboxLayout = new QVBoxLayout(Gui__TaskView__TaskAppearance);
#ifndef Q_OS_MACOS
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MACOS
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName("hboxLayout");
        textLabel1 = new QLabel(Gui__TaskView__TaskAppearance);
        textLabel1->setObjectName("textLabel1");

        hboxLayout->addWidget(textLabel1);

        changeMode = new QComboBox(Gui__TaskView__TaskAppearance);
        changeMode->setObjectName("changeMode");

        hboxLayout->addWidget(changeMode);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName("hboxLayout1");
        textLabel1_3 = new QLabel(Gui__TaskView__TaskAppearance);
        textLabel1_3->setObjectName("textLabel1_3");
        textLabel1_3->setEnabled(false);

        hboxLayout1->addWidget(textLabel1_3);

        changePlot = new QComboBox(Gui__TaskView__TaskAppearance);
        changePlot->setObjectName("changePlot");
        changePlot->setEnabled(false);

        hboxLayout1->addWidget(changePlot);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName("hboxLayout2");
        textLabel2 = new QLabel(Gui__TaskView__TaskAppearance);
        textLabel2->setObjectName("textLabel2");

        hboxLayout2->addWidget(textLabel2);

        spacerItem = new QSpacerItem(71, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem);

        spinPointSize = new QSpinBox(Gui__TaskView__TaskAppearance);
        spinPointSize->setObjectName("spinPointSize");
        spinPointSize->setMaximum(64);
        spinPointSize->setMinimum(1);
        spinPointSize->setValue(2);

        hboxLayout2->addWidget(spinPointSize);


        vboxLayout->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout3->setSpacing(6);
#endif
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName("hboxLayout3");
        textLabel3 = new QLabel(Gui__TaskView__TaskAppearance);
        textLabel3->setObjectName("textLabel3");

        hboxLayout3->addWidget(textLabel3);

        spacerItem1 = new QSpacerItem(71, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem1);

        spinLineWidth = new QSpinBox(Gui__TaskView__TaskAppearance);
        spinLineWidth->setObjectName("spinLineWidth");
        spinLineWidth->setMaximum(64);
        spinLineWidth->setMinimum(1);
        spinLineWidth->setValue(2);

        hboxLayout3->addWidget(spinLineWidth);


        vboxLayout->addLayout(hboxLayout3);

        textLabel1_2 = new QLabel(Gui__TaskView__TaskAppearance);
        textLabel1_2->setObjectName("textLabel1_2");

        vboxLayout->addWidget(textLabel1_2);

        hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MACOS
        hboxLayout4->setSpacing(6);
#endif
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName("hboxLayout4");
        horizontalSlider = new QSlider(Gui__TaskView__TaskAppearance);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        hboxLayout4->addWidget(horizontalSlider);

        spinTransparency = new QSpinBox(Gui__TaskView__TaskAppearance);
        spinTransparency->setObjectName("spinTransparency");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinTransparency->sizePolicy().hasHeightForWidth());
        spinTransparency->setSizePolicy(sizePolicy);
        spinTransparency->setMaximum(100);
        spinTransparency->setSingleStep(5);

        hboxLayout4->addWidget(spinTransparency);


        vboxLayout->addLayout(hboxLayout4);


        retranslateUi(Gui__TaskView__TaskAppearance);
        QObject::connect(horizontalSlider, &QSlider::valueChanged, spinTransparency, &QSpinBox::setValue);
        QObject::connect(spinTransparency, &QSpinBox::valueChanged, horizontalSlider, &QSlider::setValue);

        QMetaObject::connectSlotsByName(Gui__TaskView__TaskAppearance);
    } // setupUi

    void retranslateUi(QWidget *Gui__TaskView__TaskAppearance)
    {
        Gui__TaskView__TaskAppearance->setWindowTitle(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Appearance", nullptr));
        textLabel1->setText(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Document window", nullptr));
        textLabel1_3->setText(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Plot mode", nullptr));
        textLabel2->setText(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Point size", nullptr));
        textLabel3->setText(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Line width", nullptr));
        textLabel1_2->setText(QCoreApplication::translate("Gui::TaskView::TaskAppearance", "Transparency", nullptr));
    } // retranslateUi

};

} // namespace TaskView
} // namespace Gui

namespace Gui {
namespace TaskView {
namespace Ui {
    class TaskAppearance: public Ui_TaskAppearance {};
} // namespace Ui
} // namespace TaskView
} // namespace Gui

#endif // UI_TASKAPPEARANCE_H
