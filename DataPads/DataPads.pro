#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T17:29:05
#
#-------------------------------------------------

QT       += core widgets gui sql

TARGET = DataPads
TEMPLATE = lib

VERSION = 3.0.1003

DEFINES += DATAPADS_LIBRARY

SOURCES += \
    adresspad.cpp \
    cclientaccountpad.cpp \
    cadresssearch.cpp \
    cclientsearch.cpp \
    cquerynavigator.cpp

HEADERS +=\
        DataPads_global.h \
    adresspad.h \
    cclientaccountpad.h \
    cadresssearch.h \
    cclientsearch.h \
    cquerynavigator.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    adresspad.ui \
    cclientaccountpad.ui \
    cadresssearch.ui \
    cclientsearch.ui \
    cquerynavigator.ui

INCLUDEPATH += $$PWD/../MEGAMover
