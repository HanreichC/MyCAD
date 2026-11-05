// SPDX-License-Identifier: LGPL-2.1-or-later

/***************************************************************************
 *   Copyright (c) 2024 David Carter <dcarter@david.carter.ca>             *
 *                                                                         *
 *   This file is part of FreeCAD.                                         *
 *                                                                         *
 *   FreeCAD is free software: you can redistribute it and/or modify it    *
 *   under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation, either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   FreeCAD is distributed in the hope that it will be useful, but        *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with FreeCAD. If not, see                               *
 *   <https://www.gnu.org/licenses/>.                                      *
 *                                                                         *
 **************************************************************************/


#include <map>
#include <string>

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture3.h>


#include "ViewProviderTextureExtension.h"
#include <Gui/BitmapFactory.h>
#include <App/Material.h>


using namespace Gui;

namespace
{
/// Mitgelieferte Textur. Alle Körper teilen sich einen Knoten, sonst läge das Bild je Körper im Speicher und auf der GPU.
SoTexture2* bundledTexture(const std::string& path)
{
    // Der Pfad kommt aus der geöffneten Datei: nur eigene Ressourcen laden, keine beliebigen Dateien
    if (!path.starts_with(":/mycad/textures/")) {
        return nullptr;
    }
    static std::map<std::string, SoTexture2*> textures;  // lebt bis zum Programmende
    auto known = textures.find(path);
    if (known != textures.end()) {
        return known->second;
    }
    SoTexture2* texture = nullptr;
    const QImage image(QString::fromStdString(path));
    if (!image.isNull()) {
        SoSFImage pixels;
        Gui::BitmapFactory().convert(image, pixels);
        texture = new SoTexture2;
        texture->ref();
        texture->image = pixels;
    }
    textures[path] = texture;  // auch den Fehlschlag merken: Der Körper bleibt dann einfach einfarbig
    return texture;
}
}  // namespace


EXTENSION_PROPERTY_SOURCE(Gui::ViewProviderTextureExtension, Gui::ViewProviderExtension)


ViewProviderTextureExtension::ViewProviderTextureExtension()
{
    initExtensionType(ViewProviderTextureExtension::getExtensionClassTypeId());

    pcSwitchAppearance = new SoSwitch;
    pcSwitchAppearance->ref();
    pcSwitchAppearance->setName("SwitchAppearance");
    pcSwitchTexture = new SoSwitch;
    pcSwitchTexture->ref();
    pcSwitchTexture->setName("SwitchTexture");

    pcShapeTexture2D = new SoTexture2;
    pcShapeTexture2D->ref();
    pcShapeTexture2D->setName("ShapeTexture2D");

    pcTextureMaterial = new SoMaterial;
    pcTextureMaterial->ref();
    pcTextureMaterial->setName("TextureMaterial");
    pcTexture2D = new SoGroup;
    pcTexture2D->ref();
    pcTexture2D->addChild(pcTextureMaterial);
    pcTexture2D->addChild(pcShapeTexture2D);

    pcTextureGroup3D = new SoGroup;
    pcTextureGroup3D->ref();
    pcTextureGroup3D->setName("TextureGroup3D");
}

void ViewProviderTextureExtension::setup(SoMaterial* pcShapeMaterial)
{
    // Materials go first, with textured faces drawing over them
    pcSwitchAppearance->addChild(pcShapeMaterial);
    pcSwitchAppearance->addChild(pcSwitchTexture);
    pcSwitchTexture->addChild(pcTexture2D);
    pcSwitchTexture->addChild(pcTextureGroup3D);
    pcSwitchAppearance->whichChild.setValue(0);
    pcSwitchTexture->whichChild.setValue(SO_SWITCH_NONE);
}

ViewProviderTextureExtension::~ViewProviderTextureExtension()
{
    pcSwitchAppearance->unref();
    pcSwitchTexture->unref();
    pcShapeTexture2D->unref();
    pcTextureMaterial->unref();
    pcTexture2D->unref();
    pcTextureGroup3D->unref();
}

SoSwitch* ViewProviderTextureExtension::getAppearance() const
{
    return pcSwitchAppearance;
}

SoGroup* ViewProviderTextureExtension::getTextureGroup3D() const
{
    return pcTextureGroup3D;
}

void ViewProviderTextureExtension::setCoinAppearance(
    SoMaterial* pcShapeMaterial,
    const App::Material& source
)
{
    if (SoTexture2* bundled = bundledTexture(source.imagePath)) {
        pcTexture2D->replaceChild(1, bundled);
        activateTexture2D();
    }
    else if (!source.image.empty()) {
        pcTexture2D->replaceChild(1, pcShapeTexture2D);
        activateTexture2D();

        QByteArray by = QByteArray::fromBase64(QString::fromStdString(source.image).toUtf8());
        auto image = QImage::fromData(by, "PNG");  //.scaled(64, 64, Qt::KeepAspectRatio);

        SoSFImage texture;
        Gui::BitmapFactory().convert(image, texture);
        pcShapeTexture2D->image = texture;
    }
    else {
        activateMaterial();
    }

    // Mit Textur kommt die Farbe aus dem Bild, das Material liefert nur Glanz und Licht
    pcTextureMaterial->diffuseColor.setValue(1.0F, 1.0F, 1.0F);
    pcTextureMaterial->ambientColor.setValue(source.ambientColor.r, source.ambientColor.g, source.ambientColor.b);
    pcTextureMaterial->specularColor.setValue(source.specularColor.r, source.specularColor.g, source.specularColor.b);
    pcTextureMaterial->emissiveColor.setValue(source.emissiveColor.r, source.emissiveColor.g, source.emissiveColor.b);
    pcTextureMaterial->shininess.setValue(source.shininess);
    pcTextureMaterial->transparency.setValue(source.transparency);

    // Always set the material for items such as lines that don't support textures
    pcShapeMaterial->ambientColor
        .setValue(source.ambientColor.r, source.ambientColor.g, source.ambientColor.b);
    pcShapeMaterial->diffuseColor
        .setValue(source.diffuseColor.r, source.diffuseColor.g, source.diffuseColor.b);
    pcShapeMaterial->specularColor
        .setValue(source.specularColor.r, source.specularColor.g, source.specularColor.b);
    pcShapeMaterial->emissiveColor
        .setValue(source.emissiveColor.r, source.emissiveColor.g, source.emissiveColor.b);
    pcShapeMaterial->shininess.setValue(source.shininess);
    pcShapeMaterial->transparency.setValue(source.transparency);
}

void ViewProviderTextureExtension::activateMaterial()
{
    pcSwitchAppearance->whichChild.setValue(0);
    pcSwitchTexture->whichChild.setValue(SO_SWITCH_NONE);
}

void ViewProviderTextureExtension::activateTexture2D()
{
    pcSwitchAppearance->whichChild.setValue(1);
    pcSwitchTexture->whichChild.setValue(0);
}

void ViewProviderTextureExtension::activateTexture3D()
{
    pcSwitchAppearance->whichChild.setValue(1);
    pcSwitchTexture->whichChild.setValue(1);
}

void ViewProviderTextureExtension::activateMixed3D()
{
    pcSwitchAppearance->whichChild.setValue(SO_SWITCH_ALL);
    pcSwitchTexture->whichChild.setValue(1);
}

// ------------------------------------------------------------------------------------------------

EXTENSION_PROPERTY_SOURCE(Gui::ViewProviderFaceTexture, Gui::ViewProviderTextureExtension)


ViewProviderFaceTexture::ViewProviderFaceTexture()
{
    initExtensionType(ViewProviderFaceTexture::getExtensionClassTypeId());

    // Support for textured faces
    pcShapeTexture3D = new SoTexture3;
    pcShapeTexture3D->ref();
    pcShapeTexture3D->setName("ShapeTexture3D");
    pcShapeCoordinates = new SoCoordinate3;
    pcShapeCoordinates->ref();
    pcShapeCoordinates->setName("ShapeCoordinates");
    pcShapeFaceset = new SoIndexedFaceSet;
    pcShapeFaceset->ref();
    pcShapeFaceset->setName("ShapeFaceset");
}

ViewProviderFaceTexture::~ViewProviderFaceTexture()
{
    pcShapeTexture3D->unref();
    pcShapeCoordinates->unref();
    pcShapeFaceset->unref();
}

void ViewProviderFaceTexture::setup(SoMaterial* mat)
{
    ViewProviderTextureExtension::setup(mat);

    getTextureGroup3D()->addChild(pcShapeTexture3D);
    getTextureGroup3D()->addChild(pcShapeCoordinates);
    getTextureGroup3D()->addChild(pcShapeFaceset);
}
