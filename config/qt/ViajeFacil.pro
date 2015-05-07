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
QMAKE_CXXFLAGS += -Wall
INCLUDEPATH += ../../source/include/

SOURCES += ../../source/fecha.cpp \
    ../../source/main.cpp \
    ../../source/nego.cpp \
    ../../source/oficina.cpp \
    ../../source/peticion.cpp \
    ../../source/login.cpp \
    ../../source/owner.cpp \
    ../../source/mainwindow.cpp \
    ../../source/bcrypt.cpp \
    ../../source/diagowner.cpp \
    ../../source/dialognego.cpp \
    dialogpeticiones.cpp

HEADERS  += ../../source/fecha.hpp \
    ../../source/nego.hpp \
    ../../source/oficina.hpp \
    ../../source/owner.hpp \
    ../../source/peticion.hpp \
    ../../source/login.hpp \
    ../../source/mainwindow.hpp \
    ../../source/diagowner.hpp \
    ../../source/dialognego.hpp \
    ../../source/bcrypt.h \
    dialogpeticiones.h

FORMS    += \
    ../../source/login.ui \
    ../../source/mainwindow.ui \
    ../../source/diagowner.ui \
    ../../source/dialognego.ui \
    dialogpeticiones.ui
