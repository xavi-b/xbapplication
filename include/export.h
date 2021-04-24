#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/QtGlobal>

#if defined(XBAPPLICATION_LIBRARY)
#  define XBAPPLICATION_EXPORT Q_DECL_EXPORT
#else
#  define XBAPPLICATION_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORT_H
