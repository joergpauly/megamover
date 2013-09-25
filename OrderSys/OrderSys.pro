#-------------------------------------------------
#
# Project created by QtCreator 2013-05-09T15:08:33
#
#-------------------------------------------------

QT       += core widgets gui sql

TARGET = OrderSys
TEMPLATE = lib

VERSION = 3.0.1001

DEFINES += ORDERSYS_LIBRARY

SOURCES += \
    corders.cpp

HEADERS +=\
        OrderSys_global.h \
    corders.h

unix:!symbian{
    maemo5    {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    corders.ui

INCLUDEPATH += \
    ../MEGAMover

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DataPads/release/ -lDataPads
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DataPads/debug/ -lDataPads
else:unix: LIBS += -L$$OUT_PWD/../DataPads/ -lDataPads

INCLUDEPATH += $$PWD/../DataPads
DEPENDPATH += $$PWD/../DataPads

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../StData/release/ -lStData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../StData/debug/ -lStData
else:unix: LIBS += -L$$OUT_PWD/../StData/ -lStData

INCLUDEPATH += $$PWD/../StData
DEPENDPATH += $$PWD/../StData
