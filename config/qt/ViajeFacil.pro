#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T18:38:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViajeFacil
TEMPLATE = app
CONFIG += c++11


SOURCES += ../../source/fecha.cpp \
    ../../source/main.cpp \
    ../../source/mainwindow.cpp \
    ../../source/nego.cpp \
    ../../source/oficina.cpp \
    ../../source/peticion.cpp

HEADERS  += ../../source/fecha.h \
    ../../source/header.h \
    ../../source/mainwindow.h \
    ../../source/nego.h \
    ../../source/oficina.h \
    ../../source/owner.h \
    ../../source/peticion.h \
    ../../source/ui_mainwindow.h

FORMS    += ../../source/mainwindow.ui
