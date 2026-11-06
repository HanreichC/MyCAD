// SPDX-License-Identifier: LGPL-2.1-or-later
// Scribbles: freihand zeichnen mit Grafiktablett (Druck, Radierer-Ende) oder Maus. Gezeichnet wird auf einem Blatt, das
// sich im Raum umstellen lässt: auf eine Körperfläche, aufrecht entlang eines Strichs oder zur Ansicht hin. So entstehen
// aus 2D-Ideen 3D-Drahtmodelle. Hält der Stift am Ende eines Strichs kurz still, wird er zur Linie, zum Kreis oder Rechteck.

#include "ScribbleShapes.h"
#include "ViewProviders.h"

#include <App/Document.h>
#include <Base/Placement.h>
#include <Gui/Action.h>
#include <Gui/Application.h>
#include <Gui/BitmapFactory.h>
#include <Gui/Command.h>
#include <Gui/Document.h>
#include <Gui/Inventor/SoFCBoundingBox.h>
#include <Gui/View3DInventorViewer.h>
#include <Mod/Design/App/Features.h>

#include <Inventor/SbLine.h>
#include <Inventor/SbViewVolume.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoMarkerSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTransparencyType.h>
#include <Inventor/nodes/SoTriangleStripSet.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <Inventor/sensors/SoOneShotSensor.h>
#include <Inventor/system/gl.h>

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPointer>
#include <QTabletEvent>
#include <QTimer>

#include <optional>

#include <Gui/Shell/Theme.h>

#ifndef GL_DEPTH_CLAMP
#define GL_DEPTH_CLAMP 0x864F
#endif

using namespace DesignGui;
using Stroke = Design::Scribble::Stroke;
using Tool = ViewProviderScribble::Tool;

namespace
{

/// Werkzeug: Breite in Bildschirm-Pixeln bei vollem Druck, Anteil bei leichtestem Druck, Deckkraft der Farbe
struct Nib
{
    double px;
    double light;
    float alpha;
};
Nib nib(long tool)
{
    switch (tool) {
        case Design::Scribble::Pencil:
            return {1.8, 0.35, 0.8F};
        case Design::Scribble::Marker:
            return {16, 1.0, 0.35F};
        default:
            return {2.6, 0.45, 1.0F};
    }
}

/// Tinte: feste Werte des hellen Modus (MyStyle labelPrimary), das Blatt ist in Hell und Dunkel hell wie Post-its
constexpr Base::Color Ink(0x1D / 255.0F, 0x1D / 255.0F, 0x1F / 255.0F);

Tool currentTool = Tool::Pen;
Tool lastDrawTool = Tool::Pen;  ///< nach "Blatt umstellen" geht es mit diesem Werkzeug weiter
Base::Color currentColor = Ink;
ViewProviderScribble* active = nullptr;

constexpr std::pair<const char*, Tool> ToolCommands[] = {
    {"Design_ScribblePencil", Tool::Pencil}, {"Design_ScribblePen", Tool::Pen}, {"Design_ScribbleMarker", Tool::Marker},
    {"Design_ScribbleEraser", Tool::Eraser}, {"Design_ScribbleSheet", Tool::Sheet},
};

QAction* commandAction(const char* name)
{
    Gui::Command* cmd = Gui::Application::Instance->commandManager().getCommandByName(name);
    return cmd && cmd->getAction() ? cmd->getAction()->action() : nullptr;
}

/// Toolbar und Palette zeigen das aktive Werkzeug und das Transparentpapier als gedrückt
void syncActions()
{
    for (const auto& [name, tool] : ToolCommands) {
        if (QAction* a = commandAction(name)) {
            a->setCheckable(true);
            a->setChecked(active && tool == currentTool);
        }
    }
    if (QAction* a = commandAction("Design_ScribbleTracing")) {
        a->setCheckable(true);
        a->setChecked(active && static_cast<Design::Scribble*>(active->getObject())->Tracing.getValue());
    }
}

SbVec3f sb(const Base::Vector3d& v)
{
    return {float(v.x), float(v.y), float(v.z)};
}

Base::Vector3d vec(const SbVec3f& v)
{
    return Base::Vector3d(v[0], v[1], v[2]);
}

Base::Vector3d sheetNormal(const Base::Placement& sheet)
{
    return sheet.getRotation().multVec(Base::Vector3d(0, 0, 1));
}

/// Blatt mit Ursprung, Normale und einer Richtung, die (auf das Blatt projiziert) seine X-Achse wird
Base::Placement sheetAt(const Base::Vector3d& origin, Base::Vector3d xHint, Base::Vector3d normal)
{
    normal.Normalize();
    xHint = xHint - normal * (xHint * normal);
    if (xHint.Length() < 1e-9) {
        xHint = normal % Base::Vector3d(0, 1, 0);
        if (xHint.Length() < 1e-9) {
            xHint = normal % Base::Vector3d(1, 0, 0);
        }
    }
    return Base::Placement(origin, Base::Rotation::makeRotationByAxes(xHint, Base::Vector3d(), normal, "ZXY"));
}

/// Band eines Strichs in seiner Blatt-Ebene, mit runden Enden. Breite je Punkt, also dünner bei wenig Druck.
SoSeparator* strokeNode(const Stroke& s, const Base::Color& color)
{
    auto sep = new SoSeparator;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(color.r, color.g, color.b);
    material->transparency = 1.0F - color.a;
    sep->addChild(material);
    const size_t n = s.points.size();
    if (n == 0) {
        return sep;
    }
    Base::Vector3d normal = s.normal;
    normal.Normalize();
    const auto halfWidth = [&s](size_t i) { return std::max(1e-6, s.widths[i] / 2); };

    std::vector<SbVec3f> band;
    std::vector<SbVec3f> caps;
    std::vector<int> capSizes;
    // Halbkreis um p von +side über dir nach -side
    const auto cap = [&](const Base::Vector3d& p, const Base::Vector3d& side, const Base::Vector3d& dir, double r, int steps) {
        for (int k = 0; k <= steps; ++k) {
            const double t = M_PI * k / steps;
            caps.push_back(sb(p + side * (r * std::cos(t)) + dir * (r * std::sin(t))));
        }
        capSizes.push_back(steps + 1);
    };
    if (n == 1) {  // Tupfer: ganzer Kreis aus zwei Halbkreisen
        Base::Vector3d side = normal % Base::Vector3d(1, 0, 0);
        if (side.Length() < 1e-9) {
            side = normal % Base::Vector3d(0, 1, 0);
        }
        side.Normalize();
        cap(s.points[0], side, normal % side, halfWidth(0), 8);
        cap(s.points[0], side * -1, (normal % side) * -1, halfWidth(0), 8);
    }
    else {
        Base::Vector3d side, firstSide, firstDir, dir;
        for (size_t i = 0; i < n; ++i) {
            dir = s.points[std::min(i + 1, n - 1)] - s.points[i > 0 ? i - 1 : 0];
            if (dir.Length() > 1e-12) {
                dir.Normalize();
                Base::Vector3d next = normal % dir;
                if (next.Length() > 1e-12) {
                    side = next.Normalize();
                }
            }
            if (i == 0) {
                firstSide = side;
                firstDir = dir;
            }
            band.push_back(sb(s.points[i] + side * halfWidth(i)));
            band.push_back(sb(s.points[i] - side * halfWidth(i)));
        }
        cap(s.points.front(), firstSide, firstDir * -1, halfWidth(0), 6);
        cap(s.points.back(), side * -1, dir, halfWidth(n - 1), 6);
    }
    if (!band.empty()) {
        auto coords = new SoCoordinate3;
        coords->point.setValues(0, int(band.size()), band.data());
        auto strip = new SoTriangleStripSet;
        strip->numVertices.setValue(int(band.size()));
        sep->addChild(coords);
        sep->addChild(strip);
    }
    auto capCoords = new SoCoordinate3;
    capCoords->point.setValues(0, int(caps.size()), caps.data());
    auto capFaces = new SoFaceSet;
    capFaces->numVertices.setValues(0, int(capSizes.size()), capSizes.data());
    sep->addChild(capCoords);
    sep->addChild(capFaces);
    return sep;
}

/// 1 px breite Mittellinie: so bleibt ein Strich sichtbar, auch wenn man sein Blatt von der Kante sieht
SoSeparator* hairlineNode(const Stroke& s, const Base::Color& color)
{
    auto sep = new SoSeparator;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(color.r, color.g, color.b);
    sep->addChild(material);
    std::vector<SbVec3f> pts;
    for (const auto& p : s.points) {
        pts.push_back(sb(p));
    }
    auto coords = new SoCoordinate3;
    coords->point.setValues(0, int(pts.size()), pts.data());
    auto lines = new SoLineSet;
    lines->numVertices.setValue(int(pts.size()));
    sep->addChild(coords);
    sep->addChild(lines);
    return sep;
}

/// Gruppe für Striche: flache Farbe ohne Licht, beide Seiten sichtbar, nicht anklickbar
SoSeparator* inkGroup()
{
    auto sep = new SoSeparator;
    auto light = new SoLightModel;
    light->model = SoLightModel::BASE_COLOR;
    auto hints = new SoShapeHints;
    hints->vertexOrdering = SoShapeHints::UNKNOWN_ORDERING;
    hints->shapeType = SoShapeHints::UNKNOWN_SHAPE_TYPE;
    auto pick = new SoPickStyle;
    pick->style = SoPickStyle::UNPICKABLE;
    sep->addChild(light);
    sep->addChild(hints);
    sep->addChild(pick);
    return sep;
}

SoCallback* depthClamp(bool on)
{
    auto cb = new SoCallback;
    cb->setCallback(
        [](void* on, SoAction* action) {
            if (action->isOfType(SoGLRenderAction::getClassTypeId())) {
                on ? glEnable(GL_DEPTH_CLAMP) : glDisable(GL_DEPTH_CLAMP);
            }
        },
        on ? cb : nullptr);
    return cb;
}

/// Zeichenblatt: helles Papier mit Punktraster, das beim Zoomen in Zehnerschritten dichter oder gröber wird.
/// Wie das Bodenraster der Shell legt der Shader ein Quadrat um den Punkt des Blatts in der Bildmitte. Sieht man schräg
/// aufs Blatt (3D), wird es fast durchsichtig, damit man die Striche und das Modell im Raum sieht.
SoNode* paperNode(SoTransform* placement, SoShaderParameter4f* color)
{
    auto vertex = new SoVertexShader;
    vertex->sourceType = SoShaderObject::GLSL_PROGRAM;
    vertex->sourceProgram = R"(
        #version 120
        varying vec2 world;   // Punkt auf dem Blatt (mm)
        varying vec2 local;   // 1 = Bildrand, für das Auslaufen
        varying float facing; // 1 = gerade drauf, 0 = Blatt von der Kante gesehen
        void main()
        {
            vec3 n = gl_NormalMatrix * vec3(0.0, 0.0, 1.0);
            vec3 o = (gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
            float z = dot(n, o) / (abs(n.z) > 1e-3 ? n.z : 1e-3);
            float h = (gl_ProjectionMatrix[3][3] == 1.0 ? 1.0 : abs(z)) / gl_ProjectionMatrix[1][1];
            float r = h * max(1.0, gl_ProjectionMatrix[1][1] / gl_ProjectionMatrix[0][0]);
            vec2 center = (gl_ModelViewMatrixInverse * vec4(0.0, 0.0, z, 1.0)).xy;
            local = gl_Vertex.xy;
            world = center + local * r;
            facing = abs(normalize(n).z);
            gl_Position = gl_ModelViewProjectionMatrix * vec4(world, 0.0, 1.0);
        }
    )";
    auto fragment = new SoFragmentShader;
    fragment->sourceType = SoShaderObject::GLSL_PROGRAM;
    fragment->sourceProgram = R"(
        #version 120
        uniform vec4 paperColor;  // a = Deckkraft des Blatts
        varying vec2 world;
        varying vec2 local;
        varying float facing;
        // Rasterpunkte mit Abstand s, rund 1 px Radius
        float dots(float s, vec2 px)
        {
            vec2 d = abs(fract(world / s + 0.5) - 0.5) * s / px;
            return 1.0 - smoothstep(0.7, 1.5, length(d));
        }
        void main()
        {
            vec2 px = max(fwidth(world), vec2(1e-6));
            float lod = log(max(px.x, px.y) * 18.0) / log(10.0);  // Punktabstand mindestens 18 px
            float k = ceil(lod);
            float fine = clamp((k - lod) * 3.0, 0.0, 1.0);         // feine Stufe blendet weich ein
            float dot = max(fine * dots(pow(10.0, k), px), dots(pow(10.0, k + 1.0), px));
            // schräg wird das Papier fast durchsichtig, das Punktraster bleibt: es zeigt, wo das Blatt im Raum steht
            float fill = paperColor.a * mix(0.06, 1.0, smoothstep(0.8, 0.97, facing));
            float ink = 0.55 * dot * min(1.0, paperColor.a * 2.0);
            float a = max(fill, ink) * (1.0 - smoothstep(1.2, 1.9, length(local)));
            if (a < 0.004) {
                discard;
            }
            vec3 grey = vec3(0.63, 0.63, 0.65);  // labelTertiary (hell)
            gl_FragColor = vec4(mix(paperColor.rgb, grey, clamp(ink / max(fill, ink), 0.0, 1.0)), a);
        }
    )";
    fragment->parameter.set1Value(0, color);
    auto program = new SoShaderProgram;
    program->shaderObject.set1Value(0, vertex);
    program->shaderObject.set1Value(1, fragment);

    auto material = new SoMaterial;
    material->transparency = 0.5F;  // schaltet Blending ein; die Deckkraft kommt aus dem Shader
    auto coords = new SoCoordinate3;
    coords->point.setValues(0, 4, std::array<SbVec3f, 4> {{{-2, -2, 0}, {2, -2, 0}, {2, 2, 0}, {-2, 2, 0}}}.data());
    auto sep = new SoSeparator;
    sep->renderCulling = SoSeparator::OFF;  // die echte Lage entsteht erst im Shader
    for (SoNode* node : std::initializer_list<SoNode*> {placement, material, program, coords, depthClamp(true),
                                                        new SoFaceSet, depthClamp(false)}) {
        sep->addChild(node);
    }
    auto skip = new Gui::SoSkipBoundingGroup;  // Einpassen richtet sich nach den Strichen, nicht nach dem Blatt
    skip->mode = Gui::SoSkipBoundingGroup::EXCLUDE_BBOX;
    skip->addChild(sep);
    return skip;
}

double distanceToSegment(const QPointF& p, const QPointF& a, const QPointF& b)
{
    const QPointF ab = b - a;
    const double len2 = QPointF::dotProduct(ab, ab);
    const double t = len2 > 0 ? std::clamp(QPointF::dotProduct(p - a, ab) / len2, 0.0, 1.0) : 0.0;
    const QPointF d = p - (a + ab * t);
    return std::hypot(d.x(), d.y());
}

constexpr double SnapRadius = 10;   ///< px: so nah muss der Stift an ein Strich-Ende, damit er einrastet
constexpr double EraseRadius = 10;  ///< px
constexpr int HoldMs = 450;         ///< so lange still halten, damit ein Strich zur Form wird

}  // namespace

struct ViewProviderScribble::Private
{
    explicit Private(ViewProviderScribble* vp);

    Design::Scribble* object() const
    {
        return static_cast<Design::Scribble*>(vp->getObject());
    }

    void rebuild();
    void updatePaper();
    void updateSheet();

    // Koordinaten: "lokal" = Koordinaten der Komponente (darin liegen die Punkte), Bildschirm = Pixel im 3D-Fenster
    SbViewVolume viewVolume() const;
    QPointF toScreen(const Base::Vector3d& local) const;
    std::optional<Base::Vector3d> onSheet(const QPointF& pos) const;
    Base::Vector3d viewDirection() const;  ///< lokal, vom Auge weg
    std::optional<Base::Vector3d> snapEndpoint(const QPointF& pos, bool includeCurrent) const;
    bool overPanel(const QPointF& pos) const;

    void press(const QPointF& pos, double pressure, bool eraser);
    void move(const QPointF& pos, double pressure);
    void release(const QPointF& pos);
    void hover(const QPointF& pos);
    void addPoint(const Base::Vector3d& p, const QPointF& pos, double pressure);
    void shapeUp();
    void updateLineEnd(const QPointF& pos);
    void erase(const QPointF& pos);
    void pickSheet(const QPointF& pos);
    void showLive();
    void showSnap(const std::optional<Base::Vector3d>& p);
    void cancel();

    ViewProviderScribble* vp;
    SoSwitch* displaySwitch;   ///< Anzeige im Modell; im Zeichenmodus aus, dann zeigt das Blatt die Striche
    SoSeparator* displayInk;   ///< Striche mit Tiefe, Haarlinien, Tinte im Dunkelmodus hell
    SoSeparator* editRoot;     ///< Zeichenmodus: Blatt, Striche, laufender Strich, Fangpunkt, über allem anderen
    SoSeparator* editInk;
    SoSeparator* live;
    SoSwitch* snapSwitch;
    SoCoordinate3* snapCoords;
    SoTransform* sheetTransform;
    SoShaderParameter4f* paperColor;
    SoOneShotSensor rebuildSensor;

    Gui::View3DInventorViewer* viewer = nullptr;
    QPointer<QWidget> viewport;
    std::unique_ptr<QObject> input;
    Base::Matrix4D toWorld, toLocal;
    std::vector<Base::Vector3d> endpoints;  ///< Anfang und Ende jedes gespeicherten Strichs (fürs Einrasten)

    // laufende Geste
    bool down = false;
    bool fromTablet = false;
    Tool gesture = Tool::Pen;
    QPointF pressPos;
    Stroke current;
    std::vector<QPointF> screen;  ///< Bildschirmlage der Punkte von current
    double screenLength = 0;
    double mmPerPx = 0.1;
    std::optional<Base::Vector3d> snappedStart;
    bool shaped = false;
    QPointF anchor;
    QTimer hold;
    bool erased = false;
};

namespace
{

/// Stift und Maus im 3D-Fenster, solange ein Scribble offen ist. Der Stift zeichnet mit Druck, sein hinteres Ende radiert,
/// seine Seitentasten (und mittlere/rechte Maustaste) bleiben bei der Navigation (drehen, schieben).
class ScribbleInput: public QObject
{
public:
    explicit ScribbleInput(ViewProviderScribble::Private* d)
        : d(d)
    {}

protected:
    bool eventFilter(QObject*, QEvent* event) override
    {
        switch (event->type()) {
            case QEvent::TabletPress: {
                auto te = static_cast<QTabletEvent*>(event);
                if (te->button() != Qt::LeftButton || d->overPanel(te->position())) {
                    te->ignore();  // Qt macht daraus Mausereignisse: Navigation, Glas-Panels
                    return false;
                }
                d->fromTablet = true;
                d->press(te->position(), te->pressure(), te->pointerType() == QPointingDevice::PointerType::Eraser);
                te->accept();
                return true;
            }
            case QEvent::TabletMove: {
                auto te = static_cast<QTabletEvent*>(event);
                if (d->down && d->fromTablet) {
                    d->move(te->position(), te->pressure());
                }
                else if (te->buttons() != Qt::NoButton || d->overPanel(te->position())) {
                    te->ignore();
                    return false;
                }
                else {
                    d->hover(te->position());
                }
                te->accept();
                return true;
            }
            case QEvent::TabletRelease: {
                auto te = static_cast<QTabletEvent*>(event);
                if (!d->down || !d->fromTablet || te->button() != Qt::LeftButton) {
                    te->ignore();
                    return false;
                }
                d->release(te->position());
                te->accept();
                return true;
            }
            case QEvent::MouseButtonPress:
            case QEvent::MouseButtonDblClick: {
                auto me = static_cast<QMouseEvent*>(event);
                if (d->down) {
                    return true;
                }
                if (me->button() != Qt::LeftButton || d->overPanel(me->position())) {
                    return false;
                }
                if (event->type() == QEvent::MouseButtonPress) {
                    d->fromTablet = false;
                    d->press(me->position(), 0.6, false);  // Maus: mittlerer Druck
                }
                return true;
            }
            case QEvent::MouseMove: {
                auto me = static_cast<QMouseEvent*>(event);
                if (d->down) {
                    if (!d->fromTablet) {
                        d->move(me->position(), 0.6);
                    }
                    return true;
                }
                if (me->buttons() == Qt::NoButton && !d->overPanel(me->position())) {
                    d->hover(me->position());
                }
                return false;
            }
            case QEvent::MouseButtonRelease: {
                auto me = static_cast<QMouseEvent*>(event);
                if (!d->down) {
                    return false;
                }
                if (!d->fromTablet && me->button() == Qt::LeftButton) {
                    d->release(me->position());
                }
                return true;
            }
            default:
                return false;
        }
    }

private:
    ViewProviderScribble::Private* d;
};

}  // namespace

ViewProviderScribble::Private::Private(ViewProviderScribble* vp)
    : vp(vp)
{
    displaySwitch = new SoSwitch;
    displaySwitch->ref();
    auto display = inkGroup();
    auto offset = new SoPolygonOffset;  // Striche auf einer Körperfläche liegen vor der Fläche
    display->addChild(offset);
    displayInk = new SoSeparator;
    display->addChild(displayInk);
    displaySwitch->addChild(display);
    displaySwitch->whichChild = 0;

    editRoot = new SoSeparator;
    editRoot->ref();
    auto annotation = new SoAnnotation;  // nach allem anderen und ohne Tiefentest: Blatt deckt das Modell ab
    auto blend = new SoTransparencyType;  // in Reihenfolge mischen: Blatt, Striche, laufender Strich
    blend->value = SoTransparencyType::BLEND;
    annotation->addChild(blend);
    sheetTransform = new SoTransform;
    paperColor = new SoShaderParameter4f;
    paperColor->name = "paperColor";
    annotation->addChild(paperNode(sheetTransform, paperColor));
    auto ink = inkGroup();
    editInk = new SoSeparator;
    live = new SoSeparator;
    ink->addChild(editInk);
    ink->addChild(live);
    annotation->addChild(ink);

    snapSwitch = new SoSwitch;
    auto snap = inkGroup();
    auto snapMaterial = new SoMaterial;
    const QColor accent = Gui::Shell::theme().accentText;  // Ring ist eine Glyphe (MyStyle C-2)
    snapMaterial->diffuseColor.setValue(accent.redF(), accent.greenF(), accent.blueF());
    snapCoords = new SoCoordinate3;
    auto marker = new SoMarkerSet;
    marker->markerIndex = SoMarkerSet::CIRCLE_LINE_9_9;
    snap->addChild(snapMaterial);
    snap->addChild(snapCoords);
    snap->addChild(marker);
    snapSwitch->addChild(snap);
    annotation->addChild(snapSwitch);
    editRoot->addChild(annotation);

    rebuildSensor.setFunction([](void* data, SoSensor*) { static_cast<Private*>(data)->rebuild(); });
    rebuildSensor.setData(this);

    hold.setSingleShot(true);
    hold.setInterval(HoldMs);
    QObject::connect(&hold, &QTimer::timeout, [this] { shapeUp(); });
}

void ViewProviderScribble::Private::rebuild()
{
    displayInk->removeAllChildren();
    editInk->removeAllChildren();
    endpoints.clear();
    const bool dark = Gui::Shell::theme().dark;
    const QColor light = Gui::Shell::theme().labelPrimary;
    for (const Stroke& s : object()->strokes()) {
        // ohne Blatt im Dunkelmodus: schwarze Tinte wird hell, sonst verschwände sie im Hintergrund
        Base::Color shown = s.color;
        if (dark && std::abs(s.color.r - Ink.r) + std::abs(s.color.g - Ink.g) + std::abs(s.color.b - Ink.b) < 0.01F) {
            shown = Base::Color(float(light.redF()), float(light.greenF()), float(light.blueF()), s.color.a);
        }
        displayInk->addChild(strokeNode(s, shown));
        editInk->addChild(strokeNode(s, s.color));
        if (s.tool != Design::Scribble::Marker) {
            displayInk->addChild(hairlineNode(s, shown));
            editInk->addChild(hairlineNode(s, s.color));
        }
        if (!s.points.empty() && s.kind != Design::Scribble::Circle && s.kind != Design::Scribble::Rectangle) {
            endpoints.push_back(s.points.front());
            endpoints.push_back(s.points.back());
        }
    }
    if (!down) {
        live->removeAllChildren();  // der fertige Strich steht jetzt in editInk
    }
}

void ViewProviderScribble::Private::updatePaper()
{
    // Beim Umstellen fast durchsichtig: man muss die Körperfläche sehen, auf die man tippt
    const float opacity = active == vp && currentTool == Tool::Sheet ? 0.15F : object()->Tracing.getValue() ? 0.3F : 1.0F;
    paperColor->value.setValue(1, 1, 1, opacity);
}

void ViewProviderScribble::Private::updateSheet()
{
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Vector3d p = sheet.getPosition();
    const Base::Rotation r = sheet.getRotation();
    sheetTransform->translation.setValue(float(p.x), float(p.y), float(p.z));
    sheetTransform->rotation.setValue(float(r[0]), float(r[1]), float(r[2]), float(r[3]));
}

SbViewVolume ViewProviderScribble::Private::viewVolume() const
{
    const float aspect = viewer->getSoRenderManager()->getViewportRegion().getViewportAspectRatio();
    return viewer->getSoRenderManager()->getCamera()->getViewVolume(aspect);
}

QPointF ViewProviderScribble::Private::toScreen(const Base::Vector3d& local) const
{
    SbVec3f out;
    viewVolume().projectToScreen(sb(toWorld * local), out);
    return {out[0] * viewport->width(), (1.0 - out[1]) * viewport->height()};
}

std::optional<Base::Vector3d> ViewProviderScribble::Private::onSheet(const QPointF& pos) const
{
    SbLine line;
    viewVolume().projectPointToLine(SbVec2f(float(pos.x() / viewport->width()), float(1.0 - pos.y() / viewport->height())), line);
    const Base::Vector3d origin = toLocal * vec(line.getPosition());
    const Base::Vector3d dir = (toLocal * vec(line.getPosition() + line.getDirection())) - origin;
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Vector3d n = sheetNormal(sheet);
    const double facing = n * dir;
    if (std::abs(facing) < 1e-9) {
        return std::nullopt;  // Blatt genau von der Kante gesehen
    }
    return origin + dir * (n * (sheet.getPosition() - origin) / facing);
}

Base::Vector3d ViewProviderScribble::Private::viewDirection() const
{
    const Base::Vector3d origin = toLocal * Base::Vector3d();
    Base::Vector3d dir = toLocal * vec(viewer->getViewDirection()) - origin;
    return dir.Normalize();
}

std::optional<Base::Vector3d> ViewProviderScribble::Private::snapEndpoint(const QPointF& pos, bool includeCurrent) const
{
    std::optional<Base::Vector3d> best;
    double bestDist = SnapRadius;
    auto consider = [&](const Base::Vector3d& p) {
        const QPointF s = toScreen(p);
        const double dist = std::hypot(s.x() - pos.x(), s.y() - pos.y());
        if (dist < bestDist) {
            bestDist = dist;
            best = p;
        }
    };
    for (const auto& p : endpoints) {
        consider(p);
    }
    // den eigenen Anfang erst, wenn der Strich schon länger ist: so schließt sich eine Umrisslinie
    if (includeCurrent && !current.points.empty() && screenLength > 4 * SnapRadius) {
        consider(current.points.front());
    }
    return best;
}

bool ViewProviderScribble::Private::overPanel(const QPointF& pos) const
{
    auto view = viewport ? qobject_cast<QGraphicsView*>(viewport->parentWidget()) : nullptr;
    return view && view->itemAt(pos.toPoint());
}

void ViewProviderScribble::Private::press(const QPointF& pos, double pressure, bool eraser)
{
    App::Document* doc = vp->getObject()->getDocument();
    down = true;
    pressPos = pos;
    gesture = eraser ? Tool::Eraser : currentTool;
    hold.stop();
    if (gesture == Tool::Eraser) {
        erased = false;
        doc->openTransaction("Erase");
        erase(pos);
        return;
    }
    if (gesture == Tool::Sheet) {
        return;  // Tippen wertet release() aus
    }
    const auto p = onSheet(pos);
    const auto right = onSheet(pos + QPointF(1, 0));
    if (!p || !right) {
        down = false;
        return;
    }
    current = Stroke();
    screen.clear();
    screenLength = 0;
    shaped = false;
    current.tool = gesture == Tool::Pencil ? Design::Scribble::Pencil
        : gesture == Tool::Marker          ? Design::Scribble::Marker
                                           : Design::Scribble::Pen;
    current.color = currentColor;
    current.color.a = nib(current.tool).alpha;
    current.normal = sheetNormal(object()->Sheet.getValue());
    mmPerPx = std::max(1e-6, (*right - *p).Length());  // Breite in Pixeln: beim Zeichnen gleich dick, egal wie gezoomt
    snappedStart = snapEndpoint(pos, false);
    addPoint(snappedStart.value_or(*p), pos, pressure);
    anchor = pos;
    hold.start();
    showSnap(std::nullopt);
    showLive();
}

void ViewProviderScribble::Private::addPoint(const Base::Vector3d& p, const QPointF& pos, double pressure)
{
    const Nib n = nib(current.tool);
    current.points.push_back(p);
    current.widths.push_back(n.px * mmPerPx * (n.light + (1 - n.light) * std::clamp(pressure, 0.0, 1.0)));
    if (!screen.empty()) {
        screenLength += std::hypot(pos.x() - screen.back().x(), pos.y() - screen.back().y());
    }
    screen.push_back(pos);
}

void ViewProviderScribble::Private::move(const QPointF& pos, double pressure)
{
    if (gesture == Tool::Eraser) {
        erase(pos);
        return;
    }
    if (gesture == Tool::Sheet) {
        return;
    }
    if (shaped) {
        if (current.kind == Design::Scribble::Line) {
            updateLineEnd(pos);  // die Linie folgt dem Stift weiter, rastet an Enden und Achsen ein
        }
        return;
    }
    if (std::hypot(pos.x() - screen.back().x(), pos.y() - screen.back().y()) < 1.0) {
        return;  // dichter als ein Pixel bringt nichts
    }
    const auto p = onSheet(pos);
    if (!p) {
        return;
    }
    addPoint(*p, pos, pressure);
    if (std::hypot(pos.x() - anchor.x(), pos.y() - anchor.y()) > 4) {
        anchor = pos;
        hold.start();  // bewegt: Halten beginnt von vorn
    }
    showLive();
}

void ViewProviderScribble::Private::shapeUp()
{
    if (!down || shaped || gesture == Tool::Eraser || gesture == Tool::Sheet || current.points.size() < 3) {
        return;
    }
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Placement inverse = sheet.inverse();
    std::vector<ScribbleShapes::P> flat;
    for (const auto& p : current.points) {
        const Base::Vector3d q = inverse.toMatrix() * p;
        flat.push_back({q.x, q.y});
    }
    const ScribbleShapes::Shape shape = ScribbleShapes::recognize(flat);
    if (shape.kind == ScribbleShapes::Kind::Free) {
        return;
    }
    double width = 0;
    for (double w : current.widths) {
        width += w / double(current.widths.size());
    }
    current.points.clear();
    for (const auto& q : shape.points) {
        current.points.push_back(sheet.toMatrix() * Base::Vector3d(q.x, q.y, 0));
    }
    current.widths.assign(current.points.size(), width);
    current.kind = long(shape.kind);
    shaped = true;
    if (current.kind == Design::Scribble::Line) {
        if (snappedStart) {
            current.points.front() = *snappedStart;
        }
        updateLineEnd(screen.back());
    }
    showLive();
}

void ViewProviderScribble::Private::updateLineEnd(const QPointF& pos)
{
    std::optional<Base::Vector3d> end = snapEndpoint(pos, false);
    showSnap(end);
    if (!end) {
        const auto p = onSheet(pos);
        if (!p) {
            return;
        }
        const Base::Placement sheet = object()->Sheet.getValue();
        const Base::Matrix4D toSheet = sheet.inverse().toMatrix();
        const Base::Vector3d a = toSheet * current.points.front(), b = toSheet * *p;
        const ScribbleShapes::P r = ScribbleShapes::snapAxis({a.x, a.y}, {b.x, b.y});
        end = sheet.toMatrix() * Base::Vector3d(r.x, r.y, 0);
    }
    current.points.back() = *end;
    showLive();
}

void ViewProviderScribble::Private::release(const QPointF& pos)
{
    down = false;
    hold.stop();
    showSnap(std::nullopt);
    App::Document* doc = vp->getObject()->getDocument();
    if (gesture == Tool::Eraser) {
        erased ? doc->commitTransaction() : doc->abortTransaction();
        return;
    }
    if (gesture == Tool::Sheet) {
        if (std::hypot(pos.x() - pressPos.x(), pos.y() - pressPos.y()) < 6) {
            pickSheet(pos);
        }
        return;
    }
    if (current.points.empty()) {
        return;
    }
    if (!shaped && current.points.size() > 1) {
        if (auto end = snapEndpoint(pos, true)) {
            current.points.back() = *end;
        }
    }
    doc->openTransaction("Scribble");
    auto all = object()->strokes();
    all.push_back(current);
    object()->setStrokes(all);
    doc->commitTransaction();
}

void ViewProviderScribble::Private::hover(const QPointF& pos)
{
    showSnap(currentTool == Tool::Eraser || currentTool == Tool::Sheet ? std::nullopt : snapEndpoint(pos, false));
}

void ViewProviderScribble::Private::erase(const QPointF& pos)
{
    const auto all = object()->strokes();
    std::vector<Stroke> keep;
    for (const Stroke& s : all) {
        bool hit = false;
        QPointF prev = s.points.empty() ? QPointF() : toScreen(s.points.front());
        for (size_t i = 0; i < s.points.size() && !hit; ++i) {
            const QPointF here = toScreen(s.points[i]);
            hit = distanceToSegment(pos, prev, here) < EraseRadius;
            prev = here;
        }
        if (!hit) {
            keep.push_back(s);
        }
    }
    if (keep.size() != all.size()) {
        object()->setStrokes(keep);
        erased = true;
    }
}

void ViewProviderScribble::Private::pickSheet(const QPointF& pos)
{
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Vector3d xAxis = sheet.getRotation().multVec(Base::Vector3d(1, 0, 0));
    const Base::Vector3d view = viewDirection();
    std::optional<Base::Placement> next;

    // gerader Strich (Linie, Rechteckkante): Blatt stellt sich entlang dieser Linie auf, senkrecht zum bisherigen Blatt
    for (const Stroke& s : object()->strokes()) {
        if ((s.kind != Design::Scribble::Line && s.kind != Design::Scribble::Rectangle) || next) {
            continue;
        }
        for (size_t i = 1; i < s.points.size() && !next; ++i) {
            if (distanceToSegment(pos, toScreen(s.points[i - 1]), toScreen(s.points[i])) > SnapRadius) {
                continue;
            }
            Base::Vector3d dir = s.points[i] - s.points[i - 1];
            dir.Normalize();
            Base::Vector3d normal = dir % sheetNormal(sheet);
            if (normal.Length() < 1e-6) {  // Linie steht schon senkrecht zum Blatt: Blatt durch sie, zur Ansicht hin
                normal = dir % (view % dir);
            }
            if (normal * view > 0) {
                normal = normal * -1;  // Vorderseite zum Betrachter
            }
            next = sheetAt(s.points[i - 1], dir, normal);
        }
    }
    // Körperfläche (auch gewölbt: dann die Tangentialebene) oder Ebene
    SbVec3f point, normal;
    if (!next && viewer->pickPoint(viewer->fromQPoint(pos.toPoint()), point, normal)) {
        const Base::Vector3d p = toLocal * vec(point);
        Base::Vector3d n = (toLocal * vec(point + normal)) - p;
        if (n * view > 0) {
            n = n * -1;
        }
        next = sheetAt(p, xAxis, n);
    }
    // ins Leere: Blatt dreht sich zur Ansicht, bleibt aber, wo es ist
    if (!next) {
        const Base::Vector3d up = toLocal * vec(viewer->getUpDirection()) - toLocal * Base::Vector3d();
        next = sheetAt(sheet.getPosition(), up % (view * -1), view * -1);
    }
    App::Document* doc = vp->getObject()->getDocument();
    doc->openTransaction("Move Sheet");
    object()->Sheet.setValue(*next);
    doc->commitTransaction();
    setTool(lastDrawTool);
}

void ViewProviderScribble::Private::showLive()
{
    live->removeAllChildren();
    if (!current.points.empty()) {
        live->addChild(strokeNode(current, current.color));
    }
}

void ViewProviderScribble::Private::showSnap(const std::optional<Base::Vector3d>& p)
{
    snapSwitch->whichChild = p ? 0 : SO_SWITCH_NONE;
    if (p) {
        snapCoords->point.setValue(sb(*p));
    }
}

void ViewProviderScribble::Private::cancel()
{
    if (down && gesture == Tool::Eraser) {
        App::Document* doc = vp->getObject()->getDocument();
        erased ? doc->commitTransaction() : doc->abortTransaction();
    }
    down = false;
    hold.stop();
    current = Stroke();
    live->removeAllChildren();
    showSnap(std::nullopt);
}

PROPERTY_SOURCE(DesignGui::ViewProviderScribble, Gui::ViewProviderDocumentObject)

ViewProviderScribble::ViewProviderScribble()
    : d(std::make_unique<Private>(this))
{}

ViewProviderScribble::~ViewProviderScribble()
{
    if (active == this) {
        active = nullptr;
    }
    d->rebuildSensor.unschedule();
    d->displaySwitch->unref();
    d->editRoot->unref();
}

void ViewProviderScribble::attach(App::DocumentObject* obj)
{
    Gui::ViewProviderDocumentObject::attach(obj);
    addDisplayMaskMode(d->displaySwitch, "Scribble");
    d->updateSheet();
    d->updatePaper();
    d->rebuild();
}

std::vector<std::string> ViewProviderScribble::getDisplayModes() const
{
    return {"Scribble"};
}

const char* ViewProviderScribble::getDefaultDisplayMode() const
{
    return "Scribble";
}

void ViewProviderScribble::setDisplayMode(const char* mode)
{
    setDisplayMaskMode("Scribble");
    Gui::ViewProviderDocumentObject::setDisplayMode(mode);
}

void ViewProviderScribble::updateData(const App::Property* prop)
{
    auto obj = static_cast<Design::Scribble*>(getObject());
    if (prop == &obj->Sheet) {
        d->updateSheet();
    }
    else if (prop == &obj->Tracing) {
        d->updatePaper();
        syncActions();
    }
    else if (prop == &obj->Points || prop == &obj->Widths || prop == &obj->Counts || prop == &obj->Tools
             || prop == &obj->Kinds || prop == &obj->Colors || prop == &obj->Normals) {
        d->rebuildSensor.schedule();  // setStrokes ändert sieben Listen: einmal neu aufbauen
    }
    Gui::ViewProviderDocumentObject::updateData(prop);
}

QIcon ViewProviderScribble::getIcon() const
{
    return QIcon(Gui::BitmapFactory().pixmapFromSvg(":/mycad/icons/Design_Scribble.svg", QSize(32, 32)));
}

bool ViewProviderScribble::doubleClicked()
{
    return Gui::Application::Instance->getDocument(getObject()->getDocument())->setEdit(this);
}

bool ViewProviderScribble::setEdit(int ModNum)
{
    if (ModNum != Default) {
        return false;
    }
    active = this;
    return true;
}

void ViewProviderScribble::unsetEdit(int)
{
    if (active == this) {
        active = nullptr;
    }
    syncActions();
}

void ViewProviderScribble::setEditViewer(Gui::View3DInventorViewer* viewer, int ModNum)
{
    Q_UNUSED(ModNum);
    d->viewer = viewer;
    d->toWorld = Gui::Application::Instance->getDocument(getObject()->getDocument())->getEditingTransform();
    d->toLocal = d->toWorld;
    d->toLocal.inverseGauss();
    viewer->setupEditingRoot(d->editRoot, &d->toWorld);
    viewer->setEditing(true);
    viewer->setSelectionEnabled(false);
    d->displaySwitch->whichChild = SO_SWITCH_NONE;
    d->viewport = viewer->viewport();
    d->input = std::make_unique<ScribbleInput>(d.get());
    d->viewport->installEventFilter(d->input.get());
    d->viewport->setAttribute(Qt::WA_TabletTracking);  // Stift in der Luft: Fangpunkt schon vor dem Aufsetzen zeigen
    if (currentTool == Tool::Eraser || currentTool == Tool::Sheet) {
        currentTool = lastDrawTool;  // jedes Öffnen beginnt mit einem Stift
    }
    setTool(currentTool);
    lookAtSheet();  // jedes Öffnen (Toolbar, Doppelklick, Bearbeiten im Browser) schaut gerade aufs Blatt
}

void ViewProviderScribble::unsetEditViewer(Gui::View3DInventorViewer* viewer)
{
    d->cancel();
    if (d->viewport) {
        d->viewport->removeEventFilter(d->input.get());
        d->viewport->setAttribute(Qt::WA_TabletTracking, false);
    }
    d->input.reset();
    d->viewport = nullptr;
    d->viewer = nullptr;
    d->displaySwitch->whichChild = 0;
    viewer->setEditing(false);
    viewer->setSelectionEnabled(true);
}

bool ViewProviderScribble::keyPressed(bool pressed, int key)
{
    // Esc legt "Blatt umstellen" weg; ohne dieses Werkzeug schließt Esc das Scribble (FreeCADs Vorgabe)
    if (key == SoKeyboardEvent::ESCAPE && currentTool == Tool::Sheet) {
        if (!pressed) {
            setTool(lastDrawTool);
        }
        return true;
    }
    return Gui::ViewProviderDocumentObject::keyPressed(pressed, key);
}

ViewProviderScribble* ViewProviderScribble::editing()
{
    return active;
}

ViewProviderScribble::Tool ViewProviderScribble::tool()
{
    return currentTool;
}

void ViewProviderScribble::setTool(Tool tool)
{
    currentTool = tool;
    if (tool != Tool::Eraser && tool != Tool::Sheet) {
        lastDrawTool = tool;
    }
    if (active && active->d->viewer) {
        active->d->viewer->setEditingCursor(QCursor(tool == Tool::Sheet ? Qt::PointingHandCursor : Qt::CrossCursor));
        active->d->updatePaper();
        active->d->showSnap(std::nullopt);
    }
    syncActions();
}

void ViewProviderScribble::setColor(const Base::Color& color)
{
    currentColor = color;
    if (currentTool == Tool::Eraser || currentTool == Tool::Sheet) {
        setTool(lastDrawTool);  // Farbe wählen heißt weiterzeichnen
    }
}

const Base::Color& ViewProviderScribble::ink()
{
    return Ink;
}

void ViewProviderScribble::lookAtSheet()
{
    Gui::View3DInventorViewer* viewer = d->viewer;
    if (!viewer) {
        return;
    }
    const Base::Placement world = Base::Placement(d->toWorld) * static_cast<Design::Scribble*>(getObject())->Sheet.getValue();
    const Base::Rotation r = world.getRotation();
    // wie beim Öffnen einer Skizze: Kamera auf das Blatt, gerade von vorn
    SoCamera* camera = viewer->getSoRenderManager()->getCamera();
    SbVec3f dir;
    camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
    camera->position.setValue(sb(world.getPosition()) - camera->focalDistance.getValue() * dir);
    viewer->setCameraOrientation(SbRotation(float(r[0]), float(r[1]), float(r[2]), float(r[3])));
}
