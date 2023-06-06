#-------------------------------------------------
#
# Project created by QtCreator 2022-09-25T15:46:05
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = site_search
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG +=C++11

SOURCES += \
        main.cpp \
        widget.cpp \
    person.cpp \
    desk.cpp \
    subwidget.cpp \
    chuangkou.cpp \
    map.cpp \
    result.cpp \
    chuangsearch.cpp \
    chuangshow.cpp \
    clientwidget.cpp \
    canteenwidget.cpp \
    template.cpp \
    thread.cpp \
    information.cpp \
    node.cpp

HEADERS += \
        widget.h \
    person.h \
    desk.h \
    subwidget.h \
    chuangkou.h \
    map.h \
    result.h \
    chuangsearch.h \
    chuangshow.h \
    clientwidget.h \
    canteenwidget.h \
    abstract.h \
    const.h \
    template.h \
    thread.h \
    information.h \
    node.h

FORMS += \
        widget.ui \
    subwidget.ui \
    map.ui \
    result.ui \
    chuangsearch.ui \
    chuangshow.ui \
    clientwidget.ui \
    canteenwidget.ui \
    information.ui

RESOURCES += \
    image.qrc
