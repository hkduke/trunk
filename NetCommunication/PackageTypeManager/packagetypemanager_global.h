#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PACKAGETYPEMANAGER_LIB)
#  define PACKAGETYPEMANAGER_EXPORT Q_DECL_EXPORT
# define BASEPACKAGE_EXPORT Q_DECL_EXPORT
# else
#  define PACKAGETYPEMANAGER_EXPORT Q_DECL_IMPORT
# define BASEPACKAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PACKAGETYPEMANAGER_EXPORT
# define BASEPACKAGE_EXPORT
#endif
