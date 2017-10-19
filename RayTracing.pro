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

SOURCES += Source\main.cpp\
        Source\mainwindow.cpp \
    Source\tiny_obj_loader.cc \
    Source\Camera.cpp \
    Source\DataStructure.cpp \
    Source\ImageData.cpp \
    Source\Initialize.cpp \
    Source\kdTree.cpp \
    Source\LightRay.cpp \
    Source\Point.cpp \
    Source\RayInitialization.cpp \
    Source\Triangle.cpp \
    Source\Vector.cpp \
    Source\DialogLights.cpp \
    Source\Colour.cpp \
    Source\Ray.cpp \
    Source\LightPoint.cpp \
    Source\Intersection.cpp \
    Source\DialogOptions.cpp \
    Source\RenderOptions.cpp \
    Source\IntersectionLine.cpp \
    Source\AABB.cpp \
    Source\PhotonMapping.cpp \
    Source\PhotonPoint.cpp \
    Source\RayTracing.cpp \
    Source\KdTreePhoton.cpp

HEADERS  += Source\mainwindow.h \
    Source\Camera.h \
    Source\DataStructure.h \
    Source\ImageData.h \
    Source\initialize.h \
    Source\kdTree.h \
    Source\LightRay.h \
    Source\Point.h \
    Source\RayInitialization.h \
    Source\tiny_obj_loader.h \
    Source\Triangle.h \
    Source\Vector.h \
    Source\DialogLights.h \
    Source\Colour.h \
    Source\Ray.h \
    Source\LightPoint.h \
    Source\Intersection.h \
    Source\DialogOptions.h \
    Source\RenderOptions.h \
    Source\IntersectionLine.h \
    Source\AABB.h \
    Source\PhotonMapping.h \
    Source\PhotonPoint.h \
    Source\RayTracing.h \
    Source\KdTreePhoton.h

FORMS    += Source\mainwindow.ui \
    Source\DialogLights.ui \
    Source\DialogOptions.ui

INCLUDEPATH += $$PWD/../../../../../boost_1_57_0
DEPENDPATH += $$PWD/../../../../../boost_1_57_0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../boost_1_57_0/stage/lib/ -llibboost_thread-vc120-mt-1_57
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../boost_1_57_0/stage/lib/ -llibboost_thread-vc120-mt-gd-1_57
