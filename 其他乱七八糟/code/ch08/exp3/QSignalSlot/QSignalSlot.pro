#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T00:10:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSignalSlot
TEMPLATE = app


SOURCES += main.cpp\
        qdlgmain.cpp \
    qdlgchild.cpp

HEADERS  += qdlgmain.h \
    qdlgchild.h

FORMS    += qdlgmain.ui \
    qdlgchild.ui
