#-------------------------------------------------
#
# Project created by QtCreator 2013-05-13T13:39:25
#
#-------------------------------------------------

QT       += core widgets gui sql

TARGET = StData
TEMPLATE = lib

DEFINES += STDATA_LIBRARY

SOURCES += \
    cclient.cpp \
    cadresses.cpp

HEADERS +=\
        StData_global.h \
    cclient.h \
    cadresses.h \
    stdata.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    cclient.ui \
    cadresses.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DataPads/release/ -lDataPads
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DataPads/debug/ -lDataPads
else:unix: LIBS += -L$$OUT_PWD/../DataPads/ -lDataPads

INCLUDEPATH += $$PWD/../DataPads
DEPENDPATH += $$PWD/../DataPads
