/********************************************************************************
** Form generated from reading UI file 'TaskSketcherConstraints.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKSKETCHERCONSTRAINTS_H
#define UI_TASKSKETCHERCONSTRAINTS_H

#include <QListWidget>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace SketcherGui {

class Ui_TaskSketcherConstraints
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout1;
    QCheckBox *filterBox;
    QToolButton *filterButton;
    QToolButton *showHideButton;
    QToolButton *settingsButton;
    ConstraintView *listWidgetConstraints;

    void setupUi(QWidget *SketcherGui__TaskSketcherConstraints)
    {
        if (SketcherGui__TaskSketcherConstraints->objectName().isEmpty())
            SketcherGui__TaskSketcherConstraints->setObjectName("SketcherGui__TaskSketcherConstraints");
        SketcherGui__TaskSketcherConstraints->resize(299, 350);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SketcherGui__TaskSketcherConstraints->sizePolicy().hasHeightForWidth());
        SketcherGui__TaskSketcherConstraints->setSizePolicy(sizePolicy);
        SketcherGui__TaskSketcherConstraints->setMaximumSize(QSize(16777215, 350));
        SketcherGui__TaskSketcherConstraints->setWindowTitle(QString::fromUtf8("Form"));
        verticalLayout = new QVBoxLayout(SketcherGui__TaskSketcherConstraints);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout1 = new QHBoxLayout();
        horizontalLayout1->setObjectName("horizontalLayout1");
        filterBox = new QCheckBox(SketcherGui__TaskSketcherConstraints);
        filterBox->setObjectName("filterBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filterBox->sizePolicy().hasHeightForWidth());
        filterBox->setSizePolicy(sizePolicy1);
        filterBox->setStyleSheet(QString::fromUtf8("padding-right: 0px; margin-right: 0px"));
        filterBox->setText(QString::fromUtf8(""));

        horizontalLayout1->addWidget(filterBox);

        filterButton = new QToolButton(SketcherGui__TaskSketcherConstraints);
        filterButton->setObjectName("filterButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(filterButton->sizePolicy().hasHeightForWidth());
        filterButton->setSizePolicy(sizePolicy2);
        filterButton->setStyleSheet(QString::fromUtf8("padding-left: 0px; margin-left: 0px"));
        filterButton->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout1->addWidget(filterButton);

        showHideButton = new QToolButton(SketcherGui__TaskSketcherConstraints);
        showHideButton->setObjectName("showHideButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(showHideButton->sizePolicy().hasHeightForWidth());
        showHideButton->setSizePolicy(sizePolicy3);
        showHideButton->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Std_ToggleVisibility.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        showHideButton->setIcon(icon);

        horizontalLayout1->addWidget(showHideButton);

        settingsButton = new QToolButton(SketcherGui__TaskSketcherConstraints);
        settingsButton->setObjectName("settingsButton");
        sizePolicy3.setHeightForWidth(settingsButton->sizePolicy().hasHeightForWidth());
        settingsButton->setSizePolicy(sizePolicy3);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/dialogs/Sketcher_Settings.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon1);
        settingsButton->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout1->addWidget(settingsButton);


        verticalLayout->addLayout(horizontalLayout1);

        listWidgetConstraints = new ConstraintView(SketcherGui__TaskSketcherConstraints);
        listWidgetConstraints->setObjectName("listWidgetConstraints");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidgetConstraints->sizePolicy().hasHeightForWidth());
        listWidgetConstraints->setSizePolicy(sizePolicy4);
        listWidgetConstraints->setIconSize(QSize(24, 24));
        listWidgetConstraints->setModelColumn(0);

        verticalLayout->addWidget(listWidgetConstraints);


        retranslateUi(SketcherGui__TaskSketcherConstraints);

        QMetaObject::connectSlotsByName(SketcherGui__TaskSketcherConstraints);
    } // setupUi

    void retranslateUi(QWidget *SketcherGui__TaskSketcherConstraints)
    {
#if QT_CONFIG(tooltip)
        filterBox->setToolTip(QCoreApplication::translate("SketcherGui::TaskSketcherConstraints", "Toggles the chosen constraint filters", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        filterButton->setToolTip(QCoreApplication::translate("SketcherGui::TaskSketcherConstraints", "Filters constraints by type", nullptr));
#endif // QT_CONFIG(tooltip)
        filterButton->setText(QCoreApplication::translate("SketcherGui::TaskSketcherConstraints", "Filter", nullptr));
#if QT_CONFIG(tooltip)
        showHideButton->setToolTip(QCoreApplication::translate("SketcherGui::TaskSketcherConstraints", "Toggles the visibility of all listed constraints from the 3D view", nullptr));
#endif // QT_CONFIG(tooltip)
        showHideButton->setText(QString());
#if QT_CONFIG(tooltip)
        settingsButton->setToolTip(QCoreApplication::translate("SketcherGui::TaskSketcherConstraints", "Settings", nullptr));
#endif // QT_CONFIG(tooltip)
        settingsButton->setText(QString());
        (void)SketcherGui__TaskSketcherConstraints;
    } // retranslateUi

};

} // namespace SketcherGui

namespace SketcherGui {
namespace Ui {
    class TaskSketcherConstraints: public Ui_TaskSketcherConstraints {};
} // namespace Ui
} // namespace SketcherGui

#endif // UI_TASKSKETCHERCONSTRAINTS_H
