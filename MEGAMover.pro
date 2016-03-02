TEMPLATE = subdirs

VERSION = 3.0.1001

SUBDIRS += \
    DataPads \
    StData \
    OrderSys \
    MEGAMover \
    DataClasses

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/StData/release/ -lStData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/StData/debug/ -lStData
else:unix: LIBS += -L$$OUT_PWD/StData/ -lStData

INCLUDEPATH += $$PWD/StData
DEPENDPATH += $$PWD/StData

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/OrderSys/release/ -lOrderSys
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/OrderSys/debug/ -lOrderSys
else:unix: LIBS += -L$$OUT_PWD/OrderSys/ -lOrderSys

INCLUDEPATH += $$PWD/OrderSys
DEPENDPATH += $$PWD/OrderSys

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/DataPads/release/ -lDataPads
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/DataPads/debug/ -lDataPads
else:unix: LIBS += -L$$OUT_PWD/DataPads/ -lDataPads

INCLUDEPATH += $$PWD/DataPads
DEPENDPATH += $$PWD/DataPads
