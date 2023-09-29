QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovementModeling
TEMPLATE = app

SOURCES += main.cpp\
    view/mainwindow.cpp \
    model/inertialmodule.cpp \
    ../../import/qcustomplot.cpp

HEADERS  += view/mainwindow.h \
    model/inertialmodule.h \
    ../../import/qcustomplot.h

FORMS    += view/mainwindow.ui

include(../../common.pro)
include(../../app.pro)
