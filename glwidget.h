#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Compatibility>
#include <QMatrix4x4>
#include <QString>
#include "mesh.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Compatibility
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void loadMesh(QString fileName);

protected:
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

private:
    void draw();

    QMatrix4x4 m_projection;
    Mesh * m_mesh;
    GLfloat * test_vertices;
    bool m_isPainting;
};

#endif // GLWIDGET_H
