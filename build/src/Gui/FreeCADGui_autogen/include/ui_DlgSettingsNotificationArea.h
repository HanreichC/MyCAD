/********************************************************************************
** Form generated from reading UI file 'DlgSettingsNotificationArea.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSNOTIFICATIONAREA_H
#define UI_DLGSETTINGSNOTIFICATIONAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "Gui/PrefWidgets.h"

namespace Gui {
namespace Dialog {

class Ui_DlgSettingsNotificationArea
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *NotificationAreaEnabled;
    QGridLayout *gridLayout;
    QGroupBox *NonIntrusiveNotificationsEnabled;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLabel *label;
    Gui::PrefSpinBox *maxDuration;
    Gui::PrefSpinBox *minDuration;
    QLabel *label_3;
    Gui::PrefSpinBox *maxNotifications;
    QLabel *label_width;
    Gui::PrefSpinBox *notificationWidth;
    Gui::PrefCheckBox *hideNonIntrusiveNotificationsWhenWindowDeactivated;
    Gui::PrefCheckBox *preventNonIntrusiveNotificationsWhenWindowNotActive;
    QGroupBox *GroupBoxSubscriptions;
    QGridLayout *gridLayout_1;
    Gui::PrefCheckBox *developerErrorSubscriptionEnabled;
    Gui::PrefCheckBox *developerWarningSubscriptionEnabled;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    Gui::PrefSpinBox *maxWidgetMessages;
    QLabel *label_4;
    Gui::PrefCheckBox *autoRemoveUserNotifications;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Gui__Dialog__DlgSettingsNotificationArea)
    {
        if (Gui__Dialog__DlgSettingsNotificationArea->objectName().isEmpty())
            Gui__Dialog__DlgSettingsNotificationArea->setObjectName("Gui__Dialog__DlgSettingsNotificationArea");
        Gui__Dialog__DlgSettingsNotificationArea->resize(654, 557);
        gridLayout_2 = new QGridLayout(Gui__Dialog__DlgSettingsNotificationArea);
        gridLayout_2->setObjectName("gridLayout_2");
        NotificationAreaEnabled = new QGroupBox(Gui__Dialog__DlgSettingsNotificationArea);
        NotificationAreaEnabled->setObjectName("NotificationAreaEnabled");
        NotificationAreaEnabled->setCheckable(true);
        gridLayout = new QGridLayout(NotificationAreaEnabled);
        gridLayout->setObjectName("gridLayout");
        NonIntrusiveNotificationsEnabled = new QGroupBox(NotificationAreaEnabled);
        NonIntrusiveNotificationsEnabled->setObjectName("NonIntrusiveNotificationsEnabled");
        NonIntrusiveNotificationsEnabled->setCheckable(true);
        NonIntrusiveNotificationsEnabled->setChecked(true);
        gridLayout_3 = new QGridLayout(NonIntrusiveNotificationsEnabled);
        gridLayout_3->setObjectName("gridLayout_3");
        label_2 = new QLabel(NonIntrusiveNotificationsEnabled);
        label_2->setObjectName("label_2");

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(NonIntrusiveNotificationsEnabled);
        label->setObjectName("label");

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        maxDuration = new Gui::PrefSpinBox(NonIntrusiveNotificationsEnabled);
        maxDuration->setObjectName("maxDuration");
        maxDuration->setMinimum(0);
        maxDuration->setMaximum(120);
        maxDuration->setValue(20);
        maxDuration->setProperty("prefEntry", QVariant(QByteArray("NotificationTime")));
        maxDuration->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(maxDuration, 0, 1, 1, 1);

        minDuration = new Gui::PrefSpinBox(NonIntrusiveNotificationsEnabled);
        minDuration->setObjectName("minDuration");
        minDuration->setValue(5);
        minDuration->setProperty("prefEntry", QVariant(QByteArray("MinimumOnScreenTime")));
        minDuration->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(minDuration, 1, 1, 1, 1);

        label_3 = new QLabel(NonIntrusiveNotificationsEnabled);
        label_3->setObjectName("label_3");

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        maxNotifications = new Gui::PrefSpinBox(NonIntrusiveNotificationsEnabled);
        maxNotifications->setObjectName("maxNotifications");
        maxNotifications->setValue(15);
        maxNotifications->setProperty("prefEntry", QVariant(QByteArray("MaxOpenNotifications")));
        maxNotifications->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(maxNotifications, 2, 1, 1, 1);

        label_width = new QLabel(NonIntrusiveNotificationsEnabled);
        label_width->setObjectName("label_width");

        gridLayout_3->addWidget(label_width, 3, 0, 1, 1);

        notificationWidth = new Gui::PrefSpinBox(NonIntrusiveNotificationsEnabled);
        notificationWidth->setObjectName("notificationWidth");
        notificationWidth->setMinimum(300);
        notificationWidth->setMaximum(10000);
        notificationWidth->setValue(800);
        notificationWidth->setProperty("prefEntry", QVariant(QByteArray("NotificiationWidth")));
        notificationWidth->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(notificationWidth, 3, 1, 1, 1);

        hideNonIntrusiveNotificationsWhenWindowDeactivated = new Gui::PrefCheckBox(NonIntrusiveNotificationsEnabled);
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setObjectName("hideNonIntrusiveNotificationsWhenWindowDeactivated");
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setChecked(true);
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setProperty("prefEntry", QVariant(QByteArray("HideNonIntrusiveNotificationsWhenWindowDeactivated")));
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(hideNonIntrusiveNotificationsWhenWindowDeactivated, 4, 0, 1, 1);

        preventNonIntrusiveNotificationsWhenWindowNotActive = new Gui::PrefCheckBox(NonIntrusiveNotificationsEnabled);
        preventNonIntrusiveNotificationsWhenWindowNotActive->setObjectName("preventNonIntrusiveNotificationsWhenWindowNotActive");
        preventNonIntrusiveNotificationsWhenWindowNotActive->setChecked(true);
        preventNonIntrusiveNotificationsWhenWindowNotActive->setProperty("prefEntry", QVariant(QByteArray("PreventNonIntrusiveNotificationsWhenWindowNotActive")));
        preventNonIntrusiveNotificationsWhenWindowNotActive->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_3->addWidget(preventNonIntrusiveNotificationsWhenWindowNotActive, 5, 0, 1, 1);


        gridLayout->addWidget(NonIntrusiveNotificationsEnabled, 2, 0, 1, 1);

        GroupBoxSubscriptions = new QGroupBox(NotificationAreaEnabled);
        GroupBoxSubscriptions->setObjectName("GroupBoxSubscriptions");
        gridLayout_1 = new QGridLayout(GroupBoxSubscriptions);
        gridLayout_1->setObjectName("gridLayout_1");
        developerErrorSubscriptionEnabled = new Gui::PrefCheckBox(GroupBoxSubscriptions);
        developerErrorSubscriptionEnabled->setObjectName("developerErrorSubscriptionEnabled");
        developerErrorSubscriptionEnabled->setChecked(false);
        developerErrorSubscriptionEnabled->setProperty("prefEntry", QVariant(QByteArray("DeveloperErrorSubscriptionEnabled")));
        developerErrorSubscriptionEnabled->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_1->addWidget(developerErrorSubscriptionEnabled, 0, 0, 1, 1);

        developerWarningSubscriptionEnabled = new Gui::PrefCheckBox(GroupBoxSubscriptions);
        developerWarningSubscriptionEnabled->setObjectName("developerWarningSubscriptionEnabled");
        developerWarningSubscriptionEnabled->setChecked(false);
        developerWarningSubscriptionEnabled->setProperty("prefEntry", QVariant(QByteArray("DeveloperWarningSubscriptionEnabled")));
        developerWarningSubscriptionEnabled->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_1->addWidget(developerWarningSubscriptionEnabled, 1, 0, 1, 1);


        gridLayout->addWidget(GroupBoxSubscriptions, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(NotificationAreaEnabled);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName("gridLayout_4");
        maxWidgetMessages = new Gui::PrefSpinBox(groupBox_2);
        maxWidgetMessages->setObjectName("maxWidgetMessages");
        maxWidgetMessages->setMaximum(10000);
        maxWidgetMessages->setValue(1000);
        maxWidgetMessages->setProperty("prefEntry", QVariant(QByteArray("MaxWidgetMessages")));
        maxWidgetMessages->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_4->addWidget(maxWidgetMessages, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        autoRemoveUserNotifications = new Gui::PrefCheckBox(groupBox_2);
        autoRemoveUserNotifications->setObjectName("autoRemoveUserNotifications");
        autoRemoveUserNotifications->setChecked(true);
        autoRemoveUserNotifications->setProperty("prefEntry", QVariant(QByteArray("AutoRemoveUserNotifications")));
        autoRemoveUserNotifications->setProperty("prefPath", QVariant(QByteArray("NotificationArea")));

        gridLayout_4->addWidget(autoRemoveUserNotifications, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        gridLayout_2->addWidget(NotificationAreaEnabled, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 63, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);


        retranslateUi(Gui__Dialog__DlgSettingsNotificationArea);

        QMetaObject::connectSlotsByName(Gui__Dialog__DlgSettingsNotificationArea);
    } // setupUi

    void retranslateUi(QWidget *Gui__Dialog__DlgSettingsNotificationArea)
    {
        Gui__Dialog__DlgSettingsNotificationArea->setWindowTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Notification Area", nullptr));
#if QT_CONFIG(tooltip)
        NotificationAreaEnabled->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "<html><head/><body><p>If checked, show the notification area in the status bar: a button with the current notification count, which can expand the detailed notification list. Optionally, with additional pop-up notifications.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        NotificationAreaEnabled->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Enable Notification Area", nullptr));
#if QT_CONFIG(tooltip)
        NonIntrusiveNotificationsEnabled->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Enables non-intrusive pop-up notifications above the notification area. Pop-up notifications can be dismissed manually by clicking on them, or automatically after a set duration.", nullptr));
#endif // QT_CONFIG(tooltip)
        NonIntrusiveNotificationsEnabled->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Enable Pop-Up Notifications", nullptr));
        label_2->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Minimum duration", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Maximum duration", nullptr));
#if QT_CONFIG(tooltip)
        maxDuration->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "<html><head/><body><p>Maximum amount of time the notification will be shown (unless mouse buttons are clicked). It also controls when user notifications will be removed if the &quot;Auto-remove user notifications&quot; setting is checked.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        maxDuration->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", " s", nullptr));
#if QT_CONFIG(tooltip)
        minDuration->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "<html><head/><body><p>Minimum amount of time the notification will be shown (unless the notification bubble is dismissed by clicking on it).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        minDuration->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", " s", nullptr));
        label_3->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Maximum concurrent notification count", nullptr));
#if QT_CONFIG(tooltip)
        maxNotifications->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Maximum number of notifications that will be simultaneously present on the notification bubble.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_width->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Notification bubble width", nullptr));
#if QT_CONFIG(tooltip)
        notificationWidth->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Width of the pop-up notification bubble in pixels.", nullptr));
#endif // QT_CONFIG(tooltip)
        notificationWidth->setSuffix(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", " px", nullptr));
        notificationWidth->setPrefix(QString());
#if QT_CONFIG(tooltip)
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Any open pop-up notifications will disappear when another window is activated.", nullptr));
#endif // QT_CONFIG(tooltip)
        hideNonIntrusiveNotificationsWhenWindowDeactivated->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Hide when other window is activated", nullptr));
#if QT_CONFIG(tooltip)
        preventNonIntrusiveNotificationsWhenWindowNotActive->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Prevent pop-up notifications from appearing when the FreeCAD window is not the active window.", nullptr));
#endif // QT_CONFIG(tooltip)
        preventNonIntrusiveNotificationsWhenWindowNotActive->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Do not show when window is inactive", nullptr));
#if QT_CONFIG(tooltip)
        GroupBoxSubscriptions->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Additional notification sources to show in the notification area.", nullptr));
#endif // QT_CONFIG(tooltip)
        GroupBoxSubscriptions->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Additional Data Sources", nullptr));
#if QT_CONFIG(tooltip)
        developerErrorSubscriptionEnabled->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Errors intended for developers will appear in the notification area.", nullptr));
#endif // QT_CONFIG(tooltip)
        developerErrorSubscriptionEnabled->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Debug errors", nullptr));
#if QT_CONFIG(tooltip)
        developerWarningSubscriptionEnabled->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Warnings intended for developers will appear in the notification area.", nullptr));
#endif // QT_CONFIG(tooltip)
        developerWarningSubscriptionEnabled->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Debug warnings", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_2->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Controls the amount of notifications to show in the list.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_2->setTitle(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Notifications List", nullptr));
#if QT_CONFIG(tooltip)
        maxWidgetMessages->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Limits the number of notifications that will be kept in the list. If 0, there is no limit.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Maximum notification count", nullptr));
#if QT_CONFIG(tooltip)
        autoRemoveUserNotifications->setToolTip(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Removes the user notifications from the notifications list after the maximum duration for pop-up notifications has lapsed.", nullptr));
#endif // QT_CONFIG(tooltip)
        autoRemoveUserNotifications->setText(QCoreApplication::translate("Gui::Dialog::DlgSettingsNotificationArea", "Auto-remove user notifications", nullptr));
    } // retranslateUi

};

} // namespace Dialog
} // namespace Gui

namespace Gui {
namespace Dialog {
namespace Ui {
    class DlgSettingsNotificationArea: public Ui_DlgSettingsNotificationArea {};
} // namespace Ui
} // namespace Dialog
} // namespace Gui

#endif // UI_DLGSETTINGSNOTIFICATIONAREA_H
