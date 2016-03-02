#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T02:59:09
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = DataClasses
TEMPLATE = lib

DEFINES += DATACLASSES_LIBRARY

SOURCES += ccoworker.cpp \
    cadress.cpp \
    cdata.cpp

HEADERS += ccoworker.h\
        dataclasses_global.h \
    cadress.h \
    cdata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
