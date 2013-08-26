/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
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

#include "qopenglwindow.h"
#include "qwindowcompositor.h"

#include <QGuiApplication>
#include <QStringList>
#include <QScreen>
#include <QSurfaceFormat>
#include <QtCompositor/QWaylandOutput>

int main(int argc, char *argv[])
{
    // Enable the following to have touch events generated from mouse events.
    // Very handy for testing touch event delivery without a real touch device.
    // QGuiApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, true);

    QGuiApplication app(argc, argv);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setStencilBufferSize(8);

    QRect geom = screenGeometry;
    if (QCoreApplication::arguments().contains(QLatin1String("-nofullscreen")))
        geom = QRect(screenGeometry.width() / 4, screenGeometry.height() / 4,
                     screenGeometry.width() / 2, screenGeometry.height() / 2);

    QWindowCompositor *compositor = new QWindowCompositor();

    QOpenGLWindow *window = new QOpenGLWindow(format, geom);
    QWaylandOutput *output = new QWaylandOutput(compositor, window);
    output->setRefreshRate(qRound(screen->refreshRate() * 1000.0));
    window->show();

    return app.exec();
}
