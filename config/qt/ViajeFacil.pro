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
    ../../source/owner.cpp \
    ../../source/dialogOficinas.cpp \
    ../../source/dialogNego.cpp \
    ../../source/dialogOwner.cpp \
    ../../source/dialogPeticiones.cpp \
    ../../source/dialogLogin.cpp \
    ../../source/mainWindow.cpp \
    ../../source/dialogInforme.cpp \
    ../../source/entradaHistorial.cpp \
    ../../source/test.cpp

HEADERS  += ../../source/fecha.hpp \
    ../../source/nego.hpp \
    ../../source/oficina.hpp \
    ../../source/owner.hpp \
    ../../source/peticion.hpp \
    ../../source/dialogOficinas.hpp \
    ../../source/dialogOwner.hpp \
    ../../source/dialogNego.hpp \
    ../../source/dialogPeticiones.hpp \
    ../../source/dialogLogin.hpp \
    ../../source/mainWindow.hpp \
    ../../source/dialogInforme.hpp \
    ../../source/entradaHistorial.hpp \
    ../../source/pelVector.hpp

FORMS    += ../../source/dialogOficinas.ui \
    ../../source/dialogOwner.ui \
    ../../source/dialogNego.ui \
    ../../source/dialogPeticiones.ui \
    ../../source/dialogLogin.ui \
    ../../source/mainWindow.ui \
    ../../source/dialogInforme.ui
