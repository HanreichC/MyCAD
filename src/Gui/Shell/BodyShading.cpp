// SPDX-License-Identifier: LGPL-2.1-or-later

#include "BodyShading.h"

#include <App/Application.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoVertexShader.h>

#include <QImage>
#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <cstring>
#include <map>

namespace
{

constexpr int EnvUnit = 2;  ///< Texturstufe der Umgebung; 0 bleibt für Holz, Stein … (TextureExtension)

/// Umgebung "Raum" (tools/make_environment.py) als GL-Textur je Kontext an Stufe 2 binden. Direkt in GL statt über einen
/// SoTexture2-Knoten: Coin erzeugte sonst für Stufe 2 Texturkoordinaten und ließe den schnellen Zeichenweg der Flächen aus.
void bindEnvironment(void*, SoAction* action)
{
    if (!action->isOfType(SoGLRenderAction::getClassTypeId())) {
        return;
    }
    QOpenGLContext* ctx = QOpenGLContext::currentContext();
    if (!ctx) {
        return;
    }
    static std::map<QOpenGLContext*, GLuint> textures;
    QOpenGLFunctions* f = ctx->functions();
    auto known = textures.find(ctx);
    if (known == textures.end()) {
        const QImage img = QImage(QStringLiteral(":/mycad/environment/room.png")).convertToFormat(QImage::Format_RGBA8888);
        GLuint tex = 0;
        f->glGenTextures(1, &tex);
        f->glActiveTexture(GL_TEXTURE0 + EnvUnit);
        f->glBindTexture(GL_TEXTURE_2D, tex);
        f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.constBits());
        // ohne Mipmaps: an der Naht der Kugelkarte (u = 0/1) wählte die GPU sonst eine winzige Stufe, eine Linie wäre zu sehen
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        known = textures.emplace(ctx, tex).first;
        QObject::connect(ctx, &QOpenGLContext::aboutToBeDestroyed, [ctx] { textures.erase(ctx); });
    }
    f->glActiveTexture(GL_TEXTURE0 + EnvUnit);
    f->glBindTexture(GL_TEXTURE_2D, known->second);
    f->glActiveTexture(GL_TEXTURE0);
}

const char* const Vertex = R"(
#version 120
varying vec3 objNormal;  // Objekt-Koordinaten: darin steht die Umgebung (Z oben)
varying vec3 objPos;
varying vec3 eyeNormal;
varying vec4 baseColor;
void main()
{
    objNormal = gl_Normal;
    objPos = gl_Vertex.xyz;
    eyeNormal = gl_NormalMatrix * gl_Normal;
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
uniform sampler2D baseMap;        // Stufe 0: Holz, Stein … aus dem Material
uniform sampler2D envMap;         // Stufe 2: Umgebung "Raum", 6 Ebenen 512x256 RGBM untereinander
uniform float exposure;
varying vec3 objNormal;
varying vec3 objPos;
varying vec3 eyeNormal;
varying vec4 baseColor;

const float PI = 3.14159265;
const float LEVELS = 6.0;

vec3 envLevel(vec3 d, float level)
{
    float u = atan(d.y, d.x) / (2.0 * PI) + 0.5;
    float v = clamp(acos(clamp(d.z, -1.0, 1.0)) / PI, 0.5 / 256.0, 1.0 - 0.5 / 256.0);
    vec4 c = texture2D(envMap, vec2(u, (level + v) / LEVELS));
    return c.rgb * c.a * 64.0;
}

/// Spiegelung aus der Umgebung, Ebene 0 (scharf) bis 4 (rau), dazwischen gemischt
vec3 envSpecular(vec3 d, float roughness)
{
    float level = clamp(roughness, 0.0, 1.0) * 4.0;
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

void main()
{
    if (coin_light_model == 0) {  // Auswahl und Vorauswahl: Farbe wie gehabt
        gl_FragColor = baseColor;
        return;
    }
    // Markierungen in der Leuchtfarbe (unsichtbar, siehe BodyShading.h): Rot 1/255 = Textur auf Stufe 0 (setzt die
    // TextureExtension), Blau 1/255 = kein Metall, 2/255 = Metall
    vec3 e = gl_FrontMaterial.emission.rgb * 255.0;
    vec4 base = baseColor;
    if (coin_texunit0_model != 0 || (e.r > 0.5 && e.r < 1.5)) {
        base *= texture2D(baseMap, gl_TexCoord[0].st);
    }
    vec3 albedo = pow(base.rgb, vec3(2.2));
    vec3 spec = pow(gl_FrontMaterial.specular.rgb, vec3(2.2));
    float roughness = clamp(1.0 - gl_FrontMaterial.shininess / 128.0, 0.03, 1.0);
    // Metall: Markierung, sonst geschätzt aus dem Glanzlicht
    float metal;
    if (e.g < 0.5 && e.b > 0.5 && e.b < 2.5) {
        metal = e.b > 1.5 ? 1.0 : 0.0;
    }
    else {
        float s = dot(spec, vec3(0.2126, 0.7152, 0.0722));
        float a = dot(albedo, vec3(0.2126, 0.7152, 0.0722));
        metal = step(0.12, s) * step(a * 0.9, s);  // Glanzlicht hell und heller als die Grundfarbe: Metall (Chrom, Gold …)
    }
    vec3 N = normalize(objNormal);
    vec3 Ne = normalize(eyeNormal);
    if (!gl_FrontFacing) {
        N = -N;
        Ne = -Ne;
    }
    vec3 V = gl_ProjectionMatrix[3][3] == 1.0 ? normalize((gl_ModelViewMatrixInverse * vec4(0.0, 0.0, 1.0, 0.0)).xyz)
                                              : normalize((gl_ModelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0)).xyz - objPos);
    float NoV = max(dot(N, V), 1e-4);
    vec3 R = reflect(-V, N);
    // Metall spiegelt in seiner Farbe; altes Phong-Metall hat dunkle Grundfarbe und helles Glanzlicht: das hellere zählt
    vec3 F0 = mix(vec3(0.04), max(albedo, spec * metal), metal);
    vec2 ab = envBRDF(NoV, roughness);
    vec3 specular = envSpecular(R, roughness) * (F0 * ab.x + ab.y);
    vec3 diffuse = albedo * (1.0 - metal) * envLevel(N, 5.0);
    // Kopflicht als leichte Aufhellung: auch die von der Umgebung abgewandte Seite bleibt lesbar
    float head = max(dot(Ne, normalize(gl_LightSource[0].position.xyz)), 0.0);
    diffuse += albedo * (1.0 - metal) * head * 0.18;
    specular += F0 * head * 0.08;
    vec3 color = neutral((diffuse + specular) * exposure);
    gl_FragColor = vec4(pow(max(color, vec3(0.0)), vec3(1.0 / 2.2)), base.a);
}
)";

SoSwitch* root()
{
    static SoSwitch* node = [] {
        auto group = new SoGroup;
        auto bind = new SoCallback;
        bind->setCallback(bindEnvironment);
        group->addChild(bind);
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

/// Einstellung "Materialien" (MyCAD/RenderQuality) wirkt sofort, auch wenn ein Skript sie setzt
class QualityObserver: public ParameterGrp::ObserverType
{
public:
    void OnChange(ParameterGrp::SubjectType&, ParameterGrp::MessageType reason) override
    {
        if (reason && std::strcmp(reason, "RenderQuality") == 0) {
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
    const long quality = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetInt("RenderQuality", 0);
    root()->whichChild = quality >= 2 ? SO_SWITCH_NONE : 0;  // Sparsam: Phong wie früher
}
