/****************************************************************************
**
** Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
** Copyright (C) 2013 Klarälvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Compositor.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDOUTPUT_H
#define QWAYLANDOUTPUT_H

#include <QtCompositor/qwaylandexport.h>

#include <QObject>
#include <QRect>
#include <QSize>

QT_BEGIN_NAMESPACE

struct wl_resource;

class QWaylandCompositor;
class QWindow;
class QWaylandOutputPrivate;

namespace QtWayland {
    class Output;
}

class Q_COMPOSITOR_EXPORT QWaylandOutput : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWaylandOutput)
    Q_PROPERTY(QString manufacturer READ manufacturer CONSTANT)
    Q_PROPERTY(QString model READ model CONSTANT)
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
    Q_PROPERTY(QRect availableGeometry READ availableGeometry WRITE setAvailableGeometry NOTIFY availableGeometryChanged)
    Q_PROPERTY(QSize physicalSize READ physicalSize WRITE setPhysicalSize NOTIFY physicalSizeChanged)
    Q_PROPERTY(qreal refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
    Q_PROPERTY(QWaylandOutput::Subpixel subpixel READ subpixel WRITE setSubpixel NOTIFY subpixelChanged)
    Q_PROPERTY(QWaylandOutput::Transform transform READ transform WRITE setTransform NOTIFY transformChanged)
    Q_PROPERTY(int scaleFactor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)
    Q_PROPERTY(QWindow *window READ window CONSTANT)
    Q_ENUMS(Subpixel Transform)
public:
    enum Subpixel {
      SubpixelUnknown = 0,
      SubpixelNone,
      SubpixelHorizontalRgb,
      SubpixelHorizontalBgr,
      SubpixelVerticalRgb,
      SubpixelVerticalBgr
    };

    enum Transform {
        TransformNormal = 0,
        Transform90,
        Transform180,
        Transform270,
        TransformFlipped,
        TransformFlipped90,
        TransformFlipped180,
        TransformFlipped270
    };

    QWaylandOutput(QWaylandCompositor *compositor, QWindow *window,
                   const QString &manufacturer, const QString &model);
    ~QWaylandOutput();

    static QWaylandOutput *fromResource(wl_resource *resource);

    QString manufacturer() const;

    QString model() const;

    QRect geometry() const;
    void setGeometry(const QRect &geometry);

    QRect availableGeometry() const;
    void setAvailableGeometry(const QRect &availableGeometry);

    QSize physicalSize() const;
    void setPhysicalSize(const QSize &size);

    qreal refreshRate() const;
    void setRefreshRate(qreal refreshRateHz);

    Subpixel subpixel() const;
    void setSubpixel(const Subpixel &subpixel);

    Transform transform() const;
    void setTransform(const Transform &transform);

    int scaleFactor() const;
    void setScaleFactor(int scale);

    QWindow *window() const;

    QtWayland::Output *handle();

Q_SIGNALS:
    void geometryChanged();
    void availableGeometryChanged();
    void physicalSizeChanged();
    void refreshRateChanged();
    void scaleFactorChanged();
    void subpixelChanged();
    void transformChanged();
};

QT_END_NAMESPACE

#endif // QWAYLANDOUTPUT_H
