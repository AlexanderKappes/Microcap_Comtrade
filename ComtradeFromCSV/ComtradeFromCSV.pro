QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SignalComtr.cpp \
    main.cpp \
    mainwindow.cpp \
    Text_read.cpp \
    Comtrade.cpp \
    Text_write.cpp

HEADERS += \
    Header.hpp \
    SignalComtr.hpp \
    mainwindow.h \
    Text_read.hpp \
    Comtrade.hpp \
    Text_write.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
