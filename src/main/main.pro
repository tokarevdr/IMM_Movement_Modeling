QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovementModeling
TEMPLATE = app

SOURCES += main.cpp\
    view/mainwindow.cpp

HEADERS  += view/mainwindow.h

FORMS    += view/mainwindow.ui

include(../../common.pro)
include(../../app.pro)
