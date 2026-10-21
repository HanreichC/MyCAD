// SPDX-License-Identifier: LGPL-2.1-or-later

#include "GlassPanel.h"
#include "Theme.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGuiApplication>
#include <QHash>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QPainter>
#include <QVector3D>

#include <algorithm>

#include <memory>

using namespace Gui::Shell;

namespace
{

// glass.thickness.regular (Bars, Browser, Inspector, Palette) und elevation.glass
constexpr float LensZone = 30, LensStrength = 32, EdgeBlur = 8, Chroma = 0.08F, Saturation = 1.5F;
constexpr qreal ShadowBlur = 28, ShadowY = 6;
constexpr qreal ShadowMargin = ShadowBlur + ShadowY;  // logische Pixel um das Panel herum für den Schatten

const char* QuadVs = R"(
#version 120
attribute vec2 aPos;
uniform vec4 uRect;   // NDC: x0, y0, x1, y1
varying vec2 vUv;
void main() {
    vec2 t = aPos * 0.5 + 0.5;
    vUv = t;
    gl_Position = vec4(mix(uRect.xy, uRect.zw, t), 0.0, 1.0);
}
)";

// 9-Tap-Gauß mit linearer Filterung (5 Lesezugriffe)
const char* BlurFs = R"(
#version 120
uniform sampler2D uTex;
uniform vec2 uDir;
varying vec2 vUv;
void main() {
    vec4 c = texture2D(uTex, vUv) * 0.2270270270;
    c += texture2D(uTex, vUv + uDir * 1.3846153846) * 0.3162162162;
    c += texture2D(uTex, vUv - uDir * 1.3846153846) * 0.3162162162;
    c += texture2D(uTex, vUv + uDir * 3.2307692308) * 0.0702702703;
    c += texture2D(uTex, vUv - uDir * 3.2307692308) * 0.0702702703;
    gl_FragColor = c;
}
)";

// MyStyle glass.frag: zum Rand hin nach innen gezogener Hintergrund mit leichter Farbaufspaltung, Vibrancy,
// Tönung nach Glas-Stufe, Lichtkante oben links/unten rechts, abgedunkeltes äußerstes Pixel (iOS 27), Glanz von oben
const char* GlassFs = R"(
#version 120
uniform sampler2D uTex;
uniform float uFbH;
uniform vec2 uCenter, uHalf, uCapOrigin, uCapSize;
uniform float uRadius, uShadow, uShadowY, uShadowAlpha, uDpr;
uniform float uTint, uRim, uEdge, uSheen, uLensZone, uLensStrength, uEdgeBlur, uChroma, uSaturation;
uniform vec3 uTintColor;

float sdRound(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b + vec2(r);
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}
vec3 blurred(vec2 p) {
    vec2 uv = (p - uCapOrigin) / uCapSize;
    uv.y = 1.0 - uv.y;
    return texture2D(uTex, clamp(uv, 0.0, 1.0)).rgb;
}
// Hintergrund durch das Glas bei p, um off verschoben; Rot und Blau leicht versetzt (Dispersion)
vec3 refracted(vec2 p, vec2 off) {
    return vec3(blurred(p - off * (1.0 + uChroma)).r, blurred(p - off).g, blurred(p - off * (1.0 - uChroma)).b);
}
void main() {
    vec2 p = vec2(gl_FragCoord.x, uFbH - gl_FragCoord.y);   // oben-links-Koordinaten wie Qt
    vec2 rel = p - uCenter;
    float d = sdRound(rel, uHalf, uRadius);
    float e = uDpr;
    vec2 n = normalize(vec2(sdRound(rel + vec2(e, 0.0), uHalf, uRadius) - sdRound(rel - vec2(e, 0.0), uHalf, uRadius),
                            sdRound(rel + vec2(0.0, e), uHalf, uRadius) - sdRound(rel - vec2(0.0, e), uHalf, uRadius)) + 1e-6);
    float inside = clamp(0.5 - d, 0.0, 1.0);

    // weicher Schatten, leicht nach unten versetzt
    float ds = sdRound(rel - vec2(0.0, uShadowY), uHalf, uRadius);
    float shadow = pow(1.0 - smoothstep(-uShadow * 0.3, uShadow, ds), 2.0) * uShadowAlpha;

    // Linse wie eine runde Glaskante (Viertelkreis): die Steigung und damit die Brechung bleibt in der Linsenzone sanft
    // und wird ganz außen steil; dort streut das gewölbte Glas auch, der Hintergrund verschwimmt mehr
    // (Werte in logischen Pixeln)
    float t = -d / uDpr;
    float u = clamp(1.0 - t / uLensZone, 0.0, 1.0);
    float k = 0.97 * u;
    vec2 off = n * (k / sqrt(1.0 - k * k) / 3.99) * uLensStrength * uDpr;
    vec3 col = refracted(p, off);
    float scatter = u * u * uEdgeBlur * uDpr;
    if (scatter > 0.5) {
        for (int i = 0; i < 8; ++i) {
            float a = float(i) * 0.7853982;
            col += refracted(p + scatter * vec2(cos(a), sin(a)), off);
        }
        col /= 9.0;
    }

    // Vibrancy, dann die Tönung
    float l = dot(col, vec3(0.299, 0.587, 0.114));
    col = mix(vec3(l), col, uSaturation);
    col = mix(col, uTintColor, uTint);

    // äußerstes Pixel abgedunkelt, die Lichtkante direkt innen
    float outer = 1.0 - smoothstep(0.0, 1.0, t);
    float band = (1.0 - outer) * (1.0 - smoothstep(1.0, 2.6, t));
    col += band * uRim * (0.3 + 0.7 * abs(dot(n, normalize(vec2(-0.45, -1.0)))));
    col *= 1.0 - outer * uEdge;

    // feiner Glanz von oben
    col += (1.0 - smoothstep(0.0, 2.0 * uHalf.y, rel.y + uHalf.y)) * uSheen;
    gl_FragColor = vec4(min(col, 1.0), 1.0) * inside + vec4(0.0, 0.0, 0.0, shadow) * (1.0 - inside);
}
)";

class GlassRenderer: protected QOpenGLExtraFunctions
{
public:
    GlassRenderer()
    {
        initializeOpenGLFunctions();
        ok = build(blur, BlurFs) && build(glass, GlassFs);
        const float quad[] = {-1, -1, 1, -1, -1, 1, 1, 1};
        vbo.create();
        vbo.bind();
        vbo.allocate(quad, sizeof(quad));
        vbo.release();
    }

    static GlassRenderer* forContext(QOpenGLContext* ctx)
    {
        static QHash<QOpenGLContext*, GlassRenderer*> renderers;
        auto it = renderers.find(ctx);
        if (it != renderers.end()) {
            return *it;
        }
        auto r = new GlassRenderer;
        renderers.insert(ctx, r);
        QObject::connect(ctx, &QOpenGLContext::aboutToBeDestroyed, [ctx] {
            delete renderers.take(ctx);
        });
        return r;
    }

    /// panel/fb in Gerätepixeln, Ursprung oben links. Gibt false zurück, wenn GL den Blur nicht kann.
    bool draw(const QRect& panel, const QSize& fb, float radius, float dpr, bool textSurface)
    {
        const Theme& th = theme();
        const bool inactive = qApp->applicationState() != Qt::ApplicationActive;  // GM-4: Glas tritt zurück
        const float shadow = float(ShadowBlur * dpr);
        // Blur je Glas-Stufe ist MultiEffect.blurMax wie in MyStyles Glass.qml: ein leichter Weichzeichner, Text darunter
        // bleibt fast lesbar (an MyPods abgeglichen: Sigma etwa Radius / 8). Gerechnet wird verkleinert, je stärker der
        // Blur, desto kleiner; bei wenig Blur in voller Auflösung, damit dünne Linien (Raster) scharf durchscheinen
        const float sigma = float(th.glassBlur() / 8.0 * dpr);
        const int down = sigma >= 6 ? 4 : sigma >= 3 ? 2 : 1;
        const float spread = sigma / float(down) / 2.32f;  // zwei H+V-Durchgänge des 9-Tap-Gauß: 2.32 * spread Texel Sigma
        if (!ok) {
            return false;
        }
        GLint prevFbo = 0;
        GLint vp[4];
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);
        glGetIntegerv(GL_VIEWPORT, vp);
        const GLboolean scissor = glIsEnabled(GL_SCISSOR_TEST);
        const GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
        const GLboolean stencil = glIsEnabled(GL_STENCIL_TEST);
        const GLboolean blend = glIsEnabled(GL_BLEND);
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        while (glGetError() != GL_NO_ERROR) {}

        const int margin = int(40 * dpr);
        const QRect cap = panel.adjusted(-margin, -margin, margin, margin) & QRect(QPoint(0, 0), fb);
        bool drawn = false;
        if (!cap.isEmpty()) {
            const QSize half(std::max(1, cap.width() / 2), std::max(1, cap.height() / 2));
            const QSize small = down == 1 ? cap.size()
                : down == 2               ? half
                                          : QSize(std::max(1, half.width() / 2), std::max(1, half.height() / 2));
            ensure(resolve, cap.size());
            ensure(pingA, small);
            ensure(pingB, small);

            // 1:1 auflösen (Quelle kann multisampled sein), dann in Halbierungen verkleinern: jede mittelt genau
            // 2 x 2 Pixel (ein Sprung auf 1/4 läse nur 4 von 16 Pixeln, dünne Linien wie das Raster fielen heraus)
            const int gy0 = fb.height() - (cap.y() + cap.height());
            glBindFramebuffer(GL_READ_FRAMEBUFFER, prevFbo);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolve->handle());
            glBlitFramebuffer(cap.x(), gy0, cap.x() + cap.width(), gy0 + cap.height(),
                              0, 0, cap.width(), cap.height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
            GLuint from = resolve->handle();
            if (down == 4) {
                ensure(halved, half);
                glBindFramebuffer(GL_READ_FRAMEBUFFER, from);
                glBindFramebuffer(GL_DRAW_FRAMEBUFFER, halved->handle());
                glBlitFramebuffer(0, 0, half.width() * 2, half.height() * 2,
                                  0, 0, half.width(), half.height(), GL_COLOR_BUFFER_BIT, GL_LINEAR);
                from = halved->handle();
            }
            const int step = down == 1 ? 1 : 2;
            glBindFramebuffer(GL_READ_FRAMEBUFFER, from);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pingA->handle());
            glBlitFramebuffer(0, 0, small.width() * step, small.height() * step,
                              0, 0, small.width(), small.height(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

            if (glGetError() == GL_NO_ERROR) {
                vbo.bind();
                glActiveTexture(GL_TEXTURE0);
                glViewport(0, 0, small.width(), small.height());
                blur.bind();
                setupQuad(blur, -1, -1, 1, 1);
                blur.setUniformValue("uTex", 0);
                for (int i = 0; i < 2; ++i) {
                    pass(pingB.get(), pingA->texture(), QVector2D(spread / small.width(), 0));
                    pass(pingA.get(), pingB->texture(), QVector2D(0, spread / small.height()));
                }

                glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
                glViewport(vp[0], vp[1], vp[2], vp[3]);
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                glass.bind();
                const float m = float(ShadowMargin * dpr);
                const QRectF q = QRectF(panel).adjusted(-m, -m, m, m);
                setupQuad(glass,
                          float(2 * q.left() / fb.width() - 1), float(1 - 2 * q.bottom() / fb.height()),
                          float(2 * q.right() / fb.width() - 1), float(1 - 2 * q.top() / fb.height()));
                glBindTexture(GL_TEXTURE_2D, pingA->texture());
                glass.setUniformValue("uTex", 0);
                glass.setUniformValue("uFbH", float(fb.height()));
                glass.setUniformValue("uCenter", QVector2D(QRectF(panel).center()));
                glass.setUniformValue("uHalf", QVector2D(panel.width() / 2.f, panel.height() / 2.f));
                glass.setUniformValue("uCapOrigin", QVector2D(cap.topLeft()));
                glass.setUniformValue("uCapSize", QVector2D(cap.width(), cap.height()));
                glass.setUniformValue("uRadius", radius);
                glass.setUniformValue("uShadow", shadow);
                glass.setUniformValue("uShadowY", float(ShadowY * dpr));
                glass.setUniformValue("uShadowAlpha", float(th.shadow.alphaF()));
                glass.setUniformValue("uDpr", dpr);
                glass.setUniformValue("uTint", float(std::min(1.0, th.glassTintAmount(textSurface) + (inactive ? 0.1 : 0.0))));
                glass.setUniformValue("uTintColor", QVector3D(th.glassTint.redF(), th.glassTint.greenF(), th.glassTint.blueF()));
                glass.setUniformValue("uRim", float(th.glassRim() * (inactive ? 0.5 : 1.0)));
                glass.setUniformValue("uEdge", float(th.glassEdge.alphaF()));
                glass.setUniformValue("uSheen", th.dark ? 0.03f : 0.05f);
                glass.setUniformValue("uLensZone", LensZone);
                // Bewegung reduzieren: Linse halbiert
                glass.setUniformValue("uLensStrength", th.reduceMotion ? LensStrength / 2 : LensStrength);
                glass.setUniformValue("uEdgeBlur", EdgeBlur);
                glass.setUniformValue("uChroma", Chroma);
                glass.setUniformValue("uSaturation", Saturation);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                glass.release();
                vbo.release();
                drawn = true;
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
        glViewport(vp[0], vp[1], vp[2], vp[3]);
        blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        scissor ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
        depth ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        stencil ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
        return drawn;
    }

private:
    static bool build(QOpenGLShaderProgram& prog, const char* fs)
    {
        prog.addShaderFromSourceCode(QOpenGLShader::Vertex, QuadVs);
        prog.addShaderFromSourceCode(QOpenGLShader::Fragment, fs);
        prog.bindAttributeLocation("aPos", 0);
        return prog.link();
    }

    void ensure(std::unique_ptr<QOpenGLFramebufferObject>& fbo, const QSize& size)
    {
        if (fbo && fbo->size() == size) {
            return;
        }
        fbo = std::make_unique<QOpenGLFramebufferObject>(size);
        glBindTexture(GL_TEXTURE_2D, fbo->texture());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    void setupQuad(QOpenGLShaderProgram& prog, float x0, float y0, float x1, float y1)
    {
        prog.setUniformValue("uRect", QVector4D(x0, y0, x1, y1));
        prog.enableAttributeArray(0);
        prog.setAttributeBuffer(0, GL_FLOAT, 0, 2);
    }

    void pass(QOpenGLFramebufferObject* target, GLuint tex, const QVector2D& dir)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, target->handle());
        glBindTexture(GL_TEXTURE_2D, tex);
        blur.setUniformValue("uDir", dir);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    bool ok = false;
    QOpenGLShaderProgram blur, glass;
    QOpenGLBuffer vbo;
    std::unique_ptr<QOpenGLFramebufferObject> resolve, halved, pingA, pingB;
};

}  // namespace

GlassPanel::GlassPanel(QWidget* content, qreal radius, bool textSurface)
    : radius(radius)
    , textSurface(textSurface)
    , proxy(new QGraphicsProxyWidget(this))
{
    content->setAttribute(Qt::WA_TranslucentBackground);
    content->setAutoFillBackground(false);
    proxy->setWidget(content);
    setZValue(10);
}

QWidget* GlassPanel::content() const
{
    return proxy->widget();
}

void GlassPanel::setGeometry(const QRectF& rect)
{
    prepareGeometryChange();
    size = rect.size();
    setPos(rect.topLeft());
    proxy->setPos(0, 0);
    proxy->resize(size);
}

void GlassPanel::setRadius(qreal r)
{
    if (r != radius) {
        radius = r;
        update();
    }
}

QRectF GlassPanel::boundingRect() const
{
    return QRectF(QPointF(0, 0), size).adjusted(-ShadowMargin, -ShadowMargin, ShadowMargin, ShadowMargin);
}

void GlassPanel::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget)
{
    const QRectF local(QPointF(0, 0), size);
    const qreal r = std::min({radius, size.width() / 2, size.height() / 2});  // Kapsel = Höhe / 2
    auto gl = qobject_cast<QOpenGLWidget*>(widget);
    auto view = gl ? qobject_cast<QGraphicsView*>(gl->parentWidget()) : nullptr;
    auto ctx = QOpenGLContext::currentContext();

    bool drawn = false;
    if (view && ctx && !theme().reduceTransparency) {
        const qreal dpr = gl->devicePixelRatioF();
        const QRectF viewRect = view->mapFromScene(mapToScene(local)).boundingRect();
        const QRect px(QPoint(qRound(viewRect.x() * dpr), qRound(viewRect.y() * dpr)),
                       QSize(qRound(size.width() * dpr), qRound(size.height() * dpr)));
        painter->beginNativePainting();
        drawn = GlassRenderer::forContext(ctx)->draw(px, gl->size() * dpr, float(r * dpr), float(dpr), textSurface);
        painter->endNativePainting();
    }

    painter->setRenderHint(QPainter::Antialiasing);
    if (!drawn) {  // ohne Blur-fähiges GL oder mit "Transparenz reduzieren"
        paintGlass(*painter, local, r, textSurface);
    }
    else if (theme().increaseContrast) {  // Kontrast erhöhen: sichtbarer Rand um die Linse
        painter->setPen(QPen(theme().glassBorder, 1));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(local.adjusted(0.5, 0.5, -0.5, -0.5), r, r);
    }
}

void GlassPanel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();  // Klicks auf das Glas nicht an die 3D-Navigation durchreichen
}

#include "moc_GlassPanel.cpp"
