#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T21:25:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basicDatabase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database_repo.cpp

HEADERS  += mainwindow.h \
    database_repo.h

FORMS    += mainwindow.ui
