/********************************************************************************
** Form generated from reading UI file 'DlgActions.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGACTIONS_H
#define UI_DLGACTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/Widgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgCustomActions
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *GroupBox7;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QTreeWidget *actionListWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *TextLabel1_3;
    QLabel *TextLabel3;
    QLabel *TextLabel2_2;
    QLabel *TextLabel3_2;
    QLabel *TextLabel2;
    QLabel *TextLabel1;
    Gui::AccelLineEdit *actionAccel;
    QSpacerItem *horizontalSpacer;
    QLabel *TextLabel5_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *buttonChoosePixmap;
    QLabel *pixmapLabel;
    QSpacerItem *spacerItem;
    QComboBox *actionMacros;
    QLineEdit *actionMenu;
    QLineEdit *actionToolTip;
    QLineEdit *actionStatus;
    QLineEdit *actionWhatsThis;
    QSpacerItem *spacerItem1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonAddAction;
    QPushButton *buttonRemoveAction;
    QPushButton *buttonReplaceAction;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *Gui__Dialog__DlgCustomActions)
    {
        if (Gui__Dialog__DlgCustomActions->objectName().isEmpty())
            Gui__Dialog__DlgCustomActions->setObjectName("Gui__Dialog__DlgCustomActions");
        Gui__Dialog__DlgCustomActions->resize(564, 383);
        horizontalLayout_3 = new QHBoxLayout(Gui__Dialog__DlgCustomActions);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        GroupBox7 = new QGroupBox(Gui__Dialog__DlgCustomActions);
        GroupBox7->setObjectName("GroupBox7");
        verticalLayout_2 = new QVBoxLayout(GroupBox7);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        splitter = new QSplitter(GroupBox7);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        actionListWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        actionListWidget->setHeaderItem(__qtreewidgetitem);
        actionListWidget->setObjectName("actionListWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(actionListWidget->sizePolicy().hasHeightForWidth());
        actionListWidget->setSizePolicy(sizePolicy);
        actionListWidget->setRootIsDecorated(false);
        splitter->addWidget(actionListWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        sizePolicy.setHeightForWidth(layoutWidget->sizePolicy().hasHeightForWidth());
        layoutWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        TextLabel1_3 = new QLabel(layoutWidget);
        TextLabel1_3->setObjectName("TextLabel1_3");

        gridLayout->addWidget(TextLabel1_3, 0, 0, 1, 1);

        TextLabel3 = new QLabel(layoutWidget);
        TextLabel3->setObjectName("TextLabel3");

        gridLayout->addWidget(TextLabel3, 1, 0, 1, 1);

        TextLabel2_2 = new QLabel(layoutWidget);
        TextLabel2_2->setObjectName("TextLabel2_2");

        gridLayout->addWidget(TextLabel2_2, 2, 0, 1, 1);

        TextLabel3_2 = new QLabel(layoutWidget);
        TextLabel3_2->setObjectName("TextLabel3_2");

        gridLayout->addWidget(TextLabel3_2, 3, 0, 1, 1);

        TextLabel2 = new QLabel(layoutWidget);
        TextLabel2->setObjectName("TextLabel2");

        gridLayout->addWidget(TextLabel2, 4, 0, 1, 1);

        TextLabel1 = new QLabel(layoutWidget);
        TextLabel1->setObjectName("TextLabel1");

        gridLayout->addWidget(TextLabel1, 5, 0, 1, 1);

        actionAccel = new Gui::AccelLineEdit(layoutWidget);
        actionAccel->setObjectName("actionAccel");

        gridLayout->addWidget(actionAccel, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 2, 1, 1);

        TextLabel5_2 = new QLabel(layoutWidget);
        TextLabel5_2->setObjectName("TextLabel5_2");

        gridLayout->addWidget(TextLabel5_2, 6, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        buttonChoosePixmap = new QToolButton(layoutWidget);
        buttonChoosePixmap->setObjectName("buttonChoosePixmap");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonChoosePixmap->sizePolicy().hasHeightForWidth());
        buttonChoosePixmap->setSizePolicy(sizePolicy1);
        buttonChoosePixmap->setMinimumSize(QSize(40, 30));
        buttonChoosePixmap->setMaximumSize(QSize(40, 30));
        buttonChoosePixmap->setText(QString::fromUtf8("\342\200\246"));

        horizontalLayout->addWidget(buttonChoosePixmap);

        pixmapLabel = new QLabel(layoutWidget);
        pixmapLabel->setObjectName("pixmapLabel");
        pixmapLabel->setMinimumSize(QSize(40, 40));
        pixmapLabel->setMaximumSize(QSize(40, 40));
        pixmapLabel->setScaledContents(true);

        horizontalLayout->addWidget(pixmapLabel);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(spacerItem);


        gridLayout->addLayout(horizontalLayout, 6, 1, 1, 1);

        actionMacros = new QComboBox(layoutWidget);
        actionMacros->setObjectName("actionMacros");

        gridLayout->addWidget(actionMacros, 0, 1, 1, 2);

        actionMenu = new QLineEdit(layoutWidget);
        actionMenu->setObjectName("actionMenu");

        gridLayout->addWidget(actionMenu, 1, 1, 1, 2);

        actionToolTip = new QLineEdit(layoutWidget);
        actionToolTip->setObjectName("actionToolTip");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(actionToolTip->sizePolicy().hasHeightForWidth());
        actionToolTip->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(actionToolTip, 2, 1, 1, 2);

        actionStatus = new QLineEdit(layoutWidget);
        actionStatus->setObjectName("actionStatus");

        gridLayout->addWidget(actionStatus, 3, 1, 1, 2);

        actionWhatsThis = new QLineEdit(layoutWidget);
        actionWhatsThis->setObjectName("actionWhatsThis");

        gridLayout->addWidget(actionWhatsThis, 4, 1, 1, 2);


        verticalLayout->addLayout(gridLayout);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(spacerItem1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonAddAction = new QPushButton(layoutWidget);
        buttonAddAction->setObjectName("buttonAddAction");

        horizontalLayout_2->addWidget(buttonAddAction);

        buttonRemoveAction = new QPushButton(layoutWidget);
        buttonRemoveAction->setObjectName("buttonRemoveAction");

        horizontalLayout_2->addWidget(buttonRemoveAction);

        buttonReplaceAction = new QPushButton(layoutWidget);
        buttonReplaceAction->setObjectName("buttonReplaceAction");

        horizontalLayout_2->addWidget(buttonReplaceAction);

        spacerItem2 = new QSpacerItem(41, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(spacerItem2);


        verticalLayout->addLayout(horizontalLayout_2);

        splitter->addWidget(layoutWidget);

        verticalLayout_2->addWidget(splitter);


        horizontalLayout_3->addWidget(GroupBox7);

        QWidget::setTabOrder(actionMacros, actionMenu);
        QWidget::setTabOrder(actionMenu, actionToolTip);
        QWidget::setTabOrder(actionToolTip, actionStatus);
        QWidget::setTabOrder(actionStatus, actionWhatsThis);
        QWidget::setTabOrder(actionWhatsThis, actionAccel);
        QWidget::setTabOrder(actionAccel, buttonAddAction);
        QWidget::setTabOrder(buttonAddAction, buttonRemoveAction);

        retranslateUi(Gui__Dialog__DlgCustomActions);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgCustomActions);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgCustomActions)
    {
        Gui__Dialog__DlgCustomActions->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Macros", nullptr));
        GroupBox7->setTitle(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Setup Custom Macros", nullptr));
        TextLabel1_3->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Macro", nullptr));
        TextLabel3->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Menu text", nullptr));
        TextLabel2_2->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Tooltip", nullptr));
        TextLabel3_2->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Status text", nullptr));
        TextLabel2->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "What's this", nullptr));
        TextLabel1->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Accelerator", nullptr));
        TextLabel5_2->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Icon", nullptr));
#if QT_CONFIG(tooltip)
        buttonChoosePixmap->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Choose an icon", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonAddAction->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Add", nullptr));
        buttonRemoveAction->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Remove", nullptr));
        buttonReplaceAction->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomActions", "Replace", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgCustomActions: public Ui_DlgCustomActions {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGACTIONS_H
