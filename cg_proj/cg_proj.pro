QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3DObjects/baseobject.cpp \
    MathObjects/matrix.cpp \
    MathObjects/point.cpp \
    MathObjects/transformmatrix.cpp \
    MathObjects/triangle.cpp \
    MathObjects/vector.cpp \
    camera.cpp \
    color.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    3DObjects/baseobject.h \
    MathObjects/matrix.h \
    MathObjects/point.h \
    MathObjects/transformmatrix.h \
    MathObjects/triangle.h \
    MathObjects/vector.h \
    camera.h \
    color.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
