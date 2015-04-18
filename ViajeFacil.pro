#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T18:38:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViajeFacil
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fecha.cpp \
    Negos.cpp \
    Oficinas.cpp \
    Peticiones.cpp \
    debug/moc_mainwindow.cpp \
    negos.cpp \
    oficinas.cpp \
    peticiones.cpp

HEADERS  += mainwindow.h \
    fecha.h \
    Header.h \
    negos.h \
    ui_mainwindow.h \
    nego.h \
    oficinas.h \
    owner.h \
    peticion.h \
    header.h

FORMS    += mainwindow.ui
