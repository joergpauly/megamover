#-------------------------------------------------
#
# Project created by QtCreator 2013-05-05T10:49:45
#
#-------------------------------------------------

QT       += core gui sql


TARGET = MEGAMover
TEMPLATE = app subdirs

SUBDIRS += \
	DataPads \
	OrderSys

VERSION = 3.0.1001

SOURCES += main.cpp\
        mainwindow.cpp \
    ccore.cpp \
    cdatabasemanager.cpp \
    csettings.cpp \
    coptions.cpp \
    cmandant.cpp \
    cabout.cpp \
    cmdtwahl.cpp \
    cnkr.cpp

HEADERS  += mainwindow.h \
    ccore.h \
    cdatabasemanager.h \
    csettings.h \
    coptions.h \
    cmandant.h \
    cabout.h \
    qtversion.h \
    cmdtwahl.h \
    cnkr.h

FORMS    += mainwindow.ui \
    coptions.ui \
    cmandant.ui \
    cabout.ui \
    cmdtwahl.ui

RESOURCES += \
    MEGAMover.qrc


target.path = /usr/bin
INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../OrderSys/release/ -lOrderSys
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../OrderSys/debug/ -lOrderSys
else:unix: LIBS += -L$$OUT_PWD/../OrderSys/ -lOrderSys

INCLUDEPATH += $$PWD/../OrderSys
DEPENDPATH += $$PWD/../OrderSys

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