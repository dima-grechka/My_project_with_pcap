#-------------------------------------------------
#
# Project created by QtCreator 2020-12-26T17:30:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_program_with_pcap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    mythread.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/WpdPack/Lib/ -lwpcap -lpacket

INCLUDEPATH += $$PWD/WpdPack/Include
DEPENDPATH += $$PWD/WpdPack/Include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/WpdPack/Lib/wpcap.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/WpdPack/Lib/libwpcap.a
