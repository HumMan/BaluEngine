/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

#include <baluEngine.h>

#include <../Source/Render/DrawingHelper.h>

using namespace BaluEngine;

class GLWidgetPrivate
{
public:
    WorldInstance::IScene* scene_instance;
    WorldInstance::TScreen* screen;
    WorldDef::IViewport* main_viewport;
    WorldInstance::TView main_viewport_view;
    WorldInstance::IDirector* director;
    WorldDef::IWorld* demo_world;
    WorldInstance::IWorld* demo_world_instance;
};

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_xRot(0),
      m_yRot(0),
      m_zRot(0),
      d_ptr(new GLWidgetPrivate())
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::update()
{
    QOpenGLWidget::update();
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup()
{
    makeCurrent();

    WorldInstance::IDirector::Destroy(d_ptr->director, false);

    doneCurrent();
}


void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    auto assets_dir = "c:/Users/kop3n/Documents/GitHub/BaluEngine/Output/Debug/assets";
    d_ptr->director = WorldInstance::IDirector::Create(assets_dir);
    d_ptr->director->Initialize(false);
    d_ptr->demo_world = WorldDef::CreateWorld();
    d_ptr->demo_world->LoadFromXML("c:/Users/kop3n/Documents/GitHub/BaluEngine/Example/demo_test_2.xml");
    d_ptr->screen = new WorldInstance::TScreen(d_ptr->director->GetScreenSize());

    d_ptr->main_viewport_view = WorldInstance::TView(BaluLib::TVec2(0.5, 0.5), BaluLib::TVec2(1, 1));

    std::string error;
    bool compile_success;
    d_ptr->demo_world_instance = WorldInstance::CreateWorld(
                d_ptr->demo_world,
                d_ptr->director->GetResources(), assets_dir, true, compile_success, error);

    d_ptr->director->SetWorldInstance(d_ptr->demo_world_instance);

    d_ptr->director->SetSymulatePhysics(true);
}

void GLWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // glDisable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

//    m_world.setToIdentity();
//    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
//    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
//    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
//    m_program->bind();
//    m_program->setUniformValue(m_projMatrixLoc, m_proj);
//    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
//    QMatrix3x3 normalMatrix = m_world.normalMatrix();
//    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

//    glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

//    m_program->release();

    d_ptr->director->Step(0.01);
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
//    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
//    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
//    int dx = event->x() - m_lastPos.x();
//    int dy = event->y() - m_lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(m_xRot + 8 * dy);
//        setYRotation(m_yRot + 8 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(m_xRot + 8 * dy);
//        setZRotation(m_zRot + 8 * dx);
//    }
//    m_lastPos = event->pos();
}
