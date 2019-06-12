#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T10:18:09
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MongoTest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


INCLUDEPATH += \
    $$PWD/../mongoDBlib/include \
    $$PWD/../mongoDBlib/include/bsoncxx \
    $$PWD/../mongoDBlib/include/mongocxx/v_noabi

LIBS += \
    -L$$PWD/../mongoDBlib/lib \
    -lmongoc-static-1.0 \
    -lmongocxx \
    -lbsoncxx

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mongodb.cpp

HEADERS += \
        mainwindow.h \
    mongodb.h

FORMS += \
        mainwindow.ui
