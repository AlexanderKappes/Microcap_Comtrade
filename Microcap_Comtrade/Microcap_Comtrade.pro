QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

contains(TARGET_ARCH, x86_64) {
    ARCHITECTURE = x64
} else {
    ARCHITECTURE = x86
}

win32-g++:contains(ARCHITECTURE, x86): {
    INCLUDEPATH += C:/boost_1_84_0/boost_mingw1120_64/include/boost-1_84
    LIBS += "-LC:/boost/boost_mingw1120_64/lib" \
}

win32-g++:contains(ARCHITECTURE, x64): {
    INCLUDEPATH += C:/boost_1_84_0/boost_mingw1120_64/include/boost-1_84
    LIBS += "-LC:/boost/boost_mingw1120_64/lib" \
}

SOURCES += \
    Comtrade.cpp \
    SignalComtr.cpp \
    Text_read.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Comtrade.hpp \
    SignalComtr.hpp \
    Text_read.hpp \
    mainwindow.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
