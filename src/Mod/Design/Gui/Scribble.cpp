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
#include <QPolygonF>
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

/// Tinte: gespeichert als labelPrimary des hellen Modus, damit die Datei nicht vom Modus abhängt
constexpr Base::Color Ink(0x1D / 255.0F, 0x1D / 255.0F, 0x1F / 255.0F);

/// Farbe auf dem Bildschirm: schwarze Tinte ist im Dunkelmodus labelPrimary (hell), auf dem dunklen Blatt und im Modell
Base::Color shown(const Base::Color& c)
{
    if (!Gui::Shell::theme().dark || std::abs(c.r - Ink.r) + std::abs(c.g - Ink.g) + std::abs(c.b - Ink.b) >= 0.01F) {
        return c;
    }
    const QColor light = Gui::Shell::theme().labelPrimary;
    return Base::Color(float(light.redF()), float(light.greenF()), float(light.blueF()), c.a);
}

Tool currentTool = Tool::Pen;
Tool lastDrawTool = Tool::Pen;  ///< nach "Blatt umstellen" geht es mit diesem Werkzeug weiter; Formen zeichnen mit ihm
Base::Color currentColor = Ink;
ViewProviderScribble* active = nullptr;

bool isPen(Tool t)
{
    return t == Tool::Pencil || t == Tool::Pen || t == Tool::Marker;
}

constexpr std::pair<const char*, Tool> ToolCommands[] = {
    {"Design_ScribblePencil", Tool::Pencil}, {"Design_ScribblePen", Tool::Pen}, {"Design_ScribbleMarker", Tool::Marker},
    {"Design_ScribbleEraser", Tool::Eraser}, {"Design_ScribbleSheet", Tool::Sheet}, {"Design_ScribbleLine", Tool::Line},
    {"Design_ScribbleRectangle", Tool::Rectangle}, {"Design_ScribbleCircle", Tool::Circle},
    {"Design_ScribbleArrow", Tool::Arrow}, {"Design_ScribbleTriangle", Tool::Triangle},
    {"Design_ScribbleHexagon", Tool::Hexagon}, {"Design_ScribbleEllipse", Tool::Ellipse}, {"Design_ScribbleFill", Tool::Fill},
    {"Design_ScribbleSelect", Tool::Select},
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
SoSeparator* strokeNode(const Stroke& s)
{
    Base::Color color = shown(s.color);
    if (s.tool == Design::Scribble::Marker && Gui::Shell::theme().dark) {
        color.a = 0.6F;  // ponytail: kein MyStyle-Token; mit 0,35 wird Leuchtfarbe auf dunklem Grund olivbraun
    }
    auto sep = new SoSeparator;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(color.r, color.g, color.b);
    material->transparency = 1.0F - color.a;
    sep->addChild(material);
    const size_t n = s.points.size();
    if (n == 0) {
        return sep;
    }
    if (s.kind == Design::Scribble::Fill) {  // Fläche im Umriss, auch nach innen gewölbt (Coin zerlegt sie)
        auto hints = new SoShapeHints;
        hints->faceType = SoShapeHints::UNKNOWN_FACE_TYPE;
        hints->vertexOrdering = SoShapeHints::UNKNOWN_ORDERING;
        std::vector<SbVec3f> pts;
        for (const auto& p : s.points) {
            pts.push_back(sb(p));
        }
        if (pts.size() > 1 && pts.front() == pts.back()) {
            pts.pop_back();
        }
        auto coords = new SoCoordinate3;
        coords->point.setValues(0, int(pts.size()), pts.data());
        auto face = new SoFaceSet;
        face->numVertices.setValue(int(pts.size()));
        sep->addChild(hints);
        sep->addChild(coords);
        sep->addChild(face);
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
    std::vector<int> stripSizes;
    // ein Stück a..b ohne Knick: Band entlang der Punkte, runde Enden an beiden Seiten
    const auto run = [&](size_t a, size_t b) {
        Base::Vector3d side, firstSide, firstDir, dir;
        for (size_t i = a; i <= b; ++i) {
            dir = s.points[std::min(i + 1, b)] - s.points[i > a ? i - 1 : a];
            if (dir.Length() > 1e-12) {
                dir.Normalize();
                Base::Vector3d next = normal % dir;
                if (next.Length() > 1e-12) {
                    side = next.Normalize();
                }
            }
            if (i == a) {
                firstSide = side;
                firstDir = dir;
            }
            band.push_back(sb(s.points[i] + side * halfWidth(i)));
            band.push_back(sb(s.points[i] - side * halfWidth(i)));
        }
        stripSizes.push_back(int(2 * (b - a + 1)));
        cap(s.points[a], firstSide, firstDir * -1, halfWidth(a), 6);
        cap(s.points[b], side * -1, dir, halfWidth(b), 6);
    };
    if (n > 1) {
        // an Knicken über 30° (Rechteckecken, Zickzack) teilen: ein durchgehendes Band verdrehte sich dort und würde
        // bis zur nächsten Ecke fast unsichtbar dünn; die runden Enden der Stücke ergeben eine runde Ecke. Nur wenn
        // beide Abschnitte länger als die Strichbreite sind, sonst hätte der Marker an jedem Pixel-Knick dunkle Tupfer
        size_t from = 0;
        for (size_t i = 1; i + 1 < n; ++i) {
            Base::Vector3d in = s.points[i] - s.points[i - 1], out = s.points[i + 1] - s.points[i];
            const double minLength = 2 * halfWidth(i);
            if (in.Length() > minLength && out.Length() > minLength && in.Normalize() * out.Normalize() < 0.87) {
                run(from, i);
                from = i;
            }
        }
        run(from, n - 1);
    }
    if (!band.empty()) {
        auto coords = new SoCoordinate3;
        coords->point.setValues(0, int(band.size()), band.data());
        auto strip = new SoTriangleStripSet;
        strip->numVertices.setValues(0, int(stripSizes.size()), stripSizes.data());
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
SoSeparator* hairlineNode(const Stroke& s)
{
    const Base::Color color = shown(s.color);
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

/// Zeichenblatt: Papier (warmes Weiß, dunkel warmes system.gray5, siehe updatePaper) mit Punktraster in labelTertiary, das beim Zoomen in
/// Zehnerschritten dichter oder gröber wird.
/// Wie das Bodenraster der Shell legt der Shader ein Quadrat um den Punkt des Blatts in der Bildmitte. Sieht man schräg
/// aufs Blatt (3D), wird es fast durchsichtig, damit man die Striche und das Modell im Raum sieht.
SoNode* paperNode(SoTransform* placement, SoShaderParameter4f* color, SoShaderParameter3f* dotColor)
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
        uniform vec3 dotColor;
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
            gl_FragColor = vec4(mix(paperColor.rgb, dotColor, clamp(ink / max(fill, ink), 0.0, 1.0)), a);
        }
    )";
    fragment->parameter.set1Value(0, color);
    fragment->parameter.set1Value(1, dotColor);
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

    void rebuild(bool editOnly = false);
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
    void updateShape(const QPointF& pos);
    QPolygonF screenPolygon(const Stroke& s) const;
    void fillAt(const QPointF& pos);
    void erase(const QPointF& pos);
    bool hits(const Stroke& s, const QPointF& pos) const;
    int hitStroke(const QPointF& pos) const;  ///< oberster Strich unter dem Stift, sonst -1
    bool selected(int i) const;
    QRectF selectionBox() const;               ///< Bildschirm, mit Rand; leer ohne Auswahl
    double pixelSize() const;                  ///< mm je Pixel in der Bildmitte, auf dem Blatt
    void grab(const QPointF& pos);
    void showSelection();
    void showLasso();
    void deleteSelection();
    void pickSheet(const QPointF& pos);
    void showLive();
    void showSnap(const std::optional<Base::Vector3d>& p);
    void cancel();

    ViewProviderScribble* vp;
    SoSwitch* displaySwitch;   ///< Anzeige im Modell; im Zeichenmodus aus, dann zeigt das Blatt die Striche
    SoSeparator* displayInk;   ///< Striche mit Tiefe, Haarlinien
    SoSeparator* editRoot;     ///< Zeichenmodus: Blatt, Striche, laufender Strich, Fangpunkt, über allem anderen
    SoSeparator* editInk;
    SoSeparator* selectionInk;  ///< Schein unter den ausgewählten Strichen und gestrichelter Rahmen
    SoSeparator* live;
    SoSwitch* snapSwitch;
    SoCoordinate3* snapCoords;
    SoTransform* sheetTransform;
    SoShaderParameter4f* paperColor;
    SoShaderParameter3f* dotColor;
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
    Base::Vector3d start;  ///< Form-Werkzeug: wo das Ziehen begann (Linienanfang, Ecke, Kreismitte)
    bool shaped = false;
    QPointF anchor;
    QTimer hold;
    bool erased = false;

    // Auswählen und Verschieben
    std::vector<int> selection;      ///< Nummern in strokes()
    bool moving = false;
    Base::Vector3d grabFrom;         ///< wo das Ziehen begann (auf dem Blatt)
    Base::Vector3d moveOffset;       ///< bisher gezogen
    int grabCandidate = -1;          ///< Stift auf einem Strich: Halten greift ihn
    std::vector<QPointF> lasso;      ///< Bildschirm
    bool overSelection = false;      ///< Mauszeiger zeigt "verschieben"
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
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        // Tasten kommen je nach Fokus beim Viewport oder bei der Ansicht an. Entf ist auch ein Befehlskürzel
        // (Std_Delete): solange etwas ausgewählt ist, gehört die Taste der Auswahl
        if (event->type() == QEvent::ShortcutOverride || event->type() == QEvent::KeyPress) {
            const int key = static_cast<QKeyEvent*>(event)->key();
            const bool mine = !d->selection.empty()
                && (key == Qt::Key_Delete || key == Qt::Key_Backspace || key == Qt::Key_Escape);
            if (mine && event->type() == QEvent::KeyPress) {
                if (key == Qt::Key_Escape) {
                    d->selection.clear();
                    d->showSelection();
                }
                else {
                    d->deleteSelection();
                }
            }
            if (mine) {
                event->accept();
            }
            return mine;
        }
        if (obj != d->viewport) {
            return false;
        }
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
    dotColor = new SoShaderParameter3f;
    dotColor->name = "dotColor";
    annotation->addChild(paperNode(sheetTransform, paperColor, dotColor));
    auto ink = inkGroup();
    editInk = new SoSeparator;
    selectionInk = new SoSeparator;
    live = new SoSeparator;
    ink->addChild(selectionInk);
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

void ViewProviderScribble::Private::rebuild(bool editOnly)
{
    if (!editOnly) {
        displayInk->removeAllChildren();
    }
    editInk->removeAllChildren();
    endpoints.clear();
    const auto strokes = object()->strokes();
    std::erase_if(selection, [&strokes](int i) { return i >= int(strokes.size()); });  // nach Rückgängig
    for (const bool fills : {true, false}) {  // Flächen zuerst: die Linien liegen darüber
        for (int i = 0; i < int(strokes.size()); ++i) {
            const Stroke& s = strokes[size_t(i)];
            if ((s.kind == Design::Scribble::Fill) != fills) {
                continue;
            }
            Stroke shifted = s;  // beim Verschieben zeigt das Blatt die Auswahl schon am neuen Ort
            if (moving && selected(i)) {
                for (auto& q : shifted.points) {
                    q += moveOffset;
                }
            }
            if (!editOnly) {
                displayInk->addChild(strokeNode(s));
            }
            editInk->addChild(strokeNode(shifted));
            if (s.tool != Design::Scribble::Marker) {
                if (!editOnly) {
                    displayInk->addChild(hairlineNode(s));
                }
                editInk->addChild(hairlineNode(shifted));
            }
            // offene Striche rasten an ihren Enden ein (Freihand, Linie, Pfeil)
            if (!s.points.empty()
                && (s.kind == Design::Scribble::Free || s.kind == Design::Scribble::Line || s.kind == Design::Scribble::Polygon)) {
                endpoints.push_back(s.points.front());
                endpoints.push_back(s.points.back());
            }
        }
    }
    if (!down) {
        live->removeAllChildren();  // der fertige Strich steht jetzt in editInk
    }
    showSelection();
}

void ViewProviderScribble::Private::updatePaper()
{
    // Beim Umstellen fast durchsichtig: man muss die Körperfläche sehen, auf die man tippt
    const float opacity = active == vp && currentTool == Tool::Sheet ? 0.15F : object()->Tracing.getValue() ? 0.3F : 1.0F;
    const Gui::Shell::Theme& t = Gui::Shell::theme();
    // warmer Papierton wie bei den Notizen (C-8, glass.noteTint), nur ein Hauch: hell Weiß mit system.yellow (Creme),
    // dunkel system.gray5 mit system.orange (warmes Anthrazit)
    // ponytail: die Anteile 0,07 und 0,04 sind kein MyStyle-Token; ein "glass.paperTint" gehörte dorthin
    const QColor base = t.dark ? t.gray5 : QColor(Qt::white), warm = t.dark ? t.orange : t.yellow;
    const double f = t.dark ? 0.04 : 0.07;
    const auto channel = [f](double a, double b) { return float(a + (b - a) * f); };
    paperColor->value.setValue(channel(base.redF(), warm.redF()), channel(base.greenF(), warm.greenF()),
                               channel(base.blueF(), warm.blueF()), opacity);
    dotColor->value.setValue(float(t.labelTertiary.redF()), float(t.labelTertiary.greenF()), float(t.labelTertiary.blueF()));
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
    if (gesture == Tool::Select) {
        // auf der Auswahl oder einem Strich: ziehen (ein anderer Strich wird dabei die Auswahl); sonst umranden
        const int hit = hitStroke(pos);
        if ((hit >= 0 && selected(hit)) || selectionBox().contains(pos)) {
            grab(pos);
        }
        else if (hit >= 0) {
            selection = {hit};
            grab(pos);
        }
        else {
            selection.clear();
            lasso = {pos};
            showSelection();
        }
        return;
    }
    grabCandidate = isPen(gesture) ? hitStroke(pos) : -1;
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
    const Tool pen = isPen(gesture) ? gesture : lastDrawTool;
    current.tool = pen == Tool::Pencil ? Design::Scribble::Pencil
        : pen == Tool::Marker          ? Design::Scribble::Marker
                                       : Design::Scribble::Pen;
    current.color = currentColor;
    current.color.a = nib(current.tool).alpha;
    current.normal = sheetNormal(object()->Sheet.getValue());
    mmPerPx = std::max(1e-6, (*right - *p).Length());  // Breite in Pixeln: beim Zeichnen gleich dick, egal wie gezoomt
    snappedStart = snapEndpoint(pos, false);
    addPoint(snappedStart.value_or(*p), pos, pressure);
    anchor = pos;
    showSnap(std::nullopt);
    if (gesture == Tool::Fill) {  // Umranden wie mit dem Stift, Farbe wie ein Marker
        current.tool = Design::Scribble::Marker;
        current.color.a = nib(current.tool).alpha;
        current.kind = Design::Scribble::Fill;
        return;
    }
    if (!isPen(gesture)) {
        shaped = true;  // die Form steht von Anfang an fest, Halten braucht es nicht
        current.kind = gesture == Tool::Line ? Design::Scribble::Line
            : gesture == Tool::Rectangle     ? Design::Scribble::Rectangle
            : gesture == Tool::Circle        ? Design::Scribble::Circle
            : gesture == Tool::Ellipse       ? Design::Scribble::Ellipse
                                             : Design::Scribble::Polygon;
        start = current.points.front();
        return;
    }
    hold.start();
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
    if (gesture == Tool::Select) {
        if (moving) {
            if (const auto p = onSheet(pos)) {
                moveOffset = *p - grabFrom;
                rebuild(true);
            }
        }
        else {
            lasso.push_back(pos);
            showLasso();
        }
        return;
    }
    if (!isPen(gesture) && gesture != Tool::Fill) {
        updateShape(pos);
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
    if (isPen(gesture) && std::hypot(pos.x() - anchor.x(), pos.y() - anchor.y()) > 4) {
        anchor = pos;
        hold.start();  // bewegt: Halten beginnt von vorn
    }
    showLive();
}

void ViewProviderScribble::Private::shapeUp()
{
    // Halten zum Greifen: der Stift steht seit dem Aufsetzen still auf einem Strich, dann hängt der Strich am Stift
    if (down && isPen(gesture) && grabCandidate >= 0 && screenLength < 4) {
        current = Stroke();
        live->removeAllChildren();
        selection = {grabCandidate};
        gesture = Tool::Select;
        grab(pressPos);
        return;
    }
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

/// Form-Werkzeug beim Ziehen (Formen in ScribbleShapes::dragged). Linie und Pfeil rasten wie eine Linie an Achsen
/// und Strich-Enden ein, die anderen Formen mit dem Stift an Strich-Enden; alle liegen achsparallel zum Blatt.
void ViewProviderScribble::Private::updateShape(const QPointF& pos)
{
    const double width = current.widths.front();
    std::optional<Base::Vector3d> end;
    if (gesture == Tool::Line || gesture == Tool::Arrow) {
        current.points = {start, start};
        current.widths = {width, width};
        updateLineEnd(pos);
        if (gesture == Tool::Line) {
            return;
        }
        end = current.points.back();
    }
    else {
        end = snapEndpoint(pos, false);
        showSnap(end);
        if (!end) {
            end = onSheet(pos);
        }
    }
    if (!end) {
        return;
    }
    using ScribbleShapes::Drag;
    const Drag drag = gesture == Tool::Rectangle ? Drag::Rectangle
        : gesture == Tool::Ellipse              ? Drag::Ellipse
        : gesture == Tool::Triangle             ? Drag::Triangle
        : gesture == Tool::Circle               ? Drag::Circle
        : gesture == Tool::Hexagon              ? Drag::Hexagon
                                                : Drag::Arrow;
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Matrix4D toSheet = sheet.inverse().toMatrix(), fromSheet = sheet.toMatrix();
    const Base::Vector3d a = toSheet * start, b = toSheet * *end;
    const double head = std::max(18 * mmPerPx, 4 * width);  // Pfeilspitze: gut sichtbar, auch beim Marker
    current.points.clear();
    for (const ScribbleShapes::P& q : ScribbleShapes::dragged(drag, {a.x, a.y}, {b.x, b.y}, head)) {
        current.points.push_back(fromSheet * Base::Vector3d(q.x, q.y, 0));
    }
    current.widths.assign(current.points.size(), width);
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
    if (gesture == Tool::Select) {
        if (moving) {
            moving = false;
            const Base::Vector3d offset = moveOffset;
            moveOffset = Base::Vector3d();
            if (offset.Length() > 1e-9) {
                auto all = object()->strokes();
                for (int i : selection) {
                    for (auto& q : all[size_t(i)].points) {
                        q += offset;
                    }
                }
                doc->openTransaction("Move Strokes");
                object()->setStrokes(all);
                doc->commitTransaction();
            }
            if (currentTool != Tool::Select) {
                selection.clear();  // mit dem Stift gegriffen: danach geht es mit dem Stift weiter
            }
            rebuild(true);
            return;
        }
        // umrandet: ausgewählt ist, was überwiegend im Umriss liegt
        const QPolygonF loop(QList<QPointF>(lasso.begin(), lasso.end()));
        const auto all = object()->strokes();
        for (int i = 0; lasso.size() > 2 && i < int(all.size()); ++i) {
            const QPolygonF poly = screenPolygon(all[size_t(i)]);
            const auto inside = std::count_if(poly.begin(), poly.end(), [&loop](const QPointF& q) {
                return loop.containsPoint(q, Qt::OddEvenFill);
            });
            if (!poly.isEmpty() && inside * 10 >= poly.size() * 6) {
                selection.push_back(i);
            }
        }
        lasso.clear();
        live->removeAllChildren();
        showSelection();
        return;
    }
    if (current.points.empty()) {
        return;
    }
    const bool tapped = std::hypot(pos.x() - pressPos.x(), pos.y() - pressPos.y()) < 3 && screenLength < 6;
    if (gesture == Tool::Fill && (tapped || current.points.size() < 3)) {
        live->removeAllChildren();
        if (tapped) {
            fillAt(pos);
        }
        current = Stroke();
        return;
    }
    if (gesture == Tool::Fill) {  // umrandete Fläche: Zittern und Überhang weg, geschlossen
        const Base::Placement sheet = object()->Sheet.getValue();
        const Base::Matrix4D toSheet = sheet.inverse().toMatrix(), fromSheet = sheet.toMatrix();
        std::vector<ScribbleShapes::P> flat;
        for (const auto& p : current.points) {
            const Base::Vector3d q = toSheet * p;
            flat.push_back({q.x, q.y});
        }
        current.points.clear();
        for (const auto& q : ScribbleShapes::lasso(flat, mmPerPx)) {
            current.points.push_back(fromSheet * Base::Vector3d(q.x, q.y, 0));
        }
        current.widths.assign(current.points.size(), 0);
    }
    else if (!isPen(gesture) && tapped) {
        current = Stroke();  // nur getippt: keine Form ohne Größe
        live->removeAllChildren();
        return;
    }
    if (!shaped && gesture != Tool::Fill && current.points.size() > 1) {
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
    const bool snaps = currentTool != Tool::Eraser && currentTool != Tool::Sheet && currentTool != Tool::Fill
        && currentTool != Tool::Select;
    showSnap(snaps ? snapEndpoint(pos, false) : std::nullopt);
    const bool over = currentTool == Tool::Select && (selectionBox().contains(pos) || hitStroke(pos) >= 0);
    if (over != overSelection && viewer) {
        overSelection = over;
        viewer->setEditingCursor(QCursor(over ? Qt::SizeAllCursor : Qt::ArrowCursor));
    }
}

bool ViewProviderScribble::Private::hits(const Stroke& s, const QPointF& pos) const
{
    QPointF prev = s.points.empty() ? QPointF() : toScreen(s.points.front());
    for (const auto& p : s.points) {
        const QPointF here = toScreen(p);
        if (distanceToSegment(pos, prev, here) < EraseRadius) {
            return true;
        }
        prev = here;
    }
    return s.kind == Design::Scribble::Fill && screenPolygon(s).containsPoint(pos, Qt::OddEvenFill);
}

int ViewProviderScribble::Private::hitStroke(const QPointF& pos) const
{
    const auto all = object()->strokes();
    for (int i = int(all.size()) - 1; i >= 0; --i) {  // oben liegt, was zuletzt gezeichnet wurde; Linien vor Flächen
        if (all[size_t(i)].kind != Design::Scribble::Fill && hits(all[size_t(i)], pos)) {
            return i;
        }
    }
    for (int i = int(all.size()) - 1; i >= 0; --i) {
        if (hits(all[size_t(i)], pos)) {
            return i;
        }
    }
    return -1;
}

bool ViewProviderScribble::Private::selected(int i) const
{
    return std::ranges::find(selection, i) != selection.end();
}

QRectF ViewProviderScribble::Private::selectionBox() const
{
    QRectF box;
    const auto all = object()->strokes();
    for (int i : selection) {
        box = box.united(screenPolygon(all[size_t(i)]).boundingRect());
    }
    return box.isNull() ? box : box.adjusted(-8, -8, 8, 8);
}

double ViewProviderScribble::Private::pixelSize() const
{
    const QPointF c(viewport->width() / 2.0, viewport->height() / 2.0);
    const auto a = onSheet(c), b = onSheet(c + QPointF(1, 0));
    return a && b ? std::max(1e-6, (*b - *a).Length()) : mmPerPx;
}

void ViewProviderScribble::Private::grab(const QPointF& pos)
{
    const auto p = onSheet(pos);
    if (!p) {
        down = false;
        return;
    }
    moving = true;
    grabFrom = *p;
    moveOffset = Base::Vector3d();
    showSelection();
}

/// Auswahl: ein Schein in Akzentfarbe unter jedem Strich und ein gestrichelter Rahmen um alle, im Blatt gezeichnet
void ViewProviderScribble::Private::showSelection()
{
    selectionInk->removeAllChildren();
    const auto all = object()->strokes();
    if (selection.empty() || !viewport) {
        return;
    }
    const Gui::Shell::Theme& t = Gui::Shell::theme();
    const double px = pixelSize();
    const Base::Vector3d offset = moving ? moveOffset : Base::Vector3d();
    for (int i : selection) {
        Stroke glow = all[size_t(i)];
        glow.kind = Design::Scribble::Polygon;  // eine Fläche leuchtet an ihrem Umriss
        glow.tool = Design::Scribble::Pen;
        glow.color = Base::Color(float(t.accent.redF()), float(t.accent.greenF()), float(t.accent.blueF()), 0.35F);
        for (size_t k = 0; k < glow.points.size(); ++k) {
            glow.points[k] += offset;
            glow.widths[k] += 8 * px;
        }
        selectionInk->addChild(strokeNode(glow));
    }
    // Rahmen in Blatt-Koordinaten um alle Punkte
    const Base::Placement sheet = object()->Sheet.getValue();
    const Base::Matrix4D toSheet = sheet.inverse().toMatrix(), fromSheet = sheet.toMatrix();
    double x0 = 1e300, y0 = 1e300, x1 = -1e300, y1 = -1e300;
    for (int i : selection) {
        for (const auto& q : all[size_t(i)].points) {
            const Base::Vector3d r = toSheet * (q + offset);
            x0 = std::min(x0, r.x); y0 = std::min(y0, r.y); x1 = std::max(x1, r.x); y1 = std::max(y1, r.y);
        }
    }
    const double m = 8 * px;
    std::vector<SbVec3f> box;
    for (const auto& [x, y] : {std::pair {x0 - m, y0 - m}, {x1 + m, y0 - m}, {x1 + m, y1 + m}, {x0 - m, y1 + m}, {x0 - m, y0 - m}}) {
        box.push_back(sb(fromSheet * Base::Vector3d(x, y, 0)));
    }
    auto sep = new SoSeparator;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(float(t.accentText.redF()), float(t.accentText.greenF()), float(t.accentText.blueF()));
    auto style = new SoDrawStyle;
    style->linePattern = 0xF0F0;  // gestrichelt
    style->lineWidth = 1.5F;
    auto coords = new SoCoordinate3;
    coords->point.setValues(0, int(box.size()), box.data());
    auto lines = new SoLineSet;
    lines->numVertices.setValue(int(box.size()));
    sep->addChild(material);
    sep->addChild(style);
    sep->addChild(coords);
    sep->addChild(lines);
    selectionInk->addChild(sep);
}

/// Umriss beim Umranden: gestrichelt in Akzentfarbe
void ViewProviderScribble::Private::showLasso()
{
    live->removeAllChildren();
    std::vector<SbVec3f> pts;
    for (const QPointF& q : lasso) {
        if (const auto p = onSheet(q)) {
            pts.push_back(sb(*p));
        }
    }
    if (pts.size() < 2) {
        return;
    }
    const QColor accent = Gui::Shell::theme().accentText;
    auto material = new SoMaterial;
    material->diffuseColor.setValue(float(accent.redF()), float(accent.greenF()), float(accent.blueF()));
    auto style = new SoDrawStyle;
    style->linePattern = 0xF0F0;
    style->lineWidth = 1.5F;
    auto coords = new SoCoordinate3;
    coords->point.setValues(0, int(pts.size()), pts.data());
    auto lines = new SoLineSet;
    lines->numVertices.setValue(int(pts.size()));
    live->addChild(material);
    live->addChild(style);
    live->addChild(coords);
    live->addChild(lines);
}

void ViewProviderScribble::Private::deleteSelection()
{
    auto all = object()->strokes();
    std::vector<Stroke> keep;
    for (int i = 0; i < int(all.size()); ++i) {
        if (!selected(i)) {
            keep.push_back(all[size_t(i)]);
        }
    }
    selection.clear();
    App::Document* doc = vp->getObject()->getDocument();
    doc->openTransaction("Delete Strokes");
    object()->setStrokes(keep);
    doc->commitTransaction();
    showSelection();
}

QPolygonF ViewProviderScribble::Private::screenPolygon(const Stroke& s) const
{
    QPolygonF poly;
    for (const auto& p : s.points) {
        poly << toScreen(p);
    }
    return poly;
}

/// Tippen mit Füllen: die kleinste geschlossene Form unter dem Stift wird in der aktuellen Farbe gefüllt, eine schon
/// gefüllte Fläche umgefärbt.
/// ponytail: nur einzelne geschlossene Striche (Formen, Umrisse mit eingerastetem Ende, Füllflächen); Flächen, die erst
/// mehrere Striche zusammen umschließen, bräuchten eine Schnittpunkt-Zerlegung aller Striche
void ViewProviderScribble::Private::fillAt(const QPointF& pos)
{
    auto all = object()->strokes();
    int best = -1;
    double bestArea = 0;
    for (int i = 0; i < int(all.size()); ++i) {
        const Stroke& s = all[size_t(i)];
        if (s.points.size() < 4) {
            continue;
        }
        const QPolygonF poly = screenPolygon(s);
        const QPointF gap = poly.front() - poly.back();
        if (std::hypot(gap.x(), gap.y()) > 1.5 || !poly.containsPoint(pos, Qt::OddEvenFill)) {
            continue;  // offen, oder der Stift ist nicht darin
        }
        double area = 0;
        for (int k = 1; k < poly.size(); ++k) {
            area += poly[k - 1].x() * poly[k].y() - poly[k].x() * poly[k - 1].y();
        }
        area = std::abs(area) / 2;
        // gleich groß: die Füllfläche gewinnt gegen ihren Umriss, damit Tippen umfärbt statt eine zweite Lage zu legen
        if (best < 0 || area < bestArea - 1e-9
            || (std::abs(area - bestArea) <= 1e-9 && s.kind == Design::Scribble::Fill)) {
            best = i;
            bestArea = area;
        }
    }
    if (best < 0) {
        return;
    }
    Base::Color color = currentColor;
    color.a = nib(Design::Scribble::Marker).alpha;
    App::Document* doc = vp->getObject()->getDocument();
    doc->openTransaction("Fill");
    Stroke& target = all[size_t(best)];
    if (target.kind == Design::Scribble::Fill) {
        target.color = color;
    }
    else {
        Stroke fill;
        fill.points = target.points;
        fill.widths.assign(fill.points.size(), 0);
        fill.tool = Design::Scribble::Marker;
        fill.kind = Design::Scribble::Fill;
        fill.color = color;
        fill.normal = target.normal;
        all.push_back(fill);
    }
    object()->setStrokes(all);
    doc->commitTransaction();
}

void ViewProviderScribble::Private::erase(const QPointF& pos)
{
    const auto all = object()->strokes();
    std::vector<Stroke> keep;
    for (const Stroke& s : all) {
        if (!hits(s, pos)) {
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
        if ((s.kind != Design::Scribble::Line && s.kind != Design::Scribble::Rectangle && s.kind != Design::Scribble::Polygon)
            || next) {
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
        live->addChild(strokeNode(current));
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
    moving = false;
    moveOffset = Base::Vector3d();
    lasso.clear();
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
    if (d->viewport->parentWidget()) {
        d->viewport->parentWidget()->installEventFilter(d->input.get());  // Tasten, wenn die Ansicht den Fokus hat
    }
    d->viewport->setAttribute(Qt::WA_TabletTracking);  // Stift in der Luft: Fangpunkt schon vor dem Aufsetzen zeigen
    if (!isPen(currentTool)) {
        currentTool = lastDrawTool;  // jedes Öffnen beginnt mit einem Stift
    }
    d->rebuild();  // Hell/Dunkel kann seit dem letzten Aufbau gewechselt haben: Tinte passend zum Blatt
    setTool(currentTool);
    lookAtSheet();  // jedes Öffnen (Toolbar, Doppelklick, Bearbeiten im Browser) schaut gerade aufs Blatt
}

void ViewProviderScribble::unsetEditViewer(Gui::View3DInventorViewer* viewer)
{
    d->cancel();
    if (d->viewport) {
        d->viewport->removeEventFilter(d->input.get());
        if (d->viewport->parentWidget()) {
            d->viewport->parentWidget()->removeEventFilter(d->input.get());
        }
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
    // Esc legt Blatt umstellen und die Formen weg (zurück zum Stift); beim Stift oder Radierer schließt Esc das Scribble
    if (key == SoKeyboardEvent::ESCAPE && currentTool != Tool::Eraser && !isPen(currentTool)) {
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
    if (isPen(tool)) {
        lastDrawTool = tool;
    }
    if (active && active->d->viewer) {
        active->d->viewer->setEditingCursor(QCursor(tool == Tool::Sheet ? Qt::PointingHandCursor
                                                        : tool == Tool::Select ? Qt::ArrowCursor
                                                                               : Qt::CrossCursor));
        active->d->overSelection = false;
        active->d->updatePaper();
        active->d->showSnap(std::nullopt);
        if (tool != Tool::Select) {
            active->d->selection.clear();
            active->d->showSelection();
        }
    }
    syncActions();
}

void ViewProviderScribble::setColor(const Base::Color& color)
{
    currentColor = color;
    if (active && !active->d->selection.empty()) {  // Auswahl umfärben, jede Strich-Art behält ihre Deckkraft
        auto all = active->d->object()->strokes();
        for (int i : active->d->selection) {
            const float alpha = all[size_t(i)].color.a;
            all[size_t(i)].color = color;
            all[size_t(i)].color.a = alpha;
        }
        App::Document* doc = active->getObject()->getDocument();
        doc->openTransaction("Color Strokes");
        active->d->object()->setStrokes(all);
        doc->commitTransaction();
        return;
    }
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
