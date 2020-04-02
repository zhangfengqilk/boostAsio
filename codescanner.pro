TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        serialport/ABCodeScannerComConnect.cpp \
        serialport/CodeScannerComConnect.cpp \
        serialport/CodeScannerFrame.cpp \
        serialport/ComConnect.cpp \
        serialport/Connect.cpp \
        serialport/CustomTool.cpp \
        serialport/TimeStamp.cpp \
        testconsumer.cpp

HEADERS += \
    serialport/ABCodeScannerComConnect.h \
    serialport/CodeScannerComConnect.h \
    serialport/CodeScannerFrame.h \
    serialport/ComConnect.h \
    serialport/Connect.h \
    serialport/CustomTool.h \
    serialport/Global.h \
    serialport/TimeStamp.h \
    serialport/TypeDef.h \
    testconsumer.h

# boost
LIBS += -lboost_system  -lpthread -lboost_thread

DISTFILES += \
    README.md
