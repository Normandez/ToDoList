#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T20:05:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDoList
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addnewtask.cpp \
    event.cpp \
    remindwindow.cpp \
    aboutwindow.cpp

HEADERS  += mainwindow.h \
    addnewtask.h \
    event.h \
    remindwindow.h \
    aboutwindow.h

FORMS    += mainwindow.ui \
    addnewtask.ui \
    remindwindow.ui \
    aboutwindow.ui

RESOURCES += \
    icons.qrc
