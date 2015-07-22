#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T19:43:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml quick

TARGET = qtui
TEMPLATE = app


SOURCES +=     ArgoLoader.cpp \
    torrentobserver.cpp \
        main.cpp\
        mainwindow.cpp \
    qtorrentlistmodel.cpp \
    qtorrentobject.cpp \
    argoqmlcontext.cpp


HEADERS  += mainwindow.h \
    torrentobserver.h \
    ArgoLoader.h \
    qtorrentlistmodel.h \
    qtorrentobject.h \
    argoqmlcontext.h

FORMS    += mainwindow.ui

RESOURCES += \
    qml/qml.qrc
