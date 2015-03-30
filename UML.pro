#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T08:56:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UML
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    element.cpp \
    relacja.cpp \
    koder.cpp

HEADERS  += mainwindow.h \
    element.h \
    relacja.h \
    koder.h

FORMS    += mainwindow.ui

