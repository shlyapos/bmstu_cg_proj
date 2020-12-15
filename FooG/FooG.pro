QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MathObjects/matrix.cpp \
    MathObjects/transformmatrix.cpp \
    MathObjects/vector2.cpp \
    MathObjects/vector3.cpp \
    addlightwindow.cpp \
    addmodelwindow.cpp \
    camera.cpp \
    cameranew.cpp \
    drawer.cpp \
    lightsourcepoint.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    scene.cpp \
    zbuffer.cpp

HEADERS += \
    MathObjects/matrix.h \
    MathObjects/transformmatrix.h \
    MathObjects/vector2.h \
    MathObjects/vector3.h \
    MathObjects/vector3.hpp \
    addlightwindow.h \
    addmodelwindow.h \
    camera.h \
    cameranew.h \
    drawer.h \
    lightsourcepoint.h \
    mainwindow.h \
    model.h \
    scene.h \
    vector2.h \
    zbuffer.h

FORMS += \
    addlightwindow.ui \
    addmodelwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
