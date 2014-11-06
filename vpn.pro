#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T21:00:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vpn
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    listdialog.cpp \
    file.cpp \
    linelist.cpp

HEADERS  += logindialog.h \
    listdialog.h \
    file.hpp \
    linelist.hpp

FORMS    += logindialog.ui \
    listdialog.ui

OTHER_FILES += \
    list.ini
