/********************************************************************************
** Form generated from reading UI file 'DlgSettingsMaterial.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGSETTINGSMATERIAL_H
#define UI_DLGSETTINGSMATERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Gui/FileDialog.h"
#include "Gui/PrefWidgets.h"

namespace MatGui {

class Ui_DlgSettingsMaterial
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *gb_4_materials;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_6;
    Gui::PrefCheckBox *cb_use_built_in_materials;
    Gui::PrefCheckBox *cb_use_mat_from_workbenches;
    Gui::PrefCheckBox *cb_use_mat_from_config_dir;
    Gui::PrefCheckBox *cb_use_mat_from_custom_dir;
    QGridLayout *gridLayout;
    QLabel *l_custom_mat_dir;
    Gui::PrefFileChooser *fc_custom_mat_dir;
    QGroupBox *gb_4_materials_2;
    QVBoxLayout *verticalLayout_3;
    Gui::PrefCheckBox *cb_delete_duplicates;
    Gui::PrefCheckBox *cb_sort_by_resources;
    QGroupBox *gbMaterialSelector;
    QVBoxLayout *verticalLayout_5;
    Gui::PrefCheckBox *cb_show_favorites;
    Gui::PrefCheckBox *cb_show_recent;
    Gui::PrefCheckBox *cb_show_empty_libraries;
    Gui::PrefCheckBox *cb_show_empty_folders;
    Gui::PrefCheckBox *cb_show_legacy;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    Gui::PrefCheckBox *cb_show_favorites_editor;
    Gui::PrefCheckBox *cb_show_recent_editor;
    Gui::PrefCheckBox *cb_show_empty_libraries_editor;
    Gui::PrefCheckBox *cb_show_empty_folders_editor;
    Gui::PrefCheckBox *cb_show_legacy_editor;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MatGui__DlgSettingsMaterial)
    {
        if (MatGui__DlgSettingsMaterial->objectName().isEmpty())
            MatGui__DlgSettingsMaterial->setObjectName("MatGui__DlgSettingsMaterial");
        MatGui__DlgSettingsMaterial->resize(434, 553);
        verticalLayout = new QVBoxLayout(MatGui__DlgSettingsMaterial);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        gb_4_materials = new QGroupBox(MatGui__DlgSettingsMaterial);
        gb_4_materials->setObjectName("gb_4_materials");
        verticalLayout_2 = new QVBoxLayout(gb_4_materials);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName("verticalLayout_6");
        cb_use_built_in_materials = new Gui::PrefCheckBox(gb_4_materials);
        cb_use_built_in_materials->setObjectName("cb_use_built_in_materials");
        cb_use_built_in_materials->setChecked(true);
        cb_use_built_in_materials->setProperty("prefEntry", QVariant(QByteArray("UseBuiltInMaterials")));
        cb_use_built_in_materials->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Resources")));

        verticalLayout_6->addWidget(cb_use_built_in_materials);

        cb_use_mat_from_workbenches = new Gui::PrefCheckBox(gb_4_materials);
        cb_use_mat_from_workbenches->setObjectName("cb_use_mat_from_workbenches");
        cb_use_mat_from_workbenches->setChecked(true);
        cb_use_mat_from_workbenches->setProperty("prefEntry", QVariant(QByteArray("UseMaterialsFromWorkbenches")));
        cb_use_mat_from_workbenches->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Resources")));

        verticalLayout_6->addWidget(cb_use_mat_from_workbenches);

        cb_use_mat_from_config_dir = new Gui::PrefCheckBox(gb_4_materials);
        cb_use_mat_from_config_dir->setObjectName("cb_use_mat_from_config_dir");
        cb_use_mat_from_config_dir->setChecked(true);
        cb_use_mat_from_config_dir->setProperty("prefEntry", QVariant(QByteArray("UseMaterialsFromConfigDir")));
        cb_use_mat_from_config_dir->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Resources")));

        verticalLayout_6->addWidget(cb_use_mat_from_config_dir);

        cb_use_mat_from_custom_dir = new Gui::PrefCheckBox(gb_4_materials);
        cb_use_mat_from_custom_dir->setObjectName("cb_use_mat_from_custom_dir");
        cb_use_mat_from_custom_dir->setChecked(true);
        cb_use_mat_from_custom_dir->setProperty("prefEntry", QVariant(QByteArray("UseMaterialsFromCustomDir")));
        cb_use_mat_from_custom_dir->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Resources")));

        verticalLayout_6->addWidget(cb_use_mat_from_custom_dir);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        l_custom_mat_dir = new QLabel(gb_4_materials);
        l_custom_mat_dir->setObjectName("l_custom_mat_dir");
        l_custom_mat_dir->setEnabled(true);
        l_custom_mat_dir->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(l_custom_mat_dir, 1, 0, 1, 1);

        fc_custom_mat_dir = new Gui::PrefFileChooser(gb_4_materials);
        fc_custom_mat_dir->setObjectName("fc_custom_mat_dir");
        fc_custom_mat_dir->setEnabled(true);
        fc_custom_mat_dir->setMode(Gui::FileChooser::Directory);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fc_custom_mat_dir->sizePolicy().hasHeightForWidth());
        fc_custom_mat_dir->setSizePolicy(sizePolicy);
        fc_custom_mat_dir->setProperty("prefEntry", QVariant(QByteArray("CustomMaterialsDir")));
        fc_custom_mat_dir->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Resources")));

        gridLayout->addWidget(fc_custom_mat_dir, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout);


        verticalLayout_2->addLayout(verticalLayout_6);


        verticalLayout->addWidget(gb_4_materials);

        gb_4_materials_2 = new QGroupBox(MatGui__DlgSettingsMaterial);
        gb_4_materials_2->setObjectName("gb_4_materials_2");
        verticalLayout_3 = new QVBoxLayout(gb_4_materials_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        cb_delete_duplicates = new Gui::PrefCheckBox(gb_4_materials_2);
        cb_delete_duplicates->setObjectName("cb_delete_duplicates");
        cb_delete_duplicates->setChecked(true);
        cb_delete_duplicates->setProperty("prefEntry", QVariant(QByteArray("DeleteDuplicates")));
        cb_delete_duplicates->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Cards")));

        verticalLayout_3->addWidget(cb_delete_duplicates);

        cb_sort_by_resources = new Gui::PrefCheckBox(gb_4_materials_2);
        cb_sort_by_resources->setObjectName("cb_sort_by_resources");
        cb_sort_by_resources->setChecked(true);
        cb_sort_by_resources->setProperty("prefEntry", QVariant(QByteArray("SortByResources")));
        cb_sort_by_resources->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Cards")));

        verticalLayout_3->addWidget(cb_sort_by_resources);


        verticalLayout->addWidget(gb_4_materials_2);

        gbMaterialSelector = new QGroupBox(MatGui__DlgSettingsMaterial);
        gbMaterialSelector->setObjectName("gbMaterialSelector");
        verticalLayout_5 = new QVBoxLayout(gbMaterialSelector);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        cb_show_favorites = new Gui::PrefCheckBox(gbMaterialSelector);
        cb_show_favorites->setObjectName("cb_show_favorites");
        cb_show_favorites->setChecked(true);
        cb_show_favorites->setProperty("prefEntry", QVariant(QByteArray("ShowFavorites")));
        cb_show_favorites->setProperty("prefPath", QVariant(QByteArray("Mod/Material/TreeWidget")));

        verticalLayout_5->addWidget(cb_show_favorites);

        cb_show_recent = new Gui::PrefCheckBox(gbMaterialSelector);
        cb_show_recent->setObjectName("cb_show_recent");
        cb_show_recent->setChecked(true);
        cb_show_recent->setProperty("prefEntry", QVariant(QByteArray("ShowRecent")));
        cb_show_recent->setProperty("prefPath", QVariant(QByteArray("Mod/Material/TreeWidget")));

        verticalLayout_5->addWidget(cb_show_recent);

        cb_show_empty_libraries = new Gui::PrefCheckBox(gbMaterialSelector);
        cb_show_empty_libraries->setObjectName("cb_show_empty_libraries");
        cb_show_empty_libraries->setChecked(true);
        cb_show_empty_libraries->setProperty("prefEntry", QVariant(QByteArray("ShowEmptyLibraries")));
        cb_show_empty_libraries->setProperty("prefPath", QVariant(QByteArray("Mod/Material/TreeWidget")));

        verticalLayout_5->addWidget(cb_show_empty_libraries);

        cb_show_empty_folders = new Gui::PrefCheckBox(gbMaterialSelector);
        cb_show_empty_folders->setObjectName("cb_show_empty_folders");
        cb_show_empty_folders->setProperty("prefEntry", QVariant(QByteArray("ShowEmptyFolders")));
        cb_show_empty_folders->setProperty("prefPath", QVariant(QByteArray("Mod/Material/TreeWidget")));

        verticalLayout_5->addWidget(cb_show_empty_folders);

        cb_show_legacy = new Gui::PrefCheckBox(gbMaterialSelector);
        cb_show_legacy->setObjectName("cb_show_legacy");
        cb_show_legacy->setProperty("prefEntry", QVariant(QByteArray("ShowLegacy")));
        cb_show_legacy->setProperty("prefPath", QVariant(QByteArray("Mod/Material/TreeWidget")));

        verticalLayout_5->addWidget(cb_show_legacy);


        verticalLayout->addWidget(gbMaterialSelector);

        groupBox = new QGroupBox(MatGui__DlgSettingsMaterial);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        cb_show_favorites_editor = new Gui::PrefCheckBox(groupBox);
        cb_show_favorites_editor->setObjectName("cb_show_favorites_editor");
        cb_show_favorites_editor->setChecked(true);
        cb_show_favorites_editor->setProperty("prefEntry", QVariant(QByteArray("ShowFavorites")));
        cb_show_favorites_editor->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Editor")));

        verticalLayout_4->addWidget(cb_show_favorites_editor);

        cb_show_recent_editor = new Gui::PrefCheckBox(groupBox);
        cb_show_recent_editor->setObjectName("cb_show_recent_editor");
        cb_show_recent_editor->setChecked(true);
        cb_show_recent_editor->setProperty("prefEntry", QVariant(QByteArray("ShowRecent")));
        cb_show_recent_editor->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Editor")));

        verticalLayout_4->addWidget(cb_show_recent_editor);

        cb_show_empty_libraries_editor = new Gui::PrefCheckBox(groupBox);
        cb_show_empty_libraries_editor->setObjectName("cb_show_empty_libraries_editor");
        cb_show_empty_libraries_editor->setChecked(true);
        cb_show_empty_libraries_editor->setProperty("prefEntry", QVariant(QByteArray("ShowEmptyLibraries")));
        cb_show_empty_libraries_editor->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Editor")));

        verticalLayout_4->addWidget(cb_show_empty_libraries_editor);

        cb_show_empty_folders_editor = new Gui::PrefCheckBox(groupBox);
        cb_show_empty_folders_editor->setObjectName("cb_show_empty_folders_editor");
        cb_show_empty_folders_editor->setProperty("prefEntry", QVariant(QByteArray("ShowEmptyFolders")));
        cb_show_empty_folders_editor->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Editor")));

        verticalLayout_4->addWidget(cb_show_empty_folders_editor);

        cb_show_legacy_editor = new Gui::PrefCheckBox(groupBox);
        cb_show_legacy_editor->setObjectName("cb_show_legacy_editor");
        cb_show_legacy_editor->setChecked(true);
        cb_show_legacy_editor->setProperty("prefEntry", QVariant(QByteArray("ShowLegacy")));
        cb_show_legacy_editor->setProperty("prefPath", QVariant(QByteArray("Mod/Material/Editor")));

        verticalLayout_4->addWidget(cb_show_legacy_editor);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(MatGui__DlgSettingsMaterial);
        QObject::connect(cb_use_mat_from_custom_dir, SIGNAL(toggled(bool)), fc_custom_mat_dir, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(MatGui__DlgSettingsMaterial);
    } // setupUi

    void retranslateUi(QWidget *MatGui__DlgSettingsMaterial)
    {
        MatGui__DlgSettingsMaterial->setWindowTitle(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "General", nullptr));
        gb_4_materials->setTitle(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Card Resources", nullptr));
#if QT_CONFIG(tooltip)
        cb_use_built_in_materials->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "The cards built-in to FreeCAD will be listed as available", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_use_built_in_materials->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Use built-in materials", nullptr));
#if QT_CONFIG(tooltip)
        cb_use_mat_from_workbenches->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Use materials added by external workbenches", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_use_mat_from_workbenches->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Use materials from external workbenches", nullptr));
#if QT_CONFIG(tooltip)
        cb_use_mat_from_config_dir->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Cards from FreeCAD\342\200\231s preferences directory are also listed as available", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_use_mat_from_config_dir->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Use materials from the Materials preference directory", nullptr));
#if QT_CONFIG(tooltip)
        cb_use_mat_from_custom_dir->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Material cards from the specified directory will also be listed as available", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_use_mat_from_custom_dir->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Use materials from user-defined directory", nullptr));
        l_custom_mat_dir->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "User directory", nullptr));
        gb_4_materials_2->setTitle(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Card Sorting and Duplicates", nullptr));
#if QT_CONFIG(tooltip)
        cb_delete_duplicates->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Duplicate cards will be deleted from the displayed material card list", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_delete_duplicates->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Delete card duplicates", nullptr));
#if QT_CONFIG(tooltip)
        cb_sort_by_resources->setToolTip(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Material cards appear sorted by their resources (locations).\n"
"If unchecked, they will be sorted by their name.", nullptr));
#endif // QT_CONFIG(tooltip)
        cb_sort_by_resources->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Sort by resources", nullptr));
        gbMaterialSelector->setTitle(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Material Selector", nullptr));
        cb_show_favorites->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show favorites", nullptr));
        cb_show_recent->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show recent", nullptr));
        cb_show_empty_libraries->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show empty libraries", nullptr));
        cb_show_empty_folders->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show empty folders", nullptr));
        cb_show_legacy->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show legacy files", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Material Editor", nullptr));
        cb_show_favorites_editor->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show favorites", nullptr));
        cb_show_recent_editor->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show recent", nullptr));
        cb_show_empty_libraries_editor->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show empty libraries", nullptr));
        cb_show_empty_folders_editor->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show empty folders", nullptr));
        cb_show_legacy_editor->setText(QCoreApplication::translate("MatGui::DlgSettingsMaterial", "Show legacy files", nullptr));
    } // retranslateUi

};

} // namespace MatGui

namespace MatGui {
namespace Ui {
    class DlgSettingsMaterial: public Ui_DlgSettingsMaterial {};
} // namespace Ui
} // namespace MatGui

#endif // UI_DLGSETTINGSMATERIAL_H
