#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T10:38:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basicDatabase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbhandler.cpp

HEADERS  += mainwindow.h \
    dbhandler.h

FORMS    += mainwindow.ui
