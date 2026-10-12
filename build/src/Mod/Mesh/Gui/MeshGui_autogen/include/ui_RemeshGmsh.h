/********************************************************************************
** Form generated from reading UI file 'RemeshGmsh.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMESHGMSH_H
#define UI_REMESHGMSH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "Gui/FileDialog.h"
#include "Gui/PrefWidgets.h"
#include "Gui/QuantitySpinBox.h"

namespace MeshGui {

class Ui_RemeshGmsh
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *remeshParam;
    QGridLayout *gridLayout_2;
    QLabel *labelMethod;
    QComboBox *method;
    QLabel *labelMax;
    Gui::QuantitySpinBox *maxSize;
    QLabel *labelMin;
    Gui::QuantitySpinBox *minSize;
    QLabel *labelAngle;
    Gui::QuantitySpinBox *angle;
    QGroupBox *gmshOutput;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    Gui::PrefFileChooser *fileChooser;
    QPushButton *killButton;
    QTextEdit *outputWindow;
    QLabel *labelTime;
    QPushButton *clearButton;

    void setupUi(QWidget *MeshGui__RemeshGmsh)
    {
        if (MeshGui__RemeshGmsh->objectName().isEmpty())
            MeshGui__RemeshGmsh->setObjectName("MeshGui__RemeshGmsh");
        MeshGui__RemeshGmsh->resize(458, 506);
        gridLayout_3 = new QGridLayout(MeshGui__RemeshGmsh);
        gridLayout_3->setObjectName("gridLayout_3");
        remeshParam = new QGroupBox(MeshGui__RemeshGmsh);
        remeshParam->setObjectName("remeshParam");
        remeshParam->setMaximumSize(QSize(16777215, 1677215));
        gridLayout_2 = new QGridLayout(remeshParam);
        gridLayout_2->setObjectName("gridLayout_2");
        labelMethod = new QLabel(remeshParam);
        labelMethod->setObjectName("labelMethod");

        gridLayout_2->addWidget(labelMethod, 0, 0, 1, 1);

        method = new QComboBox(remeshParam);
        method->setObjectName("method");

        gridLayout_2->addWidget(method, 0, 1, 1, 1);

        labelMax = new QLabel(remeshParam);
        labelMax->setObjectName("labelMax");

        gridLayout_2->addWidget(labelMax, 1, 0, 1, 1);

        maxSize = new Gui::QuantitySpinBox(remeshParam);
        maxSize->setObjectName("maxSize");
        maxSize->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        maxSize->setMinimum(0.000000000000000);
        maxSize->setMaximum(1000.000000000000000);
        maxSize->setSingleStep(0.100000000000000);
        maxSize->setValue(0.000000000000000);

        gridLayout_2->addWidget(maxSize, 1, 1, 1, 1);

        labelMin = new QLabel(remeshParam);
        labelMin->setObjectName("labelMin");

        gridLayout_2->addWidget(labelMin, 2, 0, 1, 1);

        minSize = new Gui::QuantitySpinBox(remeshParam);
        minSize->setObjectName("minSize");
        minSize->setProperty("unit", QVariant(QString::fromUtf8("mm")));
        minSize->setMinimum(0.000000000000000);
        minSize->setMaximum(1000.000000000000000);
        minSize->setSingleStep(0.100000000000000);
        minSize->setValue(0.000000000000000);

        gridLayout_2->addWidget(minSize, 2, 1, 1, 1);

        labelAngle = new QLabel(remeshParam);
        labelAngle->setObjectName("labelAngle");

        gridLayout_2->addWidget(labelAngle, 3, 0, 1, 1);

        angle = new Gui::QuantitySpinBox(remeshParam);
        angle->setObjectName("angle");
        angle->setProperty("unit", QVariant(QString::fromUtf8("deg")));
        angle->setMinimum(20.000000000000000);
        angle->setMaximum(120.000000000000000);
        angle->setValue(40.000000000000000);

        gridLayout_2->addWidget(angle, 3, 1, 1, 1);


        gridLayout_3->addWidget(remeshParam, 0, 0, 1, 1);

        gmshOutput = new QGroupBox(MeshGui__RemeshGmsh);
        gmshOutput->setObjectName("gmshOutput");
        gmshOutput->setMaximumSize(QSize(16777215, 1677215));
        gridLayout = new QGridLayout(gmshOutput);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(gmshOutput);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        fileChooser = new Gui::PrefFileChooser(gmshOutput);
        fileChooser->setObjectName("fileChooser");
        fileChooser->setProperty("prefEntry", QVariant(QByteArray("gmshExe")));
        fileChooser->setProperty("prefPath", QVariant(QByteArray("Mod/Mesh/Meshing")));

        horizontalLayout->addWidget(fileChooser);

        killButton = new QPushButton(gmshOutput);
        killButton->setObjectName("killButton");
        killButton->setEnabled(false);

        horizontalLayout->addWidget(killButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        outputWindow = new QTextEdit(gmshOutput);
        outputWindow->setObjectName("outputWindow");
        outputWindow->setLineWrapMode(QTextEdit::NoWrap);

        gridLayout->addWidget(outputWindow, 1, 0, 1, 2);

        labelTime = new QLabel(gmshOutput);
        labelTime->setObjectName("labelTime");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        labelTime->setFont(font);

        gridLayout->addWidget(labelTime, 2, 0, 1, 1);

        clearButton = new QPushButton(gmshOutput);
        clearButton->setObjectName("clearButton");

        gridLayout->addWidget(clearButton, 2, 1, 1, 1);


        gridLayout_3->addWidget(gmshOutput, 1, 0, 1, 1);

        QWidget::setTabOrder(method, maxSize);
        QWidget::setTabOrder(maxSize, minSize);
        QWidget::setTabOrder(minSize, angle);
        QWidget::setTabOrder(angle, killButton);
        QWidget::setTabOrder(killButton, outputWindow);

        retranslateUi(MeshGui__RemeshGmsh);

        QMetaObject::connectSlotsByName(MeshGui__RemeshGmsh);
    } // setupUi

    void retranslateUi(QWidget *MeshGui__RemeshGmsh)
    {
        MeshGui__RemeshGmsh->setWindowTitle(QCoreApplication::translate("MeshGui::RemeshGmsh", "Remesh by Gmsh", nullptr));
        remeshParam->setTitle(QCoreApplication::translate("MeshGui::RemeshGmsh", "Remeshing Parameter", nullptr));
        labelMethod->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Meshing", nullptr));
        labelMax->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Max element size (0.0 = Auto)", nullptr));
        labelMin->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Min element size (0.0 = Auto)", nullptr));
        labelAngle->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Angle", nullptr));
        gmshOutput->setTitle(QCoreApplication::translate("MeshGui::RemeshGmsh", "Gmsh", nullptr));
        label->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Path", nullptr));
#if QT_CONFIG(tooltip)
        fileChooser->setToolTip(QCoreApplication::translate("MeshGui::RemeshGmsh", "Leave empty to use default gmsh executable", nullptr));
#endif // QT_CONFIG(tooltip)
        killButton->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Kill", nullptr));
        labelTime->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Time", nullptr));
        clearButton->setText(QCoreApplication::translate("MeshGui::RemeshGmsh", "Clear", nullptr));
    } // retranslateUi

};

} // namespace MeshGui

namespace MeshGui {
namespace Ui {
    class RemeshGmsh: public Ui_RemeshGmsh {};
} // namespace Ui
} // namespace MeshGui

#endif // UI_REMESHGMSH_H
