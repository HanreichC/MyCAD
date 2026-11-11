// SPDX-License-Identifier: LGPL-2.1-or-later

#include "BodyShading.h"

#include <App/Application.h>

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDepthBuffer.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransparencyType.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoVertexShader.h>

#include <Gui/BitmapFactory.h>
#include <Gui/Inventor/SoFCBoundingBox.h>
#include <Gui/SoFCOffscreenRenderer.h>

#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QTimer>

#include <GL/gl.h>
#include <GL/glext.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace
{

constexpr int SurfaceUnit = 1;  ///< Normale und Rauheit des Fotoscans; Stufe 0 hat seine Farbe (TextureExtension)
constexpr int EnvUnit = 2;      ///< Umgebung "Raum"

/// Bild als GL-Textur je Kontext an eine Stufe binden. Direkt in GL statt über einen SoTexture2-Knoten: Coin erzeugte
/// sonst für die Stufe Texturkoordinaten und ließe den schnellen Zeichenweg der Flächen aus.
struct GlImage
{
    QString path;
    int unit;
    bool tiled;  ///< kachelt und hat Mipmaps (Fotoscan); sonst Kugelkarte
    std::map<QOpenGLContext*, GLuint> textures;
};

void bindImage(void* data, SoAction* action)
{
    if (!action->isOfType(SoGLRenderAction::getClassTypeId())) {
        return;
    }
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    if (!ctx) {
        return;
    }
    auto image = static_cast<GlImage*>(data);
    QOpenGLFunctions* f = ctx->functions();
    f->glActiveTexture(GL_TEXTURE0 + image->unit);
    auto known = image->textures.find(ctx);
    if (known == image->textures.end()) {
        // 16 Bit (Umgebung) bleibt 16 Bit: 8 Bit reichten nicht für Lichtflächen und dunkle Ecken zugleich
        const QImage source(image->path);
        const bool deep = source.depth() == 64;
        const QImage img = source.convertToFormat(deep ? QImage::Format_RGBA64 : QImage::Format_RGBA8888);
        GLuint tex = 0;
        f->glGenTextures(1, &tex);
        f->glBindTexture(GL_TEXTURE_2D, tex);
        f->glTexImage2D(GL_TEXTURE_2D, 0, deep ? GL_RGBA16 : GL_RGBA, img.width(), img.height(), 0, GL_RGBA,
                        deep ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE, img.constBits());
        // Kugelkarte ohne Mipmaps: an ihrer Naht (u = 0/1) wählte die GPU sonst eine winzige Stufe, eine Linie wäre zu sehen
        if (image->tiled) {
            f->glGenerateMipmap(GL_TEXTURE_2D);
        }
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, image->tiled ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, image->tiled ? GL_REPEAT : GL_CLAMP_TO_EDGE);
        known = image->textures.emplace(ctx, tex).first;
        QObject::connect(ctx, &QOpenGLContext::aboutToBeDestroyed, [image, ctx] { image->textures.erase(ctx); });
    }
    f->glBindTexture(GL_TEXTURE_2D, known->second);
    f->glActiveTexture(GL_TEXTURE0);
}

SoCallback* imageBinder(const QString& path, int unit, bool tiled)
{
    auto bind = new SoCallback;
    bind->setCallback(bindImage, new GlImage {path, unit, tiled, {}});  // lebt bis zum Programmende wie der Knoten
    return bind;
}

const char* const Vertex = R"(
#version 120
varying vec3 objNormal;  // Objekt-Koordinaten: darin steht die Umgebung (Z oben)
varying vec3 objPos;
varying vec3 eyePos;
varying vec4 baseColor;
void main()
{
    objNormal = gl_Normal;
    objPos = gl_Vertex.xyz;
    eyePos = (gl_ModelViewMatrix * gl_Vertex).xyz;
    baseColor = gl_Color;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;  // Schnittebenen der Ansicht schneiden weiter
    gl_Position = ftransform();
}
)";

const char* const Fragment = R"(
#version 120
uniform int coin_light_model;     // von Coin: 0 = Grundfarbe (Auswahl, Vorauswahl), 1 = beleuchtet
uniform int coin_texunit0_model;  // von Coin: 0 = keine Textur auf Stufe 0
uniform sampler2D baseMap;        // Stufe 0: Farbe des Fotoscans oder eigenes Bild
uniform sampler2D surfaceMap;     // Stufe 1: Normale x/y und Rauheit des Fotoscans (tools/fetch_textures.py)
uniform sampler2D envMap;         // Stufe 2: Umgebung "Studio" oder "Raum", 6 Ebenen 512x256 untereinander, 16 Bit, Wert² * 128
uniform float exposure;
uniform int detail;               // 1: Oberflächen-Karten, Hirnholz, Druckschichten (Einstellung "Relief und Hirnholz")
uniform int reflections;          // 0: keine Spiegelbilder, nur weicher Glanz (Einstellung "Spiegelungen")
varying vec3 objNormal;
varying vec3 objPos;
varying vec3 eyePos;
varying vec4 baseColor;

const float PI = 3.14159265;
const float LEVELS = 6.0;
const float TILE = 200.0;  // mm je Kachel vor der Texturmatrix, wie faceTextureCoordinates in ViewProviderExt.cpp
const vec3 LUM = vec3(0.2126, 0.7152, 0.0722);

vec3 envLevel(vec3 d, float level)
{
    float u = atan(d.y, d.x) / (2.0 * PI) + 0.5;
    float v = clamp(acos(clamp(d.z, -1.0, 1.0)) / PI, 0.5 / 256.0, 1.0 - 0.5 / 256.0);
    vec3 c = texture2D(envMap, vec2(u, (level + v) / LEVELS)).rgb;
    return c * c * 128.0;  // Wurzel-kodiert, tools/make_environment.py
}

/// Spiegelung aus der Umgebung, Ebene 0 (scharf) bis 4 (rau), dazwischen gemischt. Ohne Spiegelungen nur die weichen
/// Ebenen: Glanz und Form bleiben lesbar, Fenster und Lampen tauchen nicht auf.
vec3 envSpecular(vec3 d, float roughness)
{
    float level = clamp(reflections == 1 ? roughness : max(roughness, 0.85), 0.0, 1.0) * 4.0;
    float l0 = floor(level);
    return mix(envLevel(d, l0), envLevel(d, min(l0 + 1.0, 4.0)), level - l0);
}

/// Karis' Näherung des Glanz-Integrals (UE4 Mobile): spart die Tabelle der Split-Sum-Methode
vec2 envBRDF(float NoV, float roughness)
{
    const vec4 c0 = vec4(-1.0, -0.0275, -0.572, 0.022);
    const vec4 c1 = vec4(1.0, 0.0425, 1.04, -0.04);
    vec4 r = roughness * c0 + c1;
    float a004 = min(r.x * r.x, exp2(-9.28 * NoV)) * r.x + r.y;
    return vec2(-1.04, 1.04) * a004 + r.zw;
}

/// Khronos PBR Neutral: Farben bleiben bis kurz vor Weiß, wie sie sind (für CAD besser als ACES)
vec3 neutral(vec3 color)
{
    const float start = 0.76;
    const float desaturation = 0.15;
    float x = min(color.r, min(color.g, color.b));
    float offset = x < 0.08 ? x - 6.25 * x * x : 0.04;
    color -= offset;
    float peak = max(color.r, max(color.g, color.b));
    if (peak < start) {
        return color;
    }
    float d = 1.0 - start;
    float newPeak = 1.0 - d * d / (peak + d - start);
    color *= newPeak / peak;
    float g = 1.0 - 1.0 / (desaturation * (peak - newPeak) + 1.0);
    return mix(color, vec3(newPeak), g);
}

/// Kachelkoordinate eines Punkts der Ebene (mm), im Maßstab der Textur (SoTexture2Transform aus bodyTexture)
vec2 tile(vec2 mm)
{
    return (gl_TextureMatrix[0] * vec4(mm / TILE, 0.0, 1.0)).xy;
}

/// Hirnholz: Jahresringe um eine Markröhre weit unter dem Brett, gestört von der Maserung; Farbe aus der Textur, dunkler
vec3 endGrain(vec2 q)
{
    vec3 hue = (texture2D(baseMap, tile(q * 0.05)).rgb + texture2D(baseMap, tile(q * 0.05 + vec2(37.0, 11.0))).rgb) * 0.5;
    vec2 d = q - vec2(-60.0, -110.0);
    float angle = atan(d.y, d.x);
    // Ringe ungleich breit und leicht wellig: Wachstum je Jahr und Richtung verschieden
    float r = length(d) * (1.0 + 0.04 * sin(5.0 * angle + 1.3) + 0.025 * sin(11.0 * angle));
    float f = r / 2.6 + 0.9 * sin(r * 0.37) + 1.6 * dot(texture2D(baseMap, tile(q * 0.4)).rgb, LUM);
    float ring = pow(fract(f), 4.0);  // Frühholz hell und breit, Spätholz schmal und dunkel
    ring = mix(ring, 0.2, clamp(fwidth(f) * 1.5 - 0.3, 0.0, 1.0));  // klein auf dem Schirm: mitteln statt flimmern
    float pores = dot(texture2D(baseMap, tile(q * 1.7)).rgb, LUM) / max(dot(hue, LUM), 0.05);  // Poren aus der Maserung
    return hue * (0.80 - 0.30 * ring) * mix(1.0, pores, 0.35);
}

void main()
{
    if (coin_light_model == 0) {  // Auswahl und Vorauswahl: Farbe wie gehabt
        gl_FragColor = baseColor;
        return;
    }
    // Markierungen in der Leuchtfarbe (unsichtbar, siehe BodyShading.h): Rot 1/255 eigenes Bild, 2/255 Fotoscan;
    // Grün Bits 1 Klarlack, 2 Schliff entlang x, 4 Holz (Hirnholz an x-Flächen), 8 Druckschichten entlang z;
    // Blau 1/255 kein Metall, 2/255 Metall
    vec3 e = gl_FrontMaterial.emission.rgb * 255.0;
    bool marked = e.r < 2.5 && e.g < 15.5 && e.b > 0.5 && e.b < 2.5;
    float flags = marked ? floor(e.g + 0.5) : 0.0;
    bool coat = mod(flags, 2.0) > 0.5;
    bool brushed = mod(floor(flags / 2.0), 2.0) > 0.5;
    bool wood = mod(floor(flags / 4.0), 2.0) > 0.5;
    bool layers = flags > 7.5;
    bool scan = e.r > 1.5 && e.r < 2.5;

    vec3 N = normalize(objNormal);
    if (!gl_FrontFacing) {
        N = -N;
    }
    vec4 base = baseColor;
    float roughness = clamp(1.0 - gl_FrontMaterial.shininess / 128.0, 0.03, 1.0);
    vec3 bump = vec3(0.0);
    if (scan) {
        // Dreiseitig projiziert: keine Nähte auf gekrümmten Flächen, die Maserung läuft auf allen Seiten entlang x
        vec3 w = pow(abs(N), vec3(4.0));
        w /= w.x + w.y + w.z;
        vec2 ux = tile(objPos.yz), uy = tile(objPos.xz), uz = tile(objPos.xy);
        vec3 side = wood && detail == 1 ? endGrain(objPos.yz) : texture2D(baseMap, ux).rgb;
        base.rgb *= side * w.x + texture2D(baseMap, uy).rgb * w.y + texture2D(baseMap, uz).rgb * w.z;
        if (detail == 1) {
            vec3 sx = texture2D(surfaceMap, ux).rgb, sy = texture2D(surfaceMap, uy).rgb, sz = texture2D(surfaceMap, uz).rgb;
            if (wood) {
                sx = vec3(0.5, 0.5, 0.65);  // Hirnholz: ohne Relief, etwas rauer
            }
            bump = vec3(0.0, sx.xy * 2.0 - 1.0) * w.x + vec3(sy.x * 2.0 - 1.0, 0.0, sy.y * 2.0 - 1.0) * w.y
                 + vec3(sz.xy * 2.0 - 1.0, 0.0) * w.z;
            roughness = clamp(roughness * 2.0 * (sx.b * w.x + sy.b * w.y + sz.b * w.z), 0.03, 1.0);
        }
    }
    else if (coin_texunit0_model != 0 || (e.r > 0.5 && e.r < 1.5)) {
        base *= texture2D(baseMap, gl_TexCoord[0].st);
    }
    if (layers && detail == 1) {
        // 3D-Druck: Schichten 0,2 mm entlang z als feine Rillen, verschwinden, bevor sie flimmern
        float f = objPos.z / 0.2;
        bump.z += 0.35 * sin(2.0 * PI * f) * (1.0 - abs(N.z)) * clamp(1.5 - 2.0 * fwidth(f), 0.0, 1.0);
    }
    vec3 Ng = N;  // Klarlack liegt glatt über dem Relief
    N = normalize(N + bump - N * dot(N, bump));

    vec3 albedo = pow(base.rgb, vec3(2.2));
    vec3 spec = pow(gl_FrontMaterial.specular.rgb, vec3(2.2));
    // Metall: Markierung, sonst geschätzt aus dem Glanzlicht
    float metal;
    if (marked) {
        metal = e.b > 1.5 ? 1.0 : 0.0;
    }
    else {
        float s = dot(spec, LUM);
        float a = dot(albedo, LUM);
        metal = step(0.12, s) * step(a * 0.9, s);  // Glanzlicht hell und heller als die Grundfarbe: Metall (Chrom, Gold …)
    }
    // Blickrichtung. Orthografisch sähe jede ebene Fläche nur eine Richtung der Umgebung und wäre überall gleich hell
    // (oder ganz weiß, wenn das eine Lampe ist). Darum spiegelt sie wie bei einer Kamera mit rund 30° Bildwinkel, die
    // Form bleibt orthografisch.
    vec3 V;
    if (gl_ProjectionMatrix[3][3] == 1.0) {
        float height = 2.0 / gl_ProjectionMatrix[1][1];
        V = normalize((gl_ModelViewMatrixInverse * vec4(-eyePos.xy, 1.8 * height, 0.0)).xyz);
    }
    else {
        V = normalize((gl_ModelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0)).xyz - objPos);
    }
    float NoV = max(dot(N, V), 1e-4);
    vec3 Nr = N;
    if (brushed) {
        // Schliff entlang x: der Glanz zieht sich quer zu den Rillen (gebogene Normale wie in Filament)
        vec3 T = abs(N.x) > 0.95 ? vec3(0.0, 1.0, 0.0) : vec3(1.0, 0.0, 0.0);
        vec3 B = normalize(cross(N, T));
        vec3 bent = cross(cross(B, V), B);
        Nr = normalize(mix(N, bent, 0.6 * clamp(roughness * 3.0, 0.0, 1.0)));
    }
    vec3 R = reflect(-V, Nr);
    // Metall spiegelt in seiner Farbe; altes Phong-Metall hat dunkle Grundfarbe und helles Glanzlicht: das hellere zählt
    vec3 F0 = mix(vec3(0.04), max(albedo, spec * metal), metal);
    // wie three.js MeshPhysicalMaterial: Einfach- und Mehrfachstreuung (Fdez-Agüera), raues Metall wird nicht zu dunkel;
    // was der Glanz zurückwirft, fehlt dem Streulicht. Kein Zusatzlicht: die Umgebung allein beleuchtet.
    vec2 ab = envBRDF(NoV, roughness);
    vec3 FssEss = F0 * ab.x + ab.y;
    float Ems = 1.0 - (ab.x + ab.y);
    vec3 Favg = F0 + (1.0 - F0) / 21.0;
    vec3 Fms = FssEss * Favg / (1.0 - Ems * Favg);
    vec3 irradiance = envLevel(N, 5.0);
    vec3 specular = envSpecular(R, roughness) * FssEss + irradiance * Fms * Ems;
    vec3 diffuse = albedo * (1.0 - metal) * (1.0 - FssEss - Fms * Ems) * irradiance;
    float alpha = base.a;
    diffuse *= alpha;  // Glas: das Dahinter scheint durch, die Spiegelung bleibt voll (siehe alpha unten)
    if (coat) {
        float Fc = 0.04 + 0.96 * pow(1.0 - max(dot(Ng, V), 1e-4), 5.0);
        diffuse *= 1.0 - Fc;
        specular = specular * (1.0 - Fc) + envSpecular(reflect(-V, Ng), 0.04) * Fc;
    }
    vec3 color = neutral((diffuse + specular) * exposure);
    if (alpha < 1.0) {
        float a = clamp(alpha + dot(specular * exposure, LUM), alpha, 1.0);
        color = min(color / a, vec3(1.0));
        alpha = a;
    }
    gl_FragColor = vec4(pow(max(color, vec3(0.0)), vec3(1.0 / 2.2)), alpha);
}
)";

SoShaderParameter1i* detail()
{
    static auto node = new SoShaderParameter1i;
    return node;
}

SoShaderParameter1i* reflections()
{
    static auto node = new SoShaderParameter1i;
    return node;
}

/// Umgebung (Einstellung "Licht"): 0 Studio, 1 Raum (tools/make_environment.py)
SoSwitch* environment()
{
    static SoSwitch* node = [] {
        auto sw = new SoSwitch;
        sw->addChild(imageBinder(QStringLiteral(":/mycad/environment/studio.png"), EnvUnit, false));
        sw->addChild(imageBinder(QStringLiteral(":/mycad/environment/room.png"), EnvUnit, false));
        return sw;
    }();
    return node;
}

SoSwitch* root()
{
    static SoSwitch* node = [] {
        auto group = new SoGroup;
        group->addChild(environment());
        auto vertex = new SoVertexShader;
        vertex->sourceType = SoShaderObject::GLSL_PROGRAM;
        vertex->sourceProgram = Vertex;
        auto fragment = new SoFragmentShader;
        fragment->sourceType = SoShaderObject::GLSL_PROGRAM;
        fragment->sourceProgram = Fragment;
        auto baseMap = new SoShaderParameter1i;
        baseMap->name = "baseMap";
        baseMap->value = 0;
        auto envMap = new SoShaderParameter1i;
        envMap->name = "envMap";
        envMap->value = EnvUnit;
        auto exposure = new SoShaderParameter1f;
        exposure->name = "exposure";
        exposure->value = 1.0F;
        fragment->parameter.set1Value(0, baseMap);
        fragment->parameter.set1Value(1, envMap);
        fragment->parameter.set1Value(2, exposure);
        auto surfaceMap = new SoShaderParameter1i;
        surfaceMap->name = "surfaceMap";
        surfaceMap->value = SurfaceUnit;
        fragment->parameter.set1Value(3, surfaceMap);
        detail()->name = "detail";
        fragment->parameter.set1Value(4, detail());
        reflections()->name = "reflections";
        fragment->parameter.set1Value(5, reflections());
        auto program = new SoShaderProgram;
        program->shaderObject.set1Value(0, vertex);
        program->shaderObject.set1Value(1, fragment);
        group->addChild(program);
        auto sw = new SoSwitch;
        sw->ref();  // lebt bis zum Programmende, jeder Körper hängt ihn ein
        sw->addChild(group);
        return sw;
    }();
    return node;
}

struct ContactShadow;
std::vector<ContactShadow*>& shadows();
void renderMask(ContactShadow* s);
void setShadow(ContactShadow* s, bool on);

/// Einstellungen "Materialien und Licht" wirken sofort, auch wenn ein Skript sie setzt
class QualityObserver: public ParameterGrp::ObserverType
{
public:
    void OnChange(ParameterGrp::SubjectType&, ParameterGrp::MessageType reason) override
    {
        static const std::set<std::string> names {"RealisticMaterials", "Reflections", "SurfaceDetail", "ContactShadow", "Lighting"};
        if (reason && names.contains(reason)) {
            Gui::Shell::applyRenderQuality();
        }
    }
};

}  // namespace

SoNode* Gui::Shell::bodyShading()
{
    SoSwitch* sw = root();
    static bool first = true;
    if (first) {
        first = false;
        static QualityObserver observer;
        App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->Attach(&observer);
        applyRenderQuality();
    }
    return sw;
}

void Gui::Shell::applyRenderQuality()
{
    auto p = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    root()->whichChild = p->GetBool("RealisticMaterials", true) ? 0 : SO_SWITCH_NONE;  // aus: Phong wie früher
    detail()->value = p->GetBool("SurfaceDetail", true) ? 1 : 0;
    environment()->whichChild = int(std::clamp(p->GetInt("Lighting", 0), 0L, 1L));
    reflections()->value = p->GetBool("Reflections", true) ? 1 : 0;
    for (ContactShadow* shadow : shadows()) {
        setShadow(shadow, p->GetBool("ContactShadow", true));
    }
}

SoNode* Gui::Shell::bodyTexture(const std::string& path)
{
    // Der Pfad kommt aus der geöffneten Datei: nur eigene Ressourcen laden, keine beliebigen Dateien
    if (!path.starts_with(":/mycad/textures/")) {
        return nullptr;
    }
    static std::map<std::string, SoNode*> nodes;  // ein Knoten je Bild: es liegt nur einmal im Speicher und auf der GPU
    auto known = nodes.find(path);
    if (known != nodes.end()) {
        return known->second;
    }
    SoGroup* group = nullptr;
    const QString file = QString::fromStdString(path);
    QImageReader reader(file);
    const QImage image = reader.read();
    if (!image.isNull()) {
        group = new SoGroup;
        group->ref();
        // Kachelgröße aus dem JPEG-Kommentar "mm: 1000" (tools/fetch_textures.py); die Koordinaten zählen 200-mm-Kacheln
        const double mm = image.text(QStringLiteral("mm")).toDouble();
        auto scale = new SoTexture2Transform;
        scale->scaleFactor.setValue(SbVec2f(1, 1) * float(mm > 0 ? 200.0 / mm : 1.0));
        group->addChild(scale);
        auto texture = new SoTexture2;
        SoSFImage pixels;
        Gui::BitmapFactory().convert(image, pixels);
        texture->image = pixels;
        group->addChild(texture);
        QString surface = file;
        surface.replace(QStringLiteral(".jpg"), QStringLiteral("_s.jpg"));
        if (QFile::exists(surface)) {
            group->addChild(imageBinder(surface, SurfaceUnit, true));
        }
    }
    nodes[path] = group;  // auch den Fehlschlag merken: Der Körper bleibt dann einfach einfarbig
    return group;
}

namespace
{

/// Kontaktschatten einer Ansicht, wie in der Browser-Vorschau ein großer weicher Fleck unter dem Teil, aber in dessen
/// Grundriss: Eine Kamera unter dem Boden schaut nach oben und sieht, was bis zur halben Teilgröße über dem Boden liegt.
/// Das wird schwarz auf weiß in eine kleine Maske gerendert (eigener Kontext wie bei den Material-Kugeln), auf der CPU
/// weichgezeichnet und vom Boden halbdurchsichtig gezeichnet. Nur Körper werfen Schatten (Skizzen, Profile, Scribbles,
/// Hilfsgeometrie sind dabei ausgeblendet). Neu gerendert wird nur, wenn sich die Szene ändert.
struct ContactShadow
{
    SoSwitch* sw;
    SoGroup* objects;
    SoSeparator* under;  ///< Kamera, Grundfarbe schwarz erzwingen, Körper
    SoOrthographicCamera* camera;
    SoTexture2* mask;
    SoShaderParameter4f* area;  ///< Mitte x, y; halbe Breite; Stärke
    SoCoordinate3* quad;
    SoNodeSensor* sensor;
    QTimer* timer;
    std::function<std::vector<SoSwitch*>()> others;  ///< Anzeige-Schalter von allem, was kein Körper ist
    SbBox3f drawn;  ///< Umriss der ganzen Szene beim letzten Rendern der Maske
};

constexpr int MaskSize = 128;

std::vector<ContactShadow*>& shadows()
{
    static std::vector<ContactShadow*> list;  // ponytail: je Ansicht ein Eintrag, der bis zum Programmende bleibt
    return list;
}

/// dreimal Kastenfilter waagrecht und senkrecht ≈ Gauß mit Sigma ≈ r; außerhalb der Maske ist nichts
void soften(std::vector<float>& m, int n, int r)
{
    std::vector<float> tmp(m.size());
    for (int pass = 0; pass < 6; ++pass) {
        const bool rows = pass % 2 == 0;
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                float sum = 0;
                for (int k = std::max(0, b - r); k <= std::min(n - 1, b + r); ++k) {
                    sum += rows ? m[a * n + k] : m[k * n + a];
                }
                (rows ? tmp[a * n + b] : tmp[b * n + a]) = sum / float(2 * r + 1);
            }
        }
        m.swap(tmp);
    }
}

void renderMask(ContactShadow* s)
{
    if (s->sw->whichChild.getValue() == SO_SWITCH_NONE) {
        return;
    }
    s->sensor->detach();  // das eigene Rendern (und Ausblenden) soll nicht gleich das nächste auslösen
    SoGetBoundingBoxAction all(SbViewportRegion(MaskSize, MaskSize));
    all.apply(s->objects);
    s->drawn = all.getBoundingBox();
    std::vector<std::pair<SoSwitch*, int>> hidden;
    for (SoSwitch* other : s->others()) {
        hidden.emplace_back(other, other->whichChild.getValue());
        other->whichChild = SO_SWITCH_NONE;
    }
    SoGetBoundingBoxAction bbox(SbViewportRegion(MaskSize, MaskSize));
    bbox.apply(s->objects);
    const SbBox3f box = bbox.getBoundingBox();
    QImage image;
    float cx = 0, cy = 0, half = 0, ground = 0;
    if (!box.isEmpty()) {
        float x0, y0, z0, x1, y1, z1;
        box.getBounds(x0, y0, z0, x1, y1, z1);
        const float size = std::max(x1 - x0, y1 - y0);
        half = size * 0.8F + 5.0F;          // Platz für den weichen Rand
        ground = std::min(z0, 0.0F);        // auf dem Raster, oder darunter, wenn der Körper tiefer reicht
        cx = (x0 + x1) / 2, cy = (y0 + y1) / 2;
        s->camera->position.setValue(cx, cy, ground - 1);
        s->camera->height = 2 * half;
        s->camera->nearDistance = 0.5F;
        s->camera->farDistance = 1 + std::max(size * 0.5F, 2.0F);  // was bis zur halben Größe über dem Boden liegt
        Gui::SoQtOffscreenRenderer renderer(SbViewportRegion(MaskSize, MaskSize));
        renderer.setBackgroundColor(SbColor4f(1, 1, 1, 1));
        if (renderer.render(s->under)) {
            renderer.writeToImage(image);
        }
    }
    for (const auto& [other, value] : hidden) {
        other->whichChild = value;
    }
    s->sensor->attach(s->objects);
    if (image.isNull()) {
        s->quad->point.setNum(0);
        return;
    }
    image = image.convertToFormat(QImage::Format_Grayscale8);
    std::vector<float> cover(MaskSize * MaskSize);
    for (int y = 0; y < MaskSize; ++y) {
        const uchar* row = image.constScanLine(y);
        for (int x = 0; x < MaskSize; ++x) {
            cover[y * MaskSize + x] = 1.0F - row[x] / 255.0F;  // 1 unter einem Körper
        }
    }
    soften(cover, MaskSize, 5);  // Sigma rund 1/10 der Teilgröße
    for (int y = 0; y < MaskSize; ++y) {
        uchar* row = image.scanLine(y);
        for (int x = 0; x < MaskSize; ++x) {
            row[x] = uchar(std::clamp(cover[y * MaskSize + x], 0.0F, 1.0F) * 255.0F + 0.5F);
        }
    }
    SoSFImage pixels;
    Gui::BitmapFactory().convert(image, pixels);
    s->mask->image = pixels;
    s->area->value.setValue(cx, cy, half, 0.55F);  // wie die Vorschau: mitten unter dem Teil 55 % Schwarz
    const SbVec3f corners[] = {{cx - half, cy - half, ground}, {cx + half, cy - half, ground},
                               {cx + half, cy + half, ground}, {cx - half, cy + half, ground}};
    s->quad->point.setValues(0, 4, corners);
}

void setShadow(ContactShadow* s, bool on)
{
    s->sw->whichChild = on ? 0 : SO_SWITCH_NONE;
    if (on) {
        s->timer->start();
    }
}

const char* const ShadowVertex = R"(
#version 120
varying vec2 world;
varying float up;  // > 0: Blick von oben auf den Boden
void main()
{
    world = gl_Vertex.xy;
    up = -(gl_ModelViewMatrixInverse * vec4(0.0, 0.0, -1.0, 0.0)).z;
    gl_Position = ftransform();
}
)";

const char* const ShadowFragment = R"(
#version 120
uniform sampler2D mask;  // Deckung, weichgezeichnet: Körper nah am Boden, von unten gesehen (x gespiegelt)
uniform vec4 area;       // Mitte x, y; halbe Breite; Stärke
varying vec2 world;
varying float up;
void main()
{
    vec2 uv = vec2(0.5 - (world.x - area.x) / (2.0 * area.z), 0.5 + (world.y - area.y) / (2.0 * area.z));
    float shadow = texture2D(mask, uv).r * area.w * smoothstep(0.05, 0.3, up);  // schon weich (soften)
    if (shadow < 0.004) {
        discard;
    }
    gl_FragColor = vec4(0.0, 0.0, 0.0, shadow);
}
)";

void depthClamp(void* on, SoAction* action)
{
    if (action->isOfType(SoGLRenderAction::getClassTypeId())) {
        on ? glEnable(GL_DEPTH_CLAMP) : glDisable(GL_DEPTH_CLAMP);
    }
}

}  // namespace

SoNode* Gui::Shell::contactShadow(SoNode* objects, std::function<std::vector<SoSwitch*>()> others)
{
    auto s = new ContactShadow {};
    s->others = std::move(others);
    s->objects = new SoGroup;
    s->objects->ref();
    s->objects->addChild(objects);
    s->camera = new SoOrthographicCamera;
    s->camera->orientation = SbRotation(SbVec3f(0, 1, 0), float(M_PI));  // nach oben schauen, y bleibt oben
    // alles in Grundfarbe schwarz (der Körper-Shader gibt dann die Grundfarbe aus), auch Texturen und Linien
    auto flat = new SoLightModel;
    flat->model = SoLightModel::BASE_COLOR;
    flat->setOverride(TRUE);
    auto black = new SoMaterial;
    black->diffuseColor.setValue(0, 0, 0);
    black->transparency = 0;
    black->setOverride(TRUE);
    s->under = new SoSeparator;
    s->under->ref();
    for (SoNode* n : std::initializer_list<SoNode*> {s->camera, flat, black, s->objects}) {
        s->under->addChild(n);
    }
    s->mask = new SoTexture2;
    s->mask->wrapS = SoTexture2::CLAMP;
    s->mask->wrapT = SoTexture2::CLAMP;
    s->area = new SoShaderParameter4f;
    s->area->name = "area";
    s->quad = new SoCoordinate3;
    s->quad->point.setNum(0);

    auto vertex = new SoVertexShader;
    vertex->sourceType = SoShaderObject::GLSL_PROGRAM;
    vertex->sourceProgram = ShadowVertex;
    auto fragment = new SoFragmentShader;
    fragment->sourceType = SoShaderObject::GLSL_PROGRAM;
    fragment->sourceProgram = ShadowFragment;
    auto maskUnit = new SoShaderParameter1i;
    maskUnit->name = "mask";
    maskUnit->value = 0;
    fragment->parameter.set1Value(0, maskUnit);
    fragment->parameter.set1Value(1, s->area);
    auto program = new SoShaderProgram;
    program->shaderObject.set1Value(0, vertex);
    program->shaderObject.set1Value(1, fragment);

    auto pick = new SoPickStyle;
    pick->style = SoPickStyle::UNPICKABLE;
    auto blend = new SoTransparencyType;  // in Reihenfolge nach den Körpern zeichnen, wie das Raster
    blend->value = SoTransparencyType::BLEND;
    auto material = new SoMaterial;
    material->transparency = 0.5F;  // schaltet Blending ein; die Deckkraft kommt aus dem Shader
    auto depth = new SoDepthBuffer;
    depth->write = FALSE;
    depth->function = SoDepthBuffer::LEQUAL;
    auto clampOn = new SoCallback;
    clampOn->setCallback(depthClamp, clampOn);
    auto clampOff = new SoCallback;
    clampOff->setCallback(depthClamp, nullptr);
    auto sep = new SoSeparator;
    sep->renderCulling = SoSeparator::OFF;
    for (SoNode* n : std::initializer_list<SoNode*> {pick, blend, material, depth, new SoPolygonOffset, s->mask, program,
                                                     s->quad, clampOn, new SoFaceSet, clampOff}) {
        sep->addChild(n);
    }
    auto skip = new SoSkipBoundingGroup;  // Einpassen und Clipping richten sich nur nach den Körpern
    skip->mode = SoSkipBoundingGroup::EXCLUDE_BBOX;
    skip->addChild(sep);
    s->sw = new SoSwitch;
    s->sw->ref();
    s->sw->addChild(skip);
    s->sw->whichChild = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("ContactShadow", true)
        ? 0 : SO_SWITCH_NONE;

    // Szene geändert (Körper bearbeitet, ein- oder ausgeblendet): Maske kurz danach neu, beim Tippen nicht bei jeder Taste
    s->timer = new QTimer;
    s->timer->setSingleShot(true);
    s->timer->setInterval(400);
    QObject::connect(s->timer, &QTimer::timeout, [s] { renderMask(s); });
    s->sensor = new SoNodeSensor([](void* data, SoSensor*) {
        auto s = static_cast<ContactShadow*>(data);
        // Form geändert (anderer Umriss): der alte Schatten zeigte bis zum neuen Rendern den Grundriss der vorigen Form,
        // etwa ein großes Rechteck unter einem neuen Zylinder; dann lieber kurz keiner. Auswahl und Vorauswahl ändern
        // den Umriss nicht, der Schatten bleibt dabei stehen
        SoGetBoundingBoxAction all(SbViewportRegion(MaskSize, MaskSize));
        all.apply(s->objects);
        if (all.getBoundingBox() != s->drawn) {
            s->quad->point.setNum(0);
        }
        s->timer->start();
    }, s);
    s->sensor->attach(s->objects);
    s->timer->start();
    shadows().push_back(s);
    return s->sw;
}
