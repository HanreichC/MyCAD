/********************************************************************************
** Form generated from reading UI file 'DlgToolbars.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTOOLBARS_H
#define UI_DLGTOOLBARS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Gui {
namespace Dialog {

class Ui_DlgCustomToolbars
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QComboBox *categoryBox;
    QLineEdit *editCommand;
    QLabel *label_4;
    QTreeWidget *commandTreeWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *spacerItem;
    QPushButton *moveActionRightButton;
    QPushButton *moveActionLeftButton;
    QPushButton *moveActionUpButton;
    QPushButton *moveActionDownButton;
    QSpacerItem *spacerItem1;
    QVBoxLayout *verticalLayout;
    QComboBox *workbenchBox;
    QTreeWidget *toolbarTreeWidget;
    QVBoxLayout *vboxLayout;
    QSpacerItem *spacerItem2;
    QPushButton *newButton;
    QPushButton *renameButton;
    QPushButton *deleteButton;
    QSpacerItem *spacerItem3;
    QLabel *label;

    void setupUi(QWidget *Gui__Dialog__DlgCustomToolbars)
    {
        if (Gui__Dialog__DlgCustomToolbars->objectName().isEmpty())
            Gui__Dialog__DlgCustomToolbars->setObjectName("Gui__Dialog__DlgCustomToolbars");
        Gui__Dialog__DlgCustomToolbars->resize(736, 352);
        Gui__Dialog__DlgCustomToolbars->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(Gui__Dialog__DlgCustomToolbars);
        verticalLayout_3->setObjectName("verticalLayout_3");
        splitter = new QSplitter(Gui__Dialog__DlgCustomToolbars);
        splitter->setObjectName("splitter");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName("widget");
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        categoryBox = new QComboBox(widget);
        categoryBox->setObjectName("categoryBox");

        gridLayout_2->addWidget(categoryBox, 1, 1, 1, 1);

        editCommand = new QLineEdit(widget);
        editCommand->setObjectName("editCommand");

        gridLayout_2->addWidget(editCommand, 0, 0, 1, 2);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        commandTreeWidget = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        commandTreeWidget->setHeaderItem(__qtreewidgetitem);
        commandTreeWidget->setObjectName("commandTreeWidget");
        commandTreeWidget->setMinimumSize(QSize(400, 0));
        commandTreeWidget->setRootIsDecorated(false);

        gridLayout_2->addWidget(commandTreeWidget, 2, 0, 1, 2);

        splitter->addWidget(widget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        spacerItem = new QSpacerItem(33, 58, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(spacerItem);

        moveActionRightButton = new QPushButton(layoutWidget);
        moveActionRightButton->setObjectName("moveActionRightButton");
        moveActionRightButton->setEnabled(true);
        moveActionRightButton->setMinimumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/button_right.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        moveActionRightButton->setIcon(icon);

        verticalLayout_2->addWidget(moveActionRightButton);

        moveActionLeftButton = new QPushButton(layoutWidget);
        moveActionLeftButton->setObjectName("moveActionLeftButton");
        moveActionLeftButton->setEnabled(true);
        moveActionLeftButton->setMinimumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/button_left.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        moveActionLeftButton->setIcon(icon1);
        moveActionLeftButton->setAutoDefault(true);

        verticalLayout_2->addWidget(moveActionLeftButton);

        moveActionUpButton = new QPushButton(layoutWidget);
        moveActionUpButton->setObjectName("moveActionUpButton");
        moveActionUpButton->setEnabled(true);
        moveActionUpButton->setMinimumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/button_up.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        moveActionUpButton->setIcon(icon2);

        verticalLayout_2->addWidget(moveActionUpButton);

        moveActionDownButton = new QPushButton(layoutWidget);
        moveActionDownButton->setObjectName("moveActionDownButton");
        moveActionDownButton->setEnabled(true);
        moveActionDownButton->setMinimumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/button_down.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        moveActionDownButton->setIcon(icon3);
        moveActionDownButton->setAutoDefault(true);

        verticalLayout_2->addWidget(moveActionDownButton);

        spacerItem1 = new QSpacerItem(33, 57, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(spacerItem1);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        workbenchBox = new QComboBox(layoutWidget);
        workbenchBox->setObjectName("workbenchBox");

        verticalLayout->addWidget(workbenchBox);

        toolbarTreeWidget = new QTreeWidget(layoutWidget);
        toolbarTreeWidget->setObjectName("toolbarTreeWidget");
        toolbarTreeWidget->setColumnCount(0);

        verticalLayout->addWidget(toolbarTreeWidget);


        horizontalLayout->addLayout(verticalLayout);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem2 = new QSpacerItem(20, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        vboxLayout->addItem(spacerItem2);

        newButton = new QPushButton(layoutWidget);
        newButton->setObjectName("newButton");

        vboxLayout->addWidget(newButton);

        renameButton = new QPushButton(layoutWidget);
        renameButton->setObjectName("renameButton");

        vboxLayout->addWidget(renameButton);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName("deleteButton");

        vboxLayout->addWidget(deleteButton);

        spacerItem3 = new QSpacerItem(20, 152, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem3);


        horizontalLayout->addLayout(vboxLayout);

        splitter->addWidget(layoutWidget);

        verticalLayout_3->addWidget(splitter);

        label = new QLabel(Gui__Dialog__DlgCustomToolbars);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(label);

        QWidget::setTabOrder(editCommand, categoryBox);
        QWidget::setTabOrder(categoryBox, commandTreeWidget);
        QWidget::setTabOrder(commandTreeWidget, moveActionRightButton);
        QWidget::setTabOrder(moveActionRightButton, moveActionLeftButton);
        QWidget::setTabOrder(moveActionLeftButton, moveActionUpButton);
        QWidget::setTabOrder(moveActionUpButton, moveActionDownButton);
        QWidget::setTabOrder(moveActionDownButton, workbenchBox);
        QWidget::setTabOrder(workbenchBox, toolbarTreeWidget);
        QWidget::setTabOrder(toolbarTreeWidget, newButton);
        QWidget::setTabOrder(newButton, renameButton);
        QWidget::setTabOrder(renameButton, deleteButton);

        retranslateUi(Gui__Dialog__DlgCustomToolbars);

        moveActionLeftButton->setDefault(false);


        QMetaObject::connectSlotsByName(Gui__Dialog__DlgCustomToolbars);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgCustomToolbars)
    {
        Gui__Dialog__DlgCustomToolbars->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Toolbars", nullptr));
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Category", nullptr));
#if QT_CONFIG(tooltip)
        moveActionRightButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Move Right", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        moveActionRightButton->setWhatsThis(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "<b>Moves the selected item one level down.</b><p>This will also change the level of the parent item.</p>", nullptr));
#endif // QT_CONFIG(whatsthis)
        moveActionRightButton->setText(QString());
#if QT_CONFIG(tooltip)
        moveActionLeftButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Move Left", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        moveActionLeftButton->setWhatsThis(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "<b>Moves the selected item one level up.</b><p>This will also change the level of the parent item.</p>", nullptr));
#endif // QT_CONFIG(whatsthis)
        moveActionLeftButton->setText(QString());
#if QT_CONFIG(tooltip)
        moveActionUpButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Move Up", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        moveActionUpButton->setWhatsThis(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "<b>Moves the selected item up.</b><p>The item will be moved within the hierarchy level.</p>", nullptr));
#endif // QT_CONFIG(whatsthis)
        moveActionUpButton->setText(QString());
#if QT_CONFIG(tooltip)
        moveActionDownButton->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Move Down", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        moveActionDownButton->setWhatsThis(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "<b>Moves the selected item down.</b><p>The item will be moved within the hierarchy level.</p>", nullptr));
#endif // QT_CONFIG(whatsthis)
        moveActionDownButton->setText(QString());
        newButton->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "New", nullptr));
        renameButton->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Rename", nullptr));
        deleteButton->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "Delete", nullptr));
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgCustomToolbars", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-size:7.8pt; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><span style=\" font-weight:600;\">Note:</span> The changes become active the next time you load the appropriate workbench</p></body></html>", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgCustomToolbars: public Ui_DlgCustomToolbars {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGTOOLBARS_H
