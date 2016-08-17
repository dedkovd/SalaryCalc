#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T23:07:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testemployee
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../

SOURCES += tst_testemployee.cpp \
    ../employee.cpp \
    ../baseemployee.cpp \
    ../manager.cpp \
    ../sales.cpp

HEADERS += ../employee.h \
        ../baseemployee.h \
        ../manager.h \
        ../sales.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
