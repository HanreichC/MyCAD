// SPDX-License-Identifier: LGPL-2.1-or-later

#include "GlassPanel.h"

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
#include <QStyleHints>

#include <memory>

using namespace Gui::Shell;

namespace
{

constexpr qreal ShadowMargin = 28.0;  // logische Pixel um das Panel herum für den Schatten

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

const char* GlassFs = R"(
#version 120
uniform sampler2D uTex;
uniform float uFbH;
uniform vec2 uCenter, uHalf, uCapOrigin, uCapSize;
uniform float uRadius, uShadow, uDpr, uDark;

float sdRound(vec2 p, vec2 b, float r) {
    vec2 q = abs(p) - b + vec2(r);
    return length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - r;
}
vec3 blurred(vec2 p) {
    vec2 uv = (p - uCapOrigin) / uCapSize;
    uv.y = 1.0 - uv.y;
    return texture2D(uTex, clamp(uv, 0.0, 1.0)).rgb;
}
void main() {
    vec2 p = vec2(gl_FragCoord.x, uFbH - gl_FragCoord.y);   // oben-links-Koordinaten wie Qt
    vec2 rel = p - uCenter;
    float d = sdRound(rel, uHalf, uRadius);
    float e = uDpr;
    vec2 n = normalize(vec2(sdRound(rel + vec2(e, 0.0), uHalf, uRadius) - sdRound(rel - vec2(e, 0.0), uHalf, uRadius),
                            sdRound(rel + vec2(0.0, e), uHalf, uRadius) - sdRound(rel - vec2(0.0, e), uHalf, uRadius)) + 1e-6);
    float inside = clamp(0.5 - d, 0.0, 1.0);
    bool dark = uDark > 0.5;

    // weicher Schatten, leicht nach unten versetzt
    float ds = sdRound(rel - vec2(0.0, 6.0 * uDpr), uHalf, uRadius);
    float shadow = pow(1.0 - smoothstep(-uShadow * 0.3, uShadow, ds), 2.0) * (dark ? 0.45 : 0.16);

    // Linse: zum Rand hin wird der Hintergrund nach innen gezogen, mit leichter Farbaufspaltung
    float t = -d;
    float bend = 1.0 - smoothstep(0.0, 20.0 * uDpr, t);
    vec2 off = n * bend * bend * 18.0 * uDpr;
    vec3 col = vec3(blurred(p - off * 1.08).r, blurred(p - off).g, blurred(p - off * 0.92).b);

    // Vibrancy + Tönung
    float l = dot(col, vec3(0.299, 0.587, 0.114));
    col = mix(vec3(l), col, 1.4);
    col = dark ? mix(col, vec3(0.12, 0.12, 0.14), 0.42) : mix(col, vec3(1.0), 0.38);

    // Glanzkante: oben-links und unten-rechts heller
    float rim = 1.0 - smoothstep(0.0, 1.6 * uDpr, t);
    float spec = rim * (0.3 + 0.7 * abs(dot(n, normalize(vec2(-0.45, -1.0)))));
    col += spec * (dark ? 0.32 : 0.55);
    // feiner Innenverlauf von oben
    col += (1.0 - smoothstep(0.0, 2.0 * uHalf.y, rel.y + uHalf.y)) * (dark ? 0.03 : 0.05);

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
    bool draw(const QRect& panel, const QSize& fb, float radius, float shadow, float dpr, bool dark)
    {
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
            const QSize small(std::max(1, cap.width() / 4), std::max(1, cap.height() / 4));
            ensure(resolve, cap.size());
            ensure(pingA, small);
            ensure(pingB, small);

            // 1:1 auflösen (Quelle kann multisampled sein), dann auf 1/4 verkleinern
            const int gy0 = fb.height() - (cap.y() + cap.height());
            glBindFramebuffer(GL_READ_FRAMEBUFFER, prevFbo);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolve->handle());
            glBlitFramebuffer(cap.x(), gy0, cap.x() + cap.width(), gy0 + cap.height(),
                              0, 0, cap.width(), cap.height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, resolve->handle());
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pingA->handle());
            glBlitFramebuffer(0, 0, cap.width(), cap.height(),
                              0, 0, small.width(), small.height(), GL_COLOR_BUFFER_BIT, GL_LINEAR);

            if (glGetError() == GL_NO_ERROR) {
                vbo.bind();
                glActiveTexture(GL_TEXTURE0);
                glViewport(0, 0, small.width(), small.height());
                blur.bind();
                setupQuad(blur, -1, -1, 1, 1);
                blur.setUniformValue("uTex", 0);
                for (int i = 0; i < 2; ++i) {
                    pass(pingB.get(), pingA->texture(), QVector2D(1.6f / small.width(), 0));
                    pass(pingA.get(), pingB->texture(), QVector2D(0, 1.6f / small.height()));
                }

                glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
                glViewport(vp[0], vp[1], vp[2], vp[3]);
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                glass.bind();
                const QRectF q = QRectF(panel).adjusted(-shadow, -shadow, shadow, shadow);
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
                glass.setUniformValue("uDpr", dpr);
                glass.setUniformValue("uDark", dark ? 1.f : 0.f);
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
    std::unique_ptr<QOpenGLFramebufferObject> resolve, pingA, pingB;
};

bool isDark()
{
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}

}  // namespace

GlassPanel::GlassPanel(QWidget* content, qreal radius)
    : radius(radius)
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

QRectF GlassPanel::boundingRect() const
{
    return QRectF(QPointF(0, 0), size).adjusted(-ShadowMargin, -ShadowMargin, ShadowMargin, ShadowMargin);
}

void GlassPanel::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget)
{
    const QRectF local(QPointF(0, 0), size);
    auto gl = qobject_cast<QOpenGLWidget*>(widget);
    auto view = gl ? qobject_cast<QGraphicsView*>(gl->parentWidget()) : nullptr;
    auto ctx = QOpenGLContext::currentContext();

    bool drawn = false;
    if (view && ctx) {
        const qreal dpr = gl->devicePixelRatioF();
        const QRectF viewRect = view->mapFromScene(mapToScene(local)).boundingRect();
        const QRect px(QPoint(qRound(viewRect.x() * dpr), qRound(viewRect.y() * dpr)),
                       QSize(qRound(size.width() * dpr), qRound(size.height() * dpr)));
        painter->beginNativePainting();
        drawn = GlassRenderer::forContext(ctx)->draw(px, gl->size() * dpr, float(radius * dpr),
                                                     float(ShadowMargin * dpr), float(dpr), isDark());
        painter->endNativePainting();
    }

    if (!drawn) {  // ponytail: ohne Blur-fähiges GL nur halbtransparente Fläche
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(isDark() ? QColor(30, 30, 34, 225) : QColor(250, 250, 252, 225));
        painter->drawRoundedRect(local, radius, radius);
    }
}

void GlassPanel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();  // Klicks auf das Glas nicht an die 3D-Navigation durchreichen
}

#include "moc_GlassPanel.cpp"
