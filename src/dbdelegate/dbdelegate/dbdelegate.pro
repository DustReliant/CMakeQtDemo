QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

TARGET      = dbdelegate
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

DEFINES     += no_qrc_font
HEADERS     += head.h
SOURCES     += main.cpp
RESOURCES   += main.qrc

INCLUDEPATH += $$PWD

INCLUDEPATH += $$PWD/app
include($$PWD/app/app.pri)

INCLUDEPATH += $$PWD/form
include($$PWD/form/form.pri)

INCLUDEPATH += $$PWD/../core_common
include ($$PWD/../core_common/core_common.pri)
