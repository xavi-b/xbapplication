TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets network
DESTDIR         = $$PWD

SUBDIRS += \
    src/

include(src/src.pri)
