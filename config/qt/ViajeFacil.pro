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
QMAKE_CXXFLAGS += -fpermissive

SOURCES += ../../source/fecha.cpp \
    ../../source/main.cpp \
    ../../source/mainwindow.cpp \
    ../../source/nego.cpp \
    ../../source/oficina.cpp \
    ../../source/peticion.cpp \
    ../../source/mainwindow2.cpp

HEADERS  += ../../source/fecha.h \
    ../../source/header.h \
    ../../source/mainwindow.h \
    ../../source/nego.h \
    ../../source/oficina.h \
    ../../source/owner.h \
    ../../source/peticion.h \
    ../../source/mainwindow2.h

FORMS    += ../../source/mainwindow.ui \
    ../../source/mainwindow2.ui
