#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T20:49:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scarb_Mesh_Viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    mesh.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    mesh.h \
    meshio.h

FORMS    += mainwindow.ui

LIBS    += C:/Programs/Qt5.7.0/5.7/mingw53_32/lib/libQt5OpenGL.a -lopengl32

RESOURCES += \
    resources.qrc
