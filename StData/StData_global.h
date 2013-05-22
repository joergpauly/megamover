/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   13.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef STDATA_GLOBAL_H
#define STDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STDATA_LIBRARY)
#  define STDATASHARED_EXPORT Q_DECL_EXPORT
#else
#  define STDATASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STDATA_GLOBAL_H
