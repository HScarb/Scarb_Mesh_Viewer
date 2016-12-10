#include "glwidget.h"
#include <iostream>
#include <QMouseEvent>
using namespace std;

GLWidget::GLWidget(QWidget * parent) :QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);
}

GLWidget::~GLWidget()
{
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
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2, 0.2, 0.2, 1);

//    test_vertices = new GLfloat[6];
//    test_vertices[0] = -0.5f;
//    test_vertices[1] = -0.5f;
//    test_vertices[2] = 0.5f;
//    test_vertices[3] = -0.5f;
//    test_vertices[4] = 0.0f;
//    test_vertices[5] = 0.5f;
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(2, GL_FLOAT, 0, test_vertices);

    m_mesh = new Mesh();
    m_mesh->loadPointers("test.hex");
    //m_mesh->loadPointers("test.hex");
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_mesh->vertices);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);


    draw();

    const int indexNum = m_mesh->h_cnt * 24;

    glColor3f(0.3f, 0.8f, 0.3f);
    glDrawElements(GL_QUADS, indexNum, GL_UNSIGNED_SHORT, m_mesh->item_indices);
    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_LINES, indexNum, GL_UNSIGNED_SHORT, m_mesh->wire_indices);
    glColor3f(0.3f, 0.8f, 0.3f);

//    GLushort test_indices[] = {0, 1, 2, 3, 4, 5};
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, test_indices);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GLWidget::resizeGL(int w, int h)
{
//    m_projection.setToIdentity();
//    m_projection.perspective(60.0f, w/float(h), 0.01f, 1000.0f);
//    int side = qMin(w, h);
//    glViewport((w - side) / 2, (h - side) / 2, side, side);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif
//    glMatrixMode(GL_MODELVIEW);
    //glViewport(0, 0, 600, 600);
    int side = qMin(w, h);
    glViewport((w - side) / 2, (h - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, +50, -50, +50, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void GLWidget::draw()
{
    glColor3f(1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}
