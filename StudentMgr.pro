#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T16:49:07
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentMgr
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    connectdialog.cpp \
    sqlserver.cpp \
    lectureeditor.cpp \
    thdconnect.cpp \
    thdsqlexec.cpp \
    sqlfactory.cpp \
    myprodlg.cpp \
    majoreditor.cpp \
    lecturemapdialog.cpp \
    lectureselectdialog.cpp \
    studenteditor.cpp

HEADERS += \
        mainwindow.h \
    connectdialog.h \
    structdef.h \
    common.h \
    sqlbase.h \
    sqlserver.h \
    lectureeditor.h \
    thdconnect.h \
    thdsqlexec.h \
    sqlfactory.h \
    sqlcommandbase.h \
    myprodlg.h \
    majoreditor.h \
    lecturemapdialog.h \
    lectureselectdialog.h \
    studenteditor.h

FORMS += \
        mainwindow.ui \
    connectdialog.ui \
    lectureeditor.ui \
    majoreditor.ui \
    lecturemapdialog.ui \
    lectureselectdialog.ui \
    studenteditor.ui

#win32:CONFIG += console
#for debug output!
#remove it when use release mode
