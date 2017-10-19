#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T12:31:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracing
TEMPLATE = app
CONFIG += static

SOURCES += main.cpp\
        mainwindow.cpp \
    tiny_obj_loader.cc \
    Camera.cpp \
    DataStructure.cpp \
    ImageData.cpp \
    Initialize.cpp \
    kdTree.cpp \
    LightRay.cpp \
    Point.cpp \
    RayInitialization.cpp \
    Triangle.cpp \
    Vector.cpp \
    DialogLights.cpp \
    Colour.cpp \
    Ray.cpp \
    LightPoint.cpp \
    Intersection.cpp \
    DialogOptions.cpp \
    RenderOptions.cpp \
    IntersectionLine.cpp \
    AABB.cpp \
    PhotonMapping.cpp \
    PhotonPoint.cpp \
    RayTracing.cpp \
    KdTreePhoton.cpp

HEADERS  += mainwindow.h \
    Camera.h \
    DataStructure.h \
    ImageData.h \
    initialize.h \
    kdTree.h \
    LightRay.h \
    Point.h \
    RayInitialization.h \
    tiny_obj_loader.h \
    Triangle.h \
    Vector.h \
    DialogLights.h \
    Colour.h \
    Ray.h \
    LightPoint.h \
    Intersection.h \
    DialogOptions.h \
    RenderOptions.h \
    IntersectionLine.h \
    AABB.h \
    PhotonMapping.h \
    PhotonPoint.h \
    RayTracing.h \
    KdTreePhoton.h

FORMS    += mainwindow.ui \
    DialogLights.ui \
    DialogOptions.ui

INCLUDEPATH += $$PWD/../../../../../boost_1_57_0
DEPENDPATH += $$PWD/../../../../../boost_1_57_0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../boost_1_57_0/stage/lib/ -llibboost_thread-vc120-mt-1_57
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../boost_1_57_0/stage/lib/ -llibboost_thread-vc120-mt-gd-1_57
