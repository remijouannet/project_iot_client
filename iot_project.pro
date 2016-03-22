#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T16:29:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = iot_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    cpu_usage.cpp \
    mem_info.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    cpu_usage.h \
    mem_info.h

FORMS    += mainwindow.ui
