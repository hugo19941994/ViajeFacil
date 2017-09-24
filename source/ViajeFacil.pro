#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T18:38:37
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViajeFacil
TEMPLATE = app
CONFIG += c++11
INCLUDEPATH += include
RC_FILE = myapp.rc
QMAKE_CXX = g++
QMAKE_CC = gcc
QMAKE_LINK = g++
QMAKE_CXXFLAGS += "-DEXEC_TEST -Wall -fprofile-arcs -ftest-coverage"
QMAKE_CFLAGS += "-DEXEC_TEST -Wall -fprofile-arcs -ftest-coverage"
QMAKE_LFLAGS += "-fprofile-arcs -ftest-coverage"
QMAKE_CLEAN += *.gcda *.gcno

SOURCES += fecha.cpp \
    main.cpp \
    nego.cpp \
    oficina.cpp \
    peticion.cpp \
    owner.cpp \
    dialogOficinas.cpp \
    dialogNego.cpp \
    dialogOwner.cpp \
    dialogPeticiones.cpp \
    dialogLogin.cpp \
    mainWindow.cpp \
    dialogInforme.cpp \
    entradaHistorial.cpp \
    test.cpp \
    bcrypt.cpp

HEADERS += fecha.hpp \
    nego.hpp \
    oficina.hpp \
    owner.hpp \
    peticion.hpp \
    dialogOficinas.hpp \
    dialogOwner.hpp \
    dialogNego.hpp \
    dialogPeticiones.hpp \
    dialogLogin.hpp \
    mainWindow.hpp \
    dialogInforme.hpp \
    entradaHistorial.hpp \
    pelVector.hpp \
    bcrypt.h

FORMS += dialogOficinas.ui \
    dialogOwner.ui \
    dialogNego.ui \
    dialogPeticiones.ui \
    dialogLogin.ui \
    mainWindow.ui \
    dialogInforme.ui
