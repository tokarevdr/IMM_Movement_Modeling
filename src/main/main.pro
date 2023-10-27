QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovementModeling
TEMPLATE = app

SOURCES += main.cpp\
    view/mainwindow.cpp \
    model/inertialmodule.cpp \
    ../../import/qcustomplot.cpp \
    model/abstractmodulecontroller.cpp \
    model/timermodulecontroller.cpp \
    model/datamodulecontroller.cpp \
    view/angle.cpp \
    view/qcpaxistickerangle.cpp

HEADERS  += view/mainwindow.h \
    model/inertialmodule.h \
    ../../import/qcustomplot.h \
    model/abstractmodulecontroller.h \
    model/timermodulecontroller.h \
    model/datamodulecontroller.h \
    view/angle.h \
    view/qcpaxistickerangle.h

FORMS    += view/mainwindow.ui

include(../../common.pro)
include(../../app.pro)
