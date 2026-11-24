// SPDX-License-Identifier: LGPL-2.1-or-later

#include "BodyShading.h"
#include <Inventor/SbColor.h>

#include <App/Application.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoVertexShader.h>

#include <Gui/BitmapFactory.h>

#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

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

/// Bild als GL-Textur an eine Stufe binden. Direkt in GL statt über einen SoTexture2-Knoten: Coin erzeugte sonst für
/// die Stufe Texturkoordinaten und ließe den schnellen Zeichenweg der Flächen aus.
/// Eine Textur je GL-Gruppe (Kontexte, die sich Texturen teilen; die Ansichten von Qt alle): vorher je Kontext, und
/// beim Schließen einer Ansicht wurde nur der Eintrag vergessen; die Textur blieb in der gemeinsamen Gruppe liegen
/// (U8: ~6 MB je geschlossenem Design, gemessen mit heaptrack). Ein Eintrag fällt erst weg, wenn der letzte Kontext
/// seiner Gruppe endet; dann gibt der Treiber die Textur mit dem Kontext frei.
struct GlImage
{
    QString path;
    int unit;
    bool tiled;  ///< kachelt und hat Mipmaps (Fotoscan); sonst Kugelkarte
    std::map<QOpenGLContextGroup*, GLuint> textures;
    std::set<QOpenGLContext*> watched;  ///< Kontexte, deren Ende geprüft wird
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
    QOpenGLContextGroup* group = ctx->shareGroup();
    if (image->watched.insert(ctx).second) {
        QObject::connect(ctx, &QOpenGLContext::aboutToBeDestroyed, [image, ctx, group] {
            image->watched.erase(ctx);
            if (group->shares().size() <= 1) {
                image->textures.erase(group);  // letzter Kontext der Gruppe: die Textur geht mit ihm
            }
        });
    }
    auto known = image->textures.find(group);
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
        known = image->textures.emplace(group, tex).first;
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

/// Nach dem Programm: Uniform eyeToWorld aus der Kamera dieser Ansicht. Ohne sie läge die Umgebung im Körper und drehte
/// sich mit ihm: ein vom Gelenk gekippter Arm hatte oben den braunen Boden und an der Stirn das weiße Licht.
void setEyeToWorld(void*, SoAction* action)
{
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    if (!ctx || !action->isOfType(SoGLRenderAction::getClassTypeId())) {
        return;
    }
    QOpenGLFunctions* f = ctx->functions();
    GLint program = 0;
    f->glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    const GLint at = program ? f->glGetUniformLocation(GLuint(program), "eyeToWorld") : -1;
    if (at >= 0) {
        const SbMatrix m = SoViewingMatrixElement::get(action->getState()).inverse();
        f->glUniformMatrix4fv(at, 1, GL_FALSE, m[0]);
    }
}

const char* const Vertex = R"(
#version 120
varying vec3 objNormal;  // Objekt-Koordinaten: darin liegen Fotoscan, Schliff und Schichten; die Umgebung steht in Welt
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

/// Phong-Modus (RealisticMaterials aus) bei offener Skizze: nur Grundfarbe mal Licht, zur Hintergrundfarbe gemischt wie
/// im physikalischen Shader. Ohne Skizze bleibt der Phong-Modus ganz ohne Shader wie früher.
const char* const PlainVertex = R"(
varying vec3 normal;
varying vec3 position;
varying vec4 color;
void main()
{
    position = vec3(gl_ModelViewMatrix * gl_Vertex);
    normal = normalize(gl_NormalMatrix * gl_Normal);
    color = gl_Color;
    gl_Position = ftransform();
}
)";

const char* const PlainFragment = R"(
varying vec3 normal;
varying vec3 position;
varying vec4 color;
uniform float fade;
uniform vec3 background;
void main()
{
    vec3 n = normalize(gl_FrontFacing ? normal : -normal);
    vec3 l = normalize(gl_LightSource[0].position.xyz - position * gl_LightSource[0].position.w);
    vec3 lit = color.rgb * (0.35 + 0.65 * max(dot(n, l), 0.0));
    gl_FragColor = vec4(mix(lit, background, fade), color.a);
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
uniform mat4 eyeToWorld;          // Kamera-Drehung zurück in die Welt (setEyeToWorld)
uniform float fade;               // Skizze offen: Körper treten zur Hintergrundfarbe hin zurück (fadeBodies)
uniform vec3 background;
varying vec3 objNormal;
varying vec3 objPos;
varying vec3 eyePos;
varying vec4 baseColor;

const float PI = 3.14159265;
const float LEVELS = 6.0;
const float TILE = 200.0;  // mm je Kachel vor der Texturmatrix, wie faceTextureCoordinates in ViewProviderExt.cpp
const vec3 LUM = vec3(0.2126, 0.7152, 0.0722);

/// d in Objekt-Koordinaten; die Umgebung steht in der Welt (Z oben), auch unter gedrehten Komponenten und Körpern
vec3 envLevel(vec3 d, float level)
{
    d = normalize(mat3(eyeToWorld) * (gl_NormalMatrix * d));
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
    gl_FragColor = vec4(mix(pow(max(color, vec3(0.0)), vec3(1.0 / 2.2)), background, fade), alpha);
}
)";

SoShaderParameter1f* fade()
{
    static auto node = new SoShaderParameter1f;
    return node;
}

SoShaderParameter3f* background()
{
    static auto node = new SoShaderParameter3f;
    return node;
}

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
        fade()->name = "fade";
        fade()->value = 0.0F;
        fragment->parameter.set1Value(6, fade());
        background()->name = "background";
        fragment->parameter.set1Value(7, background());
        auto program = new SoShaderProgram;
        program->shaderObject.set1Value(0, vertex);
        program->shaderObject.set1Value(1, fragment);
        group->addChild(program);
        auto eye = new SoCallback;
        eye->setCallback(setEyeToWorld);
        group->addChild(eye);
        auto sw = new SoSwitch;
        sw->ref();  // lebt bis zum Programmende, jeder Körper hängt ihn ein
        sw->addChild(group);
        // Kind 1: Phong-Modus bei offener Skizze (fadeBodies), teilt fade und background mit dem physikalischen Shader
        auto plainVertex = new SoVertexShader;
        plainVertex->sourceType = SoShaderObject::GLSL_PROGRAM;
        plainVertex->sourceProgram = PlainVertex;
        auto plainFragment = new SoFragmentShader;
        plainFragment->sourceType = SoShaderObject::GLSL_PROGRAM;
        plainFragment->sourceProgram = PlainFragment;
        plainFragment->parameter.set1Value(0, fade());
        plainFragment->parameter.set1Value(1, background());
        auto plain = new SoShaderProgram;
        plain->shaderObject.set1Value(0, plainVertex);
        plain->shaderObject.set1Value(1, plainFragment);
        sw->addChild(plain);
        return sw;
    }();
    return node;
}

/// Einstellungen "Materialien und Licht" wirken sofort, auch wenn ein Skript sie setzt
class QualityObserver: public ParameterGrp::ObserverType
{
public:
    void OnChange(ParameterGrp::SubjectType&, ParameterGrp::MessageType reason) override
    {
        static const std::set<std::string> names {"RealisticMaterials", "Reflections", "SurfaceDetail", "Lighting"};
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
    // aus: Phong wie früher, nur bei offener Skizze ein schlichter Shader, damit die Körper zurücktreten
    root()->whichChild = p->GetBool("RealisticMaterials", true) ? 0 : fade()->value.getValue() > 0 ? 1 : SO_SWITCH_NONE;
    detail()->value = p->GetBool("SurfaceDetail", true) ? 1 : 0;
    environment()->whichChild = int(std::clamp(p->GetInt("Lighting", 0), 0L, 1L));
    reflections()->value = p->GetBool("Reflections", true) ? 1 : 0;
}

void Gui::Shell::fadeBodies(bool on)
{
    // Mitte des Hintergrundverlaufs: dahinter verschwindet ein zurückgetretener Körper nicht, wirkt aber blass
    auto view = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/View");
    float transparency;
    const SbColor top = SbColor().setPackedValue(view->GetUnsigned("BackgroundColor2", 0xF2F2F7FF), transparency);
    const SbColor bottom = SbColor().setPackedValue(view->GetUnsigned("BackgroundColor3", 0xE5E5EAFF), transparency);
    background()->value = (top + bottom) / 2.0F;
    fade()->value = on ? 0.5F : 0.0F;
    applyRenderQuality();  // Phong-Modus: schlichten Shader nur bei offener Skizze
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
