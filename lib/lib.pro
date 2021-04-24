TEMPLATE        = lib
CONFIG         += c++17
DEFINES        += QT_DEPRECATED_WARNINGS
QT             += widgets network
TARGET          = xbapplication
DESTDIR         = $$PWD

DEFINES += XBAPPLICATION_LIBRARY

qm_file.files = $$files($$[QT_INSTALL_TRANSLATIONS]/qtbase_*.qm)
qm_file.base = $$[QT_INSTALL_TRANSLATIONS]
qm_file.prefix = qt_translations
RESOURCES += qm_file

SUBDIRS += \
    $$PWD/../include \
    $$PWD/../src

include($$PWD/../include/include.pri)
include($$PWD/../src/src.pri)
