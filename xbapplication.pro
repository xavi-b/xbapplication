TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets network
TARGET          = xbapplication
DESTIR          = $$PWD

SUBDIRS += \
    src/

include(src/src.pri)
