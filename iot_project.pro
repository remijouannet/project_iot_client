#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T16:29:00
#
#-------------------------------------------------

QT       += core gui widgets printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport network

TARGET = iot_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    client_tcp.cpp \
    protocole.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    client_tcp.h \
    protocole.h

FORMS    += mainwindow.ui
