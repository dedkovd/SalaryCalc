#-------------------------------------------------
#
# Project created by QtCreator 2016-08-16T21:44:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SalaryCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    baseemployee.cpp \
    manager.cpp \
    sales.cpp \
    employeesmodel.cpp \
    addemployeedialog.cpp

HEADERS  += mainwindow.h \
    employee.h \
    baseemployee.h \
    manager.h \
    abstractemployee.h \
    sales.h \
    employeesmodel.h \
    addemployeedialog.h

FORMS    += mainwindow.ui \
    addemployeedialog.ui

RESOURCES += \
    resources.qrc
