// SPDX-License-Identifier: LGPL-2.1-or-later

/***************************************************************************
 *   Copyright (c) 2015 Victor Titov (DeepSOIC) <vv.titov@gmail.com>       *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include <Base/Console.h>
#include <Base/ProgramVersion.h>
#include <Base/Tools.h>

#include <App/Document.h>
#include <App/Datums.h>
#include <App/ObjectIdentifier.h>
#include <App/Expression.h>
#include <App/ExpressionParser.h>

#include "AttachExtension.h"
#include "AttachExtensionPy.h"
#include "PartFeature.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>


using namespace Part;
using namespace Attacher;

namespace
{
std::vector<std::string> EngineEnums = {"Engine 3D", "Engine Plane", "Engine Line", "Engine Point"};

const char* enumToClass(const char* mode)
{
    if (EngineEnums.at(0) == mode) {
        return "Attacher::AttachEngine3D";
    }
    if (EngineEnums.at(1) == mode) {
        return "Attacher::AttachEnginePlane";
    }
    if (EngineEnums.at(2) == mode) {
        return "Attacher::AttachEngineLine";
    }
    if (EngineEnums.at(3) == mode) {
        return "Attacher::AttachEnginePoint";
    }

    return "Attacher::AttachEngine3D";
}

const char* classToEnum(const char* type)
{
    if (strcmp(type, "Attacher::AttachEngine3D") == 0) {
        return EngineEnums.at(0).c_str();
    }
    if (strcmp(type, "Attacher::AttachEnginePlane") == 0) {
        return EngineEnums.at(1).c_str();
    }
    if (strcmp(type, "Attacher::AttachEngineLine") == 0) {
        return EngineEnums.at(2).c_str();
    }
    if (strcmp(type, "Attacher::AttachEnginePoint") == 0) {
        return EngineEnums.at(3).c_str();
    }

    return EngineEnums.at(0).c_str();
}

void restoreAttacherEngine(AttachExtension* self)
{
    const char* mode = enumToClass(self->AttacherEngine.getValueAsString());
    const char* type = self->AttacherType.getValue();
    if (strcmp(mode, type) != 0) {
        self->AttacherEngine.setValue(classToEnum(type));
    }
}
}  // namespace

EXTENSION_PROPERTY_SOURCE(Part::AttachExtension, App::DocumentObjectExtension)

AttachExtension::AttachExtension()
{
    EXTENSION_ADD_PROPERTY_TYPE(
        AttacherType,
        ("Attacher::AttachEngine3D"),
        "Attachment",
        (App::PropertyType)(App::Prop_ReadOnly | App::Prop_Hidden),
        "Class name of attach engine object driving the attachment."
    );

    EXTENSION_ADD_PROPERTY_TYPE(
        AttacherEngine,
        (0L),
        "Attachment",
        (App::PropertyType)(App::Prop_None),
        "Attach engine object driving the attachment."
    );
    AttacherEngine.setEnums(EngineEnums);

    EXTENSION_ADD_PROPERTY_TYPE(
        AttachmentSupport,
        (nullptr, nullptr),
        "Attachment",
        (App::PropertyType)(App::Prop_None),
        "Support of the 2D geometry"
    );
    AttachmentSupport.setScope(App::LinkScope::Global);

    EXTENSION_ADD_PROPERTY_TYPE(
        MapMode,
        (mmDeactivated),
        "Attachment",
        App::Prop_None,
        "Mode of attachment to other object"
    );
    MapMode.setEditorName("PartGui::PropertyEnumAttacherItem");
    MapMode.setEnums(AttachEngine::eMapModeStrings);
    // a rough test if mode string list in Attacher.cpp is in sync with eMapMode enum.
    assert(MapMode.getEnumVector().size() == mmDummy_NumberOfModes);

    EXTENSION_ADD_PROPERTY_TYPE(
        MapReversed,
        (false),
        "Attachment",
        App::Prop_None,
        "Reverse Z-direction (flip sketch upside down)"
    );

    EXTENSION_ADD_PROPERTY_TYPE(
        MapPathParameter,
        (0.0),
        "Attachment",
        App::Prop_None,
        "Sets point of curve to map the sketch to. 0..1 = start..end"
    );

    EXTENSION_ADD_PROPERTY_TYPE(
        AttachmentOffset,
        (Base::Placement()),
        "Attachment",
        App::Prop_None,
        "Extra placement to apply in addition to attachment (in local coordinates)"
    );

    // Only show these properties when applicable. Controlled by extensionOnChanged
    this->MapPathParameter.setStatus(App::Property::Status::Hidden, true);
    this->MapReversed.setStatus(App::Property::Status::Hidden, true);
    this->AttachmentOffset.setStatus(App::Property::Status::Hidden, true);

    _props.attacherType = &AttacherType;
    _props.attachment = &AttachmentSupport;
    _props.mapMode = &MapMode;
    _props.mapReversed = &MapReversed;
    _props.mapPathParameter = &MapPathParameter;

    setAttacher(new AttachEngine3D);  // default attacher
    _baseProps.attacher.reset(new AttachEngine3D);

    updatePropertyStatus(false);

    initExtensionType(AttachExtension::getExtensionClassTypeId());
}

AttachExtension::~AttachExtension()
{}

template<class T>
static inline bool getProp(
    bool force,
    T*& prop,
    Base::Type type,
    App::PropertyContainer* owner,
    const char* name,
    const char* doc
)
{
    prop = freecad_cast<T*>(owner->getDynamicPropertyByName(name));
    if (prop || !force) {
        return false;
    }
    prop = static_cast<T*>(owner->addDynamicProperty(type.getName(), name, "Attachment", doc));
    if (!prop) {
        FC_THROWM(Base::RuntimeError, "Failed to add property " << owner->getFullName() << name);
    }
    prop->setStatus(App::Property::Status::LockDynamic, true);
    prop->setStatus(App::Property::Status::Hidden, true);
    return true;
}

template<class T>
static inline bool getProp(
    bool force,
    T*& prop,
    App::PropertyContainer* owner,
    const char* name,
    const char* doc
)
{
    return getProp(force, prop, T::getClassTypeId(), owner, name, doc);
}

void AttachExtension::initBase(bool force)
{
    if (_baseProps.attacherType) {
        return;
    }
    auto obj = getExtendedObject();

    // Temporary holding the properties so that we only handle onChanged() event
    // when all relevant properties are ready.
    Properties props;

    if (getProp<App::PropertyString>(
            force,
            props.attacherType,
            obj,
            "BaseAttacherType",
            "Class name of attach engine object driving the attachment for base geometry."
        )) {
        props.attacherType->setValue(std::string {_baseProps.attacher->getTypeId().getName()}.c_str());
    }
    else if (!props.attacherType) {
        return;
    }

    getProp<App::PropertyLinkSubList>(
        force,
        props.attachment,
        App::PropertyLinkSubListHidden::getClassTypeId(),
        obj,
        "BaseAttachment",
        "Link to base geometry."
    );

    if (getProp<App::PropertyEnumeration>(
            force,
            props.mapMode,
            obj,
            "BaseMapMode",
            "Mode of attachment for the base geometry"
        )) {
        props.mapMode->setStatus(App::Property::Status::Hidden, false);
    }
    if (props.mapMode) {
        props.mapMode->setEditorName("PartGui::PropertyEnumAttacherItem");
        props.mapMode->setEnums(AttachEngine::eMapModeStrings);
    }

    getProp<App::PropertyBool>(
        force,
        props.mapReversed,
        obj,
        "BaseMapReversed",
        "Reverse Z-direction of the base geometry attachment"
    );

    getProp<App::PropertyFloat>(
        force,
        props.mapPathParameter,
        obj,
        "BaseMapPathParameter",
        "Sets point of base curve to map 0..1 = start..end"
    );

    static_cast<Properties&>(_baseProps) = props;
}

void AttachExtension::setAttacher(AttachEngine* pAttacher, bool base)
{
    auto& props = base ? _baseProps : _props;
    props.attacher.reset(pAttacher);
    if (props.attacher) {
        if (base) {
            initBase(true);
        }
        const auto typeName = props.attacher->getTypeId().getName();
        if (props.attacherType->getValue() == typeName) {
            // make sure we need to change, to break recursive
            // onChange->changeAttacherType->onChange...
            props.attacherType->setValue(std::string {typeName}.c_str());
        }
        // Also update the visible AttacherEngine property for non-base attachers
        // to keep it in sync with AttacherType (fixes issue #15716)
        if (!base) {
            const char* enumVal = classToEnum(std::string {typeName}.c_str());
            if (strcmp(AttacherEngine.getValueAsString(), enumVal) != 0) {
                AttacherEngine.setValue(enumVal);
            }
        }
        updateAttacherVals(base);
    }
    else {
        if (
            props.attacherType && strlen(props.attacherType->getValue()) != 0
        ) {  // make sure we need to change, to break recursive
             // onChange->changeAttacherType->onChange...
            props.attacherType->setValue("");
        }
    }
}

bool AttachExtension::changeAttacherType(const char* typeName, bool base)
{
    auto& prop = base ? _baseProps : _props;

    // check if we need to actually change anything
    if (prop.attacher) {
        if (prop.attacher->getTypeId().getName() == typeName) {
            return false;
        }
    }
    else if (strlen(typeName) == 0) {
        return false;
    }
    if (strlen(typeName) == 0) {
        setAttacher(nullptr, base);
        return true;
    }
    Base::Type t = Base::Type::fromName(typeName);
    if (t.isDerivedFrom(AttachEngine::getClassTypeId())) {
        AttachEngine* pNewAttacher = static_cast<Attacher::AttachEngine*>(
            Base::Type::createInstanceByName(typeName)
        );
        this->setAttacher(pNewAttacher, base);
        return true;
    }

    std::stringstream errMsg;
    errMsg << "Object if this type is not derived from AttachEngine: " << typeName;
    throw AttachEngineException(errMsg.str());
}

bool AttachExtension::positionBySupport()
{
    _active = 0;
    if (!_props.attacher) {
        throw Base::RuntimeError(
            "AttachExtension: can't positionBySupport, because no AttachEngine is set."
        );
    }
    updateAttacherVals();
    Base::Placement plaOriginal = getPlacement().getValue();
    try {
        if (_props.attacher->mapMode == mmDeactivated) {
            return false;
        }
        bool subChanged = false;

        getPlacement().setValue(Base::Placement());

        Base::Placement basePlacement;
        if (_baseProps.attacher && _baseProps.attacher->mapMode != mmDeactivated) {
            basePlacement
                = _baseProps.attacher->calculateAttachedPlacement(Base::Placement(), &subChanged);
            if (subChanged) {
                _baseProps.attachment->setValues(
                    _baseProps.attachment->getValues(),
                    _baseProps.attacher->getSubValues()
                );
            }
        }

        subChanged = false;
        _props.attacher->setOffset(AttachmentOffset.getValue() * basePlacement.inverse());
        auto placement = _props.attacher->calculateAttachedPlacement(plaOriginal, &subChanged);
        if (subChanged) {
            Base::ObjectStatusLocker<App::Property::Status, App::Property> guard(
                App::Property::User3,
                &AttachmentSupport
            );
            AttachmentSupport.setValues(AttachmentSupport.getValues(), _props.attacher->getSubValues());
        }
        getPlacement().setValue(placement);
        _active = 1;
        return true;
    }
    catch (ExceptionCancel&) {
        // disabled, don't do anything
        getPlacement().setValue(plaOriginal);
        return false;
    }
    catch (Base::Exception&) {
        getPlacement().setValue(plaOriginal);
        throw;
    }
    catch (Standard_Failure&) {
        getPlacement().setValue(plaOriginal);
        throw;
    }
}

bool AttachExtension::isAttacherActive() const
{
    if (_active < 0) {
        _active = 0;
        try {
            updateAttacherVals(/*base*/ false);
            updateAttacherVals(/*base*/ true);
            _props.attacher->calculateAttachedPlacement(getPlacement().getValue());
            _active = 1;
        }
        catch (Base::Exception&) {
        }
    }
    return _active != 0;
}

short int AttachExtension::extensionMustExecute()
{
    return DocumentObjectExtension::extensionMustExecute();
}


/// MyCAD: die Fläche, an der Skizze oder Ebene hingen, ist unter ihrem Namen nicht mehr da (der Körper darunter hat sich
/// geändert, die Flächen heißen anders). Über die Lage wiederfinden: dieselbe Ebene wie zuletzt (aus Placement und
/// Versatz), darin die Fläche, die dem Objekt am nächsten liegt. Den Versatz so anpassen, dass es genau an seinem Platz
/// bleibt. Vorher blieb es mit "Fläche weg" stehen und folgte dem Körper nicht mehr (ConceptKey: Skizze001-004, Ebene).
bool AttachExtension::refindFace(bool misplaced, bool* turned)
{
    auto objs = AttachmentSupport.getValues();
    auto subs = AttachmentSupport.getSubValues();
    if (objs.empty() || objs.size() != subs.size()) {
        return false;
    }
    App::DocumentObject* owner = getExtendedObject();
    const Base::Placement last = getPlacement().getValue();
    const Base::Placement offset = AttachmentOffset.getValue();
    const Base::Placement plane = last * offset.inverse();  // Lage der alten Fläche
    Base::Vector3d n;
    plane.getRotation().multVec(Base::Vector3d(0, 0, 1), n);
    const gp_Dir normal(n.x, n.y, n.z);
    const gp_Pnt origin(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z);
    // Wo das Objekt liegt: Mitte seiner Form (Skizzenlinien, Ebene), sonst der Ursprung der Ebene
    gp_Pnt near = origin;
    if (auto feature = dynamic_cast<Part::Feature*>(owner)) {
        const TopoDS_Shape own = feature->Shape.getValue();
        if (!own.IsNull()) {
            GProp_GProps props;
            BRepGProp::LinearProperties(own, props);
            if (props.Mass() > 0) {
                near = props.CentreOfMass();
            }
        }
    }
    // Außennormale wie der Attacher (Orientierung der Fläche und Händigkeit der Ebene): die linke und die rechte Wand
    // sind parallel, zeigen aber entgegengesetzt. Vorher sprang eine Skizze von der einen an die andere (ConceptKey)
    const auto outward = [](const TopoDS_Face& face, const gp_Pln& pln) {
        gp_Dir d = pln.Axis().Direction();
        if ((face.Orientation() == TopAbs_REVERSED) != !pln.Direct()) {
            d.Reverse();
        }
        return d;
    };
    const auto sameWay = [&normal](const gp_Dir& d) { return d.IsEqual(normal, Precision::Angular()); };
    bool changed = false;
    for (size_t i = 0; i < objs.size(); ++i) {
        auto support = dynamic_cast<Part::Feature*>(objs[i]);
        std::string sub = subs[i];
        const auto dot = sub.rfind('.');
        const std::string element = dot == std::string::npos ? sub : sub.substr(dot + 1);
        if (!support || element.find("Face") == std::string::npos) {
            continue;
        }
        TopoDS_Shape named;
        try {
            if (element[0] != '?') {
                named = support->Shape.getShape().getSubShape(element.c_str(), true);
            }
        }
        catch (...) {
        }
        if (!misplaced && !named.IsNull()) {
            continue;
        }
        if (misplaced) {
            // Die benannte Fläche liegt noch in der alten Ebene: alles gut
            if (named.IsNull() || named.ShapeType() != TopAbs_FACE) {
                continue;
            }
            BRepAdaptor_Surface surface(TopoDS::Face(named));
            if (surface.GetType() != GeomAbs_Plane) {
                continue;
            }
            const gp_Pln pln = surface.Plane();
            const bool parallel = sameWay(outward(TopoDS::Face(named), pln));
            if (parallel && pln.Distance(origin) <= 1e-6) {
                continue;
            }
            if (!parallel && turned) {
                *turned = true;  // eine ganz andere Fläche (andere Richtung): nicht dorthin springen
            }
        }
        const TopoDS_Shape shape = support->Shape.getShape().getShape();
        double best = Precision::Infinite();
        int bestIndex = 0, index = 0;
        for (TopExp_Explorer it(shape, TopAbs_FACE); it.More(); it.Next()) {
            ++index;
            BRepAdaptor_Surface surface(TopoDS::Face(it.Current()));
            if (surface.GetType() != GeomAbs_Plane) {
                continue;
            }
            const gp_Pln pln = surface.Plane();
            if (!sameWay(outward(TopoDS::Face(it.Current()), pln)) || pln.Distance(origin) > 1e-6) {
                continue;
            }
            BRepExtrema_DistShapeShape dist(BRepBuilderAPI_MakeVertex(near).Vertex(), it.Current());
            if (dist.IsDone() && dist.Value() < best - 1e-9) {
                best = dist.Value();
                bestIndex = index;
            }
        }
        // Name zeigt auf eine andere Fläche: nur eine Fläche nehmen, auf der das Objekt wirklich liegt (sonst ist der
        // Körper nur höher/tiefer geworden und das Objekt folgt der benannten Fläche wie bisher)
        if (!bestIndex || (misplaced && best > 1e-6)) {
            return false;
        }
        subs[i] = "Face" + std::to_string(bestIndex);
        changed = true;
    }
    if (!changed) {
        return false;
    }
    try {
        AttachmentSupport.setValues(objs, subs);
        positionBySupport();
        // An der neuen Fläche genau an den alten Platz: Versatz ausgleichen
        const Base::Placement now = getPlacement().getValue();
        AttachmentOffset.setValue(offset * now.inverse() * last);
        positionBySupport();
    }
    catch (...) {
        return false;
    }
    Base::Console().log("{}: face found again by its position\n", owner->getFullName());
    if (auto warning = dynamic_cast<App::PropertyString*>(owner->getPropertyByName("Warning"));
        warning && std::string(warning->getValue()).starts_with("Face gone")) {
        warning->setValue("");
    }
    return true;
}

App::DocumentObjectExecReturn* AttachExtension::extensionExecute()
{
    // MyCAD: findet eine Skizze oder Ebene ihre Fläche nicht mehr (der Körper darunter hat sich geändert), bleibt sie
    // an ihrem Platz und warnt (Timeline, Hinweis oben rechts), statt als Fehler alles danach zu blockieren: sonst
    // rechnete nichts mehr, eine neue Skizze erschien erst nach einem Neustart und mit alten Linien (ConceptKey).
    // Wie Extrude bei verlorenem Profil.
    static constexpr const char* faceLost =
        "Face gone: the face this was drawn on no longer exists; it stays where it was";
    App::DocumentObject* owner = getExtendedObject();
    auto warning = dynamic_cast<App::PropertyString*>(owner->getPropertyByName("Warning"));
    const auto keepPlace = [&](const char* why) {
        if (AttachmentSupport.getValues().empty()) {
            return false;
        }
        Base::Console().warning("{}: {}\n", owner->getFullName(), why);
        if (!warning) {
            warning = static_cast<App::PropertyString*>(owner->addDynamicProperty(
                "App::PropertyString", "Warning", "Design", "Hint without an error (stays until confirmed)",
                App::Prop_Hidden));
        }
        if (std::string(warning->getValue()) != faceLost) {
            warning->setValue(faceLost);
        }
        return true;
    };
    if (this->isTouched_Mapping()) {
        try {
            // Nur wenn der Körper darunter sich geändert hat, nicht die Anheftung selbst (neu angeheftet, versetzt)
            // Ein nur umbenannter Bezug (FreeCADs Namensverfolgung setzt "Face29" -> "Face28", dasselbe Objekt) zählt nicht
            // als Änderung: er zeigte in ConceptKey auf die gegenüberliegende Wand, Skizze001 sprang dorthin
            const bool keep = (!AttachmentSupport.isTouched() || AttachmentSupport.getValues() == lastSupport)
                && !AttachmentOffset.isTouched() && !MapMode.isTouched() && !getExtendedObject()->isRestoring();
            bool turned = false;
            if (keep && refindFace(true, &turned)) {
                lastSupport = AttachmentSupport.getValues();
                return App::DocumentObjectExtension::extensionExecute();
            }
            if (turned && keepPlace("the face it was attached to now points elsewhere")) {
                return App::DocumentObjectExtension::extensionExecute();
            }
            positionBySupport();
            lastSupport = AttachmentSupport.getValues();
            if (warning && std::string(warning->getValue()) == faceLost) {
                warning->setValue("");  // Fläche wieder da
            }
        }
        catch (Base::Exception& e) {
            if (!refindFace(false) && !keepPlace(e.what())) {
                throw;
            }
        }
        catch (Standard_Failure& e) {
            if (!refindFace(false) && !keepPlace(e.GetMessageString())) {
                throw Base::RuntimeError(e.GetMessageString());
            }
        }
    }
    return App::DocumentObjectExtension::extensionExecute();
}

void AttachExtension::extensionOnChanged(const App::Property* prop)
{
    if (!getExtendedObject()->isRestoring()) {
        // If we change anything that affects our position, update it immediately so you can see it
        // interactively.
        // MyCAD: nur umbenannt (dieselben Objekte, FreeCADs Namensverfolgung nach einer Änderung weiter vorn): nicht sofort
        // springen, das Rechnen prüft, ob die Fläche noch in der Ebene liegt (extensionExecute). Sonst galt die falsche
        // Wand schon als letzte Lage, bevor geprüft wurde (ConceptKey: Skizze001 an der gegenüberliegenden Wand)
        const bool renamedOnly = prop == &AttachmentSupport && !lastSupport.empty()
            && AttachmentSupport.getValues() == lastSupport;
        if ((prop == &AttachmentSupport || prop == &MapMode || prop == &MapPathParameter
             || prop == &MapReversed || prop == &AttachmentOffset) && !renamedOnly) {
            bool bAttached = false;
            try {
                bAttached = positionBySupport();
            }
            catch (Base::Exception& e) {
                getExtendedObject()->setStatus(App::Error, true);
                Base::Console().error("PositionBySupport: {}\n", e.what());
                // set error message - how?
            }
            catch (Standard_Failure& e) {
                getExtendedObject()->setStatus(App::Error, true);
                Base::Console().error("PositionBySupport: {}\n", e.GetMessageString());
            }

            updateSinglePropertyStatus(bAttached);
        }
        if (prop == &AttacherEngine) {
            AttacherType.setValue(enumToClass(AttacherEngine.getValueAsString()));
        }
        else if (_props.matchProperty(prop)) {
            _active = -1;
            updateAttacherVals(/*base*/ false);
            updatePropertyStatus(isAttacherActive());
        }
        else if (_baseProps.matchProperty(prop)) {
            _active = -1;
            updateAttacherVals(/*base*/ true);
            updatePropertyStatus(isAttacherActive(), /*base*/ true);
        }
    }
    if (prop == &(this->AttacherType)) {
        this->changeAttacherType(this->AttacherType.getValue());
    }
    else if (prop == _baseProps.attacherType) {
        this->changeAttacherType(_baseProps.attacherType->getValue());
    }

    App::DocumentObjectExtension::extensionOnChanged(prop);
}

bool AttachExtension::extensionHandleChangedPropertyName(
    Base::XMLReader& reader,
    const char* TypeName,
    const char* PropName
)
{
    Base::Type type = Base::Type::fromName(TypeName);
    // superPlacement -> AttachmentOffset
    if (strcmp(PropName, "superPlacement") == 0 && AttachmentOffset.getClassTypeId() == type) {
        AttachmentOffset.Restore(reader);
        return true;
    }
    // Support -> AttachmentSupport
    if (strcmp(PropName, "Support") == 0) {
        // At one point, the type of Support changed from PropertyLinkSub to its present type
        // of PropertyLinkSubList. Later, the property name changed to AttachmentSupport
        App::PropertyLinkSub tmp;
        if (tmp.getTypeId().getName() == TypeName) {
            tmp.setContainer(this->getExtendedContainer());
            tmp.Restore(reader);
            if (tmp.getValue()) {
                AttachmentSupport.setValue(tmp.getValue(), tmp.getSubValues());
                this->MapMode.setValue(Attacher::mmFlatFace);
            }
            return true;
        }
        if (AttachmentSupport.getClassTypeId() == type) {
            App::PropertyLinkSubList tmp;
            tmp.setContainer(this->getExtendedContainer());
            tmp.Restore(reader);
            if (!tmp.getValues().empty()) {
                AttachmentSupport.Paste(tmp);
            }
            return true;
        }
    }
    return App::DocumentObjectExtension::extensionHandleChangedPropertyName(reader, TypeName, PropName);
}

void AttachExtension::handleLegacyTangentPlaneOrientation()
{
    // check attachment mode
    if (_props.attacher->mapMode != mmTangentPlane) {
        return;
    }

    // check stored document program version (applies to v1.0 and earlier only)
    if (Base::getVersion(getExtendedObject()->getDocument()->getProgramVersion())
        > Base::Version::v1_0) {
        return;
    }

    // check for an App::Plane support object exists
    App::GeoFeature* geof = nullptr;
    for (auto obj : this->AttachmentSupport.linkedObjects()) {
        if (obj->isDerivedFrom<App::Plane>()) {
            geof = freecad_cast<App::GeoFeature*>(obj);
            break;
        }
    }
    if (!geof) {
        return;
    }

    /*
     * determine which global axis (X/Y/Z) is closest to the plane normal
     */

    // extract the plane normal
    Base::Vector3d norm;
    geof->Placement.getValue().getRotation().multVec(Base::Vector3d(0.0, 0.0, 1.0), norm);
    gp_Dir normal(norm.x, norm.y, norm.z);

    // determine the dominant global axis
    std::array<double, 3> cosXYZ = {
        fabs(normal.Dot(gp_Dir(1, 0, 0))),  // normal dot global X axis
        fabs(normal.Dot(gp_Dir(0, 1, 0))),  // normal dot global Y axis
        fabs(normal.Dot(gp_Dir(0, 0, 1)))   // normal dot global Z axis
    };
    std::size_t axis = std::distance(cosXYZ.begin(), std::ranges::max_element(cosXYZ));

    // if Z is dominant, no changes needed
    if (axis == 2) {
        return;
    }

    /*
     * correct attachment offset position and rotation based on dominant axis
     */

    App::DocumentObject* owner = getExtendedObject();
    Base::Console().message("Converting attachment offset of {}\n", owner->getNameInDocument());

    try {
        // extract current attachment offset values
        Base::Placement placement = this->AttachmentOffset.getValue();
        Base::Vector3d position = placement.getPosition();
        Base::Rotation rotation = placement.getRotation();
        double yaw, pitch, roll;
        rotation.getYawPitchRoll(yaw, pitch, roll);

        // extract existing expressions
        auto buildOID = [owner](const std::vector<std::string>& path) {
            App::ObjectIdentifier oid(owner, true);
            for (const auto& name : path) {
                oid.addComponent(App::ObjectIdentifier::SimpleComponent(name));
            }
            return oid;
        };
        App::ObjectIdentifier oidX = buildOID({"AttachmentOffset", "Base", "x"});
        App::ObjectIdentifier oidY = buildOID({"AttachmentOffset", "Base", "y"});
        App::ObjectIdentifier oidYaw = buildOID({"AttachmentOffset", "Rotation", "Yaw"});
        const App::Expression* exprX = nullptr;
        const App::Expression* exprY = nullptr;
        const App::Expression* exprYaw = nullptr;
        for (const auto& [oid, expr] : owner->ExpressionEngine.getExpressions()) {
            if (oid == oidX) {
                exprX = expr;
            }
            else if (oid == oidY) {
                exprY = expr;
            }
            else if (oid == oidYaw) {
                exprYaw = expr;
            }
        }

        // convert placement and expressions according to the dominant axis
        auto makeRotatedExpression =
            [owner](const App::Expression* expr, double angle) -> App::ExpressionPtr {
            if (!expr) {
                return nullptr;
            }

            std::string unitSafeExprStr = "(" + expr->toString() + ")";
            if (angle >= 0) {
                unitSafeExprStr += " + " + std::to_string(angle);
            }
            else {
                unitSafeExprStr += " - " + std::to_string(-angle);
            }

            if (App::ExpressionPtr simple = expr->eval(); simple) {
                if (auto ue = dynamic_cast<const App::UnitExpression*>(simple.get())) {
                    const auto& q = ue->getQuantity();
                    if (q.getUnit() == Base::Unit::Angle) {
                        unitSafeExprStr += " deg";
                    }
                }
            }

            return App::ExpressionParser::parse(owner, unitSafeExprStr.c_str());
        };
        App::ExpressionPtr newExprX {};
        App::ExpressionPtr newExprY {};
        App::ExpressionPtr newExprYaw {};
        if (axis == 0) {  // normal mostly X
            // values
            std::swap(position.x, position.y);
            position.x = -position.x;
            rotation.setYawPitchRoll(yaw + 90, pitch, roll);

            // expressions
            if (exprX) {
                newExprY = App::ExpressionParser::parse(owner, exprX->toString().c_str());
            }
            if (exprY) {
                std::string expr = "-1 * (" + exprY->toString() + ")";
                newExprX = App::ExpressionParser::parse(owner, expr.c_str());
            }
            if (exprYaw) {
                if (yaw > 90) {
                    newExprYaw = makeRotatedExpression(exprYaw, -270);
                }
                else {
                    newExprYaw = makeRotatedExpression(exprYaw, 90);
                }
            }
        }
        else if (axis == 1) {  // normal mostly Y
            // values
            std::swap(position.x, position.y);
            position.y = -position.y;
            rotation.setYawPitchRoll(yaw - 90, pitch, roll);

            // expressions
            if (exprX) {
                std::string expr = "-1 * (" + exprX->toString() + ")";
                newExprY = App::ExpressionParser::parse(owner, expr.c_str());
            }
            if (exprY) {
                newExprX = App::ExpressionParser::parse(owner, exprY->toString().c_str());
            }
            if (exprYaw) {
                if (yaw < -90) {
                    newExprYaw = makeRotatedExpression(exprYaw, 270);
                }
                else {
                    newExprYaw = makeRotatedExpression(exprYaw, -90);
                }
            }
        }
        else {
            // should not happen
            return;
        }

        // store updated placement and expressions back to the document object

        // expressions
        owner->ExpressionEngine.setValue(oidX, std::move(newExprX));
        owner->ExpressionEngine.setValue(oidY, std::move(newExprY));
        owner->ExpressionEngine.setValue(oidYaw, std::move(newExprYaw));

        // values
        placement.setPosition(position);
        placement.setRotation(rotation);
        this->AttachmentOffset.setValue(placement);
    }
    catch (const Base::Exception& e) {
        Base::Console().error(
            "Error converting legacy attachment offset of {}: {}\n",
            owner->getNameInDocument(),
            e.what()
        );
    }
}

void AttachExtension::onExtendedDocumentRestored()
{
    lastSupport = AttachmentSupport.getValues();  // MyCAD: Stand aus der Datei (siehe extensionExecute)
    try {
        initBase(false);
        if (_baseProps.attachment) {
            _baseProps.attachment->setScope(App::LinkScope::Hidden);
        }
        if (_baseProps.attacherType) {
            changeAttacherType(_baseProps.attacherType->getValue(), true);
        }
        _active = -1;
        updatePropertyStatus(isAttacherActive());

        restoreAttacherEngine(this);

        if (_props.attacher->mapMode == mmTangentPlane) {
            handleLegacyTangentPlaneOrientation();
        }

        bool bAttached = positionBySupport();

        updateSinglePropertyStatus(bAttached);
    }
    catch (Base::Exception&) {
    }
    catch (Standard_Failure&) {
    }
}

void AttachExtension::updateSinglePropertyStatus(bool bAttached, bool base)
{
    auto& props = base ? this->_baseProps : this->_props;
    if (!props.mapMode) {
        return;
    }

    // Hide properties when not applicable to reduce user confusion
    eMapMode mmode = eMapMode(props.mapMode->getValue());
    bool modeIsPointOnCurve
        = (mmode == mmNormalToPath || mmode == mmFrenetNB || mmode == mmFrenetTN
           || mmode == mmFrenetTB || mmode == mmRevolutionSection || mmode == mmConcentric);

    // MapPathParameter is only used if there is a reference to one edge and not edge + vertex
    bool hasOneRef = props.attacher && props.attacher->subnames.size() == 1;

    props.mapPathParameter->setStatus(
        App::Property::Status::Hidden,
        !bAttached || !(modeIsPointOnCurve && hasOneRef)
    );
    props.mapReversed->setStatus(App::Property::Status::Hidden, !bAttached);

    if (base) {
        props.attachment->setStatus(App::Property::Status::Hidden, !bAttached);
    }
    else {
        this->AttachmentOffset.setStatus(App::Property::Status::Hidden, !bAttached);
        if (getExtendedContainer()) {
            // for mmTranslate, orientation should remain editable even when attached.
            getPlacement().setReadOnly(bAttached && mmode != mmTranslate);
        }
    }
}

void AttachExtension::updatePropertyStatus(bool bAttached, bool base)
{
    updateSinglePropertyStatus(bAttached, base);

    if (!base) {
        updateSinglePropertyStatus(bAttached, true);
    }
}

void AttachExtension::updateAttacherVals(bool base) const
{
    auto& props = base ? this->_baseProps : this->_props;
    if (!props.attachment) {
        return;
    }
    attacher(base).setUp(
        *props.attachment,
        eMapMode(props.mapMode->getValue()),
        props.mapReversed->getValue(),
        props.mapPathParameter->getValue(),
        0.0,
        0.0
    );
}

AttachExtension::Properties AttachExtension::getProperties(bool base) const
{
    return base ? _baseProps : _props;
}

AttachExtension::Properties AttachExtension::getInitedProperties(bool base)
{
    if (base) {
        initBase(true);
        return _baseProps;
    }
    return _props;
}

App::PropertyPlacement& AttachExtension::getPlacement() const
{
    auto pla = freecad_cast<App::PropertyPlacement*>(
        getExtendedObject()->getPropertyByName("Placement")
    );
    if (!pla) {
        throw Base::RuntimeError("AttachExtension cannot find placement property");
    }
    return *pla;
}

PyObject* AttachExtension::getExtensionPyObject()
{

    if (ExtensionPythonObject.is(Py::_None())) {
        // ref counter is set to 1
        ExtensionPythonObject = Py::Object(new AttachExtensionPy(this), true);
    }
    return Py::new_reference_to(ExtensionPythonObject);
}


Attacher::AttachEngine& AttachExtension::attacher(bool base) const
{
    auto& props = base ? _baseProps : _props;
    if (!props.attacher) {
        throw AttachEngineException("AttachableObject: no attacher is set.");
    }
    return *props.attacher;
}

// ------------------------------------------------

AttachEngineException::AttachEngineException()
    : Base::Exception()
{}

AttachEngineException::AttachEngineException(const char* sMessage)
    : Base::Exception(sMessage)
{}

AttachEngineException::AttachEngineException(const std::string& sMessage)
    : Base::Exception(sMessage)
{}

namespace App
{
/// @cond DOXERR
EXTENSION_PROPERTY_SOURCE_TEMPLATE(Part::AttachExtensionPython, Part::AttachExtension)
/// @endcond

// explicit template instantiation
template class PartExport ExtensionPythonT<Part::AttachExtension>;
}  // namespace App
