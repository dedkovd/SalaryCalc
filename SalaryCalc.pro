#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T21:44:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SalaryCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    baseemployee.cpp

HEADERS  += mainwindow.h \
    employee.h \
    baseemployee.h

FORMS    += mainwindow.ui
